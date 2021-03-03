//////////////////////////////////////////////////
//				C++ XO
//		Naughty Panda @ 2021
//////////////////////////////////////////////////

#include <iostream>

#include "GameData.h"


int main() {

	//std::unique_ptr<int[]> arr = std::make_unique<int[]>(10);
	//std::unique_ptr<TFrame> frame = std::make_unique<TFrame>();

	// Grid creation (3 - 5)
	std::pair<size_t, size_t> PGridSize = GetGridSize();
	auto GI = CreateGameInstance(PGridSize.first, PGridSize.second);

	// Set the number of marks to win (3 - 5)
	size_t nWinCount(0);
	GI->GameData.nWinCount = nWinCount;

	// Assign Icons
	TEntity* Player = &GI->GameData.Player;
	TEntity* AI = &GI->GameData.AI;

	Player->Icon = GetPlayerIcon();
	AI->Icon = Player->Icon == ECell::X ? ECell::O : ECell::X;
	
	// Who moves first?
	srand(time(NULL));
	GI->GameData.ActivePlayer = rand() % 2 ? Player : AI;
	
	// Starting game!
	GI->StartGame();



	//std::cout << (char)GI->GameData.Player.Icon << std::endl;
	//std::cout << (char)GI->GameData.AI.Icon << std::endl;

	return 0;
}
