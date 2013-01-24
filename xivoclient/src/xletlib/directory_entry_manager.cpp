/* XiVO Client
 * Copyright (C) 2007-2013, Avencall
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

#include <QDebug>

#include <baseengine.h>
#include <dao/phonedao.h>
#include <dao/userdao.h>
#include <storage/phoneinfo.h>
#include <xletlib/line_directory_entry.h>

#include "directory_entry_manager.h"

DirectoryEntryManager::DirectoryEntryManager(const PhoneDAO &phone_dao,
                                             const UserDAO &user_dao,
                                             QObject *parent)
    : QObject(parent), m_phone_dao(phone_dao), m_user_dao(user_dao)
{
    connect(b_engine, SIGNAL(updatePhoneConfig(const QString &)),
            this, SLOT(updatePhone(const QString &)));
    connect(b_engine, SIGNAL(updatePhoneStatus(const QString &)),
            this, SLOT(updatePhone(const QString &)));
    connect(b_engine, SIGNAL(removePhoneConfig(const QString &)),
            this, SLOT(removePhone(const QString &)));
}

const LineDirectoryEntry & DirectoryEntryManager::getEntry(int entry_index) const
{
    return m_directory_entries.at(entry_index);
}

int DirectoryEntryManager::entryCount() const
{
    return m_directory_entries.size();
}

void DirectoryEntryManager::updatePhone(const QString &phone_xid)
{
    const PhoneInfo *phone = this->m_phone_dao.findByXId(phone_xid);
    if (phone == NULL) {
        qDebug() << Q_FUNC_INFO << "phone" << phone_xid << "is null";
        return;
    }
    LineDirectoryEntry updated_entry(*phone, m_user_dao, m_phone_dao);
    int matching_entry_index = m_directory_entries.indexOf(updated_entry);
    if (matching_entry_index == -1) {
        m_directory_entries.append(updated_entry);
        emit directoryEntryAdded(m_directory_entries.size() - 1);
    } else {
        emit directoryEntryUpdated(matching_entry_index);
    }
}

void DirectoryEntryManager::removePhone(const QString &phone_xid)
{
    const PhoneInfo *phone = this->m_phone_dao.findByXId(phone_xid);
    if (phone == NULL) {
        qDebug() << Q_FUNC_INFO << "phone" << phone_xid << "is null";
        return;
    }
    LineDirectoryEntry removed_entry(*phone, m_user_dao, m_phone_dao);
    int matching_entry_index = m_directory_entries.indexOf(removed_entry);
    if (matching_entry_index == -1) {
        qDebug() << Q_FUNC_INFO << "removed phone" << phone_xid << "not in cache";
    } else {
        m_directory_entries.removeAt(matching_entry_index);
        emit directoryEntryDeleted(matching_entry_index);
    }
}
