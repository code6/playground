#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

#define PEOPLE_NUM 130
#define MAX_NUM 126

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

int main(int argc,char **argv)
{
	if(argc<2)
	{
		fprintf(stderr,"Error:Invalid para numbers.\nSample Usage: exe answer1\n");
		return -1;
	}
	int retv = 0; 

	FILE* fin1 = fopen(argv[1],"r");
	if(NULL==fin1) 
	{
		fprintf(stderr,"Error:Can not open file %s.\n",argv[1]);
		return -2;
	}
	char t_line[1000];
	int a,b,c,d;
	int Lines = 0;
	int used[PEOPLE_NUM]={0};
	while(!feof(fin1))
	{
		if(!fgets(t_line,1000,fin1))
			break;
		if( t_line[strlen(t_line)-1]!='\n' )
		{
			fprintf(stderr,"Error:The last character of line is not \\n.\n");
			retv = 6;
			break;
		}
		t_line[strlen(t_line)-1] = '\0';
		string tt(t_line);
		vector<string> ts;
		split_string(tt,';',35,&ts);
		if( ts.size()!=31 ) 
		{
			fprintf(stderr,"Error:group num is invalid.\n");
			retv = 1;break;
		}
		memset(used,0,sizeof(int)*PEOPLE_NUM);

		for(int i=0;i<31;i++)
		{
			const char * tss = ts[i].c_str();
			
			int ret = sscanf(tss,"%d,%d,%d,%d",&a,&b,&c,&d);
			sprintf(t_line,"%d,%d,%d,%d",a,b,c,d);
			if( ret!=4 || strlen(tss)!=strlen(t_line) )
			{
				fprintf(stderr,"Error:not enough people in a group or error read data.\n");
				retv = 4;
				break;
			}
			if( a<1 || a>MAX_NUM || b<1 || b>MAX_NUM ||
			    c<1 || c>MAX_NUM || d<1 || d>MAX_NUM || 
				a==60 || b==60 || c==60 || d==60 )
			{
				fprintf(stderr,"Error:people number is invalid.\n");
				retv = 2;
				break;
			}
			used[a]++;
			used[b]++;
			used[c]++;
			used[d]++;
			if( used[a]>1 || used[b]>1 || used[c]>1 || used[d]>1 )
			{
				fprintf(stderr,"Error:two people number is same.\n");
				retv = 3;
				break;
			}
		} 
		if( retv!=0 ) 
			break;
		Lines++;
	}
	if(retv==0&&Lines!=10)
	{
		fprintf(stderr,"Error:more than or less than 10 lines.\n");
		retv = 5;
	}
	if(retv==0)
	{
		fprintf(stderr,"Right.\n");
	}
	return retv;
}
