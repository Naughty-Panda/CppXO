#pragma once

enum class ECell {};
enum class EGameState {};
struct TGameData {};
struct TGameInstance {};


std::unique_ptr<TGameInstance> CreateGameInstance();
