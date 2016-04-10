
#include "stdio.h"
#include <iostream>
#include <string.h>
#include "Mygraph.h"
#include "Myqueue.h"
//#include "stdafx.h"
#include <time.h>
#include <math.h>
using namespace std;
#define MAX_LINE_LEN 4000
static char g_result[MAX_LINE_LEN] = "NA";

int evaluateMessage(Mymessage* Mtemp, Mygraph* MyG){
	Mtemp->Veval = (Mtemp->value  * (1 + MyG->R_flag)) / (1 + 1 * Mtemp->R_flag);
	//Mtemp->Veval = (Mtemp->value*(MyG->R_flag+1-Mtemp->R_flag) + *(MyG->Dmin+Mtemp->pfrom*MyG->GMAX+Mtemp->pto)*1-Mtemp->length*0) / (1 + 1.0*Mtemp->R_flag);
	return 1;
}
void shell_sort(vector<double> &nums, vector<int> &list)   //include <algorithm> sort 
{
	for (int gap = nums.size() >> 1; gap > 0; gap >>= 1) { // times
		for (int i = gap; i < nums.size(); i++) { // position
			double temp = nums[i];
			int  temp_l = list[i];
			int j = i - gap;
			for (; j >= 0 && nums[j] < temp; j -= gap) {
				nums[j + gap] = nums[j];
				list[j + gap] = list[j];
			}

			nums[j + gap] = temp;
			list[j + gap] = temp_l;
		}
	}
}


int random_partion(double *p, int n)
{
	int idx = rand() % n;
	swap(p[idx], p[n - 1]);
	int i = -1;    //i表示最后一个小于p[n-1]的元素的位置  
	int j = 0;     //j用来扫描数组  
	for (j = 0; j<n; j++)
	{
		//将小于p[n-1]的数交换到前半部分  
		if (p[j]<p[n - 1])
		{
			swap(p[++i], p[j]);
		}
	}
	swap(p[++i], p[n - 1]);
	return i;
}
double getMaxK(double *p, int n, int k)
{
	int mid;
	if (k <= 0)
		return -1;
	if (n<k)
		return -1;
	mid = random_partion(p, n);   //对原数组进行一次划分  
	if (mid == n - k)      //如果mid==n-k，那么返回该值，这就是第k大的数  
		return p[mid];
	else if (mid<n - k)
		return getMaxK(p + mid + 1, n - mid - 1, k);  //如果mid<n-k，那么第k大的数在右半数组，而且仍然是第k大数  
	else
		return getMaxK(p, mid, k - (n - mid));   //如果mid>n-k，那么第k大的数在左半数组，且在左半数组中是第k-(n-mid)大的数  
}


int startsearch(Mygraph* MyG, Myqueue* MyQ){
	for (int i = 0; i < (MyG->Son+MyG->source)->size(); i++)
	{
		Mymessage* Mtemp = new Mymessage;
		Mtemp->length = 1;
		Mtemp->pfrom = MyG->source;
		Mtemp->pto = (*(MyG->Son + MyG->source))[i];
		Mtemp->value = *(MyG->G+MyG->GMAX*MyG->source+Mtemp->pto);
		vector<int> * pt = new vector<int>;
		Mtemp->path = *pt;
		Mtemp->path.push_back(Mtemp->pfrom);
		Mtemp->R_flag = 0;
		Mtemp->Veval = 0;
	//	evaluateMessage(Mtemp, MyG);
		MyQ->insert(*Mtemp, Mtemp->value);
		delete Mtemp;
	}
	return 1;
};

int checkcircle(Mymessage* Mtemp){  //用 bool 600的数组代替
	for (int i = 0; i < Mtemp->length; i++)
	{
		if (Mtemp->pto == (Mtemp->path)[i])
	//	if (pto == (Mtemp->path)[i])
		{
			return 0;
		}
	}
	return 1;
};

