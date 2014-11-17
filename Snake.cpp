#include<fstream>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<Windows.h>

using namespace std;

int sx[1000],sy[1000],n,egg=0,apple=0,start=0,curse=0,ctr_apple=0,ctr_curse=0,ctr_egg=0,ctr=0,h=0;
int g[21][60],i,j,x=10,y=27,lose=0,lvl=1;
int apple_x,apple_y,curse_x,curse_y,egg_x,egg_y;
long int score=0;


void replay()
{
	system("cls");
	char c[100];
	ifstream fin("replay.txt");

	while(fin.eof()==0)
	{
		fin.getline(c,100);
		if(strcmp(c,"clear")==0)
			{
				Sleep(150);
				system("cls");
			}
		else
			cout<<c<<endl;
	}
}

void initial()
{
		int i,j;
		sx[0]=10;sy[0]=27;
		sx[1]=11;sy[0]=27;
		sx[2]=12;sy[0]=27;
		egg=apple=start=curse=ctr_apple=ctr_curse=ctr_egg=ctr=h=lose=0;
		x=10;y=27;lvl=1;score=0;
		for(i=3;i<1000;i++)
			{
				sx[i]=0;
				sy[i]=0;
			}
		n=2;
		for(i=0;i<21;++i)
			for(j=0;j<60;++j)
			{
				g[i][j]=0;

			}
}
void main()
{
	char c,k,temp,base,head,body;
	base=(char)175;
	head=(char)2;
	body=(char)169;
	system("cls");
	START:
	srand((unsigned int)time(NULL));
	initial();
	ofstream refresh("replay.txt");
	refresh.close();
	ofstream fout("replay.txt",ios::app);
	cout<<"Use for movement:\n\n"
		<<"\t         w(up)\n"
		<<"\ta(left)  s(down)  d(right)\n\n"
		<<"'*' - egg     10 points (+2 pts fr each egg fr every 7 eggs eaten)\n"
		<<"      length(+1)        (+1 length fr each egg fr every 15 eggs eaten)\n\n"
		<<"'@' - apple   25 points\n"
		<<"      length(-3)\n\n"
		<<"'#' - curse   35 points\n"
		<<"      length(+3)\n\n"
		<<"->Snake can go through wall in level 1...\n->level 2 unlocked at 750 pts...\n->snake dies on contact with wall on level 2...\n\n"
		<<"Press any key to continue";
	_getch();




while(1)
{
	system("cls");
	g[sx[0]][sy[0]]=2;
	if(start==1 && (egg!=1 || apple!=1 || curse!=1))
	{
	if(egg!=2 + (score/350))
		{
			egg_x=(rand()%21)+1;
			egg_y=(rand()%60)+1;
			if(g[egg_x][egg_y]==0)
			  {
					g[egg_x][egg_y]=1;
					++egg;
			  }
		}
	if(apple!=1)
		{
			apple=(rand()%21)+1;
			if(apple==1)
				{
					apple_x=(rand()%21)+1;
					apple_y=(rand()%60)+1;
					if(g[apple_x][apple_y]==0)
						g[apple_x][apple_y]=4;
					else
						apple=0;
				}
		}

	if(curse!=1)
		{
			curse=(rand()%21)+1;
			if(curse==1)
				{
					curse_x=(rand()%21)+1;
					curse_y=(rand()%60)+1;
					if(g[curse_x][curse_y]==0)
						g[curse_x][curse_y]=5;
					else
						curse=0;
				}
		}
	}
	if(apple==1)
		{
			ctr_apple++;
			if(ctr_apple==90)
				{
					apple=0;
					ctr_apple=0;
					g[apple_x][apple_y]=0;
				}
		}
	if(curse==1)
		{
			ctr_curse++;
			if(ctr_curse==100)
				{
					curse=0;
					ctr_curse=0;
					g[curse_x][curse_y]=0;
				}
		}

	for(i=0;i<21;++i)
		{
			for(j=0;j<60;++j)
				{

					if(g[i][j]==0)
						{
							cout<<" ";
							fout<<" ";
						}
					else
						if(g[i][j]==3)
							{
								cout<<"0";
								fout<<"0";
							}
						else
							if(g[i][j]==2)
								{
									cout<<head;
									fout<<head;
								}
							else
								if(g[i][j]==1)
									{
										cout<<"*";
										fout<<"*";
									}
								else
									if(g[i][j]==4)
										{
											cout<<"@";
											fout<<"@";
										}
									else
										if(g[i][j]==5)
											{
												cout<<"#";
												fout<<"#";
											}

				}
			cout<<"|";
			fout<<"|";
			if(i==2)
				{
					cout<<"\t"<<score;
					fout<<"\t"<<score;
				}
			cout<<endl;
			fout<<endl;

		}

	for(j=0;j<60;++j)
		{
			cout<<base;
			fout<<base;
		}

	fout<<endl<<"clear"<<endl;


	if(score>=750 && lvl==1)
		{
			cout<<endl<<"Proceed to level 2...beware of the walls...press direction to continue...";
			_getch();
			k=_getch();
			if((k=='w' || k=='a' || k=='s' || k=='d'))
				c=k;

			lvl=2;
		}
	while(start==0)
		{
			c=_getch();
			if(c=='w' || c=='a' || c=='s' || c=='d')
				start=1;
		}



	if(lose==1 && h==0)
		{
			char opt;
			cout<<"\ngame over...your score is: "<<score;
			fout.close();
			cout<<endl<<"New game?\t(y/n)\nor check replay\t(r)";
			do{
				opt=_getch();
				if(opt=='y')
					goto START;
				if(opt=='r')
					{
						replay();
						cout<<endl<<"New game?\t(y/n)\nor check replay\t(r)";
					}
				}while(opt!='n');
			return;
		}

	Sleep(150);
	
	if(_kbhit())
		{
			k=_getch();
			if((k=='w' || k=='a' || k=='s' || k=='d') && (((int)k+(int)c)!=197&&((int)k+(int)c)!=234))
				c=k;
			else
				if(k=='h')
					{
						temp=c;
						c=k;
					}
		}
	g[sx[n]][sy[n]]=0;
	for(i=n;i>=1;i--)
	{
		sx[i]=sx[i-1];
		sy[i]=sy[i-1];
		g[sx[i]][sy[i]]=3;
	}



	 MOVE:
		switch(c)
		{
			case 'w':
				if(x-1>=0)
					{
						--x;
						--sx[0];
					}
				else
					if(lvl==1)
					{
						x=20;
						sx[0]=20;
					}
					else
						lose=1;

				break;

			case 's':
				if(x+1<21)
					{
						++x;
						++sx[0];
					}
				else
					if(lvl==1)
					{
						x=0;
						sx[0]=0;
					}
					else
						lose=1;
				break;

			case 'a':
				if(y-1>=0)
					{
						--y;
						--sy[0];
					}
				else
					if(lvl==1)
					{
						y=59;
						sy[0]=59;
					}
					else
						lose=1;
				break;

			case 'd':
				if(y+1<60)
					{
						++y;
						++sy[0];
					}
				else
					if(lvl==1)
						{
							y=0;
							sy[0]=0;
						}
					else
						lose=1;
				break;

			case 'h':
				if(h==0)
					h=1;
				else
					{
						h=0;
						lose=0;
					}
				c=temp;
				goto MOVE;



			default:
				break;
	}
		if(g[sx[0]][sy[0]]!=0)
			if(g[sx[0]][sy[0]]==3)
				lose=1;
			else
				if(g[sx[0]][sy[0]]==1)
					{
						++ctr;
						score+=10+2*(ctr/7);
						for(int q=1;q<=(1+ctr/15);q++)
							{
								++n;
								sx[n]=sx[n-1];
								sy[n]=sy[n-1];
							}
						--egg;
					}
				else
					if(g[sx[0]][sy[0]]==4)
						{
							score+=25;
							apple=0;
							for(int q=0;q<3;q++)
							if(n>0)
								{

									g[sx[n]][sy[n]]=0;
									--n;
								}


						}
					else
						if(g[sx[0]][sy[0]]==5)
						{
							score+=35;
							curse=0;
							for(int q=0;q<3;q++)
							{
								++n;
								sx[n]=sx[n-1];
								sy[n]=sy[n-1];
							}


						}

  }
}