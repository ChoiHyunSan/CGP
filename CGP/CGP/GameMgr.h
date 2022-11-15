#pragma once
#include "pch.h"

class GameMgr
{
	SINGLE(GameMgr)

public:
	void	update();

public:
	int		getPlayerLife() const { return m_playerLife; }
	int		getPlayerPower() const { return m_playerPower; }
	void	setPlayerLife(int playerLife) { m_playerLife = playerLife; };

	int		getPlayTime() const { return m_playTime; }
	int		getPlayScore() const { return m_score; }
	void	AddScore() { m_score += 100; }
private:
	int		m_score;
	int		m_playTime;
	int		m_playerLife;
	int		m_playerPower;
	float	m_timer;

};