int checkbestpath(Mymessage* Mtemp, Mygraph* MyG){
	if (Mtemp->pto != MyG->destination)
	{
		return -1;
	}
	int count = Mtemp->R_flag;
	//for (int j = 0; j < Mtemp->length; j++){for (int i = 0; i < MyG->Restrain.size(); i++){	if ((*Mtemp->path)[j]==MyG->Restrain[i]){count++;}}}
	if (count == MyG->Restrain.size())
	{
		return 1;
	}
	else
	{
		return 0;
	}

};

int sentmessage(Mymessage* Mtemp, Mygraph* MyG, Myqueue* MyQ){
	int n = (MyG->Son+Mtemp->pto)->size();
	for (int j = 0; j < MyG->R_flag; j++)
	{
		if (Mtemp->pto == MyG->Restrain[j])
		{
			Mtemp->R_flag++;
			double increase = MyG->Son[Mtemp->pto].size();
			if (increase>MyG->mother[Mtemp->pto].size())
			{
				increase = MyG->mother[Mtemp->pto].size();
			}
			Mtemp->Veval += 1.0 / increase;
	//		Mtemp->Veval = Mtemp->Veval + 1.0 / (MyG->Son[Mtemp->pto].size() + 0.005) / (MyG->mother[Mtemp->pto].size() + 0.005) / (MyG->Son[Mtemp->pto].size() + 0.005) / (MyG->mother[Mtemp->pto].size() + 0.005);
			break;
		}
	}
	for (int i = 0; i < n; i++)
	{
		Mymessage* newM = new Mymessage;
		newM->R_flag = Mtemp->R_flag;
		newM->length = Mtemp->length + 1;
		vector<int>* pt = new vector<int>;
		pt->reserve(newM->length);
		newM->path = *pt;
		newM->path = (Mtemp->path);
		newM->path.push_back(Mtemp->pto);
		newM->pfrom = Mtemp->pto;
		newM->pto = (*(MyG->Son+newM->pfrom ))[i];
		newM->value = Mtemp->value + *(MyG->G+newM->pfrom*MyG->GMAX+newM->pto);
		//evaluateMessage(newM, MyG);
		newM->Veval = Mtemp->Veval;
		MyQ->insert(*newM, *(MyG->G + newM->pfrom*MyG->GMAX + newM->pto));
		delete newM;
	}
	return 1;
};
int main()
{  
	int read_file(char ** const buff, const unsigned int spec, const char * const filename);
	void write_file(const bool cover, const char * const buff, const char * const filename);
	void write_result(const char * const filename);
	void record_result(unsigned short edge);
	char *topo[5000];
	int start_point, end_point;
	int must_pass_point[50];
	int edge_num;
	char *demand;
	int demand_num;
	char *topo_file = "mytoposmall2.csv";
	edge_num = read_file(topo, 5000, topo_file);
	char *demand_file = "mydemandsmall2.csv";
	demand_num = read_file(&demand, 1, demand_file);
	char *result_file = "rrr.csv";;
	int topo_int[5000][4];



	clock_t start, finish;
	double totaltime;
	start = clock();
	
	int topo_line;
	int sum = 0;
	bool i_flag = true;
	bool j_flag = true;
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i_flag;){
		j_flag = true;
		for (j = 0; j_flag;)
		{
			if ((topo[i][j] >= '0') && (topo[i][j] <= '9')) { sum = sum * 10 + (int)(topo[i][j] - '0'); j++; }
			if ((topo[i][j]) == ','){ topo_int[i][k] = sum; sum = 0; j++; k++; }
			if ((topo[i][j]) == '\n'){ topo_int[i][k] = sum; sum = 0;  i++; j = 0; k = 0; j_flag = false; if (i >= edge_num){ i_flag = false; topo_line = i-1;  break; } }
			if ((topo[i][j]) == '\0'){ topo_int[i][k] = sum; sum = 0; topo_line = i; i = 0; j = 0; k = 0; j_flag = false; i_flag = false; }
		}
	}
	topo_line = topo_line + 1;//topo图的行数，也就是总共的变数
	//for (k = 0; k < 30; k++){ cout << demand[k] << endl; }
	int must_pass_number = 0;
	k = 0;sum = 0;j = 0;
	i_flag = true;
	j_flag = true;
	bool start_dest_flag=true;//挑选起始点标志
	int douhao_count=0;
	for (i = 0; i_flag;i++){
		if (douhao_count == 0)
		{			
				if ((demand[i] >= '0') && (demand[i] <= '9')) { sum = sum * 10 + (int)(demand[i] - '0'); }
				if ((demand[i]) == ','){ douhao_count = 1; start_point = sum; cout << "start point is: " << start_point
					<< endl;  sum = 0;  continue; }
		}
		if (douhao_count == 1)
		{			
				if ((demand[i] >= '0') && (demand[i] <= '9')) { sum = sum * 10 + (int)(demand[i] - '0'); }
				if ((demand[i]) == ','){ douhao_count = 2; end_point = sum; cout << "end point is: " << end_point 
					<< endl;  sum = 0; continue; }

		}
		if(douhao_count>1){
			if ((demand[i] >= '0') && (demand[i] <= '9')) { sum = sum * 10 + (int)(demand[i] - '0'); }
			if ((demand[i]) == '|'){ must_pass_point[k] = sum; cout <<"must_pass_point: "<< must_pass_point[k] << endl; sum = 0;  k++; }
			if ((demand[i]) == '\0'){ must_pass_point[k] = sum; sum = 0; cout <<"must_pass_point: "<< must_pass_point[k] << endl;  k++;  i_flag = false; }
	     	}
	}
	must_pass_number = k;



	//图信息存储在topo[i][j]中，矩阵5000*4，行数(实际含的边数)topo_line
	//起点startpoint（int类型，是一个点的序号），终点同上
	//必经点信息demand[i],int数组，共must_pass_number个
	Mygraph MyG;
	Myqueue MyQ;
	MyG.source = start_point;
	MyG.destination = end_point;
	MyG.R_flag = must_pass_number;
	for ( i = 0; i <MyG.R_flag; i++)
	{
		MyG.Restrain.push_back(must_pass_point[i]);
	}
	MyG.GMAX = 0;
	for (i = 0; i < topo_line;i++)
	{
		if (MyG.GMAX<=topo_int[i][1])
		{
			MyG.GMAX = topo_int[i][1];
		}
		if (MyG.GMAX <= topo_int[i][2])
		{
			MyG.GMAX = topo_int[i][2];
		}
	}
	MyG.GMAX++;
	memset(MyG.G, INF, sizeof(int)*MyG.GMAX*MyG.GMAX);
	memset(MyG.Gn, INF, sizeof(int)*MyG.GMAX*MyG.GMAX);
	for ( i = 0; i < topo_line; i++)
	{
		*(MyG.G + topo_int[i][1] * MyG.GMAX + topo_int[i][2]) = topo_int[i][3];
		*(MyG.Gn + topo_int[i][1] * MyG.GMAX + topo_int[i][2]) = topo_int[i][0];
		(MyG.Son + topo_int[i][1])->push_back(topo_int[i][2]);
		(MyG.mother + topo_int[i][2])->push_back(topo_int[i][1]);
	}
	for ( i = 0; i < MyG.GMAX; i++)
	{
		*(MyG.G + i * MyG.GMAX + i) = 0;
	}
	MyQ.initial();
	bool key = true;
