#ifndef MOVIE_H
#define MOVIE_H

#include "Video.h"

class Movie : public Video
{
public:

DECLARE_SERIAL(Movie);

	Movie(CString title_new) :
		title(title_new)
	{
	}

	const Movie& Movie::operator<(const Movie& other) const;

	const Movie& Movie::operator>(const Movie& other) const;

	Movie(void)
	{
	}

	~Movie(void)
	{
	}

	void Use()  
	{ 
		CString toPrint = _T("Watching Movie ");
		toPrint += title;
		AfxMessageBox(toPrint);
	}

	CString get_title() { return this->title; }

	void set_title(CString title_new) { this->title = title_new; }

	void Serialize(CArchive& ar);

private:
	CString title;
};

const Movie& Movie::operator<(const Movie& other) const { return *this; }

const Movie& Movie::operator>(const Movie& other) const { return *this; }

IMPLEMENT_SERIAL(Movie,Video,1)

void Movie::Serialize(CArchive& ar)
{
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
