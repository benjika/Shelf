#pragma once
#include "command.h"
#include "Shelf.h"
#include <vector>

using namespace std;

class AddCommand :
	public Command
{
public:

	AddCommand(vector<Shelf*> &shelves, Shelf *shelf)
		: shelves(shelves), shelf(shelf) {}

	void perform() { shelves.push_back(shelf); }

	void rollback() {
		vector<Shelf*>::iterator it;
		for (it = shelves.begin(); it != shelves.end(); ++it)
			if (*it == shelf)
				break;
		if (it != shelves.end())
			shelves.erase(it);
	}

private:
	std::vector<Shelf*> &shelves;
	Shelf *shelf;

};

