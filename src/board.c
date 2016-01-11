#include "board.h"

Pair point_to_pair(int x, int y, Board *board) {
    Pair pair;

    pair.y = floor((y - board->offset_y) / board->field_height);
    pair.x = floor(((pair.y % 2 == 0 ? x : x - board->field_size) - board->offset_x) / board->field_width);

    return pair;
}

Field *pair_to_field(Pair pair, Board *board) {
    if (pair.x < 0 || pair.y < 0 || pair.x >= board->width || pair.y >= board->height) {
        return NULL;
    }
    Field *field = &board->fields[pair.x][pair.y];
    return field;
}

Field *point_to_field(int x, int y, Board *board) {
    return pair_to_field(point_to_pair(x, y, board), board);
}

Pair field_to_point(int x, int y, Board *board) {
    Pair point;

    point.y = y * board->field_height + board->field_height * 0.5 + board->offset_y;
    point.x = (y % 2 == 0 ? 0 : board->field_width * 0.5) + x * board->field_width + board->field_width * 0.5 +
              board->offset_x;

    return point;
}

Pair field_to_pair(Field *field) {
    Pair pair = {field->x, field->y};
    return pair;
}

Field *random_field(PairStack *pair_stack, Board *board) {

    if (pair_stack->size == 0) return NULL;

    Field *field;

    PairItem *pair_item = pair_stack->top;
    for (int i = 0; i < rand() % pair_stack->size; i++) {
        pair_item = pair_item->prev;
    }

    field = pair_to_field(pair_item->pair, board);
    return field;
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

            new_board->fields[x][y].x = x;
            new_board->fields[x][y].y = y;
        }
    }

    new_board->hover_field = NULL;

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

bool has_neighbour(int x, int y, enum Race race, Board *board) {
    int odd[6][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 0}};
    int even[6][2] = {{-1, -1}, {0, -1}, {1, 0}, {0, 1}, {-1, 1}, {-1, 0}};

    int X, Y;

    for (int i = 0; i < 6; i++) {
        if(y % 2 == 0) {
            X = x + even[i][0];
            Y = y + even[i][1];
        }
        else {
            X = x + odd[i][0];
            Y = y + odd[i][1];
        }

        if (X < 0 || X >= board->width || Y < 0 || Y >= board->height) continue;

        switch (race) {
            case NEUTRAL:
                if (board->fields[X][Y].owner == 0) return true;
                break;
            case ENEMY:
                if (board->fields[X][Y].owner > 0 && board->fields[X][Y].owner != board->fields[x][y].owner) return true;
                break;
            case ALLY:
                if (board->fields[X][Y].owner == board->fields[x][y].owner) return true;
                break;
            default:
                break;
        }
    }

    return false;
}

void update_field_info(SDL_Renderer *renderer, Board *board) {
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    board->field_size = min(w / (2 * (0.5 + board->width)), 50);

    board->field_width = board->field_size * 2;
    board->field_height = board->field_width * 0.75;

    board->offset_x = (w - board->width * board->field_width - board->field_width * 0.5) * 0.5;
    board->offset_y = board->field_width * 0.5;

}