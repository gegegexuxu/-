//��Ϸ��
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>//��ɫ�������ת��������أ� 
#include<conio.h>//�����Լ���getch,�ж��Ƿ��м��̶��� 
void color(int x);//����ͱ���ɫ����
void gotoxy(int x,int y);//�ƶ����
void chessboard();//����������
void playchess();//����������
struct placexy//������������������ 
{
	int x;
	int y;
};
int board[23][23]={0};//������ȫ�ֶ��壬��¼���̵�״̬,1Ϊ���壬-1Ϊ����
void background_tu();//Ϳɫ��ս����
void gamer();//Ϳɫ��ս��Ϸ
void decide(int s[][22]);//Ϳɫ��սʤ���ж� 
void over();//��Ϸ����
int  world[22][22]={};//-1Ϊǽ��0Ϊ�գ�1��2��3��4
void background_level_1();//�����ӵ�һ��
void background_level_2();//�����ӵڶ���
void background_level_3();//�����ӵ�����
void background_level_4();//�����ӵ��Ĺ�
void background_level_5();//�����ӵ����
void boxplace(int s[][8],int b,int c,int *d);//ָ�룬����λ���ж�
int  placebox(int a,int b,int c,int d,int s[][8],char f);//1:�˵�λ����ǽ��ͻ��2�����ӵ�λ����ǽ��ͻ��3���޳�ͻ,0:�޹�
void pushbox(int *c,int *d,char f);//����λ�õĸı�
void backperson(int *a,int *b,char f);//λ�ó�ͻ��ȡ���ƶ�
void start_level_1();//��һ����Ϸ��ʼ 
void start_level_2();//�ڶ�����Ϸ��ʼ
void start_level_3();//��������Ϸ��ʼ
void start_level_4();//���Ĺ���Ϸ��ʼ
void start_level_5();//�������Ϸ��ʼ
int base1[8][8]={0};//������ȫ�ֶ��壬1Ϊǽ��2ΪĿ�ĵ� 
int base2[5][6]={0};
int base3[6][6]={0};
int base4[8][8]={0};
int base5[8][8]={0};
void maze();//���Թ���Ϸ 
void menu();//��Ϸ�����˵� 
int t=0;//�Թ�ʱ��
int ma=2,mb=1;//�˵������ʼ����maΪ��mbΪ��
void time(int *a);//��ʱ��
void tips(int i);//�Թ���ʾ��Ϣ
void maze_level1_B();//�Թ����� 
void maze_level1_P();//�Թ� 
void delay(int t)//��ʱ��tԽ��Խ��,tΪ������ 
{
	int j,i=568000000/t;
	for(j=0;j<i;j++);
}
void ying()  //���ع�� 
{
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut,&cci);
	cci.bVisible=0;
	SetConsoleCursorInfo(hOut,&cci);
}
void color(int x)//����ͱ���ɫ���� 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}
void gotoxy(int x,int y)//�ƶ���� 
{
	COORD coord={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int main()//��������ʼ��
{
	char choose;
	ying(); //���ع�� 
    for(;;)
    {
	system("CLS");
    menu();
    choose=getch();
	switch(choose)
	{
		case'1':
			system("CLS");//����Ļ����ʼ��������Ϸ 
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
			system("CLS");//����Ļ����ʼͿɫ��ս��Ϸ
			background_tu();
			gamer();
			decide(world);
			over();
			break; 
		case'3':
			system("CLS");//����Ļ����ʼ��������Ϸ
			background_level_1();
			start_level_1();
			printf("��ϲ���أ�");
			delay(1); 
			system("CLS");
			background_level_2();
			start_level_2();
			printf("��ϲ���أ�");
			delay(1);
			system("CLS");
			background_level_3();
			start_level_3();
			printf("��ϲ���أ�");
			delay(1);
			system("CLS");
			background_level_4();
			start_level_4();
			printf("��ϲ���أ�"); 
			delay(1);
			system("CLS");
			background_level_5();
			start_level_5();
			printf("��ϲ���أ�"); 
			delay(1);
			break;
		case'4':
			system("CLS");
			maze_level1_B();
	        maze_level1_P();
	        gotoxy(0,35);
	        printf("���سɹ�����ʱ��%d\n",t/12); 
	        system("PAUSE");
		case' ':
			gotoxy(0,35);
			printf("��л����ʹ��\n");
			exit(0);
		default:break;	
	}
    }
}
void chessboard()//���������� 
{
	int i,j;
	printf("\n\n\n\t\t\t***������˫�˶�ս��Ϸ***\n\n");
	printf("\t  ");
	for(i=1;i<16;i++)
	printf("%02d  ",i);
	printf("\n\t01�X�T");
	for(i=0;i<13;i++)
	printf("�T�T�j�T");
	printf("�T�T�[\n");
	for(i=0;i<13;i++)
	{
		printf("\t  ");
		for(j=0;j<13;j++)
		printf("�U   ");
		printf("�U   �U\n");
		printf("\t%02d�d�T",i+2);
		for(j=0;j<13;j++)
		printf("�T�T�p�T");
		printf("�T�T�g\n");
	}
	printf("\t  �U   ");
	for(i=0;i<13;i++)
	printf("�U   ");
	printf("�U\n\t15�^�T");
	for(i=0;i<13;i++)
	printf("�T�T�m�T");
	printf("�T�T�a\n");
}
void playchess()//����������
{
    FILE *record;
	record=fopen("���������¼.txt","w");
	struct placexy blackchess,whitechess;//���壬��������� 
	char point;//С���� 
	int i,j,a=0;
	int m,n;
	printf("�����Ӧ���꼴��������壡һ��Ҫ������ �ַ� ���ֵ���ʽ����\n\n");
	for(i=0;i<225;i=i+2)//��ͣ���������� 
	{
		for(;;)
		{
		    gotoxy(0,37+i/2); 
		    printf("�ֵ�����:                ");
		    gotoxy(10,37+i/2);
		    fflush(stdin);
			if(scanf("%d%c%d",&whitechess.x,&point,&whitechess.y)==3)
			{
				if(board[whitechess.x+4][whitechess.y+4]!=0||whitechess.x>15||whitechess.x<1||whitechess.y<1||whitechess.y>15)//�ж��Ƿ񳬳����̻��ظ�
			    {
					gotoxy(0,36);
		            color(24);
		            printf("��λ�����Ѿ������Ӵ��ڣ������ӹ��磡");
		            color(7);
		        }
		        else
		        break;
		    }
		    else
		    {
		        gotoxy(0,36);
				color(24); 
			    printf("\t���Ϸ��������ʽ��"); 
		        color(7);
		    }
		}
		board[whitechess.x+4][whitechess.y+4]=1;//��¼����
		gotoxy(0,36);
		printf("                                    ");//�ÿո񸲸�ʵ��ָ���ص��ɾ�� 
		gotoxy(4*whitechess.x+6,2*whitechess.y+4);
		printf("��");
		fprintf(record,"���壺%d.%d\n",whitechess.x,whitechess.y);//�������λ�ô浽�ļ��� 
		for(m=whitechess.x;m<=whitechess.x+4;m++)//���� 
	    {
	    	if(board[m][whitechess.y+4]==1&&board[m+1][whitechess.y+4]==1&&board[m+2][whitechess.y+4]==1&&board[m+3][whitechess.y+4]==1&&board[m+4][whitechess.y+4]==1)
		    a=5; 
	    }
	    for(n=whitechess.y;n<=whitechess.y+4;n++)//���� 
	    {
	    	if(board[whitechess.x+4][n]==1&&board[whitechess.x+4][n+1]==1&&board[whitechess.x+4][n+2]==1&&board[whitechess.x+4][n+3]==1&&board[whitechess.x+4][n+4]==1)
		    a=5;
	    }
	    for(m=whitechess.x,n=whitechess.y;m<=whitechess.x+4,n<=whitechess.y+4;m++,n++)//б��Ʋ�� 
	    {
		    if(board[m][n]==1&&board[m+1][n+1]==1&&board[m+2][n+2]==1&&board[m+3][n+3]==1&&board[m+4][n+4]==1)
		    a=5;
    	}
	    for(m=whitechess.x+8,n=whitechess.y;m>=whitechess.x+4,n<=whitechess.y+4;m--,n++)//б���࡯ 
	    {
		    if(board[m][n]==1&&board[m-1][n+1]==1&&board[m-2][n+2]==1&&board[m-3][n+3]==1&&board[m-4][n+4]==1)
		    a=5;
	    }
	    if(a==5)
	    break;
	    for(;;)
		{
		    gotoxy(30,37+i/2); 
		    printf("�ֵ�����:                ");
		    gotoxy(40,37+i/2);
		    fflush(stdin);
			if(scanf("%d%c%d",&blackchess.x,&point,&blackchess.y)==3)
			{
				if(board[blackchess.x+4][blackchess.y+4]!=0||blackchess.x>15||blackchess.x<1||blackchess.y<1||blackchess.y>15)//�ж��Ƿ񳬳����̻��ظ�
			    {
					gotoxy(0,36);
		            color(24);
		            printf("��λ�����Ѿ������Ӵ��ڣ������ӹ��磡");
		            color(7);
		        }
		        else
		        break;
		    }
		    else
		    {
		        gotoxy(0,36);
		        color(24);
			    printf("\t���Ϸ��������ʽ��"); 
		        color(7);
		    }
		}
    
		board[blackchess.x+4][blackchess.y+4]=-1;//��¼���� 
		gotoxy(0,36);
	    printf("                                             ");
		gotoxy(4*blackchess.x+6,2*blackchess.y+4);
		printf("��");
		fprintf(record,"���壺%d.%d\n",blackchess.x,blackchess.y);//�������λ�ô浽�ļ��� 
		for(m=blackchess.x;m<=blackchess.x+4;m++)//���� 
	    {
	    	if(board[m][blackchess.y+4]==-1&&board[m+1][blackchess.y+4]==-1&&board[m+2][blackchess.y+4]==-1&&board[m+3][blackchess.y+4]==-1&&board[m+4][blackchess.y+4]==-1)
		    a=-5; 
	    }
	    for(n=blackchess.y;n<=blackchess.y+4;n++)//���� 
	    {
	    	if(board[blackchess.x+4][n]==-1&&board[blackchess.x+4][n+1]==-1&&board[blackchess.x+4][n+2]==-1&&board[blackchess.x+4][n+3]==-1&&board[blackchess.x+4][n+4]==-1)
		    a=-5;
	    }
	    for(m=blackchess.x,n=blackchess.y;m<=blackchess.x+4,n<=blackchess.y+4;m++,n++)//б��Ʋ�� 
	    {
		    if(board[m][n]==-1&&board[m+1][n+1]==-1&&board[m+2][n+2]==-1&&board[m+3][n+3]==-1&&board[m+4][n+4]==-1)
		    a=-5;
    	}
	    for(m=blackchess.x+8,n=blackchess.y;m>=blackchess.x+4,n<=blackchess.y+4;m--,n++)//б���࡯ 
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
		case  5:  gotoxy(0,38+i/2); printf("\n\t\t\t****����ʤ��****\t\t\t\n"); system("PAUSE");break;
		case -5:  gotoxy(0,38+i/2); printf("\n\t\t\t****����ʤ��****\t\t\t\n"); system("PAUSE");break;
		default:  gotoxy(0,38+i/2); printf("\n\t\t\t****  ���壡****\t\t\t\n"); system("PAUSE");break;
	}
	color(07);
}
void  background_tu()//Ϳɫ��ս����
{
	int i,j;
	printf("\n\n\t\t\t******Ϳɫ��ս��Ϸ******\n\n\t\t");
	for(i=0;i<22;i++)
	{
		for(j=0;j<22;j++)
		if(i==0||j==0||i==21||j==21)
		{
			color(8); 
			printf("��");
			world[j][i]=-1;
			color(7);
		}
		else
		printf("  ");
		switch(i)
		{
		    case 2 :color(11); printf("һ�����wasd����");break;
		    case 4 :color(12); printf("�������ijkl����");break;
		    case 6 :color(13); printf("�������5123����");break;
		    case 8 :color(14); printf("�ĺ����gvbn����");break;
		    case 10:color(7);  printf("�ո�ȫ��ͼ��ɫ����Ϸ�ͻ������");break;
			case 12:printf("ռ���Լ��ĵ����������Ϸ��ʤ����"); 
			default:break;
	    }
		printf("\n\t\t"); 
	}
}

void gamer()//Ϳɫ��ս��Ϸ 
{
	int g1j=1,g1i=1,g2j=1,g2i=20,g3j=20,g3i=1,g4j=20,g4i=20;
	int i,j,m=400;//ͳ�ƿո��� 
	char mc;//�û��Ĳ�������
	for(;;)
	{
	m=400;
	
	gotoxy(g1j*2+16,g1i+4);
	color(11);
	printf("��");
	world[g1j][g1i]=1;
	gotoxy(g2j*2+16,g2i+4);
	color(12);
	printf("��");
	world[g2j][g2i]=2;
	gotoxy(g3j*2+16,g3i+4);
	color(13);
	printf("��");
	world[g3j][g3i]=3;
	gotoxy(g4j*2+16,g4i+4);
	color(14);
	printf("��");
	world[g4j][g4i]=4;
	
	gotoxy(0,26);
	mc=getch();//��ȡ�û��������
	
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
	    case'a': g1j-=1; break;//1�� 
		case'w': g1i-=1; break;//1�� 
		case's': g1i+=1; break;//1�� 
		case'd': g1j+=1; break;//1�� 
		case'j': g2j-=1; break;//2�� 
		case'i': g2i-=1; break;//2��
		case'k': g2i+=1; break;//2��
		case'l': g2j+=1; break;//2�� 
		case'1': g3j-=1; break;//3�� 
		case'5': g3i-=1; break;//3�� 
		case'2': g3i+=1; break;//3�� 
		case'3': g3j+=1; break;//3�� 
		case'v': g4j-=1; break;//4�� 
		case'g': g4i-=1; break;//4�� 
		case'b': g4i+=1; break;//4�� 
		case'n': g4j+=1; break;//4��
		default: break;
    }
    if(g1i==0||g1j==0||g1i==21||g1j==21||g2i==0||g2j==0||g2i==21||g2j==21||g3i==0||g3j==0||g3i==21||g3j==21||g4i==0||g4j==0||g4i==21||g4j==21)
    {
        switch(mc)
    	{
	        case'd': g1j-=1; break;//1�� 
		    case's': g1i-=1; break;//1�� 
		    case'w': g1i+=1; break;//1�� 
		    case'a': g1j+=1; break;//1�� 
	    	case'l': g2j-=1; break;//2�� 
		    case'k': g2i-=1; break;//2��
		    case'i': g2i+=1; break;//2��
		    case'j': g2j+=1; break;//2�� 
		    case'3': g3j-=1; break;//3�� 
		    case'2': g3i-=1; break;//3�� 
		    case'5': g3i+=1; break;//3�� 
		    case'1': g3j+=1; break;//3�� 
		    case'n': g4j-=1; break;//4�� 
		    case'b': g4i-=1; break;//4�� 
		    case'g': g4i+=1; break;//4�� 
	    	case'v': g4j+=1; break;//4�� 
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
	printf("�հ׿黹��%3d��",m);
	if(m==0)
	break;
    }
}

void decide(int s[][22])//Ϳɫ��սʤ���ж�
{
	int i,j;
	int score[5]={};
	for(i=0;i<22;i++)//ͳ�Ƶ÷� 
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
		printf("\n\t%d����ҵĵ÷���%d\n",i+1,score[i+1]);
		 
		color(7);
	}
}

void over()//��Ϸ����
{
	char c='a';
	printf("\n��Ϸ����!���ո������\n");
	while(c!=' ')
	{
		c=getch();
	}
}

void background_level_1()//�����ӵ�һ�ر�����Χǽ�� 
{
	int i,j;
	printf("\n\n");
	printf("\t\t �����ӵ�һ��\n\n\t\t");
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if((i==0&&j>=2&&j<=4)||(i==1&&(j==2||j==4))||(i==2&&((j>=4&&j<=7)||j==2))||(i==3&&((j>=0&&j<=2)||j==7))||(i==4&&(j==0||(j>=5&&j<=7)))||(i==5&&((j>=0&&j<=3)||j==5))||(i==6&&(j==3||j==5))||(i==7&&j>=3&&j<=5))//ǽ
			{
				color(8); 
				printf("��");
				base1[j][i]=1;
				color(7); 
			}
			else
			{
				if((i==1&&j==3)||(i==3&&j==6)||(i==4&&j==1)||(i==6&&j==4))//Ŀ�ĵ� 
				{
					base1[j][i]=2;
					color(12);
					printf("��");
					color(7);
				}
				else
				{
					color(7);
				    printf("  ");
				}
			}
		}
		if(i==0) printf(" w--->��");
		if(i==1) printf(" s--->��");
		if(i==2) printf(" a--->��");
		if(i==3) printf(" d--->��");
		if(i==4) printf(" r--->��������");
		printf("\n\t\t");
	}
}

