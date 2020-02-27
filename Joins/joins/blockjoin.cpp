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

void BlockNestedLoopJoin(JoinSpec specOfR, JoinSpec specOfS, int B, long& pinRequests, long& pinMisses, double& duration)
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

    // create heap file for the final result
    HeapFile* res = new HeapFile(NULL, status);
    if(status != OK){
        exit(1);
    }

    int recLenR = specOfR.recLen;
    int recLenS = specOfS.recLen;
    int recLenT = recLenS + recLenS;
    int pagePerBlock = recLenR/B;

    int offsetR = specOfR.offset;
    int offsetS = specOfS.offset;

    char* recPtrR = new char[recLenR];
    char* recPtrS = new char[recLenS];
    char* recPtrT = new char[recLenT];
    char* recPtrBlock = new char[B];

    RecordID ridR, ridS, ridT;

    int index = 0;

    // For each block b in R (need to fix this line)
    while(scanR->GetNext(ridR, recPtrBlock + index * recLenR, recLenR) == OK){
        // fill up th block before matching tuples
        while(index ++ < pagePerBlock) continue;
        index = 0;
        
        Scan* scanS = specOfS.file -> OpenScan(status);
        if(status != OK){
            exit(1);
        }
        // for each tuple in S (Done)
        while(scanS->GetNext(ridS, recPtrS, recLenS) == OK){
            int* joinAttrS = (int *)(recPtrS + offsetS);

            // // For each tuple r in b (Done)
            for(int i = 0; i < pagePerBlock; i++){
                int* joinAttrB = (int *)(recPtrBlock + i * recLenR + offsetR);
                if(joinAttrB == joinAttrS){
                MakeNewRecord(recPtrT, recPtrR, recPtrS, recLenR, recLenS);
                res->InsertRecord(recPtrT, recLenT, ridT);
            }
            }
        }
        delete scanS;
        delete[] recPtrBlock;
        recPtrBlock = new char[B];
    }

    // in case the block is fully filled for the remaining tuples
    if(index != 0){
        Scan* scanS = specOfS.file -> OpenScan(status);
        if(status != OK){
            exit(1);
        }
        // for each tuple in S (Done)
        while(scanS->GetNext(ridS, recPtrS, recLenS) == OK){
            int* joinAttrS = (int *)(recPtrS + offsetS);

            // // For each tuple r in b (Done)
            for(int i = 0; i < pagePerBlock; i++){
                int* joinAttrB = (int *)(recPtrBlock + i * recLenR + offsetR);
                if(joinAttrB == joinAttrS){
                MakeNewRecord(recPtrT, recPtrR, recPtrS, recLenR, recLenS);
                res->InsertRecord(recPtrT, recLenT, ridT);
            }
            }
        }
        delete scanS;
        delete[] recPtrBlock;
        recPtrBlock = new char[B];
    }

    delete scanR;
    delete[] recPtrR, recPtrS, recPtrT;
    delete res;

    MINIBASE_BM->GetStat(pinRequests, pinMisses);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
}
