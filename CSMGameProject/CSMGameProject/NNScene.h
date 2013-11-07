
#pragma once

#include "NNObject.h"
#include "NNCamera.h"

/* */
/* NNScene
/* SceneDirector�� ��ϵ� �� �ִ� Scene ���
/* */

class NNScene : virtual public NNObject
{
public:
	NNScene();
	virtual ~NNScene();

	static NNScene* Create();

	void Render();
	void Update( float dTime );

	NNCamera* GetCamera() const { return m_Camera; }

protected:
	NNCamera* m_Camera;
};