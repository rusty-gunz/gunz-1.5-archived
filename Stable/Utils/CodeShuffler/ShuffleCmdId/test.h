#ifndef MSHAREDCOMMANDTABLE_H
#define MSHAREDCOMMANDTABLE_H

class MCommandManager;


#define MCOMMAND_VERSION	58



#define MSCT_MASTER			1
#define MSCT_CLIENT			2
#define MSCT_MATCHSERVER	4
#define MSCT_AGENT			8
#define MSCT_ALL			(MSCT_MASTER+MSCT_CLIENT+MSCT_AGENT)




/// ��� Ŀ�´������Ͱ� �����ϴ� Ŀ�ǵ�
void MAddSharedCommandTable(MCommandManager* pCommandManager, int nSharedType);


/// ���� Ŭ���̾�Ʈ ���� ���
#define MATCH_CYCLE_CHECK_SPEEDHACK	20000


// �⺻ Ŀ�ǵ� ����Ʈ
#define MC_HELP						0
#define MC_VERSION					1

#define MC_DEBUG_TEST				100

#define MC_LOCAL_INFO				201		///< Local ������ ��´�.
#define MC_LOCAL_ECHO				202		///< Local Echo �׽�Ʈ
#define MC_LOCAL_LOGIN				203		///< Login ó�� Local Command



#define MC_NET_ENUM					301		///< ������ �� �ִ� Ŀ�´������� Enum
#define MC_NET_CONNECT				302		///< Ŀ�´������Ϳ� ����
#define MC_NET_DISCONNECT			303		///< Ŀ�´������Ϳ� ���� ����
#define MC_NET_CLEAR				304		///< Ŀ�´������Ϳ� ���� ���� �� �����ڿ� ó��
#define MC_NET_ONCONNECT			311		///< Ŀ�´������Ϳ� ����Ǿ��� ��
#define MC_NET_ONDISCONNECT			312		///< Ŀ�´������Ϳ� ������ ������ ��
#define MC_NET_ONERROR				313		///< Ŀ�´������Ϳ� ���� ����
#define MC_NET_CHECKPING			321		///< Ŀ�´������� �����ӵ��˻�
#define MC_NET_PING					322		///< Ŀ�´������� �����ӵ��˻� ��û
#define MC_NET_PONG					323		///< Ŀ�´������� �����ӵ��˻� ����

#define MC_HSHIELD_PING				324		///< �ٽǵ� �޼��� ��û(��ġ���� -> Ŭ���̾�Ʈ)
#define MC_HSHIELD_PONG				325		///< �ٽǵ� �޼��� ����(Ŭ���̾�Ʈ -> ��ġ����)

#define MC_NET_BANPLAYER_FLOODING	326		///< CommandBuilder���� Flooding ����� ����� Command

#define MC_NET_CONNECTTOZONESERVER	331		///< 127.0.0.1:6000 ����

#define MC_NET_REQUEST_INFO			341		///< Net ������ ��û�Ѵ�.
#define MC_NET_RESPONSE_INFO		342		///< Net ������ ��´�.
#define MC_NET_REQUEST_UID			343		///< MUID�� ��û
#define MC_NET_RESPONSE_UID			344		///< MUID�� Ȯ���ؼ� �����ش�.
#define MC_NET_ECHO					351		///< Net Echo �׽�Ʈ

#define MC_CLOCK_SYNCHRONIZE		361		///< Ŭ�� ��ũ




// �̱� �� ������ �����ϱ� ���� �Ʒ� SHUFFLE BEGIN ~ END ������ ���� Ŀ�ǵ�ID�� ������ ���α׷����� ���´�
//[[SHUFFLE_BEGIN]] 				<< �� �ּ����� ID �����ִ� ���α׷����� �ν��ϴ� ��ũ�̴�
//[[SHUFFLE_RANGE]](70000,79999)

// ��ġ���� ���� ��ɾ�
#define MC_MATCH_NOTIFY						70231		///< �˸� �޽���
#define MC_MATCH_ANNOUNCE					70253		///< ����
#define MC_MATCH_RESPONSE_RESULT			70033		///< request�� ���� ����� �˸�(S -> C)

// ������ ���� ��ɾ�
#define MC_ADMIN_ANNOUNCE					70021		///< ��ü �����ڿ��� ���
#define MC_ADMIN_REQUEST_SERVER_INFO		70076		///< ���� ���� ��û
#define MC_ADMIN_RESPONSE_SERVER_INFO		70336		///< ���� ���� ����
#define MC_ADMIN_SERVER_HALT				70199		///< ������ ���� �Ѵ�
#define MC_ADMIN_TERMINAL					70049		///< �͹̳�
#define MC_ADMIN_REQUEST_UPDATE_ACCOUNT_UGRADE	70241	///< ���� ���� ���� ��û
#define MC_ADMIN_RESPONSE_UPDATE_ACCOUNT_UGRADE	70348	///< ���� ���� ���� ����
#define MC_ADMIN_REQUEST_BAN_PLAYER			70096		///< Ÿ�� ���� ���� ��û
#define MC_ADMIN_RESPONSE_BAN_PLAYER		70326		///< Ÿ�� ���� ���� ����
#define MC_ADMIN_PING_TO_ALL				70157		///< Garbage Connection û�� Ȯ���� ���� �������
#define MC_ADMIN_REQUEST_SWITCH_LADDER_GAME	70354		///< Ŭ���� ��û ���ɿ��� ����
#define MC_ADMIN_HIDE						70184		///< ��� �Ⱥ��̱�
#define MC_ADMIN_RELOAD_CLIENT_HASH			70171		///< reload XTrap Hashmap
#define MC_ADMIN_RESET_ALL_HACKING_BLOCK	70180		///< ��� ��ŷ ���� ����Ѵ�.
#define MC_ADMIN_RELOAD_GAMBLEITEM			70322		///< �׺� ������ ���� �ٽ� �б�.
#define MC_ADMIN_DUMP_GAMBLEITEM_LOG		70264		///< ���� �׺� ������ ������ Log���Ͽ� ����Ѵ�.
#define MC_ADMIN_ASSASIN					70053		///< GM�� Ŀ�Ǵ��� �ȴ�.

// �̺�Ʈ ������ ��ɾ�
#define MC_EVENT_CHANGE_MASTER				70052		///< ��������� ����´�
#define MC_EVENT_CHANGE_PASSWORD			70303		///< ���� ��й�ȣ�� �ٲ۴�
#define MC_EVENT_REQUEST_JJANG				70014		///< ¯��ũ �ο�
#define MC_EVENT_REMOVE_JJANG				70250		///< ¯��ũ ȸ��
#define MC_EVENT_UPDATE_JJANG				70191		///< ¯��ũ �˸�

// ��ġ����-Ŭ���̾�Ʈ
#define MC_MATCH_LOGIN							70287	///< �α���
#define MC_MATCH_RESPONSE_LOGIN					70073	///< �α��� ����
#define MC_MATCH_LOGIN_NETMARBLE				70127	///< �ݸ����� �α���
#define MC_MATCH_LOGIN_NETMARBLE_JP				70175	///< �Ϻ��ݸ����� �α���
#define MC_MATCH_LOGIN_FROM_DBAGENT				70213	///< DBAgent�κ����� �α��� ����(�Ϻ��ݸ��� ����)
#define MC_MATCH_LOGIN_FROM_DBAGENT_FAILED		70304	///< DBAgent�κ����� �α��� ����(�Ϻ��ݸ��� ����)
#define MC_MATCH_FIND_HACKING					70056	///< ��ŷ ����
#define MC_MATCH_DISCONNMSG						70100	///< Discconst�޽���.
#define MC_MATCH_LOGIN_NHNUSA					70290	///< �̱� NHN���� �α���.
#define MC_MATCH_LOGIN_GAMEON_JP				70261	///< �Ϻ� gameon���� �α���

