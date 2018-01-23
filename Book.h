#ifndef BOOK_H
#define BOOK_H

#include "afxwin.h"
#include "Shelf.h"
#include "TvShow.h"

using namespace std;
class Book : public Shelf
{
public:

	Book(CString title_new ) : title(title_new) , next(nullptr)
	{
		AfxMessageBox(_T("New book added to Basket"));
	}

	Book(void) : title(""){}

	Book& GetFont() { return this; }

	~Book(void){}

	void Use(CString title_to_compare) override
	{
		if(this->title == title_to_compare)AfxMessageBox(_T("Reading book"));
		else next->Use(title_to_compare);
	}

	CString get_title() override
	{
		return title;
	}

	Book* insert(CString title) 
	{
		if(next == nullptr) 
		{
			next = new Book(title);
			return next;
		}

		else {return next->insert(title);}
	}

	bool exists(CString title_to_compare)override
	{
		if(this->title == title_to_compare){ return true;} 
		else if(next == nullptr) {return false;}
		else {return next->exists(title_to_compare);}
	}

	void set_title(CString title_old,CString title_new)override
	{
		if(this->title == title_old) this->title = title_new;
		else next->set_title(title_old , title_new);
	}

	void set_next(Book *next_new)
	{
		next = next_new;
	}

	Book* get_next()
	{
		return next;
	} 

	void set_prev(Book *prev_new)
	{
		prev = prev_new;
	}

	Book* get_prev()
	{
		return next;
	} 



private:
	CString title;
	Book *next;
	Book *prev;

};

#endif
