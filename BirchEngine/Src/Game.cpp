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
#include "preguntas.h"
#include "AudioManager.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Texture* videoTexture = nullptr;

SDL_Rect Game::camera = { 0,0,800,600 };

SDL_Rect Game::Message_rect = { 0, 0, 0, 0 };

AssetManager* Game::assets = new AssetManager(&manager);

AudioManager audioManager;

int width;
int height;

bool check = false;
bool Game::isRunning = false;
bool introShown = false;
bool npc1 = true;
bool npc22 = true;
bool npc33 = true;
bool npc44 = true;
TTF_Font* font = nullptr;



auto& player(manager.addEntity());
auto& label(manager.addEntity());
auto& npc(manager.addEntity());
auto& npc2(manager.addEntity());
auto& npc3(manager.addEntity());
auto& npc4(manager.addEntity());
auto& textEntity(manager.addEntity());
auto& playButton(manager.addEntity());
auto& tex(manager.addEntity());
auto& fixedImage(manager.addEntity());
auto& text1(manager.addEntity());
auto& opcion1(manager.addEntity());
auto& opcion2(manager.addEntity());
auto& opcion3(manager.addEntity());
auto& opcion4(manager.addEntity());
auto& salud(manager.addEntity());
auto& salud2(manager.addEntity());
auto& win(manager.addEntity());
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


	int totalFrames = 0;

	std::vector<std::string> animationFrames;
	std::vector<SDL_Texture*> frameTextures;

	for (int i = 1; i <= 86; ++i)
	{
		std::string framePath = "assets/frames/ezgif-frame-" + std::to_string(i) + ".png";
		std::cout << "Loading frame: " << framePath << std::endl;
		SDL_Surface* frameSurface = IMG_Load(framePath.c_str());

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
		audioManager.reproducirMusica("assets/SourGrapes-Mapa.mp3");
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
					audioManager.reproducirMusica("assets/Click.mp3");
					break;
				}
				if (mouseX >= (width / 2 + 20) && mouseX <= (width / 2 + 160) &&
					mouseY >= (height / 2 + 40) && mouseY <= (height / 2 + 110))
				{
					Game::isRunning = false;
					break;
				}
			}


		}
		Mix_HaltMusic();
	}

	// Mostrar la intro
	for (SDL_Texture* frameTexture : frameTextures)
	{
		SDL_RenderCopy(renderer, frameTexture, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(frameDuration);
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	audioManager.reproducirMusica("assets/SourGrapes-Mapa.mp3");

	assets->AddTexture("terrain", "assets/terrain_ss2.png");
	assets->AddTexture("player", "assets/test5.png");
	assets->AddTexture("projectile", "assets/proj.png");
	assets->AddTexture("npc", "assets/doc4.png");
	assets->AddTexture("npc2", "assets/doc11.png");
	assets->AddTexture("npc3", "assets/doc12.png");
	assets->AddTexture("npc4", "assets/doc13.png");
	assets->AddFont("arial", "assets/arial.ttf", 16);
	assets->AddFont("pokemon", "assets/Pokemon Classic.ttf", 16);
	assets->AddTexture("menu", "assets/menu.png");

	map = new Map("terrain", 2, 32);
	map->LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(760.0f, 1100.0f, 42, 31.5, 2.5);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);



	npc.addComponent<TransformComponent>(760.0f, 640.0f, 64, 56, 2);
	npc.addComponent<SpriteComponentt>("npc", true);
	npc.addComponent<ColliderComponent>("npc");
	npc.addGroup(groupnpc);
	npc2.addComponent<TransformComponent>(200.0f, 180.0f, 64, 56, 2);
	npc2.addComponent<SpriteComponentt>("npc2", true);
	npc2.addComponent<ColliderComponent>("npc2");
	npc2.addGroup(groupnpc2);
	npc3.addComponent<TransformComponent>(1200.0f, 200.0f, 64, 56, 2);
	npc3.addComponent<SpriteComponentt>("npc3", true);
	npc3.addComponent<ColliderComponent>("npc3");
	npc3.addGroup(groupnpc3);
	npc4.addComponent<TransformComponent>(1250.0f, 1000.0f, 64, 56, 2);
	npc4.addComponent<SpriteComponentt>("npc4", true);
	npc4.addComponent<ColliderComponent>("npc4");
	npc4.addGroup(groupnpc4);

	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Color black = { 0, 0, 0, 0 };
	int buttonX = 100;
	int buttonY = 100;
	int buttonWidth = 200;
	int buttonHeight = 50;
	float buttonScale = 1.0f;

	playButton.addComponent<TransformComponent>(buttonX, buttonY, buttonWidth, buttonHeight, buttonScale);
	playButton.addComponent<SpriteComponent>("menu", true);
	buttons.push_back(&playButton);

	label.addComponent<UILabel>(10, 10, "Test String", "arial", white);
	Vector2D npcPos = npc.getComponent<TransformComponent>().position;
	textEntity.addComponent<UILabel>(180, 20, "Hello, World!", "pokemon", white);
	text1.addComponent<UILabel>(35, 510, "Hello, World!", "pokemon", black);
	opcion1.addComponent<UILabel>(420, 500, "Hello, World!", "pokemon", black);
	opcion2.addComponent<UILabel>(620, 500, "Hello, World!", "pokemon", black);
	opcion3.addComponent<UILabel>(420, 570, "Hello, World!", "pokemon", black);
	opcion4.addComponent<UILabel>(620, 570, "Hello, World!", "pokemon", black);
	salud.addComponent<UILabel>(530, 380, "Hello, World!", "pokemon", black);
	salud2.addComponent<UILabel>(75, 120, "Hello, World!", "pokemon", black);
	win.addComponent<UILabel>(180, 20, "Hello, World!", "pokemon", white);
	assets->AddTexture("menu", "assets/menu.png");

	fixedImage.addComponent<TransformComponent>(400.0f, 300.0f, 200, 150, 1.0f);
	fixedImage.addComponent<SpriteComponent>("person", true);
	fixedImage.addComponent<ColliderComponent>("fixedImage");
	fixedImage.addGroup(groupUI);


}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& npcs(manager.getGroup(Game::groupnpc));
auto& npcs2(manager.getGroup(Game::groupnpc2));
auto& npcs3(manager.getGroup(Game::groupnpc3));
auto& npcs4(manager.getGroup(Game::groupnpc4));



