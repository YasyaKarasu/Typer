#include <windows.h>
#include <winuser.h>
#include "extgraph.h"
#include "imgui.h"
#include "node.h"

void MouseEventProcess(int x, int y, int button, int event){
	uiGetMouse(x, y, button, event);
}

extern int basis, maxbasis;
void KeyboardEventProcess(int key, int event){
	uiGetKeyboard(key, event);
	if (event == KEY_UP){//左右键调整显示记录 
		if (key == VK_RIGHT)
			basis += basis == maxbasis ? 0 : 5;
		if (key == VK_LEFT)
			basis -= basis == 0 ? 0 : 5;
	}
}

void CharEventProcess(char ch)
{
	uiGetChar(ch);
	display();
}

extern int pauseTag, color;
extern double speed, seconds;
extern Node *p;
extern char alpha[2];
static int lastColor;

void TimerEventProcess(int id){
	switch (id){
		case 0:
			if (pauseTag == 0){
				if (p->y <= 1.5){
					KillNodeptr(p);
					p = RandNewNode();
					memset(alpha, 0, sizeof(alpha));
				}
				else
					p->y -= speed;
			}
			display();
			break;
		case 1:
			color = rand() % 14;
			while (color == lastColor)
				color = rand() % 14;
			lastColor = color;
			break;
		case 2:
			if (pauseTag == 0)
				seconds += 0.1;
			break;
	}
}
