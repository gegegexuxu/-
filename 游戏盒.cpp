//游戏盒
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>//颜色，光标跳转，光标隐藏， 
#include<conio.h>//不回显键入getch,判断是否有键盘读入 
void color(int x);//字体和背景色控制
void gotoxy(int x,int y);//移动光标
void chessboard();//五子棋棋盘
void playchess();//五子棋下棋
struct placexy//五子棋便于输入的坐标 
{
	int x;
	int y;
};
int board[23][23]={0};//五子棋全局定义，记录棋盘的状态,1为白棋，-1为黑棋
void background_tu();//涂色大战背景
void gamer();//涂色大战游戏
void decide(int s[][22]);//涂色大战胜负判断 
void over();//游戏结束
int  world[22][22]={};//-1为墙，0为空，1，2，3，4
void background_level_1();//推箱子第一关
void background_level_2();//推箱子第二关
void background_level_3();//推箱子第三关
void background_level_4();//推箱子第四关
void background_level_5();//推箱子第五关
void boxplace(int s[][8],int b,int c,int *d);//指针，箱子位置判断
int  placebox(int a,int b,int c,int d,int s[][8],char f);//1:人的位置与墙冲突，2：箱子的位置与墙冲突，3：无冲突,0:无关
void pushbox(int *c,int *d,char f);//箱子位置的改变
void backperson(int *a,int *b,char f);//位置冲突，取消移动
void start_level_1();//第一关游戏开始 
void start_level_2();//第二关游戏开始
void start_level_3();//第三关游戏开始
void start_level_4();//第四关游戏开始
void start_level_5();//第五关游戏开始
int base1[8][8]={0};//推箱子全局定义，1为墙，2为目的地 
int base2[5][6]={0};
int base3[6][6]={0};
int base4[8][8]={0};
int base5[8][8]={0};
void maze();//走迷宫游戏 
void menu();//游戏盒主菜单 
int t=0;//迷宫时间
int ma=2,mb=1;//人的坐标初始化，ma为行mb为列
void time(int *a);//计时器
void tips(int i);//迷宫提示信息
void maze_level1_B();//迷宫背景 
void maze_level1_P();//迷宫 
void delay(int t)//延时，t越大越久,t为正整数 
{
	int j,i=568000000/t;
	for(j=0;j<i;j++);
}
void ying()  //隐藏光标 
{
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut,&cci);
	cci.bVisible=0;
	SetConsoleCursorInfo(hOut,&cci);
}
void color(int x)//字体和背景色控制 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}
void gotoxy(int x,int y)//移动光标 
{
	COORD coord={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int main()//主函数开始！
{
	char choose;
	ying(); //隐藏光标 
    for(;;)
    {
	system("CLS");
    menu();
    choose=getch();
	switch(choose)
	{
		case'1':
			system("CLS");//清屏幕，开始五子棋游戏 
			chessboard();
			playchess();
			int i,j;
			for(i=0;i<23;i++)
			{
				for(j=0;j<23;j++)
				{
					board[i][j]=0;
				}
			}
			break; 
		case'2':
			system("CLS");//清屏幕，开始涂色大战游戏
			background_tu();
			gamer();
			decide(world);
			over();
			break; 
		case'3':
			system("CLS");//清屏幕，开始推箱子游戏
			background_level_1();
			start_level_1();
			printf("恭喜过关！");
			delay(1); 
			system("CLS");
			background_level_2();
			start_level_2();
			printf("恭喜过关！");
			delay(1);
			system("CLS");
			background_level_3();
			start_level_3();
			printf("恭喜过关！");
			delay(1);
			system("CLS");
			background_level_4();
			start_level_4();
			printf("恭喜过关！"); 
			delay(1);
			system("CLS");
			background_level_5();
			start_level_5();
			printf("恭喜过关！"); 
			delay(1);
			break;
		case'4':
			system("CLS");
			maze_level1_B();
	        maze_level1_P();
	        gotoxy(0,35);
	        printf("闯关成功，用时：%d\n",t/12); 
	        system("PAUSE");
		case' ':
			gotoxy(0,35);
			printf("感谢您的使用\n");
			exit(0);
		default:break;	
	}
    }
}
void chessboard()//五子棋棋盘 
{
	int i,j;
	printf("\n\n\n\t\t\t***五子棋双人对战游戏***\n\n");
	printf("\t  ");
	for(i=1;i<16;i++)
	printf("%02d  ",i);
	printf("\n\t01╔═");
	for(i=0;i<13;i++)
	printf("══╦═");
	printf("══╗\n");
	for(i=0;i<13;i++)
	{
		printf("\t  ");
		for(j=0;j<13;j++)
		printf("║   ");
		printf("║   ║\n");
		printf("\t%02d╠═",i+2);
		for(j=0;j<13;j++)
		printf("══╬═");
		printf("══╣\n");
	}
	printf("\t  ║   ");
	for(i=0;i<13;i++)
	printf("║   ");
	printf("║\n\t15╚═");
	for(i=0;i<13;i++)
	printf("══╩═");
	printf("══╝\n");
}
void playchess()//五子棋下棋
{
    FILE *record;
	record=fopen("棋子输入记录.txt","w");
	struct placexy blackchess,whitechess;//黑棋，白棋的坐标 
	char point;//小数点 
	int i,j,a=0;
	int m,n;
	printf("输入对应坐标即可完成下棋！一定要是数字 字符 数字的形式！！\n\n");
	for(i=0;i<225;i=i+2)//不停的轮流下棋 
	{
		for(;;)
		{
		    gotoxy(0,37+i/2); 
		    printf("轮到白棋:                ");
		    gotoxy(10,37+i/2);
		    fflush(stdin);
			if(scanf("%d%c%d",&whitechess.x,&point,&whitechess.y)==3)
			{
				if(board[whitechess.x+4][whitechess.y+4]!=0||whitechess.x>15||whitechess.x<1||whitechess.y<1||whitechess.y>15)//判断是否超出棋盘或重复
			    {
					gotoxy(0,36);
		            color(24);
		            printf("该位置上已经有棋子存在，或棋子过界！");
		            color(7);
		        }
		        else
		        break;
		    }
		    else
		    {
		        gotoxy(0,36);
				color(24); 
			    printf("\t不合法的输入格式！"); 
		        color(7);
		    }
		}
		board[whitechess.x+4][whitechess.y+4]=1;//记录白棋
		gotoxy(0,36);
		printf("                                    ");//用空格覆盖实现指定地点的删除 
		gotoxy(4*whitechess.x+6,2*whitechess.y+4);
		printf("◆");
		fprintf(record,"白棋：%d.%d\n",whitechess.x,whitechess.y);//将白棋的位置存到文件中 
		for(m=whitechess.x;m<=whitechess.x+4;m++)//横向 
	    {
	    	if(board[m][whitechess.y+4]==1&&board[m+1][whitechess.y+4]==1&&board[m+2][whitechess.y+4]==1&&board[m+3][whitechess.y+4]==1&&board[m+4][whitechess.y+4]==1)
		    a=5; 
	    }
	    for(n=whitechess.y;n<=whitechess.y+4;n++)//纵向 
	    {
	    	if(board[whitechess.x+4][n]==1&&board[whitechess.x+4][n+1]==1&&board[whitechess.x+4][n+2]==1&&board[whitechess.x+4][n+3]==1&&board[whitechess.x+4][n+4]==1)
		    a=5;
	    }
	    for(m=whitechess.x,n=whitechess.y;m<=whitechess.x+4,n<=whitechess.y+4;m++,n++)//斜向‘撇’ 
	    {
		    if(board[m][n]==1&&board[m+1][n+1]==1&&board[m+2][n+2]==1&&board[m+3][n+3]==1&&board[m+4][n+4]==1)
		    a=5;
    	}
	    for(m=whitechess.x+8,n=whitechess.y;m>=whitechess.x+4,n<=whitechess.y+4;m--,n++)//斜向‘捺’ 
	    {
		    if(board[m][n]==1&&board[m-1][n+1]==1&&board[m-2][n+2]==1&&board[m-3][n+3]==1&&board[m-4][n+4]==1)
		    a=5;
	    }
	    if(a==5)
	    break;
	    for(;;)
		{
		    gotoxy(30,37+i/2); 
		    printf("轮到黑棋:                ");
		    gotoxy(40,37+i/2);
		    fflush(stdin);
			if(scanf("%d%c%d",&blackchess.x,&point,&blackchess.y)==3)
			{
				if(board[blackchess.x+4][blackchess.y+4]!=0||blackchess.x>15||blackchess.x<1||blackchess.y<1||blackchess.y>15)//判断是否超出棋盘或重复
			    {
					gotoxy(0,36);
		            color(24);
		            printf("该位置上已经有棋子存在，或棋子过界！");
		            color(7);
		        }
		        else
		        break;
		    }
		    else
		    {
		        gotoxy(0,36);
		        color(24);
			    printf("\t不合法的输入格式！"); 
		        color(7);
		    }
		}
    
		board[blackchess.x+4][blackchess.y+4]=-1;//记录黑棋 
		gotoxy(0,36);
	    printf("                                             ");
		gotoxy(4*blackchess.x+6,2*blackchess.y+4);
		printf("◇");
		fprintf(record,"黑棋：%d.%d\n",blackchess.x,blackchess.y);//将黑棋的位置存到文件中 
		for(m=blackchess.x;m<=blackchess.x+4;m++)//横向 
	    {
	    	if(board[m][blackchess.y+4]==-1&&board[m+1][blackchess.y+4]==-1&&board[m+2][blackchess.y+4]==-1&&board[m+3][blackchess.y+4]==-1&&board[m+4][blackchess.y+4]==-1)
		    a=-5; 
	    }
	    for(n=blackchess.y;n<=blackchess.y+4;n++)//纵向 
	    {
	    	if(board[blackchess.x+4][n]==-1&&board[blackchess.x+4][n+1]==-1&&board[blackchess.x+4][n+2]==-1&&board[blackchess.x+4][n+3]==-1&&board[blackchess.x+4][n+4]==-1)
		    a=-5;
	    }
	    for(m=blackchess.x,n=blackchess.y;m<=blackchess.x+4,n<=blackchess.y+4;m++,n++)//斜向‘撇’ 
	    {
		    if(board[m][n]==-1&&board[m+1][n+1]==-1&&board[m+2][n+2]==-1&&board[m+3][n+3]==-1&&board[m+4][n+4]==-1)
		    a=-5;
    	}
	    for(m=blackchess.x+8,n=blackchess.y;m>=blackchess.x+4,n<=blackchess.y+4;m--,n++)//斜向‘捺’ 
	    {
		    if(board[m][n]==-1&&board[m-1][n+1]==-1&&board[m-2][n+2]==-1&&board[m-3][n+3]==-1&&board[m-4][n+4]==-1)
		    a=-5;
	    }
	    if(a==-5)
	    break;
		gotoxy(0,38+i/2);
	}
	color(23);
	switch(a)
	{
		case  5:  gotoxy(0,38+i/2); printf("\n\t\t\t****白棋胜！****\t\t\t\n"); system("PAUSE");break;
		case -5:  gotoxy(0,38+i/2); printf("\n\t\t\t****黑棋胜！****\t\t\t\n"); system("PAUSE");break;
		default:  gotoxy(0,38+i/2); printf("\n\t\t\t****  和棋！****\t\t\t\n"); system("PAUSE");break;
	}
	color(07);
}
void  background_tu()//涂色大战背景
{
	int i,j;
	printf("\n\n\t\t\t******涂色大战游戏******\n\n\t\t");
	for(i=0;i<22;i++)
	{
		for(j=0;j<22;j++)
		if(i==0||j==0||i==21||j==21)
		{
			color(8); 
			printf("█");
			world[j][i]=-1;
			color(7);
		}
		else
		printf("  ");
		switch(i)
		{
		    case 2 :color(11); printf("一号玩家wasd控制");break;
		    case 4 :color(12); printf("二号玩家ijkl控制");break;
		    case 6 :color(13); printf("三号玩家5123控制");break;
		    case 8 :color(14); printf("四号玩家gvbn控制");break;
		    case 10:color(7);  printf("空格全部图上色后游戏就会结束！");break;
			case 12:printf("占领自己的地盘来获得游戏的胜利！"); 
			default:break;
	    }
		printf("\n\t\t"); 
	}
}

void gamer()//涂色大战游戏 
{
	int g1j=1,g1i=1,g2j=1,g2i=20,g3j=20,g3i=1,g4j=20,g4i=20;
	int i,j,m=400;//统计空格数 
	char mc;//用户的操作储存
	for(;;)
	{
	m=400;
	
	gotoxy(g1j*2+16,g1i+4);
	color(11);
	printf("♀");
	world[g1j][g1i]=1;
	gotoxy(g2j*2+16,g2i+4);
	color(12);
	printf("♀");
	world[g2j][g2i]=2;
	gotoxy(g3j*2+16,g3i+4);
	color(13);
	printf("♀");
	world[g3j][g3i]=3;
	gotoxy(g4j*2+16,g4i+4);
	color(14);
	printf("♀");
	world[g4j][g4i]=4;
	
	gotoxy(0,26);
	mc=getch();//读取用户键入符号
	
	gotoxy(g1j*2+16,g1i+4);
	color(176);
	printf("  ");
	gotoxy(g2j*2+16,g2i+4);
	color(192);
	printf("  ");
	gotoxy(g3j*2+16,g3i+4);
	color(208);
	printf("  ");
	gotoxy(g4j*2+16,g4i+4);
	color(224);
	printf("  ");
	
	switch(mc)
	{
	    case'a': g1j-=1; break;//1左 
		case'w': g1i-=1; break;//1上 
		case's': g1i+=1; break;//1下 
		case'd': g1j+=1; break;//1右 
		case'j': g2j-=1; break;//2左 
		case'i': g2i-=1; break;//2上
		case'k': g2i+=1; break;//2下
		case'l': g2j+=1; break;//2右 
		case'1': g3j-=1; break;//3左 
		case'5': g3i-=1; break;//3上 
		case'2': g3i+=1; break;//3下 
		case'3': g3j+=1; break;//3右 
		case'v': g4j-=1; break;//4左 
		case'g': g4i-=1; break;//4上 
		case'b': g4i+=1; break;//4下 
		case'n': g4j+=1; break;//4右
		default: break;
    }
    if(g1i==0||g1j==0||g1i==21||g1j==21||g2i==0||g2j==0||g2i==21||g2j==21||g3i==0||g3j==0||g3i==21||g3j==21||g4i==0||g4j==0||g4i==21||g4j==21)
    {
        switch(mc)
    	{
	        case'd': g1j-=1; break;//1左 
		    case's': g1i-=1; break;//1上 
		    case'w': g1i+=1; break;//1下 
		    case'a': g1j+=1; break;//1右 
	    	case'l': g2j-=1; break;//2左 
		    case'k': g2i-=1; break;//2上
		    case'i': g2i+=1; break;//2下
		    case'j': g2j+=1; break;//2右 
		    case'3': g3j-=1; break;//3左 
		    case'2': g3i-=1; break;//3上 
		    case'5': g3i+=1; break;//3下 
		    case'1': g3j+=1; break;//3右 
		    case'n': g4j-=1; break;//4左 
		    case'b': g4i-=1; break;//4上 
		    case'g': g4i+=1; break;//4下 
	    	case'v': g4j+=1; break;//4右 
		    default: break;
        }	
	}
	
	for(i=1;i<21;i++)
	{
		for(j=1;j<21;j++)
		if(world[j][i]!=0)
		m--; 
	}
	gotoxy(0,26);
	color(7);
	printf("空白块还有%3d个",m);
	if(m==0)
	break;
    }
}

void decide(int s[][22])//涂色大战胜负判断
{
	int i,j;
	int score[5]={};
	for(i=0;i<22;i++)//统计得分 
	{
		for(j=0;j<22;j++)
		{
			switch(s[i][j])
			{
				case 1: score[1]=score[1]+1; break;
				case 2: score[2]=score[2]+1; break;
				case 3: score[3]=score[3]+1; break;
				case 4: score[4]=score[4]+1; break;
				default: break;
			}
			s[i][j]=0;
		}
	}
	for(i=0;i<4;i++)
	{
		color(11+i);
		printf("\n\t%d号玩家的得分是%d\n",i+1,score[i+1]);
		 
		color(7);
	}
}

void over()//游戏结束
{
	char c='a';
	printf("\n游戏结束!按空格键跳出\n");
	while(c!=' ')
	{
		c=getch();
	}
}

void background_level_1()//推箱子第一关背景（围墙） 
{
	int i,j;
	printf("\n\n");
	printf("\t\t 推箱子第一关\n\n\t\t");
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if((i==0&&j>=2&&j<=4)||(i==1&&(j==2||j==4))||(i==2&&((j>=4&&j<=7)||j==2))||(i==3&&((j>=0&&j<=2)||j==7))||(i==4&&(j==0||(j>=5&&j<=7)))||(i==5&&((j>=0&&j<=3)||j==5))||(i==6&&(j==3||j==5))||(i==7&&j>=3&&j<=5))//墙
			{
				color(8); 
				printf("█");
				base1[j][i]=1;
				color(7); 
			}
			else
			{
				if((i==1&&j==3)||(i==3&&j==6)||(i==4&&j==1)||(i==6&&j==4))//目的地 
				{
					base1[j][i]=2;
					color(12);
					printf("☆");
					color(7);
				}
				else
				{
					color(7);
				    printf("  ");
				}
			}
		}
		if(i==0) printf(" w--->上");
		if(i==1) printf(" s--->下");
		if(i==2) printf(" a--->左");
		if(i==3) printf(" d--->右");
		if(i==4) printf(" r--->重来本关");
		printf("\n\t\t");
	}
}