//	MyG.creategraph();
	startsearch(&MyG, &MyQ);
	vector<Mymessage> * vmtemp = new vector<Mymessage>;
	vmtemp->reserve(2400);
	Mymessage * Mtemp = new Mymessage;
	int kmessage = 0;
	int tcount = 0;
	while (key)
	{
		tcount++;
		MyQ.pop(vmtemp);
		MyQ.push_blank();
		kmessage = vmtemp->size();
		finish = clock();
		cout << tcount << "      num of message per second  " << vmtemp->size()  << endl;
		/*
		vector <double>* vmV = new vector<double>;
		vmV->reserve(kmessage);
		vector <int>* vmV_n = new vector<int>;
		vmV_n->reserve(kmessage);
		for (int p = 0; p < kmessage; p++)
		{
				vmV->push_back((*vmtemp)[p].Veval);
				vmV_n->push_back(p);
		}
		if (kmessage>300)
		{
			kmessage = 300;
			shell_sort(*vmV, *vmV_n);
		}  */

		double threshold =0;
		if (kmessage>350)
		{
			double * vmV = new double[kmessage];
			
			for (int p = 0; p < kmessage; p++)
			{
				*(vmV + p) = (*vmtemp)[p].Veval;
		//		sumvmV += (*vmtemp)[p].Veval;
			}
			threshold = getMaxK(vmV, kmessage,350);
		}   

		for ( i = 0; i < kmessage; i++)
		{
		//	*Mtemp = (*vmtemp)[(*vmV_n)[i]];
		    *Mtemp = (*vmtemp)[i];
			if (kmessage>1000&&Mtemp->Veval<=threshold)		{			continue;		}
			if (checkcircle(Mtemp)){
				int flag = checkbestpath(Mtemp, &MyG);
				if (flag == -1)
				{
					sentmessage(Mtemp, &MyG, &MyQ);
				}
				else if (flag == 1)
				{
					if (!key)
					{
						break;
					}
					MyG.value = Mtemp->value;
					MyG.SP = (Mtemp->path);
					MyG.SP.push_back(MyG.destination);
					Mtemp->length++;
					cout << "result:" << MyG.value << endl;
					for (int l = 0; l <MyG.SP.size(); l++){cout << " path  " << MyG.SP[l] << endl;}
					key = false;
				}

			}
		}

	}
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\n此程序的运行时间为" << totaltime << "秒！" << endl;
	char dengdai = getchar();

	unsigned short *result=new unsigned short [MyG.SP.size()-1];
	for ( i = 0; i < MyG.SP.size()-1; i++)
	{
		*(result + i) = *(MyG.Gn + MyG.SP[i] * MyG.GMAX + MyG.SP[i + 1]);
	}
	

	//文件输出，result存储着路径信息，都是边的编号例如一个点（6,3,2,1）边的编号为6.起点为点3，终点为2，cost为1
	//unsigned short result[] = { 2, 6, 3 };//示例中的一个解
	for (int i = 0; i < MyG.SP.size() - 1; i++)
	{
		record_result(result[i]);
	}
	write_result(result_file);
	return 0;
}

