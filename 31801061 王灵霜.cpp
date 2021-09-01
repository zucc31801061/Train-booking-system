#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
struct node
{
	int i;
	struct node *next;
};
struct train//������Ϣ�ṹ�� 
{
	char trainNO[10];//�𳵱��
	char start[11]; //��ʼվ
	char terminus[11];//�յ�վ 
	int total;//��Ʊ�� 
	int stationsNum;//ͣ��վ��
	int date;//���� 
}; 
struct stationInfo//����ͣ��վ����ṹ�� 
{
	int num;//ͣ��վ���
	char name[11];//ͣ��վ
	int arrivetime;//����ʱ��
	int leavetime;//����ʱ��
	char interval[10];//ͣ��ʱ�� 
	double price;//��Ʊ�۸� 
	struct stationInfo *next;
};
struct Train//�������δ洢�ṹ�� 
{
	char trainNO[10];//�𳵱��
	char start[11];//��ʼվ
	char terminus[11];//�յ�վ
	int total;//��Ʊ��
	int stationsNum;//ͣ��վ�� 
	int date;//���� 
	struct stationInfo *SI;
	struct node *Day;
};
struct bookticket//��Ʊ��Ϣ�ṹ�� 
{
	int date;//����
	char trainNO[10];//�𳵱��
	char start[11];//��ʼվ
	char terminus[11];//�յ�վ
	char name[11];//����
	char num[18];//���֤ 
};
struct appointment//ԤԼ�˿���Ϣ�ṹ�� 
{
	char trainNO[10];//�𳵱��
	int date;//����
	char name[11];//����
	int num;//��Ʊ�� 
};
int main()
{
	int answer;
	int i, j;
	FILE *fp1, *fp2, *fp3; 
	struct train a;
	struct stationInfo b;
	struct stationInfo *front, *rear, *p;//����ָ�붨�� 
	struct Train A[10];//�½��洢�ṹ���� 
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
    day = o->tm_mday;//��ȡ��ǰ�·�����,��Χ��1-31
    month = 1+o->tm_mon;//��ȡ��ǰ�·�,��Χ��0-11,����Ҫ��1
    today = month * 100 + day;
	
	fp1 = fopen("��������.txt","r");
	if(fp1 == NULL)//�����ĵ� 
	{
		printf("File Open Error");//���File Open Error
		exit (0);
	}
	while(!feof(fp1))
	{
		fscanf(fp1,"%s %s %s %d %d %d", a.trainNO, a.start, a.terminus, &a.total, &a.stationsNum, &a.date);
		//�洢������Ϣ 
		strcpy(A[Cnt1].trainNO, a.trainNO);
		strcpy(A[Cnt1].start, a.start);
		strcpy(A[Cnt1].terminus, a.terminus);
		A[Cnt1].total = a.total;
		A[Cnt1].stationsNum = a.stationsNum;
		A[Cnt1].date = a.date;
		//��ʼ��ָ�� 
		A[Cnt1].SI = NULL;
		A[Cnt1].Day = NULL;
		Cnt1++;
		front = rear = NULL;
		for(i=0; i<a.stationsNum; i++)
		{
			p = (struct stationInfo *)malloc(sizeof(struct stationInfo));//��������̬�洢�ռ� 
			fscanf(fp1,"%d %s %d:%d %d:%d %s %lf", &p->num, p->name, &h1, &m1, &h2, &m2, p->interval, &p->price);//��ȡͣ��վ������Ϣ 
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
	
	fp2 = fopen("�Ѷ�Ʊ.txt","r");
	while(!feof(fp2))
	{
		fscanf(fp2,"%d %s %s %s %s %s", &c.date, c.trainNO, c.start, c.terminus, c.name, c.num);
		//�洢������Ϣ 
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

	fp3 = fopen("ԤԼ.txt","r");
	while(!feof(fp3))
	{
		fscanf(fp3,"%s %d %s %d", d.trainNO, &d.date, d.name, &d.num);
		//�洢ԤԼ�˿���Ϣ 
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
	printf("������%04d\n",today);
	printf("1.��ѯ����\n2.�а충Ʊҵ��\n3.�а���Ʊҵ��\n"); 
	printf("����������Ҫ�а��ҵ��:");
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
			printf("����Ҫ��ѯ�ĳ��εĳ���վ�͵���վ��");
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
				printf("δ��ѯ�������Ϣ\n"); 
				break;
			}
			printf("������������Ҫ���ε��г���ţ�"); 
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
			printf("������Ҫ��Ʊ�ĳ��γ���վ�͵���վ��");
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
				printf("δ��ѯ�������Ϣ\n"); 
				break;
			}
			printf("������������Ҫ��Ҫ��Ʊ�ĳ����г���ţ�"); 
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
			printf("������������Ҫ��ѯ�����ڣ�");
			int datee;
			scanf("%d",&datee); 
			if(strcmp(trainNO1,A[0].trainNO) == 0 && datee == A[0].date)
			{
				printf("%s���г�ʣ��%d��Ʊ\n",A[0].trainNO,x);
				if(x == 0)
				{
					answer1 = 0; 
					printf("����Ʊ���Ƿ�Ҫ����Ԥ�����У�\n1.��    2.��\n");
					scanf("%d",&answer1);
					if(answer1 == 1)
					{
						printf("������Ԥ���г����ڡ���������������Ԥ����Ʊ��\n");
						scanf("%d %s %d", &C[Cnt3].date, C[Cnt3].name, &C[Cnt3].num);
						strcpy(C[Cnt3].trainNO, trainNO1);
						fp3 = fopen("ԤԼ.txt","w");
						for(i = 0; i <= Cnt3; i++)
						{
							if(i != Cnt3 - 1)
								fprintf(fp3, "%s %d %s %d\n", C[i].trainNO, C[i].date, C[i].name, C[i].num);	
						}
						fclose(fp3);
						printf("��ԤԼ�ɹ�\n"); 
					}
					else
					{
						printf("��Ϊ��ȡ������\n");
					}
				}
				else if(x>0)
				{
					printf("����������Ҫ����·�ε���ʼվ���յ�վ��");
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
					printf("����Ҫ֧��%.1lfԪ\n",finalprice);
					printf("ȷ��֧����\n1.ȷ�ϲ����복�����ڡ����������֤��    2.ȡ��֧��\n");
					scanf("%d",&answer2);
					if(answer2 == 1)
					{
						scanf("%d %s %s", &B[Cnt2-1].date, B[Cnt2-1].name, B[Cnt2-1].num);
						if(B[Cnt2-1].date == A[0].date)
						x--;
						strcpy(B[Cnt2-1].trainNO, trainNO1);
						strcpy(B[Cnt2-1].start, startstation);
						strcpy(B[Cnt2-1].terminus, endstation);
						fp2 = fopen("�Ѷ�Ʊ.txt","w");
						for(i = 0; i < Cnt2; i++)
						{
							fprintf(fp2,"%d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
						}
						fclose(fp2);
						printf("֧���ɹ�\n");
					}
					else
					{
						printf("��ȡ��֧��\n");
					}
				}
				
			}
		    if(y>0 &&datee !=905){
		    	printf("%s���г�ʣ��%d��Ʊ\n",A[0].trainNO,y);
					printf("����������Ҫ����·�ε���ʼվ���յ�վ��");
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
					printf("����Ҫ֧��%.1lfԪ\n",finalprice);
					printf("ȷ��֧����\n1.ȷ�ϲ����복�����ڡ����������֤��    2.ȡ��֧��\n");
					scanf("%d",&answer2);
					if(answer2 == 1)
					{
						scanf("%d %s %s", &B[Cnt2-1].date, B[Cnt2-1].name, B[Cnt2-1].num);
						if(B[Cnt2-1].date == A[0].date)
						x--;
						strcpy(B[Cnt2-1].trainNO, trainNO1);
						strcpy(B[Cnt2-1].start, startstation);
						strcpy(B[Cnt2-1].terminus, endstation);
						fp2 = fopen("�Ѷ�Ʊ.txt","w");
						for(i = 0; i < Cnt2; i++)
						{
							fprintf(fp2,"%d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
						}
						fclose(fp2);
						printf("֧���ɹ�\n");
					}
					else
					{
						printf("��ȡ��֧��\n");
					}
				}
			else if(strcmp(trainNO1,A[2].trainNO) == 0)
			{ 
				answer1 = 0; 
				printf("%s���г�ʣ��%d��Ʊ\n",A[2].trainNO,y);
				if(y == 0)
				{
					answer1 = 0; 
					printf("����Ʊ���Ƿ�Ҫ����Ԥ�����У�\n1.��    2.��\n");
					scanf("%d",&answer1);
					if(answer1 == 1)
					{
						printf("������Ԥ���г����ڡ���������������Ԥ����Ʊ��\n");
						scanf("%d %s %d", &C[Cnt3].date, C[Cnt3].name, &C[Cnt3].num);
						strcpy(C[Cnt3].trainNO, trainNO1);
						fp3 = fopen("ԤԼ.txt","w");
						for(i = 0; i <= Cnt3; i++)
						{
							if(i != Cnt3 - 1)
								fprintf(fp3, "%s %d %s %d\n", C[i].trainNO, C[i].date, C[i].name, C[i].num);	
						}
						fclose(fp3);
						printf("��ԤԼ�ɹ�\n"); 
					}
					else
					{
						printf("��Ϊ��ȡ������\n");
					}
				}
				else
				{
					printf("����������Ҫ����·�ε���ʼվ���յ�վ��");
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
					printf("����Ҫ֧��%.1lfԪ\n",finalprice);
					printf("ȷ��֧����\n1.ȷ�ϲ����복�����ڡ����������֤��    2.ȡ��֧��\n");
					scanf("%d",&answer2);
					if(answer2 == 1)
					{
						scanf("%d %s %s", &B[Cnt2-1].date, B[Cnt2-1].name, B[Cnt2-1].num);
						strcpy(B[Cnt2-1].trainNO, trainNO1);
						strcpy(B[Cnt2-1].start, startstation);
						strcpy(B[Cnt2-1].terminus, endstation);
						fp2 = fopen("�Ѷ�Ʊ.txt","w");
						for(i = 0; i < Cnt2; i++)
						{
							fprintf(fp2,"%d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
						}
						fclose(fp2);
						printf("֧���ɹ�\n");
						y--;
					}
					else
					{
						printf("��ȡ��֧��\n");
					}
				}
			}
			else if(strcmp(trainNO1,A[4].trainNO) == 0)
			{
				answer1 = 0; 
				printf("%s���г�ʣ��%d��Ʊ\n",A[4].trainNO,z);
				if(z == 0)
				{
					answer1 = 0; 
					printf("����Ʊ���Ƿ�Ҫ����Ԥ�����У�\n1.��    2.��\n");
					scanf("%d",&answer1);
					if(answer1 == 1)
					{
						printf("������Ԥ���г����ڡ���������������Ԥ����Ʊ��\n");
						scanf("%d %s %d", &C[Cnt3].date, C[Cnt3].name, &C[Cnt3].num);
						strcpy(C[Cnt3].trainNO, trainNO1);
						fp3 = fopen("ԤԼ.txt","w");
						for(i = 0; i <= Cnt3; i++)
						{
							if(i != Cnt3 - 1)
								fprintf(fp3, "%s %d %s %d\n", C[i].trainNO, C[i].date, C[i].name, C[i].num);	
						}
						fclose(fp3);
						printf("��ԤԼ�ɹ�\n"); 
					}
					else
					{
						printf("��Ϊ��ȡ������\n");
					}
				}
				else
				{
					printf("����������Ҫ����·�ε���ʼվ���յ�վ��");
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
					printf("����Ҫ֧��%.1lfԪ\n",finalprice);
					printf("ȷ��֧����\n1.ȷ�ϲ����복�����ڡ����������֤��    2.ȡ��֧��\n");
					scanf("%d",&answer2);
					if(answer2 == 1)
					{
						scanf("%d %s %s", &B[Cnt2-1].date, B[Cnt2-1].name, B[Cnt2-1].num);
						strcpy(B[Cnt2-1].trainNO, trainNO1);
						strcpy(B[Cnt2-1].start, startstation);
						strcpy(B[Cnt2-1].terminus, endstation);
						fp2 = fopen("�Ѷ�Ʊ.txt","w");
						for(i = 0; i < Cnt2; i++)
						{
							fprintf(fp2,"%d %s %s %s %s %s\n", B[i].date, B[i].trainNO, B[i].start, B[i].terminus, B[i].name, B[i].num);
						}
						fclose(fp2);
						z--; 
						printf("֧���ɹ�\n");
					}
					else
					{
						printf("��ȡ��֧��\n");
					}
				}
			}
			printf("�Ƿ��ѯ��Ʊ������\n1.��    2.��\n");
			scanf("%d",&answer3);
			if(answer3 == 1)
			{
				printf("������Ҫ��ѯ�ı�ţ�");
				char numno1[10];
				scanf("%s",numno1) ;
				printf("������Ҫ��ѯ�����ڣ�");
				int date1;
				scanf("%d",&date1);
				Cnt2 = 0;
				fp2 = fopen("�Ѷ�Ʊ.txt","r");
					while(!feof(fp2))
					{
						fscanf(fp2,"%d %s %s %s %s %s", &c.date, c.trainNO, c.start, c.terminus, c.name, c.num);
						//�洢������Ϣ 
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
			printf("�Ƿ��ѯԤԼ������\n1.��    2.��\n");
			scanf("%d",&answer5);
			if(answer5 == 1){
				printf("������Ҫ��ѯ�ı�ţ�");
				char numno2[10];
				scanf("%s",numno2) ;
				printf("������Ҫ��ѯ�����ڣ�");
				int date2;
				scanf("%d",&date2);
				Cnt3 = 0; 
				fp3 = fopen("ԤԼ.txt","r");
				while(!feof(fp3))
				{
					fscanf(fp3,"%s %d %s %d", d.trainNO, &d.date, d.name, &d.num);
					//�洢ԤԼ�˿���Ϣ 
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
			printf("�������������֤�ź��Ѷ�Ʊ���Σ�");
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
				printf("δ�ҵ������Ϣ\n");
				break;
			}
			x1 = i;
			printf("ȷ����Ʊ?\n1.ȷ��    2.ȡ��\n");
			scanf("%d",&answer4);
			if(answer4 == 1)
			{
				fp2 = fopen("�Ѷ�Ʊ.txt","w");
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
				printf("��Ʊ�ɹ�\n");
				x++;
			}
			else
			{
				printf("��ȡ����Ʊ\n");
			}

			printf("�Ƿ��ѯ��Ʊ������\n1.��    2.��\n");
			scanf("%d",&answer3);
			if(answer3 == 1)
			{
				printf("������Ҫ��ѯ�ı�ţ�");
				char numno3[10];
				scanf("%s",numno3) ;
				printf("������Ҫ��ѯ�����ڣ�");
				int date3;
				scanf("%d",&date3);
				Cnt2 = 0;
				fp2 = fopen("�Ѷ�Ʊ.txt","r");
					while(!feof(fp2))
					{
						fscanf(fp2,"%d %s %s %s %s %s", &c.date, c.trainNO, c.start, c.terminus, c.name, c.num);
						//�洢������Ϣ 
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
					printf("%s����0905�п�����ɾ��ԤԼ\n",A[0].trainNO);
					tag = 0; 
					fp3 = fopen("ԤԼ.txt","r");
					Cnt3 = 0;
					while(!feof(fp3))
					{
						fscanf(fp3,"%s %d %s %d", d.trainNO, &d.date, d.name, &d.num);
						//�洢ԤԼ�˿���Ϣ 
						strcpy(C[Cnt3].trainNO, d.trainNO);
						C[Cnt3].date = d.date;
						strcpy(C[Cnt3].name, d.name);
						C[Cnt3].num = d.num;
						Cnt3++;
					}
					fclose(fp3);
					fp3 = fopen("ԤԼ.txt","w");
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
					printf("%s����0906�п�����ɾ��ԤԼ\n",A[0].trainNO);
					tag = 0; 
					fp3 = fopen("ԤԼ.txt","r");
					Cnt3 = 0;
					while(!feof(fp3))
					{
						fscanf(fp3,"%s %d %s %d", d.trainNO, &d.date, d.name, &d.num);
						//�洢ԤԼ�˿���Ϣ 
						strcpy(C[Cnt3].trainNO, d.trainNO);
						C[Cnt3].date = d.date;
						strcpy(C[Cnt3].name, d.name);
						C[Cnt3].num = d.num;
						Cnt3++;
					}
					fclose(fp3);
					fp3 = fopen("ԤԼ.txt","w");
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
					printf("%s�����п�����ɾ��ԤԼ\n",A[4].trainNO);
					tag = 0; 
					fp3 = fopen("ԤԼ.txt","r");
					Cnt3 = 0;
					while(!feof(fp3))
					{
						fscanf(fp3,"%s %d %s %d", d.trainNO, &d.date, d.name, &d.num);
						//�洢ԤԼ�˿���Ϣ 
						strcpy(C[Cnt3].trainNO, d.trainNO);
						C[Cnt3].date = d.date;
						strcpy(C[Cnt3].name, d.name);
						C[Cnt3].num = d.num;
						Cnt3++;
					}
					fclose(fp3);
					fp3 = fopen("ԤԼ.txt","w");
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
			printf("�Ƿ��ѯԤԼ������\n1.��    2.��\n");
			scanf("%d",&answer5);
			if(answer5 == 1){
				printf("������Ҫ��ѯ�ı�ţ�");
				char numno4[10];
				scanf("%s",numno4) ;
				printf("������Ҫ��ѯ�����ڣ�");
				int date4;
				scanf("%d",&date4);
				Cnt3 = 0; 
				fp3 = fopen("ԤԼ.txt","r");
				while(!feof(fp3))
				{
					fscanf(fp3,"%s %d %s %d", d.trainNO, &d.date, d.name, &d.num);
					//�洢ԤԼ�˿���Ϣ 
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
        printf("������������������\n");
        break;
	}
		printf("����������Ҫ�а��ҵ��:"); 
		scanf("%d",&answer);
	}
	return 0;
}

