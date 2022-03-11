#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<Mmsystem.h>
#include <graphics.h>
#define Length 1200//��ͼ�ĳ�
#define Width 800//��ͼ�Ŀ�
#define sizePaint 20//���ؿ�Ĵ�С
#define N 100//�ϰ�����������
#pragma comment(lib,"winmm.lib")
using namespace std;
typedef struct Snake//����ߵ�λ������
{
	int x;
	int y;
	struct Snake *next;
}snake;
struct Obstacle//����ϰ����λ������
{
	int x[N];
	int y[N];
}obstacle;
struct Food //���ʳ���λ������
{
	int x;
	int y;
}Apple,Caomei,Yintao;
struct rec//��¼��Ϸ�÷֣���Ϸʱ��,��ҵ�ID
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int highscore;
    char name[10];
}record[10];
struct cm
{	//����ṹ������
    int nian;
    int yue;
    int ri;
    int num;
}chenmi;
mouse_msg msg = {0};//�������ṹ��

snake *head;
int grate;//����ķ���
int speed;//����ʱ��
int speed1;//����ٶ�
int level;//�Ѷȵȼ�
int getAppleNum;//�Ե���ƻ������
int getCaomeiNum;//�Ե��Ĳ�ݮ����
int getYintaoNum;//�Ե���ӣ�Ҹ���
int direction;//��ʾ���˶��ķ���
int obstacleNum;//�ϰ���ĸ���
int snakelen;//�ߵĳ���
int score;//����
char name[10];
PIMAGE menu,paiming,help,carrot,caomei,stone,apple,yintao,snakeHead,snakeBody,white,over,reconds,difficulty,fangchenmi;

void getPaint();//��������Ҫ�õ���ͼƬ
void showMenu();//��ʾ���˵�
void showOver();//��ʾ��Ϸ��������
int fcm();//������
int mouse(int,int,int,int);//�ж����ĵ��
void data();//��ʼ��������
void createMap();//���ɵ�ͼ

void createFood(int);//����ʳ��
void createSnake();//���쿪��ʱ����
void createObstacle();//�����ϰ���
int snakeControl();//�����ߵ��ƶ�
void snakeMove();//��ʾ�ߵ��ƶ�
int snakeDie();//�ж����Ƿ�����
void snakeStop();//ʹ��Ϸ��ͣ
void putScore();//���Ŀǰ�ķ������ٶ�
void getHighScore(struct rec []);//�½��ļ��򽫷��������ļ���
void storeHighScore(struct rec []);//���������ļ���ȡ�����浽�ṹ����
void Ranking(struct rec []);//������ ����������������ʾ�ڻ�����
void recond();//��¼���÷���

int main()
{
	int flag=0,c=0;
	initgraph(Length,Width);//��ʼ������
	getPaint();//������Ҫ�õ���ͼƬ
	do
	{
	    MUSIC music;//��������
        music.OpenFile("one.wav");
        music.Play();
		if (c==0)
			showMenu();//��ʾ������
		else if (c==1)
		{
			showOver();//��ʾ��Ϸ�������� ����������󷵻����˵�
			getch();
			showMenu();
		}
		for(;is_run();delay_fps(60))
		{
    		while (mousemsg())//��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ
			{
	      		msg = getmouse();//�������Ϣ�������ṹ��
			}
			if (c==1 && mouse(0,0,Length,Width)==1)
			{
				c=0;flag=0;	break;
			}
			if(mouse(22,610,245,790)==1)//������������ʼ��Ϸ
        	{
            	flag=1;	break;
			}
			if(mouse(335,610,563,790)==1)//�������������а�
			{
				flag=2;	break;
			}
			if(mouse(634,610,868,790)==1)//��������������
			{
				flag=3;	break;
			}
			if(mouse(951,610,1180,790)==1)//�����������˳�
			{
				flag=4;	break;
			}
		}
		if(flag==1)//��굥���˿�ʼ��Ϸ�󣬿�ʼѡ����Ϸ�Ѷ�
		{
			if(fcm()==1)
			{
				putimage(0,0,1200,800,fangchenmi,0,0,1200,800);
				getch();
				closegraph();
				return 0;
			}
			putimage(0,0,1200,800,difficulty,0,0,1200,800);
			for(;is_run();delay_fps(60))
			{
				while (mousemsg())//��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ
				{
	      	  		msg = getmouse();//�������Ϣ�������ṹ��
				}
				if(mouse(448,144,761,271)==1)//��ģʽ
				{
					level=1;	break;
				}
				if(mouse(448,334,761,452)==1)//һ��ģʽ
				{
					level=2;	break;
				}
				if(mouse(448,530,761,652)==1)//����ģʽ
				{
					level=3;	break;
				}
			}
		}

		switch(flag)
		{
			case 1://��ʼ��Ϸ
				data();
				createMap();
				inputbox_getline("ID","����������ID",name,10);
				createSnake();
				createFood(3);
				c=snakeControl();

				recond();
    			system("cls");//����
				break;

			case 2://��ʾ���а�
				putimage(0,0,1200,800,paiming,0,0,1200,800);
				score=0;
				recond();
				Ranking(record);
				getch();
				break;

			case 3://��ʾ��������
				putimage(0,0,1200,800,help,0,0,1200,800);
				getch();
				break;

			case 4://�˳�����
				closegraph();
				return 0;
		}
	}while(1);
	getch();
    closegraph();

	return 0;
}



