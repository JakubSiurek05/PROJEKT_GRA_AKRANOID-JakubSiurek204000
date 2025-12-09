#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Paletka.h"
#include "Stone.h"
#include "Pilka.h"
#include <fstream>

struct BlockData
{
    float x, y;
    int hp;
};

class GameSave
{
public:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;

    float blockWidth = 0.f;
    float blockHeight = 0.f;

    std::vector<BlockData> blocks;

    void capture(const Paletka& m_paletka, const Pilka& m_pilka, const std::vector<Stone>& m_bloki)
    {
        paddlePosition = { m_paletka.getX(), m_paletka.getY() };
        ballPosition = { m_pilka.getX(), m_pilka.getY() };
        ballVelocity = { m_pilka.getVx(), m_pilka.getVy() };
        blocks.clear();
        blocks.reserve(m_bloki.size());

        if (!m_bloki.empty())
        {
            blockWidth = m_bloki[0].getSize().x;
            blockHeight = m_bloki[0].getSize().y;
        }

        for (const auto& s : m_bloki)
        {
            if (!s.isDestroyed())
            {
                blocks.push_back(BlockData{
                    s.getPosition().x,
                    s.getPosition().y,
                    s.getHP()
                    });
            }
        }
    }

    bool SaveToFile(const std::string& filename)
    {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        file << paddlePosition.x << " " << paddlePosition.y << "\n";
        file << ballPosition.x << " " << ballPosition.y << " "
            << ballVelocity.x << " " << ballVelocity.y << "\n";
        file << blockWidth << " " << blockHeight << "\n";
        file << blocks.size() << "\n";

        for (auto& b : blocks)
            file << b.x << " " << b.y << " " << b.hp << "\n";

        return true;
    }

    bool LoadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        file >> paddlePosition.x >> paddlePosition.y;
        file >> ballPosition.x >> ballPosition.y
            >> ballVelocity.x >> ballVelocity.y;
        file >> blockWidth >> blockHeight;
        size_t count;
        file >> count;
        blocks.resize(count);

        for (size_t i = 0; i < count; i++)
        {
            file >> blocks[i].x >> blocks[i].y >> blocks[i].hp;
        }

        return true;
    }
};
