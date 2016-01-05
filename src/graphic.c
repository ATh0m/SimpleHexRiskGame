#include "graphic.h"

SDL_Window* create_window(int width, int height)
{
	SDL_Window* window = NULL;

	window = SDL_CreateWindow(
		"SimpleHexRiskGame",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_SHOWN);

	return window;
}

SDL_Renderer* crete_renderer(SDL_Window* window)
{
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	return renderer;
}

void draw_filled_hex(SDL_Renderer* renderer, int x, int y, int size, Color color)
{

	const short vx[6] = { x - size, x - size, x, x + size, x + size, x };
	const short vy[6] = { y + size * 0.5, y - size * 0.5, y - size, y - size * 0.5, y + size * 0.5, y + size };

	//filledPolygonRGBA( renderer, vx, vy, 6, 128, 128, 128, 255 );
	filledPolygonRGBA(renderer, vx, vy, 6, color.r, color.g, color.b, color.a);
}

void draw_hex(SDL_Renderer* renderer, int x, int y, int size, Color color)
{
	const short vx[6] = { x - size, x - size, x, x + size, x + size, x };
	const short vy[6] = { y + size * 0.5, y - size * 0.5, y - size, y - size * 0.5, y + size * 0.5, y + size };

	short last_x = vx[5];
	short last_y = vy[5];

	for (int i = 0; i < 6; i++) {
		// thickLineRGBA (renderer, last_x, last_y, vx[i], vy[i], 5, 255, 51, 51, 255);
		thickLineRGBA(renderer, last_x, last_y, vx[i], vy[i], 5, color.r, color.g, color.b, color.a);

		last_x = vx[i];
		last_y = vy[i];
	}
}

