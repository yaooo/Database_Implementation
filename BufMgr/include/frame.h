#ifndef FRAME_H
#define FRAME_H

#include "page.h"

#define INVALID_FRAME -1

class Frame 
{
	private :
	
		PageID pid;
		Page   *data;
		int    pinCount;
		int    dirty;
		Bool referenced;
		clock_t timestamp;

	public :
		
		Frame();
		~Frame();
		void Pin();
		void Unpin();
		void EmptyIt();
		void DirtyIt();
		void SetPageID(PageID pid);
		Bool IsDirty();
		Bool IsValid();
		Status Write();
		Status Read(PageID pid);
		Status Free();
		Bool NotPinned();
		Bool HasPageID(PageID pid);
		PageID GetPageID();
		Page *GetPage();

		void UnsetReferenced();
		Bool IsReferenced();
		Bool IsVictim();
		clock_t GetTimestamp();

};

#endif
