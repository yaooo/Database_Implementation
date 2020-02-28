#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctime>

#include "../include/minirel.h"
#include "../include/heapfile.h"
#include "../include/scan.h"
#include "../include/join.h"
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



void TupleNestedLoopJoin(JoinSpec specOfR, JoinSpec specOfS, long& pinRequests, long& pinMisses, double& duration){
    MINIBASE_BM->ResetStat();
    Status status = OK;

    std::clock_t start;
    start = std::clock();

    // scan the frist file
    Scan* scanR = specOfR.file -> OpenScan(status);
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
    int recLenRes = recLenS + recLenS;

    int offsetR = specOfR.offset;
    int offsetS = specOfS.offset;

    char* recPtrR = new char[recLenR];
    char* recPtrS = new char[recLenS];
    char* recPtrRes = new char[recLenRes];

    RecordID ridR, ridS, ridRes;

    while(scanR->GetNext(ridR, recPtrR, recLenR) == OK){
        Scan* scanS = specOfS.file -> OpenScan(status);
        if(status != OK){
            exit(1);
        }
        int* joinAttrR = (int *)(recPtrR + offsetR);

        while(scanS->GetNext(ridS, recPtrS, recLenS) == OK){
            int* joinAttrS = (int *)(recPtrS + offsetS);
            if(joinAttrR == joinAttrS){
                MakeNewRecord(recPtrRes, recPtrR, recPtrS, recLenR, recLenS);
                res->InsertRecord(recPtrRes, recLenRes, ridRes);
            }
        }
        delete scanS;
    }

    delete scanR;
    delete[] recPtrR, recPtrS, recPtrRes;
    delete res;

    MINIBASE_BM->GetStat(pinRequests, pinMisses);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
}
