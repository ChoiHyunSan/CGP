#pragma once
#define SINGLE(type) public: \
						 static type* GetInst()\
						{ \
							static type mgr;\
							 return &mgr;\
						 } \
						private: \
							type(); \
							~type();

#define MAPSIZE 15
enum class DIR
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};

enum class GROUP_TYPE
{
	DEFAULT, // 0
	WALL,
	PLAYER,  
	ENEMY,
	BOMB,
	FIRE,

	END = 32,

};


enum class EFFECT_TYPE
{
	FIRE,
	FOG,
	WATER,

	END = 32
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,


	END,
};