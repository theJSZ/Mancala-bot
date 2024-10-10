#include "minimax.h"

minimax_result minimax(int *board, int depth, int *player, int move, int alpha, int beta) {
    if (game_over(board) || depth == 0) {
        minimax_result result;
        result.move = move;
        if (*player == 1) result.evaluation = board_evaluate_naive(board);
        if (*player == 2) result.evaluation = board_evaluate_naive(board);
        return result;
    }

    if (*player == 1) {
        int max_result = -1000;
        int best_move = -1;
        minimax_result result;
        result.evaluation = max_result;

        for (int test_move = BANK1-1; test_move >= 0; --test_move) {
            int test_board[BOARD_SIZE];
            memcpy(test_board, board, BOARD_SIZE * sizeof(board[0]));

            if (board_legal_move(test_board, test_move, 1)) {
                int temp_player = *player;
                board_move(test_board, test_move, &temp_player, false);

                result = minimax(test_board, depth - 1, &temp_player, test_move, alpha, beta);

                if (result.evaluation > max_result) {
                    best_move = test_move;
                    max_result = result.evaluation;
                    alpha = max_result;
                    if (alpha >= beta) break;
                }
            }
        }
        result.move = best_move;
        result.evaluation = max_result;
        return result;
    }

    if (*player == 2) {
        int min_result = 1000;
        int best_move = -1;
        minimax_result result;
        result.evaluation = min_result;

        for (int test_move = BANK1+1; test_move > BANK1; --test_move) {
            int test_board[BOARD_SIZE];
            memcpy(test_board, board, BOARD_SIZE * sizeof(board[0]));

            if (board_legal_move(test_board, test_move, 2)) {
                int temp_player = *player;
                board_move(test_board, test_move, &temp_player, false);

                result = minimax(test_board, depth - 1, &temp_player, test_move, alpha, beta);

                if (result.evaluation < min_result) {
                    min_result = result.evaluation;
                    best_move = test_move;
                    beta = min_result;
                    if (alpha >= beta) break;
                }
            }
        }
        result.move = best_move;
        result.evaluation = min_result;
        return result;
    }
}
