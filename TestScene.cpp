#include "TestScene.h"
#include"Engine/Image.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"


//コンストラクタ
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene"), hTitlePic_(-1)
{}

//初期化
void TestScene::Initialize()
{
	hTitlePic_ = Image::Load("tank_title.png");
	assert(hTitlePic_ >= 0);

	hTextPic_ = Image::Load("title_moji.png");
	assert(hTextPic_ >= 0);
}

//更新
void TestScene::Update()
{
	if (Input::IsKeyDown(DIK_P))
	{
		//シーンマネージャーを探して、シーン切り替えの関数を呼ぶ
		// 見つからない場合はnullptrが返るので、nullptrでないことを確認してから呼ぶ

		SceneManager* pSceneManager = (SceneManager*)(this->GetParent());
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
		//pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}
}

//描画
void TestScene::Draw()
{

	//transform_.position_ 描画位置
	//transform_.rotate_   描画向き
	//transform_.scale_    描画サイズ
	//transform_.scale_ = { 2.0f,2.0f,2.0f };      //画像サイズを二倍に

	Image::SetTransform(hTitlePic_, transform_); //画像の位置や向きなどを設定
	Image::Draw(hTitlePic_); //画像を描画

	Image::SetTransform(hTextPic_, transform_); //文字画像の位置や向きなどを設定
	Image::Draw(hTextPic_); //文字画像を描画
}

//開放
void TestScene::Release()
{}
