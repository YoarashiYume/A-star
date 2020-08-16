#include "Astar.h"

double Astar::hFunction(Cell& current,Cell& finishCell)
{
	return sqrt(pow(current.getLocation().first - finishCell.getLocation().first, 2) + pow(current.getLocation().second - finishCell.getLocation().second, 2));
}

Cell* Astar::minimymF(std::vector<Cell*> list)
{
	int minimumIndex = INT_MAX;
	double minF = INT_MAX;
	for (size_t i = 0; i < list.size(); ++i)
	{
		if (list.at(i)->getCostF() < minF && list.at(i)->getState()!= Cell::BLOCKED)
		{
			minF = list.at(i)->getCostF();
			minimumIndex = i;
		}
	}
	return list.at(minimumIndex);
}

void Astar::saveResult(std::string pathSave, std::vector<Cell> list)
{
	/*simple outprint*/
	std::ofstream out;
	out.open(pathSave);
	if (!isPathFind)
	{
		out << "No Path\n";
		out.close();
		return;
	}
	try
	{
		int size = sqrt(list.size())-1;
		for (size_t i = 0; i < list.size(); ++i)
		{
			if (i % (size + 1) == 0 && i != 0)
				out << std::endl;
			if (list[i].getState() == Cell::FINISH)
				out << 'F' << " ";
			else if (list[i].getState() == Cell::START)
				out << 'S' << " ";
			else if (list[i].inPath())
				out << '*' << " ";
			else if (list[i].getState() == Cell::BLOCKED)
				out << '1' << " ";
			else
				out << '0' << " ";
		}
		out.close();
	}
	catch (const std::ifstream::failure& ex)
	{
		std::cout << "Exception opening/readin file";
		out.close();
	}
}

Astar::Astar(std::vector<Cell> list,std::string savePath)
{
	isPathFind = false;
	std::vector<Cell*> close;
	std::vector<Cell*> open;
	auto it = std::find_if(list.begin(), list.end(), [](Cell el) {return el.getState() == Cell::START; });
	Cell finish = *std::find_if(list.begin(), list.end(), [](Cell el) {return el.getState() == Cell::FINISH; });
	open.push_back(&(*it));
	open.front()->setCostG(0);
	open.front()->setCostF(it->getCostG() + hFunction(*it, finish));
	while (open.size() != 0)
	{
		Cell* currCell = minimymF(open);
		if (currCell->getLocation() == finish.getLocation())
		{
			isPathFind = true;
			currCell->buildPath();
			break;
		}
		open.erase(std::find_if(open.begin(), open.end(), [currCell](Cell* el) {return el->getLocation() == currCell->getLocation(); }));
		close.push_back(currCell);
		currCell->setStatus(Cell::ClOSE);
		auto listOfPoint = currCell->getNeighbors();
		for (int i = 0; i < listOfPoint.size(); ++i)
		{
			auto itCurr = std::find_if(list.begin(), list.end(), [&listOfPoint,i](Cell el) {return el.getLocation() == listOfPoint[i].get().getLocation(); });
			int tempG = currCell->getCostG() + itCurr->getCellWeigth();
			if (itCurr->getState() == Cell::BLOCKED)
				continue;
			if (itCurr->getStatus() != Cell::ClOSE || (tempG < itCurr->getCostG() && itCurr->getStatus() == Cell::ClOSE))
			{
				itCurr->setPrevious(*currCell);
				itCurr->setCostG(tempG);
				itCurr->setCostF(itCurr->getCostG() + hFunction(*itCurr, finish));
				if (itCurr->getStatus() != Cell::OPEN)
				{
					itCurr->setStatus(Cell::OPEN);
					open.push_back(&(*itCurr));
				}
			}
		}
	}
	saveResult(savePath, list);
}
