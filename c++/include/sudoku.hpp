#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <set>
#include <cstdint>

using ind = std::size_t;

class Sudoku {
public:
	Sudoku() { board = {0}; }
	Sudoku(const std::string& fn) { loadfile(fn); }

	void loadfile(const std::string& fn);

	void solve();

	friend std::ostream& operator<<(std::ostream& out, const Sudoku& su);
	
private:
	bool solve_r(ind i);
	std::set<short> availablemoves(ind i);
					
	std::array<short, 81> board;
};

#endif
