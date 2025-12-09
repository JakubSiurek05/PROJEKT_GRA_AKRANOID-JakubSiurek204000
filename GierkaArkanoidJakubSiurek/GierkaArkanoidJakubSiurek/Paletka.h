#pragma once
#include <SFML/Graphics.hpp>

class Paletka
{
	float x, y;
	float szerokosc, wysokosc;
	float predkosc;
	sf::RectangleShape shape;

public:
	Paletka(float x, float y, float szerokosc, float wysokosc, float predkosc) :
		x(x), y(y), szerokosc(szerokosc), wysokosc(wysokosc), predkosc(predkosc)
	{
		shape.setSize({ szerokosc, wysokosc });
		shape.setOrigin(szerokosc / 2, wysokosc / 2);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color(0, 0, 255));
	}

	void setPosition(const sf::Vector2f& pos)
	{
		shape.setPosition(pos);
	}

	void moveLeft()
	{
		x -= predkosc;
		shape.setPosition(x, y);
	};

	void moveRight()
	{
		x += predkosc;
		shape.setPosition(x, y);
	};

	void clampToBounds(float width)
	{
		if (x - szerokosc / 2 <= 0)
		{
			x = szerokosc / 2.f;
		}
		else if (x + szerokosc / 2 >= width)
		{
			x = width - szerokosc / 2.f;
		}
		shape.setPosition(x, y);
	};

	void draw(sf::RenderTarget& target) { target.draw(shape); };

	float getX() const { return x; }
	float getY() const { return y; }
	float getSzerokosc() const { return szerokosc; }
	float getWysokosc() const { return wysokosc; }
};