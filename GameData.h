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
	STATE
};

struct TGameData {

	size_t gSizeX{ 3 };
	size_t gSizeY{ 3 };
	ECell** Grid{};
	EGameState State{};

	TGameData(size_t x = 3, size_t y = 3);
	~TGameData();

	void PrintGrid();
};

struct TGameInstance {

	TGameData GameData{};

	TGameInstance(size_t x = 3, size_t y = 3) : GameData{ x,y } {};
};


void InitGameData(TGameData&);

std::unique_ptr<TGameInstance> CreateGameInstance(size_t x, size_t y);

//////////////////////////////////////////////////////////////////////////////
//	User input
//////////////////////////////////////////////////////////////////////////////

std::pair<size_t, size_t> GetGridSize();
size_t GetUserSize(const char axis);