int mouse(int x1,int y1,int x2,int y2)   //�ж���(x1,y1)(x2,y2)���η�Χ�ڵ������
{
	if(msg.x>x1&&msg.x<x2&&msg.y>y1&&msg.y<y2&&(int)msg.is_down()==1&&(int)msg.is_left()==1)
	   return 1;
	return 0;
}
void showMenu()//��ʾ���˵�����
{
	putimage(0,0,1200,800,menu,0,0,1200,800);
}
void showOver()//��ʾ��Ϸ��������
{
	putimage(0,0,1200,800,over,0,0,1200,800);
}
void createFood(int n)//�������ʳ��
{
	srand((unsigned)time(NULL));//�������������
	int i,flag;//flag���ж��������ʳ���Ƿ��������
	snake *body;
	if(n==0)//�Ե���һ��ʳ��Ƚ���������ʳ���ñ���ɫ���ǵ���֮�����������������ʳ�� ����ˢ��Ч��
	{
		putimage(Caomei.x,Caomei.y,20,20,white,0,0,20,20);
		putimage(Yintao.x,Yintao.y,20,20,white,0,0,20,20);
	}
	else if(n==1)
	{
		putimage(Apple.x,Apple.y,20,20,white,0,0,20,20);
		putimage(Yintao.x,Yintao.y,20,20,white,0,0,20,20);
	}
	else if(n==2)
	{
		putimage(Apple.x,Apple.y,20,20,white,0,0,20,20);
		putimage(Caomei.x,Caomei.y,20,20,white,0,0,20,20);
	}

	do
	{
		flag=1;
		body=head;//��ȡ�������ͷ�ڵ���Ϣ
		Apple.x=(rand()%38+1)*sizePaint;//������ɷ��ѣ�������Ģ��������
		Apple.y=(rand()%38+1)*sizePaint;
		Caomei.x=(rand()%38+1)*sizePaint;
		Caomei.y=(rand()%38+1)*sizePaint;
		Yintao.x=(rand()%38+1)*sizePaint;
		Yintao.y=(rand()%38+1)*sizePaint;
		if((Apple.x==Caomei.x&&Apple.y==Caomei.y)||(Apple.x==Yintao.x&&Apple.y==Yintao.y)||(Caomei.x==Yintao.x&&Caomei.y==Yintao.y))//��ֹʳ�������غ�
		{
			flag=0;	break;
		}
		while (body != NULL&&flag!=0)//��ֹʳ������������������
		{
			if ((Apple.x == body->x&&Apple.y == body->y)||(Caomei.x == body->x&&Caomei.y == body->y)||(Yintao.x == body->x&&Yintao.y == body->y))//�ж�ʳ�������Ƿ��������������
			{
				flag=0;	break;
			}
			body = body->next;
		}
		for(i=0;i<=obstacleNum;i++)//��ֹʳ��������������ɵ��ϰ�����
		{
			if((Apple.x==obstacle.x[i]&&Apple.y==obstacle.y[i])||(Caomei.x==obstacle.x[i]&&Caomei.y==obstacle.y[i])||(Yintao.x==obstacle.x[i]&&Yintao.y==obstacle.y[i])||flag==0)//�ж�ʳ�������Ƿ�����ϰ�������
			{
				flag=0;	break;
			}
		}
		if(flag==1)//���������ɵ�ʳ���������������ʳ��
		{
			putimage(Apple.x,Apple.y,20,20,caomei,0,0,20,20);
			putimage(Caomei.x,Caomei.y,20,20,yintao,0,0,20,20);
			putimage(Yintao.x,Yintao.y,20,20,apple,0,0,20,20);
		}
	}while(!flag);
}
void createMap()//��������ʱ����Ϸ��ͼ
{
	setfillcolor(EGERGB(240,255,240));
	bar(20,20,780,780);
	int i;
	for(i=1;i<=40;i++)//��С���ܲ�Χ����Ϸ����ı߿�
	{
		putimage(20*(i-1),0,20,20,stone,0,0,20,20);
		putimage(20*(i-1),780,20,20,stone,0,0,20,20);
	}
	for(i=1;i<=38;i++)
	{
		putimage(0,20*i,20,20,stone,0,0,20,20);
		putimage(780,20*i,20,20,stone,0,0,20,20);
	}
	putimage(800,0,400,800,reconds,0,0,400,800);//��ʾ��Ϸ��¼����
        putimage(825,400,20,20,apple,0,0,20,20);
        putimage(825,430,20,20,yintao,0,0,20,20);
        putimage(825,460,20,20,caomei,0,0,20,20);
        putimage(920,610,20,20,stone,0,0,20,20);
}

