#pragma once

#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape
{
	int m_pktZycia;
	bool m_jestZniszczony;
	static const std::array<sf::Color, 4> m_colorLUT;

public:
	Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L)
	{
		m_pktZycia = L;
		m_jestZniszczony = false;
		setSize(rozmiar);
		this->setPosition(startPos);
		setOutlineThickness(2.f);
		aktualizujKolor();
	}

	void aktualizujKolor()
	{
		if (m_pktZycia >= 0 && m_pktZycia < m_colorLUT.size())
		{
			this->setFillColor(m_colorLUT[m_pktZycia]);
		}
	}

	bool isDestroyed() const { return m_jestZniszczony; }

	void draw(sf::RenderTarget& target) const
	{
		if (m_jestZniszczony == false)
		{
			target.draw(*this);
		}
	}

	void trafienie()
	{
		if (m_jestZniszczony == true)
			return;

		m_pktZycia -= 1;
		aktualizujKolor();

		if (m_pktZycia <= 0)
			m_jestZniszczony = true;

	}

	int getHP() const { return m_pktZycia; }
	sf::Vector2f getPosition() const { return sf::RectangleShape::getPosition(); }
	sf::Vector2f getSize() const { return sf::RectangleShape::getSize(); }
};