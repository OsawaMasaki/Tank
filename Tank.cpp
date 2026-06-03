#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

Tank::Tank(GameObject* parent)
	:GameObject(parent,"Tank"),hModel_(-1)
{
}

Tank::~Tank()
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);

	transform_.rotate_ = { transform_.position_.x,transform_.position_.y,0.0f };
	transform_.rotate_ = { 0.0f,transform_.rotate_.y,0.0f };
}

void Tank::Update()
{
	//Aキーを押している間、左に回転する
	if(Input::IsKey(DIK_A))
	{
		transform_.rotate_.y += 1.0f;
	}
	//Dキーを押している間、右に回転する
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y -= 1.0f;
	}

	//とりあえず動くように
	if (Input::IsKey(DIK_UP))
	{
		transform_.position_.x += 0.02f;
	}
}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}
