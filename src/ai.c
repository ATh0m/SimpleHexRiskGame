//
// Created by Tomasz Nanowski on 10.01.2016.
//

#include "ai.h"

bool ai_action(Player *player, Board *board, Players *players, enum State *state) {
    bool end_turn = false;

    PairStack *fields_adjacent_enemies = create_pair_stack();
    PairStack *fields_adjacent_neutrals = create_pair_stack();

    create_fields_adjacent(fields_adjacent_enemies, fields_adjacent_neutrals, player, board);

    switch (*state) {
        case START:
            end_turn = ai_start(player, board);
            break;
        case REINFORCEMENT:
            ai_reinforcement(player, board, state, fields_adjacent_enemies, fields_adjacent_neutrals);
            break;
        case MOVE:
            end_turn = ai_move(player, board, state, players, fields_adjacent_enemies, fields_adjacent_neutrals);
            break;
        default:
            break;
    }

    SDL_Delay(50);

    delete_pair_stack(fields_adjacent_enemies);
    delete_pair_stack(fields_adjacent_neutrals);

    return end_turn;
}

void create_fields_adjacent(PairStack *fields_adjacent_enemies, PairStack *fields_adjacent_neutrals, Player *player, Board *board) {

    PairItem *pair_item = player->fields_stack->top;
    while (pair_item != NULL) {
        if (has_neighbour(pair_item->pair.x, pair_item->pair.y, NEUTRAL, board)) {
            push(fields_adjacent_neutrals, pair_item->pair);
        }

        if (has_neighbour(pair_item->pair.x, pair_item->pair.y, ENEMY, board)) {
            push(fields_adjacent_enemies, pair_item->pair);
        }

        pair_item = pair_item->prev;
    }

}

bool ai_start(Player *player, Board *board) {
    int x, y;

    while (1) {
        x = rand() % board->width;
        y = rand() % board->height;

        if (board->fields[x][y].owner == 0) {
            if (!has_neighbour(x, y, ENEMY, board) || true) {
                player_start(player, pair_to_field(create_pair(x, y), board));
                return true;
            }
        }
    }
}

void ai_reinforcement(Player *player, Board *board, enum State *state, PairStack *fields_adjacent_enemies, PairStack *fields_adjacent_neutrals) {
    Field *field;

    if (fields_adjacent_enemies->size > 0 && ((rand() / (double) RAND_MAX) < 0.75 || fields_adjacent_neutrals->size == 0)) {
        field = random_field(fields_adjacent_enemies, board);
        player_reinforcement(player, field, state, SDL_BUTTON_LEFT);
    }
    else if (fields_adjacent_neutrals->size > 0){
        field = random_field(fields_adjacent_neutrals, board);
        player_reinforcement(player, field, state, SDL_BUTTON_LEFT);
    }
    else {
        field = random_field(player->fields_stack, board);
        player_reinforcement(player, field, state, SDL_BUTTON_LEFT);
    }

}

int actionable_enemy_fields_cmp (const void * a, const void * b) {
    return ( (*(Triple*)b).z - (*(Triple*)a).z );
}

bool ai_move(Player *player, Board *board, enum State *state, Players *players, PairStack *fields_adjacent_enemies, PairStack *fields_adjacent_neutrals) {
    PairStack *actionable_neutral_fields = create_pair_stack();
    PairStack *actionable_enemy_fields = create_pair_stack();

    Field *field;

    for (int x = 0; x < board->width; x++) {
        for(int y = 0; y < board->height; y++) {
            if (is_actionable(board, x, y, player, *state)) {
                if (board->fields[x][y].owner == 0) {
                    push(actionable_neutral_fields, create_pair(x, y));
                }
                else if (board->fields[x][y].owner != player->id) {
                    push(actionable_enemy_fields, create_pair(x, y));
                }
            }
        }
    }

    if ((rand() / (double)RAND_MAX) < 0.75 || actionable_enemy_fields->size == 0) {
        if (actionable_enemy_fields->size > 0 && ((rand() / (double)RAND_MAX) < 0.35 || actionable_neutral_fields->size == 0)) {
            Triple actionable_enemy_fields_tab[actionable_enemy_fields->size];

            int index = 0;
            PairItem *pair_item = actionable_enemy_fields->top;
            while (pair_item != NULL) {
                actionable_enemy_fields_tab[index] = create_triple(pair_item->pair.x, pair_item->pair.y, board->fields[pair_item->pair.x][pair_item->pair.y].force);
                pair_item = pair_item->prev;
                index++;
            }

            qsort(actionable_enemy_fields_tab, actionable_enemy_fields->size, sizeof(Triple), actionable_enemy_fields_cmp);

            if ((rand() / (double)RAND_MAX) < 0.5) {
                field = pair_to_field(create_pair(actionable_enemy_fields_tab[0].x, actionable_enemy_fields_tab[0].y) ,board);
            }
            else {
                index = rand() % actionable_enemy_fields->size;
                field = pair_to_field(create_pair(actionable_enemy_fields_tab[index].x, actionable_enemy_fields_tab[index].y) ,board);
            }
        }
        else if (actionable_neutral_fields->size > 0){
            field = random_field(actionable_neutral_fields, board);
        }
        else {
            field = random_field(player->fields_stack, board);
        }

        player_move(player, field, board, state, players);
    }
    else {
        if (fields_adjacent_enemies->size > 0) {
            field = random_field(fields_adjacent_enemies, board);
        }
        else if(fields_adjacent_neutrals->size > 0){
            field = random_field(fields_adjacent_neutrals, board);
        }
        else {
            field = random_field(player->fields_stack, board);
        }

        player_move(player, field, board, state, players);
    }

    delete_pair_stack(actionable_enemy_fields);
    delete_pair_stack(actionable_neutral_fields);

    return true;
}