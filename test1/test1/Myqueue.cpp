//#include "stdafx.h"
#include "Myqueue.h"
#include <vector>
using namespace std;
Myqueue::Myqueue()
{
	num = 0;
	first = NULL;
	last = NULL;
}


Myqueue::~Myqueue()
{
}
void Myqueue::initial(){
	for (int i = 0; i < MAX_DELAY; i++)
	{
		push_blank();
	}
};
void Myqueue::insert(Mymessage element, int t){
	if (t>=num)
	{
		cout << "error delay" << endl;
	}
	else
	{
		Node* temp=first;
		for (int i = 0; i < t-1; i++)
		{
			temp = temp->next;
		}
		temp->value->push_back(element);
	}
};
void Myqueue::push_blank(){
	Node* temp = new Node;
	vector<Mymessage>* blank_vm =new vector<Mymessage>;
	blank_vm->reserve(2800);
	temp->value = blank_vm;
	temp->next = NULL;
	if (0 == this->num){
		first = temp;
		last = temp;
		
	}
	else{
		last->next = temp;
		last = temp;
		
	}
	(this->num)++;
};

void Myqueue::pop(vector<Mymessage>* vmtemp){
	if (0 == this->num){
		cout << "No elements in the queue!" << endl;
	}
	else if (1 == this->num){
		*vmtemp = *(first->value);
		delete first;
		first = NULL;
		last = NULL;
		this->num = 0;
	}
	else{
		*vmtemp = *(first->value);
		Node* temp= first;
		first = first->next;
		num = num - 1;
		delete temp;
	}
};