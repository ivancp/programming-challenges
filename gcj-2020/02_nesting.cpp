#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct ITEM{
	int num;
	int length;
	int par;
	ITEM(){
		par = 0;
		length = 1;
	}
	string print(){
		string ret;
		string snum = std::to_string(num);
		for(int i = 0 ; i < length; i++){
			ret += snum;
		}
		for(int i = 0 ; i < num; i++){
			ret = "(" + ret + ")";
		}
		return ret ;
	}
};

int main(int argc, char *argv[]){
	int testCases = 0;
	int currentCase = 1;
	cin>>testCases;


	while(currentCase <= testCases){

		string line;
		int prevNum = -1;
		int prevIndex = -1;
		cin>>line;
		vector<ITEM> items;

		for(int i = 0 ; i < line.size() ; i++){
			ITEM item;
			item.num = line[i] - '0';
			
			if(item.num > 0){
				int nextPos = i + 1;
				while(nextPos < line.size()){
					int nextNum = line[nextPos] - '0';
					if(nextNum == item.num){
						item.length += 1;
						nextPos++;
					}else{
						break;
					}
				}
				if(item.length > 1){
					i = nextPos -1;
				}
			}
			items.push_back(item);
		}
		
		cout<<"Case #"<<currentCase++<<": ";

		string result;
		for(int i = 0 ; i < items.size() ; i++){
			result += items[i].print();
			
		}

		string ppp = ")(";
		std::size_t found = result.find(ppp);

		while(found != std::string::npos){

			result.erase(found,2);
			found = result.find(ppp);
		}

	    cout<<result<<endl;
	}
    return 0;
}