#ifndef _TESTER
#define _TESTER


#include "MUID.h"
#include "MCommandManager.h"
#include "MDebug.h"


class MSafeUDP;
class MCommand;


class Tester
{
public :
	Tester();
	~Tester();

	bool Create();
	bool CreateTestThread();

	const int MakeCmdPacket( char* pOutPacket, const int nMaxSize, MCommand* pCmd );

	MCommand* GetCommand();

	bool SendUDPtoLocator();
	void SendCommandByUDP( DWORD dwIP, int nPort, MCommand* pCmd );

	void SetOut( CEdit* pOut ) { m_pOut = pOut; }
	CEdit* GetOut() { return m_pOut; }

	inline int GetElapse() { return m_nElapse; }
	void SetElapse( const int n ) { m_nElapse = n; }

	void ReleaseCommand();
	
	static DWORD WINAPI LocatorTesterThread( void* pWorkContext );
	static bool UDPSocketRecvEvent( DWORD dwIP, WORD wRawPort, char* pPacket, DWORD dwSize );

private :
	MCommandManager	m_CommandManager;		///< Ŀ�ǵ� �Ŵ���
	MUID			m_This;					///< �ڱ� Ŀ�´������� UID
	MSafeUDP*		m_pSafeUDP;
	MCommand*		m_pCmd;
	int				m_nElapse;
	CEdit*			m_pOut;
};

#endif