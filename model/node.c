#include "node.h"
#include "extgraph.h"
extern double windowWidth, windowHeight, boxY;

Node *NewNode(char c, double x, double y){//根据指定参数返回Node指针 
	Node *ptr = (Node*)malloc(sizeof(Node));
	char *ctr = (char*)malloc(2);
	memset(ctr, 0, 2);
	*ctr = c;
	ptr->c = ctr;
	ptr->x = x;
	ptr->y = y;
	return ptr;
}

Node *RandNewNode(){//返回一个参数随机的Node指针 
	return NewNode(
		(char)(rand() % 26 + 'A'),
		rand() % (int)(windowWidth - 1) + ((double)(rand() % 100)) / 100.0,
		boxY - GetFontHeight()
	);
}

void KillNodeptr(Node *ptr){//释放Node指针的内存 
	free(ptr);
}
