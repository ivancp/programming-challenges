#include "sudoku.h"

int main(){
	Sudoku sudoku;

	sudoku.read();
	sudoku.print();
	sudoku.solve();
	sudoku.find1Missing();
	sudoku.solve();
    sudoku.print();
    sudoku.printFromRows();

	return 0;
}