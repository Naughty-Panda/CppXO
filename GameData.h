#pragma once

//constexpr auto GRID_SIZE_X = 3;
//constexpr auto GRID_SIZE_Y = 3;

enum class ECell : char {

	X = 'X',
	O = 'O',
	Empty = '_'
};

enum class EGameState {
	STATE
};

struct TGameData {

	size_t gSizeX{ 0 };
	size_t gSizeY{ 0 };
	ECell** Grid{};
	EGameState State{};

	TGameData(size_t x = 0, size_t y = 0);
	~TGameData();

	void PrintGrid();
};

struct TGameInstance {

	TGameData GameData{};

	TGameInstance(size_t x = 0, size_t y = 0) : GameData{ x,y } {};
};


void InitGameData(TGameData&);

std::unique_ptr<TGameInstance> CreateGameInstance(size_t x, size_t y);
