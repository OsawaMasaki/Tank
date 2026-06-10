#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Ground.h"

//タンクのボディのクラス

namespace
{
	XMVECTOR vFront = { 0,0,1,0 };  //タンクの前方向のベクトル
	float moveSpeed = 0.1f;         //タンクの移動速度

}


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
	//回転の処理
	//Aキーを押している間、左に回転する
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 2.0f;
	}
	//Dキーを押している間、右に回転する
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 2.0f;
	}


	//移動の処理
	if (Input::IsKey(DIK_UP) || Input::IsKey(DIK_W))
	{
		//transform_.position_.z += 0.1f;

		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//ロード：読み込み
		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//Y軸回転行列を作る
		XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);

		vPos = vPos + moveSpeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos); //ストア：書き込み
	}
	/*
	if (Input::IsKey(DIK_DOWN))
	{
		transform_.position_.z -= 0.1f;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= 0.1f;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += 0.1f;
	}
	*/

	//デバック用
	Debug::Log("Yangle = ");
	Debug::Log(transform_.rotate_.y, true);


	//レイキャストして、浮いてたら地面に落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;   //地面は0より下に作られている。そうじゃないときはもっと上から！
	data.dir = { 0, -1,0 };//真下にレイをとばす

	//groundオブジェクトのモデルのハンドルを探す
	Ground* pGround = (Ground*)FindObject("Ground");

	int hGroundModel = pGround->GetModelHandle();
	Model::RayCast(hGroundModel, &data);

	if (data.hit == true)
	{
		//レイの発射位置から、地面までの距離を引いて、地面にぴったりつける
		transform_.position_.y = - data.dist;
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
