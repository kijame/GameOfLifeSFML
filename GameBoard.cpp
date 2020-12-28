#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include "GameBoard.h"

GameBoard::GameBoard()
{
  boardState = std::vector<std::vector<sf::RectangleShape>>(60, std::vector<sf::RectangleShape>(80, sf::RectangleShape(sf::Vector2f(11, 11))));
  for (int i = 0; i < height / 10; i++)
  {
    for (int j = 0; j < width / 10; j++)
    {
      boardState[i][j].setFillColor(sf::Color(120, 120, 120));
      boardState[i][j].setOutlineThickness(-1.f);
      boardState[i][j].setOutlineColor(sf::Color::Black);
      boardState[i][j].setPosition(j * 10, i * 10);
    }
  }
}

void GameBoard::click(int x, int y)
{
  //boardState[x / 10][y / 10].setFillColor(sf::Color(255, 0, 0));
  auto hold = alive.find({x / 10, y / 10});
  if(hold != alive.end()){
    alive.erase(hold);
  }else{
    alive.insert({x / 10, y / 10});
  }
}

std::vector<std::vector<sf::RectangleShape>> *GameBoard::getState()
{
  return &boardState;
}

void GameBoard::reset()
{
  alive.clear();
}

// todo keep the active squares as a set and draw them over the background squares
// will have quicker calculations
// really should store the game state as bool array and draw it seperately
// 120,120,120 = grey im using
// could probably erase off screen cells
void GameBoard::iterate()
{
  int neighbors;
  std::vector<std::pair<int, int>> n;
  std::set<std::pair<int, int>> temp;
  // check alive squares
  std::cout << "Alive\n";
  for (auto i : alive)
  {
    std::cout << i.first << " " << i.second << std::endl;
    neighbors = 0;
    for (int x = -1; x <= 1; x++)
    {
      for (int y = -1; y <= 1; y++)
      {
        if ((x != 0 || y != 0) && alive.find({i.first + x, i.second + y}) != alive.end())
          neighbors++;
        // if its a neighbor whos unactivated its a target
        else if (x != 0 || y != 0)
          n.push_back({i.first + x, i.second + y});
      }
    }
    if (neighbors == 2 || neighbors == 3)
      temp.insert(i);
  }
  std::cout << "Neighbors of alive\n";
  // check neighbors of alive squares
  for (auto i : n)
  {
    std::cout << i.first << " " << i.second << std::endl;
    neighbors = 0;
    for (int x = -1; x <= 1; x++)
    {
      for (int y = -1; y <= 1; y++)
      {
        if ((x != 0 || y != 0) && alive.find({i.first + x, i.second + y}) != alive.end())
          neighbors++;
      }
    }
    if (neighbors == 3)
    {
      temp.insert(i);
    }
  }
  // "return" correct state
  alive = temp;
}

void GameBoard::draw(sf::RenderWindow *window)
{
  for (auto i : boardState)
  {
    for (auto j : i)
    {
      (*window).draw(j);
    }
  }
  for (auto i : alive)
  {
    sf::RectangleShape temp(sf::Vector2f(11, 11));
    temp.setPosition(i.second * 10, i.first * 10);
    temp.setFillColor(sf::Color(255, 0, 0));
    temp.setOutlineThickness(-1.f);
    temp.setOutlineColor(sf::Color::Black);
    (*window).draw(temp);
  }
}

/*/ dead square
          if(boardState[i][j].getFillColor() == sf::Color(122,122,122)){
            // if 3 neighbors are alive

          // live square
          }else{

          }
          */
