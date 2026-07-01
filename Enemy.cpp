#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Ground.h"
#include <random>

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1),count_(40)
{
}

void Enemy::Initialize()
{
	//hModel_ = Model::Load("kusa.fbx");
	hModel_ = Model::Load("kasasuraimu.fbx");
	//Model::SetAnimFrame(hModel_, 1, 120, 1.0f);
	Model::SetAnimFrame(hModel_, 1, 120, 1.0f);
	assert(hModel_ >= 0);


	// --- 初期化処理（関数やループの外、または静的変数として1回だけ行うのがベスト） ---
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	// -25.0f から 25.0f の範囲を指定
	std::uniform_real_distribution<float> dist(-20.0f, 20.0f);


	// --- 実際の座標設定の処理 ---
	// ランダムな値を生成して代入
	float EnemyPosx = dist(engine);
	float EnemyPosz = dist(engine);

	//transform_.scale_.y = 1.0f;

	transform_.position_ = { EnemyPosx, 10, EnemyPosz };
	SphereCollider* collider = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 10.5f);
	AddCollider(collider);
}

void Enemy::Update()
{
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
		transform_.position_.y = -data.dist;
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Bullet")
	{
		pTarget->KillMe();
		KillMe();
	}
}
