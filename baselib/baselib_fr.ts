<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="fr">
<context>
    <name>BaseEngine</name>
    <message>
        <location filename="src/baseengine.cpp" line="517"/>
        <source>Connection lost with XiVO CTI server</source>
        <translation>Connexion au server CTI interrompue</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="755"/>
        <source>Could not modify the Services data.</source>
        <translation>Impossible de modifier les données pour les Services.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="755"/>
        <source>Maybe Asterisk is down.</source>
        <translation>Asterisk est peut-être arrêté.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1090"/>
        <source>Failed to start a secure connection.</source>
        <translation>Impossible d&apos;établir une connexion sécurisée</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1091"/>
        <source>Do you want to disable secure connections?</source>
        <translation>Voulez-vous désactiver les connexions sécurisées?</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1115"/>
        <source>Server has sent an Error.</source>
        <translation>Le serveur a renvoyé une Erreur.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1121"/>
        <source>Your registration name &lt;%1@%2&gt; is not known by the XiVO CTI server on %3:%4.</source>
        <translation>Votre nom &lt;%1@%2&gt; est inconnu par le serveur CTI XiVO sur %3:%4.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1126"/>
        <source>You entered a wrong login / password.</source>
        <translation>Vous avez fourni un mauvais login / password.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1129"/>
        <source>You have no profile defined.</source>
        <translation>Votre profil n&apos;est pas défini.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1133"/>
        <source>The server %1:%2 did not reply to the last keepalive packet.</source>
        <oldsource>The XiVO CTI server on %1:%2 did not reply to the last keepalive.</oldsource>
        <translation>Le serveur %1:%2 n&apos;a pas répondu au paquet keepalive.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1139"/>
        <source>You defined an IP address %1 that is probably an unresolved host name.</source>
        <translation>Vous avez défini une adresse IP %1 qui est probablement un nom d&apos;hôte non résolu.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1143"/>
        <source>Socket timeout (~ 60 s) : you probably attempted to reach, via a gateway, an IP address %1 that does not exist.</source>
        <translation>Timeout de socket (~ 60 s) : vous avez probablement essayé de joindre, via une passerelle, une adresse IP %1 qui n&apos;existe pas.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1148"/>
        <source>There seems to be a machine running on this IP address %1, and either no CTI server is running, or your port %2 is wrong.</source>
        <translation>Il semble qu&apos;une machine soit présente à cette adresse IP %1, mais il n&apos;y a pas de serveur CTI, ou votre port %2 est faux.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1153"/>
        <source>An error occurred on the network while attempting to join the IP address %1 :
- no external route defined to access this IP address (~ no timeout)
- this IP address is routed but there is no machine (~ 5 s timeout)
- a cable has been unplugged on your LAN on the way to this IP address (~ 30 s timeout).</source>
        <translation>Une erreur s&apos;est produite sur le réseau en essayant de joindre l&apos;adresse IP %1 :
- aucune route externe n&apos;est définie pour accéder à cette adresse IP (~ pas de timeout)
- cette adresse IP est routée mais il n&apos;y a pas de machine (~ 5 s de timeout)
- un câble a été débranché sur votre réseau local, sur le chemin vers cette adresse IP (~ 30 s de timeout).</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1160"/>
        <source>It seems that the server with IP address %1 does not accept encryption on its port %2. Please change either your port or your encryption setting.</source>
        <translation>Il semble que le serveur à l&apos;adresse IP %1 n&apos;accepte pas le chiffrage sur son port %2. Changez soit le port soit la configuration de chiffrage.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1165"/>
        <source>An unknown socket error has occured while attempting to join the IP address:port %1:%2.</source>
        <translation>Une erreur de socket inconnue s&apos;est produite en essayant de joindre l&apos;IP %1:%2 (adresse:port).</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1170"/>
        <source>An unmanaged (number %1) socket error has occured while attempting to join the IP address:port %1:%2.</source>
        <translation>Une erreur de socket non gérée (numéro %1) s&apos;est produite en essayant de joindre l&apos;IP %1:%2 (adresse:port).</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1175"/>
        <source>The XiVO CTI server on %1:%2 has just closed the connection.</source>
        <translation>Le serveur CTI XiVO sur %1:%2 vient de fermer la connexion.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1179"/>
        <source>The XiVO CTI server on %1:%2 has just been stopped.</source>
        <translation>Le serveur CTI XiVO sur %1:%2 vient d&apos;être arrêté.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1182"/>
        <source>The XiVO CTI server on %1:%2 has just been reloaded.</source>
        <translation>Le serveur CTI XiVO sur %1:%2 vient d&apos;être rechargé.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1186"/>
        <source>You are already connected to %1:%2.</source>
        <oldsource>You are already connected from %1:%2.</oldsource>
        <translation>Vous êtes déjà connecté à %1:%2.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1188"/>
        <source>No capability allowed.</source>
        <translation>Aucune capacité autorisée.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1191"/>
        <source>Max number (%1) of XiVO Clients already reached.</source>
        <translation>Le nombre maximal (%1) de XiVO Clients est déjà connecté.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1193"/>
        <source>Missing Argument(s)</source>
        <translation>Argument(s) manquant(s)</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1198"/>
        <source>Your client&apos;s protocol version (%1)
