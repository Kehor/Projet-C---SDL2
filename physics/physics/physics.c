#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

void physics(SDL_Rect* rect_np, SDL_Rect* rect_p) {
	if (rect_p->x + rect_p->w <= rect_np->x + rect_np->w && rect_p->x + rect_p->w > rect_np->x&& rect_p->y +10 > rect_np->y && rect_p->y +10 < rect_np->y + rect_np->h && rect_p->x > 0 || rect_p->x + rect_p->w <= rect_np->x + rect_np->w && rect_p->x + rect_p->w > rect_np->x&& rect_p->y + rect_p->h -10 > rect_np->y && rect_p->y + rect_p->h -10 < rect_np->y + rect_np->h && rect_p->x > 0) { rect_p->x = rect_np->x - rect_p->w - 1;
	}
	else
	{
		if (rect_p->x <= rect_np->x + rect_np->w && rect_p->x > rect_np->x&& rect_p->y +10 > rect_np->y && rect_p->y +10 < rect_np->y + rect_np->h && rect_p->x > 0 || rect_p->x <= rect_np->x + rect_np->w && rect_p->x > rect_np->x&& rect_p->y + rect_p->h -10 > rect_np->y && rect_p->y + rect_p->h -10 < rect_np->y + rect_np->h && rect_p->x > 0) { rect_p->x = rect_np->x + rect_np->w + 1; }
	}
	if (rect_p->x + rect_p->w <= rect_np->x + rect_np->w && rect_p->x + rect_p->w > rect_np->x&& rect_p->y <= rect_np->y + rect_np->h && rect_p->y >= rect_np->y + rect_np->h -10 && rect_p->y > 0 || rect_p->x <= rect_np->x + rect_np->w && rect_p->x > rect_np->x&& rect_p->y <= rect_np->y + rect_np->h && rect_p->y >= rect_np->y + rect_np->h - 10 && rect_p->y > 0) {
		rect_p->y = rect_np->y + rect_np->h + 1;
	}
	else
	{
		if (rect_p->x + rect_p->w <= rect_np->x + rect_np->w && rect_p->x + rect_p->w > rect_np->x&& rect_p->y + rect_p->h >= rect_np->y && rect_p->y + rect_p->h <= rect_np->y +10 && rect_p->y > 0 || rect_p->x <= rect_np->x + rect_np->w && rect_p->x > rect_np->x&& rect_p->y + rect_p->h >= rect_np->y && rect_p->y + rect_p->h <= rect_np->y + 10 && rect_p->y > 0) { rect_p->y = rect_np->y - rect_p->h - 1; }
	}

	
}

int pos_m(SDL_Event event, SDL_Rect* rect) {
	if (event.motion.x >= rect->x && event.motion.x <= rect->x + rect->w && event.motion.y >= rect->y && event.motion.y <= rect->y + rect->h) {
		return 1;
	}
	else
	{
		return 0;
	}
}