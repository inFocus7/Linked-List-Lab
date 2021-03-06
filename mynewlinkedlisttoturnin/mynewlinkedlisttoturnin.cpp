#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//********************************************************************************************************************************//
template<class LINKD>
class node
{
public:
	LINKD data; //sets the data portion of node
	node<LINKD> * next; //adds the pointer to next.
};

template <class LINKD>
class linkedList
{
public:
	//first you point to the head since that's where you want to begin
	node<LINKD> * head;

	//default constructor setting up the head as start.
	linkedList()
	{
		head = NULL;
	}

	LINKD popFront()
	{
		LINKD output = (*head).data;
		//now delete first item
		node<LINKD> * doomedNode = head; //sets the pointer to doomedNode as the head
		head = (*head).next; //sets the one after head as the head
		delete doomedNode;
		return output;
	}

	void display()
	{
		node<LINKD> * current;
		current = head; //sets teh head as current in list
		while (current != NULL) //checks while current isn't NULL
		{
			cout << (*current).data << endl; //Couts the data in the pointer to current.
			current = (*current).next; //updates current to the one next
		}
	}
	void addFront(LINKD x)
	{
		if (head == NULL)
		{
			head = new node<LINKD>; //creates a new node for head
			(*head).data = x; //data inside head note is x
			(*head).next = NULL;
		}
		else
		{
			node<LINKD> * A = new node<LINKD>; //sets a as new node. NOT FULLY SURE WHY...
			(*A).data = x;
			(*A).next = head;
			head = A;
		}
	}

	void addAt(LINKD x, int i)
	{
		node<LINKD> * addThis;
		node<LINKD> * before;
		before = head;
		addThis = head;
		if (i == 0)
		{
			addFront(x);
		}
		else
		{
			for (int o = 0; o <= (i - 1); o++)
			{
				before = addThis;
				addThis = (*addThis).next;
			}
			if (before == NULL)
			{
				node<LINKD> * N = new node<LINKD>;
				N->data = x;
				N->next = NULL;
				before = N;
			}
			node<LINKD> * ADDED = new node<LINKD>;
			(*ADDED).data = x;
			(*before).next = ADDED;
			(*ADDED).next = addThis;
		}
	}