#define MC_MATCH_BRIDGEPEER						70310	///< MatchServer�� Peer���� �˸�
#define MC_MATCH_BRIDGEPEER_ACK					70307	///< Peer���� ����Ȯ��

#define MC_MATCH_OBJECT_CACHE					70247	///< ������Ʈ ĳ��

#define MC_MATCH_REQUEST_RECOMMANDED_CHANNEL	70024	///< ���� ������ ä�ο����� ��õ�� ��û�Ѵ�.
#define MC_MATCH_RESPONSE_RECOMMANDED_CHANNEL	70329	///< ���� ������ ä�ο����� ��õ�Ѵ�.
#define MC_MATCH_CHANNEL_REQUEST_JOIN			70208	///< ä�ο� ����(C -> S)
#define MC_MATCH_CHANNEL_REQUEST_JOIN_FROM_NAME	70097	///< ä���̸����� ä�� ���� ��û
#define MC_MATCH_CHANNEL_RESPONSE_JOIN			70243	///< ä�� ���� ����(S -> C)
#define MC_MATCH_CHANNEL_LEAVE					70006	///< ä�� Ż��
#define MC_MATCH_CHANNEL_LIST_START				70128	///< ä�� ��� ���۽��� ��û
#define MC_MATCH_CHANNEL_LIST_STOP				70151	///< ä�� ��� �������� ��û
#define MC_MATCH_CHANNEL_LIST					70121	///< ä�� ���
#define MC_MATCH_CHANNEL_REQUEST_PLAYER_LIST	70300	///< �÷��̾� ����Ʈ ��û
#define MC_MATCH_CHANNEL_RESPONSE_PLAYER_LIST	70160	///< �÷��̾� ����Ʈ ����
#define MC_MATCH_CHANNEL_REQUEST_CHAT			70344	///< ä�ο� ��ȭ ��û
#define MC_MATCH_CHANNEL_CHAT					70205	///< ä�ο��� ��ȭ ����
#define MC_MATCH_CHANNEL_DUMB_CHAT				70176	///< ä�ο��� ��ȭ ����, ��� ��� - ȫ����(2009.08.05)

#define MC_MATCH_CHANNEL_REQUEST_RULE			70227	///< ä�α�Ģ ��û
#define MC_MATCH_CHANNEL_RESPONSE_RULE			70313	///< ä�α�Ģ ����
#define MC_MATCH_CHANNEL_REQUEST_ALL_PLAYER_LIST		70362	///< ä���� �κ� �ִ� ��� �÷��̾� ����Ʈ ��û
#define MC_MATCH_CHANNEL_RESPONSE_ALL_PLAYER_LIST		70150	///< ä���� �κ� �ִ� �÷��̾� ����Ʈ ��û


#define MC_MATCH_STAGE_CREATE					70083	///< �������� ����
#define MC_MATCH_RESPONSE_STAGE_CREATE			70043	///< �������� ���� ����
#define MC_MATCH_STAGE_JOIN						70339	///< �������� ����
#define MC_MATCH_REQUEST_STAGE_JOIN				70086	///< �������� ���� ��û
#define MC_MATCH_REQUEST_PRIVATE_STAGE_JOIN		70332	///< ��� �������� ���� ��û
#define MC_MATCH_RESPONSE_STAGE_JOIN			70221	///< ���������� ���ο��θ� �˸�
#define MC_MATCH_STAGE_LEAVE					70000	///< �������� Ż��
#define MC_MATCH_STAGE_REQUEST_PLAYERLIST		70011	///< ���������� ������� ��û
#define MC_MATCH_STAGE_FOLLOW					70113	///< ���� ������ ���� �������� ����
#define MC_MATCH_RESPONSE_STAGE_FOLLOW			70146	///< ���� ������ ���� �������� ���� ����
#define MC_MATCH_REQUEST_STAGE_LIST				70206	///< Ŭ���̾�Ʈ�� �������� ����Ʈ ��û
#define MC_MATCH_STAGE_LIST_START				70222	///< �������� ��� ���۽��� ��û
#define MC_MATCH_STAGE_LIST_STOP				70147	///< �������� ��� �������� ��û
#define MC_MATCH_STAGE_LIST						70103	///< �������� ���
#define MC_MATCH_STAGE_CHAT						70259	///< �������� ��ȭ
#define MC_MATCH_STAGE_REQUEST_QUICKJOIN		70345	///< ������ ��û
#define MC_MATCH_STAGE_RESPONSE_QUICKJOIN		70081	///< ������ ����
#define MC_MATCH_STAGE_GO						70260	///< �������� ��ȣ�� ����
#define MC_MATCH_STAGE_REQUIRE_PASSWORD			70325	///< ��й��̶� �н����尡 �ʿ��ϴ�.(S -> C)


#define MC_MATCH_STAGE_REQUEST_ENTERBATTLE		70163	///< �������� ���� �����Ѵٰ� ��û
#define MC_MATCH_STAGE_ENTERBATTLE				70055	///< �������� ��������
#define MC_MATCH_STAGE_LEAVEBATTLE_TO_SERVER	70108	///< �������� ����Ż��(C -> S)
#define MC_MATCH_STAGE_LEAVEBATTLE_TO_CLIENT	70072	///< �������� ����Ż��(S -> C)

#define MC_MATCH_REQUEST_STAGESETTING			70360	///< ���������� ������ ��û
#define MC_MATCH_RESPONSE_STAGESETTING			70135	///< ���������� ������ �˸�
#define MC_MATCH_STAGESETTING					70274	///< �������� ����
#define MC_MATCH_STAGE_MAP						70185	///< �������� �� ����
#define MC_MATCH_STAGE_REQUEST_FORCED_ENTRY		70305	///< ������������ ���ӿ� ���� ��û
#define MC_MATCH_STAGE_RESPONSE_FORCED_ENTRY	70045	///< �������� ���� ���� ����
#define MC_MATCH_STAGE_RELAY_MAP_ELEMENT_UPDATE	70257	///< �������� �����̸� ���(Ÿ��, ȸ��) ������Ʈ
#define MC_MATCH_STAGE_RELAY_MAP_INFO_UPDATE	70079	///< �������� �����̸� ����Ʈ ������Ʈ

#define MC_MATCH_STAGE_MASTER					70039	///< �������� ���� �˸�
#define MC_MATCH_STAGE_PLAYER_STATE				70023	///< �������� ���� ���� �÷��̾� ���� ����
#define MC_MATCH_STAGE_TEAM						70050	///< �������� ��
#define MC_MATCH_STAGE_START					70068	///< �������� ����(ī��Ʈ�ٿ�)
#define MC_MATCH_STAGE_LAUNCH					70204	///< �������� ����
#define MC_MATCH_STAGE_RELAY_LAUNCH				70217	///< �����̵� �������� ����

#define MC_MATCH_LOADING_COMPLETE				70004	///< �ε��� ������
#define MC_MATCH_STAGE_FINISH_GAME				70152	///< �������� ���� ����

#define MC_MATCH_REQUEST_GAME_INFO				70018	///< ���Ӿ� ������ �޶� ��û
#define MC_MATCH_RESPONSE_GAME_INFO				70186	///< ���Ӿ� ������ �˷��ش�

#define MC_MATCH_REQUEST_PEERLIST				70101	///< �������� �������� Peer������ ��û
#define MC_MATCH_RESPONSE_PEERLIST				70131	///< �������� �������� Peer������ �˸�

#define MC_MATCH_REQUEST_PEER_RELAY				70252	///< ��ġ������ �ش�Peer�� ���� �߰��û
#define MC_MATCH_RESPONSE_PEER_RELAY			70142	///< �ش�Peer�� ���� �߰��㰡 �뺸

