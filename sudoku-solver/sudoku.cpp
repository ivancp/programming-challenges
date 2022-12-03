#include "sudoku.h"

int main(){
	Sudoku sudoku;

	sudoku.read();
	sudoku.print();
	sudoku.solve();
    sudoku.print();
	return 0;
}