void createObstacle()//�����ϰ���
{
	snake *body;
	int i,flag,x,y;
	srand((unsigned)time(NULL));//�������������
	do
	{
		body=head;//��ȡ�������ͷ�ڵ���Ϣ
		flag=1;
		x=(rand()%38+1)*sizePaint;//��������ϰ��������
		y=(rand()%38+1)*sizePaint;
		for(i=0;i<obstacleNum;i++) //�ж������ɵ��ϰ��������Ƿ���ھ��ϰ�������
		{
			if(obstacle.x[i]==x&&obstacle.y[i]==y)
			{
				flag=0;	break;
		    }
		}
		while (body != NULL)//��ֹʳ������������������
	    {
		    if (x == body->x&&y == body->y)//�ж������ɵ��ϰ��������Ƿ��������������
		    {
	            flag=0;	break;
		    }
		    body=body->next;
	    }
	    if((x==Apple.x&&y==Apple.y)||(x==Caomei.x&&y==Caomei.y)||(x==Yintao.x&&y==Yintao.y))//��ֹ�ϰ����ʳ���غ�
	    	flag=0;
		if((x==(head->x)||x==(head->x-1*sizePaint)||x==(head->x+1*sizePaint)||x==(head->x+2*sizePaint))&&(y==(head->y-1*sizePaint)||y==(head->y)||y==(head->y+1*sizePaint)||y==(head->y+2*sizePaint))&&flag==1)//�ж��µ��ϰ����Ƿ�����ͷ�Ա�  ��ֹ��ͻȻ����
		    flag=0;
	}while(!flag);

	obstacle.x[obstacleNum]=x;//�������ɵ��ϰ���ĺ��������ṹ��������
	obstacle.y[obstacleNum]=y;//�������ɵ��ϰ�������������ṹ��������
	obstacleNum++;//�ϰ����������1
	for(i=0;i<obstacleNum;i++)//��ӡ�ϰ���
	{
		putimage(obstacle.x[i],obstacle.y[i],20,20,stone,0,0,20,20);
	}

}
void createSnake()//��������ʱ����
{
	snake *p;
	int i;
	p=(snake*)malloc(sizeof(snake));//��p����ռ�
	p->x=2*sizePaint;//��ʼ����βλ�õĺ�����
	p->y=10*sizePaint;//��ʼ����βλ�õ�������
	p->next=NULL;
	for(i=0;i<snakelen;i++)//�����ߵ�λ��   ���巨
	{
		head=(snake*)malloc(sizeof(snake));//��head����ռ�
		head->x=(2+i)*sizePaint;
		head->y=10*sizePaint;
		head->next=p;
		p=head;
	}
	putimage(p->x,p->y,20,20,snakeHead,0,0,20,20);//��ӡ��ͷ
	p=p->next;
	while(p!=NULL)//��ӡ����
	{
		putimage(p->x,p->y,20,20,snakeBody,0,0,20,20);
		p=p->next;
	}
}

