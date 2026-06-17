#include "TankHead.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Tank.h"

namespace
{

}

TankHead::TankHead(GameObject* parent)
	:GameObject(parent, "TankHead"), hModel_(-1)
{
}

TankHead::~TankHead()
{
}

void TankHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
	assert(hModel_ >= 0);

	transform_.position_ = { transform_.position_.x,transform_.position_.y,0.0f };
	transform_.rotate_ = { 0.0f,transform_.rotate_.y,0.0f };
}

void TankHead::Update()
{
}

void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
