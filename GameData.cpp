#include <memory>

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

};

std::unique_ptr<TGameInstance> CreateGameInstance() {

	auto GI = std::make_unique<TGameInstance>();
	return GI;
}
