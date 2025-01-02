#pragma once
#include <SFML/System/Vector2.hpp>
struct AABB {
  // min -> describes the top left corner (smallest values from the coordinates)
  // max -> describes the bottom right corner (largerst values from the
  // coordinates)
  float _minX = 0, _maxX = 0;
  float _minY = 0, _maxY = 0;
  // constructor initialiser list
  AABB(float minX, float maxX, float minY, float maxY)
      : _minX(minX), _maxX(maxX), _minY(minY), _maxY(maxY) {}
  /*sf::Vector2f getMin() { return sf::Vector2f(_minX, _minY); }*/
  /*sf::Vector2f getMax() { return sf::Vector2f(_maxX, _maxY); }*/
  bool checkCollision(const AABB &otherBox) const {
    if (_maxX <= otherBox._minX || _minX >= otherBox._maxX) {
      /*std::cout << "Box Collision " << __LINE__ << std::endl;*/
      return false;
    }
    if (_maxY <= otherBox._minY || _minY >= otherBox._maxY) {
      /*std::cout << "Box Collision " << __LINE__ << std::endl;*/
      return false;
    }
    return true;
  }
};
