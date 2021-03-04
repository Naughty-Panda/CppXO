#include <iostream>
#include <string>
#include <memory>

#include "GameData.h"


std::unique_ptr<TGameInstance> CreateGameInstance(size_t x, size_t y) {

	auto GI = std::make_unique<TGameInstance>(x, y);

	InitGameData(GI->GameData);
	GI->GameData.State = EGameState::IN_PROGRESS;

	return GI;
}

//////////////////////////////////////////////////////////////////////////////
//	GameData Constructors
//////////////////////////////////////////////////////////////////////////////

TGameData::TGameData(size_t x, size_t y) : nGridSizeX(x), nGridSizeY(y) {

	//std::cout << "GameData constructor called.\n";

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
	
	//std::cout << "GameData destructor called.\n";

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

	// Header
	std::cout << "    ";
	for (size_t x = 0; x < nGridSizeX; x++) {
		std::cout << x + 1 << " ";
	}
	std::cout << std::endl;

	// Grid
	for (size_t y = 0; y < this->nGridSizeY; y++) {
		std::cout << y + 1 << " | ";
		for (size_t x = 0; x < this->nGridSizeX; x++) {
			std::cout << static_cast<char> (this->Grid[y][x]) << " ";
		}
		std::cout << "|"<< std::endl;
	}
	std::cout << std::endl;
}

void TGameData::PlayerMove() {

	std::cout << "\tYour move!\n";
	size_t nPosX(0), nPosY(0);

	do {
		nPosX = GetUserInput("\tEnter position X:", "Out of grid! Please try again!", 1, nGridSizeX) - 1;
		nPosY = GetUserInput("\tEnter position Y:", "Out of grid! Please try again!", 1, nGridSizeY) - 1;
	} while (Grid[nPosY][nPosX] != ECell::Empty);

	Grid[nPosY][nPosX] = Player.Icon;

	// Give control to AI
	ActivePlayer = &AI;
}

void TGameData::AIMove() {

	std::cout << "AI moves!\n";

	// Win or block next posotoin in the row
	if (WinBlockRow(1, 2)) return;

	// Win or block in between the row
	if (WinBlockRow(2, 1)) return;

	// Win or block next position in column
	if (WinBlockColumn(1, 2)) return;

	// Win or block in between the column
	if (WinBlockColumn(2, 1)) return;

	// TEMP
	for (size_t y = 0; y < nGridSizeY; y++) {
		for (size_t x = 0; x < nGridSizeX; x++) {
			if (Grid[y][x] == ECell::Empty) {
				Grid[y][x] = AI.Icon;
				ActivePlayer = &Player;
				return;
			}
		}
	}

	// Give control to player
	ActivePlayer = &Player;
}

bool TGameData::WinBlockRow(size_t mid, size_t next) {

	for (size_t y = 0; y < nGridSizeY; y++) {
		for (size_t x = 0; x < nGridSizeX - 2; x++) {
			if ((Grid[y][x] != ECell::Empty) && (Grid[y][x] == Grid[y][x + mid])) {
				// Win or block
				if (Grid[y][x + next] == ECell::Empty) {
					Grid[y][x + next] = AI.Icon;
					ActivePlayer = &Player;
					return true;
				}
			}
		}
	}

	return false;
}

bool TGameData::WinBlockColumn(size_t mid, size_t next) {

	for (size_t x = 0; x < nGridSizeX; x++) {
		for (size_t y = 0; y < nGridSizeY - 2; y++) {
			if ((Grid[y][x] != ECell::Empty) && (Grid[y][x] == Grid[y + next][x])) {
				// Win or block
				if (Grid[y + mid][x] == ECell::Empty) {
					Grid[y + mid][x] = AI.Icon;
					ActivePlayer = &Player;
					return true;
				}
			}
		}
	}

	return false;
}

