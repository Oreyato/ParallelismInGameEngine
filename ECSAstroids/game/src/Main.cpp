///*******************************************************************************************
//*
//*   This game has been created using raylib (www.raylib.com)
//*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
//*
//*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
//*
//********************************************************************************************/

#include "raylib.h"

#include "../engine/Engine.hpp"
#include "../game/Game.hpp"
#include "../game/Consts.hpp"

int main()
{
	Engine engine;
	engine.Start(Consts::WINDOW_WIDTH, Consts::WINDOW_HEIGHT, "ECS implementation", std::make_unique<Game>());

	return 0;
}