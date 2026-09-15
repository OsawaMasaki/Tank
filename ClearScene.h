#pragma once
#include "Engine/GameObject.h"

class ClearScene :
	public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ClearScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

private:
	int hTitlePic_; //タイトル画像のハンドル
	int hTextPic_; //文字画像のハンドル
	int WIN_WIDTH = 1280;
	int WIN_HEIGHT = 720;
};

