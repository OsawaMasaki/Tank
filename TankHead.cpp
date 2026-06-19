#include "TankHead.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
//#include "Engine/Debug.h"
#include "Tank.h"
#include "Bullet.h"

namespace
{
	const float BULLET_SPEED = 0.2; //弾のスピード
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
}

void TankHead::Update()
{
	if (Input::IsKey(DIK_RIGHT) && transform_.rotate_.y <= 150.0f)
	{
		transform_.rotate_.y += 1.0f;
	}
	if (Input::IsKey(DIK_LEFT) && transform_.rotate_.y >= -150.0f)
	{
		transform_.rotate_.y -= 1.0f;
	}

	if (Input::IsKey(DIK_SPACE))
	{
		XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");
		XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");
		XMVECTOR vTop = XMLoadFloat3(&cannonTop);
		XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);
		XMVECTOR vMove = XMVectorSubtract(vTop,vRoot);

		vMove = 0.2 * vMove;
		XMFLOAT3 move;
		XMStoreFloat3(&move, vMove);

		//弾の生成
		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent()); //親をタンクにして弾を発射
		pBullet->SetMoveVector(move);
		pBullet->SetPosition(cannonTop);
	}

}

void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
