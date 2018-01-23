#ifndef MOVIE_H
#define MOVIE_H

#include "Video.h"

class Movie :public Video
{
public:

	Movie(CString title_new) : title(title_new) , next(nullptr)
	{
		AfxMessageBox(_T("New movie added to Basket"));
	}

	Movie(void){}

	~Movie(void){}

	void Use(CString title_to_compare)
	{
		if(this->title == title_to_compare)AfxMessageBox(_T("Watching Movie"));
		else next->Use(title_to_compare);
	}

	CString get_title() {return this->title;}

	Movie* insert(CString title)
	{
		if(next == nullptr) 
		{
			next = new Movie(title);
			return next;
		}

		else return next->insert(title);
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
	Movie *next;

};

#endif