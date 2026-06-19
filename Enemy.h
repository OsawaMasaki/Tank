#pragma once
#include "Engine/GameObject.h"

class Enemy :
    public GameObject
{
public:
    //コンストラクタ
    Enemy(GameObject* parent);
    ~Enemy() {};
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget);
private:
    int hModel_;   //地形モデルのハンドル
    int count_;
};

