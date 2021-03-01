//////////////////////////////////////////////////
//				C++ XO
//		Naughty Panda @ 2021
//////////////////////////////////////////////////

#include <iostream>

#include "GameData.h"


int main() {

	//std::unique_ptr<int[]> arr = std::make_unique<int[]>(10);
	//std::unique_ptr<TFrame> frame = std::make_unique<TFrame>();


	auto GI = CreateGameInstance();

	GI->GameData.Grid[0][0] = ECell::O;

	for (size_t n = 0; n < GRID_SIZE_Y; n++) {
		for (size_t m = 0; m < GRID_SIZE_X; m++) {
			std::cout << (char)GI->GameData.Grid[n][m] << " ";
		}
		std::cout << std::endl;
	}




	return 0;
}
