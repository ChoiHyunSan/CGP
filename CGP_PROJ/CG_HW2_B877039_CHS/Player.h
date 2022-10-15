#pragma once
#include "modelclass.h"
class Player :
    public ModelClass
{


public:
    Player(ID3D11Device*, const WCHAR*, const WCHAR*);
    ~Player();

public:
    virtual void Update();

};