void Game::handleNPCInteraction()
{

	SDL_Color white = { 255, 255, 255, 255 };
	int salud_jugador = 20;
	int salud_oponente = 20;
	int  restar, daño, op;
	textEntity.addComponent<TransformComponent>(900.0f, 700.0f, 32, 32, 4);
	textEntity.getComponent<UILabel>().SetLabelText("Hola, ¿crees poder pasar mi examen?", "pokemon");
	win.addComponent<TransformComponent>(900.0f, 700.0f, 32, 32, 4);
	win.getComponent<UILabel>().SetLabelText("Me ganaste ¿cómo lo hiciste?", "pokemon");
	if (npc1)
	{


		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		{

			srand(time(NULL));
			Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
			audioManager.reproducirMusica("assets/Panorama.mp3");
			assets->AddTexture("test", "assets/test.png");
			SDL_SetWindowSize(window, width, height);
			SDL_Texture* menuTexture = assets->GetTexture("test");

			if (menuTexture) {
				//inicio:
				bool waitForClick = true;
				bool ti = true;
				while (waitForClick)
				{
					if (ti)
					{
						op = rand() % 27;
						ti = false;
					}
					SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
					text1.getComponent<UILabel>().SetLabelTextt(preguntasGeografia[op].enunciado, "pokemon");
					text1.getComponent<UILabel>().draw();
					opcion1.getComponent<UILabel>().SetLabelTexttt(preguntasGeografia[op].opciones[0], "pokemon");
					opcion1.getComponent<UILabel>().draw();
					opcion2.getComponent<UILabel>().SetLabelTexttt(preguntasGeografia[op].opciones[1], "pokemon");
					opcion2.getComponent<UILabel>().draw();
					opcion3.getComponent<UILabel>().SetLabelTexttt(preguntasGeografia[op].opciones[2], "pokemon");
					opcion3.getComponent<UILabel>().draw();
					opcion4.getComponent<UILabel>().SetLabelTexttt(preguntasGeografia[op].opciones[3], "pokemon");
					opcion4.getComponent<UILabel>().draw();
					std::string cadena = std::to_string(salud_jugador);
					salud.getComponent<UILabel>().SetLabelTexttt(cadena, "pokemon");
					salud.getComponent<UILabel>().draw();
					std::string cadena2 = std::to_string(salud_oponente);
					salud2.getComponent<UILabel>().SetLabelTexttt(cadena2, "pokemon");
					salud2.getComponent<UILabel>().draw();
					int res = preguntasGeografia[op].respuestaCorrecta + 1;
					SDL_RenderPresent(renderer);
					SDL_PollEvent(&event);
					if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
						case SDLK_1:
							if (1 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc1 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;
								}
							}
							ti = true;
							break;
						case SDLK_2:
							if (2 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc1 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;
								}
							}
							ti = true;
							break;
						case SDLK_3:
							if (3 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc1 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;


								}
							}
							ti = true;
							break;
						case SDLK_4:
							if (4 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc1 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;
								}
							}
							ti = true;
							break;
						default:
							break;
						}
					}
					SDL_Delay(16);
				}
			}
		}

		audioManager.reproducirMusica("assets/SourGrapes-Mapa.mp3");

		check = true;

	}

}


