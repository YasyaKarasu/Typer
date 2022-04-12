#ifndef _NODE_H
#define _NODE_H

typedef struct _Node{
	char *c;
	double x, y;
}Node;

extern Node *NewNode(char c, double x, double y);
extern Node *RandNewNode();
extern void KillNodeptr(Node *ptr);

#endif
