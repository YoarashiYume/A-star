#include "Reader.h"
/*reading point from file*/
Reader::Reader(std::string path, int size_)
{
	
	this->size = size_;
	std::fstream in;
	in.open(path);
	try
	{
		if (!in.is_open())
		{
			std::cout << "Exception opening/readin file";
			std::exit(1);
		}
		int x = 0;
		int y = 0;
		while (!in.eof() && list.size() < size * size)
		{
			std::string value;
			in >> value;
			list.push_back(Cell(value, x, y));
			y = x == size-1 ? y + 1 : y;
			x = x == size-1 ? 0 : x + 1;
			if (y == 2)
				y = 2;
		}
		in.close();
	}
	catch (const std::ifstream::failure& ex)
	{
		std::cout << "Exception opening/readin file";
		std::exit(1);
		in.close();
	}
	for (auto& el : list)
	{
		for (auto& elother : list)
			el.addNeighbors(elother);
	}
}

std::vector<Cell>& Reader::getList()
{
	return list;
}
