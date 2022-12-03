#include "sudoku.h"

int main(){
	Sudoku sudoku;

	sudoku.read();
	sudoku.printFromRows();
	//sudoku.printFromCols();
	return 0;
}