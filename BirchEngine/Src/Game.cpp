#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "SDL_ttf.h"
#include <sstream>
#include "SDL_image.h"
#include "SDL_mixer.h"


Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Texture* videoTexture = nullptr;

SDL_Rect Game::camera = { 0,0,1200,650 };

SDL_Rect Game::Message_rect = { 0, 0, 0, 0 };

AssetManager* Game::assets = new AssetManager(&manager);



bool check = false;
bool Game::isRunning = false;
bool introShown = false;
TTF_Font* font = nullptr;



auto& player(manager.addEntity());
auto& label(manager.addEntity());
auto& npc(manager.addEntity());
auto& textEntity(manager.addEntity());
auto& playButton(manager.addEntity());

std::string npcMessage;

std::vector<Entity*> buttons;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		}

		isRunning = true;
	}
	/*
		int totalFrames = 0;

		std::vector<std::string> animationFrames;
		std::vector<SDL_Texture*> frameTextures;

		for (int i = 1; i <= 999; ++i)
		{
			std::string framePath = "assets/frames/ezgif-frame-" + std::to_string(i) + ".png";
			std::cout << "Loading frame: " << framePath << std::endl;
			SDL_Surface* frameSurface = IMG_Load(framePath.c_str());

			if (!frameSurface)
			{
				std::cerr << "Error loading frame: " << framePath << std::endl;
				// Si no se puede cargar el frame, termina el bucle
				break;
			}

			SDL_Texture* frameTexture = SDL_CreateTextureFromSurface(renderer, frameSurface);
			SDL_FreeSurface(frameSurface);

			frameTextures.push_back(frameTexture);
			animationFrames.push_back(framePath);

			totalFrames = i;
		}

		// Obtén la información de la animación para determinar la duración total
		int frameDuration = 100;  // Ajusta la duración de cada frame en milisegundos
		int duration = SDL_GetTicks() + frameDuration * frameTextures.size();

		while (!introShown && SDL_GetTicks() < duration)
		{
			for (SDL_Texture* frameTexture : frameTextures)
			{
				SDL_RenderCopy(renderer, frameTexture, NULL, NULL);
				SDL_RenderPresent(renderer);
				SDL_Delay(frameDuration);
			}
		}

		// Libera las texturas
		for (SDL_Texture* frameTexture : frameTextures)
		{
			SDL_DestroyTexture(frameTexture);
		}

		// Restaura el tamaño de la ventana del juego principal
		SDL_SetWindowSize(window, width, height);
		SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
		introShown = true;

		assets->AddTexture("menu", "assets/menu1.png");

		// Mostrar la intro
		for (SDL_Texture* frameTexture : frameTextures)
		{
			SDL_RenderCopy(renderer, frameTexture, NULL, NULL);
			SDL_RenderPresent(renderer);
			SDL_Delay(frameDuration);
		}

		// Mostrar la imagen del menú después de la intro
		SDL_Texture* menuTexture = assets->GetTexture("menu");
		if (menuTexture)
		{
			while (true)  // Bucle hasta que se haga clic
			{
				SDL_RenderCopy(renderer, menuTexture, NULL, NULL);

				SDL_RenderPresent(renderer);

				SDL_PollEvent(&event);

				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
				{
					int mouseX, mouseY;
					SDL_GetMouseState(&mouseX, &mouseY);

					// Comprobar si el clic ocurrió en el medio de la pantalla
					if (mouseX >= (width / 2 - 150) && mouseX <= (width / 2 + -10) &&
						mouseY >= (height / 2 + 40) && mouseY <= (height / 2 + 110))
					{

						break;
					}
					if (mouseX >= (width / 2 + 20) && mouseX <= (width / 2 + 160) &&
						mouseY >= (height / 2 + 40) && mouseY <= (height / 2 + 110))
					{
						Game::isRunning = false;
						break;
					}
				}

				SDL_Delay(16);
			}
		}

		// Mostrar la intro
		for (SDL_Texture* frameTexture : frameTextures)
		{
			SDL_RenderCopy(renderer, frameTexture, NULL, NULL);
			SDL_RenderPresent(renderer);
			SDL_Delay(frameDuration);
		}
		*/


	assets->AddTexture("terrain", "assets/terrain_ss2.png");
	assets->AddTexture("player", "assets/test5.png");
	assets->AddTexture("projectile", "assets/proj.png");
	assets->AddTexture("npc", "assets/doc4.png");
	assets->AddFont("arial", "assets/arial.ttf", 16);
	assets->AddTexture("menu", "assets/menu.png");

	map = new Map("terrain", 2, 32);
	map->LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(800.0f, 640.0f, 42, 31.5, 2.5);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	

	

	npc.addComponent<TransformComponent>(800.0f, 640.0f, 64, 56, 2);
	npc.addComponent<SpriteComponentt>("npc", true);
	npc.addComponent<ColliderComponent>("npc");
	npc.addGroup(groupnpc);
	SDL_Color white = { 255, 255, 255, 255 };
	
	int buttonX = 100;
	int buttonY = 100;
	int buttonWidth = 200;
	int buttonHeight = 50;
	float buttonScale = 1.0f;

	playButton.addComponent<TransformComponent>(buttonX, buttonY, buttonWidth, buttonHeight, buttonScale);
	playButton.addComponent<SpriteComponent>("menu", true);  // Utiliza el nombre de la textura del menú
	buttons.push_back(&playButton);

	label.addComponent<UILabel>(10, 10, "Test String", "arial", white);
	Vector2D npcPos = npc.getComponent<TransformComponent>().position;
	textEntity.addComponent<UILabel>(20, 20, "Hello, World!", "arial", white);


}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& npcs(manager.getGroup(Game::groupnpc));



