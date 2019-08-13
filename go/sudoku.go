package main

import (
	"fmt"
	"os"
	"bufio"	
	"strconv"
)

type Sudoku struct {
	board [9][9]int
}

func (su *Sudoku) Load(fn string) {
	file, _ := os.Open(fn)

	sc := bufio.NewScanner(file)
	sc.Split(bufio.ScanWords)

	for i := 0; i < 9; i++ {
		for j := 0; j < 9; j++ {
			if sc.Scan() {
				su.board[i][j],_ = strconv.Atoi(sc.Text())
			} else {
				break
			}
		}
	}
}

func (su *Sudoku) get_poss(row, col int) []int {
	poss := make([]int, 0, 9)
	
	for val := 1; val <= 9; val++ {
		add := true
		for i := 0; i < 9; i++ {
			if su.board[i][col] == val {
				add = false
				break
			}

			if su.board[row][i] == val {
				add = false
				break
			}

			if su.board[int(row/3)*3 + int(i/3)][int(col/3)*3 + i%3] == val {
				add = false
				break
			}				
		}

		if add {
			poss = poss[:len(poss)+1]
			poss[len(poss)-1] = val
		}
	}

	return poss
}

func (su *Sudoku) solve_r(ind int) bool {
	if ind == 81 {
		return true
	}

	row := int(ind / 9)
	col := ind % 9

	if su.board[row][col] != 0 {
		return su.solve_r(ind+1)
	}

	poss := su.get_poss(row, col)

	for _, val := range poss {
		su.board[row][col] = val

		if su.solve_r(ind+1) {
			return true
		}

		su.board[row][col] = 0
	}

	return false
}

func (su *Sudoku) Solve() bool {
	return su.solve_r(0)
}

func (su Sudoku) String() string {
	b := ""

	for i := 0; i < 9; i++ {
		if i % 3 == 0 && i != 0  {
			b += "-------+-------+-------\n"
		}

		b += fmt.Sprintf(" %d %d %d | %d %d %d | %d %d %d \n",
			su.board[i][0], su.board[i][1], su.board[i][2],
			su.board[i][3], su.board[i][4], su.board[i][5],
			su.board[i][6], su.board[i][7], su.board[i][8])
	}

	return b
}


func main() {
	var su Sudoku
	su.Load("./example_board.txt")
	su.Solve()
	
	fmt.Println(su)
}
