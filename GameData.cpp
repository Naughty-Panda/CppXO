#include <memory>

#include "GameData.h"


std::unique_ptr<TGameData> CreateGameData() {

	auto GD = std::make_unique<TGameData>();
	return GD;
}

void InitGameData(TGameData& gd) {

	for (size_t n = 0; n < GRID_SIZE_Y; n++) {
		for (size_t m = 0; m < GRID_SIZE_X; m++) {
			gd.Grid[n][m] = ECell::Empty;
		}
	}
}

std::unique_ptr<TGameInstance> CreateGameInstance() {

	auto GI = std::make_unique<TGameInstance>();
	InitGameData(GI->GameData);
	GI->GameData.State = EGameState::STATE;

	return GI;
}