void background_level_2()//�����ӵڶ��ر�����Χǽ�� 
{
	int i,j;
	printf("\n\n");
	printf("\t\t �����ӵڶ���\n\n\t\t");
	for(i=0;i<6;i++)
	{
		for(j=0;j<5;j++)
		{
			if((i==0&&j<=3)||(i==1&&j!=2&&j!=1)||(i==2&&(j==0||j==4))||(i==5&&j<=3)||(i==4&&j!=2&&j!=1)||(i==3&&(j==0||j==4)))//ǽ 
			{
				color(8); 
				printf("��");
				base2[j][i]=1;
				color(7); 
			}
			else
			{
				if((i==1&&j==1)||(i==1&&j==2))//Ŀ�ĵ� 
				{
					base2[j][i]=2;
					color(12);
					printf("��");
					color(7);
				}
				else
				{
					color(7);
				    printf("  ");
				}
			}
		}
		if(i==0) printf(" w--->��");
		if(i==1) printf(" s--->��");
		if(i==2) printf(" a--->��");
		if(i==3) printf(" d--->��");
		if(i==4) printf(" r--->��������");
		printf("\n\t\t");
	}
}

void background_level_3()//�����ӵ����ر�����Χǽ�� 
{
	int i,j;
	printf("\n\n");
	printf("\t\t �����ӵ�����\n\n\t\t");
	for(i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
		{
			if(((i==0||i==5)&&j>=1&&j<=4)||(i==1&&(j==1||j==4))||((i==2||i==4)&&((j>=0&&j<=1)||(j>=4&&j<=5)))||(i==3&&(j==0||j==5)))
			{
				color(8); 
				printf("��");
				base3[j][i]=1;
				color(7); 
			}
			else
			{
				if((i==3&&j==1)||(i==3&&j==4))//Ŀ�ĵ� 
				{
					base3[j][i]=2;
					color(12);
					printf("��");
					color(7);
				}
				else
				{
					color(7);
				    printf("  ");
				}
			}
		}
		if(i==0) printf(" w--->��");
		if(i==1) printf(" s--->��");
		if(i==2) printf(" a--->��");
		if(i==3) printf(" d--->��");
		if(i==4) printf(" r--->��������");
		printf("\n\t\t");
	}
}

