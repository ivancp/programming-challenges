#include <iostream>
#include <vector>
#include <map>

#define SIZE 9

using namespace std;
enum GroupType{
	ROW,
	COL,
	GRP
} ;



class Sudoku{

	struct POS{
		int i;
		int j;
	};
    struct UNIQUE;
	typedef UNIQUE* UNIQUEPtr;
	struct PROB;
	

	struct PROBABILITY{
		double total = 0;
		double row = 0;
		double col = 0;
		double grp = 0;
	};

	class Cell{
	 public:
		int value = 0;
		POS pos;
		 
		map<int,PROBABILITY> possible;
        Cell(int i, int j){
			pos.i = i;
			pos.j = j;
            for(int v = 1 ; v <= 9;v++){
				possible[v] = PROBABILITY();
			}
        }
        void clearPossible(){
            possible.clear();
        }
        int removePossible(int val){
			//possible.erase(std::remove(possible.begin(), possible.end(), val),possible.end());

			map<int,PROBABILITY>::iterator it = possible.find(val);
			if(it != possible.end()){
				possible.erase(it);
			}

			
			return possible.size();
        }

        bool setValue(int val){
            if(isValuePossible(val)){
                value = val;
                clearPossible();
                return true;
            }
            return false;
        }

		bool isValuePossible(int val){
			map<int,PROBABILITY>::iterator it = possible.find(val);
			return (it != possible.end());

			/*if(std::find(possible.begin(), possible.end(), val) != possible.end()){
				return true;
			}
			return false;*/
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
    

	struct PROB{
		int num;
		double prob;
		CellPtr cell;
		PROB(int a,double pr,CellPtr p):num(a),prob(pr),cell(p){}
	};
	static bool compare(PROB a ,PROB b){
		return a.prob > b.prob;
	}
	vector<PROB> result;

	struct UNIQUE{
		vector<CellPtr> mCells;
		//map<int,PROBABILITY> missing;
		vector<int> missing;
		bool solved;
		UNIQUE(){
			solved = false;
			for(int i = 1 ; i <= SIZE; i++){
				//missing[i] = PROBABILITY();
				missing.push_back(i);
			}
		}

		int removeMissing(int val){
			/*map<int,PROBABILITY>::iterator it = missing.find(val);
			if(it != missing.end()){
				missing.erase(it);
			}*/
			missing.erase(std::remove(missing.begin(), missing.end(), val),missing.end());
			return missing.size();
		}

		void addCell(CellPtr ptr){
			mCells.push_back(ptr);
		}

		void sumProbability(vector<PROB> &result){
			for(auto cell: mCells){
				for(auto possible : cell->possible){
					possible.second.total = possible.second.col + possible.second.row + possible.second.grp;
					//cout<<" Prob: ["<<cell->pos.i<<","<<cell->pos.j<<"] => "<<possible.first<<": "<<possible.second.total<<endl;
					result.push_back(PROB(possible.first,possible.second.total,cell));
				}
			}

		}
		void calcProbability(GroupType type){
			for(auto number: missing){
				double count = 0.0;
				for(auto cell: mCells){
					if(cell->isValuePossible(number)){
						count = count + 1.0;
					}
				}

				if(count > 0){
					double percent = 1/count;
					for(auto cell: mCells){
						if(cell->isValuePossible(number)){
							switch(type){
								case COL:
									cell->possible[number].col = percent;
								break;
								case ROW:
									cell->possible[number].row = percent;
								break;
								case GRP:
									cell->possible[number].grp = percent;
								break;
							}
						}
					}

				}
			}
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
						cout<<"Found 1 in row"<<i<<","<<j<<" after remove "<<val<<" leaved "<<r->possible.begin()->first<<endl;
						checkStack.push_back(r->pos);
					}
                }
				row->removeMissing(val);
            }
            UNIQUEPtr col = mSudoku[i][j].relatedCol;
            if(col != nullptr){
                for(auto c: col->mCells){
                    if(c->removePossible(val) == 1){
						cout<<"Found 1 in col"<<i<<","<<j<<" after remove "<<val<<" leaved "<<c->possible.begin()->first<<endl;
						checkStack.push_back(c->pos);
					}
                }
				col->removeMissing(val);
            }

            UNIQUEPtr grp = mSudoku[i][j].relatedGrp;
            if(grp != nullptr){
                for(auto g: grp->mCells){
                    if(g->removePossible(val) == 1){
						cout<<"Found 1 in grp"<<i<<","<<j<<" after remove "<<val<<" leaved "<<g->possible.begin()->first<<endl;
						checkStack.push_back(g->pos);
					}
                }
				grp->removeMissing(val);
            }
            return true;
        }
        return false;
    }

public:
	Sudoku(){
		init();
	}

	int solve(){
		int inserted = 0;
		while(checkStack.size() > 0){

			POS p = checkStack[0];
			CellPtr cell = &mSudoku[p.i][p.j];
			cout<<"checking "<<cell->possible.begin()->first<<" in "<<p.i<<","<<p.j<<endl;
			if(cell->possible.size() == 1){
				
				insert(p.i,p.j,cell->possible.begin()->first);
				inserted++;
			}
			checkStack.erase(checkStack.begin());
		}
		return inserted;
	}
	int find1Missing(){
		return find1Missing(mRows) +
				find1Missing(mCols) + 
				find1Missing(mGrps);
	}

	void calcProbability(){
		for(auto row:mRows){
			row.calcProbability(ROW);
		}
		for(auto col:mCols){
			col.calcProbability(COL);
		}
		for(auto grp:mGrps){
			grp.calcProbability(GRP);
		}

		for(auto row:mRows){
			row.sumProbability(result);
		}

		sort(result.begin(), result.end(), compare);

		for(auto item : result){
			
			cout<<" Prob: ["<<item.cell->pos.i<<","<<item.cell->pos.j<<"] => "<<item.num<<": "<<item.prob<<endl;
			if(item.prob >= 1.5){
				insert(item.cell->pos.i,item.cell->pos.j,item.num);
			}
		}
		
	}

	int find1Missing(vector<UNIQUE> cells){
		int inserted = 0;
		for(auto row: cells){
			for(auto number: row.missing){
				int count = 0;
				CellPtr currCell = nullptr;
				for(auto cell: row.mCells){
					if(cell->isValuePossible(number)){
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
					inserted++;
				}
			}
		}
		return inserted;
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
                    cout<< possible.first;
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