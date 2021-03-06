/* XiVO Client
 * Copyright (C) 2007-2015 Avencall
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

#ifndef __CONFERENCE_H__
#define __CONFERENCE_H__

#include <QObject>
#include <QString>
#include <QVariantMap>

#include <baseengine.h>
#include <ipbxlistener.h>
#include <xletlib/functests.h>
#include <xletlib/xlet.h>
#include <xletlib/xletinterface.h>

#include <ui_conference_widget.h>

class ConferenceListModel;
class ConferenceListSortFilterProxyModel;
class ConferenceRoomModel;
class ConferenceRoomSortFilterProxyModel;

class Conference : public XLet, IPBXListener
{
    Q_OBJECT
    FUNCTESTED

    public:
        Conference(QWidget *parent=0);

    public slots:
        void parseCommand(const QVariantMap &command);

    private slots:
        void showConfList();
        void showConfRoom(QString &room_number, QString &room_name);
        void muteToggled(const QString &extension);

    private:
        //The order of this enum is determined by the order of the menu creation
        enum MenuIndex {
            ROOM_LIST_PANE,
            ROOM_NUMBER_PANE
        };

        int extractJoinOrder(const QString room_number);

        Ui::ConferenceWidget ui;
        ConferenceListModel *m_list_model;
        ConferenceListSortFilterProxyModel *m_list_proxy_model;
        ConferenceRoomModel *m_room_model;
        ConferenceRoomSortFilterProxyModel *m_room_proxy_model;
        QString m_confroom_number;
        QVariantList m_my_confroom_joined;
        QVariantMap m_confroom_configs;
};

class XLetConferencePlugin : public QObject, XLetInterface
{
    Q_OBJECT
    Q_INTERFACES(XLetInterface)
    Q_PLUGIN_METADATA(IID "com.avencall.Plugin.XLetInterface/1.2" FILE "xletconference.json")

    public:
        XLet *newXLetInstance(QWidget *parent=0);
};

#endif
