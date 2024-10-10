#ifndef MINIMAX_H
#define MINIMAX_H

#include <string.h>
#include <stdbool.h>

#include "constants.h"
#include "board.h"

typedef struct {
  int move;
  int evaluation;
} minimax_result;

minimax_result minimax(int *board, int depth, int *player, int move, int alpha, int beta);

#endif