#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), hModel_(-1), move_(XMFLOAT3(0, 0, 0))
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Bullet.fbx");
	assert(hModel_ >= 0);
}

void Bullet::Update()
{
	//進行方向に移動する
	//transform_.position_ += move_;
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMVECTOR vMove = XMLoadFloat3(&move_);
	vPos += vMove;
	XMStoreFloat3(&transform_.position_, vPos);

	if (transform_.position_.z > 50.0f || transform_.position_.z < -50.0f ||
		transform_.position_.x > 50.0f || transform_.position_.x < -50.0f)
	{
		KillMe(); //弾がある程度遠くに行ったら消す
	}
}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}
