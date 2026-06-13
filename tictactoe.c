#include <stdio.h>

char boardChk(int board[9], int num)
{
	switch(board[num]) {
		case 0:
			return ' ';
		case 1:
			return 'X';
		case -1:
			return 'O';
	}
}

int win(int board[9])
{
	/* All possible combinations */
	int com[8][3] = {{0,3,6}, {1,4,7}, {2,5,8}, {0,1,2}, {3,4,5}, {6,7,8}, {0,4,8}, {6,4,2}};

	for (int i = 0; i < 8; ++i) {
		if (board[com[i][0]] == board[com[i][1]] &&
			board[com[i][1]] == board[com[i][2]]) {
			if (board[com[i][0]] && board[com[i][1]] && board[com[i][2]])
				return board[com[i][2]];
			else
				continue;
			}
	}

	return 0;
}

int minimax(int board[9], int player)
{
	int stat = win(board);
	if (stat != 0) return stat * player;

	int score = -2;
	int currScore; /* Score for each iteration */

	for (int i = 0; i < 9; ++i) {
		if (board[i] == 0) { /* If cell is not empty */
			board[i] = player; /* Poke this square */
			currScore = -minimax(board, player * -1);
			board[i] = 0;

			if (currScore > score)
				score = currScore;
		}
	}

	if (score == -2) return 0; /* If no more positions */
	return score;
}

void computerMove(int board[9])
{
	int move = -1;
	int score = -2;
	int currScore; /* Score for each iteration */

	for (int i = 0; i < 9; ++i) { /* Poke each square */
		if (board[i] == 0) {
			board[i] = 1;
			currScore = -minimax(board, -1);
			board[i] = 0;

			if (currScore > score) {
				score = currScore;
				move = i;
			}
		}
	}

	if (move != -1)
		board[move] = 1;
}

void draw(int board[9])
{
	printf("%c|%c|%c\n", boardChk(board, 0), boardChk(board, 1), boardChk(board, 2));
	printf("-|-|-\n");
	printf("%c|%c|%c\n", boardChk(board, 3), boardChk(board, 4), boardChk(board, 5));
	printf("-|-|-\n");
	printf("%c|%c|%c\n", boardChk(board, 6), boardChk(board, 7), boardChk(board, 8));
}

int main()
{
	int board[9] = {0,0,0,0,0,0,0,0,0};
	int option;
	while (1) {
		printf("First move: You(O) [1] Computer(X) [2]: ");
		if (scanf("%d", &option) == 1)
			if (option == 1 || option == 2)
				break;
		getchar();
	}

	int playerOpt;
	for (int i = 0; (i < 9) && win(board) == 0; ++i) {
		if (((option + i) % 2) == 0) {
			computerMove(board);
		} else {
			while (1) {
				draw(board);
				printf("Your move [1-9]: ");
				if (scanf("%d", &playerOpt) == 1) {
					if (playerOpt > 0 && playerOpt < 10)
						if (!board[playerOpt - 1])
							break;
				} else {
					getchar();
				}
			}

			board[playerOpt - 1] = -1;
		}
	}

	switch(win(board)) {
		case 0:
			printf("\nDraw\n");
			break;
		case 1:
			printf("\nComputer wins\n");
			break;
		case -1:
			printf("\nPlayer wins\n");
	}
	draw(board);
}
