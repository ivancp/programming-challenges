#include <iostream>
#include <vector>

#define SIZE 9

using namespace std;

class Sudoku{

	struct POS{
		int i;
		int j;
	};
    
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
            if(std::find(possible.begin(), possible.end(), val) != possible.end()){
                value = val;
                clearPossible();
                return true;
            }
            return false;
        }

        vector<Cell*>* relatedRow = nullptr;
        vector<Cell*>* relatedCol = nullptr;
        vector<Cell*>* relatedGrp = nullptr;
        void setRelatedRow(vector<Cell*>* row){
            relatedRow = row;
        }

        void setRelatedCol(vector<Cell*>* col){
            relatedCol = col;
        }

        void setRelatedGrp(vector<Cell*>* grp){
            relatedGrp = grp;
        }

	};
	typedef Cell* CellPtr;
    typedef vector<CellPtr>* RowPtr;
    
	
	vector<vector<CellPtr>> mRows;
	vector<vector<CellPtr>> mCols;
    vector<vector<CellPtr>> mGrps;
	vector<vector<Cell>> mSudoku;
	

	vector<POS> checkStack;

    bool insert(int i, int j, int val){
        int pos = 0;
        if(mSudoku[i][j].setValue(val)){
            RowPtr row = mSudoku[i][j].relatedRow;
            if(row != nullptr){
                for(auto r: *row){
                    if(r->removePossible(val) == 1){
						cout<<"Found 1 in row"<<i<<","<<j<<" after remove "<<val<<" leaved "<<r->possible[0]<<endl;
						checkStack.push_back(r->pos);
					}
                }
            }
            RowPtr col = mSudoku[i][j].relatedCol;
            if(col != nullptr){
                for(auto c: *col){
                    if(c->removePossible(val) == 1){
						cout<<"Found 1 in col"<<i<<","<<j<<" after remove "<<val<<" leaved "<<c->possible[0]<<endl;
						checkStack.push_back(c->pos);
					}
                }
            }

            RowPtr grp = mSudoku[i][j].relatedGrp;
            if(grp != nullptr){
                for(auto g: *grp){
                    if(g->removePossible(val) == 1){
						cout<<"Found 1 in grp"<<i<<","<<j<<" after remove "<<val<<" leaved "<<g->possible[0]<<endl;
						checkStack.push_back(g->pos);
					}
                }
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
				cout<<" inserting "<<cell->possible[0]<<" in "<<p.i<<","<<p.j<<endl;
				insert(p.i,p.j,cell->possible[0]);
			}
			checkStack.erase(checkStack.begin());
		}
	}
	void init(){
		for(int i = 0 ; i < SIZE;i++){
			mSudoku.push_back( vector<Cell>());
			mRows.push_back(vector<CellPtr>());
			mCols.push_back(vector<CellPtr>());
            mGrps.push_back(vector<CellPtr>());
			for(int j = 0 ; j < SIZE;j++){
				mSudoku[i].push_back(Cell(i,j));
			}
		}

		for(int i = 0 ; i < SIZE;i++){
            //cout<<"i:"<<(int(i/3))<<endl;
			for(int j = 0 ; j < SIZE;j++){
				mRows[i].push_back(&mSudoku[i][j]);
				mCols[i].push_back(&mSudoku[j][i]);
                mSudoku[i][j].setRelatedRow(&mRows[i]);
                mSudoku[j][i].setRelatedCol(&mCols[i]);

				int group = (int(j/3)) + (int(i/3))*3;
				mGrps[group].push_back(&mSudoku[i][j]);
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
		for(auto i:mCols){
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