void background_level_2()//推箱子第二关背景（围墙） 
{
	int i,j;
	printf("\n\n");
	printf("\t\t 推箱子第二关\n\n\t\t");
	for(i=0;i<6;i++)
	{
		for(j=0;j<5;j++)
		{
			if((i==0&&j<=3)||(i==1&&j!=2&&j!=1)||(i==2&&(j==0||j==4))||(i==5&&j<=3)||(i==4&&j!=2&&j!=1)||(i==3&&(j==0||j==4)))//墙 
			{
				color(8); 
				printf("█");
				base2[j][i]=1;
				color(7); 
			}
			else
			{
				if((i==1&&j==1)||(i==1&&j==2))//目的地 
				{
					base2[j][i]=2;
					color(12);
					printf("☆");
					color(7);
				}
				else
				{
					color(7);
				    printf("  ");
				}
			}
		}
		if(i==0) printf(" w--->上");
		if(i==1) printf(" s--->下");
		if(i==2) printf(" a--->左");
		if(i==3) printf(" d--->右");
		if(i==4) printf(" r--->重来本关");
		printf("\n\t\t");
	}
}

void background_level_3()//推箱子第三关背景（围墙） 
{
	int i,j;
	printf("\n\n");
	printf("\t\t 推箱子第三关\n\n\t\t");
	for(i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
		{
			if(((i==0||i==5)&&j>=1&&j<=4)||(i==1&&(j==1||j==4))||((i==2||i==4)&&((j>=0&&j<=1)||(j>=4&&j<=5)))||(i==3&&(j==0||j==5)))
			{
				color(8); 
				printf("█");
				base3[j][i]=1;
				color(7); 
			}
			else
			{
				if((i==3&&j==1)||(i==3&&j==4))//目的地 
				{
					base3[j][i]=2;
					color(12);
					printf("☆");
					color(7);
				}
				else
				{
					color(7);
				    printf("  ");
				}
			}
		}
		if(i==0) printf(" w--->上");
		if(i==1) printf(" s--->下");
		if(i==2) printf(" a--->左");
		if(i==3) printf(" d--->右");
		if(i==4) printf(" r--->重来本关");
		printf("\n\t\t");
	}
}

