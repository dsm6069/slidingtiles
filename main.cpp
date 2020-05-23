#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_set>
#include <cstdlib>
#include <limits>
#include <iomanip>

#include "Board_Tile.h"
#include "directions.h"
#include "Sliding_Solver.h"

//function that displays the menu and takes puzzle input
//returns all of the goal and inital configurations recieved from the user.
//(only pairs of strings are stored, if the user only inputs an initial config
//and then ends the stream, that config is not pushed to the vector)
std::vector<std::string> menu();

//function that takes a string and tests if it is a proper puzzle
bool screenString(std::string);

int main() {
  std::string moves = "";
  std::shared_ptr<Board_Tile> solution;
  std::vector<std::string> configurations;
  configurations = menu();
  std::cout << std::setw(20) << std::left << std::setfill(' ') << "Start Board";
  std::cout << std::setw(20) << std::left << std::setfill(' ') << "Goal Board";
  std::cout << std::setw(20) << std::left << std::setfill(' ') << "Number Of Moves";
  std::cout << std::setw(20) << std::left << std::setfill(' ') << "Solution" << std::endl;
  for(unsigned int i = 0; i < configurations.size(); i += 2) {
    Sliding_Solver solver(configurations[i]);
    solution = solver.Solve_Puzzle(configurations[i + 1]);
    std::cout << std::setw(20) << std::left << std::setfill(' ') << configurations[i];
    std::cout << std::setw(20) << std::left << std::setfill(' ') << configurations[i + 1];
    if(solution->getConfig() != "NO SOLUTION") {
      std::cout << std::setw(20) << std::left << std::setfill(' ') << solution->numMoves();
      std::cout << std::setw(20) << std::left << std::setfill(' ') << solution->getDirection() << std::endl;
    } else
      std::cout << std::setw(20) << std::left << std::setfill(' ') << "NO SOLUTION" << std::endl;
  }


  std::cin.clear();
  std::cin.ignore(std::numeric_limits<int>::max(), '\n');
  std::cin.get();
  return 0;
}

std::vector<std::string> menu() {
  std::string initial, goal;
  int i = 1;
  std::vector<std::string> configurations;
  std::cout << "Enter each puzzle you would like to test in a nine digit string, \n";
  std::cout << "Followed by, on the next line the configuration you would like to end with.\n";
  std::cout << "For example:\n";
  std::cout << ">132475680\n";
  std::cout << ">123456780\n";
  std::cout << "Enter 'END' at any time to end input and see the solutions to the puzzles.\n";
  while(1) {
      std::cout << "Initial Configuration " << i << ": ";
      std::cin >> initial;
      std::cout << '\n';
      if(initial == "END")
        return configurations;
      else if(!screenString(initial)) {
        std::cout << "Please input a valid puzzle configuration of 9 distinct integers\n";
        continue;
      }
      while(1) {
        std::cout << "Goal Configuration " << i << ": ";
        std::cin >> goal;
        std::cout << '\n';
        if(goal == "END")
          return configurations;
        else if(!screenString(goal)) {
            std::cout << "Please input a valid puzzle configuration of 9 distinct integers\n";
            continue;
        }
        ++i;
        break;
      }
    configurations.push_back(initial);
    configurations.push_back(goal);
  }
  return configurations;
}

bool screenString(std::string config) {
  std::unordered_set<char> integers;
  std::string temp = "";
  bool ret = true, isAlpha = false, sizeError = false, alphaError = false, duplicateError = false;
  for(unsigned int i = 0; i < config.size(); ++i) {
    if(!sizeError && config.size() != 9) {
      std::cout << "ERROR: Config is not 9 digits long" << std::endl;
      ret = false;
      sizeError = true;
    }
    if(std::isalpha(config[i])) {
      if(!alphaError)
        std::cout << "ERROR: Config includes alphas" << std::endl;
      alphaError = true;
      isAlpha = true;
      ret = false;
    } else
      isAlpha = false;
    temp = config[i];
    if(!isAlpha && (std::stoi(temp) < 0 || std::stoi(temp) > 8)) {
      std::cout << "ERROR: Some numbers in this config are out of range." << std::endl;
      ret = false;
    }
    if(!duplicateError && integers.count(config[i])) {
      std::cout << "ERROR: There are duplicate numbers in this config" << std::endl;
      duplicateError = true;
      ret = false;
    }
    integers.insert(config[i]);
  }
  return ret;
}
