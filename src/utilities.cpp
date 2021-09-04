/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

vector <process_stats> structs;

int loadData(const char* filename, bool ignoreFirstRow) {
	//clear vector
	structs.clear();

	ifstream readfile;
	readfile.open(filename);

	//vibe check
	if (!readfile){
		return COULD_NOT_OPEN_FILE;
	}

	//begin reading in
	while (!readfile.eof()) {
			process_stats prostate;
			string line;
			getline(readfile, line);
			stringstream rows;
			rows.str(line);
			string str;
			if (ignoreFirstRow){
				ignoreFirstRow = false;
				continue;
			}
			if (!getline(rows, str, ',') || str.empty()){
				continue;
			}
			prostate.process_number = stringToInt(str.c_str());
			if (!getline(rows, str, ',') || str.empty()){
				continue;
			}
			prostate.start_time = stringToInt(str.c_str());
			if (!getline(rows, str, ',') || str.empty()){
				continue;
			}
			prostate.cpu_time = stringToInt(str.c_str());
			if (!getline(rows, str) || str.empty()){
				continue;
			}
			prostate.io_time = stringToInt(str.c_str());
			if (!str.empty()){
				structs.push_back(prostate);
			}
		}
		return SUCCESS;
	}

//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	auto compareTo = [mySortOrder](const process_stats &struct1, const process_stats &struct2) {
		switch (mySortOrder) {
				case SORT_ORDER::PROCESS_NUMBER:
					return struct1.process_number < struct2.process_number;
				case SORT_ORDER::START_TIME:
					return struct1.start_time < struct2.start_time;
				case SORT_ORDER::CPU_TIME:
					return struct1.cpu_time < struct2.cpu_time;
				case SORT_ORDER::IO_TIME:
					return struct1.io_time < struct2.io_time;
				default:
					break;
			}
		};
	sort(begin(structs),end(structs), compareTo);
}
//deletes first element
process_stats getNext() {
	process_stats myFirst;
	myFirst = structs.front();
	structs.erase(structs.begin());
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return structs.size();
}
