#!/usr/bin/env python3

import sys

if len(sys.argv) >= 2 and sys.argv[1] == 'slow':
	import slowdoku as sudoku
else:
	import cydoku as sudoku

board = sudoku.Sudoku()

board.loadtxt('./example_board.txt')
board.solve()

print(board)

