#pragma once
#include "modelclass.h"
class Player :
    public ModelClass
{


public:
    Player(ID3D11Device*, GROUP_TYPE type);
    ~Player();

public:
    virtual void Update();

};

