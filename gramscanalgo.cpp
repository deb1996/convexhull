//graham scan algorithm//
#include<iostream>
#include<math.h>
using namespace std;
double d=0;
class point
{
	public:
	int x;
	int y;
};
class rotate
{
	public:
		int mat[10][10];
		point*s;
		point*h;
		point a;
		int sz;
		int hz;
		void entry()
		{
			cout<<"enter the size of the elements"<<endl;
			cin>>sz;
			s=new point[sz];
			hz=sz+1;
			h=new point[sz+1];
			int i=0;
			while(i<sz)
			{
				cout<<"enter the x and y co ordinate of the point"<<endl;
				cin>>s[i].x;
				cin>>s[i].y;
				i++;
			}
		}
		point anchorset()
		{
			point p=s[0];
			int i=0;
			while(i<sz)
			{
				if(p.y>s[i].y)
				p=s[i];
				else if(p.y==s[i].y)
				{
					if(p.x>s[i].x)
					p=s[i];
				}
				i++;
			}
			return p;
		}
		void deleteanchor(point p,point*&s1,int &sz1)
		{
			int i=0;
			while(i<sz1)
			{
				if((s1[i].x==p.x)&&(s1[i].y==p.y))
				break;
				i++;
			}
			int j=i;
			while(j<sz1-1)
			{
				s1[j]=s1[j+1];
				j++;
			}
			sz1--;
		}
		void sort()
		{
			a=anchorset();
			deleteanchor(a,s,sz);
			point mid;
			int j=1;
			int t=0;
			h[t]=a;
			t++;
			point temp;
			double d1=0;
			while(sz)
			{
				if(sz==1)
				{
					h[t]=s[0];
					t++;
					deleteanchor(s[0],s,sz);
				}
				else
				{
				j=1;
				mid=s[0];
				while(j<sz)
				{
					initialise(a,mid,s[j]);
					d=0;
					d1=det(3,mat);
					if(d1>0)
				    {
				    	j++;
					}
					else
					{
						temp=s[0];
						s[0]=s[j];
						s[j]=temp;
						mid=s[0];
						j=1;
					}
				}
				h[t]=mid;
				t++;
				deleteanchor(mid,s,sz);
			    }  
			}
			h[t]=a;
			t++;
		}
		point before(point p)
		{
			int k=0;
			for(int i=0;i<hz-1;i++)
			{
				if((h[i].x==p.x)&&(h[i].y==p.y))
				{
					k=i-1;
					break;
				}
			}
			return h[k];
		}
		point after (point p)
		{
			int k=0;
			for(int i=0;i<hz-1;i++)
			{
				if((h[i].x==p.x)&&(h[i].y==p.y))
				{
					k=i+1;
				}
			}
			return h[k];
		}
		void show1()
		{
			int i=0;
			cout<<"the sorted array"<<endl;
			for(i=0;i<hz-1;i++)
			cout<<h[i].x<<"  "<<h[i].y<<"  "<<endl;
		}
		void convexhull()
		{
			point prev=h[0];
			point next;
			double d1=0;
			point curr=after(prev);
			//cout<<curr.x<<endl;
			while((curr.x!=a.x)&&(curr.y!=a.y))
			{
				next=after(curr);
				initialise(prev,curr,next);
				d=0;
				d1=det(3,mat);
				//cout<<d1<<"  "<<endl;
				if(d1>0)
				{
					prev=curr;
				}
				else
				{
					//cout<<curr.x<<"  "<<curr.y<<"  "<<endl;
					deleteanchor(curr,h,hz);
					prev=before(prev);
				}
				curr=after(prev);
			}
			show();
		}
		void show()
		{
			cout<<"the x and y co ordinates of the points in convex hull"<<endl;
			for(int i=0;i<hz-1;i++)
			{
				cout<<h[i].x<<"  "<<h[i].y<<endl;
			}
		}
void initialise(point p1,point p2,point p3)
{
	point*p=NULL;
	p=new point[3];
	p[0]=p1;
	p[1]=p2;
	p[2]=p3;
	int j;
	for(int i=0;i<3;i++)
	{
	  for(j=0;j<3;j++)
	  {
	     if(j==2)
	     {
	     	mat[i][j]=1;
		 }
		 else if(j==0)
		 {
		 	mat[i][j]=p[i].x;
		 }
		 else
		 {
		 	mat[i][j]=p[i].y;
		 }
	  }
	}
}
double det(int n,int mat[10][10])
{int c,i,j,subi,subj;                            // sub - submatrix
int submat[10][10];
if(n==2) return( (mat[0][0]*mat[1][1])-(mat[1][0]*mat[0][1]));
else
{  for(c=0;c<n;c++)
   {  subi=0;
      for(i=1;i<n;i++)
       {  subj=0;
          for(j=0;j<n;j++)
              {if(j==c)
                   continue;
                     submat[subi][subj]=mat[i][j];
                     subj++;
                     }
              subi++;

         }
      d=d+(pow(-1,c)*mat[0][c]*det(n-1,submat));
    }
}
return d;//
}     
};
int main()
{
 rotate r;
 r.entry();
 r.sort();
 //r.show1();
 r.convexhull();
 //r.show();
 return 0;
}
