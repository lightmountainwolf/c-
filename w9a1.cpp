#include<iostream>
#include<math.h>
using namespace std;

class Shape
{
	public:
		long area;
		long curriculum;
		
		//-1��ʾ����ΪShape�� 
		int id()
		{
			return -1;
		}
		
		long getArea();
		long getCur();
}; 

class Rectangle : public Shape
{
	public:
		//�������� (�����Ͽ�ʼ��ʱ��),�߿� 
		int point[4][2]; 
		int height,width;
		
		Rectangle(const Rectangle &r1)
		{
			*this=r1;
		}
		
		long getArea()
		{
			return height*width;
		}
		
		long getCur()
		{
			return (height+width)*2;
		}
		
		Rectangle(int x1,int y1,int x2,int y2)
		{
			this->point[0][0]=x1;
			this->point[0][1]=y1;
			this->point[2][0]=x2;
			this->point[2][1]=y2;
			this->point[1][0]=x1;
			this->point[1][1]=y2;
			this->point[3][0]=x2;
			this->point[3][1]=y1;
			this->height=y1-y2;
			this->width=x2-x1;
			this->area=this->getArea();
			this->curriculum=this->getCur();
		}
		
		//4��ʾ����ΪRec�� 
		int id()
		{
			return 4;
		}
		
		//�жϵ��Ƿ��ھ����� 
		bool include(int x,int y)
		{
			if((this->point[0][0])<=x&&(this->point[0][1]>=y))
			{
				if((this->point[2][0])>=x&&(this->point[2][1]<=y))
				{
					return true;
				}
			}
			return false;
		}
		
		//�ж�this���Ƿ����r2��һ���� �����ذ�������� 
		int cover(Rectangle r2)
		{
			//this��ȫ��Χr2 
			if((this->point[0][0])<=r2.point[0][0]&&(this->point[0][1])>=r2.point[0][1])
			{
				if((this->point[2][0])>=r2.point[2][0]&&(this->point[2][1])<=r2.point[2][1])
				{
					return r2.area;
				}
			}
			
			//r2��this�ڵĶ����� 
			int num=0;
			//�洢r2��this�ڵĶ��㣬������� 
			int pointIn[2][2]={0};
			int situation=0;
			
			for(int i=0;i<4;i++)
			{
				if(this->include(r2.point[i][0],r2.point[i][1]))
				{
					pointIn[num][0]=r2.point[i][0];
					pointIn[num][1]=r2.point[i][1];
					num++;
					if(situation==0&&i==0)
					{
						situation=1;//���Ͻ� 
					}
					else if(situation==0&&i==1)
					{
						situation=2;//���½� 
					}
					else if(situation==0&&i==2)
					{
						situation=3;//���½� 
					}
					else if(situation==0&&i==3)
					{
						situation=4;//���Ͻ� 
					}
					else if(situation==1)
					{
						if(i==1)
						{
							situation=5;//��� 
						} 
						else if(i==3)
						{
							situation=8;//�ϱ� 
						} 
					}
					else if(situation==2)
					{
						if(i==2)
						{
							situation=6;//�±� 
						}
					}
					else if(situation==3)
					{
						if(i==3)
						{
							situation=7;//�ұ� 
						 } 
					} 
				}
			} 
			
			if(num==0)
			{
				return 0;
			}
			
			else if(num==1)
			{
				if(situation==1) 
				{
					return (this->point[2][0]-pointIn[0][0])*(pointIn[0][1]-this->point[2][1]);
				}
				else if(situation==2) 
				{
					return (this->point[3][0]-pointIn[0][0])*(this->point[3][1]-pointIn[0][1]);
				}
				else if(situation==3) 
				{
					return (pointIn[0][0]-this->point[0][0])*(this->point[0][1]-pointIn[0][1]);
				}
				else if(situation==4) 
				{
					return (pointIn[0][0]-this->point[1][0])*(pointIn[0][1]-this->point[1][1]);
				}
			}
			
			else if(num==2)
			{
				if(situation==5) 
				{
					return r2.height*(this->point[2][0]-pointIn[0][0]);
				}
				else if(situation==6) 
				{
					return r2.width*(this->point[0][1]-pointIn[0][1]);
				}
				else if(situation==7) 
				{
					return r2.height*(pointIn[0][0]-this->point[0][0]);
				}
				else if(situation==8) 
				{
					return r2.width*(pointIn[0][1]-this->point[2][1]);
				}
			}
			
			return 0;
		}
		
		//��ĿҪ��ĺ������ж�this��r2�İ�����ϵ������� 
		int bothCover(Rectangle r2)
		{
			if(this->cover(r2)==0)
			{
				return r2.cover(*this);
			}
			else 
			{
				return this->cover(r2);
			}
		 } 
		 
		// 
		int adjust(int area)
		{
			int t=0;//����break 
			int len=sqrt(area);
			int w=0,h=0;
			for(int i=len;i>0;i--)
			{
				for(int j=len;(i*j<=area);j++)
				{
					if(i*j==area)
					{
						w=i;
						h=j;
						t=1; 
						break;
					}
				}
				if(t==1)
				{
					break;
				}
			}
			this->width=w;
			this->height=h;
			
			this->point[2][0]=this->point[0][0]+w;
			this->point[2][1]=this->point[0][1]-h;

			this->point[1][1]=this->point[0][1]-h;
			this->point[3][0]=this->point[0][0]+w;

			this->area=this->getArea();
			this->curriculum=this->getCur();
			
			cout<<this->point[2][0]<<" "<<this->point[2][1]<<endl;
		}
};

class Circle : public Shape
{
	public:
		//Բ�����꣬�뾶 
		int x1,y1,r;
		
		//0��ʾ����ΪCircle�� 
		int id()
		{
			return 0;
		}
		
		long getArea()
		{
			return 3.14159*r*r;
		}
		
		long getCur()
		{
			return 2*3.14159*r;
		}
};

//��ȡ�������� 
int getNum(Shape*p)
{
	return p->id();
}

int main()
{
	int x11,y11,x21,y21,x12,y12,x22,y22,area;
	cout<<"��˳�������һ���������Ϻ����꣬���������꣬���º����꣬���������꣬�ڶ����������Ϻ����꣬���������꣬���º����꣬����������"<<endl;
	cin>>x11>>y11>>x21>>y21>>x12>>y12>>x22>>y22;
	Rectangle r1=Rectangle(x11,y11,x21,y21);
	Rectangle r2=Rectangle(x12,y12,x22,y22);
	cout<<"�غ����Ϊ"<<r1.bothCover(r2)<<endl;
	cout<<"��˳��������Ҫ�����ľ������Ϻ����꣬���������꣬���º����꣬���������꣬����������"<<endl; 
	cin>>x11>>y11>>x21>>y21>>area;
	Rectangle r3=Rectangle(x11,y11,x21,y21);
	cout<<"���������������Ϊ";
	r3.adjust(area);
	return 0;
}

