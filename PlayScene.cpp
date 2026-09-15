#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "Enemy.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//#include "TankHead.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),timer(0)
{
}

void PlayScene::Initialize()
{
	Instantiate<Ground>(this);
	Instantiate<Tank>(this);
	Instantiate<Enemy>(this);
	//Instantiate<TankHead>(this);
	//Instantiate<Enemy>();
}

void PlayScene::Update()
{
	timer++;
	if (timer > 400)
	{
		timer = 0;
	}
	if (timer == 90)
	{
		Instantiate<Enemy>(this);
		Instantiate<Enemy>(this);
	}

	if (FindObject("Enemy") == nullptr)
	{
		SceneManager* pSceneManager = (SceneManager*)(this->GetParent());
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);

	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
