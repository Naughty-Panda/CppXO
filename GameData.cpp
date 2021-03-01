#include <iostream>
#include <memory>

#include "GameData.h"



std::unique_ptr<TGameInstance> CreateGameInstance(size_t x, size_t y) {

	auto GI = std::make_unique<TGameInstance>(x, y);

	InitGameData(GI->GameData);
	GI->GameData.State = EGameState::STATE;

	return GI;
}

//////////////////////////////////////////////////////////////////////////////
//	GameData Constructors
//////////////////////////////////////////////////////////////////////////////

TGameData::TGameData(size_t x, size_t y) : gSizeX(x), gSizeY(y) {

	std::cout << "GameData constructor called.\n";

	Grid = new (std::nothrow) ECell * [gSizeY];
	if (!Grid) {
		std::cerr << "Can't allocate grid's outer array.\n" << std::endl;
		return;
	}

	for (size_t y = 0; y < gSizeY; y++) {
		Grid[y] = new (std::nothrow) ECell[gSizeX];
		if (!Grid[y]) {
			std::cerr << "Can't allocate grid's inner array.\n" << std::endl;
			return;
		}
	}
}

TGameData::~TGameData() {
	
	std::cout << "GameData destructor called.\n";

	for (size_t y = 0; y < this->gSizeY; y++) {
		delete[] this->Grid[y];
	}

	delete[] this->Grid;
}

//////////////////////////////////////////////////////////////////////////////
//	GameData Functions
//////////////////////////////////////////////////////////////////////////////

void InitGameData(TGameData& gd) {

	if (!gd.Grid) return;

	for (size_t n = 0; n < gd.gSizeY; n++) {
		for (size_t m = 0; m < gd.gSizeX; m++) {
			gd.Grid[n][m] = ECell::Empty;
		}
	}
}

void TGameData::PrintGrid() {

	for (size_t n = 0; n < this->gSizeY; n++) {
		for (size_t m = 0; m < this->gSizeX; m++) {
			std::cout << static_cast<char> (this->Grid[n][m]) << " ";
		}
		std::cout << std::endl;
	}
}