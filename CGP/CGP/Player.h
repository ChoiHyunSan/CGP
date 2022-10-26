#pragma once
#include "modelclass.h"
class Player :
    public ModelClass
{


public:
    Player(ID3D11Device*);
    ~Player();

public:
    virtual void Update();

};

