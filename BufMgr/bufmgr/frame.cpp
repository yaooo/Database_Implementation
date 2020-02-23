#include "../include/frame.h"
#include "../include/db.h"

Frame:: Frame(){
	this -> data = new Page();
	EmptyIt();
}

Frame:: ~Frame(){
	if (this->IsDirty())
	{
		this->Write();
	}
	delete data;
}
void Frame:: Pin(){
	pinCount ++;
}

void Frame:: Unpin(){
	if(pinCount > 0){
		pinCount --;
		if(this -> NotPinned())
			this-> timestamp = clock();
	}
}

void Frame:: EmptyIt(){
	this -> pid = -1;
	this -> pinCount = 0;
	this -> dirty = false;
	this -> timestamp = clock();
	this -> referenced = false;
}

void Frame:: DirtyIt(){
	dirty = true;
}

void Frame:: SetPageID(PageID pid){
	this -> pid = pid;
}

Bool Frame:: IsDirty(){
	return this-> dirty;
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
	PageID pid = this -> pid;
	this -> EmptyIt();
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


clock_t Frame::GetTimestamp()
{
	return this->timestamp;
}