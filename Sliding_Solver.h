#ifndef SLIDING_SOLVER_H
#define SLIDING_SOLVER_H

#include <string>
#include <queue>
#include <memory>
#include <iostream>
#include <vector>

#include "Board_Tile.h"

class Sliding_Solver {
public:
  //default constructor of sliding solver. Does nothing.
  Sliding_Solver(){};

  //constructor of a sliding solver that takes a string representing the starting configuration of the puzzle
  Sliding_Solver(std::string start): startingConfig{start} {};

  //function that sets the config of the solver
  void setConfig(std::string config) {startingConfig = config; }

  //function that solves the puzzle using A* Search
  //takes a string representing the goal configuration of the puzzle
  //returns a smart pointer to a Board_Tile, which is the final configuration of the puzzle
  std::shared_ptr<Board_Tile> Solve_Puzzle(const std::string& goalConfig);

private:

  //class that contains a comparator operator that is used to 'convert' a priority_queue into a minHeap
  class myComparator {
  public:
    bool operator() (const Board_Tile a, const Board_Tile b) const {
      return (a.numMoves() +  a.Manhattan_Distance(Board_Tile::goalConfig)) > (b.numMoves() + b.Manhattan_Distance(Board_Tile::goalConfig));
    }
  };

  //string representing the starting configuration of the puzzle
  std::string startingConfig = "";

  //priority_queue implementation of a minHeap
  std::priority_queue<Board_Tile, std::vector<Board_Tile>, myComparator> tileQueue;
};
#endif
