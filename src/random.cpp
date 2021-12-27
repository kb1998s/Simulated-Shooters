//============================================================================
// Name        : Project.cpp
// Author      : Vito Luong
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <sys/time.h> // Delete this line on MSW
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;
//========================================================================//
//========================================================================//
struct Dominoes{
	int head;
	int tail;
};
class CRandom{
	public:
		CRandom(){}  // constructor
		~CRandom(){} // destructor
		int getRandomPublic(int rangeLow, int rangeHigh){
			int myRand_scaled;
			myRand_scaled=getRandomPrivate(rangeLow, rangeHigh);
		    return myRand_scaled;
		}
	private:// uniform distribution between rangeLow and rangeHigh
		int getRandomPrivate(int rangeLow, int rangeHigh) {
		    double myRand = rand()/(1.0 + RAND_MAX);
		    int range = rangeHigh - rangeLow + 1;
		    int myRand_scaled = (myRand * range) + rangeLow;
		    return myRand_scaled;
		}
	protected:// uniform distribution between rangeLow and rangeHigh
		int getRandomProtected(int rangeLow, int rangeHigh) {
		    double myRand = rand()/(1.0 + RAND_MAX);
		    int range = rangeHigh - rangeLow + 1;
		    int myRand_scaled = (myRand * range) + rangeLow;
		    return myRand_scaled;
		}
};
