
#include "SecondCut.h"

SecondCut::SecondCut()
{
	m_Background = NNSprite::Create( L"Sprite/map.png" );
	AddChild( m_Background );

	m_Text = NNLabel::Create( L"�׽�Ʈ2 �׽�Ʈ2\n�׽�Ʈ2 �׽�Ʈ2 �Դϴ�.", L"���� ���", 20.f );
	AddChild( m_Text );

	m_Text->SetPosition( 30.f, 500.f );
	m_Text->SetBold( true );
}
SecondCut::~SecondCut()
{

}

void SecondCut::Render()
{
	StoryCut::Render();
}
void SecondCut::Update( float dTime )
{
	StoryCut::Update( dTime );
}