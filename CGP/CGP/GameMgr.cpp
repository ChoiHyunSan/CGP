#include "GameMgr.h"
#include "pch.h"
#include "TimeMgr.h"
GameMgr::GameMgr():
	m_score(0),
	m_playTime(100),
	m_playerLife(0),
	m_playerPower(2),
	m_timer(0)
{

}

GameMgr::~GameMgr()
{

}

void GameMgr::update()
{
	// GameTimer µ¹¸®±â
	if (m_timer >= 1.f)
	{
		m_playTime -= 1;
		m_timer = 0.f;
	}
	else
		m_timer += fDT;
}