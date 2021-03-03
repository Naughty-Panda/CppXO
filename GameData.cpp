#include <iostream>
#include <string>
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

	for (size_t y = 0; y < gd.gSizeY; y++) {
		for (size_t x = 0; x < gd.gSizeX; x++) {
			gd.Grid[y][x] = ECell::Empty;
		}
	}
}

void TGameData::PrintGrid() {

	for (size_t y = 0; y < this->gSizeY; y++) {
		for (size_t x = 0; x < this->gSizeX; x++) {
			std::cout << static_cast<char> (this->Grid[y][x]) << " ";
		}
		std::cout << std::endl;
	}
}

void TGameData::PlayerMove() {

	std::cout << "Your move!\n";
	std::pair<size_t, size_t> PInput{ 0, 0 };

	do {
		PInput.first = GetUserInput("Please enter position X:", 1, gSizeX) - 1;
		PInput.second = GetUserInput("Please enter position Y:", 1, gSizeY) - 1;
	} while (Grid[PInput.second][PInput.first] != ECell::Empty);

	Grid[PInput.second][PInput.first] = Player.Icon;

	PrintGrid();

	// Give control to AI
	ActivePlayer = &AI;
}

void TGameData::AIMove() {

	std::cout << "AI moves!\n";

	// Give control to player
	ActivePlayer = &Player;
}

//////////////////////////////////////////////////////////////////////////////
//	GameInstance Functions
//////////////////////////////////////////////////////////////////////////////

void TGameInstance::StartGame() {

	TPlayer* Player = &GameData.Player;
	TPlayer* AI = &GameData.AI;


	for (int i = 0; i < 10; i++) {

		if (!GameData.ActivePlayer) {
			std::cerr << "No active player!\n";
			return;
		}

		GameData.ActivePlayer == Player ? GameData.PlayerMove() : GameData.AIMove();
	}
}

//////////////////////////////////////////////////////////////////////////////
//	User input
//////////////////////////////////////////////////////////////////////////////

std::pair<size_t, size_t> GetGridSize() {

	std::pair<size_t, size_t> PGridSize{ 0, 0 };

	PGridSize.first = GetUserInput("Please enter size X (3 - 5):", 3, 5);
	PGridSize.second = GetUserInput("Please enter size Y (3 - 5):", 3, 5);

	return PGridSize;
}

size_t GetUserInput(const std::string& inStr, const size_t min, const size_t max) {

	size_t tmp(0);

	while (tmp < min || tmp > max) {
		std::cout << inStr;
		std::cin >> tmp;
		if (std::cin.fail()) {
			std::cout << "\nThat's not gonna work!\n";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			tmp = 0;
		}
	}

	return tmp;
}

ECell GetPlayerIcon() {

	size_t icon = GetUserInput("Please choose your icon:\n\t(1 to play as X)\n\t(2 to play as O):", 1, 2);
	return icon == 1 ? ECell::X : ECell::O;
}
