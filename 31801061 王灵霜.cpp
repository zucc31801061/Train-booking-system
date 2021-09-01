#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
struct node
{
	int i;
	struct node *next;
};
struct train//车次信息结构体 
{
	char trainNO[10];//火车编号
	char start[11]; //起始站
	char terminus[11];//终点站 
	int total;//总票数 
	int stationsNum;//停靠站数
	int date;//日期 
}; 
struct stationInfo//车次停靠站链表结构体 
{
	int num;//停靠站编号
	char name[11];//停靠站
	int arrivetime;//到达时间
	int leavetime;//出发时间
	char interval[10];//停靠时间 
	double price;//车票价格 
	struct stationInfo *next;
};
struct Train//高铁车次存储结构体 
{
	char trainNO[10];//火车编号
	char start[11];//起始站
	char terminus[11];//终点站
	int total;//总票数
	int stationsNum;//停靠站数 
	int date;//日期 
	struct stationInfo *SI;
	struct node *Day;
};
struct bookticket//订票信息结构体 
{
	int date;//日期
	char trainNO[10];//火车编号
	char start[11];//起始站
	char terminus[11];//终点站
	char name[11];//姓名
	char num[18];//身份证 
};
struct appointment//预约乘客信息结构体 
{
	char trainNO[10];//火车编号
	int date;//日期
	char name[11];//姓名
	int num;//订票数 
};
int main()
{
	int answer;
	int i, j;
	FILE *fp1, *fp2, *fp3; 
	struct train a;
	struct stationInfo b;
	struct stationInfo *front, *rear, *p;//链表指针定义 
	struct Train A[10];//新建存储结构数组 
	struct bookticket B[60];
	struct bookticket c;
	struct appointment C[60];
	struct appointment d;
	int h1, m1, h2, m2;
	int Cnt1 = 0, Cnt2 = 0, Cnt3 = 0;
	char trainnum[10];
	int x = 0, y = 0, z = 0;
	
	time_t timep;
    struct tm *o;
    int today, month, day;
    time (&timep);
    o=gmtime(&timep);
    day = o->tm_mday;//获取当前月份日数,范围是1-31
    month = 1+o->tm_mon;//获取当前月份,范围是0-11,所以要加1
    today = month * 100 + day;
	
	fp1 = fopen("高铁车次.txt","r");
	if(fp1 == NULL)//若无文档 
	{
		printf("File Open Error");//输出File Open Error
		exit (0);
	}
	while(!feof(fp1))
	{
		fscanf(fp1,"%s %s %s %d %d %d", a.trainNO, a.start, a.terminus, &a.total, &a.stationsNum, &a.date);
		//存储车次信息 
		strcpy(A[Cnt1].trainNO, a.trainNO);
		strcpy(A[Cnt1].start, a.start);
		strcpy(A[Cnt1].terminus, a.terminus);
		A[Cnt1].total = a.total;
		A[Cnt1].stationsNum = a.stationsNum;
		A[Cnt1].date = a.date;
		//初始化指针 
		A[Cnt1].SI = NULL;
		A[Cnt1].Day = NULL;
		Cnt1++;
		front = rear = NULL;
		for(i=0; i<a.stationsNum; i++)
		{
			p = (struct stationInfo *)malloc(sizeof(struct stationInfo));//申请链表动态存储空间 
			fscanf(fp1,"%d %s %d:%d %d:%d %s %lf", &p->num, p->name, &h1, &m1, &h2, &m2, p->interval, &p->price);//读取停靠站车次信息 
			p->arrivetime = h1 * 100 + m1;
			p->leavetime = h2 * 100 + m2;
			if(front == NULL)
			{
				front = p;
			}
			else
			{
				rear->next = p;
			}
			rear = p;
		}
		rear->next = NULL;
		A[Cnt1].SI = front;
		Cnt1++;
	}
/*	
	for(int i = 0; i < Cnt1; i++)
	{
		if(A[i].trainNO[0] == 'G')
		{
			printf("%s %s %s %d %d\n", A[i].trainNO, A[i].start, A[i].terminus, A[i].total, A[i].stationsNum);
		}
		p = A[i].SI;
		while(p)
		{
			printf("%02d\t%s\t%04d\t%04d\t%s\t%.1lf\n", p->num, p->name, p->arrivetime, p->leavetime, p->interval, p->price);
			p = p->next;
		}
	}
*/
	fclose(fp1);
	
	fp2 = fopen("已定票.txt","r");
	while(!feof(fp2))
	{
		fscanf(fp2,"%d %s %s %s %s %s", &c.date, c.trainNO, c.start, c.terminus, c.name, c.num);
		//存储车次信息 
		B[Cnt2].date = c.date;
		strcpy(B[Cnt2].trainNO, c.trainNO);
		strcpy(B[Cnt2].start, c.start);
		strcpy(B[Cnt2].terminus, c.terminus);
		strcpy(B[Cnt2].name, c.name);
		strcpy(B[Cnt2].num, c.num);
		Cnt2++;
	}
	for(i = 0; i < Cnt2-1; i++){
		if(strcmp(B[i].trainNO, A[0].trainNO) == 0 && B[i].date == A[0].date)
				x++;
		else if(strcmp(B[i].trainNO, A[0].trainNO) == 0)
				y++;
		else if(strcmp(B[i].trainNO, A[2].trainNO) == 0)
				z++;
	}
	x = A[0].total - x;
	y = A[2].total - y;
	z = A[4].total - z;
/*
	for(int i = 0; i < Cnt2-1; i++)
	{

		printf("%d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
	}
*/
	fclose(fp2);

	fp3 = fopen("预约.txt","r");
	while(!feof(fp3))
	{
		fscanf(fp3,"%s %d %s %d", d.trainNO, &d.date, d.name, &d.num);
		//存储预约乘客信息 
		strcpy(C[Cnt3].trainNO, d.trainNO);
		C[Cnt3].date = d.date;
		strcpy(C[Cnt3].name, d.name);
		C[Cnt3].num = d.num;
		Cnt3++;
	}
/*
	for(int i = 0; i < Cnt3 - 1; i++)
	{
		printf("%s %d %s %d\n", C[i].trainNO, C[i].date, C[i].name, C[i].num);
	}
*/
	fclose(fp3);
	printf("今天是%04d\n",today);
	printf("1.查询车次\n2.承办订票业务\n3.承办退票业务\n"); 
	printf("请输入您所要承办的业务:");
	scanf("%d", &answer);
	while(answer){
	switch(answer)
	{
		case 1:
			char station1[11];
			char station2[11];
			char trainNO[10];
			int i, flag;
			flag = 0;
			printf("您所要查询的车次的出发站和到达站：");
			scanf("%s %s",station1, station2);
			for(i = 0; i < Cnt1; i++){
				if((strcmp(station1,A[i].start) == 0)&& (strcmp(station2,A[i].terminus) == 0))
				{
					if(A[i].trainNO[0] == 'G' && A[i].date >= today)
					{
						printf("%s %s %s %d %d %04d\n", A[i].trainNO, A[i].start, A[i].terminus, A[i].total, A[i].stationsNum, A[i].date);
					}
					flag = 1;
				}
			}
			if(!flag && i == Cnt1)
			{
				printf("未查询到相关信息\n"); 
				break;
			}
			printf("请输入您所需要车次的列车编号："); 
			scanf("%s",trainNO);
			for(i = 0; i < Cnt1; i++){
				if(strcmp(trainNO,A[i].trainNO) == 0)
				{
					if(A[i].trainNO[0] == 'G')
					{
						printf("%s %s %s %d %d %04d\n", A[i].trainNO, A[i].start, A[i].terminus, A[i].total, A[i].stationsNum, A[i].date);
					}
					int j = i + 1;
					p = A[j].SI;
					while(p)
					{
						printf("%02d\t%s\t%04d\t%04d\t%s\t%.1lf\n", p->num, p->name, p->arrivetime, p->leavetime, p->interval, p->price);
						p = p->next;
					}
				}
			}
			break;
		case 2:
			char station3[11];
			char station4[11];
			char trainNO1[10];
			char startstation[11];
			char endstation[11];
			int answer1; 
			int answer2;
			int answer3;
			int answer5;
			double price1;
			double price2;
			double finalprice;
			int flag1;
			
			flag1 = 0;
			printf("您所需要车票的车次出发站和到达站：");
			scanf("%s %s",station3, station4);
			for(i = 0; i < Cnt1; i++){
				if((strcmp(station3,A[i].start) == 0)|| (strcmp(station4,A[i].terminus) == 0))
				{
					if(A[i].trainNO[0] == 'G' && A[i].date >= today)
					{
						printf("%s %s %s %d %d %04d\n", A[i].trainNO, A[i].start, A[i].terminus, A[i].total, A[i].stationsNum, A[i].date);
					}
					flag1 = 1;
				}
			}
			if(!flag1 && i == Cnt1)
			{
				printf("未查询到相关信息\n"); 
				break;
			}
			printf("请输入您所需要需要车票的车次列车编号："); 
			scanf("%s",trainNO1);
			for(i = 0; i < Cnt1; i++){
				if(strcmp(trainNO1,A[i].trainNO) == 0)
				{
					if(A[i].trainNO[0] == 'G')
					{
						printf("%s %s %s %d %d %04d\n", A[i].trainNO, A[i].start, A[i].terminus, A[i].total, A[i].stationsNum, A[i].date);
					}
					int j = i + 1;
					p = A[j].SI;
					while(p)
					{
						printf("%02d\t%s\t%04d\t%04d\t%s\t%.1lf\n", p->num, p->name, p->arrivetime, p->leavetime, p->interval, p->price);
						p = p->next;
					}
				}
			}
			printf("请输入您所需要查询的日期：");
			int datee;
			scanf("%d",&datee); 
			if(strcmp(trainNO1,A[0].trainNO) == 0 && datee == A[0].date)
			{
				printf("%s次列车剩余%d张票\n",A[0].trainNO,x);
				if(x == 0)
				{
					answer1 = 0; 
					printf("已无票，是否要加入预订行列？\n1.是    2.否\n");
					scanf("%d",&answer1);
					if(answer1 == 1)
					{
						printf("请输入预订列车日期、您的姓名和所需预订的票数\n");
						scanf("%d %s %d", &C[Cnt3].date, C[Cnt3].name, &C[Cnt3].num);
						strcpy(C[Cnt3].trainNO, trainNO1);
						fp3 = fopen("预约.txt","w");
						for(i = 0; i <= Cnt3; i++)
						{
							if(i != Cnt3 - 1)
								fprintf(fp3, "%s %d %s %d\n", C[i].trainNO, C[i].date, C[i].name, C[i].num);	
						}
						fclose(fp3);
						printf("已预约成功\n"); 
					}
					else
					{
						printf("已为您取消服务\n");
					}
				}
				else if(x>0)
				{
					printf("请输入您所要购买路段的起始站和终点站：");
					scanf("%s %s", startstation, endstation);
					p = A[1].SI;
					while(p)
					{
						if(strcmp(startstation, p->name) == 0)
						{
							price1 = p->price;
						}
						else if(strcmp(endstation, p->name) == 0)
						{
							price2 = p->price;
							break;
						}
						p = p->next;
					}
					finalprice = price2 - price1;
					printf("您需要支付%.1lf元\n",finalprice);
					printf("确认支付？\n1.确认并输入车次日期、姓名和身份证号    2.取消支付\n");
					scanf("%d",&answer2);
					if(answer2 == 1)
					{
						scanf("%d %s %s", &B[Cnt2-1].date, B[Cnt2-1].name, B[Cnt2-1].num);
						if(B[Cnt2-1].date == A[0].date)
						x--;
						strcpy(B[Cnt2-1].trainNO, trainNO1);
						strcpy(B[Cnt2-1].start, startstation);
						strcpy(B[Cnt2-1].terminus, endstation);
						fp2 = fopen("已定票.txt","w");
						for(i = 0; i < Cnt2; i++)
						{
							fprintf(fp2,"%d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
						}
						fclose(fp2);
						printf("支付成功\n");
					}
					else
					{
						printf("已取消支付\n");
					}
				}
				
			}
		    if(y>0 &&datee !=905){
		    	printf("%s次列车剩余%d张票\n",A[0].trainNO,y);
					printf("请输入您所要购买路段的起始站和终点站：");
					scanf("%s %s", startstation, endstation);
					p = A[1].SI;
					while(p)
					{
						if(strcmp(startstation, p->name) == 0)
						{
							price1 = p->price;
						}
						else if(strcmp(endstation, p->name) == 0)
						{
							price2 = p->price;
							break;
						}
						p = p->next;
					}
					finalprice = price2 - price1;
					printf("您需要支付%.1lf元\n",finalprice);
					printf("确认支付？\n1.确认并输入车次日期、姓名和身份证号    2.取消支付\n");
					scanf("%d",&answer2);
					if(answer2 == 1)
					{
						scanf("%d %s %s", &B[Cnt2-1].date, B[Cnt2-1].name, B[Cnt2-1].num);
						if(B[Cnt2-1].date == A[0].date)
						x--;
						strcpy(B[Cnt2-1].trainNO, trainNO1);
						strcpy(B[Cnt2-1].start, startstation);
						strcpy(B[Cnt2-1].terminus, endstation);
						fp2 = fopen("已定票.txt","w");
						for(i = 0; i < Cnt2; i++)
						{
							fprintf(fp2,"%d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
						}
						fclose(fp2);
						printf("支付成功\n");
					}
					else
					{
						printf("已取消支付\n");
					}
				}
			else if(strcmp(trainNO1,A[2].trainNO) == 0)
			{ 
				answer1 = 0; 
				printf("%s次列车剩余%d张票\n",A[2].trainNO,y);
				if(y == 0)
				{
					answer1 = 0; 
					printf("已无票，是否要加入预订行列？\n1.是    2.否\n");
					scanf("%d",&answer1);
					if(answer1 == 1)
					{
						printf("请输入预订列车日期、您的姓名和所需预订的票数\n");
						scanf("%d %s %d", &C[Cnt3].date, C[Cnt3].name, &C[Cnt3].num);
						strcpy(C[Cnt3].trainNO, trainNO1);
						fp3 = fopen("预约.txt","w");
						for(i = 0; i <= Cnt3; i++)
						{
							if(i != Cnt3 - 1)
								fprintf(fp3, "%s %d %s %d\n", C[i].trainNO, C[i].date, C[i].name, C[i].num);	
						}
						fclose(fp3);
						printf("已预约成功\n"); 
					}
					else
					{
						printf("已为您取消服务\n");
					}
				}
				else
				{
					printf("请输入您所要购买路段的起始站和终点站：");
					scanf("%s %s", startstation, endstation);
					p = A[3].SI;
					while(p)
					{
						if(strcmp(startstation, p->name) == 0)
						{
							price1 = p->price;
						}
						else if(strcmp(endstation, p->name) == 0)
						{
							price2 = p->price;
							break;
						}
						p = p->next;
					}
					finalprice = price2 - price1;
					printf("您需要支付%.1lf元\n",finalprice);
					printf("确认支付？\n1.确认并输入车次日期、姓名和身份证号    2.取消支付\n");
					scanf("%d",&answer2);
					if(answer2 == 1)
					{
						scanf("%d %s %s", &B[Cnt2-1].date, B[Cnt2-1].name, B[Cnt2-1].num);
						strcpy(B[Cnt2-1].trainNO, trainNO1);
						strcpy(B[Cnt2-1].start, startstation);
						strcpy(B[Cnt2-1].terminus, endstation);
						fp2 = fopen("已定票.txt","w");
						for(i = 0; i < Cnt2; i++)
						{
							fprintf(fp2,"%d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
						}
						fclose(fp2);
						printf("支付成功\n");
						y--;
					}
					else
					{
						printf("已取消支付\n");
					}
				}
			}
			else if(strcmp(trainNO1,A[4].trainNO) == 0)
			{
				answer1 = 0; 
				printf("%s次列车剩余%d张票\n",A[4].trainNO,z);
				if(z == 0)
				{
					answer1 = 0; 
					printf("已无票，是否要加入预订行列？\n1.是    2.否\n");
					scanf("%d",&answer1);
					if(answer1 == 1)
					{
						printf("请输入预订列车日期、您的姓名和所需预订的票数\n");
						scanf("%d %s %d", &C[Cnt3].date, C[Cnt3].name, &C[Cnt3].num);
						strcpy(C[Cnt3].trainNO, trainNO1);
						fp3 = fopen("预约.txt","w");
						for(i = 0; i <= Cnt3; i++)
						{
							if(i != Cnt3 - 1)
								fprintf(fp3, "%s %d %s %d\n", C[i].trainNO, C[i].date, C[i].name, C[i].num);	
						}
						fclose(fp3);
						printf("已预约成功\n"); 
					}
					else
					{
						printf("已为您取消服务\n");
					}
				}
				else
				{
					printf("请输入您所要购买路段的起始站和终点站：");
					scanf("%s %s", startstation, endstation);
					p = A[5].SI;
					while(p)
					{
						if(strcmp(startstation, p->name) == 0)
						{
							price1 = p->price;
						}
						else if(strcmp(endstation, p->name) == 0)
						{
							price2 = p->price;
							break;
						}
						p = p->next;
					}
					finalprice = price2 - price1;
					printf("您需要支付%.1lf元\n",finalprice);
					printf("确认支付？\n1.确认并输入车次日期、姓名和身份证号    2.取消支付\n");
					scanf("%d",&answer2);
					if(answer2 == 1)
					{
						scanf("%d %s %s", &B[Cnt2-1].date, B[Cnt2-1].name, B[Cnt2-1].num);
						strcpy(B[Cnt2-1].trainNO, trainNO1);
						strcpy(B[Cnt2-1].start, startstation);
						strcpy(B[Cnt2-1].terminus, endstation);
						fp2 = fopen("已定票.txt","w");
						for(i = 0; i < Cnt2; i++)
						{
							fprintf(fp2,"%d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
						}
						fclose(fp2);
						z--; 
						printf("支付成功\n");
					}
					else
					{
						printf("已取消支付\n");
					}
				}
			}
			printf("是否查询订票名单？\n1.是    2.否\n");
			scanf("%d",&answer3);
			if(answer3 == 1)
			{
				printf("请输入要查询的编号：");
				char numno1[10];
				scanf("%s",numno1) ;
				printf("请输入要查询的日期：");
				int date1;
				scanf("%d",&date1);
				Cnt2 = 0;
				fp2 = fopen("已定票.txt","r");
					while(!feof(fp2))
					{
						fscanf(fp2,"%d %s %s %s %s %s", &c.date, c.trainNO, c.start, c.terminus, c.name, c.num);
						//存储车次信息 
						B[Cnt2].date = c.date;
						strcpy(B[Cnt2].trainNO, c.trainNO);
						strcpy(B[Cnt2].start, c.start);
						strcpy(B[Cnt2].terminus, c.terminus);
						strcpy(B[Cnt2].name, c.name);
						strcpy(B[Cnt2].num, c.num);
						Cnt2++;
					}

				for(int i = 0; i < Cnt2-1; i++)
				{
					if((strcmp(numno1,B[i].trainNO) == 0) && (date1 == B[i].date))
						printf("%04d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
				}

				fclose(fp2);
			}
			printf("是否查询预约名单？\n1.是    2.否\n");
			scanf("%d",&answer5);
			if(answer5 == 1){
				printf("请输入要查询的编号：");
				char numno2[10];
				scanf("%s",numno2) ;
				printf("请输入要查询的日期：");
				int date2;
				scanf("%d",&date2);
				Cnt3 = 0; 
				fp3 = fopen("预约.txt","r");
				while(!feof(fp3))
				{
					fscanf(fp3,"%s %d %s %d", d.trainNO, &d.date, d.name, &d.num);
					//存储预约乘客信息 
					strcpy(C[Cnt3].trainNO, d.trainNO);
					C[Cnt3].date = d.date;
					strcpy(C[Cnt3].name, d.name);
					C[Cnt3].num = d.num;
					Cnt3++;
				}

				for(int i = 0; i < Cnt3 - 1; i++)
				{
					if((strcmp(numno2,B[i].trainNO) == 0) && date2 == C[i].date)
						printf("%s %04d %s %d\n", C[i].trainNO, C[i].date, C[i].name, C[i].num);
				}

			fclose(fp3);
			}
			break;
		case 3:
			char IDnum[18];
			char trainnumb[10]; 
			int answer4, answer6; 
			int x1, y1;
			printf("请输入您的身份证号和已订票车次：");
			scanf("%s %s",IDnum, trainnumb);
			y1 = 0; 
			for(i = 0; i < Cnt2-1; i++)
			{
				if((strcmp(IDnum, B[i].num) == 0) && (strcmp(trainnumb, B[i].trainNO) == 0))
				{
					printf("%d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
					y1 = 1;
					break;
				}
			}
			if((i == Cnt2-1) && y1 == 0)
			{
				printf("未找到相关信息\n");
				break;
			}
			x1 = i;
			printf("确认退票?\n1.确认    2.取消\n");
			scanf("%d",&answer4);
			if(answer4 == 1)
			{
				fp2 = fopen("已定票.txt","w");
				for(i = 0; i < Cnt2-1; i++)
				{
					if(i == x1)
					{
						continue;
					}
					else
						fprintf(fp2,"%d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
				}
				fclose(fp2);
				printf("退票成功\n");
				x++;
			}
			else
			{
				printf("已取消退票\n");
			}

			printf("是否查询订票名单？\n1.是    2.否\n");
			scanf("%d",&answer3);
			if(answer3 == 1)
			{
				printf("请输入要查询的编号：");
				char numno3[10];
				scanf("%s",numno3) ;
				printf("请输入要查询的日期：");
				int date3;
				scanf("%d",&date3);
				Cnt2 = 0;
				fp2 = fopen("已定票.txt","r");
					while(!feof(fp2))
					{
						fscanf(fp2,"%d %s %s %s %s %s", &c.date, c.trainNO, c.start, c.terminus, c.name, c.num);
						//存储车次信息 
						B[Cnt2].date = c.date;
						strcpy(B[Cnt2].trainNO, c.trainNO);
						strcpy(B[Cnt2].start, c.start);
						strcpy(B[Cnt2].terminus, c.terminus);
						strcpy(B[Cnt2].name, c.name);
						strcpy(B[Cnt2].num, c.num);
						Cnt2++;
					}
				for(int i = 0; i < Cnt2-1; i++)
				{
					if((strcmp(numno3,B[i].trainNO) == 0) && date3 == B[i].date)
						printf("%04d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
				}

				fclose(fp2);
			}
			
			int tag;
			if(strcmp(B[i].trainNO,A[0].trainNO) == 0){
				if(x > 0){
					printf("%s车次0905有空余已删除预约\n",A[0].trainNO);
					tag = 0; 
					fp3 = fopen("预约.txt","r");
					Cnt3 = 0;
					while(!feof(fp3))
					{
						fscanf(fp3,"%s %d %s %d", d.trainNO, &d.date, d.name, &d.num);
						//存储预约乘客信息 
						strcpy(C[Cnt3].trainNO, d.trainNO);
						C[Cnt3].date = d.date;
						strcpy(C[Cnt3].name, d.name);
						C[Cnt3].num = d.num;
						Cnt3++;
					}
					fclose(fp3);
					fp3 = fopen("预约.txt","w");
					for(int i = 0; i < Cnt3 - 1; i++)
					{
						if(strcmp(C[i].trainNO, A[0].trainNO) == 0 && tag < x &&C[i].date ==905)
						{
						tag ++;
						continue;
						}
						else
							fprintf(fp3,"%s %04d %s %d\n", C[i].trainNO, C[i].date, C[i].name, C[i].num);
					}
					fclose(fp3);
					x--;
				}
			}
			else if(strcmp(B[i].trainNO,A[0].trainNO) == 0){
				if(y > 0){
					printf("%s车次0906有空余已删除预约\n",A[0].trainNO);
					tag = 0; 
					fp3 = fopen("预约.txt","r");
					Cnt3 = 0;
					while(!feof(fp3))
					{
						fscanf(fp3,"%s %d %s %d", d.trainNO, &d.date, d.name, &d.num);
						//存储预约乘客信息 
						strcpy(C[Cnt3].trainNO, d.trainNO);
						C[Cnt3].date = d.date;
						strcpy(C[Cnt3].name, d.name);
						C[Cnt3].num = d.num;
						Cnt3++;
					}
					fclose(fp3);
					fp3 = fopen("预约.txt","w");
					for(int i = 0; i < Cnt3 - 1; i++)
					{
						if(strcmp(C[i].trainNO, A[0].trainNO) == 0 && tag < y &&C[i].date == 906)
						{
							tag ++;
							continue;
						}
					else
						fprintf(fp3,"%s %04d %s %d\n", C[i].trainNO, C[i].date, C[i].name, C[i].num);
					}
					fclose(fp3);
					y--;
				}
			}
			if(strcmp(B[i].trainNO,A[6].trainNO) == 0){
				if(z > 0){
					printf("%s车次有空余已删除预约\n",A[4].trainNO);
					tag = 0; 
					fp3 = fopen("预约.txt","r");
					Cnt3 = 0;
					while(!feof(fp3))
					{
						fscanf(fp3,"%s %d %s %d", d.trainNO, &d.date, d.name, &d.num);
						//存储预约乘客信息 
						strcpy(C[Cnt3].trainNO, d.trainNO);
						C[Cnt3].date = d.date;
						strcpy(C[Cnt3].name, d.name);
						C[Cnt3].num = d.num;
						Cnt3++;
					}
					fclose(fp3);
					fp3 = fopen("预约.txt","w");
					for(int i = 0; i < Cnt3 - 1; i++)
					{
						if(strcmp(C[i].trainNO, A[2].trainNO) == 0 && tag < z)
						{
							tag ++;
							continue;
						}
						else
							fprintf(fp3,"%s %04d %s %d\n", C[i].trainNO, C[i].date, C[i].name, C[i].num);
					}
					fclose(fp3);
					z--;
				}
			}
			printf("是否查询预约名单？\n1.是    2.否\n");
			scanf("%d",&answer5);
			if(answer5 == 1){
				printf("请输入要查询的编号：");
				char numno4[10];
				scanf("%s",numno4) ;
				printf("请输入要查询的日期：");
				int date4;
				scanf("%d",&date4);
				Cnt3 = 0; 
				fp3 = fopen("预约.txt","r");
				while(!feof(fp3))
				{
					fscanf(fp3,"%s %d %s %d", d.trainNO, &d.date, d.name, &d.num);
					//存储预约乘客信息 
					strcpy(C[Cnt3].trainNO, d.trainNO);
					C[Cnt3].date = d.date;
					strcpy(C[Cnt3].name, d.name);
					C[Cnt3].num = d.num;
					Cnt3++;
				}

				for(int i = 0; i < Cnt3 - 1; i++)
				{
					if((strcmp(numno4,B[i].trainNO) == 0) && date4 == C[i].date)
						printf("%s %04d %s %d\n", C[i].trainNO, C[i].date, C[i].name, C[i].num);
				}

			fclose(fp3);
			}
			break;
		default:
        printf("您的输入有误，请重输\n");
        break;
	}
		printf("请输入您所要承办的业务:"); 
		scanf("%d",&answer);
	}
	return 0;
}

