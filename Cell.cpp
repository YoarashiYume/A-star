#include "Cell.h"

Cell::Cell(std::string type,int x_,int y_)
{
	if (isdigit(type[0]))
	{
		this->cellWeigth = std::atoi(type.c_str());
		this->state = NOT_VISITED;
	}
	else
		switch (type[0])
		{
		case 's' | 'S':
			this->state = START;
			this->cellWeigth = 1;
			break;
		case 'f' | 'F':
			this->state = FINISH;
			this->cellWeigth = 1;
			break;
		default:
			this->state = BLOCKED;
			this->cellWeigth = INT_MAX;
			break;
		}
	if (this->state == START)
		this->costG = 0;
	else
		this->costG = INT_MAX;
	this->status = Cell::NONE;
	this->location.first = x_;
	this->location.second = y_;
	this->previous = nullptr;
	isPath = false;
}

Cell::~Cell()
{

}

void Cell::addNeighbors(Cell& other)
{
	if (this->neighbors.size() == 4)/*add Neighbors point*/
		return;
	if (abs(this->getX() - other.getX()) == 1 && abs(this->getY() - other.getY()) == 0 || abs(this->getX() - other.getX()) ==0 && abs(this->getY() - other.getY()) == 1)
		if (this->getX() != other.getX() || this->getY() != other.getY())
			neighbors.push_back(std::ref(other));
}


std::vector<std::reference_wrapper<Cell>> Cell::getNeighbors()
{
	return this->neighbors;
}

Cell::Statement Cell::getState()
{
	return this->state;
}

Cell* Cell::getPrevious()
{
	return previous;
}

std::pair<int, int> Cell::getLocation()
{
	return this->location;
}

void Cell::setCostG(int cost_)
{
	costG = cost_;
}

int Cell::getCostG()
{
	return costG;
}

void Cell::setCostF(double cost_)
{
	costF = cost_;
}

double Cell::getCostF()
{
	return costF;
}

int Cell::getCellWeigth()
{
	return cellWeigth;
}

Cell::Status Cell::getStatus()
{
	return this->status;
}

void Cell::setStatus(Status newStatus_)
{
	status = newStatus_;
}

void Cell::buildPath()
{
	this->isPath = true;
	if (this->previous != nullptr)
		this->previous->buildPath();

}

bool Cell::inPath()
{
	return isPath;
}

int Cell::getX()
{
	return location.first;
}

int Cell::getY()
{
	return location.second;
}

void Cell::setPrevious(Cell& cell)
{
	this->previous = &cell;
}
