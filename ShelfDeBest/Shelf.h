#ifndef SHELF_H
#define SHELF_H


using namespace std;

class Shelf : public CObject {
public:
	DECLARE_SERIAL(Shelf);

	Shelf(void){}

	virtual ~Shelf(void){}

	virtual void Use(){}
	
	virtual void set_title(CString title_new) {}

	virtual void Serialize(CArchive& ar);

};

IMPLEMENT_SERIAL(Shelf,CObject,1)

void Shelf::Serialize(CArchive& ar){
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

