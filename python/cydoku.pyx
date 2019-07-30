# distutils: language = c++

from libcpp.vector cimport vector

cdef class Sudoku:
	cdef int board[9][9]
		
	def __cinit__(self):
		self.board = [[0]*9]*9 # Fill with zeros
	
	#=============================================================================	
	#=== Loads data in from a text file ==========================================		
	#=============================================================================	
		
	def loadtxt(self, fp):
		cdef int i = 0, j = 0, val
		
		with open(fp, 'r') as fin:
			lines = fin.readlines()
			
			 # Wrong number of lines in file
			if len(lines) != 9:
				print("ERROR: Invalid input in '{}'".format(fp))
				return
			
			for line in lines:
				line = line.split()
				
				# Wrong number of columns in row
				if len(line) != 9:
					print("ERROR: Invalid input in '{}'".format(fp)) 
					return
				
				for j in range(9):
					val = int(line[j])
					
					# Invalid value in a square
					if val < 0 or val > 9:
						print("ERROR: Invalid input in '{}'".format(fp)) 
						return
						
					self.board[i][j] = val
					
				i += 1
				
		self.validate() # good place to validate the board, at the very least the user gets notified
	
	#=============================================================================	
	#=== Checks a square for what possible moves are available ===================	
	#=============================================================================					
		
	def get_available_moves(self, int row, int col):
		cdef vector[int] moves
		cdef int val, i, j, sq_row, sq_col
		cdef bint valid
		
		if self.board[row][col] != 0: # Square already filled
			return moves # which is empty
			
		for val in range(1, 10):
			valid = True
			
			for i in range(9):
				# invalid if val already exists in the row
				if val == self.board[row][i]: valid = False
	
			for i in range(9):
				# invalid if val already exists in the column
				if val == self.board[i][col]: valid = False
				
			sq_row = row//3 *3 #upper-most row of 3x3 square
			sq_col = col//3 *3 #left-most column of 3x3 square
			for i in range(3):
				for j in range(3):
					# invalid if val already exists in the 3x3 square
					if val == self.board[sq_row+i][sq_col+j]: valid = False	
			
			# val is valid according to rules of sudoku
			if valid:
				moves.push_back(val)
				
		return moves
	
	#=============================================================================		
	#=== SOLVER: Solves the puzzle ===============================================	
	#=============================================================================		
		
	def solve(self):
		if not self.validate(): # bad puzzles will gum up the solver
			return False
		
		return self.__solve_recursive(0) # Start recursive brute-force solver at (0, 0)
		
		
	def __solve_recursive(self, int ind):
		if ind == 81:
			return True # reached the end of the puzzle, solved
		
		cdef int row, col, val
		
		# translate index [0, 81) to row, column
		row = ind // 9 
		col = ind % 9
		
		if self.board[row][col] != 0:
			return self.__solve_recursive(ind+1) # spot already has a value, skip it
		
		cdef vector[int] moves
		moves = self.get_available_moves(row, col) # grab available moves
		
		# try each of available values
		for val in moves: 
			self.board[row][col] = val
			
			# 'false' means the value we tried in this loop didn't give a valid solution,
			# so we loop through and try the next
			if self.__solve_recursive(ind+1):
				return True
			
			self.board[row][col] = 0
		
		# None of the available values in this square gave a valid solution,
		# go back and try another value on a previous square
		return False
	
	#=============================================================================	
	#=== Checks to see if the board has valid values, see below ==================	
	#=============================================================================		
	def validate(self):
		cdef int val, i, j
		cdef vector[int] moves
		
		# iterates through the whole board, 'lifts' values from filled spaces then checks
		# if they belonged there in the first place, finally replacing them
		# if a value exists where it should not be, the board is invalid
		for i in range(9):
			for j in range(9):
				if self.board[i][j] == 0:
					continue
			
				val = self.board[i][j]
				self.board[i][j] = 0
				
				moves = self.get_available_moves(i,j)
				self.board[i][j] = val
				
				if val not in list(moves):
					print('ERROR: invalid board')
					return False
					
		return True		
	
	
	#=============================================================================	
	#=== Formats the board for pretty printing ===================================	
	#=============================================================================	
	def __str__(self):
		cdef int i
		
		s = ''
		
		for i in range(9):
			# replaces 0 with ' ', then formats them into a nice row
			str_vals = [(x if x != 0 else ' ') for x in list(self.board[i])] 
			s += ' {} {} {} | {} {} {} | {} {} {} \n'.format(*str_vals)
			
			if i == 2 or i == 5:
				s += '-------+-------+-------\n'
			
		return s
		
		
