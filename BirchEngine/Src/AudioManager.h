#include "SDL_mixer.h"
#include "SDL.h"
#include <stdio.h>

class AudioManager {
public:
	AudioManager() {
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
			// Manejar el error al inicializar SDL
			printf("Error al inicializar SDL: %s\n", SDL_GetError());
			exit(1);
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			// Manejar el error al inicializar SDL_mixer
			printf("Error al inicializar SDL_mixer: %s\n", Mix_GetError());
			SDL_Quit();
			exit(1);
		}
	}

	~AudioManager() {
		Mix_CloseAudio();
		SDL_Quit();
	}

	void reproducirMusica(const char* rutaMusica) {
		musica = Mix_LoadMUS(rutaMusica);
		if (musica == nullptr) {
			printf("Error al cargar la música: %s\n", Mix_GetError());
			exit(1);
		}

		Mix_PlayMusic(musica, -1);
	}

	void reproducirEfectoSonido(const char* rutaEfecto) {
		Mix_Chunk* efectoSonido = Mix_LoadWAV(rutaEfecto);
		if (efectoSonido == nullptr) {
			printf("Error al cargar el efecto de sonido: %s\n", Mix_GetError());
			exit(1);
		}

		Mix_PlayChannel(-1, efectoSonido, 0);

		// Liberar el recurso después de reproducir
		Mix_FreeChunk(efectoSonido);
	}

private:
	Mix_Music* musica;
};