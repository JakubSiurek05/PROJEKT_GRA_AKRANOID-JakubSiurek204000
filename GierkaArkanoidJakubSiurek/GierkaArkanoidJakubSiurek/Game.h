#pragma once

#include <vector> 
#include "Paletka.h"
#include "Stone.h"
#include "Pilka.h"
#include "GameSave.h"
#ifndef WIDTH
const unsigned int WIDTH = 640;
const unsigned int HEIGHT = 480;
#endif

class Game
{
	sf::Clock m_deltaClock;
	Paletka m_paletka;
	Pilka m_pilka;
	std::vector<Stone> m_bloki;

public:
	Game() :
		m_paletka(320.f, 440.f, 100.f, 20.f, 8.f),
		m_pilka(320.f, 400.f, 4.f, 3.f, 8.f),
		m_bloki()
	{
		const int KOLUMNY = 6;
		const int WIERSZE = 7;
		const float BLOK_Y = 25.f;
		const float BLOK_X = (WIDTH - (KOLUMNY - 1) * 2.f) / KOLUMNY;

		for (int y = 0; y < WIERSZE; y++)
		{
			for (int x = 0; x < KOLUMNY; x++)
			{
				float posX = x * (BLOK_X + 2.f);
				float posY = 50.f + y * (BLOK_Y + 2.f);
				int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

				m_bloki.emplace_back(
					sf::Vector2f(posX, posY),
					sf::Vector2f(BLOK_X, BLOK_Y),
					L
				);
			}
		}
	}

	void update(sf::Time dt)
	{
		m_paletka.clampToBounds(WIDTH);
		m_pilka.move();
		m_pilka.collideWalls(WIDTH, HEIGHT);
		m_pilka.collidePaddle(m_paletka);
		m_pilka.collideStone(m_bloki);
	}

	void render(sf::RenderTarget& target)
	{
		m_paletka.draw(target);
		m_pilka.draw(target);
		for (auto& blok : m_bloki) blok.draw(target);
	}

	void moveRight()
	{
		m_paletka.moveRight();
	}

	void moveLeft()
	{
		m_paletka.moveLeft();
	}

	void applySave(const GameSave& save)
	{
		m_paletka.setPosition(save.paddlePosition);
		m_pilka.setPosition(save.ballPosition);
		m_pilka.setVelocity(save.ballVelocity.x, save.ballVelocity.y);
		m_bloki.clear();
		for (const auto& b : save.blocks)
		{
			m_bloki.emplace_back(
				sf::Vector2f(b.x, b.y),
				sf::Vector2f(save.blockWidth, save.blockHeight),
				b.hp
			);
		}
	}

	bool EndGame() const
	{
		if (m_pilka.getY() > HEIGHT)
		{
			return true;
		}

		bool allDestroyed = true;

		for (const auto& blok : m_bloki)
		{
			if (!blok.isDestroyed())
			{
				allDestroyed = false;
				break;
			}
		}

		if (allDestroyed)
			return true;

		return false;

	}

	Paletka& getPaletka() { return m_paletka; }
	Pilka& getPilka() { return m_pilka; }
	std::vector<Stone>& getBloki() { return m_bloki; }
};