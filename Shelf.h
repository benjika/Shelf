#ifndef SHELF_H
#define SHELF_H

using namespace std;

class Shelf : public CObject {
public:
	
	Shelf(void);
	Shelf(CString title){}
	virtual ~Shelf(void);

	virtual void Use(CString title_to_compare) = 0;

	virtual bool exists(CString title_to_compare) = 0;

	virtual CString get_title() = 0;
	
	virtual void set_title(CString title_old,CString title_new) = 0;

};
#endif

