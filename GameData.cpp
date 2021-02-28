#include <memory>

enum class ECell {};
enum class EGameState {};
struct TGameData {};
struct TGameInstance {};

std::unique_ptr<TGameData> CreateGameData() {

	auto GD = std::make_unique<TGameData>();
	return GD;
}

std::unique_ptr<TGameInstance> CreateGameInstance() {

	auto GI = std::make_unique<TGameInstance>();
	return GI;
}
