#ifndef BOOK_H
#define BOOK_H

#include "afxwin.h"
#include "Shelf.h"

using namespace std;

class Book : public Shelf
{
public:

	DECLARE_SERIAL(Book);

	Book(CString title_new) :
	title(title_new) {}

	Book(void){}

	Book(const Book& other);

	~Book(void){}

	const Book& Book::operator<(const Book& other) const;

	const Book& Book::operator>(const Book& other) const;

	void set_title(CString title_new) { title = title_new; }

	CString get_title() const { return title; }

	void Use()
	{
		CString toPrint = _T("Reading Book ");
		toPrint += title;
		AfxMessageBox(toPrint);
	}

	void Serialize(CArchive& ar);

private:
	CString title;
};

inline const Book& Book::operator<(const Book& other) const { return *this; }

inline const Book& Book::operator>(const Book& other) const { return *this; }

IMPLEMENT_SERIAL(Book,Shelf,1)

void Book::Serialize(CArchive& ar){
	if (ar.IsStoring())
	{
		ar << get_title();
	}
	else
	{
		CString title_temp;
		ar >> title_temp;
		set_title(title_temp);
	}
}


#endif