/////////////////////////////////////////////////////////////////////////////////

void Game::handleNPCInteractionn()
{
	SDL_Color white = { 255, 255, 255, 255 };
	int salud_jugador = 20;
	int salud_oponente = 20;
	int  restar, daño, op;
	textEntity.addComponent<TransformComponent>(900.0f, 700.0f, 32, 32, 4);
	textEntity.getComponent<UILabel>().SetLabelText("Hola, ¿crees poder pasar mi examen?", "pokemon");
	win.addComponent<TransformComponent>(900.0f, 700.0f, 32, 32, 4);
	win.getComponent<UILabel>().SetLabelText("Me ganaste ¿cómo lo hiciste?", "pokemon");
	if (npc22)
	{

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		{
			Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
			audioManager.reproducirMusica("assets/Panorama.mp3");
			srand(time(NULL));

			assets->AddTexture("test", "assets/test.png");
			SDL_SetWindowSize(window, width, height);
			SDL_Texture* menuTexture = assets->GetTexture("test");

			if (menuTexture) {
				//inicio:
				bool waitForClick = true;
				bool ti2 = true;
				while (waitForClick)
				{
					if (ti2)
					{
						op = rand() % 27;
						ti2 = false;
					}
					SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
					text1.getComponent<UILabel>().SetLabelTextt(preguntasCienciasNaturales[op].enunciado, "pokemon");
					text1.getComponent<UILabel>().draw();
					opcion1.getComponent<UILabel>().SetLabelTexttt(preguntasCienciasNaturales[op].opciones[0], "pokemon");
					opcion1.getComponent<UILabel>().draw();
					opcion2.getComponent<UILabel>().SetLabelTexttt(preguntasCienciasNaturales[op].opciones[1], "pokemon");
					opcion2.getComponent<UILabel>().draw();
					opcion3.getComponent<UILabel>().SetLabelTexttt(preguntasCienciasNaturales[op].opciones[2], "pokemon");
					opcion3.getComponent<UILabel>().draw();
					opcion4.getComponent<UILabel>().SetLabelTexttt(preguntasCienciasNaturales[op].opciones[3], "pokemon");
					opcion4.getComponent<UILabel>().draw();
					std::string cadena = std::to_string(salud_jugador);
					salud.getComponent<UILabel>().SetLabelTexttt(cadena, "pokemon");
					salud.getComponent<UILabel>().draw();
					std::string cadena2 = std::to_string(salud_oponente);
					salud2.getComponent<UILabel>().SetLabelTexttt(cadena2, "pokemon");
					salud2.getComponent<UILabel>().draw();
					int res = preguntasCienciasNaturales[op].respuestaCorrecta + 1;
					SDL_RenderPresent(renderer);
					SDL_PollEvent(&event);
					if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
						case SDLK_1:
							if (1 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc22 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;
								}
							}
							ti2 = true;
							break;
						case SDLK_2:
							if (2 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc22 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;
								}
							}
							ti2 = true;
							break;
						case SDLK_3:
							if (3 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc22 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;


								}
							}
							ti2 = true;
							break;
						case SDLK_4:
							if (4 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc22 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;
								}
							}
							ti2 = true;
							break;
						default:
							break;
						}
					}

					Mix_HaltMusic();

					SDL_Delay(16);
				}
			}
		}

		audioManager.reproducirMusica("assets/SourGrapes-Mapa.mp3");


		check = true;

	}
}