void Game::handleNPCInteraction()
{

	SDL_Color white = { 255, 255, 255, 255 };
	textEntity.addComponent<TransformComponent>(900.0f, 700.0f, 32, 32, 4);
	textEntity.getComponent<UILabel>().SetLabelText("Hola, ¿crees poder pasar mi examen?", "arial");
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
	{
		assets->AddTexture("test", "assets/test.png");
		SDL_Texture* menuTexture = assets->GetTexture("test");

		if (menuTexture)
		{
			std::cout << "Texture loaded successfully!" << std::endl;

			bool waitForClick = true;

			while (waitForClick)
			{
				SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
				SDL_RenderPresent(renderer);

				SDL_PollEvent(&event);

				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
				{
					waitForClick = false;
				}
			}
		}
		else
		{
			std::cerr << "Error loading texture!" << std::endl;
		}
	}


	check = true;
}


void Game::handleEvents()
{
	
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;

		break;
	default:
		break;
	}
	
}



void Game::update()
{	

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	SDL_Rect npcCol = npc.getComponent<ColliderComponent>().collider;

	std::stringstream ss;
	ss << "Player position: " << playerPos;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");
	manager.refresh();
	manager.update();

	TTF_Font* Sans = TTF_OpenFont("assets/arial.ttf", 24); 
	SDL_Color White = { 255, 255, 255 };
	

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& button : buttons)
	{
		button->update();
	}

	for (auto& a : npcs)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, a->getComponent<ColliderComponent>().collider))
		{
			handleNPCInteraction();
		}
	}
	
	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Hit player!" << std::endl;
			p->destroy();
		}
	}

	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}

void Game::render()
{
	SDL_RenderClear(renderer);


	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& a : npcs)
	{
		a->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

	for (auto& button : buttons)
	{
		button->draw();
	}

	label.draw();
	if (check)
	{
		textEntity.getComponent<UILabel>().draw();
	}
	check = false;

	SDL_RenderPresent(renderer);
}


void Game::clean()
{

	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();

}