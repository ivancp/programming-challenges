#include <iostream>
#include <map>
#include <vector>

using namespace std;


int main(int argc, char *argv[]){
	int testCases = 0;
	int currentCase = 1;
	cin>>testCases;

	while(currentCase <= testCases){
		int Z;
		int sum = 0;
		int num = 0 ;

		map<int,int> repeated_col;
		map<int,int>::iterator it;
		int row_repeated_count = 0;
		int col_repeated_count = 0;

		cin>>Z;

		vector<map<int,int>> map_cols(Z);
		vector<int> map_cols_count(Z);


		for(int i = 0 ; i < Z;i++){

			map<int,int> row_numbers;
			bool repeated_row_found = false;
			for(int j = 0 ; j < Z;j++){
				cin>>num;

				if(i == j){
					sum += num;
				}
				if(!repeated_row_found){
					it = row_numbers.find(num);
					if (it == row_numbers.end()){
						row_numbers[num] = 1;
					}else{
						repeated_row_found = true;
						row_repeated_count++;
					}
				}

				if(map_cols_count[j] == 0){
					it = map_cols[j].find(num);
					if (it == map_cols[j].end()){
						map_cols[j][num] = 1;
					}else{
						map_cols_count[j] = 1;
						col_repeated_count++;
					}					
				}

			}
		}

		cout<<"Case #"<<currentCase++<<": "
			<<sum<<" "
			<<row_repeated_count<<" "
			<<col_repeated_count
			<<endl;
	}

    return 0;
}