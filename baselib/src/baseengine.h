/* XiVO Client
 * Copyright (C) 2007-2016 Avencall
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

#ifndef __BASEENGINE_H__
#define __BASEENGINE_H__

#include "baselib_export.h"

#include <QHash>
#include <QMultiHash>
#include <QObject>
#include <QTime>
#include <QVector>

#include <storage/init_watcher.h>
#include <storage/xinfo.h>

#include "baseconfig.h"

class QApplication;
class QDateTime;
class QFile;
class QSettings;
class QSocketNotifier;
class QSslError;
class QSslSocket;
class QTcpSocket;
class QTimerEvent;
class QTranslator;
class QUdpSocket;
class QVariant;

class IPBXListener;
class XletDebug;

class AgentInfo;
class PhoneInfo;
class QueueInfo;
class QueueMemberInfo;
class UserInfo;
class VoiceMailInfo;

class BASELIB_EXPORT BaseEngine: public QObject
{
    Q_OBJECT

    public:
        //! Enum for BaseEngine state logged/not logged
        typedef enum {ENotLogged, ELogged} EngineState;

        BaseEngine(QSettings *, const QString &);  //! Constructor
        ~BaseEngine();  //! Destructor


        // public config and settings
        QSettings* getSettings();

        QVariantMap getConfig() const;              //!< all BaseEngine settings.
        QVariant getConfig(const QString &) const;  //!< one BaseEngine setting. Use to read a setting.
        void setConfig(const QVariantMap &);        //!< set as many settings as you want
        void setConfig(const QString &, QVariant);    //!< set one setting

        // public setters/getters for properties
        EngineState state();               //!< Engine state (Logged/Not Logged)

        bool checkedFunction(const QString &);             //!< get m_checked_function

        const QVariantList & getCapaXlets() const;

        const QVariantMap & getOptionsUserStatus() const;
        const QVariantMap & getOptionsPhoneStatus() const;

        const QString & getCapaApplication() const;
        const QString osname() const { return m_osname; };
        const QString ipbxid() const { return m_ipbxid; };

        const QString & getFullId() const { return m_xuserid; };
        UserInfo * getXivoClientUser();       //!< Return the user of the XiVO CTI Client

        double timeDeltaServerClient() const;
        QString timeElapsed(double) const;

        bool hasAgent(const QString & xid) { return m_anylist.value("agents").contains(xid); };

        QHash<QString, XInfo *> iterover(const QString & listname) { return m_anylist.value(listname); };

        const UserInfo * user(const QString & id) const;
        const PhoneInfo * phone(const QString & id) const;
        const AgentInfo * agent(const QString & id) const;
        const QueueInfo * queue(const QString & id) const;
        const VoiceMailInfo * voicemail(const QString & id) const;
        const QueueMemberInfo * queuemember(const QString & id) const;

        // public operations

        void registerMeetmeUpdate();

        void registerListener(const QString &, IPBXListener *); //!< Register an XLet wanting to listen IPBX messages

        QString sendJsonCommand(const QVariantMap &);

        QStringList phonenumbers(const UserInfo *);

        void registerTranslation(const QString &);
        void setupTranslation();
        QTranslator *createTranslator(const QString &translation_file);

        void urlAuto(const QString &);

        void changeWatchedAgent(const QString &, bool);
        void changeWatchedQueue(const QString &);

        QVariant parseJson(const QByteArray &) const;
        QByteArray toJson(const QVariantMap &map) const;

        bool isConnectionEncrypted() const;

        void setPresence(const QString &new_presence);

    private:

        // private getters/setters

        void setUserLogin(const QString &);                   //!< see userid()
        void setUserLogin(const QString &, const QString &);  //!< set userid and userid option

        void setOSInfos(const QString &);

        // private operations

        void loadSettings();  //!< load server settings from QSettings (conf file)
        void saveSettings();  //!< save server settings into QSettings (conf file)

        int forwardToListeners(QString className, const QVariantMap &map); //!< forward IPBX message to XLets listening

        void stopConnection();
        void sendLogout(const QString & stopper);
        void saveLogoutData(const QString & stopper);
        void clearInternalData();  //!< clear the engine internal data

        void openLogFile();

    public slots:

        void connected();

        // public getters/setters slots

        void restoreAvailState();

        // public operations slots

        void start(); //!< start the connection process.
        void stop();  //!< stop the engine

        void actionDial(const QString &);

        void fetchIPBXList();
        void fetchLists();

        void meetmeAction(const QString &, const QString &);

        void pasteToDial(const QString &);

        void saveToFile(const QString &);

        void logAction(const QString &);  //!< client side logging

        void ipbxCommand(const QVariantMap &);

        void emitMessage(const QString &);
        void onDisconnectedBeforeStartTls();

        // void sslSocketReadyRead();
        void sslErrors(const QList<QSslError> &);

    private slots:
        void keepLoginAlive();  //!< Keep session alive

        void authenticate();
        void authenticated();
        void ctiSocketReadyRead();
        void onCTIServerDisconnected();

        void sheetSocketConnected();

        void popupError(const QString & message,
                        const QString & server_address = "",
                        const QString & server_port = "");

        void updatePresence(const QString & user_xid);

    signals:
        void connectionFailed();
        void settingsChanged();  //!< signal emitted when the setting are changed

        void logged();    //!< signal emitted when the state becomes ELogged
        void delogged();  //!< signal emitted when the state becomes ENotLogged
        void aboutToBeDelogged();
        void doneConnecting();

        void initialized();
        void initializing();

        void emitTextMessage(const QString &);  //!< message to be displayed to the user.

        void pasteToXlets(const QString &);  //!< Xlets intercept this signal from paste to dial

        void fileReceived();                       //!< needed by agentdetails

        void statusListen(const QString &, const QString &, const QString &);

        void emitMessageBox(const QString &);

        void peersReceived();  //!< list of peer was received

        void updatePhoneConfig(const QString &);
        void updatePhoneStatus(const QString &);
        void updateUserConfig(const QString &);
        void updateUserConfig(const QString &, const QVariantMap &);
        void updateUserStatus(const QString &);
        void updateAgentConfig(const QString &);
        void updateAgentStatus(const QString &);
        void updateQueueConfig(const QString &);
        void updateQueueStatus(const QString &);
        void updateVoiceMailConfig(const QString &);
        void updateVoiceMailStatus(const QString &);
        void updateQueueMemberConfig(const QString &);
        void removePhoneConfig(const QString &);
        void removeUserConfig(const QString &);
        void removeAgentConfig(const QString &);
        void removeQueueConfig(const QString &);
        void removeQueueMemberConfig(const QString &);
        void postRemoveQueueMemberConfig(const QString &);
        void postRemoveQueueConfig(const QString &);

        void newQueueList(const QStringList &);
        void removeQueues(const QString &, const QStringList &);

        void directoryResponse(const QStringList &, const QStringList &);  //! the directory search response has been received.

        void localUserInfoDefined();

        void changeWatchedAgentSignal(const QString &);
        void changeWatchedQueueSignal(const QString &);

        void displayFiche(const QString &, bool, const QString &);

        void queueEntryUpdate(const QString &, const QVariantList &);
        void clearingCache();

    protected:
        void timerEvent(QTimerEvent *);  //!< receive timer events

    private:
        void stopKeepAliveTimer();  //!< Stop the keep alive timer if running
        void startTryAgainTimer();  //!< Start the "try to reconnect" timer
        void stopTryAgainTimer();   //!< Stop the "try to reconnect" timer
        void sendKeepAliveMsg();
        void disconnectNoKeepAlive();

        void emitLogged();
        void emitDelogged();

        void startConnection();
        void sendCommand(const QByteArray &);
        void parseCommand(const QByteArray &);
        void configsLists(const QString &function, const QVariantMap &datamap);
        void handleGetlistListId(const QString &listname, const QString &ipbxid, const QStringList &ids);
        void handleGetlistDelConfig(const QString &listname, const QString &ipbxid, const QStringList &ids);
        void handleGetlistUpdateConfig(const QString &listname, const QString &ipbxid, const QString &id, const QVariantMap &data);
        void handleGetlistUpdateStatus(const QString &listname, const QString &ipbxid, const QString &id, const QVariantMap &status);
        void requestListConfig(const QString &listname, const QString &ipbxid, const QStringList &listid);
        void requestStatus(const QString &listname, const QString &ipbxid, const QString &id);
        void addConfigs(const QString &listname, const QString &ipbxid, const QStringList &listid);

        void clearLists();
        void clearChannelList();
        void deleteTranslators();

        QString getInitialPresence() const;

        QByteArray encodePassword(const QString &password);
        QString decodePassword(const QByteArray &password);

        // Class Members
        // Parameters given by the User at Login time

        BaseConfig m_config;            //!< Stores the configuration values.

        QString m_xuserid;              //!< Full Id (userid)
        QString m_ipbxid;               //!< IPBX id of the current user
        QString m_userid;               //!< xivo user id of the current user
        QString m_profilename_read;     //!< CTI profile name of the current user
        QString m_profilename_write;    //!< CTI profile name of the current user
        QStringList m_ipbxlist;

        QDateTime m_timeclt;
        double m_timesrv;

        QString m_locale;
        QList<QTranslator *> m_translators;   //!< Vector of translators

        // Replies given by the server
        QVariantList m_capaxlets;        //!< List of xlet capabilities issued by the server after a successful login
        QVariantMap m_options_userstatus;    //!< Display Options for User statuses (presence)
        QVariantMap m_options_phonestatus;   //!< Display Options for Phone statuses

        QString m_appliname;            //!< Application name to be displayed
        QString m_sessionid;            //!< Session id obtained after a successful login

        // Status variables
        EngineState m_state;            //!< State of the engine (Logged/Not Logged)
        QString m_availstate;           //!< Availability state to send to the server

        // QSslSocket * m_sslsocket;

        // Internal management
        QSslSocket * m_ctiserversocket;     //!< Connection to the CTI server
        QTcpSocket * m_tcpsheetsocket;  //!< TCP connection for Sheet sockets
        QUdpSocket * m_udpsheetsocket;  //!< UDP connection for Sheet sockets
        int m_timerid_keepalive;        //!< timer id for keep alive
        int m_timerid_tryreconnect;     //!< timer id for try to reconnect
        int m_pendingkeepalivemsg;      //!< number of keepalivemsg sent without response
        QString m_osname;               //!< OS informations

        QSettings * m_settings;  //!< Settings (stored in .ini file)
        QFile * m_eventdevice;
        QByteArray m_downloaded;    //!< downloaded data
        QFile * m_logfile;

        bool m_attempt_loggedin;
        bool m_forced_to_disconnect;    //!< set to true when disconnected by server

        QMultiHash<QString, IPBXListener*> m_listeners;

        // miscellaneous statuses to share between xlets
        QHash<QString, newXInfoProto> m_xinfoList;  //!< XInfo constructors
        QHash<QString, QHash<QString, XInfo *> > m_anylist;
        QHash<QString, QueueMemberInfo *> m_queuemembers;

        InitWatcher m_init_watcher;

    friend class CTIServer;
    friend class XletDebug;
};

extern BASELIB_EXPORT BaseEngine *b_engine;
#define nelem(x)    static_cast<int>(sizeof(x)/sizeof(x)[0])

#endif /* __BASEENGINE_H__ */
