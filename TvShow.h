#ifndef TVSHOW_H
#define TVSHOW_H

#include "Video.h"
#include "afxwin.h"

class TvShow :public Video
{
public:

	TvShow(CString title_new ) : title(title_new) , next(nullptr)
	{
			AfxMessageBox(_T("New TvShow added to Basket"));	
	}

	TvShow(void){}

	~TvShow(void){}

	void Use(CString title_to_compare) 
	{
		if(this->title == title_to_compare)AfxMessageBox(_T("Watching NetFlix"));
		else next->Use(title_to_compare);
	}

	CString get_title() {return this->title;}

	TvShow* insert(CString title)
	{
		if(next == nullptr) 
		{
			next = new TvShow(title);
			return next;
		}

		else
		{
			next->insert(title);
			return next;
		}
	}

	bool exists(CString title_to_compare)
	{
		if(this->title == title_to_compare){ return true;} 
		else if(next == nullptr) {return false;}
		else {return next->exists(title_to_compare);}
	}

	void set_title(CString title_old,CString title_new)
	{
		if(this->title == title_old) this->title = title_new;
		else next->set_title(title_old , title_new);
	}


private:
	CString title;
	TvShow *next;

};


#endif