
#include "scene.h"
#include "pacman.h"
#include "system_renderer.h"
#include "Entity.h"
#include "Ghost.h"
#include "Player.h"
#include <iostream>

using namespace sf;
using namespace std;

shared_ptr<Scene> gameScene;
shared_ptr<Scene> menuScene;
shared_ptr<Scene> activeScene;

void Scene::render() { _ents.Render(Renderer::getWindow()); }

void Scene::update(double dt) {

	// Add something here?

}

vector<shared_ptr<Entity>>& Scene::getEnts() { return _ents.list; }

void MenuScene::update(double dt) {

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}

	Scene::update(dt);
	text.setString("Almost Pacman");
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load() {

	Font font;

	if (!font.loadFromFile("res/fonts/font.ttf"))
	{
		cout << "Font problems";
	}
	
	font.loadFromFile("res/fonts/font.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);
}

void GameScene::load() {
	for (int i = 1; i < 5; i++)
	{
		Color colors[4] = { Color::Red, Color::Blue, Color::Green, Color::Magenta };

		shared_ptr<Entity> ghost(new Ghost(colors[i]));

		_ents.list.push_back(ghost);
	}

	shared_ptr<Entity> player(new Player);
	_ents.list.push_back(player);
}

void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}

	Scene::update(dt);

	for (auto& e : _ents.list) {
		e->Update(dt);
	}
}

void GameScene::render() {

}