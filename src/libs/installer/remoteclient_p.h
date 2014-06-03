/**************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Installer Framework.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
**************************************************************************/

#ifndef REMOTECLIENT_P_H
#define REMOTECLIENT_P_H

#include "adminauthorization.h"
#include "messageboxhandler.h"
#include "protocol.h"
#include "remoteclient.h"
#include "utils.h"

#include <QCoreApplication>
#include <QElapsedTimer>
#include <QHostAddress>
#include <QMutex>
#include <QPointer>
#include <QTcpSocket>
#include <QThread>
#include <QTimer>

namespace QInstaller {

class KeepAliveObject : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(KeepAliveObject)

public:
    KeepAliveObject(RemoteClient *client)
        : m_timer(0)
        , m_client(client)
    {
    }

public slots:
    void run()
    {
        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
        m_timer->start(1000);
    }

private slots:
    void onTimeout()
    {
        m_timer->stop();

        if (!m_client)
            return;

        {
            // Try to connect to the server. If we succeed the server side running watchdog gets
            // restarted and the server keeps running for another 30 seconds.
            QScopedPointer<QTcpSocket> socket(m_client->connect());
        }

        m_timer->start(1000);
    }

private:
    QTimer *m_timer;
    QPointer<RemoteClient> m_client;
};

class RemoteClientPrivate
{
    Q_DECLARE_PUBLIC(RemoteClient)
    Q_DISABLE_COPY(RemoteClientPrivate)

public:
    RemoteClientPrivate(RemoteClient *parent)
        : q_ptr(parent)
        , m_mutex(QMutex::Recursive)
        , m_port(0)
        , m_startServerAsAdmin(false)
        , m_serverStarted(false)
        , m_serverStarting(false)
        , m_active(false)
        , m_quit(false)
    {
    }

    ~RemoteClientPrivate()
    {
        m_thread.quit();
        m_thread.wait();
    }

    void init(quint16 port, const QHostAddress &address, RemoteClient::Mode mode)
    {
        m_port = port;
        m_mode = mode;
        m_address = address;

        if (m_mode == RemoteClient::Release) {
            QObject *const object = new KeepAliveObject(q_ptr);
            object->moveToThread(&m_thread);
            QObject::connect(&m_thread, SIGNAL(finished()), object, SLOT(deleteLater()));
            m_thread.start();
            QTimer::singleShot(0, object, SLOT(run()));
        } else if (mode == RemoteClient::Debug) {
            m_active = true;
            m_serverStarted = true;
            m_key = QLatin1String(Protocol::DebugAuthorizationKey);
        } else {
            Q_ASSERT_X(false, Q_FUNC_INFO, "RemoteClient mode not set properly.");
        }
    }

    void maybeStartServer() {
        if (m_serverStarted || m_serverCommand.isEmpty())
            return;

        const QMutexLocker ml(&m_mutex);
        if (m_serverStarted)
            return;

        m_serverStarting = true;

        if (m_startServerAsAdmin) {
            AdminAuthorization auth;
            m_serverStarted = auth.authorize() && auth.execute(0, m_serverCommand, m_serverArguments);

            if (!m_serverStarted) {
                // something went wrong with authorizing, either user pressed cancel or entered
                // wrong password
                const QString fallback = m_serverCommand + QLatin1String(" ") + m_serverArguments
                    .join(QLatin1String(" "));

                const QMessageBox::Button res =
                    MessageBoxHandler::critical(MessageBoxHandler::currentBestSuitParent(),
                    QObject::tr("Authorization Error"), QObject::tr("Could not get authorization."),
                    QObject::tr("Could not get authorization that is needed for continuing the "
                        "installation.\n Either abort the installation or use the fallback "
                        "solution by running\n%1\nas root and then clicking ok.").arg(fallback),
                    QMessageBox::Abort | QMessageBox::Ok, QMessageBox::Ok);

                if (res == QMessageBox::Ok)
                    m_serverStarted = true;
            }
        } else {
            m_serverStarted = QInstaller::startDetached(m_serverCommand, m_serverArguments,
                QCoreApplication::applicationDirPath());
        }

        if (m_serverStarted) {
            QElapsedTimer t;
            t.start();
             // 30 seconds ought to be enough for the app to start
            while (m_serverStarting && m_serverStarted && t.elapsed() < 30000) {
                Q_Q(RemoteClient);
                QScopedPointer<QTcpSocket> socket(q->connect());
                if (socket)
                    m_serverStarting = false;
            }
        }
        m_serverStarting = false;
    }

    void maybeStopServer()
    {
        if (!m_serverStarted)
            return;

        const QMutexLocker ml(&m_mutex);
        if (!m_serverStarted)
            return;

        Q_Q(RemoteClient);
        QScopedPointer<QTcpSocket> socket(q->connect());
        if (socket) {
            QDataStream stream(socket.data());
            stream << QString::fromLatin1(Protocol::Authorize);
            stream << m_key;
            stream << QString::fromLatin1(Protocol::Shutdown);
            socket->flush();
        }
        m_serverStarted = false;
    }

private:
    RemoteClient *q_ptr;
    QMutex m_mutex;
    QHostAddress m_address;
    quint16 m_port;
    QString m_socket;
    bool m_startServerAsAdmin;
    bool m_serverStarted;
    bool m_serverStarting;
    bool m_active;
    QString m_serverCommand;
    QStringList m_serverArguments;
    QString m_key;
    QThread m_thread;
    RemoteClient::Mode m_mode;
    volatile bool m_quit;
};

} // namespace QInstaller

#endif // REMOTECLIENT_P_H
