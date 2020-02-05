#include <iostream>
#include <stdlib.h>
#include <memory.h>

#include "../include/heappage.h"
#include "../include/heapfile.h"
#include "../include/bufmgr.h"
#include "../include/db.h"

using namespace std;

//------------------------------------------------------------------
// Constructor of HeapPage
//
// Input     : Page ID
// Output    : None
//------------------------------------------------------------------

void HeapPage::Init(PageID pageNo){
	nextPage = INVALID_PAGE;
	prevPage = INVALID_PAGE;
	numOfSlots = 0;
	pid = pageNo;
	fillPtr = 0;
	freeSpace = HEAPPAGE_DATA_SIZE;
}

void HeapPage::SetNextPage(PageID pageNo){
	nextPage = pageNo;
}

void HeapPage::SetPrevPage(PageID pageNo){
	prevPage = pageNo;
}

PageID HeapPage::GetNextPage(){
  return nextPage;
}

PageID HeapPage::GetPrevPage(){
  return prevPage;
}


bool HeapPage::invalidSlot(const RecordID& rid){
	return (rid.pageNo != pid || rid.slotNo >= numOfSlots ||
		rid.slotNo < 0 || slots[rid.slotNo].length == -1);
}
//------------------------------------------------------------------
// HeapPage::InsertRecord
//
// Input     : Pointer to the record and the record's length 
// Output    : Record ID of the record inserted.
// Purpose   : Insert a record into the page
// Return    : OK if everything went OK, DONE if sufficient space 
//             does not exist
//------------------------------------------------------------------

Status HeapPage::InsertRecord(char *recPtr, int length, RecordID& rid)
{
	if(AvailableSpace() < length) return DONE;

	int index = 0;
	while(index < numOfSlots){
		if(slots[index].length == -1){
			break;
		}
		index++;
	}

	int memory = length + ((index >= numOfSlots)? sizeof(Slot):0);

	// enough memory
	SLOT_FILL(slots[index], fillPtr, length);
	
	// insert new record
	memcpy(&data[HEAPPAGE_DATA_SIZE - fillPtr - length], recPtr, length);
	
	if(index >= numOfSlots)	numOfSlots++;
	rid.pageNo = pid;
	rid.slotNo = index;
	freeSpace -= memory;
	fillPtr += length;
	return OK;

}


//------------------------------------------------------------------
// HeapPage::DeleteRecord 
//
// Input    : Record ID
// Output   : None
// Purpose  : Delete a record from the page
// Return   : OK if successful, FAIL otherwise  
//------------------------------------------------------------------ 

Status HeapPage::DeleteRecord(const RecordID& rid){
	if (invalidSlot(rid)){
		return FAIL;
	}

	int length = slots[rid.slotNo].length;
	int offset = slots[rid.slotNo].offset;

	// directly remove the last slot 
	if(numOfSlots - 1 == rid.slotNo){
		numOfSlots--;
		freeSpace += sizeof(Slot);
	}else{
		// length of the moved bits
		int len = 0;
		for(int i = 0; i < sizeof(slots)/sizeof(Slot); i++){
			if(slots[i].length != -1 && slots[i].offset > offset){
				slots[i].offset -= length;
				len += slots[i].length;
			}
		}
		memmove(&data[HEAPPAGE_DATA_SIZE - fillPtr + length], &data[HEAPPAGE_DATA_SIZE - fillPtr], len);
	}

	// make updates over the removed slot, and other parameters
	freeSpace += length;
	fillPtr -= length;
	slots[rid.slotNo].length = -1;
	return OK;
}


//------------------------------------------------------------------
// HeapPage::FirstRecord
//
// Input    : None
// Output   : record id of the first record on a page
// Purpose  : To find the first record on a page
// Return   : OK if successful, DONE otherwise
//------------------------------------------------------------------

Status HeapPage::FirstRecord(RecordID& rid)
{
	for (int i = 0; i < sizeof(slots)/sizeof(Slot); i++)
	{
		if (!SLOT_IS_EMPTY(this->slots[i])){
			rid.pageNo = pid;
			rid.slotNo = i;
			return OK;
		}
	}
	return DONE;
}


//------------------------------------------------------------------
// HeapPage::NextRecord
//
// Input    : ID of the current record
// Output   : ID of the next record
// Return   : Return DONE if no more records exist on the page; 
//            otherwise OK
//------------------------------------------------------------------

Status HeapPage::NextRecord (RecordID curRid, RecordID& nextRid){
	if (invalidSlot(curRid)){
		return FAIL;
	}

	for (int i = curRid.slotNo + 1; i < numOfSlots; i++){
		if (slots[i].length != -1){
			nextRid.pageNo = pid;
			nextRid.slotNo = i;
			return OK;
		}
	}
	return DONE;
}


//------------------------------------------------------------------
// HeapPage::GetRecord
//
// Input    : Record ID
// Output   : Records length and a copy of the record itself
// Purpose  : To retrieve a _copy_ of a record with ID rid from a page
// Return   : OK if successful, FAIL otherwise
//------------------------------------------------------------------

Status HeapPage::GetRecord(RecordID rid, char *recPtr, int& length){
	if (invalidSlot(rid)){
		return FAIL;
	}

	length =  slots[rid.slotNo].length;
	int offset = slots[rid.slotNo].offset;
	char* src = &data[HEAPPAGE_DATA_SIZE - offset - length];
	memcpy(recPtr, src , length);
    return OK;
}


//------------------------------------------------------------------
// HeapPage::ReturnRecord
//
// Input    : Record ID
// Output   : pointer to the record, record's length
// Purpose  : To output a _pointer_ to the record
// Return   : OK if successful, FAIL otherwise
//------------------------------------------------------------------

Status HeapPage::ReturnRecord(RecordID rid, char*& recPtr, int& length)
{
	if (invalidSlot(rid)){
		return FAIL;
	}
	length =  slots[rid.slotNo].length;
	int offset = slots[rid.slotNo].offset;

	recPtr = &data[HEAPPAGE_DATA_SIZE - offset - length];
	
    return OK;
}


//------------------------------------------------------------------
// HeapPage::AvailableSpace
//
// Input    : None
// Output   : None
// Purpose  : To return the amount of available space
// Return   : The amount of available space on the heap file page.
//------------------------------------------------------------------

int HeapPage::AvailableSpace(void){
	return freeSpace - sizeof(Slot);
}


//------------------------------------------------------------------
// HeapPage::IsEmpty
// 
// Input    : None
// Output   : None
// Purpose  : Check if there is any record in the page.
// Return   : true if the HeapPage is empty, and false otherwise.
//------------------------------------------------------------------

bool HeapPage::IsEmpty(void){
	return (GetNumOfRecords() == 0);
}


void HeapPage::CompactSlotDir(){
	int count = 0;	// number of empty slots
	int length = 0;	//data length + size of slots

	for(int i = 0; i < numOfSlots; i++){
		if(slots[i].length == -1){
			count ++;
		}else{
			length += slots[i].length + sizeof(Slot);

			// move the non-empty slot to the empty spot
			slots[i - count] = slots[i];
			SLOT_SET_EMPTY(Slot[i-count]);
		}
	}
	// update parameters
	numOfSlots -= count;
	freeSpace = length;
}

int HeapPage::GetNumOfRecords(){
	return numOfSlots;
}