// ���� ����
#define MC_MATCH_GAME_ROUNDSTATE				70158	///< ������ ���¸� ����ȭ
#define MC_MATCH_ROUND_FINISHINFO				70125	///< ���� ����� ���� ������Ʈ (C <- S)
#define MC_MATCH_GAME_KILL						70020	///< ĳ���� ��� (C -> S)
#define MC_MATCH_GAME_DEAD						70123	///< ĳ���� �׾��� (S -> C)
#define MC_MATCH_GAME_LEVEL_UP					70092	///< ������ ������
#define MC_MATCH_GAME_LEVEL_DOWN				70266	///< ������ �����ٿ�
#define MC_MATCH_GAME_REQUEST_SPAWN				70140	///< ĳ���� ��Ȱ��û (C -> S)
#define MC_MATCH_GAME_RESPONSE_SPAWN			70207	///< ĳ���� ��Ȱ��û (C -> S)
#define MC_MATCH_GAME_TEAMBONUS					70267	///< �� ���ʽ�(S -> C)

#define MC_MATCH_GAME_REQUEST_TIMESYNC			70109	///< Match������ �ð�����ȭ ��û
#define MC_MATCH_GAME_RESPONSE_TIMESYNC			70238	///< �ð�����ȭ
#define MC_MATCH_GAME_REPORT_TIMESYNC			70077	///< �ð����� �˻�

#define MC_MATCH_REQUEST_SUICIDE				70155	///< �ڻ� ��û
#define MC_MATCH_RESPONSE_SUICIDE				70027	///< �ڻ� ����
#define MC_MATCH_RESPONSE_SUICIDE_RESERVE		70088	///< �ڻ� ����.
#define MC_MATCH_REQUEST_OBTAIN_WORLDITEM		70114	///< ������ �Ե��� ��û
#define MC_MATCH_OBTAIN_WORLDITEM				70353	///< ������ ���� ��ε�ĳ��Ʈ(S -> C)
#define MC_MATCH_SPAWN_WORLDITEM				70177	///< �������� ������
#define MC_MATCH_REQUEST_SPAWN_WORLDITEM		70359	///< �������� �������� ��û(C -> S)
#define MC_MATCH_REMOVE_WORLDITEM				70104	///< ������ ������(S -> C)
#define MC_MATCH_ASSIGN_COMMANDER				70156	///< �ϻ��� �������� �Ӹ�
#define MC_MATCH_RESET_TEAM_MEMBERS				70299	///< ����� �ٽ� ����
#define MC_MATCH_SET_OBSERVER					70041	///< ������ ���������� ��ȯ


// ���ǰ���
#define MC_MATCH_REQUEST_PROPOSAL				70182	///< �ٸ� ����� ���� ��û
#define MC_MATCH_RESPONSE_PROPOSAL				70192	///< ���� ��û ����
#define MC_MATCH_ASK_AGREEMENT					70060	///< �ٸ� ������� ���� ����(S -> C)
#define MC_MATCH_REPLY_AGREEMENT				70223	///< ���� ����(C -> S)

// ���� ����
#define MC_MATCH_LADDER_REQUEST_CHALLENGE		70037	///< ���� ���� ��û(C -> S)
#define MC_MATCH_LADDER_RESPONSE_CHALLENGE		70029	///< ���� ���� ����
#define MC_MATCH_LADDER_SEARCH_RIVAL			70330	///< ���� �˻���		
#define MC_MATCH_LADDER_REQUEST_CANCEL_CHALLENGE	70129	///< ���� ���� ��ҿ�û
#define MC_MATCH_LADDER_CANCEL_CHALLENGE		70136	///< ���� ���� ���
#define MC_MATCH_LADDER_PREPARE					70196	///< ���� �����غ�
#define MC_MATCH_LADDER_LAUNCH					70272	///< ���� ��ġ (S -> C)

// �ǻ���� ����
#define MC_MATCH_USER_WHISPER					70134	///< �ӼӸ�
#define MC_MATCH_USER_WHERE						70078	///< ��ġȮ��
#define MC_MATCH_USER_OPTION					70087	///< �����ɼ�(�Ӹ��ź�,�ʴ�ź�,ģ���ź� ���)
#define MC_MATCH_CHATROOM_CREATE				70262	///< ä�÷� ����
#define MC_MATCH_CHATROOM_JOIN					70019	///< ä�÷� ����
#define MC_MATCH_CHATROOM_LEAVE					70280	///< ä�÷� Ż��
#define MC_MATCH_CHATROOM_INVITE				70251	///< ä�÷� �ʴ�
#define MC_MATCH_CHATROOM_CHAT					70013	///< ä��
#define MC_MATCH_CHATROOM_SELECT_WRITE			70242	///< ä�÷� ����

// ĳ���� ����
#define MC_MATCH_REQUEST_ACCOUNT_CHARLIST		70116	///< ������ ��ü ĳ���� ����Ʈ�� ��û
#define MC_MATCH_RESPONSE_ACCOUNT_CHARLIST		70311	///< ������ ��ü ĳ���� ����Ʈ�� ����
#define MC_MATCH_REQUEST_SELECT_CHAR			70340	///< ĳ���� ���� ��û
#define MC_MATCH_RESPONSE_SELECT_CHAR			70138	///< ĳ���� ���� ����
#define MC_MATCH_REQUEST_MYCHARINFO				70017	///< �� ĳ���� ���� ��û
#define MC_MATCH_RESPONSE_MYCHARINFO			70105	///< �� ĳ���� ���� ����
#define MC_MATCH_REQUEST_CREATE_CHAR			70296	///< �� ĳ���� ���� ��û
#define MC_MATCH_RESPONSE_CREATE_CHAR			70293	///< �� ĳ���� ���� ����
#define MC_MATCH_REQUEST_DELETE_CHAR			70308	///< �� ĳ���� ���� ��û
#define MC_MATCH_RESPONSE_DELETE_CHAR			70126	///< �� ĳ���� ���� ����
#define MC_MATCH_REQUEST_COPY_TO_TESTSERVER		70130	///< ĳ���� �׽�Ʈ������ ���� ��û - �̱���
#define MC_MATCH_RESPONSE_COPY_TO_TESTSERVER	70093	///< ĳ���� �׽�Ʈ������ ���� ���� - �̱���
#define MC_MATCH_REQUEST_CHARINFO_DETAIL		70346	///< �ٸ� �÷��̾� �������� ���� �ڼ��� �÷��̾� ���� ��û
#define MC_MATCH_RESPONSE_CHARINFO_DETAIL		70040	///< �ٸ� �÷��̾� �������� ���� �ڼ��� �÷��̾� ���� ����
#define MC_MATCH_REQUEST_ACCOUNT_CHARINFO		70095	///< ������ �� ĳ���� ���� ��û
#define MC_MATCH_RESPONSE_ACCOUNT_CHARINFO		70228	///< ������ �� ĳ���� ���� ����

// ������ ����
#define MC_MATCH_REQUEST_SIMPLE_CHARINFO		70154	///< ĳ������ ������ ���� ��û	
#define MC_MATCH_RESPONSE_SIMPLE_CHARINFO		70082	///< ĳ������ ������ ���� ����
#define MC_MATCH_REQUEST_MY_SIMPLE_CHARINFO		70166	///< �� ĳ���� XP, BP�� ���� ��û
#define MC_MATCH_RESPONSE_MY_SIMPLE_CHARINFO	70281	///< �� ĳ���� XP, BP�� ���� ����

#define MC_MATCH_REQUEST_BUY_ITEM				70232	///< ������ ���� ��û
#define MC_MATCH_RESPONSE_BUY_ITEM				70189	///< ������ ���� ����
#define MC_MATCH_REQUEST_SELL_ITEM				70118	///< ������ �Ǹ� ��û
#define MC_MATCH_RESPONSE_SELL_ITEM				70225	///< ������ �Ǹ� ����
#define MC_MATCH_REQUEST_SHOP_ITEMLIST			70315	///< ������ �Ǹ��ϴ� ������ ����Ʈ ��û
#define MC_MATCH_RESPONSE_SHOP_ITEMLIST			70337	///< ������ �Ǹ��ϴ� ������ ����Ʈ ����

