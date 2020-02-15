#include "../include/frame.h"
#include "../include/db.h"

Frame:: Frame(){
	this -> pid = -1;
	this -> data = new Page();
	this -> pinCount = 0;
	this -> dirty = 0;
	this -> referenced = false;
}

Frame:: ~Frame(){
	delete data;
}
void Frame:: Pin(){
	pinCount ++;
}
void Frame:: Unpin(){
	pinCount --;
}

void Frame:: EmptyIt(){
	this -> pid = -1;
	this -> data = new Page();
	this -> pinCount = 0;
	this -> dirty = 0;
	this -> referenced = false;
}

void Frame:: DirtyIt(){
	dirty = 1;
}

void Frame:: SetPageID(PageID pid){
	this -> pid = pid;
}

Bool Frame:: IsDirty(){
	return this-> dirty == 1;
}

Bool Frame:: IsValid(){
	return this -> pid != -1;
}

Status Frame:: Write(){
	return MINIBASE_DB -> WritePage(pid, data);
}

Status Frame:: Read(PageID pid){
	if(MINIBASE_DB -> ReadPage(pid, data) != OK){
		return FAIL;
	}
	this-> pid = pid;
	return OK;
}

Status Frame:: Free(){
	if(pinCount > 1)
		return FAIL;
	EmptyIt();

	return MINIBASE_DB -> DeallocatePage(pid);
}

Bool Frame:: NotPinned(){
	return pinCount == 0;
}

Bool Frame:: HasPageID(PageID pid){
	return this->pid == pid;
}

PageID Frame:: GetPageID(){
	return this->pid;
}

Page* Frame:: GetPage(){
	return data;
}

// void UnsetReferenced(){
// 	referenced = false;
// }
// Bool IsReferenced(){
// 	return referenced;
//}

// Bool IsVictim(){
// 	return (pinCount == 0 && !referenced);
// }