#pragma once
#include "define.h"
#include <vector>
#include <string>
#include "d3dclass.h"
#include "struct.h"

using namespace std;
using std::vector;

#define BOXSCALE 1
#define fDT TimeMgr::GetInst()->GetfDT()

struct Pos
{
	float x;
	float y;
	float z;
};