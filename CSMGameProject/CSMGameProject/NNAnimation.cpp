
#include "NNAnimation.h"

NNAnimation::NNAnimation()
	: m_Frame(0), m_Time(0.f)
{

}
NNAnimation::~NNAnimation()
{

}

void NNAnimation::Render()
{
	NNObject::Render();
}
void NNAnimation::Update( float eTime )
{
	NNObject::Update( eTime );
}