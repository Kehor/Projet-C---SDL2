#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "main.h"

int main(int argc, char* argv[]) {
	SDL_Window* ecran = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;
	SDL_Surface* bmpsurface;
	SDL_Texture* tmario, *texture;
	int continuer = 1;
	int w = 1920;
	int h = 640;
	int press = 0;
	int hsol = 498;
	int fo = 0, ba = 0, dist = 0, fullscreen = 0;
	int tick_a = 0, tick_prev = 0;
	int i = 0, tableaux = 0;


	SDL_Init(SDL_INIT_VIDEO);

	ecran = SDL_CreateWindow("Mario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	SDL_SetWindowIcon(ecran, SDL_LoadBMP("icon.bmp"));
	renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	bmpsurface = SDL_LoadBMP("map.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, bmpsurface);
	SDL_Rect destmap = { 0, 0, bmpsurface->w , h };

	bmpsurface = SDL_LoadBMP("mario.bmp");
	tmario = SDL_CreateTextureFromSurface(renderer, bmpsurface);
	SDL_Rect dest = { 100, hsol - (bmpsurface->h/2), bmpsurface->w /DIV_TAILLE, bmpsurface->h /DIV_TAILLE };
	
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_WarpMouseInWindow(ecran, w / 2, h / 2);

	while (continuer)
	{
		tick_a = SDL_GetTicks();
			if (dest.y >= hsol) { dest.y = hsol; }
			if (dest.y < hsol && i == 0) { dest.y += 2; }
			if (press == 1) {
				dest.y = event.motion.y - dest.h / 2;
				dest.x = event.motion.x - dest.w / 2;
			}
			if (dest.y >= h - dest.h/2) { dest.y = 0 - dest.h/2; }else{ if(dest.y <= 0 - dest.h/2){ dest.y = h - dest.h/2; }}
			if (dest.x >= w - dest.w/2) { dest.x = 0 - dest.w/2; }else{ if(dest.x <= 0 - dest.w/2){ dest.x = w - dest.w/2; }}
			if ( i == 0 && dest.y < hsol && tick_a - tick_prev > 15 || i > 25 && dest.y < hsol && tick_a - tick_prev > 15 ) {
				dest.y += 0.3* (dest.h / 2);
				tick_prev = tick_a;
			}
			if(fo==1){
				if (dest.x < destmap.w / 4.5) {
					dest.x += 1 + (dest.w / (3 * DIV_TAILLE));
				}
				else
				{
					destmap.x -= 1 + (dest.w / (3 * DIV_TAILLE));
					if (destmap.x <= 0-destmap.w/2) {
						destmap.x = 1;
						tableaux += 1;
					}
				}
			}
			else {
				if (ba == 1) {
					if (dest.x > destmap.w / 6 || dest.x >= 10 && destmap.x >= 1) {
						dest.x -= 1 + (dest.w / (3 * DIV_TAILLE));
					}
					else
					{
						if (destmap.x <= 1) {
							destmap.x += 1 + (dest.w / (3 * DIV_TAILLE));
							
						}
					}
					if (destmap.x >= 1 && tableaux > 0) {
						destmap.x = 0 - (destmap.w / 2);
						tableaux -= 1;
					}
				} 
			}
			if (i >= 1) { 
				if (i<= 25) {
					if (tick_a - tick_prev > 15 && i < 16) {
						dest.y -= 0.4 *(dest.h / 3);
						tick_prev = tick_a;
						i += 1;
					}
					if (tick_a - tick_prev > 20 && i < 21) { 
						dest.y -= 0.3 * (dest.h / 3);
						tick_prev = tick_a;
						i += 1; 
					}
					if (tick_a - tick_prev > 20) {
						dest.y += 0.2 * (dest.h / 3);
						tick_prev = tick_a;
						i += 1;
					}
				}
				if (dest.y == hsol && i > 25) { i = 0; }
				/*else {
					if (i > 25 && dest.y < hsol) {
						if (dest.y <= hsol && tick_a - tick_prev > 15) {
							dest.y += 0.3* (dest.h / 2);
							tick_prev = tick_a;
						}
						i += 1;
					}
					else {
						if (dest.y != hsol || i >= 50) { i = 0; dest.y = hsol; }
					}
				}*/
			}
			//SDL_WaitEvent(&event);
			
			SDL_PollEvent(&event);
			switch (event.type)
			{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					continuer = 0;
					break;
				case SDLK_UP:
					if (i == 0) { i = 1; }
					break;
				case SDLK_DOWN:
					if (dest.y < hsol && dest.y < hsol -1) { dest.y += 4; }
					if (i > 10) { i = 0; }
					break;
				case SDLK_LEFT:
					if (ba == 0) { ba = 1; }
					break;
				case SDLK_RIGHT:
					if (fo == 0) { fo = 1; }
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
					if (fo == 1) { fo = 0; }
					break;
				case SDLK_LEFT:
					if (ba == 1) { ba = 0; }
					break;
				case SDLK_f:
					if (fullscreen == 0) {
						SDL_SetWindowFullscreen(ecran, SDL_WINDOW_FULLSCREEN);
						fullscreen = 1;
					}
					else
					{
						fullscreen = 0;
						SDL_SetWindowFullscreen(ecran, 0);
					}
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					dest.y = event.button.y - dest.h /2;
					dest.x = event.button.x - dest.w / 2;
					press = 1;
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				press = 0;
				break;
			case SDL_WINDOWEVENT: 
				switch (event.window.event) {

				case SDL_WINDOWEVENT_SIZE_CHANGED:
					if (event.key.keysym.sym == SDLK_f) {
						if (event.window.data1 != w) {
							dest.w += ((event.window.data1 - w) / DIV_TAILLE) / 2;
							dest.h += ((event.window.data1 - w) / DIV_TAILLE) / 2;
						}
						else if (event.window.data2 != h) {
							dest.h += ((event.window.data2 - h) / DIV_TAILLE) / 2;
							dest.w += ((event.window.data2 - h) / DIV_TAILLE) / 2;
							if (fullscreen) {
								destmap.h = (event.window.data2 / 2);
								hsol += ((event.window.data2 / 2 - h) / 1.22);
								dest.w /= 2;
								dest.h /= 2;
								dest.y = hsol;
							}
							else
							{
								destmap.h = (event.window.data2);
								hsol = ((event.window.data2 - h) / 1.3);
								dest.y = hsol;
							}
						}
						h = event.window.data2;
						w = event.window.data1;
					}
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					pause();
					break;
				}
				break;
			}
			if (event.type != SDL_QUIT) {
				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, texture, NULL, &destmap);
				SDL_RenderCopy(renderer, tmario, NULL, &dest);
				SDL_RenderPresent(renderer);
			}
	}
	
	SDL_DestroyWindow(ecran);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return EXIT_SUCCESS;
}

void pause() {
	SDL_Event event;
	int wait = 1;

	while (wait == 1) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_WINDOWEVENT:
			switch (event.window.event) {
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				wait = 0;
				break;
			case SDL_WINDOWEVENT_ENTER:
				wait = 0;
				break;
			}
		}
	}
}

