#pragma once
#include "pch.h"

class GameMgr
{
	SINGLE(GameMgr)

public:
	void	update();

public:
	int		getPlayerLife() const { return m_playerLife; }
	void	setPlayerLife(int playerLife) { m_playerLife = playerLife; };

	int		getPlayTime() const { return m_playTime; }

private:
	int		m_score;
	int		m_playTime;
	int		m_playerLife;
	int		m_playerPower;

};

