#include<cstdio>
#include<cstring>
#include<string>
#include<fstream>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;


int n,m,d;

string s,t;

int i,j;
char ic,jc;

bool flag=0;

int main(int argc,char *argv[])
{
	ifstream in_is("input"),out_is("user_out");
	ifstream ans_is("answer");
	FILE *f_score=stdout;
	FILE *f_msg=stderr;
	int flag2;
	out_is>>s;
	in_is>>n>>d;
	in_is>>t;
	string ans;
	ans_is>>ans;
	if (s==ans)
	{
		fprintf(f_score,"100");
		goto lab;
	}
	if(ans[0]=='-')
	{
		fprintf(f_score,"0");
		goto lab;
	}		
	if (t.length()!=s.length())	
		flag=1;
	flag2=flag;
	for(int i=0;i<s.length();i++)
		if(s[i]!='A'&&s[i]!='B'&&s[i]!='C')		flag=1;
		
	for (int i=0;i<min(s.length(),t.length());++i)
	{
		if (s[i]=='A'&&t[i]=='a')	flag=1;
		if (s[i]=='B'&&t[i]=='b')	flag=1;
		if (s[i]=='C'&&t[i]=='c')	flag=1;
	}

	in_is>>m;
	while (m--)
	{
		in_is>>i>>ic>>j>>jc;
		--i,--j;
		if (s.length()<max(i,j)||(s[i]==ic&&s[j]!=jc))	flag=1;
		//		cout<<i<<"("<<s[i]<<") "<<ic<<" "<<j<<"("<<s[j]<<") "<<jc<<" "<<flag<<endl;
	}

	if (flag==1)	
	{  
		fprintf(f_score,"0");
		fprintf(f_msg,"%s",(flag2==0)?"长度相同":"长度不同");
	}
	else
	{  
		fprintf(f_score,"100");
	}
lab:
	fclose(f_score);
	fclose(f_msg);
	return 0;
}
