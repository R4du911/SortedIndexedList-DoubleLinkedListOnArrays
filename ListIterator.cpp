#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	this->index = list.head;
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(1)
//average case: Θ(1)
void ListIterator::first(){
	this->index = list.head;
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(1)
//average case: Θ(1)
void ListIterator::next(){
	if(valid()){
        this->index = list.elements[this->index].next;
    }else{
        throw exception();
    }
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(1)
//average case: Θ(1)
bool ListIterator::valid() const{
	if(index != -1)
        return true;
	return false;
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(1)
//average case: Θ(1)
TComp ListIterator::getCurrent() const{
	if(valid()){
        return list.elements[this->index].info;
    }else{
        throw exception();
    }
}


