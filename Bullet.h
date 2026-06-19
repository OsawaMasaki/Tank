#pragma once
#include "Engine/GameObject.h"

class Bullet :
    public GameObject
{
public:
    //コンストラクタ
    Bullet(GameObject* parent);
    ~Bullet() {};
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void SetMoveVector(XMFLOAT3 move) { move_ = move; }
private:
    int hModel_;   //地形モデルのハンドル
    XMFLOAT3 move_; //弾の進行方向
};