std::pair<ECell, EGameState> TGameData::CheckState() {

	size_t nCount(0);
	size_t nDiag = nGridSizeX < nGridSizeY ? nGridSizeX - 1 : nGridSizeY - 1;

	// Check rows
	for (size_t y = 0; y < nGridSizeY; y++) {
		for (size_t x = 0; x < nGridSizeX - 1; x++) {
			(Grid[y][x] != ECell::Empty) && (Grid[y][x] == Grid[y][x + 1]) ? nCount++ : nCount = 0;
			if (nCount == nWinStreak - 1) return { Grid[y][x], EGameState::WIN };
		}
	}

	// Check columns
	for (size_t x = 0; x < nGridSizeX; x++) {
		for (size_t y = 0; y < nGridSizeY - 1; y++) {
			(Grid[y][x] != ECell::Empty) && (Grid[y][x] == Grid[y + 1][x]) ? nCount++ : nCount = 0;
			if (nCount == nWinStreak - 1) return { Grid[y][x], EGameState::WIN };
		}
	}

	// Check main diagonal
	for (size_t d = 0; d < nDiag; d++) {
		(Grid[d][d] != ECell::Empty) && (Grid[d][d] == Grid[d + 1][d + 1]) ? nCount++ : nCount = 0;
		if (nCount == nWinStreak - 1) return { Grid[d][d], EGameState::WIN };
	}

	// Check reverse diagonal
	for (size_t d = 0; d < nDiag; d++) {
		(Grid[d][nDiag - d] != ECell::Empty) && (Grid[d][nDiag - d] == Grid[d + 1][nDiag - d - 1]) ? nCount++ : nCount = 0;
		if (nCount == nWinStreak - 1) return { Grid[d][nDiag - d], EGameState::WIN };
	}

	// Check empty cells	
	for (size_t y = 0; y < nGridSizeY; y++) {
		for (size_t x = 0; x < nGridSizeX; x++) {
			if (Grid[y][x] == ECell::Empty) return { ECell::Empty, EGameState::IN_PROGRESS };
		}
	}

	return { ECell::Empty, EGameState::DRAW };
}


//////////////////////////////////////////////////////////////////////////////
//	GameInstance Functions
//////////////////////////////////////////////////////////////////////////////

void TGameInstance::StartGame() {

	TEntity* Player = &GameData.Player;
	TEntity* AI = &GameData.AI;
	std::pair<ECell, EGameState> CheckResult{};
	ECell Winner{ ECell::Empty };
	EGameState NewState{ EGameState::IN_PROGRESS };

	while (GameData.State == EGameState::IN_PROGRESS) {

		if (!GameData.ActivePlayer) {
			std::cerr << "No active player!\n";
			return;
		}

		ClearScreen();
		GameData.PrintGrid();

		GameData.ActivePlayer == Player ? GameData.PlayerMove() : GameData.AIMove();
		GameData.nMoveCount++;

		if (GameData.nMoveCount > (GameData.nWinStreak - 1) * 2) {

			// Update status if needed
			CheckResult = GameData.CheckState();
			GameData.State = NewState = CheckResult.second;
		}
	}
	
	ClearScreen();
	GameData.PrintGrid();

	Winner = CheckResult.first;
	if (Winner != ECell::Empty) {

		std::cout << (Winner == Player->Icon ? "\tCongratulations!\n\tVictory is yours!\n" : "\tAI wins!\n");
	}

	if (NewState == EGameState::DRAW) {

		std::cout << "\tIt's a draw!\n";
	}
}

//////////////////////////////////////////////////////////////////////////////
//	User input
//////////////////////////////////////////////////////////////////////////////

std::pair<size_t, size_t> GetGridSize() {

	std::pair<size_t, size_t> PGridSize{ 0, 0 };
	const std::string sErrMsg{ "Size should be (3 - 5)! Please try again!" };

	PGridSize.second = PGridSize.first = GetUserInput("\tEnter grid size (3 - 5):", sErrMsg, 3, 5);

	//PGridSize.first = GetUserInput("\tEnter size X (3 - 5):", sErrMsg, 3, 5);
	//PGridSize.second = GetUserInput("\tEnter size Y (3 - 5):", sErrMsg, 3, 5);

	return PGridSize;
}

void SetWinStreak(TGameData& gamedata) {

	size_t nMin = gamedata.nGridSizeX < gamedata.nGridSizeY ? gamedata.nGridSizeX : gamedata.nGridSizeY;
	// No need to ask user if one of grid's sizes is 3
	gamedata.nWinStreak = nMin == 3 ? nMin : GetUserInput("Enter win streak (3 - 5):", "Please try again!", 3, nMin);
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

//////////////////////////////////////////////////////////////////////////////
//	Utility
//////////////////////////////////////////////////////////////////////////////

void ClearScreen() {

	// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
	std::cout << "\x1B[2J\x1B[H";
}
