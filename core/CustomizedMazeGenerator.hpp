// CustomizedMazeGenerator.hpp
//
// ICS 46 Spring 2015
// Project #1: Dark at the End of the Tunnel

#ifndef CUSTOMIZEDMAZEGENERATOR_HPP
#define CUSTOMIZEDMAZEGENERATOR_HPP

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "Direction.hpp"
#include "Maze.hpp"
#include "MazeGenerator.hpp"


class CustomizedMazeGenerator : public MazeGenerator
{
public:
    CustomizedMazeGenerator();
    ~CustomizedMazeGenerator();

    bool isModified(int vec_c, int vec_r, Direction cur_dir);
    bool allModified(int vec_c, int vec_r);

    Direction randomDirection();

    int getIndexFromPosition(int vec_x, int vec_y, Direction cur_dir);

    void generateMaze(Maze& maze);
    void recursiveForGenerateMaze(Maze& maze, int vec_c, int vec_r);

private:
    int heightOfMaze;
    int widthOfMaze;
    int sizeOfMaze;
    int indexOfVector;
    std::vector<std::string> vectorOfMaze;
    Direction dir_arr[4] = { Direction::up, Direction::down, Direction::left, Direction::right };
};


#endif // CUSTOMIZEDMAZEGENERATOR_HPP