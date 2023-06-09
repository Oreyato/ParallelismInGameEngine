#include "SceneGame.hpp"
#include "../engine/AssetsManager.hpp"
#include "Consts.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>


SceneGame::SceneGame(shared_ptr<ECSManager> ecsRef,	Game& game): 
	ecs{ std::move(ecsRef) }, 
	game{ game }
{
}

void SceneGame::Load() {
	srand((unsigned)time(0));
	i32 sceneId = ToSceneId(SceneName::SceneGame);

	//v Load textures ================================================
	AssetsManager::LoadTexture("Ship", "..\\resources\\Ship.png", sceneId);
	AssetsManager::LoadTexture("ShipWithThrust", "..\\resources\\ShipWithThrust.png", sceneId);
	AssetsManager::LoadTexture("Laser", "..\\resources\\Laser.png", sceneId);

	AssetsManager::LoadTexture("Astroid", "..\\resources\\Astroid.png", sceneId);

	AssetsManager::LoadTexture("Farback01", "..\\resources\\Farback01.png", sceneId);
	AssetsManager::LoadTexture("Stars", "..\\resources\\Stars.png", sceneId);

	//^ Load textures ================================================
	//v Create entities ==============================================
	// -- SHIP --
	u64 ship = ecs->CreateEntity();
	Transform2D& shipTransform = ecs->CreateTransform2DComponent(ship);
	shipTransform.pos = { 100.0f, 100.0f };

	Sprite& shipSprite = ecs->CreateSpriteComponent(ship, "Ship");
	Rigidbody2D& shipRb = ecs->CreateRigidbody2DComponent(ship, Vector2{ 0, 0 }, shipSprite.srcRect);
	shipRb.velocity = { 100.0f, 10.0f };
	  
	// -- ASTROIDS --
	// Random values
	i32 maxAstroidsCount{ 10 };
	i16 maxXPos = Consts::WINDOW_WIDTH * 0.9f;
	i16 maxYPos = Consts::WINDOW_HEIGHT * 0.9f;
	i16 maxVelocity = 50;
	i16 minVelocity = -50;

	// Spawn astroids
	for (i16 i = 0; i < maxAstroidsCount; i++) {
		// Random position
		float randXPos = (float)(rand() % maxXPos);
		float randYPos = (float)(rand() % maxYPos);
		Vector2 randPos = { randXPos, randYPos };

		// Random velocity
		float randXVel = (float)(rand() % (maxVelocity - minVelocity)) + minVelocity;
		float randYVel = (float)(rand() % (maxVelocity - minVelocity)) + minVelocity;
		Vector2 randVel = { randXVel, randYVel };
		
		u64 astroid = ecs->CreateEntity();
		Transform2D& astroidTransform = ecs->CreateTransform2DComponent(astroid);
		astroidTransform.pos = randPos;

		Sprite& astroidSprite = ecs->CreateSpriteComponent(astroid, "Astroid");
		Rigidbody2D& astroidRb = ecs->CreateRigidbody2DComponent(astroid, Vector2{ 0, 0 }, astroidSprite.srcRect);
		astroidRb.velocity = randVel;
	}

	// -- BACKGROUND --
	// Far back

	// Stars

	//^ Create entities ==============================================
}

void SceneGame::Update(f32 dt) {
	ecs->UpdateScene(dt);
}

void SceneGame::Draw() {
	ecs->PrepareDraw();
	ecs->DrawScene();
}

void SceneGame::Unload() {
	AssetsManager::UnloadSceneTextures(ToSceneId(SceneName::SceneGame));
}
