#pragma once
//#include "stdafx.h"
#include"Mygraph.h"
#include <vector>
using namespace std;
class Mymessage
{
public:

	int value;
	int pfrom;
	int pto;
	int length;
	double Veval;
	int R_flag;
	//UINT64 Sonmark;
	vector<int>  path;
	Mymessage(){
		value = INF;
		pfrom = INF;
		pto = INF;
		length = INF;
		R_flag = INF;
		Veval = 0;
		path.reserve(100);
	}
	~Mymessage(){
	//	path->swap(vector<int>());
	};

};
 class Node{
 public:
	    vector<Mymessage> * value;
	    Node *next;
		Node(){ 
			value = new vector<Mymessage>;
			value->reserve(4000);
			next = NULL;
		};
		~Node(){
			delete value;
//			delete next;
		};
};
class Myqueue
{
private:
	int num;
	
public:
	Node *first;
    Node *last;
	Myqueue();
	~Myqueue();
	void insert(Mymessage element,int t);
	void push_blank();
	void initial();
	void pop(vector<Mymessage>* vmtemp);
};

