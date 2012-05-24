/* XiVO Client
 * Copyright (C) 2007-2011, Avencall
 *
 * This file is part of XiVO Client.
 *
 * XiVO Client is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version, with a Section 7 Additional
 * Permission as follows:
 *   This notice constitutes a grant of such permission as is necessary
 *   to combine or link this software, or a modified version of it, with
 *   the OpenSSL project's "OpenSSL" library, or a derivative work of it,
 *   and to copy, modify, and distribute the resulting work. This is an
 *   extension of the special permission given by Trolltech to link the
 *   Qt code with the OpenSSL library (see
 *   <http://doc.trolltech.com/4.4/gpl.html>). The OpenSSL library is
 *   licensed under a dual license: the OpenSSL License and the original
 *   SSLeay license.
 *
 * XiVO Client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XiVO Client.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef FUNCTESTS

#include <QLocalServer>
#include <QLocalSocket>

#include "remotecontrol.h"

RemoteControl::RemoteControl(ExecObjects exec_obj)
    : m_no_error(true)
{
    m_exec_obj = exec_obj;
    m_server = new QLocalServer;
    connect(m_server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    m_socket_name = "xivoclient";
    m_server->listen(m_socket_name);

    if (! m_server->isListening()) {
        qDebug() << "No more sockets available for remote control";
    }

    connect(m_exec_obj.baseengine, SIGNAL(emitMessageBox(const QString &)),
            this, SLOT(on_error(const QString &)));
    disconnect(m_exec_obj.baseengine, SIGNAL(emitMessageBox(const QString &)),
               m_exec_obj.win, SLOT(showMessageBox(const QString &)));
}

RemoteControl::~RemoteControl()
{
    m_server->close();
}

void RemoteControl::newConnection()
{
    m_client_cnx = m_server->nextPendingConnection();
    connect(m_client_cnx, SIGNAL(readyRead()),
            this, SLOT(processCommands()));
}

#define RC_EXECUTE(fct_name) { \
    if (this->commandMatches(command, #fct_name)) \
        fct_name(); \
    }
#define RC_EXECUTE_ARG(fct_name) { \
    if (this->commandMatches(command, #fct_name)) \
        fct_name(command.arguments); \
    }

bool RemoteControl::commandMatches(RemoteControlCommand command, std::string function_name)
{
    if (command.action == function_name.c_str()) {
        this->m_command_found = true;
        return true;
    }
    return false;
}

void RemoteControl::processCommands()
{
    while (m_client_cnx->canReadLine()) {
        QByteArray raw_command = m_client_cnx->readLine();
        RemoteControlCommand command = this->parseCommand(raw_command);

        m_no_error = true;
        m_command_found = false;

        try {
            RC_EXECUTE(i_stop_the_xivo_client);
            RC_EXECUTE(i_go_to_the_xivo_client_configuration);
            RC_EXECUTE(i_close_the_xivo_client_configuration);
            RC_EXECUTE_ARG(i_log_in_the_xivo_client_to_host_1_as_2_pass_3);
            RC_EXECUTE_ARG(i_log_in_the_xivo_client_to_host_1_as_2_pass_3_unlogged_agent);
            RC_EXECUTE(i_log_out_of_the_xivo_client);
            RC_EXECUTE_ARG(then_the_xlet_identity_shows_name_as_1_2);
            RC_EXECUTE_ARG(then_the_xlet_identity_shows_server_name_as_field_1_modified);
            RC_EXECUTE_ARG(then_the_xlet_identity_shows_phone_number_as_1);
            RC_EXECUTE_ARG(then_the_xlet_identity_shows_a_voicemail_1);
            RC_EXECUTE_ARG(then_the_xlet_identity_shows_an_agent_1);
            RC_EXECUTE(then_the_xlet_identity_does_not_show_any_agent);

            if (this->m_no_error == false) {
                this->sendResponse(TEST_FAILED);
            } else if (this->m_command_found) {
                this->sendResponse(TEST_PASSED);
            } else {
                this->sendResponse(TEST_UNKNOWN);
            }
        } catch (TestFailedException) {
            this->sendResponse(TEST_FAILED);
        }
    }
}

RemoteControlCommand RemoteControl::parseCommand(const QByteArray & raw_command)
{
    QString command_string = QString::fromUtf8(raw_command);
    command_string.chop(1);
    QStringList command_list = command_string.split(",");

    RemoteControlCommand return_command;
    return_command.action = command_list.takeFirst();
    return_command.arguments = command_list;
    return return_command;
}

void RemoteControl::sendResponse(RemoteControlResponse response)
{
    QString response_string;
    switch (response) {
    case TEST_FAILED:
        response_string = "KO";
        break;
    case TEST_UNKNOWN:
        response_string = "test unknown";
        break;
    case TEST_PASSED:
        response_string = "OK";
        break;
    }

    m_client_cnx->write(response_string.toUtf8().data());
    m_client_cnx->flush();
}

void RemoteControl::on_error(const QString &error_string)
{
    qDebug() << Q_FUNC_INFO << error_string;
    m_no_error = false ;
}

void RemoteControl::pause(unsigned millisec)
{
    QEventLoop q;
    QTimer tT;

    tT.setSingleShot(true);
    connect(&tT, SIGNAL(timeout()), &q, SLOT(quit()));

    tT.start(millisec);
    q.exec();
}

void RemoteControl::assert(bool condition)
{
    if (!condition) {
        throw TestFailedException();
    }
}

#endif
