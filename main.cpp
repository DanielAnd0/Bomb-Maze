
#include <iostream>
#include "Player.h"
#include "Maze.h"

int main() {
    constexpr unsigned int screenWidth = 15;
    constexpr unsigned int screenHeight = 5;
    constexpr auto exit = sf::Vector2u(5, 14);
    Maze maze(screenWidth, screenHeight, exit);
    sf::RenderWindow window(sf::VideoMode({screenWidth*tiles::getsize().x, screenHeight*tiles::getsize().y}), "Game");
    Player player(1*tiles::getsize().x, 3*tiles::getsize().y );
    int speed=1;
    player.set_speed(speed);

    constexpr std::array tilesMatrix = { // 0-falseWall, 1-free path, 2-wall
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    };

    maze.loadtiles(tilesMatrix.data());
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::White);
        maze.drawMaze(window);
        if (maze.can_player_move(player) == false)
            player.doNotMove();
        player.Move();
        sf::sleep(sf::seconds(0.05/player.get_speed()));
        player.draw(window);
        sf::sleep(sf::seconds(0.05/player.get_speed()));
        window.display();
    }
}