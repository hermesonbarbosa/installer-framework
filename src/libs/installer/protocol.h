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

#ifndef PROTOCOL_H
#define PROTOCOL_H

namespace QInstaller {
namespace Protocol {

const char Create[] = "Create";
const char Destroy[] = "Destroy";
const char Shutdown[] = "Shutdown";
const char Authorize[] = "Authorize";
const char DebugAuthorizationKey[] = "DebugAuthorizationKey";

// QProcessWrapper
const char QProcess[] = "QProcess";
const char QProcessCloseWriteChannel[] = "QProcess::closeWriteChannel";
const char QProcessExitCode[] = "QProcess::exitCode";
const char QProcessExitStatus[] = "QProcess::exitStatus";
const char QProcessKill[] = "QProcess::kill";
const char QProcessReadAll[] = "QProcess::readAll";
const char QProcessReadAllStandardOutput[] = "QProcess::readAllStandardOutput";
const char QProcessReadAllStandardError[] = "QProcess::readAllStandardError";
const char QProcessStartDetached[] = "QProcess::startDetached";
const char QProcessSetWorkingDirectory[] = "QProcess::setWorkingDirectory";
const char QProcessSetEnvironment[] = "QProcess::setEnvironment";
const char QProcessEnvironment[] = "QProcess::environment";
const char QProcessStart3Arg[] = "QProcess::start3";
const char QProcessStart2Arg[] = "QProcess::start2";
const char QProcessState[] = "QProcess::state";
const char QProcessTerminate[] = "QProcess::terminate";
const char QProcessWaitForFinished[] = "QProcess::waitForFinished";
const char QProcessWaitForStarted[] = "QProcess::waitForStarted";
const char QProcessWorkingDirectory[] = "QProcess::workingDirectory";
const char QProcessErrorString[] = "QProcess::errorString";
const char QProcessReadChannel[] = "QProcess::readChannel";
const char QProcessSetReadChannel[] = "QProcess::setReadChannel";
const char QProcessWrite[] = "QProcess::write";
const char QProcessProcessChannelMode[] = "QProcess::processChannelMode";
const char QProcessSetProcessChannelMode[] = "QProcess::setProcessChannelMode";
const char QProcessSetNativeArguments[] = "QProcess::setNativeArguments";

const char GetQProcessSignals[] = "GetQProcessSignals";
const char QProcessSignalBytesWritten[] = "QProcess::bytesWritten";
const char QProcessSignalAboutToClose[] = "QProcess::aboutToClose";
const char QProcessSignalReadChannelFinished[] = "QProcess::readChannelFinished";
const char QProcessSignalError[] = "QProcess::error";
const char QProcessSignalReadyReadStandardOutput[] = "QProcess::readyReadStandardOutput";
const char QProcessSignalReadyReadStandardError[] = "QProcess::readyReadStandardError";
const char QProcessSignalStarted[] = "QProcess::started";
const char QProcessSignalReadyRead[] = "QProcess::readyRead";
const char QProcessSignalStateChanged[] = "QProcess::stateChanged";
const char QProcessSignalFinished[] = "QProcess::finished";


// QSettingsWrapper
const char QSettings[] = "QSettings";
const char QSettingsAllKeys[] = "QSettings::allKeys";
const char QSettingsBeginGroup[] = "QSettings::beginGroup";
const char QSettingsBeginWriteArray[] = "QSettings::beginWriteArray";
const char QSettingsBeginReadArray[] = "QSettings::beginReadArray";
const char QSettingsChildGroups[] = "QSettings::childGroups";
const char QSettingsChildKeys[] = "QSettings::childKeys";
const char QSettingsClear[] = "QSettings::clear";
const char QSettingsContains[] = "QSettings::contains";
const char QSettingsEndArray[] = "QSettings::endArray";
const char QSettingsEndGroup[] = "QSettings::endGroup";
const char QSettingsFallbacksEnabled[] = "QSettings::fallbacksEnabled";
const char QSettingsFileName[] = "QSettings::fileName";
const char QSettingsGroup[] = "QSettings::group";
const char QSettingsIsWritable[] = "QSettings::isWritable";
const char QSettingsRemove[] = "QSettings::remove";
const char QSettingsSetArrayIndex[] = "QSettings::setArrayIndex";
const char QSettingsSetFallbacksEnabled[] = "QSettings::setFallbacksEnabled";
const char QSettingsStatus[] = "QSettings::status";
const char QSettingsSync[] = "QSettings::sync";
const char QSettingsSetValue[] = "QSettings::setValue";
const char QSettingsValue[] = "QSettings::value";
const char QSettingsOrganizationName[] = "QSettings::organizationName";
const char QSettingsApplicationName[] = "QSettings::applicationName";


// RemoteFileEngine
const char QAbstractFileEngine[] = "QAbstractFileEngine";
const char QAbstractFileEngineAtEnd[] = "QAbstractFileEngine::atEnd";
const char QAbstractFileEngineCaseSensitive[] = "QAbstractFileEngine::caseSensitive";
const char QAbstractFileEngineClose[] = "QAbstractFileEngine::close";
const char QAbstractFileEngineCopy[] = "QAbstractFileEngine::copy";
const char QAbstractFileEngineEntryList[] = "QAbstractFileEngine::entryList";
const char QAbstractFileEngineError[] = "QAbstractFileEngine::error";
const char QAbstractFileEngineErrorString[] = "QAbstractFileEngine::errorString";
const char QAbstractFileEngineFileFlags[] = "QAbstractFileEngine::fileFlags";
const char QAbstractFileEngineFileName[] = "QAbstractFileEngine::fileName";
const char QAbstractFileEngineFlush[] = "QAbstractFileEngine::flush";
const char QAbstractFileEngineHandle[] = "QAbstractFileEngine::handle";
const char QAbstractFileEngineIsRelativePath[] = "QAbstractFileEngine::isRelativePath";
const char QAbstractFileEngineIsSequential[] = "QAbstractFileEngine::isSequential";
const char QAbstractFileEngineLink[] = "QAbstractFileEngine::link";
const char QAbstractFileEngineMkdir[] = "QAbstractFileEngine::mkdir";
const char QAbstractFileEngineOpen[] = "QAbstractFileEngine::open";
const char QAbstractFileEngineOwner[] = "QAbstractFileEngine::owner";
const char QAbstractFileEngineOwnerId[] = "QAbstractFileEngine::ownerId";
const char QAbstractFileEnginePos[] = "QAbstractFileEngine::pos";
const char QAbstractFileEngineRead[] = "QAbstractFileEngine::read";
const char QAbstractFileEngineReadLine[] = "QAbstractFileEngine::readLine";
const char QAbstractFileEngineRemove[] = "QAbstractFileEngine::remove";
const char QAbstractFileEngineRename[] = "QAbstractFileEngine::rename";
const char QAbstractFileEngineRmdir[] = "QAbstractFileEngine::rmdir";
const char QAbstractFileEngineSeek[] = "QAbstractFileEngine::seek";
const char QAbstractFileEngineSetFileName[] = "QAbstractFileEngine::setFileName";
const char QAbstractFileEngineSetPermissions[] = "QAbstractFileEngine::setPermissions";
const char QAbstractFileEngineSetSize[] = "QAbstractFileEngine::setSize";
const char QAbstractFileEngineSize[] = "QAbstractFileEngine::size";
const char QAbstractFileEngineSupportsExtension[] = "QAbstractFileEngine::supportsExtension";
const char QAbstractFileEngineExtension[] = "QAbstractFileEngine::extension";
const char QAbstractFileEngineWrite[] = "QAbstractFileEngine::write";

} // namespace Protocol
} // namespace QInstaller

#endif // PROTOCOL_H
