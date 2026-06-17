#pragma once
#include "Engine/GameObject.h"

class TankHead:
    public GameObject
{
public:
    //コンストラクタ
    TankHead(GameObject* parent);
    ~TankHead();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
private:
    int hModel_;//地形モデルのハンドル
};