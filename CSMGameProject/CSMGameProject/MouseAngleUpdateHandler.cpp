#include "PacketHandler.h"
#include <stdio.h>
#include <assert.h>
#include "PlayerManager.h"

MouseAngleUpdateHandler::MouseAngleUpdateHandler()
{

}
MouseAngleUpdateHandler::~MouseAngleUpdateHandler()
{

}
void MouseAngleUpdateHandler::HandlingPacket( short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header )
{
	switch ( packetType )
	{
	case PKT_SC_MOUSEANGLE:
		{
			if ( circularBuffer->Read((char*)&m_MouseAngleUpdateResult, header->m_Size) )
			{
				// 패킷처리
				if ( m_MouseAngleUpdateResult.m_PlayerId == -1  )
				{
					/// 잘못된 데이터
					/// 무시한다
					return;
				}
				//로그인이 잘못되어 캐릭터가 없을 수 있으므로
				CPlayerManager::GetInstance()->NewPlayer( m_MouseAngleUpdateResult.m_PlayerId );
				
				CPlayerManager::GetInstance()->UpdatePlayerRotation( m_MouseAngleUpdateResult.m_PlayerId, m_MouseAngleUpdateResult.m_Angle );
				printf("Mouse Angle Changed[%d] angle : %.1f\n", m_MouseAngleUpdateResult.m_PlayerId,
					m_MouseAngleUpdateResult.m_Angle) ;
			}
			else
			{
				assert(false) ;
			}
		}
		break;
	}
}
