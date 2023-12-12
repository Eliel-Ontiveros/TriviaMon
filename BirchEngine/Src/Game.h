#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;
class Game
{

public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;
	static SDL_Rect Message_rect;
	static int cont_vict;


	enum groupLabels : std::size_t
	{
		groupnpc,
		groupnpc2,
		groupnpc3,
		groupnpc4,
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		grouptex,
		groupUI
	};

private:

	int cnt = 0;
	SDL_Window* window;
	void handleNPCInteraction();
	void handleNPCInteractionn();
	void handleNPCInteractionnn();
	void handleNPCInteractionnnn();
	void initializeFont();
	void cleanupFont();



};