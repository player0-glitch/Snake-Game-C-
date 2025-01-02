#include "../include/game.h"
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
// Snake game will be designed as a grid layout
// this makes movements very very easy
int main() {
  srand(time(nullptr));
  sf::Clock clock;
  sf::Int32 elapsedTime = 0;
  sf::ContextSettings setting;
  setting.antialiasingLevel = 8;
  sf::RenderWindow window(
      sf::VideoMode(CELL_SIZE * CELL_COUNT, CELL_COUNT * CELL_SIZE),
      "Snake-Xenga");
  window.setFramerateLimit(30);
  Game game(CELL_SIZE * CELL_COUNT, CELL_COUNT * CELL_SIZE);
  while (window.isOpen()) {
    sf::Time deltaTime = clock.restart();

    // event listeners
    sf::Event e;
    while (window.pollEvent(e)) {
      // Event handling
      switch (e.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        // controls handling
        switch (e.key.code) {
        case sf::Keyboard::Up:
          game.setDirection(DIRECTION::UP);
          /*game.move();*/
          break;
        case sf::Keyboard::Down:
          game.setDirection(DIRECTION::DOWN);
          /*game.move();*/
          break;
        case sf::Keyboard::Left:
          game.setDirection(DIRECTION::LEFT);
          /*game.move();*/
          break;
        case sf::Keyboard::Right:
          game.setDirection(DIRECTION::RIGHT);
          /*game.move();*/
          break;
        case sf::Keyboard::Escape:
          window.close();
          break;
        default:
          break;
        }
      default:
        break;
      }
    }
    // drawing happens in this sections

    window.clear(GREEN);
    window.draw(game.getFood());
    elapsedTime += deltaTime.asMilliseconds();
    game.run(elapsedTime);
    // drawing the Snake
    for (sf::RectangleShape s : game.getSnake())
      window.draw(s);

    window.display();
  }
  return 0;
}
