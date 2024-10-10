#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stdio.h>

#include "constants.h"

enum GameType {
  THREE = 3,
  FOUR
};

void   board_print(int *board);
void   board_reset(int *board, enum GameType n_of_stones);
int    board_evaluate_naive(int *board);
int    board_evaluate_fancy(int *board);
bool   game_over(int *board);
bool   board_move(int *board, int hole, int *player, bool verbose);
void   next_player(int *player);

bool   board_legal_move(int *board, int hole, int player);
int    board_count_stones(int *board);

#endif