void background_level_4()//�����ӵ��Ĺر�����Χǽ�� 
{
	int i,j;
	printf("\n\n");
	printf("\t\t �����ӵ��Ĺ�\n\n\t\t");
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(((j==0||j==7)&&(i>=4&&i<=7))||((j==1||j==6)&&((i>=2&&i<=4)||i==7))||((j==2||j==5)&&((i>=0&&i<=2)||i==7))||((j==3||j==4)&&(i==0||i==7))||(j==3&&i==5))
			{
				color(8);
				printf("��");
				base4[j][i]=1;
				color(7);
			}
			else
			{
				if((i==1&&j==3)||(i==3&&j==5)||(i==2&&j==4)||(i==1&&j==4))//Ŀ�ĵ� 
				{
					base4[j][i]=2;
					color(12);
					printf("��");
					color(7);
				}
				else
				{
					color(7);
				    printf("  ");
				}
			}
		}
		if(i==0) printf(" w--->��");
		if(i==1) printf(" s--->��");
		if(i==2) printf(" a--->��");
		if(i==3) printf(" d--->��");
		if(i==4) printf(" r--->��������");
		printf("\n\t\t");
	}
}

void background_level_5()//�����ӵ���ر�����Χǽ�� 
{
	int i,j;
	printf("\n\n");
	printf("\t\t �����ӵ����\n\n\t\t");
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if((i==0&&j>=2&&j<=5)||(i==1&&(j==2||(j>=5&&j<=7)))||(i==2&&((j>=0&&j<=2)||j==7))||(i==3&&(j==0||j==5||j==7))||(i==4&&(j==0||j==7))||(i==5&&((j>=0&&j<=2)||(j>=5&&j<=7)))||(i==6&&(j==2||j==5))||(i==7&&j>=2&&j<=5))
			{
				color(8); 
				printf("��");
				base5[j][i]=1;
				color(7); 
			}
			else
			{
				if((i==3&&j==3)||(i==4&&j==4)||(i==3&&j==4))//Ŀ�ĵ� 
				{
					base5[j][i]=2;
					color(12);
					printf("��");
					color(7);
				}
				else
				{
					color(7);
				    printf("  ");
				}
			}
		}
		if(i==0) printf(" w--->��");
		if(i==1) printf(" s--->��");
		if(i==2) printf(" a--->��");
		if(i==3) printf(" d--->��");
		if(i==4) printf(" r--->��������");
		printf("\n\t\t");
	}
}

