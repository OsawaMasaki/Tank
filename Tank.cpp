#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Ground.h"
#include "Engine/Camera.h"
#include "TankHead.h"


//タンクのボディのクラス

namespace
{
	XMVECTOR vFront = { 0,0,1,0 };  //タンクの前方向のベクトル
	float moveSpeed = 0.1f;         //タンクの移動速度
	const float CAM_HEIGHT_BIAS = 0.2f; //カメラの高さのバイアス
	enum CAM_TYPE
	{
		FIXED_CAM,   //固定カメラ
		TPS_CAM,     //三人称視点カメラ
		TPS_CAMROT,  //三人称視点カメラ(回転)
		FPS_CAM,     //一人称視点カメラ
		CAM_TYPE_MAX
	};
}


Tank::Tank(GameObject* parent)
	:GameObject(parent,"Tank"),hModel_(-1),camType_(FIXED_CAM)
{
}

Tank::~Tank()
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);

	//transform_.position_ = { transform_.position_.x,transform_.position_.y,0.0f };
	//transform_.rotate_ = { 0.0f,transform_.rotate_.y,0.0f };

	Instantiate<TankHead>(this);
}

void Tank::Update()
{

	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//ロード：読み込み
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//Y軸回転行列を作る
	XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);

	//カメラ
	if (Input::IsKeyDown(DIK_C))
	{
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
		//0,1,2,0,1....CAM_TYPE_MAX -1 の順でcamType_を切り替える
	}
	switch (camType_)
	{
	case FIXED_CAM:
		//固定カメラの処理
		SetFixedCam();
		break;
	case TPS_CAM://三人称視点カメラの処理
	{

		XMFLOAT3 camPos = transform_.position_; //タンクの位置をカメラの位置にする
		camPos.y = camPos.y + 4.0f;
		camPos.z = camPos.z - 9.0f;
		Camera::SetPosition(camPos); //カメラの位置
		Camera::SetTarget(transform_.position_);
	}
		break;
	case TPS_CAMROT://三人称視点カメラ(回転)の処理
	{
		XMFLOAT3 camPos;//タンクの位置をカメラの位置にする
		XMVECTOR vCAM = { 0.0f,3.0f,-7.0f,0.0f };//カメラの位置をタンクの位置より少し後ろに
		vCAM = XMVector3TransformCoord(vCAM, matRot); //タンクの回転をカメラの位置に反映させる
		XMStoreFloat3(&camPos,vPos + vCAM);
		Camera::SetPosition(camPos); //カメラの位置
		Camera::SetTarget(transform_.position_);
	}
		break;
	case FPS_CAM://一人称視点カメラの処理
	{

		XMFLOAT3 camPos = transform_.position_; //タンクの位置をカメラの位置にする
		camPos.y = camPos.y + CAM_HEIGHT_BIAS;
		Camera::SetPosition(camPos); //カメラの位置
		XMFLOAT3 camTarget;
		XMStoreFloat3(&camTarget, vPos + vMove);
		Camera::SetTarget(camTarget);
	}
		break;
	}

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

		vPos = vPos + moveSpeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos); //ストア：書き込み
	}
	if (Input::IsKey(DIK_DOWN) || Input::IsKey(DIK_S))
	{
		//transform_.position_.z += 0.1f;

		vPos = vPos - moveSpeed * vMove;
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
	//Debug::Log("Yangle = ");
	//Debug::Log(transform_.rotate_.y, true);
	Debug::Log("camType_ = ");
	Debug::Log(camType_, true);


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

void Tank::SetFixedCam()
{
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 20, -30));
}
