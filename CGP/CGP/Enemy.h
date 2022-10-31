#pragma once
#include "modelclass.h"
class Enemy :
    public ModelClass
{

private:
    bool isMove;        // �̵����ΰ�
    Pos  targetPos;     // �̵��ϴ� ��ġ 

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


