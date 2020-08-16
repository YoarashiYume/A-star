#ifndef _ASTAT_H_
#define _ASTAR_H_
#include <vector>
#include <algorithm>
#include "Cell.h"
#include <math.h>
#include <fstream>
#include <iostream>
class Astar
{
private:
	double hFunction(Cell& current,Cell&finishCell);
	Cell* minimymF(std::vector<Cell*> list);
	bool isPathFind;
	void saveResult(std::string pathSave, std::vector<Cell> list);
public:
	Astar(std::vector<Cell> list, std::string savePath);
};
#endif // !_ASTAT_H_