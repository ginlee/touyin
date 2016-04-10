//#include "stdafx.h"
#include "Mygraph.h"


Mygraph::Mygraph()
{
	source = INF;
	destination = INF;
//	Dmin = new int[600 * 600];
	G = new int[600 * 600];
	Gn = new int[600 * 600];
	GMAX = INF;
	R_flag = INF;
	Restrain = *(new vector<int>);
	Restrain.reserve(50);
	SP = *(new vector<int>);
	SP.reserve(200);
	Son = new vector<int>[600];
	mother = new vector<int>[600];
	value = INF;
}

/*int Mygraph::creategraph()  //在读入函数中应当已经对全部参数进行赋值
{
	memcpy_s(Dmin, sizeof(int)*GMAX*GMAX, G, sizeof(int)*GMAX*GMAX);
	for (int i = 0; i <GMAX; i++)
	{
		for (int j = 0; j < GMAX; j++)
		{
			for (int k = 0; k < GMAX; k++)
			{
				if (*(Dmin+j*GMAX+k)>*(Dmin+j*GMAX+i)+*(Dmin+i*GMAX+k))
				{
					*(Dmin + j*GMAX + k) = *(Dmin + j*GMAX + i) + *(Dmin + i*GMAX + k);
				}
			}
		}
	}
	return 1;
} */

Mygraph::~Mygraph()
{
//	delete G;
//	delete Son;
//	delete & Restrain;
//	delete &SP;
//	delete Dmin;
}
