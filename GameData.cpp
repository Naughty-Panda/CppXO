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

TGameData::TGameData(size_t x, size_t y) : nGridSizeX(x), nGridSizeY(y) {

	std::cout << "GameData constructor called.\n";

	Grid = new (std::nothrow) ECell * [nGridSizeY];
	if (!Grid) {
		std::cerr << "Can't allocate grid's outer array.\n" << std::endl;
		return;
	}

	for (size_t y = 0; y < nGridSizeY; y++) {
		Grid[y] = new (std::nothrow) ECell[nGridSizeX];
		if (!Grid[y]) {
			std::cerr << "Can't allocate grid's inner array.\n" << std::endl;
			return;
		}
	}
}

TGameData::~TGameData() {
	
	std::cout << "GameData destructor called.\n";

	for (size_t y = 0; y < this->nGridSizeY; y++) {
		delete[] this->Grid[y];
	}

	delete[] this->Grid;
}

//////////////////////////////////////////////////////////////////////////////
//	GameData Functions
//////////////////////////////////////////////////////////////////////////////

void InitGameData(TGameData& gd) {

	if (!gd.Grid) return;

	for (size_t y = 0; y < gd.nGridSizeY; y++) {
		for (size_t x = 0; x < gd.nGridSizeX; x++) {
			gd.Grid[y][x] = ECell::Empty;
		}
	}
}

void TGameData::PrintGrid() {

	for (size_t y = 0; y < this->nGridSizeY; y++) {
		for (size_t x = 0; x < this->nGridSizeX; x++) {
			std::cout << static_cast<char> (this->Grid[y][x]) << " ";
		}
		std::cout << std::endl;
	}
}

void TGameData::PlayerMove() {

	std::cout << "Your move!\n";
	size_t nPosX(0), nPosY(0);

	do {
		nPosX = GetUserInput("\tEnter position X:", "Out of grid! Please try again!", 1, nGridSizeX) - 1;
		nPosY = GetUserInput("\tEnter position Y:", "Out of grid! Please try again!", 1, nGridSizeY) - 1;
	} while (Grid[nPosY][nPosX] != ECell::Empty);

	Grid[nPosY][nPosX] = Player.Icon;

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

	TEntity* Player = &GameData.Player;
	TEntity* AI = &GameData.AI;


	for (int i = 0; i < 10; i++) {

		if (!GameData.ActivePlayer) {
			std::cerr << "No active player!\n";
			return;
		}

		GameData.ActivePlayer == Player ? GameData.PlayerMove() : GameData.AIMove();
		GameData.nMoveCount++;

		if (GameData.nMoveCount > (GameData.nWinCount - 1) * 2) {
			// Check for victory
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//	User input
//////////////////////////////////////////////////////////////////////////////

std::pair<size_t, size_t> GetGridSize() {

	std::pair<size_t, size_t> PGridSize{ 0, 0 };
	const std::string sErrMsg{ "Size should be (3 - 5)! Please try again!" };

	PGridSize.first = GetUserInput("\tEnter size X (3 - 5):", sErrMsg, 3, 5);
	PGridSize.second = GetUserInput("\tEnter size Y (3 - 5):", sErrMsg, 3, 5);

	return PGridSize;
}

void SetWinCount(TGameData& gamedata) {

	size_t nMin = gamedata.nGridSizeX < gamedata.nGridSizeY ? gamedata.nGridSizeX : gamedata.nGridSizeY;
	// No need to ask user if one of grid's sizes is 3
	gamedata.nWinCount = nMin == 3 ? nMin : GetUserInput("Enter number of marks to win:", "Please try again!", 3, nMin);
}

size_t GetUserInput(const std::string& inMsg, const std::string& errMsg, const size_t min, const size_t max) {

	size_t nInput(0), nFailCount(0);

	while (nInput < min || nInput > max) {

		if (nFailCount) {

			std::cout << errMsg << std::endl;
		}

		std::cout << inMsg;
		std::cin >> nInput;
		if (std::cin.fail()) {
			std::cout << "\nThat's not gonna work!\n";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			nInput = 0;
		}
		nFailCount++;
	}

	return nInput;
}

ECell GetPlayerIcon() {

	const std::string sMsg{ "\tChoose your icon:\n\t(1 to play as X)\n\t(2 to play as O):" };
	const std::string sErrMsg{ "No such icon, please try again!" };

	size_t nIcon = GetUserInput(sMsg, sErrMsg, 1, 2);
	return nIcon == 1 ? ECell::X : ECell::O;
}
