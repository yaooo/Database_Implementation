#include "../include/frame.h"
#inlcude "../include/db.h"

Frame:: Frame(){
	pid = -1;
	data = new Page();
	pinCount = 0;
	dirty = 0;
	referenced = false;
}

Frame:: ~Frame(){
	delete data;
}
void Frame:: Pin(){
	pinCount ++；
}
void Frame:: Unpin(){
	pinCount --;
}

void Frame:: EmptyIt(){
	pid = -1;
	data = new Page();
	pinCount = 0;
	dirty = 0;
	referenced = false;
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

}
Status Frame:: Read(PageID pid);
Status Frame:: Free();
Bool Frame:: NotPinned();
Bool Frame:: HasPageID(PageID pid);
PageID Frame:: GetPageID();
Page Frame:: *GetPage();

void UnsetReferenced();
Bool IsReferenced();
Bool IsVictim();