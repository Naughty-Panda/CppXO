//////////////////////////////////////////////////
//				C++ XO
//		Naughty Panda @ 2021
//////////////////////////////////////////////////

#include <iostream>

#include "GameData.h"


int main() {

	//std::unique_ptr<int[]> arr = std::make_unique<int[]>(10);
	//std::unique_ptr<TFrame> frame = std::make_unique<TFrame>();

	// Grid creation
	std::pair<size_t, size_t> PGridSize = GetGridSize();
	auto GI = CreateGameInstance(PGridSize.first, PGridSize.second);

	// Assign Icons
	TPlayer* Player = &GI->GameData.Player;
	TPlayer* AI = &GI->GameData.AI;

	Player->Icon = GetPlayerIcon();
	AI->Icon = Player->Icon == ECell::X ? ECell::O : ECell::X;
	
	// Who moves first?
	srand(time(NULL));
	GI->GameData.ActivePlayer = rand() % 2 ? Player : AI;
	
	// Starting game!
	GI->StartGame();



	GI->GameData.Grid[0][0] = ECell::O;
	GI->GameData.PrintGrid();



	//std::cout << (char)GI->GameData.Player.Icon << std::endl;
	//std::cout << (char)GI->GameData.AI.Icon << std::endl;

	return 0;
}
