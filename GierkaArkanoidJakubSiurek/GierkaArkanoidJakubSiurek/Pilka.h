#pragma once

#include <SFML/Graphics.hpp>
#include "Paletka.h"
#include "Stone.h"

class Pilka
{
	float x, y;
	float vx, vy;
	float r;
	sf::CircleShape shape;

public:
	Pilka(float x, float y, float vx, float vy, float r) :
		x(x), y(y), vx(vx), vy(vy), r(r)
	{
		shape.setRadius(r);
		shape.setOrigin(r, r);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::White);
	}

	void setPosition(const sf::Vector2f& pos)
	{
		shape.setPosition(pos);
	}

	void setVelocity(float vx, float vy)
	{
		vx = vx;
		vy = vy;
	}

	void move()
	{
		x += vx;
		y += vy;
		shape.setPosition(x, y);
	};

	void bounceX() { vx = -vx; };
	void bounceY() { vy = -vy; };

	void collideWalls(float width, float height)
	{
		if (x - r <= 0)
		{
			bounceX();
			x = r;
		}
		else if (x + r > width)
		{
			bounceX();
			x = width - r;
		}
		if (y - r <= 0)
		{
			bounceY();
			y = r;
		}
		
	}


	bool collidePaddle(const Paletka& p)
	{
		float p_left = p.getX() - p.getSzerokosc() / 2.f;
		float p_right = p.getX() + p.getSzerokosc() / 2.f;
		float p_top = p.getY() - p.getWysokosc() / 2.f;

		bool isOverPaddle = (x + r > p_left) && (x - r < p_right);
		bool hitTopEdge = (y + r >= p_top) && (vy > 0);

		if (isOverPaddle && hitTopEdge)
		{
			bounceY();
			y = p_top - r;
			shape.setPosition(x, y);
			return true;
		}
		return false;
	};

	bool collideStone(Stone& blok)
	{
		if (blok.isDestroyed())
			return false;


		if (shape.getGlobalBounds().intersects(blok.getGlobalBounds()))
		{

			blok.trafienie();

			sf::FloatRect b = blok.getGlobalBounds();

			if (x < b.left || x > b.left + b.width)
				bounceX();
			else
				bounceY();

			return true;
		}
		return false;
	}
	void collideStone(std::vector<Stone>& bloki)
	{
		for (auto& blok : bloki)
		{
			if (collideStone(blok))
				break;
		}
	};


	void draw(sf::RenderTarget& target) { target.draw(shape); };

	float getX() const { return x; }
	float getY() const { return y; }
	float getVx() const { return vx; }
	float getVy() const { return vy; }
	float getRadius() const { return r; }

};

