#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "main.h"
#include "physics.h"

int main(int argc, char* argv[]) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;
	SDL_Rect rect = { 420, 320 , 100, 100 };
	SDL_Rect rectb = { 530, 320 , 100, 100 };
	int x = 880;
	int y = 640;
	int play = 1, pressa = 0, pressb = 0;
	int tick_a = 0, tick_f = 0;

	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow("Phisics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "Impossible de charger le mode video : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		fprintf(stderr, "Erreur lors de la création d'un renderer : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	while (play) {
		tick_a = SDL_GetTicks();
		if (tick_a - tick_f >= 10) { draw(renderer, rect, rectb); tick_f = tick_a; }
		evenement(window, &event, &play, &pressa, &pressb, rect, rectb);
		
		if (pressa == 1) {
			rect.y = event.motion.y - rect.h / 2;
			rect.x = event.motion.x - rect.w / 2;
		}else
		{
			if (pressb == 1) {
				rectb.y = event.motion.y - rectb.h / 2;
				rectb.x = event.motion.x - rectb.w / 2;
			}
		}
		physics(&rect,&rectb);
		SDL_RenderPresent(renderer);

	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;
}

void draw(SDL_Renderer* renderer, SDL_Rect rect, SDL_Rect rectb) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 250);
	SDL_RenderDrawRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 250);
	SDL_RenderDrawRect(renderer, &rectb);
}

void evenement(SDL_Window* window, SDL_Event* event, int* play, int* pressa, int* pressb, SDL_Rect rect, SDL_Rect rectb) {
	SDL_PollEvent(event);
	//SDL_WaitEvent(event);
	switch (event->type)
	{
	case SDL_QUIT:
		*play = 0;
		break;
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			*play = 0;
			break;
		}
	case SDL_MOUSEBUTTONDOWN:
		switch (event->button.button)
		{
		case SDL_BUTTON_LEFT:
			if (pos_m(*event, &rect) == 1) {
				*pressa = 1;
				break;
			}else
			{
				if (pos_m(*event, &rectb) == 1) {
					*pressb = 1;
					break;
				}
			}
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		*pressa = 0;
		*pressb = 0;
		break;
	}
}