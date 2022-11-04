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

    void OnCollisionEnter(Collider* _pOther);
};

