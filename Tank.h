#pragma once
#include "Engine/GameObject.h"

class Tank :
    public GameObject
{
public:
    //コンストラクタ
    Tank(GameObject* parent);
    ~Tank();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
private:
    int hModel_;//地形モデルのハンドル
    int camType_;//カメラのタイプ
};

