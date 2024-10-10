#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "minimax.h"
#include "board.h"

int main() {
  /*
  The board:

  13 12 11 10 09 08 07     player2
      00 01 02 03 04 05 06  player1

  13 and 06 are "banks", other indices are "holes"
  */
  int board[BOARD_SIZE];
  int player = 1;
  int total_moves = 0;

  printf("LET'S PLAY A GAME OF MANCALA\n");
  printf("Start with 3 or 4 stones per hole?\n");

  int game_type;
  char line[1024];
      while (fgets(line, sizeof(line), stdin)) {
        if (sscanf(line, "%i", &game_type)) {
          if (game_type == 3 || game_type == 4) {
              board_reset(board, game_type);
              break;
          }
        }
      }
  int move = -1;

  while(!game_over(board)) {
    board_print(board);
    printf("Player %d is thinking\n", player);
    if (player == 1) {
      printf("PLAYER %d, enter move (1 to 6)\n", player);
      char line[1024];
      while (fgets(line, sizeof(line), stdin)) {
        if (sscanf(line, "%i", &move)) {
          move--;
          if (board_legal_move(board, move, player)) {
            break;
          }
        }
      }
      // minimax_result result = minimax(board, MINIMAX_DEPTH, &player, -1, -1000, 1000);
      // move = result.move;
      // printf("Player %d plays %d with an evaluation of %d\n", player, move, result.evaluation);
    } else {
      // printf("PLAYER %d, what is your move?\n", player);
      // char line[1024];
      // while (fgets(line, sizeof(line), stdin)) {
      //   if (sscanf(line, "%i", &move)) {
      //     if (board_legal_move(board, move, player)) {
      //       break;
      //     }
      //   }
      // }
      minimax_result result = minimax(board, MINIMAX_DEPTH, &player, -1, -1000, 1000);
      move = result.move;
      printf("Player %d plays %d with an evaluation of %d\n", player, move, result.evaluation);
    }
    board_move(board, move, &player, false);
    total_moves++;
  }

  printf("GAME OVER\n");
  board_print(board);
  printf("Final score: %d\n", board_evaluate_naive(board));
  printf("Took %d total moves\n", total_moves);

}