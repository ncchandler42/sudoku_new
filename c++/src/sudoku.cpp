#include "sudoku.hpp"

#ifdef BUILDLIB
#define MAIN(x)
#else
#define MAIN(x) x
#endif

std::ostream& operator<<(std::ostream& out, const Sudoku& su)
{
	for (ind i = 0; i < 81; i += 9) {
		if (i == 27 || i == 27*2)
			out << "-------+-------+-------" << std::endl;
			
		out << " " << su.board[i+0] << " " << su.board[i+1] << " " << su.board[i+2] << " |";
		out << " " << su.board[i+3] << " " << su.board[i+4] << " " << su.board[i+5] << " |";
		out << " " << su.board[i+6] << " " << su.board[i+7] << " " << su.board[i+8] << std::endl;				
	}

	return out;
}
void Sudoku::loadfile(const std::string& fn)
{
	std::ifstream fin(fn);
	for (ind i = 0; i < 81 && fin >> board[i]; i++);
	fin.close();
}

void Sudoku::solve()
{
	if (solve_r(0))
		std::cout << "Solved!" << std::endl;
	else
		std::cout << "No solution." << std::endl;			
}

bool Sudoku::solve_r(ind i)
{
	if (i == 81)
		return true;

	if(board[i] != 0)
		return solve_r(i+1);

	auto available = availablemoves(i);
	for (short s : available) {
		board[i] = s;
		
		if (solve_r(i+1))
			return true;
			
		board[i] = 0;
	}

	return false;
}

std::set<short> Sudoku::availablemoves(ind i)
{
	if (board[i] != 0)
		return std::set<short>();
	
	std::set<short> available = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	ind row = i / 9;
	ind col = i % 9;
	ind box_corner = 27*(row / 3) + 3*(col / 3);
	
	for (ind j = 0; j < 9; j++)	{
		available.erase(board[9*row+j]);
		available.erase(board[col+j*9]);
		available.erase(board[box_corner + 9*(j/3) + (j%3)]); 
	}

	return available;
}

MAIN(
	int main()
	{
		Sudoku s("./example_board.txt");
		s.solve();
		std::cout << s << std::endl;
	}
)
