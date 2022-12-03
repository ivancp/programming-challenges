#include <iostream>
#include <vector>
#include <map>
#define SIZE 9

using namespace std;

class Sudoku{

    
	struct Cell{
		int value = 0;
		map<int,bool> possible;
        Cell(){
            clearPossible(true);
        }
        void clearPossible(bool flag){
            for(int i = 1; i <= 9; i++){
                possible[i] = flag;
            }
        }
        void removePossible(int val){
            possible[val] = false;
        }
        bool setValue(int val){
            if(possible[val] == true){
                value = val;
                clearPossible(false);
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
	
    bool insert(int i, int j, int val){
        
        if(mSudoku[i][j].setValue(val)){
            RowPtr row = mSudoku[i][j].relatedRow;
            if(row != nullptr){
                for(auto r: *row){
                    r->removePossible(val);
                }
            }
            RowPtr col = mSudoku[i][j].relatedCol;
            if(col != nullptr){
                for(auto c: *col){
                    c->removePossible(val);
                }
            }

            RowPtr grp = mSudoku[i][j].relatedGrp;
            if(grp != nullptr){
                for(auto g: *grp){
                    g->removePossible(val);
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
	void init(){
		for(int i = 0 ; i < SIZE;i++){
			mSudoku.push_back( vector<Cell>());
			mRows.push_back(vector<CellPtr>());
			mCols.push_back(vector<CellPtr>());
            mGrps.push_back(vector<CellPtr>());
			for(int j = 0 ; j < SIZE;j++){
				mSudoku[i].push_back(Cell());
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
                    if(possible.second == true){
                       cout<< possible.first;
                    }else{
                        cout<< " ";
                    }
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