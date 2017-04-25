// CustomizedMazeGenerator.cpp
//
// ICS 46 Spring 2015
// Project #1: Dark at the End of the Tunnel

#include "CustomizedMazeGenerator.hpp"
#include <ics46/factory/DynamicFactory.hpp>


ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, CustomizedMazeGenerator, "Customized Maze Generator (Required)");


CustomizedMazeGenerator::CustomizedMazeGenerator()
{
}


CustomizedMazeGenerator::~CustomizedMazeGenerator()
{
}


bool CustomizedMazeGenerator::isModified(int vec_c, int vec_r, Direction cur_dir)
{
    bool isVisited = false;
    if ((vec_r == 0 && cur_dir == Direction::up) 
        || (vec_r == heightOfMaze-1 && cur_dir == Direction::down) 
        || (vec_c == 0 && cur_dir == Direction::left) 
        || (vec_c == widthOfMaze-1 && cur_dir == Direction::right) 
        || (vectorOfMaze[getIndexFromPosition(vec_c, vec_r, cur_dir)] == "modified"))
    {
        isVisited = true;
    }
    return isVisited;
}


bool CustomizedMazeGenerator::allModified(int vec_c, int vec_r)
{
    for (int index = 0; index < 4; index++)
    {
        if (!isModified(vec_c, vec_r, dir_arr[index]))
        {
            return false;
        }
    }
    return true;
}


Direction CustomizedMazeGenerator::randomDirection()
{
	std::default_random_engine ran_eng{std::random_device{}()};
	std::uniform_int_distribution<int> int_dis{0, 3};
	return dir_arr[int_dis(ran_eng)];
}


int CustomizedMazeGenerator::getIndexFromPosition(int vec_c, int vec_r, Direction cur_dir)
{
    if (cur_dir == Direction::left)
    {
        indexOfVector = widthOfMaze * vec_r + (vec_c - 1);	
    }
    if (cur_dir == Direction::right)
    {
        indexOfVector = widthOfMaze * vec_r + (vec_c + 1);
    }
    if (cur_dir == Direction::up)
    {
        indexOfVector = widthOfMaze * (vec_r - 1) + vec_c;
    }
    if (cur_dir == Direction::down)
    {
        indexOfVector = widthOfMaze * (vec_r + 1) + vec_c; 
    }
    return indexOfVector;
}


void CustomizedMazeGenerator::generateMaze(Maze& maze)
{
    heightOfMaze = maze.getHeight();
    widthOfMaze = maze.getWidth();
    sizeOfMaze = heightOfMaze * widthOfMaze;
    vectorOfMaze = std::vector<std::string>(sizeOfMaze, "unmodified");
    vectorOfMaze[0] = "modified";
    maze.removeAllWalls();
    maze.addAllWalls();
    recursiveForGenerateMaze(maze, 0, 0);
}


void CustomizedMazeGenerator::recursiveForGenerateMaze(Maze& maze, int vec_c, int vec_r)
{
    while(!allModified(vec_c, vec_r))
    {
	Direction cur_dir = randomDirection();
	if (!isModified(vec_c, vec_r, cur_dir))
	{
            if (maze.wallExists(vec_c, vec_r, cur_dir))
            {
	        maze.removeWall(vec_c, vec_r, cur_dir);
	        indexOfVector = getIndexFromPosition(vec_c, vec_r, cur_dir);
	        vectorOfMaze[indexOfVector] = "modified";
                int colOfMaze = indexOfVector % widthOfMaze;
                int rowOfMaze = indexOfVector / widthOfMaze;
	        recursiveForGenerateMaze(maze, colOfMaze, rowOfMaze);
            }
	}
    }
}