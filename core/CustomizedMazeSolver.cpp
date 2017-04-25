// CustomizedMazeSolver.cpp
//
// ICS 46 Spring 2015
// Project #1: Dark at the End of Tunnel

#include "CustomizedMazeSolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>


ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, CustomizedMazeSolver, "Customized Maze Solver (Required)");


CustomizedMazeSolver::CustomizedMazeSolver()
{
}


CustomizedMazeSolver::~CustomizedMazeSolver()
{	
}


bool CustomizedMazeSolver::isDeadEnd(const Maze& maze, MazeSolution& mazeSolution, Direction cur_dir)
{
    bool isBlocked = false;
    std::pair<int, int> cur_pos = mazeSolution.getCurrentCell();
    int vec_c = cur_pos.first;
    int vec_r = cur_pos.second;
    if(maze.wallExists(vec_c, vec_r, cur_dir) 
        || (vec_r == 0 && cur_dir == Direction::up) 
        || (vec_r == heightOfMaze-1 && cur_dir == Direction::down) 
        || (vec_c == 0 && cur_dir == Direction::left) 
        || (vec_c == widthOfMaze-1 && cur_dir == Direction::right) 
        || (vectorOfMaze[getIndexFromPosition(vec_c, vec_r, cur_dir)] == "visited"))
    { 
        isBlocked = true;
    }
    return isBlocked;
}


int CustomizedMazeSolver::getIndexFromPosition(int vec_c, int vec_r)
{
    return widthOfMaze * vec_r + vec_c;
}


int CustomizedMazeSolver::getIndexFromPosition(int vec_c, int vec_r, Direction cur_dir)
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


void CustomizedMazeSolver::recursiveForSolveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    std::pair<int,int> cur_pos = mazeSolution.getCurrentCell();
    int vec_c = cur_pos.first;
    int vec_r = cur_pos.second;
    vectorOfMaze[getIndexFromPosition(vec_c, vec_r)] = "visited";
    for(int index = 0; index < 4; index++)
    {
        if(!isDeadEnd(maze, mazeSolution, precedences[index]) && !mazeSolution.isComplete())
        {
            mazeSolution.extend(precedences[index]);
            recursiveForSolveMaze(maze, mazeSolution);
        }
    }
    if (!mazeSolution.isComplete())
    {
        mazeSolution.backUp();
    }
};


void CustomizedMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    mazeSolution.restart();
    heightOfMaze = maze.getHeight();
    widthOfMaze = maze.getWidth();
    sizeOfMaze = heightOfMaze * widthOfMaze;
    vectorOfMaze = std::vector<std::string>(sizeOfMaze, "unvisited");
    recursiveForSolveMaze(maze, mazeSolution);
};