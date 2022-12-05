#include "sudoku.h"

int main(){
	Sudoku sudoku;

	sudoku.read();
	sudoku.print();
	
	int inserted = 0;

	do{
		inserted  = sudoku.solve();
		inserted += sudoku.find1Missing();

	}while(inserted > 0);

	sudoku.calcProbability();

	do{
		inserted  = sudoku.solve();
		inserted += sudoku.find1Missing();
		
	}while(inserted > 0);


    sudoku.print();
    sudoku.printFromRows();

	return 0;
}