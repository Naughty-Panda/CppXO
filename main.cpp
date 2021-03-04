//////////////////////////////////////////////////
//				C++ XO
//		Naughty Panda @ 2021
//////////////////////////////////////////////////

#include <iostream>

#include "GameData.h"


int main() {

	// Grid creation (3 - 5)
	std::pair<size_t, size_t> PGridSize = GetGridSize();
	auto GI = CreateGameInstance(PGridSize.first, PGridSize.second);

	// Set win streak (3 - 5)
	SetWinStreak(GI->GameData);

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

	return 0;
}
