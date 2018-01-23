#ifndef VIDEO_H
#define VIDEO_H

#include "afxwin.h"
#include "Shelf.h"
#include "TvShow.h"

using namespace std;

class Video :public Shelf
{
public:

	Video(void){}

	~Video(void){}

	virtual void Use(CString title_to_compare) = 0;

	virtual bool exists(CString title_to_compare) = 0;

	virtual CString get_title() = 0;
	
	virtual void set_title(CString title_old,CString title_new) = 0;

};
#endif