void background_level_4()//推箱子第四关背景（围墙） 
{
	int i,j;
	printf("\n\n");
	printf("\t\t 推箱子第四关\n\n\t\t");
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(((j==0||j==7)&&(i>=4&&i<=7))||((j==1||j==6)&&((i>=2&&i<=4)||i==7))||((j==2||j==5)&&((i>=0&&i<=2)||i==7))||((j==3||j==4)&&(i==0||i==7))||(j==3&&i==5))
			{
				color(8);
				printf("█");
				base4[j][i]=1;
				color(7);
			}
			else
			{
				if((i==1&&j==3)||(i==3&&j==5)||(i==2&&j==4)||(i==1&&j==4))//目的地 
				{
					base4[j][i]=2;
					color(12);
					printf("☆");
					color(7);
				}
				else
				{
					color(7);
				    printf("  ");
				}
			}
		}
		if(i==0) printf(" w--->上");
		if(i==1) printf(" s--->下");
		if(i==2) printf(" a--->左");
		if(i==3) printf(" d--->右");
		if(i==4) printf(" r--->重来本关");
		printf("\n\t\t");
	}
}

void background_level_5()//推箱子第五关背景（围墙） 
{
	int i,j;
	printf("\n\n");
	printf("\t\t 推箱子第五关\n\n\t\t");
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if((i==0&&j>=2&&j<=5)||(i==1&&(j==2||(j>=5&&j<=7)))||(i==2&&((j>=0&&j<=2)||j==7))||(i==3&&(j==0||j==5||j==7))||(i==4&&(j==0||j==7))||(i==5&&((j>=0&&j<=2)||(j>=5&&j<=7)))||(i==6&&(j==2||j==5))||(i==7&&j>=2&&j<=5))
			{
				color(8); 
				printf("█");
				base5[j][i]=1;
				color(7); 
			}
			else
			{
				if((i==3&&j==3)||(i==4&&j==4)||(i==3&&j==4))//目的地 
				{
					base5[j][i]=2;
					color(12);
					printf("☆");
					color(7);
				}
				else
				{
					color(7);
				    printf("  ");
				}
			}
		}
		if(i==0) printf(" w--->上");
		if(i==1) printf(" s--->下");
		if(i==2) printf(" a--->左");
		if(i==3) printf(" d--->右");
		if(i==4) printf(" r--->重来本关");
		printf("\n\t\t");
	}
}

