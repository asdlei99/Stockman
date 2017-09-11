#ifndef ENUMS_H
#define ENUMS_H

#pragma region Comment

/*
	Author:

	This header contains different Enums

*/

#pragma endregion Description


namespace Logic
{
	enum GameState
	{
		gameStateGame,
		gameStateLoading,
		gameStateMenuMain,
		gameStateMenuSettings
	};

	enum PlayerState
	{
		playerStateStanding,
		playerStateCrouching,
		playerStateInAir
	};
}

#endif // !ENUMS_H