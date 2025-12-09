
#include <iostream>

#include "Exceptions.h"
#include "Player.h"
#include "Maze.h"

int main() {
    try {
        Enemies::loadTexture();
        tiles::loadTexture();
        Player::loadTexture();
        Bomb::loadTexture();

        constexpr unsigned int screenWidth = 15;
        constexpr unsigned int screenHeight = 10;

        const auto exit = sf::Vector2f(14.5f*static_cast<float>(tiles::getsize().x), 3.5f*static_cast<float>(tiles::getsize().y));

        Maze maze(screenWidth, screenHeight, exit);
        sf::RenderWindow window(sf::VideoMode({screenWidth*tiles::getsize().x, screenHeight*tiles::getsize().y}), "Game");
        window.setSize({800,400});
        Player player(0.9f*static_cast<float>(tiles::getsize().x), 2.f*static_cast<float>(tiles::getsize().y));
        constexpr float speed=32.f;
        player.set_speed(speed);

        constexpr std::array loadMaze = { // 0-falseWall, 1-free path, 2-wall, 3-exit
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
            2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2,
            2, 2, 2, 2, 2, 0, 2, 2, 1, 1, 1, 2, 2, 1, 2,
            2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 1, 2,
            2, 2, 2, 2, 2, 0, 2, 2, 1, 2, 2, 2, 2, 1, 2,
            2, 2, 2, 2, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,

        };
        maze.load(loadMaze.data());
        maze.add_enemy(10.f*static_cast<float>(tiles::getsize().x), 3.f*static_cast<float>(tiles::getsize().y));

        sf::Clock clock;
        while (window.isOpen() && !player.getHitBox().contains(maze.get_exit()) && player.get_life_status()){
            float deltaTime = clock.restart().asSeconds();
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }
            window.clear(sf::Color::White);
            maze.drawMaze(window);
            player.Update(deltaTime);
            if (sf::FloatRect hitBox = player.getHitBox(); maze.check_for_colisions(hitBox)){
                player.change_position(player.get_direction(), -player.get_speed()*deltaTime);
            }
            maze.Update(player, deltaTime);
            player.draw(window);
            window.display();
        }
    }catch (const NotInMaze& error) {
        std::cout<<"ERROR: "<< error.what()<<'\n';
    }catch (const InvalidTileNumber& error) {
        std::cout<<"ERROR: "<< error.what()<<'\n';
    }catch (const FileLoadFail& error) {
        std::cout<<"ERROR: "<<error.what()<<'\n';
    }
}