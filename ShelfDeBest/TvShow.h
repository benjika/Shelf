#ifndef TVSHOW_H
#define TVSHOW_H

#include "Video.h"
#include "afxwin.h"

class TvShow :public Video
{
public:

	DECLARE_SERIAL(TvShow);

	TvShow(CString title_new ) 
		: title(title_new) {}

	TvShow(void){}

	~TvShow(void){}

	const TvShow &TvShow::operator<(const TvShow &other) const;

	const TvShow &TvShow::operator>(const TvShow &other) const;

	void Use()
	{
		CString toPrint = _T("Watching TvShow ");
		toPrint += title;
		AfxMessageBox(toPrint);
	}

	CString get_title() const {return this->title;}

	void set_title(CString title_new){this->title = title_new;}

	void Serialize(CArchive& ar);	

private:
	CString title;

};

const TvShow &TvShow::operator<(const TvShow &other) const{ return *this;}

const TvShow &TvShow::operator>(const TvShow &other) const{ return *this;}

IMPLEMENT_SERIAL(TvShow,Video,1)
void TvShow::Serialize(CArchive& ar)
{
	if(ar.IsStoring()){ar << get_title();}

	else
	{
		CString title_temp;
		ar >> title_temp;
		set_title(title_temp);
	}
}

#endif