void Game::handleNPCInteractionnn()
{
	SDL_Color white = { 255, 255, 255, 255 };
	int salud_jugador = 20;
	int salud_oponente = 20;
	int  restar, daño, op;
	textEntity.addComponent<TransformComponent>(900.0f, 700.0f, 32, 32, 4);
	textEntity.getComponent<UILabel>().SetLabelText("Hola, ¿crees poder pasar mi examen?", "pokemon");
	win.addComponent<TransformComponent>(900.0f, 700.0f, 32, 32, 4);
	win.getComponent<UILabel>().SetLabelText("Me ganaste ¿cómo lo hiciste?", "pokemon");
	if (npc33)
	{

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		{
			Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
			audioManager.reproducirMusica("assets/Panorama.mp3");
			srand(time(NULL));

			assets->AddTexture("test", "assets/test.png");
			SDL_SetWindowSize(window, width, height);
			SDL_Texture* menuTexture = assets->GetTexture("test");

			if (menuTexture) {
				//inicio:
				bool waitForClick = true;
				bool ti3 = true;
				while (waitForClick)
				{
					if (ti3)
					{
						op = rand() % 27;
						ti3 = false;
					}
					SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
					text1.getComponent<UILabel>().SetLabelTextt(preguntasMatematicas[op].enunciado, "pokemon");
					text1.getComponent<UILabel>().draw();
					opcion1.getComponent<UILabel>().SetLabelTexttt(preguntasMatematicas[op].opciones[0], "pokemon");
					opcion1.getComponent<UILabel>().draw();
					opcion2.getComponent<UILabel>().SetLabelTexttt(preguntasMatematicas[op].opciones[1], "pokemon");
					opcion2.getComponent<UILabel>().draw();
					opcion3.getComponent<UILabel>().SetLabelTexttt(preguntasMatematicas[op].opciones[2], "pokemon");
					opcion3.getComponent<UILabel>().draw();
					opcion4.getComponent<UILabel>().SetLabelTexttt(preguntasMatematicas[op].opciones[3], "pokemon");
					opcion4.getComponent<UILabel>().draw();
					std::string cadena = std::to_string(salud_jugador);
					salud.getComponent<UILabel>().SetLabelTexttt(cadena, "pokemon");
					salud.getComponent<UILabel>().draw();
					std::string cadena2 = std::to_string(salud_oponente);
					salud2.getComponent<UILabel>().SetLabelTexttt(cadena2, "pokemon");
					salud2.getComponent<UILabel>().draw();
					int res = preguntasMatematicas[op].respuestaCorrecta + 1;
					SDL_RenderPresent(renderer);
					SDL_PollEvent(&event);
					if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
						case SDLK_1:
							if (1 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc33 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;
								}
							}
							ti3 = true;
							break;
						case SDLK_2:
							if (2 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc33 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;
								}
							}
							ti3 = true;
							break;
						case SDLK_3:
							if (3 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc33 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;


								}
							}
							ti3 = true;
							break;
						case SDLK_4:
							if (4 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc33 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;
								}
							}
							ti3 = true;
							break;
						default:
							break;
						}
					}

					Mix_HaltMusic();

					SDL_Delay(16);
				}
			}
		}

		audioManager.reproducirMusica("assets/SourGrapes-Mapa.mp3");


		check = true;

	}
}

