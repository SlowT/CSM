
#include "FirstCut.h"

FirstCut::FirstCut()
{
	m_Background = NNSprite::Create( L"Resources/Texture/map.png" );
	AddChild( m_Background );

	m_Text = NNLabel::Create( L"�׽�Ʈ �׽�Ʈ\n�׽�Ʈ �׽�Ʈ �Դϴ�.", L"���� ���", 20.f );
	AddChild( m_Text );

	m_Text->SetPosition( 30.f, 600.f );
}
FirstCut::~FirstCut()
{

}

void FirstCut::Render()
{
	StoryCut::Render();
}
void FirstCut::Update( float dTime )
{
	StoryCut::Update( dTime );
}