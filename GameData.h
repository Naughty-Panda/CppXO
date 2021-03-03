#pragma once

//////////////////////////////////////////////////////////////////////////////
//	Structs & Enums
//////////////////////////////////////////////////////////////////////////////

enum class ECell : char {

	X = 'X',
	O = 'O',
	Empty = '_'
};

enum class EGameState {
	GAME_STARTED, STATE
};

struct TEntity {

	ECell Icon{};
};

struct TGameData {

	size_t nGridSizeX{ 3 };
	size_t nGridSizeY{ 3 };
	ECell** Grid{};
	size_t nWinCount{ 3 };
	size_t nMoveCount{ 0 };
	EGameState State{};
	TEntity Player{};
	TEntity AI{};
	TEntity* ActivePlayer{nullptr};

	TGameData(size_t x = 3, size_t y = 3);
	~TGameData();

	void PrintGrid();
	void PlayerMove();
	void AIMove();
};

struct TGameInstance {

	TGameData GameData{};

	TGameInstance(size_t x = 3, size_t y = 3) : GameData{ x,y } {};

	void StartGame();
};

void InitGameData(TGameData&);
std::unique_ptr<TGameInstance> CreateGameInstance(size_t x, size_t y);

//////////////////////////////////////////////////////////////////////////////
//	User input
//////////////////////////////////////////////////////////////////////////////

std::pair<size_t, size_t> GetGridSize();
size_t GetUserInput(const std::string&, const std::string&, const size_t, const size_t);
ECell GetPlayerIcon();
