#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Sudoku_ {
	int board[9][9];
} Sudoku;

Sudoku* su_init()
{
	Sudoku* new_su = malloc(sizeof(Sudoku));
	memset(new_su, 0, sizeof(Sudoku));

	return new_su;
}

void su_free(Sudoku* su)
{
	free(su);
}

void su_readfile(Sudoku* su, const char* fn)
{
	FILE* fin = fopen(fn, "r");

	char line[25];
	for (int row = 0; row <9 && fgets(line, sizeof(line), fin); row++) {
		sscanf(line, "%d %d %d %d %d %d %d %d %d\n",
			&su->board[row][0], &su->board[row][1], &su->board[row][2],
			&su->board[row][3], &su->board[row][4], &su->board[row][5],
			&su->board[row][6], &su->board[row][7], &su->board[row][8]
			);
	}

	fclose(fin);
}

int* su_get_poss(Sudoku* su, int* vals_l, int row, int col)
{
	int* vals = malloc(9*sizeof(int));
	int vals_len = 0;

	for (int val = 1; val <= 9; val++) {
		int add = 1;

		for (int i = 0; i < 9; i++){
			if (su->board[i][col] == val) {
				add = 0;
				break;
			}

			if (su->board[row][i] == val) {
				add = 0;
				break;
			}

			if (su->board[(row/3)*3 + i/3][(col/3)*3 + i%3] == val) {
				add = 0;
				break;add = 0;add = 0;
			}
		}

		if (add) {
			vals[vals_len] = val;
			vals_len++;
		}

	}

	*vals_l = vals_len;
	return vals;
}

int su_solve_r(Sudoku* su, int ind)
{
	if (ind == 81)
		return 1;

	int row = ind/9;
	int col = ind%9;

	if (su->board[row][col] != 0)
		return su_solve_r(su, ind+1);

	int vals_l;
	int* vals = su_get_poss(su, &vals_l, row, col);

	for (int i = 0; i < vals_l; i++) {
		su->board[row][col] = vals[i];

		if (su_solve_r(su, ind+1)) {
			free(vals);
			return 1;
		}

		su->board[row][col] = 0;
	}

	free(vals);
	return 0;
}

int su_solve(Sudoku* su)
{
	return su_solve_r(su, 0);
}

char* su_str(Sudoku* su)
{
	char* str = malloc(265*sizeof(char));

	for (int i = 0, row = 0; i < 9; i++, row++) {
		if (i % 3 == 0 && i != 0) {
			sprintf(str+row*24, "-------+-------+-------\n");
			row++;
		}

		sprintf(str+row*24, " %d %d %d | %d %d %d | %d %d %d \n",
			su->board[i][0], su->board[i][1], su->board[i][2],
			su->board[i][3], su->board[i][4], su->board[i][5],
			su->board[i][6], su->board[i][7], su->board[i][8]);

	}

	return str;
}

int main()
{
	Sudoku* su = su_init();

	su_readfile(su, "./example_board.txt");

	su_solve(su);

	char* str = su_str(su);
	printf("%s\n", str);
	free(str);

	su_free(su);

	return 0;
}
