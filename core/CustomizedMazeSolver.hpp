// CustomizedMazeSolver.hpp
//
// ICS 46 Spring 2015
// Project #1: Dark at the End of the Tunnel

#ifndef	CUSTOMIZEDMAZESOLVER_HPP
#define CUSTOMIZEDMAZESOLVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Direction.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include "MazeSolver.hpp"


class CustomizedMazeSolver : public MazeSolver
{
public:
    CustomizedMazeSolver();
    ~CustomizedMazeSolver();

    bool isDeadEnd(const Maze& maze, MazeSolution& mazeSolution, Direction cur_dir);

    int getIndexFromPosition(int vec_c, int vec_r);
    int getIndexFromPosition(int vec_c, int vec_r, Direction cur_dir);

    void recursiveForSolveMaze(const Maze& maze, MazeSolution& mazeSolution);
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution);

private:
    int heightOfMaze;
    int widthOfMaze;
    int sizeOfMaze;
    int indexOfVector;
    std::vector<std::string> vectorOfMaze;
    std::vector<Direction> precedences { Direction::down, Direction::right, Direction::up, Direction::left };
};


#endif // CUSTOMIZEDMAZESOLVER_HPP