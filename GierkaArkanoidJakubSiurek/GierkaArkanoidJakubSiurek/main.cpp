#include <SFML/Graphics.hpp>
#include <iostream>
#include "Stone.h"
#include "Pilka.h"
#include "Paletka.h"
#include "Game.h"
#include "Menu.h"
#include "GameSave.h"

int main()
{
    enum class GameState { Menu, Playing, Scored, Exiting, GameOver };

    sf::Clock clock;
    sf::Clock gameOverClock;
    sf::RenderWindow m_window(sf::VideoMode(WIDTH, HEIGHT), "GRA ARKANOID!");

    Menu menu(m_window.getSize().x, m_window.getSize().y);
    Game game;
    GameSave save; 
    GameState currentState = GameState::Menu;
    m_window.setFramerateLimit(90);

    while (m_window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Event event;

       
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::F5) {
                    std::cout << "Nacisnieto F5. Aktualny stan: " << (int)currentState << std::endl;
                }
                
                if (event.key.code == sf::Keyboard::F5 && currentState == GameState::Playing)
                {
                    save.capture(game.getPaletka(), game.getPilka(), game.getBloki());
                    if (save.SaveToFile("wyniki.txt")) 
                    { 
                        std::cout << "===GRA ZAPISANA===!" << std::endl;
                    }
                }

                if (event.key.code == sf::Keyboard::F9 && currentState == GameState::Menu)
                {
                    if (save.LoadFromFile("wyniki.txt"))
                    {
                        std::cout << "WCZYTANO GRE" << std::endl;
                        game.applySave(save);
                        currentState = GameState::Playing;
                    }
                }

                if (event.key.code == sf::Keyboard::Escape && currentState == GameState::Playing) {
                    currentState = GameState::Menu;
                }

                if (currentState == GameState::Menu)
                {
                    if (event.key.code == sf::Keyboard::Up) {
                        menu.przesunG();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        menu.przesunD();
                    }
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        switch (menu.getSelectedItem())
                        {
                        case 0: 
                            std::cout << "===GRA URUCHOMIONA===" << std::endl;
                            currentState = GameState::Playing;
                            break;

                        case 1: 
                            if (save.LoadFromFile("wyniki.txt"))
                            {
                                std::cout << "===WCZYTANO GRE===" << std::endl;
                                game.applySave(save);
                                currentState = GameState::Playing;
                            } 
                            break;

                        case 2: 
                            std::cout << "===KONIEC GRY===" << std::endl;
                            m_window.close();
                            break;
                        }

                    }
                }
            }
        } 

        
        if (currentState == GameState::Playing)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
            {
                game.moveLeft();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
            {
                game.moveRight();
            }
            game.update(dt);

            if (game.EndGame())
            {
                currentState = GameState::GameOver;
                gameOverClock.restart();
            }
        }
        m_window.clear();

        if (currentState == GameState::Menu) 
        {
            menu.draw(m_window);
        }
        else if (currentState == GameState::Playing) 
        {
            game.render(m_window);
        }

        else if (currentState == GameState::GameOver)
        {
            sf::Font font;
            font.loadFromFile("arial.ttf");   

            sf::Text koniec;
            koniec.setFont(font);
            koniec.setString("KONIEC GRY");
            koniec.setCharacterSize(60);
            koniec.setFillColor(sf::Color::Red);
            koniec.setPosition(WIDTH / 2.f - 150, HEIGHT / 2.f - 50);

            m_window.draw(koniec);

            
            if (gameOverClock.getElapsedTime().asSeconds() >= 2.f)
            {
                currentState = GameState::Menu;    
                game = Game();
            }
        }


        m_window.display();
    }

    return 0;
}