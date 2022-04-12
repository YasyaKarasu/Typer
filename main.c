#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"
#include "events.h"
#include "node.h"
#include "record.h"

int pauseTag, color, score, showRanking, showHelp, readTimes, basis, maxbasis = 2147483647, hasexit;
double speed = 0.05, windowWidth, windowHeight;
double boxY, fontHeight[61], seconds;
char alpha[2];
char *presetColor[]={
	"Black",
	"Dark Gray",
	"Gray",
	"Light Gray",
	"White",
	"Brown",
	"Red",
	"Orange",
	"Yellow",
	"Green",
	"Blue",
	"Violet",
	"Magenta",
	"Cyan"
};//预设颜色 
struct tm *tm_now;//本地时间 
Node *p;
linkedlistADT recordsHead, recordsTail;

void InitFontSize();

void drawHelp();
void drawRankingList();
void drawMenulist();
void drawScorePad();
void drawFallBox();
void drawButton();
void drawTextbox();

void display(){
	DisplayClear();
	if (showHelp){//显示帮助 
		SetPenColor(presetColor[0]);
		drawHelp();
		if (button(GenUIID(0), windowWidth / 2 - 1, 1, 2, 1, "Back"))
			showHelp = 0;
		return;
	}
	if (showRanking){//显示排行榜 
		if (!readTimes)
			readRecords();
		readTimes++;
		drawRankingList();
		SetPenColor(presetColor[6]);
		SetPointSize(25);
		static char hint[45] = "Press Left/Right key to see more records!";
		drawLabel(windowWidth / 2 - TextStringWidth(hint) / 2, 2.5, hint);
		if (button(GenUIID(0), windowWidth / 2 - 1, 1, 2, 1, hasexit ? "Exit" : "Back"))
			if (hasexit)
				exit(0);
			else
				showRanking = 0;
		return;
	}
	drawMenulist();//显示游戏界面 
	drawScorePad();
	drawFallBox();
	drawButton();
	drawTextbox();
}

