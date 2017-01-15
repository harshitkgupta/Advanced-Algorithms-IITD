// written by Harshit Kumar Gupta 
// entry no 2013EET2369
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<cctype>
#include<cassert>
#include<climits>
#include<cerrno>
#include<cfloat>
#include<ciso646>
#include<clocale>
#include<csetjmp>
#include<csignal>
#include<cstdarg>
#include<cstddef>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cwchar>
#include<cwctype>
//containers
#include<vector>
#include<list>
#include<map>
#include<queue>
#include<deque>
#include<set>
#include<complex>
#include<string>
#include<stack>
#include<bitset>
#include<istream>
#include<valarray>
//IOs
#include<iostream>
#include<sstream>
#include<iomanip>
#include<fstream>
#include<exception>
#include<ios>
#include<iosfwd>
#include<ostream>
#include<iterator>
#include<stdexcept>
#include<streambuf>
//algorithm & miscellaneous
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<limits>
#include<locale>
#include<memory>
#include<new>
#define MOD 1000000007
using namespace std;

#define Max 512

int P[Max][Max]; 

/* 2D Segment Tree x */
struct Point 
{
    int x, y, h;
    Point()
    {
    }
    Point(int x, int y, int h) : x(x), y(y), h(h)
    {

    }

    bool operator < (const Point& second) const
    {
        return h < second.h;
    }
};

struct SegmentTree 
{
    Point T[2 * Max * Max];
    int n, m;

    // initialize and construct segment tree
    void initialize(int p, int q)
    {
        n = p;
        m = q;
        construct(1, 1, 1, n, m);
    }

    // construction a 2D segment tree for points in rectangle[(a1, b1),(a2, b2)]
    // Running Time: O(n logn)
    Point construct(int x, int a1, int b1, int a2, int b2) {
        // out of range construction return MIN
        if (a1 > a2 or b1 > b2)
            return Point(0, 0, INT_MIN);

        // if it is a single point, assign value to x
        if (a1 == a2 and b1 == b2)
            return T[x] = Point(a1, b1, P[a1][b1]);

        // split the tree into four segments during construction
        T[x] =Point(0, 0, INT_MIN);
        T[x] = maxPoint(T[x], construct(4*x-2,a1,b1,(a1+a2)/2,(b1+b2)/2));
        T[x] = maxPoint(T[x], construct(4*x-1,(a1+a2)/2+1,b1,a2,(b1+b2)/2));
        T[x] = maxPoint(T[x], construct(4*x+0,a1,(b1+b2)/2+1,(a1+a2)/2,b2));
        T[x] = maxPoint(T[x], construct(4*x+1,(a1+a2)/2+1,(b1+b2)/2+1,a2,b2));
        return T[x];
    }

    // utility function for queryin range of rectangle(int, int, int, int);
    Point queryRect(int x, int a1, int b1, int a2, int b2, int x1, int y1, int x2, int y2)
     {
        // if we out of range, return INT_MIN
        if (x1 > a2 or y1 > b2 or x2 < a1 or y2 < b1 or a1 > a2 or b1 > b2)
            return Point(0, 0, INT_MIN);

        // if it is within range, return the x
        if (x1 <= a1 and y1 <= b1 and a2 <= x2 and b2 <= y2)
            return T[x];

        // split query into four segments query
        Point p = Point(0, 0, INT_MIN);
        p = maxPoint(p, queryRect(4*x-2,a1,b1,(a1+a2)/2,(b1+b2)/2,x1,y1,x2,y2));
        p = maxPoint(p, queryRect(4*x-1,(a1+a2)/2+1,b1,a2,(b1+b2)/2,x1,y1,x2,y2));
        p = maxPoint(p, queryRect(4*x+0,a1,(b1+b2)/2+1,(a1+a2)/2,b2,x1,y1,x2,y2));
        p = maxPoint(p, queryRect(4*x+1,(a1+a2)/2+1,(b1+b2)/2+1,a2,b2,x1,y1,x2,y2));

        // return the point with maximum height
        return p;
    }

    // query for rectangle[(x1,y1),(x2,y2) ]
    // Running Time: O( logn )
    Point queryRect(int x1, int y1, int x2, int y2)
    {
        return queryRect(1, 1, 1, n, m, x1, y1, x2, y2);
    }

    // getting point with max height
    Point maxPoint(Point a, Point b) 
    {
        return max(a, b);
    }
};



// Segment tree object
SegmentTree maxTree;



/* main program */
int main(void) {
    int n=0, m=0,k;
    //  reading input
    puts("Enter  no of  points ");
    scanf("%d", &k);
	
    for(int i = 1; i <= k; i++)
    {int x,y,h;
	scanf("%d %d %d", &x,&y,&h);
	P[x][y]=h;
	n=max(x,n);
	m=max(y,m);
    }
    // initialize
    maxTree.initialize(n, m);
    puts("Enter the no of query");
    int q;
    scanf("%d",&q);
    printf("INT MIN=-2147483648 at 0 and 0 will indicate that no point in this rectangle exist\n");
    int x1, y1, x2, y2;		
    while(q--)	
    {    // query points
	
    
    printf("query ");	
    cin>>x1>>y1>>x2>>y2;
    Point out=maxTree.queryRect(x1, y1, x2, y2);
	
    printf("Maximum point in %d-%d and %d-%d is at %d %d with height %d \n",x1, y1, x2, y2,out.x,out.y,out.h);
    }
   

    return 0;
}
