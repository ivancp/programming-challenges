#include <iostream>
#include <vector>
#include <map>

#define SIZE 9

using namespace std;

class Sudoku{

	struct POS{
		int i;
		int j;
	};
    struct UNIQUE;
	typedef UNIQUE* UNIQUEPtr;
	class Cell{
	 public:
		int value = 0;
		POS pos;
		vector<int> possible;
        Cell(int i, int j){
			pos.i = i;
			pos.j = j;
            for(int v = 1 ; v <= 9;v++){
				possible.push_back(v);
			}
        }
        void clearPossible(){
            possible.clear();
        }
        int removePossible(int val){
			//if ( std::find(possible.begin(), possible.end(), val) != possible.end() ){
				possible.erase(std::remove(possible.begin(), possible.end(), val),possible.end());
			//}
			return possible.size();
        }

        bool setValue(int val){
            if(isValueMissing(val)){
                value = val;
                clearPossible();
                return true;
            }
            return false;
        }

		bool isValueMissing(int val){
			if(std::find(possible.begin(), possible.end(), val) != possible.end()){
				return true;
			}
			return false;
		}

        UNIQUEPtr relatedRow = nullptr;
        UNIQUEPtr relatedCol = nullptr;
        UNIQUEPtr relatedGrp = nullptr;
        void setRelatedRow(UNIQUEPtr row){
            relatedRow = row;
        }

        void setRelatedCol(UNIQUEPtr col){
            relatedCol = col;
        }

        void setRelatedGrp(UNIQUEPtr grp){
            relatedGrp = grp;
        }

	};
	typedef Cell* CellPtr;
    typedef vector<CellPtr>* RowPtr;
    

	struct UNIQUE{
		vector<CellPtr> mCells;
		map<int,double> probably;
		Cell missing;
		bool solved;
		UNIQUE():missing(0,0){
			solved = false;
		}

		void addCell(CellPtr ptr){
			mCells.push_back(ptr);
		}
	};
	
	vector<UNIQUE> mRows;
	vector<UNIQUE> mCols;
    vector<UNIQUE> mGrps;
	vector<vector<Cell>> mSudoku;

	vector<POS> checkStack;

    bool insert(int i, int j, int val){
        int pos = 0;
        if(mSudoku[i][j].setValue(val)){
			cout<<" inserted "<<val<<" in "<<i<<","<<j<<endl;
            UNIQUEPtr row = mSudoku[i][j].relatedRow;
            if(row != nullptr){
                for(auto r: row->mCells){
                    if(r->removePossible(val) == 1){
						cout<<"Found 1 in row"<<i<<","<<j<<" after remove "<<val<<" leaved "<<r->possible[0]<<endl;
						checkStack.push_back(r->pos);
					}
                }
				row->missing.removePossible(val);
            }
            UNIQUEPtr col = mSudoku[i][j].relatedCol;
            if(col != nullptr){
                for(auto c: col->mCells){
                    if(c->removePossible(val) == 1){
						cout<<"Found 1 in col"<<i<<","<<j<<" after remove "<<val<<" leaved "<<c->possible[0]<<endl;
						checkStack.push_back(c->pos);
					}
                }
				col->missing.removePossible(val);
            }

            UNIQUEPtr grp = mSudoku[i][j].relatedGrp;
            if(grp != nullptr){
                for(auto g: grp->mCells){
                    if(g->removePossible(val) == 1){
						cout<<"Found 1 in grp"<<i<<","<<j<<" after remove "<<val<<" leaved "<<g->possible[0]<<endl;
						checkStack.push_back(g->pos);
					}
                }
				grp->missing.removePossible(val);
            }
            return true;
        }
        return false;
    }

public:
	Sudoku(){
		init();
	}

	void solve(){
		while(checkStack.size() > 0){

			POS p = checkStack[0];
			CellPtr cell = &mSudoku[p.i][p.j];
			cout<<"checking "<<cell->possible[0]<<" in "<<p.i<<","<<p.j<<endl;
			if(cell->possible.size() == 1){
				
				insert(p.i,p.j,cell->possible[0]);
			}
			checkStack.erase(checkStack.begin());
		}
	}
	void find1Missing(){
		find1Missing(mRows);
		find1Missing(mCols);
		find1Missing(mGrps);
	}

	void find1Missing(vector<UNIQUE> cells){
		for(auto row: cells){
			for(auto number: row.missing.possible){
				int count = 0;
				CellPtr currCell = nullptr;
				for(auto cell: row.mCells){
					if(cell->isValueMissing(number)){
						currCell = cell;
						count++;
					}
					if(count > 1){
						break;
					}
				}
				if(count == 1 && currCell != nullptr){ //found just one missing
					cout<<" Found "<<number<<" missing "<<endl;
					insert(currCell->pos.i,currCell->pos.j,number);
					//currCell->setValue(number);
				}
			}
		}
	}

	void init(){

		//init all 9x9 cells
		for(int i = 0 ; i < SIZE;i++){
			//init rows,cols, groups, first time
			mRows.push_back(UNIQUE());
			mCols.push_back(UNIQUE());
            mGrps.push_back(UNIQUE());

			mSudoku.push_back( vector<Cell>());
			for(int j = 0 ; j < SIZE;j++){
				mSudoku[i].push_back(Cell(i,j));
			}
		}

		for(int i = 0 ; i < SIZE;i++){

			for(int j = 0 ; j < SIZE;j++){
				mRows[i].addCell(&mSudoku[i][j]);
				mCols[i].addCell(&mSudoku[j][i]);
                mSudoku[i][j].setRelatedRow(&mRows[i]);
                mSudoku[j][i].setRelatedCol(&mCols[i]);

				int group = (int(j/3)) + (int(i/3))*3;
				mGrps[group].addCell(&mSudoku[i][j]);
				mSudoku[i][j].setRelatedGrp(&mGrps[group]);
				//cout<<"i,j:"<<i<<","<<j<<" ->"<<(int(j/3)) + (int(i/3))*3<<endl;
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
					//mSudoku[i][j].value = c - '0';
                    insert(i,j,c-'0');
				}
                /*else{
					mSudoku[i][j].value = 0;
				}*/
			}

		}
	}

	void print(){
		cout<<"Current Sudoku:"<<endl;
		for(int i = 0 ; i < SIZE;i++){
			for(int j = 0 ; j < SIZE;j++){
				if(mSudoku[i][j].value)
					cout<<"    "<<mSudoku[i][j].value<<"    |";
				else
					cout<<"    -    |";
			}
            cout<<endl;
			for(int j = 0 ; j < SIZE;j++){
                
                for(auto possible: mSudoku[i][j].possible){
                    cout<< possible;
                }
				for(int s = 0; s < 9-mSudoku[i][j].possible.size();s++){
					cout<<" ";
				}
                
                cout<<"|";
			}
            cout<<"\n------------------------------------------------------------------------------------------\n";
			
		}
		cout<<endl;
	}
	void printFromRows(){
		for(auto i:mRows){
			for(auto j:i.mCells){
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
		for(auto i:mCols){
			for(auto j:i.mCells){
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