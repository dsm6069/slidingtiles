#include <unordered_set>
#include <list>

#include "Sliding_Solver.h"
#include "directions.h"

std::shared_ptr<Board_Tile> Sliding_Solver::Solve_Puzzle(const std::string& goalConfig) {
		Board_Tile::goalConfig = goalConfig; //initialise the static Board_Tile member as the goalConfig
		Board_Tile currentBoardTile, currentNeighbour;
		std::unordered_set<std::string> visited; //a set of the already visited configurations
		std::shared_ptr<Board_Tile> solution; //a pointer to the most recent currentBoardTile, if there is a solution
		//this will be returned
		std::list<Board_Tile> neighbours; //list of neighbours of the currentBoardTile

		//initialise the currentBoardTile and the queue before starting the Algorithm
		currentBoardTile.setConfig(startingConfig);
		tileQueue.push(currentBoardTile);
		solution = std::make_shared<Board_Tile>(currentBoardTile);

		//if our starting config is our goal, we don't need to do anything
		if (startingConfig == goalConfig)
			return solution;

		//iterate through the queue until there's nothing in it
		while (tileQueue.size())
		{
			//the tile is updated at the end of the loop, so we can pop that from the queue
			tileQueue.pop();
			//if we have found the goalConfiguration, we can return the solution
			if (currentBoardTile.getConfig() == goalConfig)
				return solution;
			//insert the current configuration so we can later check if a configuration has been visited before
			visited.insert(currentBoardTile.getConfig());
			//get all the possible configurations, max four, minimum two
			neighbours = currentBoardTile.nextConfigs();
			//iterate through all the next configs
			for (unsigned int i = 0; i < 4; i++)
			{
				//if no more configs, we can break
				if(neighbours.empty())
					break;
				//look at the next neighbour
				currentNeighbour = neighbours.front();
				neighbours.pop_front();
				//if it is visited, we can skip it
				if (visited.count(currentNeighbour.getConfig())) {
					continue;
				}
				//push it to the queue, this will only happen if the config hasn't been visited yet.
				tileQueue.push(currentNeighbour);
			}
			//update the current tilcurrentBoardTile
			currentBoardTile = tileQueue.top();

			//a pointer the the most recent tile; will be returned if the goal config is found.
			//its data members contain the number of moves taken to get to that configuration
			//and the moves taken to get to it as well
			solution = std::make_shared<Board_Tile>(currentBoardTile);
		}
		//if there is no solution, the queue will eventually be empty and the loop will break,
		//thus we return that there is NO SOLUTION
		return std::make_shared<Board_Tile>(Board_Tile("NO SOLUTION"));
}