is not the same as the server&apos;s (%2).</source>
        <translation>La version du protocole de votre client (%1)
est différente de celle du serveur (%2).</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1206"/>
        <source>Your server version (%1) is too old for this client.
Please upgrade it to %2 at least.</source>
        <translation>La version du serveur (%1) ne correspond pas avec celle du client. Merci de mettre à jour votre client à la version (%2) ou supérieur.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1211"/>
        <source>Your server version (%1) is too old for this client.
Please upgrade it.</source>
        <translation>La version du serveur (%1) ne correspond pas avec celle du client. Merci de mettre à jour votre client.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1215"/>
        <source>You were disconnected by the server.</source>
        <translation>Vous avez été déconnecté par le serveur.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1217"/>
        <source>You were forced to disconnect by the server.</source>
        <translation>Vous avez été déconnecté de force par le serveur.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1219"/>
        <source>Could not log agent: invalid extension.</source>
        <oldsource>Invalid extension number</oldsource>
        <translation>Impossible de loguer l&apos;agent: extension invalide.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1221"/>
        <source>Could not log agent: extension already in use.</source>
        <translation>Impossible de loguer l&apos;agent: extension déjà utilisée.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1224"/>
        <source>Unreachable number: %1</source>
        <translation>Numéro %1 injoignable</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1226"/>
        <source>The authentication server could not fulfill your request.</source>
        <translation>Le serveur d&apos;authentification a rencontré une erreur.</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1228"/>
        <source>You are not authorized to make calls</source>
        <translation>Vous n&apos;avez pas les droits requis pour faire des appels</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1230"/>
        <source>You are not authorized to hangup calls</source>
        <translation>Vous n&apos;avez pas les droits requis pour raccrocher un appel</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1232"/>
        <source>You are not authorized to transfer calls</source>
        <translation>Vous n&apos;avez pas les droits requis pour transférer un appel</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1234"/>
        <source>Service unavailable</source>
        <translation>Service non disponible</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1243"/>
        <source>ERROR</source>
        <translation>ERREUR</translation>
    </message>
    <message>
        <location filename="src/baseengine.cpp" line="1399"/>
        <source>Attempting to reconnect to server</source>
        <translation>Tentative de reconnexion au serveur</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="src/storage/queuememberinfo.cpp" line="86"/>
        <source>Agent</source>
        <translation>Agent</translation>
    </message>
    <message>
        <location filename="src/storage/queuememberinfo.cpp" line="86"/>
        <source>Phone</source>
        <translation>Téléphone</translation>
    </message>
</context>
<context>
    <name>QueueAgentStatus</name>
    <message>
        <location filename="src/storage/queue_agent_status.cpp" line="51"/>
        <source>Dynamic membership</source>
        <translation>Adhésion dynamique</translation>
    </message>
    <message>
        <location filename="src/storage/queue_agent_status.cpp" line="55"/>
        <source>Static/RT membership</source>
        <translation>Adhésion statique/RT</translation>
    </message>
    <message>
        <location filename="src/storage/queue_agent_status.cpp" line="67"/>
        <source>Agent not in Queue</source>
        <translation>Agent pas dans la File</translation>
    </message>
    <message>
        <location filename="src/storage/queue_agent_status.cpp" line="71"/>
        <location filename="src/storage/queue_agent_status.cpp" line="83"/>
        <source>Agent in Queue</source>
        <translation>Agent dans la File</translation>
    </message>
    <message>
        <location filename="src/storage/queue_agent_status.cpp" line="72"/>
        <location filename="src/storage/queue_agent_status.cpp" line="76"/>
        <source>Logged</source>
        <oldsource>Logged in</oldsource>
        <translation>Logué</translation>
    </message>
    <message>
        <location filename="src/storage/queue_agent_status.cpp" line="75"/>
        <source>Agent Called or Busy</source>
        <translation>Agent Appelé ou Occupé</translation>
    </message>
    <message>
        <location filename="src/storage/queue_agent_status.cpp" line="79"/>
        <source>Agent in Queue but Invalid</source>
        <translation>Agent dans la File mais Invalide</translation>
    </message>
    <message>
        <location filename="src/storage/queue_agent_status.cpp" line="84"/>
        <source>Unlogged</source>
        <oldsource>Logged out</oldsource>
        <translation>Délogué</translation>
    </message>
    <message>
        <location filename="src/storage/queue_agent_status.cpp" line="92"/>
        <source>Unpaused</source>
        <oldsource>Not paused</oldsource>
        <translation>Prêt</translation>
    </message>
    <message>
        <location filename="src/storage/queue_agent_status.cpp" line="96"/>
        <source>Paused</source>
        <translation>En retrait</translation>
    </message>
    <message>
        <location filename="src/storage/queue_agent_status.cpp" line="100"/>
        <source>Not relevant</source>
        <translation>Non pertinent</translation>
    </message>
</context>
</TS>
