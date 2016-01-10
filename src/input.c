#include "input.h"

bool read_events(Game *game) {

    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {

        switch (event.type) {
            case SDL_QUIT:
                return true;
            case SDL_MOUSEMOTION:
                mouse_move_event(event, game);
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouse_down_event(event, game);
                break;
            default:
                break;
        }
    }

    return false;
}

void mouse_move_event(SDL_Event event, Game *game) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    game->board->hover_field = point_to_field(x, y, game->board);
}

void mouse_down_event(SDL_Event event, Game *game) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    game->board->hover_field = point_to_field(x, y, game->board);

    Player *player = game->players->list[game->players->active_player_index];

    if (game->board->hover_field == NULL || !is_actionable(game->board, game->board->hover_field->x, game->board->hover_field->y, player, game->state)) {
        return ;
    }

    Field *field = &game->board->fields[game->board->hover_field->x][game->board->hover_field->y];

    if (player_action(player, field, game->board, &game->state, game->players)) next_turn(game);
}