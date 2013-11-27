#include "FifthCut.h"
#include "NNApplication.h"

FifthCut::FifthCut()
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	m_Background = NNSprite::Create( L"Sprite/StoryScene_4.png" );
	m_Background->SetPosition( width/2, height/2 );
	m_Background->SetCenter( m_Background->GetImageWidth()/2.f, m_Background->GetImageHeight()/2.f );
	AddChild( m_Background );

	m_Text = NNLabel::Create( L"���� ���ɿ� ��ƿ���ɸ� �����ּ���. �Ͼ����, ��翩...", L"���� ���", 20.f );
	AddChild( m_Text );

	m_Text->SetPosition( 30.f, 500.f );
	m_Text->SetBold( true );
}
FifthCut::~FifthCut()
{

}

void FifthCut::Render()
{
	StoryCut::Render();
}
void FifthCut::Update( float dTime )
{
	StoryCut::Update( dTime );
}