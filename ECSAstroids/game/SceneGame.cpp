#include "SceneGame.hpp"
#include "../engine/AssetsManager.hpp"


SceneGame::SceneGame(shared_ptr<ECSManager> ecsRef,	Game& game): 
	ecs{ std::move(ecsRef) }, 
	game{ game }
{
}

void SceneGame::Load() {
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
	shipTransform.pos = { 100, 100 };

	Sprite& shipSprite = ecs->CreateSpriteComponent(ship, "Ship");
	Rigidbody2D& shipRb = ecs->CreateRigidbody2DComponent(ship, Vector2{ 0, 0 }, shipSprite.srcRect);
	  
	// -- ASTROIDS --

	// -- BACKGROUND --
	// Far back

	// Stars

	//^ Create entities ==============================================
}

void SceneGame::Update(f32 dt) {
	
}

void SceneGame::Draw() {
	ecs->PrepareDraw();
	ecs->DrawScene();
}

void SceneGame::Unload() {
	AssetsManager::UnloadSceneTextures(ToSceneId(SceneName::SceneGame));
}
