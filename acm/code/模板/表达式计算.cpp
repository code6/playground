/*
Description

Nick is a mathematician and his speciality is Boolean logic, especially repetition-free formulas. Formula is repetition-free if each variable occurs in the formula only once.
Let us fix the syntax of considered logical formulae:
* Variables — letters from ‘a’ to ‘z’ and from ‘A’ to ‘Z’;
* Parentheses — if E is a formula, then (E) is another;
* Negation — -|E is a formula for any formula E;
* Conjunction — E ∧E ∧···∧E .
1 2 n
* Disjunction — E ∨E ∨···∨E .
1 2 n
The operations are listed from the highest priority to the lowest.
An assignment is a function that maps each variable to its Boolean value. Assignment satisfies Boolean formula F if the value of F for this assignment is true.
The problem is to count the number of assignments that satisfy a given repetition-free Boolean formula.
Input

The only line of the input file contains the Boolean formula — a string consisting of characters ‘a’..‘z’, ‘A’..‘Z’, ‘(’, ‘)’, ‘~’, ‘&’ and ‘|’. The last three tokens stand for -|, ∧ and ∨ respectively. Uppercase and lowercase letters represent di?erent variables. Tokens can be separated by an arbitrary number of spaces. The line contains 1000 characters at most. The formula in the file is a syntactically correct repetition-free formula.
Output

The first line of the output file must contain the number of variable assignments that satisfy there petition- free formula given in the input file.
*/
//fail at ~~~~~~~~~~~~~~~~~a !!!

#include<iostream>
#include<vector>
#include<cctype>

using namespace std;

const int MAXN=30000;

typedef long long ll;

struct Var
{
	ll Y,N;
	Var ()
	{
		Y=1;
		N=1;
	}
};

typedef vector<Var> VAR_STACK;



VAR_STACK VarStack;
vector<char>OpStack;
char buffer[MAXN];

bool isLegal(char ch)
{
	if (isalpha(ch)) return true;
	if (ch=='(' || ch==')' || ch=='~' || ch=='&' ||ch=='|') return true;
	return false;
}


//if priority of a< priority of b,return true
bool Pro(char a,char b)
{
	if (b=='(') return false;
	if (a=='~' && b=='~') return false;
	if (a==b) return true;
	if (a=='~') return false;
	if (b=='~') return true;
	if (a=='&') return false;
	if (b=='&' ) return true;
	return false;
}

void Calc(VAR_STACK&vs,char op)
{
	if (op=='~')
	{	
		Var &cur=vs[vs.size()-1];
		swap(cur.Y,cur.N);
		return;
	}

	Var x=vs[vs.size()-1];
	vs.pop_back();
	Var y=vs[vs.size()-1];
	Var&cur=vs[vs.size()-1];

	if (op=='|')
	{
		cur.N=x.N*y.N;
		cur.Y=x.Y*y.N+x.N*y.Y+x.Y*y.Y;
		return;
	}

	if (op=='&')
	{
		cur.Y=x.Y*y.Y;
		cur.N=x.Y*y.N+x.N*y.Y+x.N*y.N;
		return;
	}
}

void Dump()
{
	int i;
	printf("VarStack size=%d\n",VarStack.size());
	for (i=0;i<VarStack.size();i++) printf("(%lld,%lld) ",VarStack[i].Y,VarStack[i].N);putchar('\n');
	printf("OpStack size=%d\n",OpStack.size());
	for (i=0;i<OpStack.size();i++) printf("%c ",OpStack[i]);putchar('\n');
}

int main()
{
	int i;

	while (gets(buffer))
	{
		VarStack.clear();
		OpStack.clear();
		char ch;
		for (i=0;buffer[i];i++)
		{
			if (!isLegal(buffer[i]))continue;   //blank			

			if (isalpha(buffer[i]))  //var
			{
				VarStack.push_back(Var());
				continue;			
			}

			//printf("ch=%c\n",buffer[i]);

			switch (buffer[i])
			{
			case '(':
					OpStack.push_back(buffer[i]);
				break;
			case ')':
				while (!OpStack.empty())
				{
					ch=OpStack[OpStack.size()-1];
					OpStack.pop_back();
					if (ch=='(')
						break;
					Calc(VarStack,ch);
				}
				break;
			default:
				while  (!OpStack.empty())
				{
					ch=OpStack[OpStack.size()-1];
					if (Pro(buffer[i],ch))
					{
						OpStack.pop_back();
						Calc(VarStack,ch);
					}
					else 
						break;
				}
				OpStack.push_back(buffer[i]);
				break;			
			}

		//	Dump();
		}

		while (!OpStack.empty())
		{
			ch=OpStack[OpStack.size()-1];
			OpStack.pop_back();
			Calc(VarStack,ch);
		}

		Var ans=VarStack[VarStack.size()-1];

		printf("%lld\n",ans.Y);
	}
	return 0;
}