#define MC_MATCH_REQUEST_CHARACTER_ITEMLIST		70164	///< �� ������ ����Ʈ �ֽÿ�
#define MC_MATCH_RESPONSE_CHARACTER_ITEMLIST	70167	///< ������ ����Ʈ ������
#define MC_MATCH_REQUEST_EQUIP_ITEM				70314	///< ������ ��� ��û
#define MC_MATCH_RESPONSE_EQUIP_ITEM			70069	///< ������ ��� ����
#define MC_MATCH_REQUEST_TAKEOFF_ITEM			70255	///< ������ ���� ��û
#define MC_MATCH_RESPONSE_TAKEOFF_ITEM			70351	///< ������ ���� ����
#define MC_RESPONSE_GAMBLEITEMLIST				70120	///< DB�� �׺� ������ ���� ����.
#define MC_MATCH_ROUTE_UPDATE_STAGE_EQUIP_LOOK	70028	///< ĳ������ Look���� ������Ʈ�Ҷ� ����Ѵ�.
#define MC_MATCH_REQUEST_CHARACTER_ITEMLIST_FORCE	70297	///< �� ������ ����Ʈ �ֽÿ� : �ߺ� ��û�� �������� �ʴ� ����(�����ؼ� ����Ұ�)

#define MC_MATCH_REQUEST_ACCOUNT_ITEMLIST		70022	///< �� â�� ������ ����Ʈ �ֽÿ�
#define MC_MATCH_RESPONSE_ACCOUNT_ITEMLIST		70239	///< â�� ������ ����Ʈ ������
#define MC_MATCH_REQUEST_BRING_ACCOUNTITEM		70327	///< â�� �������� �� ĳ���ͷ� ��������
#define MC_MATCH_RESPONSE_BRING_ACCOUNTITEM		70188	///< â�� ������ �������� ����
#define MC_MATCH_REQUEST_BRING_BACK_ACCOUNTITEM	70246	///< �� ĳ�������� â��� �ű�� ��û
#define MC_MATCH_RESPONSE_BRING_BACK_ACCOUNTITEM	70144	///< �� ĳ�������� â��� �ű�� ����
#define MC_MATCH_EXPIRED_RENT_ITEM				70112	///< �������� �Ⱓ ����Ǿ����ϴ�.(S -> C)

#define MC_MATCH_REQUEST_GAMBLE					70233	///< �̱� (C -> S)
#define MC_MATCH_RESPONSE_GAMBLE				70115	///< �̱� ��� (S -> C)

// ģ�� ����
#define MC_MATCH_FRIEND_ADD						70211	///< ģ�� �߰�
#define MC_MATCH_FRIEND_REMOVE					70363	///< ģ�� ����
#define MC_MATCH_FRIEND_LIST					70058	///< ģ�� ��� ��û
#define MC_MATCH_RESPONSE_FRIENDLIST			70226	///< ģ�� ��� ����
#define MC_MATCH_FRIEND_MSG						70107	///< ģ�� ä��


// Ŭ������
#define MC_MATCH_CLAN_REQUEST_CREATE_CLAN			70145	///< Ŭ�� ���� ��û(C -> S)
#define MC_MATCH_CLAN_RESPONSE_CREATE_CLAN			70032	///< Ŭ�� ���� ����(S -> C)
#define MC_MATCH_CLAN_ASK_SPONSOR_AGREEMENT			70236	///< �߱��ο��� Ŭ�� ���� ���� ����(S -> C)
#define MC_MATCH_CLAN_ANSWER_SPONSOR_AGREEMENT		70178	///< �߱����� ���Ǹ� ����(C -> S)
#define MC_MATCH_CLAN_REQUEST_AGREED_CREATE_CLAN	70284	///< �߱����� ������ Ŭ�� ���� ��û(C -> S)
#define MC_MATCH_CLAN_RESPONSE_AGREED_CREATE_CLAN	70057	///< �߱����� ������ Ŭ�� ���� ����(S -> C)
#define MC_MATCH_CLAN_REQUEST_CLOSE_CLAN			70289	///< �����Ͱ� Ŭ�� ��� ��û(C -> S)
#define MC_MATCH_CLAN_RESPONSE_CLOSE_CLAN			70323	///< �������� Ŭ�� ��� ����(S -> C)
#define MC_MATCH_CLAN_REQUEST_JOIN_CLAN				70153	///< ��ڰ� �������� ������ ��û(C -> S)
#define MC_MATCH_CLAN_RESPONSE_JOIN_CLAN			70265	///< ����� ������ ������ ����(S -> C)
#define MC_MATCH_CLAN_ASK_JOIN_AGREEMENT			70237	///< �����ڿ��� ���� ���� ����(S -> C)
#define MC_MATCH_CLAN_ANSWER_JOIN_AGREEMENT			70031	///< �������� ���� ���� ����(C -> S)
#define MC_MATCH_CLAN_REQUEST_AGREED_JOIN_CLAN		70203	///< �����ڰ� ������ Ŭ�� ���� ��û(C -> S)
#define MC_MATCH_CLAN_RESPONSE_AGREED_JOIN_CLAN		70071	///< �����ڰ� ������ Ŭ�� ���� ����(S -> C)
#define MC_MATCH_CLAN_REQUEST_LEAVE_CLAN			70352	///< Ŭ������ Ż�� ��û(C -> S)
#define MC_MATCH_CLAN_RESPONSE_LEAVE_CLAN			70016	///< Ŭ������ Ż���� ����(S -> C)
#define MC_MATCH_CLAN_UPDATE_CHAR_CLANINFO			70210	///< ĳ������ Ŭ�������� ������Ʈ��(S -> C)
#define MC_MATCH_CLAN_MASTER_REQUEST_CHANGE_GRADE	70256	///< ����� ���� ���� ��û(C -> S)
#define MC_MATCH_CLAN_MASTER_RESPONSE_CHANGE_GRADE	70170	///< ����� ���� ���� ����(S -> C)
#define MC_MATCH_CLAN_ADMIN_REQUEST_EXPEL_MEMBER	70324	///< ����� Ż�� ��û(C -> S)
#define MC_MATCH_CLAN_ADMIN_RESPONSE_EXPEL_MEMBER	70047	///< ����� Ż�� ����(S -> C)
#define MC_MATCH_CLAN_REQUEST_MSG					70268	///< Ŭ�� ä�� ��û(C -> S)
#define MC_MATCH_CLAN_MSG							70119	///< Ŭ�� ä��(S -> C)
#define MC_MATCH_CLAN_REQUEST_MEMBER_LIST			70122	///< Ŭ�� ��� ����Ʈ ��û(C -> S)
#define MC_MATCH_CLAN_RESPONSE_MEMBER_LIST			70283	///< Ŭ�� ��� ����Ʈ ����(S -> C)
#define MC_MATCH_CLAN_REQUEST_CLAN_INFO				70320	///< Ŭ�� ���� ��û(C -> S)
#define MC_MATCH_CLAN_RESPONSE_CLAN_INFO			70044	///< Ŭ�� ���� ����(S -> C)
#define MC_MATCH_CLAN_STANDBY_CLAN_LIST				70298	///< Ŭ���� ������� Ŭ�� ����Ʈ ����(S -> C)
#define MC_MATCH_CLAN_MEMBER_CONNECTED				70194	///< Ŭ������ ������(S -> C)
#define MC_MATCH_CLAN_REQUEST_EMBLEMURL				70312	///< Ŭ����ũ URL ��û(C -> S)
#define MC_MATCH_CLAN_RESPONSE_EMBLEMURL			70098	///< Ŭ����ũ URL ����(S -> C)
#define MC_MATCH_CLAN_LOCAL_EMBLEMREADY				70286	///< Ŭ����ũ �ٿ�ε� �Ϸ�(C -> C)
#define MC_MATCH_CLAN_ACCOUNCE_DELETE				70002	///< Ŭ�� ��� ��û ���� ���� ����.(S -> C)


