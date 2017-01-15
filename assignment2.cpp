// Name- Harshit Kumar Gupta
// Emtry No-2013EET2369
#include<iostream>
#include<string>
#include<algorithm>
#include<cstring>
#include<stack>
int COPY_COST=0;
int REP_COST=1;
int DEL_COST=1;
int INS_COST=1;
using namespace std; 
// Strings A and B of size m and n are passed.
// Construct 2D Table for solution using DP 
void EditDistance(string &A, string &B)
{
    int m = A.length();
    int n = B.length();
 
    // ED[m+1][n+1]
    int ED[m+1][n+1];
 
    // Initialize table
    memset(ED,0,sizeof(ED));
 
    // Set up base cases
    // T[i][0] = i
    for(int i = 0; i <=m; i++)
        ED[i][0]= i*DEL_COST;
 
    // T[0][j] = j
    for(int j = 0; j <= n; j++)
        ED[0][j] = j*INS_COST;
 
    // Build the ED in top-down fashion
    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            // ED[i][j-1] left cell
           int left = ED[i][j-1]+INS_COST; //insert
            
            // ED[i-1][j]
            int top = ED[i-1][j]+DEL_COST; //delete
            
            // T[i-1][j-1]   Top-left (corner) cell
	    // EDIT_COST will apply 
            int EDIT_COST;
	    if(A[i-1]!=B[j-1])
		EDIT_COST=REP_COST;
	    else
		EDIT_COST=COPY_COST;				
            int corner = ED[i-1][j-1]+ EDIT_COST;
 
            // Minimum cost of current cell
            // Fill in the next cell ED[i][j]
            ED[i][j]= min(min(left, top), corner);
        }
    }
    cout<<"printing Edit distance table \n      ";
    for(int j = 0; j <= n; j++)
        	cout<<B[j]<<"  "; 
    cout<<"\n";		
    for(int i = 0; i <= m; i++)
    {
       if(i>0)
	cout<<A[i-1]<<"  "; 
	if(i==0)
		cout<<"   ";
        for(int j = 0; j <= n; j++)
        	cout<<ED[i][j]<<"  ";
	cout<<"\n"; 
    }	
    stack<string> op;	
    stack<pair<int,int> > st;	
    int i=m,j=n;
    while(i>0 && j>0)
    {	
		int m= min(min(ED[i-1][j], ED[i][j-1]), ED[i-1][j-1]);
		if(m==ED[i][j])
		{
			i--;
			j--;
			continue;
		}
		if(m==ED[i-1][j-1])
		{
			
			op.push("REPLACE");
			j--;i--;
		}
		else if(m==ED[i-1][j])
		{
			i--;
			op.push("INSERT");
		}
		else if(m==ED[i][j-1])
		{       j--;
			op.push("DELETE");
		}
                st.push(make_pair(i,j));
     }
     cout<<"\nSequence of operation\n";
     cout<<"1st"<<"    "<<"2nd"<<"\t"<<"OPERATION"<<"\n";	
     while(!op.empty())
     {
	i=st.top().first;
	j=st.top().second;
	if(op.top()=="INSERT")
	{       
		cout<<A[i]<<"\t"<<"-"<<"\t"<<op.top()<<"\n";
		
	}
	if(op.top()=="DELETE")
	{
		cout<<"-"<<"\t"<<B[j]<<"\t"<<op.top()<<"\n";
		
		
	}
	else if(op.top()=="REPLACE" && A[i]!=B[j])
	{
	cout<<A[i]<<"\t"<<B[j]<<"\t"<<op.top()<<"\n";
	
	}
	else if(op.top()=="REPLACE" && A[i]==B[j])
	{
	cout<<A[i]<<"\t"<<B[j]<<"\t"<<"COPY"<<"\n";
	
	}
	st.pop();
	op.pop();
     }			
    // Cost is in the cell T[m][n]
    cout<<"\nMinimum cost required to convert "<<A<<" into "<<B<<" is "<< ED[m][n]<<"\n\n";
}
int main()
{
    string A,B;
    	
    cout<<"Enter First String  ";  	
    getline(cin,A);	
    		
    cout<<"Enter Second String  ";
    getline(cin,B);
    cout<<"Enter cost of copy; replace; insert; delete  ";
    cin>>COPY_COST>>REP_COST>>INS_COST>>DEL_COST;		
    EditDistance(A, B);
    return 0;
}
