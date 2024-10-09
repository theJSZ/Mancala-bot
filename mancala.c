#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 14
const int BANK1 = BOARD_SIZE/2-1;
const int BANK2 = BOARD_SIZE-1;

enum GameType {
  THREE = 3,
  FOUR
};

void   board_print(int *board);
void   board_reset(int *board, enum GameType n_of_stones);
int    board_evaluate(int *board);
bool   game_over(int *board);
bool   board_move(int *board, int hole, int *player);
void   next_player(int *player);

void board_print(int *board) {
  for (int i = BANK2; i > BANK1; --i) {
    printf("%3d", board[i]);
  }
  printf("\n");
  printf("   ");
  for (int i = 0; i <= BANK1; ++i) {
    printf("%3d", board[i]);
  }
  // for (int i = 0; i < BOARD_SIZE; ++i) {
  //   printf("%d ", board[i]);
  // }
  printf("\n");
}

void board_reset(int *board, enum GameType n_of_stones) {
  for (int i = 0; i < BOARD_SIZE; ++i) {
    board[i] = n_of_stones;
  }
  switch (n_of_stones) {
    case 3:
      board[BANK1] = 6;
      board[BANK2] = 6;
      break;
    case 4:
      board[BANK1] = 0;
      board[BANK2] = 0;
      break;
    default:
      break;
  }
}

int board_evaluate(int *board) {
  int score1 = 0;
  int score2 = 0;

  for (int i = 0; i < BOARD_SIZE/2; ++i) {
    score1 += board[i];
    score2 += board[i+BOARD_SIZE/2];
  }

  return score1 - score2;
}

// game is over when either player has no moves left
bool game_over(int *board) {
  int stones1 = 0;
  int stones2 = 0;

  for (int i = 0; i < BANK1; ++i) {
    stones1 += board[i];
    stones2 += board[i+BOARD_SIZE/2];
  }

  return (stones1 == 0 || stones2 == 0);
}

bool board_move(int *board, int hole, int *player) {
  // printf("player %d played hole %d\n", *player, hole);
  // printf("hole %d has %d stones\n", hole, board[hole]);
  // hole must have stones
  if (board[hole] == 0) {
    // printf("hole %d was empty\n", hole);
    return false;
  }
  // boundary checks
  if (hole >= BANK2) {
    // printf("hole %d was > BANK2\n", hole);
    return false;
  }
  if (*player == 1) {
    if (hole >= BANK1) return false;
  }
  if (*player == 2) {
    if (hole <= BANK1) return false;
  }

  // legal move, take stones from hole
  int stones_left_to_place = board[hole];
  board[hole] = 0;

  int target_hole = hole;
  // if last stone placed in own bank, get another turn
  bool player_retains_turn = false;

  while (stones_left_to_place) {
    target_hole = (target_hole + 1) % BOARD_SIZE;
    // skip the other player's bank
    if (*player == 1 && target_hole == BANK2) target_hole = 0;
    if (*player == 2 && target_hole == BANK1) target_hole = BOARD_SIZE/2;

    player_retains_turn = false;
    if (*player == 1 && target_hole == BANK1) player_retains_turn = true;
    if (*player == 2 && target_hole == BANK2) player_retains_turn = true;

    board[target_hole]++;
    stones_left_to_place--;
  }

  /* if last stone placed in one of own holes that was empty,
    and the opposite hole has stones, collect your stone and
    opponent's stones from the opposite hole and place them in your bank
  */
  int opposite_hole = (BOARD_SIZE-2) - target_hole;
  if (board[target_hole] == 1 && board[opposite_hole] > 0) {
    if ((*player == 1 && target_hole < BANK1) || (*player == 2 && target_hole > BANK1)) {
      int bank = *player == 1 ? BANK1 : BANK2;
      board[bank] += (board[opposite_hole]+1);
      board[target_hole] = 0;
      board[opposite_hole] = 0;
    }
  }

  if (!player_retains_turn) {
    // printf("not retaining turn. player is now %d\n", *player);
    next_player(player);
  }

  return true;
}

void next_player(int *player) {
  *player = *player == 1 ? 2 : 1;
}


int main() {
  /*
  The board:

  13 12 11 10 09 08 07     player2
      00 01 02 03 04 05 06  player1

  13 and 06 are "banks", other indices are "holes"
  */
  int board[BOARD_SIZE];
  int player = 1;

  system("clear");
  printf("LET'S PLAY A GAME OF MANCALA\n");
  board_reset(board, 3);
  int move;

  while(!game_over(board)) {
    board_print(board);
    printf("PLAYER %d, what is your move?\n", player);
    scanf("%d", &move);
    board_move(board, move, &player);
    system("clear");
  }

  printf("GAME OVER\n");
  board_print(board);
  printf("Final score: %d\n", board_evaluate(board));


}