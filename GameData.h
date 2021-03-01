#pragma once

constexpr auto GRID_SIZE_X = 3;
constexpr auto GRID_SIZE_Y = 3;

enum class ECell : char {

	X = 'X',
	O = 'O',
	Empty = '_'
};

enum class EGameState {
	STATE
};

struct TGameData {

	ECell Grid[GRID_SIZE_Y][GRID_SIZE_X]{};
	EGameState State{};

	void PrintGrid();
};

struct TGameInstance {

	TGameData GameData{};
};


std::unique_ptr<TGameData> CreateGameData();
void InitGameData(TGameData&);

std::unique_ptr<TGameInstance> CreateGameInstance();