// ��ǥ����
#define MC_MATCH_CALLVOTE							70317	///< ��ǥ�� �����Ѵ�. (C -> S)
#define MC_MATCH_NOTIFY_CALLVOTE					70214	///< ��ǥ������ �˸���. (S -> C)
#define MC_MATCH_NOTIFY_VOTERESULT					70279	///< ��ǥ����� �˸���. (S -> C)
#define MC_MATCH_VOTE_YES							70038	///< ��ǥ (C -> S)
#define MC_MATCH_VOTE_NO							70347	///< ��ǥ (C -> S)
#define MC_MATCH_VOTE_RESPONSE						70240	///< ��ǥ ����.(S -> C)
#define MC_MATCH_VOTE_STOP							70269	///< ��ǥ ���. (S -> C)

// ��۰���
#define MC_MATCH_BROADCAST_CLAN_RENEW_VICTORIES			70292	///< Ŭ���� ��� �������Դϴ�.(S -> C)
#define MC_MATCH_BROADCAST_CLAN_INTERRUPT_VICTORIES		70319	///< Ŭ���� ������ �����Ͽ����ϴ�.(S -> C)
#define MC_MATCH_BROADCAST_DUEL_RENEW_VICTORIES			70159	///< xx���� xxä���� xx�濡�� x�������Դϴ�.(S -> C)
#define MC_MATCH_BROADCAST_DUEL_INTERRUPT_VICTORIES		70143	///< xx���� xx���� xx������ �����߽��ϴ�. (S -> C)


// Duel Tournament ����.. Added by ȫ����
#define MC_MATCH_DUELTOURNAMENT_REQUEST_JOINGAME				70334	///< ��� ��ʸ�Ʈ�� ���� ��û(C -> S)
#define MC_MATCH_DUELTOURNAMENT_RESPONSE_JOINGAME				70220	///< ��� ��ʸ�Ʈ�� ���� ��û�� ���� ����(S -> C)
#define MC_MATCH_DUELTOURNAMENT_REQUEST_CANCELGAME				70224	///< ��� ��ʸ�Ʈ�� ���� ��û ���(C -> S)
#define MC_MATCH_DUELTOURNAMENT_CHAR_INFO						70235	///< ��� ��ʸ�Ʈ�� �ɸ��� ����(S -> C)
#define MC_MATCH_DUELTOURNAMENT_PREPARE_MATCH					70200	///< ��� ��ʸ�Ʈ ���� ��
#define MC_MATCH_DUELTOURNAMENT_LAUNCH_MATCH					70277	///< ��� ��ʸ�Ʈ ����! (S - > C)
#define MC_MATCH_DUELTOURNAMENT_CANCEL_MATCH					70046	///< ��� ��ʸ�Ʈ ���! (S - > C)
#define MC_MATCH_DUELTOURNAMENT_CHAR_INFO_PREVIOUS				70106	///< ��� ��ʸ�Ʈ ĳ���� ������ ����(S -> C)
#define MC_MATCH_DUELTOURNAMENT_NOT_SERVICE_TIME				70074	///< ���� �����ʸ�Ʈ ���� �ð��� �ƴմϴ�.(���½ð� %s%d��00�� ~ %s%d��59��) (S - > C)

#define MC_MATCH_DUELTOURNAMENT_REQUEST_SIDERANKING_INFO		70229	///< �ɸ��� ��ŷ�� ��ó ��ŷ ���� ��û(C -> S)
#define MC_MATCH_DUELTOURNAMENT_RESPONSE_SIDERANKING_INFO		70187	///< �ɸ��� ��ŷ�� ��ó ��ŷ ���� ����(S -> C)
#define MC_MATCH_DUELTOURNAMENT_GROUPRANKING_INFO				70276	///< ��� ��ʸ�Ʈ�� �׷� ��ŷ ����(S -> C)

#define MC_MATCH_DUELTOURNAMENT_GAME_INFO						70270	///< ��� ��ʸ�Ʈ ���� �������� ����
#define MC_MATCH_DUELTOURNAMENT_GAME_ROUND_RESULT_INFO			70183	///< ��� ��ʸ�Ʈ ���� �������� ���� ���� ��� ����
#define MC_MATCH_DUELTOURNAMENT_GAME_MATCH_RESULT_INFO			70212	///< ��� ��ʸ�Ʈ ���� �������� ��ġ ���� ��� ����
#define MC_MATCH_DUELTOURNAMENT_GAME_PLAYER_STATUS				70051	///< ��� ��ʸ�Ʈ ���� �������� ���尡 ����� ��, �ش� ���̸��� ���¸� ������ ����(C -> S)
#define MC_MATCH_DUELTOURNAMENT_GAME_NEXT_MATCH_PLYAERINFO		70181	///< ��� ��ʸ�Ʈ ���� �������� ���� ��ġ���� �÷��̾� ����

// ���� �� ����
// ����Ŀ ���
#define MC_MATCH_ASSIGN_BERSERKER					70306	///< ����Ŀ �Ӹ�(S -> C)
#define MC_MATCH_DUEL_QUEUEINFO						70179	///< ��⿭ ���� �˸�(S -> C)

// ����Ʈ ���� ��ɾ�(�����̹� ���, ����Ʈ ��� ����)
#define MC_QUEST_NPC_SPAWN					70190	///< NPC ����(S -> C)
#define MC_QUEST_ENTRUST_NPC_CONTROL		70165	///< NPC�� ������ �Ǿ�� ����(S -> C)
#define MC_QUEST_CHECKSUM_NPCINFO			70026	///< NPC�������� üũ���� �������� ������(C -> S)
#define MC_QUEST_REQUEST_NPC_DEAD			70067	///< NPC ���� ��û(C -> S)
#define MC_QUEST_NPC_DEAD					70193	///< NPC ����(S -> C)
#define MC_QUEST_REFRESH_PLAYER_STATUS		70066	///< �׾����� �ٽ� �¾��, ��� ���¸� �ֻ����� ����(S -> C)
#define MC_QUEST_NPC_ALL_CLEAR				70148	///< NPC ��� ����(S -> C)
#define MC_MATCH_QUEST_REQUEST_DEAD			70219	///< �÷��̾� �׾��ٰ� ��û(C -> S) ����Ʈ��忡���� MC_MATCH_GAME_KILL��� ������.
#define MC_MATCH_QUEST_PLAYER_DEAD			70036	///< �÷��̾� ����(S -> C)
#define MC_QUEST_OBTAIN_QUESTITEM			70318	///< ����Ʈ ������ ȹ��(S -> C)
#define MC_QUEST_STAGE_MAPSET				70216	///< �������� �ʼ� ����(S <-> C)
#define MC_QUEST_OBTAIN_ZITEM				70282	///< �Ϲ� ������ ȹ��(S -> C)
#define MC_QUEST_PING						70273	///< ����->Ŭ�� �� (S -> C)
#define MC_QUEST_PONG						70012	///< Ŭ��->���� �� (C -> S)
#define MC_QUEST_NPCLIST					70349	///< ���� ����Ʈ���� ����� NPC�� ����.(S->C) 
///<  Ŭ��� ������ ������ ������ NPC�� �ʱ�ȭ �Ѵ�.