int read_file(char ** const buff, const unsigned int spec, const char * const filename)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		cout<<"Fail to open file "<<filename<<"error"<<endl;
		return 0;
	}
	cout << "Open file " << filename << "  OK"<<endl;

	char line[MAX_LINE_LEN + 2];
	unsigned int cnt = 0;
	while ((cnt < spec) && !feof(fp))
	{
		line[0] = 0;
		fgets(line, MAX_LINE_LEN + 2, fp);
		if (line[0] == 0)   continue;
		buff[cnt] = (char *)malloc(MAX_LINE_LEN + 2);
		strncpy(buff[cnt], line, MAX_LINE_LEN + 2 - 1);
		buff[cnt][4001] = 0;
		cnt++;
	//	cout << cnt << endl;
	}
	fclose(fp);
	cout<<"There are "<<cnt <<" lines in file "<<filename<<endl;

	return cnt;
}
void write_file(const bool cover, const char * const buff, const char * const filename)
{
	if (buff == NULL)
		return;

	const char *write_type = cover ? "w" : "a";//1:覆盖写文件，0:追加写文件
	FILE *fp = fopen(filename, write_type);
	if (fp == NULL)
	{
		cout << "Fail to open file " << filename << "error" << endl;
		return;
	}
	fputs(buff, fp);
	fputs("\n", fp);
	fclose(fp);
}
void write_result(const char * const filename)
{
	if (g_result[0] == '\0')
		return;

	write_file(1, g_result, filename);
}



void record_result(unsigned short edge)
{
	static int len = 0;
	if (len > (MAX_LINE_LEN - 10))
		return;
	if (len > 0)
		len += sprintf(g_result + len, "|");
	len += sprintf(g_result + len, "%d", edge);
}