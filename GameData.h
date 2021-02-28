#pragma once

//enum class ECell {};
//enum class EGameState {};
//struct TGameData {};
//struct TGameInstance {};

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

	ECell Grid[GRID_SIZE_Y][GRID_SIZE_X];
	EGameState State;
};

struct TGameInstance {

	TGameData GameData;

	TGameInstance() {};
	~TGameInstance() {};

};


std::unique_ptr<TGameInstance> CreateGameInstance();
std::unique_ptr<TGameData> CreateGameData();
