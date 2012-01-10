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
{
    m_exec_obj = exec_obj;
    m_server = new QLocalServer;
    connect(m_server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    m_socket_name = "xivoclient";
    m_server->listen(m_socket_name);

    if (! m_server->isListening()) {
        qDebug() << "No more sockets available for remote control";
        m_no_error = false;
    }

    connect(m_exec_obj.baseengine, SIGNAL(emitMessageBox(const QString &)),
            this, SLOT(error(const QString &)));
    disconnect(m_exec_obj.baseengine, SIGNAL(emitMessageBox(const QString &)),
               m_exec_obj.win, SLOT(showMessageBox(const QString &)));
}

RemoteControl::~RemoteControl()
{
    m_client_cnx->flush();
    m_server->close();
}

void RemoteControl::newConnection()
{
    m_client_cnx = m_server->nextPendingConnection();
    connect(m_client_cnx, SIGNAL(readyRead()),
            this, SLOT(processCommands()));
}

#define RC_COMMAND(fct_name)     {if (command == #fct_name) m_test_ok = m_test_ok && fct_name();}
#define RC_COMMAND_ARG(fct_name) {if (command == #fct_name) m_test_ok = m_test_ok && fct_name(command_words);}

void RemoteControl::processCommands()
{
    while (m_client_cnx->canReadLine()) {
        QByteArray data  = m_client_cnx->readLine();
        QString command = QString::fromUtf8(data);
        command.chop(1);
        QStringList command_words = command.split(",");
        command = command_words.takeFirst();

        m_test_ok = true;
        RC_COMMAND(i_stop_the_xivo_client);
        RC_COMMAND(i_go_to_the_xivo_client_configuration);
        RC_COMMAND(i_close_the_xivo_client_configuration);
        RC_COMMAND_ARG(i_log_in_the_xivo_client_to_host_1_as_2_pass_3);
        ackCommand();
        m_no_error = true;
    }
}

void RemoteControl::ackCommand()
{
    QString ack = QString(m_test_ok && m_no_error ? "OK" : "KO");
    m_client_cnx->write(ack.toUtf8().data());
}

void RemoteControl::error(const QString &error_string)
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

#endif
