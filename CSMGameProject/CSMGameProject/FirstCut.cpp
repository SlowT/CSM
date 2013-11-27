
#include "FirstCut.h"
#include "NNApplication.h"

FirstCut::FirstCut()
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	m_Background = NNSprite::Create( L"Sprite/StoryScene_0.png" );
	m_Background->SetPosition( width/2, height/2 );
	m_Background->SetCenter( m_Background->GetImageWidth()/2.f, m_Background->GetImageHeight()/2.f );
	AddChild( m_Background );

	m_StoryTextBox = NNSprite::Create( L"Sprite/StoryTextBox.png");
	m_StoryTextBox->SetPosition( width/2, height/2 + 200.f );
	m_StoryTextBox->SetCenter( m_StoryTextBox->GetImageWidth()/2.f, m_StoryTextBox->GetImageHeight()/2.f );
	AddChild( m_StoryTextBox );

	m_Text = NNLabel::Create( L"������ ���ɵ��� ���������ϰ� ��׿�.", L"���� ���", 20.f );
	AddChild( m_Text );

	m_Text->SetPosition( 100.f, 460.f );
	m_Text->SetBold( true );
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