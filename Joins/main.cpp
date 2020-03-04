#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "include/minirel.h"
#include "include/bufmgr.h"
#include "include/heapfile.h"
#include "include/join.h"
#include "include/relation.h"

int MINIBASE_RESTART_FLAG = 0;// used in minibase part

#define NUM_OF_DB_PAGES  2000 // define # of DB pages
// #define NUM_OF_BUF_PAGES 50 // define Buf manager size.You will need to change this for the analysis
#define ITERATION 5.0

void printStat(string name, int pinRequests, int pinMisses, double duration){
	cout << name << ":\nStats after "<< (int)ITERATION << " iterations" << endl;
	cout << "Average pinRequests: " << pinRequests/ITERATION << endl;
	cout << "Average pinMisses: " << pinMisses/ITERATION << endl;
	cout << "Average duration: " << duration/ITERATION << "s\n" << endl;
}

int main()
{
	Status s;

	int NUM_OF_BUF_PAGES[1] = {100};
	long pinRequests = 0;
	long pinMisses = 0;
	double duration = 0;

	for(int i : NUM_OF_BUF_PAGES){
		//
		// Initialize Minibase's Global Variables
		//
		cout << "\nNumber of buffer pages = " << i << endl;
		cout << "Number of Records in R:" << NUM_OF_REC_IN_R << " -- Number of records in S:" << NUM_OF_REC_IN_S << endl;

		cout << "----------------------------------------"<<endl;

		minibase_globals = new SystemDefs(s, 
			"MINIBASE.DB",
			"MINIBASE.LOG",
			NUM_OF_DB_PAGES,   // Number of pages allocated for database
			500,
			i,  // Number of frames in buffer pool
			NULL);
		
		//
		// Initialize random seed
		//
		srand(1);

		//
		// Create Random Relations R(outer relation) and S for joining. The definition is in relation.h, 
		// # of tuples: NUM_OF_REC_IN_R, NUM_OF_REC_IN_S in join.h
		//

		cerr << "Creating random records for relation R\n";
		CreateR();
		cerr << "Creating random records for relation S\n";
		CreateS();

		//
		// Initialize the specification for joins
		//

		JoinSpec specOfS, specOfR;

		CreateSpecForR(specOfR);
		CreateSpecForS(specOfS);

		string name;
		int x, y; double z;

		// Tuple join
		name = "Tuple Join";
		for(int i = 0; i < ITERATION; i++){
			TupleNestedLoopJoin(specOfR, specOfS, pinRequests, pinMisses, duration);
			x += pinRequests; y += pinMisses; z += duration;
		}
		printStat(name, x, y, z);
		x=0;y=0;z=0;

		// Block nested join
		name = "Block-nested Join";
		int B = (MINIBASE_BM->GetNumOfBuffers()-3*3)*MINIBASE_PAGESIZE;
		for(int i = 0; i < ITERATION; i++){
			BlockNestedLoopJoin(specOfR, specOfS, B, pinRequests, pinMisses, duration);
			x += pinRequests; y += pinMisses; z += duration;
		}
		printStat(name, x, y, z);
		x=0;y=0;z=0;

		// Index join
		name = "Index Join";
		for(int i = 0; i < ITERATION; i++){
			IndexNestedLoopJoin(specOfR, specOfS, pinRequests, pinMisses, duration);
			x += pinRequests; y += pinMisses; z += duration;
		}
		printStat(name, x, y, z);
		x=0;y=0;z=0;

		//delete the created database
		remove("MINIBASE.DB");
		delete minibase_globals;
	}
	return 1;
}
