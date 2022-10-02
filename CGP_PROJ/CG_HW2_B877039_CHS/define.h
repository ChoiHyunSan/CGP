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

enum class GROUP_TYPE
{
	DEFAULT, // 0
	PLAYER,  // 1
	MISSILE, // 2
	MONSTER, // 3



	END = 32,

};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};