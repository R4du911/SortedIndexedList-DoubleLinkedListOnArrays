#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
    this->nrElems = 0;
    this->cap = 5;
    this->elements = new DLLNode[this->cap];
    this->rel = r;
    this->head = -1;
    this->tail = -1;
    for (int i = 0; i < this->cap - 1; i++)
        this->elements[i].next = i + 1;
    this->elements[this->cap - 1].next = -1;
    this->firstEmpty = 0;
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(1)
//average case: Θ(1)
int SortedIndexedList::size() const {
    return this->nrElems;
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(1)
//average case: Θ(1)
bool SortedIndexedList::isEmpty() const {
    if (this->head == -1)
        return true;
    return false;
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(n)
//average case: Θ(n)
TComp SortedIndexedList::getElement(int i) const {
    if (i >= this->nrElems || i < 0)
        throw exception();

    int index = this->head;
    int pos = 0;

    while (index != -1) {
        if (pos == i) {
            return this->elements[index].info;
        }
        pos++;
        index = this->elements[index].next;
    }
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(n)
//average case: Θ(n)
TComp SortedIndexedList::remove(int i) {
    if (i >= this->nrElems || i < 0)
        throw exception();

    //list has only one element
    if (i == 0 && this->head == this->tail) {
        TComp oldvalue = this->elements[this->head].info;
        this->elements[this->head].info = NULL_TCOMP;
        this->elements[this->head].next = this->firstEmpty;
        this->elements[this->head].prev = -1;

        //position of removed element is first empty
        if (this->head < this->firstEmpty) {
            int save_pos = this->firstEmpty;
            this->firstEmpty = this->head;
            this->elements[this->firstEmpty].next = save_pos;
        }
        //position of removed element to be linked with other empty spots from the array
        else {
            int index_empty = this->firstEmpty;
            int prev_index_empty;
            while (index_empty < this->head && index_empty != -1) {
                prev_index_empty = index_empty;
                index_empty = this->elements[index_empty].next;
            }
            this->elements[prev_index_empty].next = this->head;
            this->elements[this->head].next = index_empty;
        }

        this->head = -1;
        this->tail = -1;
        this->nrElems--;
        return oldvalue;
    }

    //remove first elem
    if (i == 0) {
        int old_head = this->head;
        this->elements[this->elements[old_head].next].prev = -1;
        TComp oldvalue = this->elements[old_head].info;
        this->elements[old_head].info = NULL_TCOMP;
        this->elements[old_head].prev = INT_MIN;
        this->head = this->elements[old_head].next;

        //position of removed element is first empty
        if (old_head < this->firstEmpty) {
            int save_pos = this->firstEmpty;
            this->firstEmpty = old_head;
            this->elements[this->firstEmpty].next = save_pos;
        }
        //position of removed element to be linked with other empty spots from the array
        else {
            int index_empty = this->firstEmpty;
            int prev_index_empty;
            while (index_empty < old_head && index_empty != -1) {
                prev_index_empty = index_empty;
                index_empty = this->elements[index_empty].next;
            }
            this->elements[prev_index_empty].next = old_head;
            this->elements[old_head].next = index_empty;
        }
        this->nrElems--;
        return oldvalue;
    }

    //remove last elem
    if (i == size() - 1) {
        int old_tail = this->tail;
        this->elements[this->elements[old_tail].prev].next = -1;
        TComp oldvalue = this->elements[old_tail].info;
        this->elements[old_tail].info = NULL_TCOMP;
        this->tail = this->elements[old_tail].prev;
        this->elements[old_tail].prev = INT_MIN;


        //position of removed element is first empty
        if (old_tail < this->firstEmpty) {
            int save_pos = this->firstEmpty;
            this->firstEmpty = old_tail;
            this->elements[this->firstEmpty].next = save_pos;
        }
        //position of removed element to be linked with other empty spots from the array
        else {
            int index_empty = this->firstEmpty;
            int prev_index_empty;
            while (index_empty < old_tail && index_empty != -1) {
                prev_index_empty = index_empty;
                index_empty = this->elements[index_empty].next;
            }
            this->elements[prev_index_empty].next = old_tail;
            this->elements[old_tail].next = index_empty;
        }
        this->nrElems--;
        return oldvalue;
    }

    //remove an element from a position
    int index = this->head;
    int pos = 0;
    while (index != -1) {
        if (pos == i) {
            this->elements[this->elements[index].prev].next = this->elements[index].next;
            this->elements[this->elements[index].next].prev = this->elements[index].prev;
            TComp oldvalue = this->elements[index].info;
            this->elements[index].info = NULL_TCOMP;
            this->elements[index].prev = INT_MIN;

            //position of removed element is first empty
            if (index < this->firstEmpty) {
                int save_pos = this->firstEmpty;
                this->firstEmpty = index;
                this->elements[this->firstEmpty].next = save_pos;
            }
            //position of removed element to be linked with other empty spots from the array
            else {
                int index_empty = this->firstEmpty;
                int prev_index_empty;
                while (index_empty < index && index_empty != -1) {
                    prev_index_empty = index_empty;
                    index_empty = this->elements[index_empty].next;
                }
                this->elements[prev_index_empty].next = index;
                this->elements[index].next = index_empty;
            }
            this->nrElems--;
            return oldvalue;
        }
        pos++;
        index = this->elements[index].next;
    }
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(n)
//average case: Θ(n)
int SortedIndexedList::search(TComp e) const {
    int index = this->head;
    int pos = 0;

    while (index != -1 && this->rel(this->elements[index].info, e)) {
        if (this->elements[index].info == e) {
            return pos;
        }
        pos++;
        index = this->elements[index].next;
    }

    return -1;
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(n)
//average case: Θ(n)
void SortedIndexedList::add(TComp e) {
    if (this->firstEmpty == -1) {
        this->cap = this->cap * 2;
        DLLNode *newvec = new DLLNode[this->cap];
        for (int index = 0; index < this->nrElems; index++)
            newvec[index] = this->elements[index];
        for (int index = this->nrElems; index < this->cap - 1; index++)
            newvec[index].next = index + 1;
        newvec[this->cap - 1].next = -1;
        this->firstEmpty = this->nrElems;
        delete[] this->elements;
        this->elements = newvec;
    }

    bool added = false;

    //list is empty
    if (this->head == -1) {
        this->head = this->firstEmpty;
        this->tail = this->firstEmpty;
        this->firstEmpty = this->elements[this->firstEmpty].next;
        this->elements[this->head].next = -1;
        this->elements[this->tail].prev = -1;
        this->elements[this->head].info = e;
        this->nrElems++;
        added = true;
    }
    int index = this->head;
    while (this->elements[index].next != -1 && this->rel(this->elements[index].info, e)) {
        index = this->elements[index].next;
    }

    //add last element
    if (this->elements[index].next == -1 && !added && this->rel(this->elements[index].info, e)) {
        this->elements[this->firstEmpty].info = e;
        int next_free_elem = this->elements[this->firstEmpty].next;
        this->elements[this->firstEmpty].next = -1;
        this->elements[this->firstEmpty].prev = index;
        this->elements[index].next = this->firstEmpty;
        this->tail = this->firstEmpty;
        this->firstEmpty = next_free_elem;
        this->nrElems++;
        added = true;
    }

    //add at a position
    if (!added) {
        //add first position
        if (this->elements[index].prev == -1) {
            this->head = this->firstEmpty;
        }
        this->elements[this->firstEmpty].info = e;
        int prev_pos = this->elements[index].prev;
        int next_free_elem = this->elements[this->firstEmpty].next;
        this->elements[this->firstEmpty].next = index;
        this->elements[this->firstEmpty].prev = prev_pos;
        this->elements[prev_pos].next = this->firstEmpty;
        this->elements[index].prev = this->firstEmpty;
        this->firstEmpty = next_free_elem;
        this->nrElems++;
    }
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(1)
//average case: O(1)
ListIterator SortedIndexedList::iterator() {
    return ListIterator(*this);
}


//Complexitate:
//best case: Θ(n)
//worst case: Θ(n)
//average case: O(n)
void SortedIndexedList::remove_by_step(int step) {
    int index = this->head;
    int pos = 1;
    int next_pos;
    bool removed;

    while (index != -1) {
        removed = false;
        if (pos % step == 0) {
            //remove first elem
            if(index == this->head){
                int old_head = this->head;
                this->elements[this->elements[old_head].next].prev = -1;
                this->elements[old_head].info = NULL_TCOMP;
                this->elements[old_head].prev = INT_MIN;
                this->head = this->elements[old_head].next;

                next_pos = this->elements[old_head].next;

                if(this->head == -1)
                    this->tail = -1;

                //position of removed element is first empty
                if (old_head < this->firstEmpty) {
                    int save_pos = this->firstEmpty;
                    this->firstEmpty = old_head;
                    this->elements[this->firstEmpty].next = save_pos;
                }
                //position of removed element to be linked with other empty spots from the array
                else {
                    int index_empty = this->firstEmpty;
                    int prev_index_empty;
                    while (index_empty < old_head && index_empty != -1) {
                        prev_index_empty = index_empty;
                        index_empty = this->elements[index_empty].next;
                    }
                    this->elements[prev_index_empty].next = old_head;
                    this->elements[old_head].next = index_empty;
                }
                this->nrElems--;
                removed = true;
            }
            //remove last element
            else if(index == this->tail){
                int old_tail = this->tail;
                this->elements[this->elements[old_tail].prev].next = -1;
                this->elements[old_tail].info = NULL_TCOMP;
                this->tail = this->elements[old_tail].prev;
                this->elements[old_tail].prev = INT_MIN;

                next_pos = this->elements[old_tail].next;

                //position of removed element is first empty
                if (old_tail < this->firstEmpty) {
                    int save_pos = this->firstEmpty;
                    this->firstEmpty = old_tail;
                    this->elements[this->firstEmpty].next = save_pos;
                }
                //position of removed element to be linked with other empty spots from the array
                else {
                    int index_empty = this->firstEmpty;
                    int prev_index_empty;
                    while (index_empty < old_tail && index_empty != -1) {
                        prev_index_empty = index_empty;
                        index_empty = this->elements[index_empty].next;
                    }
                    this->elements[prev_index_empty].next = old_tail;
                    this->elements[old_tail].next = index_empty;
                }
                this->nrElems--;
                removed = true;
            }
            //remove an element from position
            else{
                this->elements[this->elements[index].prev].next = this->elements[index].next;
                this->elements[this->elements[index].next].prev = this->elements[index].prev;
                this->elements[index].info = NULL_TCOMP;
                this->elements[index].prev = INT_MIN;

                next_pos = this->elements[index].next;

                //position of removed element is first empty
                if (index < this->firstEmpty) {
                    int save_pos = this->firstEmpty;
                    this->firstEmpty = index;
                    this->elements[this->firstEmpty].next = save_pos;
                }
                //position of removed element to be linked with other empty spots from the array
                else {
                    int index_empty = this->firstEmpty;
                    int prev_index_empty;
                    while (index_empty < index && index_empty != -1) {
                        prev_index_empty = index_empty;
                        index_empty = this->elements[index_empty].next;
                    }
                    this->elements[prev_index_empty].next = index;
                    this->elements[index].next = index_empty;
                }
                this->nrElems--;
                removed = true;
            }
        }
        pos++;

        if(removed)
            index = next_pos;
        else
            index = this->elements[index].next;
    }
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(1)
//average case: O(1)
SortedIndexedList::~SortedIndexedList() {
    delete[] this->elements;
}