void boxplace_23(int s[][6],int b,int c,int *d)////指针，箱子位置判断
{
	if(s[b][c]==2)
	{
		gotoxy(b*2+16,c+4);
		color(12);
		printf("★");
		color(7);
		*d=*d+1;
	}
	else
	{
		gotoxy(b*2+16,c+4);
		color(14);
		printf("□");
		color(7);
	}
}
void boxplace_145(int s[][8],int b,int c,int *d)////指针，箱子位置判断
{
	if(s[b][c]==2)
	{
		gotoxy(b*2+16,c+4);
		color(12);
		printf("★");
		color(7);
		*d=*d+1;
	}
	else
	{
		gotoxy(b*2+16,c+4);
		color(14);
		printf("□");
		color(7);
	}
}

int placebox_145(int a,int b,int c,int d,int s[][8],char f)//1:人的位置与墙冲突，2：箱子的位置与墙冲突，3：无冲突,0:无关 
{
	if(s[a][b]==1)
	return 1;
	if(a==c&&b==d)
	{
		switch(f)
	    {
	    	case'a': c-=1; break;
		    case'w': d-=1; break;
		    case's': d+=1; break;
		    case'd': c+=1; break;
		    default: break;
    	}
		if(s[c][d]==1)
	    return 2;
	    else
	    return 3;
	}
	return 0;
}
int placebox_23(int a,int b,int c,int d,int s[][6],char f)//1:人的位置与墙冲突，2：箱子的位置与墙冲突，3：无冲突,0:无关 
{
	if(s[a][b]==1)
	return 1;
	if(a==c&&b==d)
	{
		switch(f)
	    {
	    	case'a': c-=1; break;
		    case'w': d-=1; break;
		    case's': d+=1; break;
		    case'd': c+=1; break;
		    default: break;
    	}
		if(s[c][d]==1)
	    return 2;
	    else
	    return 3;
	}
	
	return 0;
}

