#ifndef VIDEO_H
#define VIDEO_H

#include "afxwin.h"
#include "Shelf.h"

using namespace std;

class Video :public Shelf
{
public:

	DECLARE_SERIAL(Video);

	Video(void){}

	~Video(void){}

	virtual void Use() {}
	
	void set_title(CString title_new) {}

	void Serialize(CArchive& ar);

};

IMPLEMENT_SERIAL(Video,Shelf,1)

void Video::Serialize(CArchive& ar){
	if (ar.IsStoring())
	{
		ar<<  "";
	}
	else
	{
		CString none;
		ar >> none;
	}
}
#endif