void boxplace_23(int s[][6],int b,int c,int *d)////ָ�룬����λ���ж�
{
	if(s[b][c]==2)
	{
		gotoxy(b*2+16,c+4);
		color(12);
		printf("��");
		color(7);
		*d=*d+1;
	}
	else
	{
		gotoxy(b*2+16,c+4);
		color(14);
		printf("��");
		color(7);
	}
}
void boxplace_145(int s[][8],int b,int c,int *d)////ָ�룬����λ���ж�
{
	if(s[b][c]==2)
	{
		gotoxy(b*2+16,c+4);
		color(12);
		printf("��");
		color(7);
		*d=*d+1;
	}
	else
	{
		gotoxy(b*2+16,c+4);
		color(14);
		printf("��");
		color(7);
	}
}

int placebox_145(int a,int b,int c,int d,int s[][8],char f)//1:�˵�λ����ǽ��ͻ��2�����ӵ�λ����ǽ��ͻ��3���޳�ͻ,0:�޹� 
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
int placebox_23(int a,int b,int c,int d,int s[][6],char f)//1:�˵�λ����ǽ��ͻ��2�����ӵ�λ����ǽ��ͻ��3���޳�ͻ,0:�޹� 
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

void pushbox(int *c,int *d,char f)//����λ�õĸı� 
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