#define MC_QUEST_PEER_NPC_BASICINFO			70133	///< ���������� ������Ʈ�Ǵ� NPC �⺻����
#define MC_QUEST_PEER_NPC_HPINFO			70275	///< ���������� ������Ʈ�Ǵ� NPC ü������
#define MC_QUEST_PEER_NPC_ATTACK_MELEE		70149	///< ���� ����
#define MC_QUEST_PEER_NPC_ATTACK_RANGE		70358	///< ���Ÿ� ����
#define MC_QUEST_PEER_NPC_SKILL_START		70062	///< ��ų ĳ���� ����
#define MC_QUEST_PEER_NPC_SKILL_EXECUTE		70084	///< ��ų ĳ���ü��� ȿ�� ����
#define MC_QUEST_PEER_NPC_DEAD				70328	///< ���� �� ������ �Ǿ�鿡�� ������. 
#define MC_QUEST_PEER_NPC_BOSS_HPAP			70295	///< ���������� ������Ʈ�Ǵ� NPC ���� ü�� �Ƹ�

// ����Ʈ ���� ���� ����(����Ʈ ���)
#define MC_QUEST_GAME_INFO					70059	///< ���� ����. �ε��� ���ҽ� ���� �˸�(S -> C)
#define MC_QUEST_COMBAT_STATE				70075	///< ����Ʈ ���ӳ� ���� ����(S -> C)
#define MC_QUEST_SECTOR_START				70034	///< �ʼ��� ���� ����(S -> C)
#define MC_QUEST_COMPLETED					70263	///< �ش� ����Ʈ Ŭ����(S -> C)
#define MC_QUEST_FAILED						70302	///< ����Ʈ ����(S -> C)

#define MC_QUEST_REQUEST_MOVETO_PORTAL		70285	///< ��Ż�� �̵���(C -> S)
#define MC_QUEST_MOVETO_PORTAL				70309	///< ��Ż�� �̵�(S -> C)
#define MC_QUEST_READYTO_NEWSECTOR			70162	///< ���ο� ���� �غ� �Ϸ�(S <-> C)

#define MC_GAME_START_FAIL					70168	///< ����Ʈ ������ ����.(S -> C)
#define MC_QUEST_STAGE_GAME_INFO			70198	///< ����� �������� ���� �˸�(QL, �ó�����ID). (S -> C)
#define MC_QUEST_SECTOR_BONUS				70161	///< ���� ���ʽ�(S -> C)

// ����Ʈ ���� ���� ����(�����̹� ���)
#define MC_QUEST_ROUND_START				70091	///< ���ο� ���� ����(S -> C)
#define MC_QUEST_REQUEST_QL					70248	///< ���� ����Ʈ ���������� QL������ ��û.(C -> S)
#define MC_QUEST_RESPONSE_QL				70174	///< ���� ����Ʈ ���������� QL������ �˸�.(S -> C)
#define MC_QUEST_SURVIVAL_RESULT			70070	///< �����̹� ��� �뺸(S -> C)
#define MC_SURVIVAL_RANKINGLIST				70291	///< �����̹� ���� ��ŷ ��� ����(S -> C)
#define MC_SURVIVAL_PRIVATERANKING			70341	///< ������ �����̹� ��ŷ ���� ����(S -> C)


// ����Ʈ �׽�Ʈ��
#define MC_QUEST_TEST_REQUEST_NPC_SPAWN		70350	///< NPC ���� ��Ź(C -> S)
#define MC_QUEST_TEST_REQUEST_CLEAR_NPC		70195	///< NPC Clear ��Ź(C -> S)
#define MC_QUEST_TEST_REQUEST_SECTOR_CLEAR	70357	///< ���� Clear(C -> S)	
#define MC_QUEST_TEST_REQUEST_FINISH		70278	///< ����Ʈ Complete(C -> S)


// MatchServer Schedule����.
#define MC_MATCH_SCHEDULE_ANNOUNCE_MAKE				70085	///< ������ ���� ����.
#define MC_MATCH_SCHEDULE_ANNOUNCE_SEND				70090	///< ������ ���� ����.
#define MC_MATCH_SCHEDULE_CLAN_SERVER_SWITCH_DOWN	70008	///< Ŭ������ Ŭ���� ��Ȱ��ȭ.
#define MC_MATCH_SCHEDULE_CLAN_SERVER_SWITCH_ON		70202	///< Ŭ������ Ŭ���� Ȱ��ȭ.
#define MC_MATCH_SCHEDULE_STOP_SERVER				70063	///< ���� ����.


// x-trap
#define MC_REQUEST_XTRAP_HASHVALUE					70030	///< �������� ȣȯ���� ���縸(������� �ʴ´�.)
#define MC_RESPONSE_XTRAP_HASHVALUE					70137	///< �������� ȣȯ���� ���縸(������� �ʴ´�.)
#define MC_REQUEST_XTRAP_SEEDKEY					70111	///< ��ȣŰ ��û(S -> C)
#define MC_RESPONSE_XTRAP_SEEDKEY					70102	///< ��ȣŰ ����(C -> S)
#define MC_REQUEST_XTRAP_DETECTCRACK				70042	///< �������� ȣȯ���� ���縸(������� �ʴ´�.)

// gameguard
#define MC_REQUEST_GAMEGUARD_AUTH					70258
#define MC_RESPONSE_GAMEGUARD_AUTH					70338
#define MC_REQUEST_FIRST_GAMEGUARD_AUTH				70249
#define MC_RESPONSE_FIRST_GAMEGUARD_AUTH			70244

// �ڼ�.
#define MC_REQUEST_GIVE_ONESELF_UP					70342	///< �ڼ��ϴ�.

//// �Ǿ����Ǿ� ���� ��ɾ� /////////////////////////////////////////////////////////////
#define MC_PEER_PING				70173	///< peer�� ������ network latency(ping)�� �����ϱ����� command
#define MC_PEER_PONG				70124	///< ping�� ���� ����
#define MC_PEER_UDPTEST				70230	///< Peer to Peer UDP ������ �������� �˻��Ѵ�.
#define MC_PEER_UDPTEST_REPLY		70099	///< Peer to Peer UDP ������ �������� �˻��Ѵ�.

#define MC_UDP_PING					70117	///< Client�� Agent�� ������ ping�� �����ϱ����� command
#define MC_UDP_PONG					70080	///< ping�� ���� ����

#define MC_PEER_OPENED				70169	///< ���� Peer ��� ����˸�
#define MC_PEER_BASICINFO			70054	///< ���������� ������Ʈ�Ǵ� ĳ���� �⺻���� ��ǥ������ �ٰŰ� �ȴ�
#define MC_PEER_HPINFO				70025	///< ���������� ������Ʈ�Ǵ� ĳ���� ü������ ��ǥ ������ �ٰŰ� �ȴ�
#define MC_PEER_HPAPINFO			70215	///< ���������� ������Ʈ�Ǵ� ĳ���� ü��/�Ƹ� ����
#define MC_PEER_DUELTOURNAMENT_HPAPINFO		70065	///< ���������� ������Ʈ�Ǵ� �����ʸ�Ʈ ���� ĳ���� ü��/�Ƹ� ����

#define MC_PEER_CHANGECHARACTER		70209
#define MC_PEER_MOVE				70035   ///< �� ���߿� MC_OBJECT_MOVE�� �ٲ����ҵ�..
#define MC_PEER_CHANGE_WEAPON		70271   
#define MC_PEER_CHANGE_PARTS		70061
#define MC_PEER_ATTACK				70331
#define MC_PEER_DAMAGE				70321
#define MC_PEER_RELOAD				70234
#define MC_PEER_SHOT				70333
#define MC_PEER_SHOT_SP				70005
#define MC_PEER_SKILL				70048
#define MC_PEER_SHOT_MELEE			70316	///< ��������
#define MC_PEER_DIE					70294
#define MC_PEER_SPAWN				70110
#define MC_PEER_DASH				70007
#define MC_PEER_SPMOTION			70094
#define MC_PEER_CHAT				70132
#define MC_PEER_CHAT_ICON			70356	///< ä�� ����/��. �Ӹ��� �������� �����ְų� �����.
#define MC_PEER_REACTION			70201	///< ����Ʈ�� ���� �˷��ش� 
#define MC_PEER_ENCHANT_DAMAGE		70009	///< ��æƮ �������� �¾Ҵ�

