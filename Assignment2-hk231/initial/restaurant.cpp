#include "main.h"
int MAXSIZE;
void simulate(string filename)
{
	ifstream ss(filename);
	string str, maxsize, name, energy, num;
	while(ss >> str)
	{ 
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
			cout << MAXSIZE; 
    	}
		if(str == "LAPSE"){
			cout << 5 ;
		}else{
			cout << 5555;
		}
	};
}
void LAPSE(string name){
	cout << 5;
}
void HAND(){

}
void LIMITLESS(){

}
void KEITEIKEN(){

}
void KOKUSEN(){

}
void CLEAVE(){

}