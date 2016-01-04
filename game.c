#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Color{
	int r, g, b, a;
} Color;

void draw_filled_hex( SDL_Renderer *renderer, int x, int y, int size, Color color);

void draw_hex( SDL_Renderer *renderer, int x, int y, int size, Color color);

SDL_Window *create_window ( int width, int height );

SDL_Renderer *crete_renderer ( SDL_Window *window );

typedef struct Field
{
	int owner;
	int force;
} Field;

typedef struct Pair{
	int x, y;
} Pair;

enum Status {CREATE, START, REINFORCEMENT, MOVE};

typedef struct Board
{
	Field **fields;
	int width, height;
	
	int field_size;
	int field_width;
	int field_height;
	
	int offset_x;
	int offset_y;
	
	enum Status status;
	
	Pair hover_field;
} Board;

Board *create_board(int cols, int rows, int tab[cols][rows]);

void draw_board( SDL_Renderer *renderer, Board *board );

void draw ( SDL_Renderer *renderer, Board *board );

typedef struct Player{
	char *name;
	int id;
	
	bool active;
	bool ai;
	
	// TO DO List fields
	
	Color field_color;
	Color hover_color;
	Color action_color;
} Player;

bool is_actionable(Board *board, int x, int y, Player *player);

Color create_color(int r, int g, int b, int a) {
	Color new_color = {r, g, b, a};
	return new_color;
}

Pair point_to_field (int x, int y, Board *board) {
	Pair field;
	
    field.y = floor((y - board->offset_y) / board->field_height);
    field.x = floor(((field.y % 2 == 0 ? x : x - board->field_size) - board->offset_x) / board->field_width);
    
    return field;
}

Pair field_to_point (int x, int y, Board *board) {
	Pair point;
	
	point.y = y * board->field_height + board->field_height * 0.5 + board->offset_y;
	point.x = (y % 2 == 0 ? 0 : board->field_width * 0.5) + x * board->field_width + board->field_width * 0.5 + board->offset_x;
	
	return point;
}

int main ( int argc, char** argv )
{
	
	SDL_Window *window = create_window( 640, 480 );
	SDL_Renderer *renderer = crete_renderer( window );
	enum Status status;
	
	int quit = false;
	SDL_Event e;
	
	int tab[5][4] = {{1, 1, 0, 1}, {1, 0, 0, 1}, {1, 1, 1, 1}, {1, 0, 1, 0}, {1, 0, 1, 0}};
	Board *board = create_board(5, 4, tab);
	
	Player* players[3];
	
	players[0] = malloc(sizeof(Player));
	players[0]->name = strdup("Red");
	players[0]->id = 0;
	players[0]->active = false;
	players[0]->ai = false;
	players[0]->field_color = create_color(255, 255, 255, 255);
	players[0]->hover_color = create_color(0, 0, 0, 0);
	players[0]->action_color = create_color(0, 0, 0, 0);
	
	board->status = START;
	
	while ( !quit ) 
	{
		
		while( SDL_PollEvent( &e ) != 0 ) 
		{
			if( e.type == SDL_QUIT ) 
			{
				quit = true;
			}
			if ( e.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState( &x, &y );
				
				board->hover_field = point_to_field(x, y, board);
			}
		}
		
		draw( renderer, board );
		
		SDL_Delay( 10 );	
	}

	SDL_DestroyWindow( window) ;
	SDL_Quit();

	return EXIT_SUCCESS;
}

bool is_actionable(Board *board, int x, int y, Player *player) {
	if (x >= 0 && x < board->width && y >= 0 && y < board->height && board->fields[x][y].owner >= 0) {
		if(board->status == START) {
			if (board->fields[x][y].owner == 0) {
				return true;
			}
		}
	}
	
	return false;
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

void draw_filled_hex( SDL_Renderer *renderer, int x, int y, int size, Color color) 
{

	const short vx[6] = { x - size, x - size, x, x + size, x + size, x };
	const short vy[6] = { y + size * 0.5, y - size * 0.5, y - size, y - size * 0.5, y + size * 0.5, y + size };

	//filledPolygonRGBA( renderer, vx, vy, 6, 128, 128, 128, 255 );
	filledPolygonRGBA( renderer, vx, vy, 6, color.r, color.g, color.b, color.a );
}

void draw_hex( SDL_Renderer *renderer, int x, int y, int size, Color color) 
{
	const short vx[6] = { x - size, x - size, x, x + size, x + size, x };
	const short vy[6] = { y + size * 0.5, y - size * 0.5, y - size, y - size * 0.5, y + size * 0.5, y + size };

	short last_x = vx[5];
	short last_y = vy[5];

	for ( int i = 0; i < 6; i++ )
	{
		// thickLineRGBA (renderer, last_x, last_y, vx[i], vy[i], 5, 255, 51, 51, 255);
		thickLineRGBA (renderer, last_x, last_y, vx[i], vy[i], 5, color.r, color.g, color.b, color.a);

		last_x = vx[i];
		last_y = vy[i];
	}
}

void draw_board( SDL_Renderer *renderer, Board *board ) 
{

	int w, h;
	SDL_GetRendererOutputSize( renderer, &w, &h );
	board->field_size = w / (2 * (0.5 + board->width));
	
	board->field_width = board->field_size * 2;
	board->field_height = board->field_width * 0.75;
	
	board->offset_x = (w - board->width * board->field_width - board->field_width * 0.5) * 0.5;
	board->offset_y = board->field_width * 0.125;

	for (int x = 0; x < board->width; x++) 
	{
		for (int y = 0; y < board->height; y++) 
		{
			if (board->fields[x][y].owner >= 0) 
			{
				// int hy = y * board->field_size * 3 / 2 + board->field_size;
				// int hx = 2 * board->field_size * x + board->field_size;
				// if (y % 2 == 1) hx += board->field_size;
				
				Color color = {128, 128, 128, 255};
				
				Pair point = field_to_point(x, y, board);
				draw_filled_hex( renderer, point.x, point.y, board->field_size - 2, color);
	
				Player *player;
				
				Color color2 = {255, 102, 102, 255};
				
				Color color3 = {255, 51, 51, 255};
		
				if (is_actionable(board, x, y, player)) {
					if (x == board->hover_field.x && y == board->hover_field.y ) {
						draw_filled_hex( renderer, point.x, point.y, board->field_size - 2, color2);
					}
					draw_hex( renderer, point.x, point.y, board->field_size, color3);
				}
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
