#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define PEOPLE_NUM 130

int score[PEOPLE_NUM][PEOPLE_NUM];

void split_string(const string& original, char separator, uint32_t col_limit, vector<string>* result)
{
    result->clear();
	size_t current_pos = 0, previous_pos = 0;
	uint32_t col_count = 0;

	while((current_pos = original.find(separator, previous_pos)) != string::npos && (col_limit == 0 || col_count < col_limit))
	{   
		string part(original.substr(previous_pos, current_pos - previous_pos));
	    result->push_back(part);
	    previous_pos = current_pos + 1;
	    col_count ++; 
    }

    if(col_limit == 0 || col_count < col_limit)
	{   
		string part(original.substr(previous_pos));
		result->push_back(part);
	} 
}

int cal(string tt)
{
	vector<string> ts;
	split_string(tt,';',35,&ts);
	int ans = 0,a,b,c,d;
	for(int i=0;i<31;i++)
	{
		const char *tss = ts[i].c_str();
		sscanf(tss,"%d,%d,%d,%d",&a,&b,&c,&d);
		ans += score[a][b]+score[a][c]+score[a][d]+score[b][c]+score[b][d]+score[c][d];
		
		score[a][b] = score[b][a] = 0;
		score[a][c] = score[c][a] = 0;
		score[a][d] = score[d][a] = 0;
		score[b][c] = score[c][b] = 0;
		score[b][d] = score[d][b] = 0;
		score[c][d] = score[d][c] = 0;
	
	}
	
	return ans;
}

// ** input1 input2 output
int main(int argc,char **argv)
{
	if(argc<4)
	{
		fprintf(stderr,"Invalid para numbers.\nUsage:exe data_number_distance answer1 output \n");
		return -1;
	}

	FILE* fin1 = fopen(argv[1],"r"); // data_number_distance, [num1 num2 dis]
	FILE* fin2 = fopen(argv[2],"r"); // answer
	FILE* fout = fopen(argv[3],"w"); // score
	
	if( NULL==fin1 || NULL==fin2 || NULL==fout )
	{
		fprintf(stderr,"Can not open file.\n");
		return -1;
	}

	memset(score,0,sizeof(int)*PEOPLE_NUM*PEOPLE_NUM);
	
	int num1,num2,dis;
	while(!feof(fin1))
	{
		int ret = fscanf(fin1,"%d\t%d\t%d",&num1,&num2,&dis);
		if( ret==-1 ) 
			break;
		if( ret!=3 )
		{
			fprintf(stderr,"Read data error from file %s.\n",argv[1]);
			return -1;
		}
		score[num1][num2]=score[num2][num1]=dis;
	}
	fclose(fin1);
	
	char t_line[1000];
	int ans = 0,tv;
	while(!feof(fin2))
	{
		if(!fgets(t_line,1000,fin2))
			break;
		t_line[strlen(t_line)-1]='\0';
		string tt(t_line);
		tv = cal(tt);
		ans += tv;
	}

	fprintf(fout,"%d\n",ans);
	fclose(fin2);
	fclose(fout);

	return 0;
}
