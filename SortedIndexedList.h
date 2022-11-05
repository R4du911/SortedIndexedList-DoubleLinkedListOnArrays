#pragma once

class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

struct DLLNode{
    TComp info;
    int next;
    int prev;

    ~DLLNode() {};
};

class SortedIndexedList {
private:
	friend class ListIterator;
private:
    DLLNode* elements;
    int cap;
    int nrElems;
    int head;
    int tail;
    int firstEmpty;
    Relation rel;

public:
	// constructor
	SortedIndexedList(Relation r);

	// returns the size of the list
	int size() const;

	//checks if the list is empty
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
	TComp getElement(int pos) const;

	// adds an element to a given position
	//throws an exception if the position is not valid
	void add(TComp e);

	// removes an element from a given position
	//returns the removed element
	//throws an exception if the position is not valid
	TComp remove(int pos);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
	int search(TComp e) const;

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator();

    void remove_by_step(int k);

	//destructor
	~SortedIndexedList();

};
