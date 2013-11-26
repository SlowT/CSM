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
				// ��Ŷó��
				if ( m_MouseAngleUpdateResult.m_PlayerId == -1  )
				{
					/// �߸��� ������
					/// �����Ѵ�
					return;
				}
				//�α����� �߸��Ǿ� ĳ���Ͱ� ���� �� �����Ƿ�
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
