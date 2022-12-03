#include <iostream>
#include <vector>
#define SIZE 9

using namespace std;

class Sudoku{

	struct Cell{
		int value = 0;
		vector<int> possible;
	};
	typedef Cell* CellPtr;
	
	vector<vector<CellPtr>> rows;
	vector<vector<CellPtr>> cols;
	vector<vector<Cell>> mSudoku;
	

public:
	Sudoku(){
		init();
	}
	void init(){
		for(int i = 0 ; i < SIZE;i++){
			mSudoku.push_back( vector<Cell>());
			rows.push_back(vector<CellPtr>());
			cols.push_back(vector<CellPtr>());
			for(int j = 0 ; j < SIZE;j++){				
				mSudoku[i].push_back(Cell());
			}
		}

		for(int i = 0 ; i < SIZE;i++){
			for(int j = 0 ; j < SIZE;j++){
				rows[i].push_back(&mSudoku[i][j]);
				cols[i].push_back(&mSudoku[j][i]);
			}
		}

	}
	void read(){
		//char line[9];
		char c;
		for(int i = 0 ; i < SIZE;i++){
			for(int j = 0 ; j < SIZE;j++){
				cin>>c;
				if(c >= '0' && c <= '9'){
					mSudoku[i][j].value = c - '0';
				}else{
					mSudoku[i][j].value = 0;
				}
			}

		}
	}

	void print(){
		cout<<"Current Sudoku:"<<endl;
		for(int i = 0 ; i < SIZE;i++){
			for(int j = 0 ; j < SIZE;j++){
				if(mSudoku[i][j].value)
					cout<<mSudoku[i][j].value;//((mSudoku[i][j] == 0)?'-' :mSudoku[i][j]);
				else
					cout<<'-';
			}
			cout<<endl;
		}
		cout<<endl;
	}
	void printFromRows(){
		for(auto i:rows){
			for(auto j:i){
				if(j->value)
					cout<<j->value;
				else
					cout<<'-';				
			}
			cout<<endl;
		}
		cout<<endl;
	}	
	void printFromCols(){
		for(auto i:cols){
			for(auto j:i){
				if(j->value)
					cout<<j->value;
				else
					cout<<'-';				
			}
			cout<<endl;
		}
		cout<<endl;
	}	

};