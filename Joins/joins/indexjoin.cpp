#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctime>

#include "../include/minirel.h"
#include "../include/heapfile.h"
#include "../include/scan.h"
#include "../include/join.h"
#include "../include/btfile.h"
#include "../include/btfilescan.h"
#include "../include/relation.h"
#include "../include/bufmgr.h"



//---------------------------------------------------------------
// Each join method takes in at least two parameters :
// - specOfS
// - specOfR
//
// They specify which relations we are going to join, which 
// attributes we are going to join on, the offsets of the 
// attributes etc.  specOfS specifies the inner relation while
// specOfR specifies the outer one.
//
//You can use MakeNewRecord() to create the new result record.
//
// Remember to clean up before exiting by "delete"ing any pointers
// that you "new"ed.  This includes any Scan/BTreeFileScan that 
// you have opened.
//---------------------------------------------------------------

BTreeFile *buildBTree( JoinSpec specOfS)
{
	Status status = OK;

    std::clock_t start;
    start = std::clock();

    // build the heap file for the innere relation
    Scan *scan = specOfS.file ->OpenScan(status);
    if(status != OK){
        exit(1);
    }

    int len = specOfS.recLen;
    int offset = specOfS.offset;

	BTreeFile *btree;
	btree = new BTreeFile (status, "BTree", ATTR_INT, sizeof(int));

	char *recPtr = new char[len];
	int recLen = len;
	RecordID rid;
	while (scan->GetNext(rid, recPtr, recLen) == OK)
	{
		btree->Insert(recPtr + offset, rid);
	}
	delete scan;
	delete [] recPtr;
	return btree;
}

void IndexNestedLoopJoin(JoinSpec specOfR, JoinSpec specOfS, long& pinRequests, long& pinMisses, double& duration)
{
    MINIBASE_BM->ResetStat();
    Status status = OK;

    std::clock_t start;
    start = std::clock();

    // scan the frist file
    Scan* scanR = specOfR.file -> OpenScan(status);
    if(status != OK){
        exit(1);
    }

    // build btree for s, and set up btreescan
    BTreeFile* btree = buildBTree(specOfS);

	

    // build the btree for the innere relation
    specOfS.file ->OpenScan(status);
    if(status != OK){
        exit(1);
    }


    // create heap file for the final result
    HeapFile* res = new HeapFile(NULL, status);
    if(status != OK){
        exit(1);
    }

    int recLenR = specOfR.recLen;
    int recLenS = specOfS.recLen;
    int recLenT = recLenS + recLenS;

    int offsetR = specOfR.offset;

    char* recPtrR = new char[recLenR];
    char* recPtrS = new char[recLenS];
    char* recPtrT = new char[recLenT];

    RecordID ridR, ridS, ridT;


    while(scanR->GetNext(ridR, recPtrR, recLenR) == OK){
        int key;
        int* joinAttrR = (int *)(recPtrR + offsetR);
        BTreeFileScan  *btreeScan = (BTreeFileScan*)btree->OpenSearchScan(joinAttrR, joinAttrR);
        while(OK == btreeScan -> GetNext(ridS, &key)){
            specOfS.file -> GetRecord(ridS, recPtrS, recLenS);
            MakeNewRecord(recPtrT, recPtrR, recPtrS, recLenR, recLenS);
            res->InsertRecord(recPtrT, recLenT, ridT);
        }
        delete btreeScan;
    }


    btree->DestroyFile();
	delete btree;
    delete scanR;
    delete[] recPtrR, recPtrS, recPtrT;
    delete res;

    MINIBASE_BM->GetStat(pinRequests, pinMisses);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

}
