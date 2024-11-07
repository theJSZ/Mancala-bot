# A program that plays Mancala

This is a simple mancala "bot" that runs in the console. The program determines the best move using minimax with a-b pruning. Minimax search depth is determined by user input at the start and can be set from 1 to 20 ply.

Every time the computer makes a move, you get a print showing what the minimax evaluation was. The computer is the minimizing player.

Rules of mancala:

- Each player has 6 "holes" in a row and a "bank" to their right. To begin with, there are 3 or 4 (user selectable) stones in each hole. In the case of 3 stones per hole, there are also 6 stones in both banks, so that the total number of stones is always 48.
- The game ends when, after a turn, either player has no stones left in their holes.
- Players take turns doing the following:
  - Take all stones from one of their own holes
  - Advance around the board counter-clockwise, depositing those stones one at a time into holes and the player's own bank. A player never deposits into the opponent's bank.
  - If the player deposits the last stone into their own bank, they immediately get to take another turn.
  - If the player deposits the last stone into one of their holes that was empty *and* there is at least one stone in the hole directly opposite, they immediately place all these stones into their bank.
- When the game ends, each player's score is the total number of stones in their holes and bank combined.