void Main(){
	srand(time(0));
	SetWindowTitle("Typer");
	SetWindowSize(12.0, 8.0);
	
	InitGraphics();
	
	windowWidth = GetWindowWidth();
	windowHeight = GetWindowHeight();
	
	InitFontSize();
	
	p = RandNewNode();
	pauseTag = 1;

	registerTimerEvent(TimerEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	startTimer(0, 16);//掉落字母刷新timer 
	startTimer(1, 10000);//字母区边框变色timer 
	startTimer(2, 100);//玩家游戏时间timer 
	
	SetFont("Consolas");//设置字体为Consolas 
	
	display();	
}

void InitFontSize(){//预处理fontHeight数组 
	for (int i=1;i<=60;i++){
		SetPointSize(i);
		fontHeight[i] = GetFontHeight();
	}
	return;
}

void drawHelp(){
	SetPointSize(25);
	double fH = fontHeight[25];
	drawLabel(0.5, windowHeight - 1 - fH * 1.5, "This game is called Typer.");
	drawLabel(0.5, windowHeight - 1 - fH * 3, "When the focus is on the textbox,");
	drawLabel(0.5, windowHeight - 1 - fH * 4.5, "you can type in the character falling in the screen to get score.");
	drawLabel(0.5, windowHeight - 1 - fH * 6, "When you click on the exit button,");
	drawLabel(0.5, windowHeight - 1 - fH * 7.5, "your score and your game time will be recorded in RankingList.txt.");
	drawLabel(0.5, windowHeight - 1 - fH * 9, "Have fun!");
}

void drawRankingList(){
	static int fontColorIndex;
	SetPointSize(30);
	SetPenColor(presetColor[0]);
	double dy = windowHeight - 3;
	dy /= 5;//每页显示5条记录，通过左右键显示更多 
	for (int i=1;i<=5;i++){
		static char str[100];
		Record *tmp = ithNodeobj(recordsHead, i + basis);
		if (tmp != NULL)
			sprintf(
				str,
				"%d . date : %d/%02d/%02d %02d:%02d:%02d, score : %d, time : %.1f",
				i + basis,
				tmp->year,
				tmp->mon,
				tmp->mday,
				tmp->hour,
				tmp->min,
				tmp->sec,
				tmp->score,
				tmp->seconds
			);
		else{
			memset(str, 0, sizeof(str));
			maxbasis = basis;
		}
		if (
			hasexit
			&& tmp
			&& tmp->year == tm_now->tm_year + 1900
			&& tmp->mon == tm_now->tm_mon + 1
			&& tmp->mday == tm_now->tm_mday
			&& tmp->hour == tm_now->tm_hour
			&& tmp->min == tm_now->tm_min
			&& tmp->sec == tm_now->tm_sec
		)//退出时高亮最新记录 
			fontColorIndex = 7;
		else
			fontColorIndex = 0;
		SetPenColor(presetColor[0]);
		drawBox(0, windowHeight - i * dy, windowWidth, dy, 0, str, 'M', presetColor[fontColorIndex]);
	}
}

void drawMenulist(){
	SetPenSize(1);
	SetPointSize(20);
	
	static char *MenulistSetting[] = {"Setting",
		"Start",
		"Pause",
		"Speed UP | Ctrl-U",
		"Speed DOWN | Ctrl-D",
		"Exit | Ctrl-E"
	};
	static char *MenulistAbout[] = {"About",
		"Help | Ctrl-H",
		"Ranking List | Ctrl-R"
	};
	static char * selectedLabel = NULL;
	
	double fH = fontHeight[20];
	double x = 0;
	double y = windowHeight;
	double h = fH * 1.5;
	double w = TextStringWidth(MenulistSetting[0]) * 2;
	double wlist = TextStringWidth(MenulistAbout[2]) * 1.2;
	int    selection;
	
	drawMenuBar(0,y-h,windowWidth,h);
	
	selection = menuList(
		GenUIID(0),
		x,
		y - h,
		w,
		wlist,
		h,
		MenulistSetting,
		sizeof(MenulistSetting) / sizeof(MenulistSetting[0])
	);
	switch (selection){
		case 1:
			pauseTag = 0;
			break;
		case 2:
			pauseTag = 1;
			break;
		case 3:
			speed *= 2;
			break;
		case 4:
			speed /= 2;
			break;
		case 5:
			ExitGame();
			break;
	}
	
	selection = menuList(
		GenUIID(0),
		x + w,
		y - h,
		w,
		wlist,
		h,
		MenulistAbout,
		sizeof(MenulistAbout) / sizeof(MenulistAbout[0])
	);
	if (selection == 1)
		showHelp = pauseTag = 1;
	if (selection == 2)
		showRanking = pauseTag = 1;
}

void drawScorePad(){
	char *str = (char*)malloc(100);
	memset(str, 0, 100);
	sprintf(str, "SCORE : %d", score);
	SetPenColor(presetColor[0]);
	SetPointSize(50);
	drawLabel(windowWidth / 2 - TextStringWidth(str) / 2, boxY + 0.5, str);
}

void drawFallBox(){
	double fH = fontHeight[20];
	double h = fH * 1.5;
	boxY = windowHeight - h - 1.1;
	SetPenSize(2);
	SetPenColor(presetColor[color]);
	SetPointSize(50);
	drawRectangle(0, 1.5, windowWidth, boxY - 1.5, 0);
	SetPenColor(presetColor[0]);
	drawLabel(p->x, p->y, p->c);
}

void drawButton(){
	SetPointSize(30);
	double w = windowWidth / 5;
	double h = fontHeight[30] * 1.5;
	static char *buttonLabel[] = {
		"Start",
		"Pause",
		"Speed UP",
		"Speed DOWN",
		"Exit"
	};
	
	for (int i=0; i<5; i++){
		if (button(GenUIID(i), i * w, 0, w, h, buttonLabel[i]))
			switch (i){
			case 0:
				pauseTag = 0;
				break;
			case 1:
				pauseTag = 1;
				break;
			case 2:
				speed *= 2;
				break;
			case 3:
				speed /= 2;
				break;
			case 4:
				ExitGame();
				break;
		}
	}
}

void drawTextbox(){
	SetPointSize(30);
	SetPenSize(2);
	double fH = GetFontHeight();
	double h = fH*2;
	double w = TextStringWidth("W") * 3;
	
	if (textbox(
		GenUIID(0),
		windowWidth / 2 - w / 2,
		fontHeight[30] * 3,
		w,
		fontHeight[20] * 1.5,
		alpha,
		sizeof(alpha)
	))
		if (strcmp(alpha, p->c) == 0){
			score ++;
			KillNodeptr(p);
			p = RandNewNode();
			memset(alpha, 0, sizeof(alpha));
		}
}
