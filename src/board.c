#include "board.h"

Pair point_to_field(int x, int y, Board *board) {
    Pair field;

    field.y = floor((y - board->offset_y) / board->field_height);
    field.x = floor(((field.y % 2 == 0 ? x : x - board->field_size) - board->offset_x) / board->field_width);

    return field;
}

Pair field_to_point(int x, int y, Board *board) {
    Pair point;

    point.y = y * board->field_height + board->field_height * 0.5 + board->offset_y;
    point.x = (y % 2 == 0 ? 0 : board->field_width * 0.5) + x * board->field_width + board->field_width * 0.5 +
              board->offset_x;

    return point;
}

Board *create_board(int cols, int rows, int tab[cols][rows]) {
    Board *new_board = malloc(sizeof(Board));

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

bool is_neighbour(int x1, int y1, int x2, int y2) {
    int odd[6][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 0}};
    int even[6][2] = {{-1, -1}, {0, -1}, {1, 0}, {0, 1}, {-1, 1}, {-1, 0}};

    for (int i = 0; i < 6; i++) {
        if (y1 % 2 == 0) {
            if (x1 + even[i][0] == x2 && y1 + even[i][1] == y2) {
                return true;
            }
        }
        else {
            if (x1 + odd[i][0] == x2 && y1 + odd[i][1] == y2) {
                return true;
            }
        }
    }

    return false;
}

bool is_actionable(Board *board, int x, int y, Player *player, enum State state) {
    if (x >= 0 && x < board->width && y >= 0 && y < board->height && board->fields[x][y].owner >= 0) {
        if (state == START) {
            if (board->fields[x][y].owner == 0) {
                return true;
            }
        }
        if (state == REINFORCEMENT || state == MOVE) {
            if (board->fields[x][y].owner == player->id) {
                return true;
            }
        }
        if (state == MOVE) {
            PairItem *pair_item = player->fields_stack->top;

            while (pair_item != NULL) {

                if (is_neighbour(x, y, pair_item->pair.x, pair_item->pair.y)) {
                    return true;
                }

                pair_item = pair_item->prev;
            }
        }
    }

    return false;
}

void update_field_info(SDL_Renderer *renderer, Board *board) {
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    board->field_size = w / (2 * (0.5 + board->width));

    board->field_width = board->field_size * 2;
    board->field_height = board->field_width * 0.75;

    board->offset_x = (w - board->width * board->field_width - board->field_width * 0.5) * 0.5;
    board->offset_y = board->field_width * 0.125;
}