// ����Ʈ ������ ���� �κ�.
#define MC_MATCH_REQUEST_CHAR_QUEST_ITEM_LIST		70355	///< ���� ����Ʈ ������ ����� ��û.(C -> S)
#define MC_MATCH_RESPONSE_CHAR_QUEST_ITEM_LIST		70015	///< ���� ����Ʈ ������ ����� ����.(S -> C)
#define MC_MATCH_REQUEST_BUY_QUEST_ITEM				70139	///< ����Ʈ ������ ���� ��û.(C -> S)
#define MC_MATCH_RESPONSE_BUY_QUEST_ITEM			70218	///< ����Ʈ ������ ���� �Ϸ�.(S -> C)
#define MC_MATCH_REQUEST_SELL_QUEST_ITEM			70064	///< ���� ����Ʈ ������ �Ǹ� ��û.(C -> S)
#define MC_MATCH_RESPONSE_SELL_QUEST_ITEM			70361	///< ���� ����Ʈ ������ �Ǹ� �Ϸ�.(S -> C)
#define MC_MATCH_USER_REWARD_QUEST					70245	///< ����Ʈ�� �Ϸ���� ����� ����Ʈ ������ ����.
#define MC_MATCH_REQUEST_DROP_SACRIFICE_ITEM		70141	///< ��� �������� ���Կ� ���� ��û.(C -> S)
#define MC_MATCH_RESPONSE_DROP_SACRIFICE_ITEM		70172	///< ��� �������� ���Կ� ���� ����.(S -> C)
#define MC_MATCH_REQUEST_CALLBACK_SACRIFICE_ITEM	70089	///< ���Կ� �÷����� ��� �������� ȸ�� ��û.(C -> S)
#define MC_MATCH_RESPONSE_CALLBACK_SACRIFICE_ITEM	70335	///< ���Կ� �÷����� ��� �������� �ּ� ����.(S -> C)
#define MC_MATCH_REQUEST_SLOT_INFO					70003	///< ��� ������ ���� ������ ��û.(C -> S)
#define MC_MATCH_RESPONSE_SLOT_INFO					70288	///< ��� ������ ���� ������ �˸�.(S -> C)
#define MC_MATCH_NEW_MONSTER_INFO					70010	///< ���� ������ �߰��� ���ο� ���� ����.
#define MC_MATCH_REQUEST_MONSTER_BIBLE_INFO			70254	///< ���� ������ ���� ��û.(C -> S)
#define MC_MATCH_RESPONSE_MONSTER_BIBLE_INFO		70001	///< ���� ������ ���� �˸�.(S -> C)

//[[SHUFFLE_END]]		<< �� �ּ����� ID �����ִ� ���α׷����� �ν��ϴ� ��ũ�̴�






// ��ġ ������Ʈ ���� ��ɾ�
#define MC_MATCH_REGISTERAGENT				5001	///< ������Ʈ ���
#define MC_MATCH_UNREGISTERAGENT			5002	///< ������Ʈ ����
#define MC_MATCH_AGENT_REQUEST_LIVECHECK	5011	///< ������Ʈ Ȯ�ο�û
#define MC_MATCH_AGENT_RESPONSE_LIVECHECK	5012	///< ������Ʈ Ȯ������
#define MC_AGENT_ERROR						5013	///< ������Ʈ ���� ����

#define MC_AGENT_CONNECT					5021	///< ��ġ������ ������Ʈ ���� ���
#define MC_AGENT_DISCONNECT					5022	///< ��ġ������ ������Ʈ ���� �������
#define MC_AGENT_LOCAL_LOGIN				5023	///< Ŭ���̾�Ʈ ����ó��
#define MC_AGENT_RESPONSE_LOGIN				5024	///< Ŭ���̾�Ʈ�� �α��� ����
//#define MC_AGENT_MATCH_VALIDATE				5031	///< ��ġ�������� ����Ȯ��
#define MC_AGENT_STAGE_RESERVE				5051	///< ������Ʈ�� �������� ����
#define MC_AGENT_STAGE_RELEASE				5052	///< ������Ʈ�� �������� ����
#define MC_AGENT_STAGE_READY				5053	///< ������Ʈ�� �������� �غ�Ϸ�
#define MC_AGENT_LOCATETO_CLIENT			5061	///< Ŭ���̾�Ʈ���� Agent �˸�
#define MC_AGENT_RELAY_PEER					5062	///< ������Ʈ�� �߰�����
#define MC_AGENT_PEER_READY					5063	///< ��ġ������ �Ǿ��غ� �˸�
#define MC_AGENT_PEER_BINDTCP				5071	///< Ŭ���̾�Ʈ Bind TCP
#define MC_AGENT_PEER_BINDUDP				5072	///< Ŭ���̾�Ʈ Bind UDP
#define MC_AGENT_PEER_UNBIND				5073	///< Ŭ���̾�Ʈ Unbind

#define MC_AGENT_TUNNELING_TCP				5081	///< TCP �ͳθ�
#define MC_AGENT_TUNNELING_UDP				5082	///< UDP �ͳθ�
#define MC_AGENT_ALLOW_TUNNELING_TCP		5083	///< TCP �ͳθ� ���
#define MC_AGENT_ALLOW_TUNNELING_UDP		5084	///< UDP �ͳθ� ���
#define MC_AGENT_DEBUGPING					5101	///< ������
#define MC_AGENT_DEBUGTEST					5102	///< ������


#define MC_REQUEST_RESOURCE_CRC32				11001
#define MC_RESPONSE_RESOURCE_CRC32				12002

