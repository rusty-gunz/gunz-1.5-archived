#pragma once

// MFeatureDefine.h: Contains Features definitions only.
// NOTE: It affects every single project because it's CSCommons file.

#if defined(_DEBUG) || defined(_RELEASE) || defined(LOCALE_KOREA) || defined(LOCALE_NHNUSA)// || defined(LOCALE_JAPAN) || defined(LOCALE_BRAZIL)
	#define _AVATAR_ENABLE
#endif

//#if defined(_DEBUG) || defined(_RELEASE) || defined(LOCALE_KOREA)
#if 0
#	define _SELL_CASHITEM
#endif

#ifndef CAMFIX
	#define _EXTRESOLUTION 1
#endif

#if defined(LOCALE_BRAZIL)
#define _MULTILANGUAGE
#endif

#if defined(_DEBUG) || defined(_RELEASE) || defined(LOCALE_KOREA) || defined(LOCALE_NHNUSA) || defined(LOCALE_JAPAN) || defined(LOCALE_BRAZIL)
#define _DUELTOURNAMENT
#endif

//#define _PSANTICHEAT

#define _DISABLE_CLIENT_SECURITY_CHECKS
#define _DISABLE_NETWORK_SECURITY_CHECKS

//#define _PACKET_ALIAS

#define _QUEST

#define _QUEST_ITEM

#define _MONSTER_BIBLE 

//#define _PROMOCODE

//#define _GAMBLEITEM_TEST_LOG

//#define _REPLAY_TEST_LOG

//#define _LOCATOR