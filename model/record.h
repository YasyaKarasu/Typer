#ifndef _RECORD_H
#define _RECORD_H

typedef struct _record{
	int score;
	double seconds;
	int year, mon, mday, hour, min, sec;
}Record;

Record *NewRecord(int scr, double secs, struct tm *t);
void GetCurrentTime();
void ExitGame();
void readRecords();

#endif
