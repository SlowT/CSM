
#include "PacketHandler.h"
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include "PlayerManager.h"

//���� �� �����߳���?//
GameKeyStatesUpdateHandler::GameKeyStatesUpdateHandler()
{

}
GameKeyStatesUpdateHandler::~GameKeyStatesUpdateHandler()
{

}
void GameKeyStatesUpdateHandler::HandlingPacket( short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header )
{
	switch ( packetType )
	{
	case PKT_SC_KEYSTATE:
		{
			if ( circularBuffer->Read((char*)&m_GameKeyStatesUpdateResult, header->m_Size) )
			{
				// ��Ŷó��
				if ( m_GameKeyStatesUpdateResult.m_MyPlayerInfo.m_PlayerId == -1  )
				{
					/// �߸��� ������
					/// �����Ѵ�
					return;
				}
				//�α����� �߸��Ǿ� ĳ���Ͱ� ���� �� �����Ƿ�
				CPlayerManager::GetInstance()->NewPlayer( m_GameKeyStatesUpdateResult.m_MyPlayerInfo.m_PlayerId );
				
				CPlayerManager::GetInstance()->UpdatePlayerInfo( m_GameKeyStatesUpdateResult.m_MyPlayerInfo );
				printf("Key State Changed[%d] Pos : %4d, %4d \n", m_GameKeyStatesUpdateResult.m_MyPlayerInfo.m_PlayerId,
					m_GameKeyStatesUpdateResult.m_MyPlayerInfo.m_X, m_GameKeyStatesUpdateResult.m_MyPlayerInfo.m_Y) ;
			}
			else
			{
				assert(false) ;
			}
		}
		break;
	}
}
