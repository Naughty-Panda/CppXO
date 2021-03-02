//////////////////////////////////////////////////
//				C++ XO
//		Naughty Panda @ 2021
//////////////////////////////////////////////////

#include <iostream>

#include "GameData.h"


int main() {

	//std::unique_ptr<int[]> arr = std::make_unique<int[]>(10);
	//std::unique_ptr<TFrame> frame = std::make_unique<TFrame>();

	std::pair<size_t, size_t> PGridSize = GetGridSize();
	auto GI = CreateGameInstance(PGridSize.first, PGridSize.second);

	GI->GameData.Grid[0][0] = ECell::O;
	GI->GameData.PrintGrid();




	return 0;
}
