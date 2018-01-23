#ifndef BASKET_H
#define BASKET_H

#include "Shelf.h"
#include "Book.h"
#include "Video.h"
#include "Movie.h"
#include "TvShow.h"
using namespace std;

template <class T>
class Basket
{
public:

	Basket(void)
	{
		first_added = nullptr;
		first_deleted = nullptr;
		size =0;
	}

	~Basket(void)
	{
		delete first_added;
		delete first_deleted;
	}

	void insert(CString title){
		if (first_added == nullptr)
		{
			first_added = new T(title);
			last_added = first_added;
		}
		else
		{
			//last_added = T::insert(title);
		}
		size ++ ;
	}
	bool exists(CString title){return T::exists(title);}
	int getSize() const{return size;}
	void Use(CString title){first_added->Use(title);}
	void set_title(CString title_old,CString title_new)
	{
		first_added->set_title(title_old , title_new);
	}



private:
	int size;
	T *first_added;
	T *last_added;
	T *first_deleted;
	T *last_deleted;
	T *curr_ptr;
};

#endif