import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;

public class Sudoku {
	private int board[][] = new int[9][9];

	public void load(String fn)
	{
		File fin; Scanner sc;

		try {
			fin = new File(fn);
			sc = new Scanner(fin);		
		} 
		catch (IOException e) {
			return;
		}
		
		for (int ind = 0; sc.hasNextInt() && ind < 81; ind++) {
			int row = ind / 9;
			int col = ind % 9;

			this.board[row][col] = sc.nextInt();
		}
	}

	private ArrayList<Integer> get_poss(int row, int col)
	{
		ArrayList<Integer> poss = new ArrayList<Integer>();

		for (int val = 1; val <= 9; val++) {
			boolean add = true;
			for (int i = 0; i < 9; i++) {
				if (this.board[i][col] == val || this.board[row][i] == val ||
					this.board[(row/3)*3 + i/3][(col/3)*3 + i%3] == val) {

					add = false;
					break;
				}
			}

			if (add)
				poss.add(val);
		}

		return poss;
	}

	private boolean solve_r(int ind)
	{
		if (ind == 81)
			return true;

		int row = ind / 9;
		int col = ind % 9;

		if (this.board[row][col] != 0)
			return this.solve_r(ind+1);

		ArrayList<Integer> poss = this.get_poss(row, col);

		for (int val : poss) {
			this.board[row][col] = val;

			if (this.solve_r(ind+1))
				return true;

			this.board[row][col] = 0;
		}
		
		return false;
	}

	public boolean solve()
	{
		return this.solve_r(0);
	}

	public String toString()
	{
		String s = "";

		for (int i = 0; i < 9; i++) {
			if (i != 0 && i % 3 == 0)
				s += "-------+-------+-------\n";

			s += String.format(" %d %d %d | %d %d %d | %d %d %d \n",
				this.board[i][0], this.board[i][1], this.board[i][2],
				this.board[i][3], this.board[i][4], this.board[i][5],
				this.board[i][6], this.board[i][7], this.board[i][8]);
		}

		return s;
	}
	
	public static void main(String args[]) 
	{
		Sudoku s = new Sudoku();
		s.load("./example_board.txt");
		s.solve();

		System.out.println(s);
	}
}