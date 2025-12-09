#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#define MAX_LICZBA_POZIOMOW 3

class Menu
{
private:
    sf::Font font;
    sf::Text menu[MAX_LICZBA_POZIOMOW];
    int selectedItem = 0;

public:
    Menu(float width, float height);
    ~Menu() {};
    void przesunG();
    void przesunD();
    int getSelectedItem() { return selectedItem; }
    void draw(sf::RenderWindow& window);
};

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Nie mozna zaladowac czcionki arial.ttf!" << std::endl;
        return;
    }

    float baseY = height / (MAX_LICZBA_POZIOMOW + 1);

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Cyan);
    menu[0].setStyle(sf::Text::Bold);
    menu[0].setString("Nowa gra");
    menu[0].setPosition(sf::Vector2f(width / 3, baseY * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Wczytaj gre");
    menu[1].setPosition(sf::Vector2f(width / 3, baseY * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Wyjscie");
    menu[2].setPosition(sf::Vector2f(width / 3, baseY * 3));

}

void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::przesunG()
{
    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);

    selectedItem--;
    if (selectedItem < 0)
        selectedItem = MAX_LICZBA_POZIOMOW - 1;

    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}

void Menu::przesunD()
{
    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);

    selectedItem++;
    if (selectedItem >= MAX_LICZBA_POZIOMOW)
        selectedItem = 0;

    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}

void myDelay(int opoznienie)
{
    sf::Clock zegar;
    while (zegar.getElapsedTime().asMilliseconds() <= opoznienie) {}
}
