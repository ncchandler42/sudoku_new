import sudokumod as sudoku

s = sudoku.Sudoku("./example_board.txt")
s.solve()
print(s)