void backperson(int *a,int *b,char f)//λ�ó�ͻ��ȡ���ƶ�
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

void start_level_1()//��ʼ 
{
    int pj=4,pi=4,b1j=3,b1i=3,b2j=3,b2i=4,b3j=4,b3i=3,b4j=4,b4i=5;//�ˣ����ӵ������ʼ��
	char mc;//�û��Ĳ�������
	int a=0,b;
    while(a!=4)
	{
		a=0;
		b=0;
		gotoxy(pj*2+16,pi+4);
		color(11);
		printf("��");
		color(7);
		boxplace_145(base1,b1j,b1i,&a);//�����Ƿ񵽴���Ŀ�ĵ� 
		boxplace_145(base1,b2j,b2i,&a);
		boxplace_145(base1,b3j,b3i,&a);
		boxplace_145(base1,b4j,b4i,&a);
		if(a==4) break;
		fflush(stdin);
		mc=getch();//��ȡ�û��������
		
		color(12);
		gotoxy(pj*2+16,pi+4);//�����һ�κۼ�
		if((pi==1&&pj==3)||(pi==3&&pj==6)||(pi==4&&pj==1)||(pi==6&&pj==4))
		printf("��");
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

void start_level_2()//��ʼ 
{
    int pj=3,pi=2,b1j=2,b1i=2,b2j=2,b2i=3;//�ˣ����ӵ������ʼ��
	char mc;//�û��Ĳ�������
	int a=0,b;
    while(a!=2)
	{
		a=0;
		b=0;
		gotoxy(pj*2+16,pi+4);
		color(11);
		printf("��");
		
		boxplace_23(base2,b1j,b1i,&a);//�����Ƿ񵽴���Ŀ�ĵ� 
		boxplace_23(base2,b2j,b2i,&a);
		if(a==2) break;
		fflush(stdin);
		mc=getch();//��ȡ�û��������
		
		color(12);
		gotoxy(pj*2+16,pi+4);//�����һ�κۼ�
		if((pi==1&&pj==1)||(pi==1&&pj==2))
		printf("��");
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
    int pj=3,pi=4,b1j=2,b1i=3,b2j=3,b2i=3;//�ˣ����ӵ������ʼ��
	char mc;//�û��Ĳ�������
	int a=0,b;
    while(a!=2)
	{
		a=0;
		b=0;
		gotoxy(pj*2+16,pi+4);
		color(11);
		printf("��");
		color(7);
		boxplace_23(base3,b1j,b1i,&a);//�����Ƿ񵽴���Ŀ�ĵ� 
		boxplace_23(base3,b2j,b2i,&a);
		if(a==2) break;
		fflush(stdin);
		mc=getch();//��ȡ�û��������
		
		color(12);
		gotoxy(pj*2+16,pi+4);//�����һ�κۼ�
		if((pi==3&&pj==1)||(pi==3&&pj==4))
		printf("��");
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
    int pj=4,pi=4,b1j=4,b1i=3,b2j=4,b2i=5,b3j=5,b3i=4,b4j=5,b4i=5;//�ˣ����ӵ������ʼ��
	char mc;//�û��Ĳ�������
	int a=0,b;
    while(a!=4)
	{
		a=0;
		b=0;
		gotoxy(pj*2+16,pi+4);
		color(11);
		printf("��");
		color(7);
		boxplace_145(base4,b1j,b1i,&a);//�����Ƿ񵽴���Ŀ�ĵ� 
		boxplace_145(base4,b2j,b2i,&a);
		boxplace_145(base4,b3j,b3i,&a);//�����Ƿ񵽴���Ŀ�ĵ� 
		boxplace_145(base4,b4j,b4i,&a);
		if(a==4) break;
		fflush(stdin);
		mc=getch();//��ȡ�û��������
		
		color(12);
		gotoxy(pj*2+16,pi+4);//�����һ�κۼ�
		if((pi==1&&pj==3)||(pi==3&&pj==5)||(pi==2&&pj==4)||(pi==1&&pj==4))
		printf("��");
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
    int pj=4,pi=5,b1j=3,b1i=3,b2j=4,b2i=4,b3j=3,b3i=4;//�ˣ����ӵ������ʼ��
	char mc;//�û��Ĳ�������
	int a=0,b;
    while(a!=3)
	{
		a=0;
		b=0;
		gotoxy(pj*2+16,pi+4);
		color(11);
		printf("��");
		color(7);
		
		boxplace_145(base5,b1j,b1i,&a);//�����Ƿ񵽴���Ŀ�ĵ� 
		boxplace_145(base5,b2j,b2i,&a);
		boxplace_145(base5,b3j,b3i,&a);
		if(a==3) break;
		fflush(stdin);
		mc=getch();//��ȡ�û��������
		
		color(12);
		gotoxy(pj*2+16,pi+4);//�����һ�κۼ�
		if((pi==3&&pj==3)||(pi==4&&pj==4)||(pi==3&&pj==4))
		printf("��");
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
	char mc;//�û��Ĳ�������

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
	    printf("��");
	    color(07);
	    a=ma;
	    b=mb;
	    gotoxy(0,35);
		if(mb==33&&ma==58)
		{
			printf("��ϲ���أ�");
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
void tips(int i)//��ʾ��Ϣ 
{	
    if(i==1)
	printf("����һ���򵥵��Թ���");
	if(i==2)
	printf("��򵥵���");
	if(i==3)
	printf("�����������޾���");
	if(i==4)
	printf("Ҫ�������Ĵ��롣");
	if(i==7)
	printf("����ʱ�䣺");
	if(i==10)
	printf("w---�����ƶ�");
	if(i==11)
	printf("s---�����ƶ�"); 
	if(i==12)
	printf("a---�����ƶ�");
	if(i==13)
	printf("d---�����ƶ�");
	if(i==15)
	printf("����'��'�����յ�");
	if(i==16)
	printf("������ͨ��");	
} 
void maze_level1_B()//��һ�ر��� 
{
	int i,j;
	{ 
	    for(i=0;i<35;i++)
	    {
		    for(j=0;j<31;j++)
		    {
			    if(i==0||j==0||j==30||i==34||(j==2&&i!=33)||(j==4&&i!=2)||(j==6&&i!=33)||(j==8&&i!=18)||(j==10&&i!=6)||(j==12&&i!=4)||(j==14&&i!=2)||(j==16&&i!=20)||(j==18&&i!=22)||(j==20&&i!=28)||(j==22&&i!=14)||(j==24&&i!=12)||(j==26&&i!=15)||(j==28&&i!=2))//��Χǽ�� 
		    	{
		    	    color(07);
		    		printf("��");//һ������ռ�����ո�
		    		color(07);
		    	} 
		    	else
		    	{
			        if(i==33&&j==29)
			        {
			        	printf("��");
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
			case 0 : printf("����");break;
			case 1 : printf("�� ") ; break;
			case 2 : printf("����");break;
			case 3 : printf("����");break;
			case 28: printf("����");break;		
			case 29: printf("����");break;
			default: printf("����");break;
		}
		for(j=0;j<40;j++)
		{
			if(i==0||i==3||i==2||i==28||i==29)
			printf("��");
			else
			printf(" ");
		}
		switch(i)
		{
			case 0 : printf("����");break;
			case 1 : printf(" ��") ;break;
			case 2 : printf("����");break;
			case 3 : printf("����");break;
			case 28: printf("����");break;		
			case 29: printf("����");break;

			default: printf("����");break;
		}
	}
	gotoxy(25,2);
	printf("������Ȥ�ļ���С��Ϸ�ϼ���");
	gotoxy(22,6);
	printf("1.�����壨˫�˶�ս��");
	gotoxy(22,9);
	printf("2.Ϳɫ��ս�����˶�ս��");
	gotoxy(22,12);
	printf("3.�����ӣ�5�أ�");
	gotoxy(22,15);
	printf("4.���Թ�");
	gotoxy(22,18);
	printf("������ż��ɿ�ʼ��Ϸ");
	gotoxy(22,21);
	printf("ȫ����Ϸ������ѣ�");
	gotoxy(22,24);
	printf("���ո���˳�");
}
