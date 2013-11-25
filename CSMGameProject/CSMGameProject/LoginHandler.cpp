
#include "PacketHandler.h"
#include <stdio.h>
//#include <windows.h>
#include <assert.h>
#include "PlayerManager.h"
LoginHandler::LoginHandler()
{

}
LoginHandler::~LoginHandler()
{

}
void LoginHandler::HandlingPacket( short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header )
{
	switch ( packetType )
	{
	case PKT_SC_LOGIN:
		{
			if ( circularBuffer->Read((char*)&m_LoginResultPacket, header->m_Size) )
			{
				// ��Ŷó��
				if ( m_LoginResultPacket.m_MyPlayerInfo.m_PlayerId == -1  )
				{
					/// ���� �ɸ��� �α��� ���д�.
					PostQuitMessage(-1) ;
				}
				CPlayerManager::GetInstance()->SetMyPlayerId( m_LoginResultPacket.m_MyPlayerInfo.m_PlayerId );
				//���� �����ִ� �÷��̾��� ��ü �����
				for(int i=0; i<m_LoginResultPacket.m_NowPlayersLength; i++)
				{
					if( m_LoginResultPacket.m_MyPlayerInfo.m_PlayerId != m_LoginResultPacket.m_PlayerInfo[i].m_PlayerId )
					{
						CPlayerManager::GetInstance()->NewPlayer( m_LoginResultPacket.m_PlayerInfo[i].m_PlayerId );
						CPlayerManager::GetInstance()->UpdatePlayerInfo( m_LoginResultPacket.m_PlayerInfo[i] );
					}
				}
				printf("LOGIN SUCCESS ClientId[%d] \n", m_LoginResultPacket.m_MyPlayerInfo.m_PlayerId) ;
			}
			else
			{
				assert(false) ;
			}
		}
		break;
	}
}
