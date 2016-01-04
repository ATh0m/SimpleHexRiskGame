#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void draw_filled_hex( SDL_Renderer *renderer, int x, int y, int size );

void draw_hex( SDL_Renderer *renderer, int x, int y, int size );

SDL_Window *create_window ( int width, int height );

SDL_Renderer *crete_renderer ( SDL_Window *window );

typedef struct Field
{
	int owner;
	int force;
} Field;

typedef struct Board
{
	Field **fields;
	int field_size;
	int width, height;
} Board;

Board *create_board(int cols, int rows, int tab[cols][rows]);

void draw_board( SDL_Renderer *renderer, Board *board );

void draw ( SDL_Renderer *renderer, Board *board );


int main ( int argc, char** argv )
{
	
	SDL_Window *window = create_window( 640, 480 );
	SDL_Renderer *renderer = crete_renderer( window );
	
	int quit = false;
	SDL_Event e;
	
	int tab[5][4] = {{1, 1, 0, 1}, {1, 0, 0, 1}, {1, 1, 1, 1}, {1, 0, 1, 0}, {1, 0, 1, 0}};
	Board *board = create_board(5, 4, tab);
	
	while ( !quit ) 
	{
		
		while( SDL_PollEvent( &e ) != 0 ) 
		{
			if( e.type == SDL_QUIT ) 
			{
				quit = true;
			}
		}
		
		draw( renderer, board );
		
		SDL_Delay( 10 );	
	}

	SDL_DestroyWindow( window) ;
	SDL_Quit();

	return EXIT_SUCCESS;
}

Board *create_board(int cols, int rows, int tab[cols][rows]) 
{
	Board *new_board = malloc(sizeof(Board));
	
	new_board->fields = malloc(cols * sizeof(*new_board->fields));
	for( int x = 0; x < cols; x++) new_board->fields[x] = malloc(rows * sizeof(*new_board->fields[x]));
	
	new_board->width = cols;
	new_board->height = rows;
	
	for (int x = 0; x < new_board->width; x++) {
		for (int y = 0; y < new_board->height; y++) {
			new_board->fields[x][y].force = 0;
			new_board->fields[x][y].owner = tab[x][y] == 1 ? 0 : -1;
		}
	}
	
	return new_board;
}

void draw_filled_hex( SDL_Renderer *renderer, int x, int y, int size ) 
{

	const short vx[6] = { x - size, x - size, x, x + size, x + size, x };
	const short vy[6] = { y + size * 0.5, y - size * 0.5, y - size, y - size * 0.5, y + size * 0.5, y + size };

	filledPolygonRGBA( renderer, vx, vy, 6, 128, 128, 128, 255 );
}

void draw_hex( SDL_Renderer *renderer, int x, int y, int size ) 
{
	const short vx[6] = { x - size, x - size, x, x + size, x + size, x };
	const short vy[6] = { y + size * 0.5, y - size * 0.5, y - size, y - size * 0.5, y + size * 0.5, y + size };

	short last_x = vx[5];
	short last_y = vy[5];

	for ( int i = 0; i < 6; i++ )
	{
		thickLineRGBA (renderer, last_x, last_y, vx[i], vy[i], 5, 255, 51, 51, 255);

		last_x = vx[i];
		last_y = vy[i];
	}
}

void draw_board( SDL_Renderer *renderer, Board *board ) 
{

	int w, h;
	SDL_GetRendererOutputSize( renderer, &w, &h );
	board->field_size = h * 2 / (1 + 3 * board->width);

	for (int x = 0; x < board->width; x++) 
	{
		for (int y = 0; y < board->height; y++) 
		{
			if (board->fields[x][y].owner >= 0) 
			{
				int hy = y * board->field_size * 3 / 2 + board->field_size;
				int hx = 2 * board->field_size * x + board->field_size;
				if (y % 2 == 1) hx += board->field_size;

				draw_filled_hex( renderer, hx, hy, board->field_size - 2 );
				if (x == 2 && y == 3) draw_hex( renderer, hx, hy, board->field_size );
			}
		}
	}
}

void draw ( SDL_Renderer *renderer, Board *board ) 
{
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderClear( renderer );

	draw_board( renderer, board );

	SDL_RenderPresent( renderer );
}

SDL_Window *create_window ( int width, int height ) 
{
	SDL_Window* window = NULL;

	window = SDL_CreateWindow
	(
		"SimpleHexRiskGame", 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_SHOWN
	);

	return window;
}

SDL_Renderer *crete_renderer ( SDL_Window *window ) 
{
	SDL_Renderer* renderer = NULL;
	renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

	return renderer;
}
