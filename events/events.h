#ifndef _EVENTS_H
#define _EVENTS_H

extern void MouseEventProcess(int x, int y, int button, int event);
extern void KeyboardEventProcess(int key, int event);
extern void TimerEventProcess(int id);
extern void CharEventProcess(char ch);

#endif