int snakeControl()//�����ߵ��ƶ�
{
    int a=0;
	while(1)//����ѭ��ʹ����һֱ�˶�
	{
		if(GetAsyncKeyState('W')&&direction!=3)//���������������߲������ƶ�
		    direction=2;
		else if(GetAsyncKeyState('S')&&direction!=2)//���������������߲������ƶ�
		    direction=3;
		else if(GetAsyncKeyState('D')&&direction!=1)//���������������߲������ƶ�
		    direction=0;
		else if(GetAsyncKeyState('A')&&direction!=0)//���������������߲������ƶ�
		    direction=1;
		else if(GetAsyncKeyState(VK_SPACE))//����������ո�ʱ ��ͣ
			snakeStop();
		Sleep(speed);//ͨ����������ʱ��������ѭ���ٶ�  �Ӷ������ߵ��ٶ�
		snakeMove();//��ʾ�ߵ��ƶ�Ч��
		putScore();//�����Ҳ����Ϸ��¼
		a=snakeDie();//�ж����Ƿ�����
		if(a==1)
			return 1;
	}
	return 0;
}

void snakeMove()//��ʾ�ߵ��ƶ�
{
	snake *headnext,*q;
	headnext=(snake*)malloc(sizeof(snake));//��headnext����ռ�
	if(direction==0)//�����ƶ�
	{
		headnext->x=head->x+sizePaint;
	    headnext->y=head->y;
	}
	else if(direction==1)//�����ƶ�
	{
		headnext->x=head->x-sizePaint;
		headnext->y=head->y;
	}
	else if(direction==2)//�����ƶ�
	{
		headnext->x=head->x;
		headnext->y=head->y-sizePaint;
	}
	else if(direction==3)//�����ƶ�
	{
		headnext->x=head->x;
		headnext->y=head->y+sizePaint;
	}
	headnext->next=head;
	head=headnext;
	q=head;
	putimage(q->x,q->y,20,20,snakeHead,0,0,20,20);
	q=q->next;
	while(q->next->next!=NULL)//��ӡ�����壬ʹ����ǰ�������һ��
	{
		putimage(q->x,q->y,20,20,snakeBody,0,0,20,20);
		q=q->next;
	}
	if(head->x==Apple.x && head->y==Apple.y)//�ж��Ƿ�Ե�ʳ��
	{
		snakelen++;//ÿ��һ��ʳ���ߵ����۳��ȼ�1
		getAppleNum++;
		createFood(0);//�����µ�ʳ��
		createObstacle();//�����ϰ���
		if(level==1)
			score=score+10;
		else if(level==2)
			score=score+15;
		else if(level==3)
			score=score+20;
    }
	else if(head->x==Caomei.x && head->y==Caomei.y)//�ж��Ƿ�Ե�ʳ��
	{
		snakelen++;
		getCaomeiNum++;
		createFood(1);//�����µ�ʳ��
		createObstacle();//�����ϰ���
		if(level==1)
			score=score+10;
		else if(level==2)
			score=score+15;
		else if(level==3)
			score=score+20;
    }
	else if(head->x==Yintao.x && head->y==Yintao.y)//�ж��Ƿ�Ե�ʳ��
	{
		snakelen++;
		getYintaoNum++;
		createFood(2);//�����µ�ʳ��
		createObstacle();//�����ϰ���
		if(level==1)
			score=score+10;
		else if(level==2)
			score=score+15;
		else if(level==3)
			score=score+20;
    }
    else
    {
    	putimage(q->x,q->y,20,20,white,0,0,20,20);
		free(q->next);//�������ƶ�֮ǰ��βλ�õĿռ��ͷŵ�
		q->next=NULL;//���ĵ���β�ṹ���nextΪ��  �����Ժ��ҵ���βλ��
	}

	if(level==2)//�ж���Ϸ�ٶ�  ���Ѷ���Ϸ�ٶȲ���
	{
		if(score<=45)
    		speed=100;
    	else if(score<=105)
    		speed=90;
    	else if(score<=180)
    		speed=80;
    	else if(score<=255)
    		speed=70;
    	else if(score<=345)
    		speed=60;
    	else if(score<=465)
    		speed=50;
	}
	else if(level==3)
	{
		if(score<=40)
    		speed=100;
    	else if(score<=100)
    		speed=85;
    	else if(score<=200)
    		speed=70;
    	else if(score<=400)
    		speed=55;
    	else if(score<=600)
    		speed=40;
    	else if(score<=800)
    		speed=25;
	}
}
void snakeStop()//��Ϸ��ͣ
{
	while(1)
    {
        Sleep(300);
        if(GetAsyncKeyState(VK_SPACE))//����ͣʱ���ո�������ͣ״̬
            break;
	}
}

