#include <climits>
#include "../include/replacer.h"

Replacer::Replacer()
{

}

Replacer::~Replacer()
{

}

Clock::Clock( int bufSize, Frame **frames){
	this->numOfBuf = bufSize;
	this -> frames = frames;
}


Clock::~Clock()
{

}

int Clock::PickVictim(){

	clock_t timestamp = clock() + 9999;
	int index = INVALID_FRAME;
	Frame* f;

	for (int i = 0; i < numOfBuf; i++) {
		f = frames[i];
		if (f->NotPinned()) {
			// find the earliest timestamp, update the timestamp when unpin
			if(f->GetTimestamp() < timestamp){
				timestamp = f->GetTimestamp();
				index = i;
			}
		}
	}
	return index;
}