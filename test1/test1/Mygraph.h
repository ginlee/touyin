#pragma once
//#include"stdafx.h"
#include <vector>

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
//#include <thread>
#include <iostream>
//#define MAX 600
#define MAX_DELAY 21
#define INF 10000


using namespace std;
class Mygraph
{
public:
	int source;
	int destination;
	int value;
	int GMAX;

	//int Dmin[MAX][MAX];
//	int * Dmin;
//	void dijkstra();

	int R_flag;
	vector<int> SP;
	vector<int> Restrain;
	//bool Restrain[MAX];
	

	//int G[MAX][MAX];
	int * G;
	int * Gn;
	//vector<int> Son[MAX];
	vector<int>* Son;
	vector<int>* mother;
//	int creategraph();
	Mygraph();
	~Mygraph();
};

