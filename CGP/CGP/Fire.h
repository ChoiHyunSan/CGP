#pragma once
#include "EffectClass.h"
#include "pch.h"

class Fire :
    public EffectClass
{
    float timer;

public:
    virtual void update();

public:
    Fire(ID3D11Device* device);
    ~Fire();
};