	void remove(LINKD x)
	{
		node<LINKD> * dieString;
		node<LINKD> * X;
		dieString = head;
		X = dieString;
		if (head == NULL)
		{
			cout << "nah" << endl;
		}
		else
		{
			while ((*dieString).data != x && (*dieString).next != NULL) //gets to point
			{
				X = dieString;
				dieString = (*dieString).next;
			}
			if (X == head)
			{
				head = (*dieString).next;
				delete dieString;
			}
			else
			{
				(*X).next = (*dieString).next;
				delete dieString;
			}
		}
	}
	/*
	My terrible version of sorting. I don't have lecture so it took me a while to understand how to properly use pointers and the linked list, so sorry about the ugly code. Have spent the last ~9 hours trying to see what is/isn't allowed
	in linked list and troubleshooting problems. It could be 1000x better, sine I maybe used too many node pointers, but did so so that I can keep track of everthing, and I'm sure there's probably a better way of doing this so I'm going to
	ask someone if I could see how they did theirs to compare with this.
	*/
	void sort()
	{
		node<LINKD>* nextup;
		node<LINKD>* current;
		node<LINKD>* change;
		node<LINKD>* beforechange;
		node<LINKD>* beforecurrent;
		node<LINKD>* latestchange;
		latestchange = head;
		nextup = head; //next node to change should always start one one after current
		current = head; //what point i'm in the node
		change = head; //what node is moved
		beforechange = head; //before the node to be changed
		beforecurrent = head; //before current point
		nextup = nextup->next;
		while (current->next != NULL)
		{
			while (current->next != NULL)
			{
				LINKD data1 = current->data;
				LINKD data2 = nextup->data;
				node<LINKD>* currentsaver = current;
				node<LINKD>* nextupsaver = nextup;
				int checker = 0, trip = 0, steps = 1, trip2 = 0;
				LINKD smallest = current->data;
				for (int i = 0; nextup != NULL; i++) //did for loop in order to get the "beforechange" node pointer
				{
					if (data2 == smallest && steps == 1) //only works first time this starts up which checks if the two valeus are equal
					{
						trip = 1;
						break;
					}
					else
						steps--;

					if (data2 < smallest) //compares first character; strings are an array of chars.
					{
						smallest = data2; //sets value for smallest found
						change = nextup; //change happened here
						latestchange = nextup; //& here
						if (nextup->next != NULL)
							nextup = nextup->next;
						data2 = nextup->data;
						checker = i;
					}
					else if (nextup->next != NULL)
					{
						nextup = nextup->next;
						data2 = nextup->data;
					}
					else if (nextup->next == NULL)
						break;
				}
				if (trip == 1)
				{
					beforecurrent = current;
					beforechange = current;
					current = current->next;
					nextup = current->next;
					latestchange = NULL;
					break;
				}
				else if (change == latestchange) //ONLY DO THIS IF THERE WAS A CHANGE
				{
					for (int i = 0; i < checker; i++)
						beforechange = beforechange->next;

					if (current == head)
					{
						beforechange->next = change->next; //problem with beforechange since it doesn't move through my code!
						change->next = head;
						head = change;
						nextup = current->next; //nextup turns to null ptr
						trip2++;
					}
					else
					{
						beforechange->next = change->next;
						change->next = current;

						beforecurrent->next = change;

						if (change->next != current) //beforecurrent != beforechange
						{
							beforechange = current;
							current = current->next;
						}
						if (current->next != NULL)
							nextup = current->next;
					}
				}
				else
				{
					beforecurrent = current;
					current = current->next;
					if (current->next != NULL)
						nextup = current->next;
					trip2++;
				}

				if (trip2 == 0)
					beforecurrent = beforecurrent->next;
				else if (trip2 == 1 && smallest == head->data)
					beforecurrent = head;

				latestchange = NULL;
				beforechange = current;
			}
		}
	}
};

int main()
{
	//part 0:
	linkedList<string> list1;

	list1.addFront("pichacu");
	list1.addFront("elmo");
	list1.addFront("charmander");
	list1.addFront("ekans");

	list1.popFront();
	list1.popFront();

	list1.addFront("snorlax");

	list1.display(); //snorlax elmo pichacu
	cout << endl;
	//part 1:  Implement an 'addAt(string x, int i)' method which inserts
	//an items _after_ the first i items.  You may assume the given i
	//is less or equal to the number of items currently in the list.
	list1.addAt("owlbear", 2);
	list1.display(); //snorlax elmo owlbear pichacu

	list1.addAt("demogorgan", 3);
	list1.display(); //snorlax elmo owlbear demogorgan pichacu


	list1.addAt("mindFlayer", 0);
	list1.display(); //mindFlayer snorlax elmo owlbear demogorgan pichacu


	list1.addAt("centaur", 6);
	list1.display(); //mindFlayer snorlax elmo owlbear demogorgan pichacu centaur

	cout << endl;
	//part 2: implement "remove"
	//Suggestion:  To remove an item, the key is locate
	//the node right before the node you want to remove.
	//So, recommended step #1:  locate the address of the node _before_ the node to be removed.  Say node * beforeDoomed points at this node.
	//Step #2:  Now figure out how to get rid of the node given you have beforeDoomed.
	//Also, be sure to consider special cases such as when the item to be removed is the first item (in which case there is no node before it).
	list1.remove("elmo");
	list1.remove("mindFlayer");
	list1.remove("centaur");

	list1.addFront("kobold");
	list1.addAt("stirge", 5);


	list1.display();    //kobold snorlax owlbear demogorgan pichacu stirge

	cout << endl;
	//part 3: implement "sort"
	//A basic sort such as selection sort is fine for this.
	list1.sort();

	list1.display(); //demogorgan kobold owlbear pichacu snorlax stirge
	cout << endl;
	//(advanced) Part 4:  Template your class
	linkedList<double> list2;

	for (int i = 0; i<50; i++)
		list2.addFront(rand());

	list2.sort();
	list2.display();

	system("pause"); //for my VS2017-C
	return 0;
}