void Game::handleNPCInteractionnnn()
{
	SDL_Color white = { 255, 255, 255, 255 };
	int salud_jugador = 20;
	int salud_oponente = 20;
	int  restar, daño, op;
	textEntity.addComponent<TransformComponent>(900.0f, 700.0f, 32, 32, 4);
	textEntity.getComponent<UILabel>().SetLabelText("Hola, ¿crees poder pasar mi examen?", "pokemon");
	win.addComponent<TransformComponent>(900.0f, 700.0f, 32, 32, 4);
	win.getComponent<UILabel>().SetLabelText("Me ganaste ¿cómo lo hiciste?", "pokemon");
	if (npc44)
	{

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		{
			Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
			audioManager.reproducirMusica("assets/Panorama.mp3");
			srand(time(NULL));

			assets->AddTexture("test", "assets/test.png");
			SDL_SetWindowSize(window, width, height);
			SDL_Texture* menuTexture = assets->GetTexture("test");

			if (menuTexture) {
				//inicio:
				bool waitForClick = true;
				bool ti4 = true;
				while (waitForClick)
				{
					if (ti4)
					{
						op = rand() % 27;
						ti4 = false;
					}

					SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
					text1.getComponent<UILabel>().SetLabelTextt(preguntasHistoriaMexico[op].enunciado, "pokemon");
					text1.getComponent<UILabel>().draw();
					opcion1.getComponent<UILabel>().SetLabelTexttt(preguntasHistoriaMexico[op].opciones[0], "pokemon");
					opcion1.getComponent<UILabel>().draw();
					opcion2.getComponent<UILabel>().SetLabelTexttt(preguntasHistoriaMexico[op].opciones[1], "pokemon");
					opcion2.getComponent<UILabel>().draw();
					opcion3.getComponent<UILabel>().SetLabelTexttt(preguntasHistoriaMexico[op].opciones[2], "pokemon");
					opcion3.getComponent<UILabel>().draw();
					opcion4.getComponent<UILabel>().SetLabelTexttt(preguntasHistoriaMexico[op].opciones[3], "pokemon");
					opcion4.getComponent<UILabel>().draw();
					std::string cadena = std::to_string(salud_jugador);
					salud.getComponent<UILabel>().SetLabelTexttt(cadena, "pokemon");
					salud.getComponent<UILabel>().draw();
					std::string cadena2 = std::to_string(salud_oponente);
					salud2.getComponent<UILabel>().SetLabelTexttt(cadena2, "pokemon");
					salud2.getComponent<UILabel>().draw();
					int res = preguntasHistoriaMexico[op].respuestaCorrecta + 1;
					SDL_RenderPresent(renderer);
					SDL_PollEvent(&event);
					if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
						case SDLK_1:
							if (1 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc44 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;
								}
							}
							ti4 = true;
							break;
						case SDLK_2:
							if (2 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc44 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;
								}
							}
							ti4 = true;
							break;
						case SDLK_3:
							if (3 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc44 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;


								}
							}
							ti4 = true;
							break;
						case SDLK_4:
							if (4 == res)
							{
								restar = rand() % 5 + 1;
								salud_oponente -= restar;
								if (salud_oponente <= 0)
								{
									waitForClick = false;
									npc44 = false;

								}

							}
							else
							{
								restar = rand() % 5 + 1;
								salud_jugador -= restar;
								if (salud_jugador <= 0)
								{
									waitForClick = false;
								}
							}
							ti4 = true;
							break;
						default:
							break;
						}
					}

					Mix_HaltMusic();

					SDL_Delay(16);
				}
			}
		}



		audioManager.reproducirMusica("assets/SourGrapes-Mapa.mp3");

		check = true;

	}
}

void Game::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
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
	SDL_Rect npcCol2 = npc2.getComponent<ColliderComponent>().collider;
	SDL_Rect npcCol3 = npc3.getComponent<ColliderComponent>().collider;
	SDL_Rect npcCol4 = npc4.getComponent<ColliderComponent>().collider;

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
	for (auto& u : npcs2)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, u->getComponent<ColliderComponent>().collider))
		{
			handleNPCInteractionn();
		}
	}
	for (auto& i : npcs3)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, i->getComponent<ColliderComponent>().collider))
		{
			handleNPCInteractionnn();
		}
		for (auto& o : npcs4)
		{
			if (Collision::AABB(player.getComponent<ColliderComponent>().collider, o->getComponent<ColliderComponent>().collider))
			{
				handleNPCInteractionnnn();
			}
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
	for (auto& u : npcs2)
	{
		u->draw();
	}
	for (auto& i : npcs3)
	{
		i->draw();
	}
	for (auto& o : npcs4)
	{
		o->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}



	fixedImage.draw();

	//label.draw();
	if (check)
	{
		if (npc1)
		{
			textEntity.getComponent<UILabel>().draw();

		}
		else
		{

			win.getComponent<UILabel>().draw();

		}

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