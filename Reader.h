#ifndef _READER_H_
#define _READER_H_
#include <vector>
#include "Cell.h"
#include <fstream>
#include<iostream>
#include <string>
class Reader
{
private:
	std::vector<Cell> list;
	int size;
public:
	Reader(std::string path, int size_);
	std::vector<Cell>& getList();
};
#endif
