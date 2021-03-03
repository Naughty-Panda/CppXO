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

struct TPlayer {

	ECell Icon{};
	int token : 1;
};

struct TGameData {

	size_t gSizeX{ 3 };
	size_t gSizeY{ 3 };
	ECell** Grid{};
	EGameState State{};
	TPlayer Player{};
	TPlayer AI{};
	TPlayer* ActivePlayer{nullptr};

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
size_t GetUserInput(const std::string&, const size_t, const size_t);
ECell GetPlayerIcon();
