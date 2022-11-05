#pragma once
#include "SortedIndexedList.h"


class ListIterator{
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

    int index;

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
};


