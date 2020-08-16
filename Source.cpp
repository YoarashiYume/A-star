#include "Reader.h"
#include "Astar.h"
int main(int argc, char* argv[])
{
	if (argc < 4) {
		std::cout << "usage: <prog-name> <sizeOfSqareMatrix> <input.txt>  <output.txt>\n";
		std::system("pause");
		return 1;
	}
	int size = std::atoi(argv[1]);
	Reader read(argv[2], size);
	Astar aSta(read.getList(), argv[3]);
	/*Reader read("input.txt", 5);
	Astar aStar(read.getList(),"output.txt");*/
	return 0;
}