/// Keeper�� Keeper Manager�� ����ϴµ� �ʿ��� ���. 2005.06.03 Ŀ�ǵ� ���� �ʿ�.
#define MC_KEEPER_MANAGER_CONNECT				31001	///< keeper Manager���� keeper�� ���� ��û.
#define MC_CHECK_KEEPER_MANAGER_PING			31002	///< Keeper�� Keeper Manager�� ���������� ����Ǿ� �ִ��� �˻�.
#define MC_REQUEST_MATCHSERVER_STATUS			31004	///< MatchServer�� ������ ��û.(Keeper -> MatchServer)
#define MC_RESPONSE_MATCHSERVER_STATUS			31005	///< Keeper�� MatchServer�� ������ ������ ��.(MatchServer -> Keeper)
// 2005.06.01 ~
#define MC_RESPONSE_KEEPER_MANAGER_CONNECT		31006	///< Keeper manager�� ������ ���������� �̷�� ���� �˸�.( Keeper -> Keeper Manager )
#define MC_REQUEST_CONNECTION_STATE				31007	///< ���� ������ ����.(Keeper Manager -> Keeper)
#define MC_RESPONSE_CONNECTION_STATE			31008	///< �������� ����.(Keeper -> Keeper Manager)
#define MC_REQUEST_SERVER_HEARBEAT				31009	///< ������ �����ϰ� �ִ��� ���� ��û.(Keeper -> MatchServer)
#define MC_RESPONSE_SERVER_HEARHEAT				31010	///< ������ �����ϰ� ������ ����.(MatchServer -> Keeper)
#define MC_REQUEST_KEEPER_CONNECT_MATCHSERVER	31011	///< Keeper�� MatchServer�� �����ϵ��� ��û��(Keeper Manager -> Keeper -> MatchServer )
#define MC_RESPONSE_KEEPER_CONNECT_MATCHSERVER	31012	///< Keeper�� MatchServer�� �����ߴٴ� ����.(MatchServer -> Keeper -> Keeper Manager )
#define MC_REQUEST_REFRESH_SERVER				31013	///< Keeper Manager�� ���� ����Ʈ ���� ������ ���ؼ� Keeper�� MatchServer�� Heartbaetäũ ��û.(Keeper Manager -> Keeepr)
#define MC_REQUEST_LAST_JOB_STATE				31014	///< ������ ����� ���� ����� ��û.(Keeper -> Keeper Manager )
#define MC_RESPONSE_LAST_JOB_STATE				31015	///< �۾� ��� ��û ����.(Keeper -> Keeper Manager)
#define MC_REQUEST_CONFIG_STATE					31016	///< Keeper�� ����� ���� ���� ��û.(Keeper Manager -> Keeper)
#define MC_RESPONSE_CONFIG_STATE				31017	///< Keeper�� ����� ���� ���� ��û ����.(Keeper -> Keeper Manager)
#define MC_REQUEST_SET_ONE_CONFIG				31018	///< Config�ϳ� ���� ��û.(Keeper Manager -> Keeper)
#define MC_RESPONSE_SET_ONE_CONFIG				31019	///< Config�ϳ� ���� ��û ����.(Keeper -> Keeper Manager)
#define MC_REQUEST_KEEPERMGR_ANNOUNCE			31020	///< Keeper Manager���� �� ������ ������ �������� Keeper�� ��û��.(Keeper Manager -> Keeper)
#define MC_REQUEST_KEEPER_ANNOUNCE				31021	///< Keeper���� MatchServer�� ���������� �˸����� ��û��.(Keeper -> MatchServer)
#define MC_REQUEST_RESET_PATCH					31022	///< ����+���� ������ ��ġ �۾����¸� �ʱ�ȭ��.
#define MC_REQUEST_DISCONNECT_SERVER			31023	///< Keeper�� MatchServer���� ���� ����.
#define MC_REQUEST_REBOOT_WINDOWS				31024	///< ������ �����.(Keeper Manager -> Keeper)
#define MC_REQUEST_ANNOUNCE_STOP_SERVER			31025	///< �������װ� �԰� ������ ���� ��Ŵ ��û.
#define MC_RESPONSE_ANNOUNCE_STOP_SERVER		31026	///< �������װ� �԰� ������ ���� ��Ŵ ��û ����.
#define MC_REQUEST_SERVER_AGENT_STATE			31027	///< ���� ������ ������Ʈ�� ���� ���� ��û.
#define MC_RESPONSE_SERVER_AGENT_STATE			31028	///< ���� ������ ������Ʈ�� ���� ���� ��û ����.
#define MC_REQUEST_WRITE_CLIENT_CRC				31029	///< Ŭ���̾�Ʈ�� CRC CheckSum�� ���� ini���Ͽ� ���� ��û.(KeeperManager -> Keeper)
#define MC_RESPONSE_WRITE_CLIENT_CRC			31030	///< Ŭ���̾�Ʈ�� CRC CheckSum�� ���� ini���Ͽ� ���� ��û ����.(Keeper -> Keeper Manager)
#define MC_REQUEST_KEEPER_RELOAD_SERVER_CONFIG	31031	///< Keeper�� ����Ǿ��ִ� ������ ���� ������ �ٽ� �ε��ϵ��� ��û��.(KeeperManager -> Keeper)
#define MC_REQUEST_RELOAD_CONFIG				31032	///< ������ ���� ������ �ٽ� �δ��ϵ��� ��û.(Keeper -> server)
#define MC_REQUEST_KEEPER_ADD_HASHMAP			31033	
#define MC_RESPONSE_KEEPER_ADD_HASHMAP			31034
#define MC_REQUEST_ADD_HASHMAP					31035
#define MC_RESPONSE_ADD_HASHMAP					31036

// MatchServer ��ġ ����.
#define MC_REQUEST_DOWNLOAD_SERVER_PATCH_FILE	32024	///< Keeper�� FTP�������� Patch������ �ٿ�ε� ��Ŵ.(Keeper Manager -> Keeper )
#define MC_REQUEST_START_SERVER					32026	///< MatchServer���� ��û.(Keeper Manager -> Keeper)
#define MC_REQUEST_STOP_SERVER					32028	///< ���� ���� ��û.(Keeper -> Keeper Manager)
#define MC_REQUEST_PREPARE_SERVER_PATCH			32030	///< ��ġ �غ� �۾�.(���� Ǯ��, �ӽ� ���� ����.)
#define MC_REQUEST_SERVER_PATCH					32032	///< ��ġ ������ ������.(Keeper Manager -> Keeper )
// MatchAgent ��ġ ����.
#define MC_REQUEST_STOP_AGENT_SERVER			33034	///< Agent server���� ��û.(Keeper Manager -> Keeper )
#define MC_REQUEST_START_AGENT_SERVER			33036	///< Agent server���� ��û.(Keeper Manager -> Keeper)
#define MC_REQUEST_DOWNLOAD_AGENT_PATCH_FILE	33038	///< request agent patch file download.(Keeper Manager -> Keeper)
#define MC_REQUEST_PREPARE_AGENT_PATCH			33040	///< reqeust prepare agent patch.(Keeper Manager -> Keeper)
#define MC_REQUEST_AGENT_PATCH					33042	///< request agent patch.(Keeper Manager -> Keeper)
#define MC_REQUEST_SERVER_STATUS				33043	///< server�� agent�� ������ Keeper�� ��û��.(Keeper Manager -> keeper)
#define MC_RESPONSE_SERVER_STATUS				33044	///< server�� agetn�� ���� ��û ����.(Keeper -> Keeper Manager)
// Keeper manager schedule.
#define MC_REQUEST_KEEPER_MANAGER_SCHEDULE		34001	///< request keeper manager schedule.(Keeper Manager -> Keeper -> MatchServer)
#define MC_RESPONSE_KEEPER_MANAGER_SCHEDULE		34002	///< Keeper Manager�� �������� ��û ����.
#define MC_REQUEST_START_SERVER_SCHEDULE		34003	///< �ٽý��� �����ٿ��� ������ �����ϴ� ������. �����Ҷ����� �������� ���ŵ��� ����.
///


/// Locator����.
#define MC_REQUEST_SERVER_LIST_INFO				40001	/// ���Ӱ����� ������ ����Ʈ ���� ��û.(Client -> Locator)
#define MC_RESPONSE_SERVER_LIST_INFO			40002	/// ���Ӱ����� ���� ����Ʈ ���� ����.(Locator -> Client)
#define MC_RESPONSE_BLOCK_COUNTRY_CODE_IP		40003	/// ���ӺҰ� ���� �ڵ��� IP����.(Locator -> Client)


// filter.
#define MC_RESPONSE_BLOCK_COUNTRYCODE			50001	/// ���� �����ڵ��� IP�� ���ӽ� �뺸��.
#define MC_LOCAL_UPDATE_USE_COUNTRY_FILTER		50002
#define MC_LOCAL_GET_DB_IP_TO_COUNTRY			50003
#define MC_LOCAL_GET_DB_BLOCK_COUNTRY_CODE		50004
#define MC_LOCAL_GET_DB_CUSTOM_IP				50005
#define MC_LOCAL_UPDATE_IP_TO_COUNTRY			50006
#define MC_LOCAL_UPDATE_BLOCK_COUTRYCODE		50007
#define MC_LOCAL_UPDATE_CUSTOM_IP				50008
#define MC_LOCAL_UPDATE_ACCEPT_INVALID_IP		50009

#define MC_TEST_BIRDTEST1					60001	///< ���� �׽�Ʈ1
#define MC_TEST_PEERTEST_PING				60002	///< Target Peer Test
#define MC_TEST_PEERTEST_PONG				60003	///< Target Peer Test


/// Ŀ�ǵ� ���� �ɼ�

// MC_MATCH_CHANNEL_REQUEST_ALL_PLAYER_LIST�� ���οɼ�
#define MCP_MATCH_CHANNEL_REQUEST_ALL_PLAYER_LIST_NORMAL		0		
#define MCP_MATCH_CHANNEL_REQUEST_ALL_PLAYER_LIST_NONCLAN		1
#define MCP_MATCH_CHANNEL_REQUEST_ALL_PLAYER_LIST_MYCLAN		2


#endif