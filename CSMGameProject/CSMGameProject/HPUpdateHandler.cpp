
#include "PacketHandler.h"
#include <stdio.h>
#include <assert.h>
#include "PlayerManager.h"

HPUpdateHandler::HPUpdateHandler()
{

}
HPUpdateHandler::~HPUpdateHandler()
{

}
void HPUpdateHandler::HandlingPacket( short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header )
{
	switch ( packetType )
	{
	case PKT_SC_KEYSTATE:
		{
			if ( circularBuffer->Read((char*)&m_HPUpdateResult, header->m_Size) )
			{
				// ��Ŷó��
				if ( m_HPUpdateResult.m_PlayerId == -1  )
				{
					/// �߸��� ������
					/// �����Ѵ�
					return;
				}
				//�α����� �߸��Ǿ� ĳ���Ͱ� ���� �� �����Ƿ�
				CPlayerManager::GetInstance()->NewPlayer( m_HPUpdateResult.m_PlayerId );
				
				CPlayerManager::GetInstance()->UpdatePlayerHP( m_HPUpdateResult.m_PlayerId, m_HPUpdateResult.m_HP );
				printf("HP Changed[%d] Pos : %d \n", m_HPUpdateResult.m_PlayerId,
					m_HPUpdateResult.m_HP) ;
			}
			else
			{
				assert(false) ;
			}
		}
		break;
	}
}
