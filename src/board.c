#include "board.h"

Pair point_to_field(int x, int y, Board* board)
{
	Pair field;

	field.y = floor((y - board->offset_y) / board->field_height);
	field.x = floor(((field.y % 2 == 0 ? x : x - board->field_size) - board->offset_x) / board->field_width);

	return field;
}

Pair field_to_point(int x, int y, Board* board)
{
	Pair point;

	point.y = y * board->field_height + board->field_height * 0.5 + board->offset_y;
	point.x = (y % 2 == 0 ? 0 : board->field_width * 0.5) + x * board->field_width + board->field_width * 0.5 + board->offset_x;

	return point;
}

Board* create_board(int cols, int rows, int tab[cols][rows])
{
	Board* new_board = malloc(sizeof(Board));

	new_board->fields = malloc(cols * sizeof(*new_board->fields));
	for (int x = 0; x < cols; x++)
		new_board->fields[x] = malloc(rows * sizeof(*new_board->fields[x]));

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

bool is_actionable(Board* board, int x, int y, Player* player)
{
	if (x >= 0 && x < board->width && y >= 0 && y < board->height && board->fields[x][y].owner >= 0) {
		if (board->status == START) {
			if (board->fields[x][y].owner == 0) {
				return true;
			}
		}
	}

	return false;
}

void draw_board(SDL_Renderer* renderer, Board* board)
{

	int w, h;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	board->field_size = w / (2 * (0.5 + board->width));

	board->field_width = board->field_size * 2;
	board->field_height = board->field_width * 0.75;

	board->offset_x = (w - board->width * board->field_width - board->field_width * 0.5) * 0.5;
	board->offset_y = board->field_width * 0.125;

	for (int x = 0; x < board->width; x++) {
		for (int y = 0; y < board->height; y++) {
			if (board->fields[x][y].owner >= 0) {
				// int hy = y * board->field_size * 3 / 2 + board->field_size;
				// int hx = 2 * board->field_size * x + board->field_size;
				// if (y % 2 == 1) hx += board->field_size;

				Color color = { 128, 128, 128, 255 };

				Pair point = field_to_point(x, y, board);
				draw_filled_hex(renderer, point.x, point.y, board->field_size - 2, color);

				Player* player;

				Color color2 = { 255, 102, 102, 255 };

				Color color3 = { 255, 51, 51, 255 };

				if (is_actionable(board, x, y, player)) {
					if (x == board->hover_field.x && y == board->hover_field.y) {
						draw_filled_hex(renderer, point.x, point.y, board->field_size - 2, color2);
					}
					draw_hex(renderer, point.x, point.y, board->field_size, color3);
				}
			}
		}
	}
}
