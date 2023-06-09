#include "Game.hpp"
#include "SceneGame.hpp"

#include <ranges>


void Game::Load() {
	// Init jobs
	jobs::Initialize();
	// Init Entity Component System
	ecs = std::make_shared<ECSManager>();
	// Init first scene
	AddScene(std::make_unique<SceneGame>(ecs, *this));
}

void Game::Update(f32 dt) {
	for (auto&& scene : std::ranges::reverse_view(sceneStack)) {
		scene->Update(dt);
		if (scene->GetLocking()) break;
	}
}

void Game::Draw() {
	for (auto&& scene : std::ranges::reverse_view(sceneStack)) {
		scene->Draw();
		if (!scene->GetTransparent()) break;
	}
}

void Game::AddScene(unique_ptr<IScene> newScene) {
	sceneStack.push_back(std::move(newScene));
	sceneStack.back()->Load();
}

void Game::RemoveCurrentScene() {
	if (sceneStack.empty()) return;
	sceneStack.back()->Unload();
	sceneStack.pop_back();
}

void Game::SwitchScene(unique_ptr<IScene> newScene) {
	if (!sceneStack.empty()) {
		RemoveCurrentScene();
	}
	AddScene(std::move(newScene));
}

void Game::Unload() {
	for (auto&& scene : std::ranges::reverse_view(sceneStack)) {
		scene->Unload();
	}
	sceneStack.clear();
}
