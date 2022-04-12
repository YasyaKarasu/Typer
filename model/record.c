#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedlist.h"
#include "record.h"

extern int score, hasexit, showRanking, readTimes, basis, maxbasis;
extern double seconds;
static time_t now;
extern struct tm *tm_now;

Record *NewRecord(int scr, double secs, struct tm *t){//����ָ����������Recordָ�� 
	Record *ptr = (Record*)malloc(sizeof(Record));
	ptr->score = scr;
	ptr->seconds = secs;
	ptr->year = t->tm_year + 1900;
	ptr->mon = t->tm_mon + 1;
	ptr->mday = t->tm_mday;
	ptr->hour = t->tm_hour;
	ptr->min = t->tm_min;
	ptr->sec = t->tm_sec;
	return ptr;
}

void GetCurrentTime(){//��ȡ��ǰʱ�� 
	time(&now);
	tm_now = localtime(&now);
}

void ExitGame(){//������Ϸ��ʾ���а� 
	readTimes = 0;
	GetCurrentTime();
	Record *ptr = NewRecord(score, seconds, tm_now);
	FILE *fp = fopen("RankingList.txt", "a+");
	fprintf(
		fp,
		"date : %d/%02d/%02d %02d:%02d:%02d, score : %d, time : %.1f\n",
		ptr->year,
		ptr->mon,
		ptr->mday,
		ptr->hour,
		ptr->min,
		ptr->sec,
		ptr->score,
		ptr->seconds 
	);//���¼�¼д�����а��ļ� 
	fclose(fp);
	hasexit = 1;
	showRanking = 1;
	basis = 0;
	maxbasis = 2147483647;
}

extern linkedlistADT recordsHead, recordsTail;

int greater(const Record *a, const Record *b){//�Ƚ�������¼�Ĵ�С 
	return ((a->score > b->score) || ((a->score == b->score) && (a->seconds < b->seconds)));
}

linkedlistADT Sort(linkedlistADT h)//����ѡ������ 
{
	linkedlistADT p, q, great;
	Record *tmp;
	for(p = NextNode(h, h); NextNode(h, p) != NULL; p = NextNode(h, p)){
		great = p;
		for(q = NextNode(h, p); q; q = NextNode(h, q))
			if(greater(q->dataptr, great->dataptr))
				great = q;
		if(great != p){
			tmp = p->dataptr;
			p->dataptr = great->dataptr;
			great->dataptr = tmp;
		}
	}
  	return h;
}

void readRecords(){//���ļ��������а��¼ 
	FreeLinkedList(recordsHead);
	recordsHead = NewLinkedList();
	recordsTail = NULL;
	Record *ptr;
	FILE *fp = fopen("RankingList.txt", "r");
	static char s[100],str[10];
	while (!feof(fp)){
		fgets(s, sizeof(s), fp);
		ptr = (Record*)malloc(sizeof(Record));
		int x = sscanf(
			s,
			"%*s %*[:] %d%*[/]%d%*[/]%d %d%*[:]%d%*[:]%d%*[,] %*s %*[:] %d%*[,] %*s %*[:] %lf\n",
			&ptr->year,
			&ptr->mon,
			&ptr->mday,
			&ptr->hour,
			&ptr->min,
			&ptr->sec,
			&ptr->score,
			&ptr->seconds
		);
		recordsTail = InsertNode(recordsHead, recordsTail, ptr);
		fgetc(fp);
	}
	recordsHead = Sort(recordsHead);
	fclose(fp);
}
