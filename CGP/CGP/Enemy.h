#pragma once
#include "modelclass.h"
class Enemy :
    public ModelClass
{
    

public:
    void Update();

public:
    Enemy(ID3D11Device* device, GROUP_TYPE type);
    ~Enemy();
};



// path finder
// A* algorithm