void pushbox(int *c,int *d,char f)//箱子位置的改变 
{
	switch(f)
	{
	    case'a': *c-=1; break;
		case'w': *d-=1; break;
		case's': *d+=1; break;
		case'd': *c+=1; break;
		default: break;
    }
}

void backperson(int *a,int *b,char f)//位置冲突，取消移动
{
	switch(f)
	{
	    case'a': *a+=1; break;
		case'w': *b+=1; break;
		case's': *b-=1; break;
		case'd': *a-=1; break;
		default: break;
    }
}

void start_level_1()//开始 
{
    int pj=4,pi=4,b1j=3,b1i=3,b2j=3,b2i=4,b3j=4,b3i=3,b4j=4,b4i=5;//人，箱子的坐标初始化
	char mc;//用户的操作储存
	int a=0,b;
    while(a!=4)
	{
		a=0;
		b=0;
		gotoxy(pj*2+16,pi+4);
		color(11);
		printf("♀");
		color(7);
		boxplace_145(base1,b1j,b1i,&a);//箱子是否到达了目的地 
		boxplace_145(base1,b2j,b2i,&a);
		boxplace_145(base1,b3j,b3i,&a);
		boxplace_145(base1,b4j,b4i,&a);
		if(a==4) break;
		fflush(stdin);
		mc=getch();//读取用户键入符号
		
		color(12);
		gotoxy(pj*2+16,pi+4);//清除上一次痕迹
		if((pi==1&&pj==3)||(pi==3&&pj==6)||(pi==4&&pj==1)||(pi==6&&pj==4))
		printf("☆");
		else
		printf("  ");
		color(7); 
		
	    switch(mc)
	    {
	    	case'a': pj-=1; break;
		    case'w': pi-=1; break;
		    case's': pi+=1; break;
		    case'd': pj+=1; break;
		    case'r': system("CLS"); background_level_1();start_level_1(); break; 
		    default: break;
    	}
		if(mc=='r') break;
		b=placebox_145(pj,pi,b1j,b1i,base1,mc);
		switch(b)
		{
			case 3: pushbox(&b1j,&b1i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
		
		b=placebox_145(pj,pi,b2j,b2i,base1,mc);
		switch(b)
		{
			case 3: pushbox(&b2j,&b2i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
		
		b=placebox_145(pj,pi,b3j,b3i,base1,mc);
		switch(b)
		{
			case 3: pushbox(&b3j,&b3i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
		
		b=placebox_145(pj,pi,b4j,b4i,base1,mc);
		switch(b)
		{
			case 3: pushbox(&b4j,&b4i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
	}
	gotoxy(20,16);
}

void start_level_2()//开始 
{
    int pj=3,pi=2,b1j=2,b1i=2,b2j=2,b2i=3;//人，箱子的坐标初始化
	char mc;//用户的操作储存
	int a=0,b;
    while(a!=2)
	{
		a=0;
		b=0;
		gotoxy(pj*2+16,pi+4);
		color(11);
		printf("♀");
		
		boxplace_23(base2,b1j,b1i,&a);//箱子是否到达了目的地 
		boxplace_23(base2,b2j,b2i,&a);
		if(a==2) break;
		fflush(stdin);
		mc=getch();//读取用户键入符号
		
		color(12);
		gotoxy(pj*2+16,pi+4);//清除上一次痕迹
		if((pi==1&&pj==1)||(pi==1&&pj==2))
		printf("☆");
		else
		printf("  ");
		color(7);
	    switch(mc)
	    {
	    	case'a': pj-=1; break;
		    case'w': pi-=1; break;
		    case's': pi+=1; break;
		    case'd': pj+=1; break;
		    case'r': system("CLS"); background_level_2();start_level_2(); break; 
		    default: break;
    	}
		if(mc=='r') break;
		
		b=placebox_23(pj,pi,b1j,b1i,base2,mc);
		switch(b)
		{
			case 3: pushbox(&b1j,&b1i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
		
		b=placebox_23(pj,pi,b2j,b2i,base2,mc);
		switch(b)
		{
			case 3: pushbox(&b2j,&b2i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
	}
	gotoxy(20,16);
}

void start_level_3()
{
    int pj=3,pi=4,b1j=2,b1i=3,b2j=3,b2i=3;//人，箱子的坐标初始化
	char mc;//用户的操作储存
	int a=0,b;
    while(a!=2)
	{
		a=0;
		b=0;
		gotoxy(pj*2+16,pi+4);
		color(11);
		printf("♀");
		color(7);
		boxplace_23(base3,b1j,b1i,&a);//箱子是否到达了目的地 
		boxplace_23(base3,b2j,b2i,&a);
		if(a==2) break;
		fflush(stdin);
		mc=getch();//读取用户键入符号
		
		color(12);
		gotoxy(pj*2+16,pi+4);//清除上一次痕迹
		if((pi==3&&pj==1)||(pi==3&&pj==4))
		printf("☆");
		else
		printf("  ");
		color(7);
	    switch(mc)
	    {
	    	case'a': pj-=1; break;
		    case'w': pi-=1; break;
		    case's': pi+=1; break;
		    case'd': pj+=1; break;
		    case'r': system("CLS"); background_level_3();start_level_3(); break; 
		    default: break;
    	}
		if(mc=='r') break;
		
		b=placebox_23(pj,pi,b1j,b1i,base3,mc);
		switch(b)
		{
			case 3: pushbox(&b1j,&b1i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
		
		b=placebox_23(pj,pi,b2j,b2i,base3,mc);
		switch(b)
		{
			case 3: pushbox(&b2j,&b2i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
		
	}
	gotoxy(20,16);
}
void start_level_4()
{
    int pj=4,pi=4,b1j=4,b1i=3,b2j=4,b2i=5,b3j=5,b3i=4,b4j=5,b4i=5;//人，箱子的坐标初始化
	char mc;//用户的操作储存
	int a=0,b;
    while(a!=4)
	{
		a=0;
		b=0;
		gotoxy(pj*2+16,pi+4);
		color(11);
		printf("♀");
		color(7);
		boxplace_145(base4,b1j,b1i,&a);//箱子是否到达了目的地 
		boxplace_145(base4,b2j,b2i,&a);
		boxplace_145(base4,b3j,b3i,&a);//箱子是否到达了目的地 
		boxplace_145(base4,b4j,b4i,&a);
		if(a==4) break;
		fflush(stdin);
		mc=getch();//读取用户键入符号
		
		color(12);
		gotoxy(pj*2+16,pi+4);//清除上一次痕迹
		if((pi==1&&pj==3)||(pi==3&&pj==5)||(pi==2&&pj==4)||(pi==1&&pj==4))
		printf("☆");
		else
		printf("  ");
		color(7);
	    switch(mc)
	    {
	    	case'a': pj-=1; break;
		    case'w': pi-=1; break;
		    case's': pi+=1; break;
		    case'd': pj+=1; break;
		    case'r': system("CLS"); background_level_4();start_level_4(); break; 
		    default: break;
    	}
		if(mc=='r') break;
		
		b=placebox_145(pj,pi,b1j,b1i,base4,mc);
		switch(b)
		{
			case 3: pushbox(&b1j,&b1i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
		b=placebox_145(pj,pi,b2j,b2i,base4,mc);
		switch(b)
		{
			case 3: pushbox(&b2j,&b2i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
		b=placebox_145(pj,pi,b3j,b3i,base4,mc);
		switch(b)
		{
			case 3: pushbox(&b3j,&b3i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
		b=placebox_145(pj,pi,b4j,b4i,base4,mc);
		switch(b)
		{
			case 3: pushbox(&b4j,&b4i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
		
	}
	gotoxy(20,16);
}
void start_level_5()
{
    int pj=4,pi=5,b1j=3,b1i=3,b2j=4,b2i=4,b3j=3,b3i=4;//人，箱子的坐标初始化
	char mc;//用户的操作储存
	int a=0,b;
    while(a!=3)
	{
		a=0;
		b=0;
		gotoxy(pj*2+16,pi+4);
		color(11);
		printf("♀");
		color(7);
		
		boxplace_145(base5,b1j,b1i,&a);//箱子是否到达了目的地 
		boxplace_145(base5,b2j,b2i,&a);
		boxplace_145(base5,b3j,b3i,&a);
		if(a==3) break;
		fflush(stdin);
		mc=getch();//读取用户键入符号
		
		color(12);
		gotoxy(pj*2+16,pi+4);//清除上一次痕迹
		if((pi==3&&pj==3)||(pi==4&&pj==4)||(pi==3&&pj==4))
		printf("☆");
		else
		printf("  ");
		color(7);
	    switch(mc)
	    {
	    	case'a': pj-=1; break;
		    case'w': pi-=1; break;
		    case's': pi+=1; break;
		    case'd': pj+=1; break;
		    case'r': system("CLS"); background_level_5();start_level_5(); break; 
		    default: break;
    	}
		if(mc=='r') break;
		
		b=placebox_145(pj,pi,b1j,b1i,base5,mc);
		switch(b)
		{
			case 3: pushbox(&b1j,&b1i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
		
		b=placebox_145(pj,pi,b2j,b2i,base5,mc);
		switch(b)
		{
			case 3: pushbox(&b2j,&b2i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
		
		b=placebox_145(pj,pi,b3j,b3i,base5,mc);
		switch(b)
		{
			case 3: pushbox(&b3j,&b3i,mc);   break;
			case 2: backperson(&pj,&pi,mc);  break;
			case 1: backperson(&pj,&pi,mc);  break;
			case 0: break;
		}
	}
	gotoxy(20,16);
}
void maze_level1_P()//
{
	char mc;//用户的操作储存

	int i,a,b;
	for(i=0;;i=1)
	{
	    if(i!=0)
	    {	
			gotoxy(a,b);
	    	color(60);
	    	printf("  ");
	    	color(07);
		}
		gotoxy(ma,mb);
	    color(60);
	    printf("♀");
	    color(07);
	    a=ma;
	    b=mb;
	    gotoxy(0,35);
		if(mb==33&&ma==58)
		{
			printf("恭喜过关！");
			break;
		}
	    delay(20);
	    if(kbhit())
        mc=getch();
        time(&t);
	    switch(mc)
	    {
	    	case'a': ma-=2; break;
		    case'w': mb-=1; break;
		    case's': mb+=1; break;
		    case'd': ma+=2; break;
		    default: break;
    	}
	    if(mb==0||ma==0||ma==60||mb==34||(ma==4&&mb!=33)||(ma==8&&mb!=2)||(ma==12&&mb!=33)||(ma==16&&mb!=18)||(ma==20&&mb!=6)||(ma==24&&mb!=4)||(ma==28&&mb!=2)||(ma==32&&mb!=20)||(ma==36&&mb!=22)||(ma==40&&mb!=28)||(ma==44&&mb!=14)||(ma==48&&mb!=12)||(ma==52&&mb!=15)||(ma==56&&mb!=2))
	    {
		    switch(mc)
	        {
		        case'a': ma+=2; break;
		        case'w': mb+=1; break;
		        case's': mb-=1; break;
	            case'd': ma-=2; break;
	            default: break;
            }
	    }
	    mc='*';
    }
}
void time(int *a)
{
	gotoxy(70,7);
	printf("%3d",*a/12);
	*a=*a+1;
}
void tips(int i)//提示信息 
{	
    if(i==1)
	printf("这是一个简单的迷宫，");
	if(i==2)
	printf("简简单单，");
	if(i==3)
	printf("背后是无穷无尽、");
	if(i==4)
	printf("要人性命的代码。");
	if(i==7)
	printf("消耗时间：");
	if(i==10)
	printf("w---向上移动");
	if(i==11)
	printf("s---向下移动"); 
	if(i==12)
	printf("a---向左移动");
	if(i==13)
	printf("d---向右移动");
	if(i==15)
	printf("控制'♀'到达终点");
	if(i==16)
	printf("处即可通关");	
} 
void maze_level1_B()//第一关背景 
{
	int i,j;
	{ 
	    for(i=0;i<35;i++)
	    {
		    for(j=0;j<31;j++)
		    {
			    if(i==0||j==0||j==30||i==34||(j==2&&i!=33)||(j==4&&i!=2)||(j==6&&i!=33)||(j==8&&i!=18)||(j==10&&i!=6)||(j==12&&i!=4)||(j==14&&i!=2)||(j==16&&i!=20)||(j==18&&i!=22)||(j==20&&i!=28)||(j==22&&i!=14)||(j==24&&i!=12)||(j==26&&i!=15)||(j==28&&i!=2))//“围墙” 
		    	{
		    	    color(07);
		    		printf("█");//一个符号占两个空格
		    		color(07);
		    	} 
		    	else
		    	{
			        if(i==33&&j==29)
			        {
			        	printf("☆");
			    	}
				    else
			    	{
				        color(60);
				        printf("  ");
				        color(07);
			        }
			    }
	    	}
	    	tips(i); 
	       	printf("\n");
       	}
    }
}
void menu()
{
	int i,j;
	for(i=0;i<30;i++)
	{
		printf("\n\t\t");
		switch(i)
		{
			case 0 : printf("┏━");break;
			case 1 : printf("┃ ") ; break;
			case 2 : printf("┃━");break;
			case 3 : printf("┃┏");break;
			case 28: printf("┃┗");break;		
			case 29: printf("┗━");break;
			default: printf("┃┃");break;
		}
		for(j=0;j<40;j++)
		{
			if(i==0||i==3||i==2||i==28||i==29)
			printf("━");
			else
			printf(" ");
		}
		switch(i)
		{
			case 0 : printf("━┓");break;
			case 1 : printf(" ┃") ;break;
			case 2 : printf("━┃");break;
			case 3 : printf("┓┃");break;
			case 28: printf("┛┃");break;		
			case 29: printf("━┛");break;

			default: printf("┃┃");break;
		}
	}
	gotoxy(25,2);
	printf("充满乐趣的简易小游戏合集！");
	gotoxy(22,6);
	printf("1.五子棋（双人对战）");
	gotoxy(22,9);
	printf("2.涂色大战（四人对战）");
	gotoxy(22,12);
	printf("3.推箱子（5关）");
	gotoxy(22,15);
	printf("4.走迷宫");
	gotoxy(22,18);
	printf("输入序号即可开始游戏");
	gotoxy(22,21);
	printf("全屏游戏体验更佳！");
	gotoxy(22,24);
	printf("按空格键退出");
}