int snakeDie()//�ж����Ƿ�����
{
	int i,flag=1;
	snake *body;
	body=head->next;
	if(head->x==0||head->x==780||head->y==0||head->y==780)//�����߽������
		return 1;
	for(i=0;i<obstacleNum;i++)
	{
		if(head->x==obstacle.x[i]&&head->y==obstacle.y[i])//�ж����Ƿ������ϰ���
		{
			return 1;
		}
	}
	while(body!=NULL)
	{
		if(head->x==body->x&&head->y==body->y)//�ж���ͷ�Ƿ�ײ��������
		{
			return 1;
		}
		body=body->next;
	}

	return 0;
}
void putScore()
{
	speed1=110-speed;//��������ٶ�
	if(level==1)//��ʾ��ͬģʽ��ʳ��ķ�ֵ
		grate=(getAppleNum+getCaomeiNum+getYintaoNum)*10;
	else if(level==2)
		grate=(getAppleNum+getCaomeiNum+getYintaoNum)*15;
	else if(level==3)
		grate=(getAppleNum+getCaomeiNum+getYintaoNum)*20;
	char highestScore[4],playerScore[4],snakeSpeed[2],grates[4],Num1[2],Num2[2],Num3[2];
	sprintf(highestScore,"%2d",record[0].highscore);//������ת�����ַ���
	sprintf(playerScore,"%2d",score);
	sprintf(grates,"%2d",grate);
	sprintf(snakeSpeed,"%d",speed1);
	sprintf(Num1,"%d",getAppleNum);
	sprintf(Num2,"%d",getCaomeiNum);
	sprintf(Num3,"%d",getYintaoNum);
	setbkcolor(EGERGB(240,255,240));
	setcolor(EGERGB(191,293,255));
	setfont(20,0,"����");
	if(level==1)//��ʾ��ͬģʽ��ʳ��ķ�ֵ
		outtextrect(940,193,40,20,"10");
	else if(level==2)
		outtextrect(940,193,40,20,"15");
	else if(level==3)
		outtextrect(940,193,40,20,"20");

	outtextxy(930,280,snakeSpeed);
	outtextxy(900,240,grates);
	outtextxy(960,70,highestScore);
	outtextxy(875,400,Num1);
	outtextxy(875,430,Num2);
	outtextxy(875,460,Num3);
}
void getPaint()
{
	menu=newimage();
	getimage(menu,L"Menu.jpg",0,0);
	difficulty=newimage();
	getimage(difficulty,L"difficulty.jpg");
	fangchenmi=newimage();
	getimage(fangchenmi,L"chenmi.jpg");
	white=newimage();
	getimage(white,L"white.png",0,0);
	help=newimage();
	getimage(help,L"help.jpg",0,0);
	snakeBody=newimage();
	getimage(snakeBody,L"snakeBody.png",0,0);
	snakeHead=newimage();
	getimage(snakeHead,L"snakeHead.png",0,0);
	over=newimage();
	getimage(over,L"over.jpg",0,0);
	reconds=newimage();
	getimage(reconds,L"recond.jpg",0,0);
	paiming=newimage();
	getimage(paiming,L"paiming.jpg",0,0);
	stone=newimage();
	getimage(stone,L"tree.png",0,0);
	caomei=newimage();
	getimage(caomei,L"fanqie.png",0,0);
	yintao=newimage();
	getimage(yintao,L"hanbao.png",0,0);
	apple=newimage();
	getimage(apple,L"apple.jpg",0,0);
	help=newimage();
	getimage(help,L"help.jpg",0,0);
}
void data()//��ʼ��������
{
    grate=0;
	score=0;//��ʼ������Ϊ0
	speed1=0;//��ʼ���ٶ�0
	speed=100;
	snakelen=3;//��ʼ���ߵĳ���Ϊ3��
    direction=0;//��ʼ������ʱ���������ƶ�
    obstacleNum=0;//��ʼ���ϰ���ĸ���Ϊ
    getAppleNum=0;//��ʼ���Ե���ƻ������
    getCaomeiNum=0;//��ʼ���Ե��Ĳ�ݮ����
	getYintaoNum=0;//��ʼ���Ե���ӣ�Ҹ���
}

