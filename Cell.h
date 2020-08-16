#ifndef _CELL_H_
#define _CELL_H_
#include <vector>
#include <string>
#include <utility>
class Cell
{
public:
	enum Statement {
		START,
		FINISH,
		NOT_VISITED,
		VISITED,
		BLOCKED
	};
	enum Status {
		OPEN,
		ClOSE,
		NONE
	};
private:
	int costG;
	double costF;
	int cellWeigth;
	Status status;
	std::vector<std::reference_wrapper<Cell>> neighbors;
	Statement state;
	std::pair<int, int> location;
	Cell* previous;
	bool isPath;
	int getX();
	int getY();
public:
	Cell(std::string, int x_, int y_);
	~Cell();
	void addNeighbors(Cell& other);
	std::vector<std::reference_wrapper<Cell>> getNeighbors();
	Statement getState();
	Cell* getPrevious();
	std::pair<int, int> getLocation();
	void setCostG(int cost_);
	int getCostG();
	void setCostF(double cost_);
	double getCostF();
	void setPrevious(Cell& cell);
	int getCellWeigth();
	Status getStatus();
	void setStatus(Status newStatus_);
	void buildPath();
	bool inPath();
};
#endif // !_CELL_H_