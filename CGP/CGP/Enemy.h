#pragma once
#include "modelclass.h"
class Enemy :
    public ModelClass
{

private:
    bool isMove;        // 이동중인가
    Pos  targetPos;     // 이동하는 위치 

public:
    void Update();


private:
    void setTargetPos(DIR dir);
    void Move();

public:
    Enemy(ID3D11Device* device);
    ~Enemy();
};



// path finder
// A* algorithm