void recond()
{
	time_t t;
    struct tm * lt;
    time (&t);//��ȡUnixʱ�����
    lt = localtime (&t);//תΪʱ��ṹ��
    //int score = 0;      //��ǰ�Σ���Ϸ�÷�
	int i,j;
    for(i=0;i<10;i++)
    	   record[i].highscore=0;

	  //�洢��߷�
    getHighScore(record);
    for(i=0;i<10;i++)
    {
    	if(score>record[i].highscore)
        {
        	for(j=9;j>i;j--)
        		record[j]=record[j-1];
        	record[i].highscore=score;
        	record[i].year=lt->tm_year+1900;
        	record[i].month=lt->tm_mon;
        	record[i].day=lt->tm_mday;
        	record[i].hour=lt->tm_hour;
        	record[i].minute=lt->tm_min;
        	record[i].second=lt->tm_sec;
        	 strcpy(record[i].name,name);
        	break;
		}
	}
    //���뵱ǰ��߷�
    storeHighScore(record);
}
//����Ѵ˺���д��main�������棬�ǵ���main����ǰ��ĳ�д������Ϻ���������
void getHighScore(struct rec record[10])
{
    FILE * fp = NULL;   //�ļ�ָ�룬ָ��ɹ��򿪵��ļ�
	int i;
    //���ļ�����ֻ���ķ�ʽr
    fp = fopen("highscore.txt","r");

    //����ļ������ڣ����ļ�����д��ķ�ʽw
    if (fp == NULL)
    {
        fp = fopen("highscore.txt","w");
    }
    else
    for(i=0;i<10;i++)
        fscanf(fp,"%5d %4d %4d %4d %4d %4d %4d %10s",&record[i].highscore,&record[i].year,&record[i].month ,&record[i].day ,&record[i].hour ,&record[i].minute ,&record[i].second,record[i].name);

    //�ر��ļ�
    fclose(fp);

}
//����Ѵ˺���д��main�������棬�ǵ���main����ǰ��ĳ�д������Ϻ���������
void storeHighScore(struct rec record[10])
{
    FILE * fp = NULL;
	int i;
    fp = fopen("highscore.txt","w");
    for(i=0;i<10;i++)
    fprintf(fp,"%5d %4d %4d %4d %4d %4d %4d %10s",record[i].highscore,record[i].year,record[i].month ,record[i].day ,record[i].hour ,record[i].minute ,record[i].second,record[i].name);
    fclose(fp);
}
void Ranking(struct rec record[10])
{
	int i;
	char s[100];
  	char k[100];
  	char j[100];
	getbkcolor(paiming);
    setbkmode(TRANSPARENT);
    setbkcolor(getbkcolor(paiming));
    //���ñ�����ɫΪ
    setcolor(RED);
    for(i=0;i<10;i++)
    {
    	sprintf(s, "��%d��    %s", i+1,record[i].name);
    	setfont(20,0,"����");
    	 outtextxy(300,100+50*i,s);
    	 sprintf(j, "%d",record[i].highscore);
    	 outtextxy(500,100+50*i,j);
    	sprintf(k,"%d/%d/%d           %d:%d:%d",record[i].year,record[i].month ,record[i].day ,record[i].hour ,record[i].minute ,record[i].second);
    	setfont(20,0,"����");
    	outtextxy(700,100+50*i,k);
	}
    getch();
}

int fcm()
{
	time_t t;
    struct tm * lt;
    time (&t);//��ȡUnixʱ�����
    lt = localtime (&t);
	FILE * fp = NULL;   //�ļ�ָ�룬ָ��ɹ��򿪵��ļ�
    fp = fopen("chenmi.txt","r");
    //����ļ������ڣ����ļ�����д��ķ�ʽw
    if (fp == NULL)
    {
        fp = fopen("chenmi.txt","w");
    }
    else
        fscanf(fp,"%5d %4d %4d %4d",&chenmi.num,&chenmi.nian,&chenmi.yue ,&chenmi.ri);
    //�ر��ļ�
    if(chenmi.nian!=lt->tm_year+1900||chenmi.yue!=lt->tm_mon||chenmi.ri!=lt->tm_mday)
    {
    	fp = fopen("chenmi.txt","w");
    	chenmi.num=0;
	}
    fclose(fp);
    chenmi.nian=lt->tm_year+1900;
	chenmi.yue=lt->tm_mon;
	chenmi.ri=lt->tm_mday;
    if(chenmi.nian==lt->tm_year+1900&&chenmi.yue==lt->tm_mon&&chenmi.ri==lt->tm_mday)
    	chenmi.num=chenmi.num+1;
    if(chenmi.num<=10)
    {
    	FILE * fp = NULL;
    	fp = fopen("chenmi.txt","w");
    	fprintf(fp,"%5d %4d %4d %4d",chenmi.num,chenmi.nian,chenmi.yue ,chenmi.ri);
    	fclose(fp);
    	return 0;
	}
    else
    	return 1;
}
