#include "node.h"
#include "extgraph.h"
extern double windowWidth, windowHeight, boxY;

Node *NewNode(char c, double x, double y){//����ָ����������Nodeָ�� 
	Node *ptr = (Node*)malloc(sizeof(Node));
	char *ctr = (char*)malloc(2);
	memset(ctr, 0, 2);
	*ctr = c;
	ptr->c = ctr;
	ptr->x = x;
	ptr->y = y;
	return ptr;
}

Node *RandNewNode(){//����һ�����������Nodeָ�� 
	return NewNode(
		(char)(rand() % 26 + 'A'),
		rand() % (int)(windowWidth - 1) + ((double)(rand() % 100)) / 100.0,
		boxY - GetFontHeight()
	);
}

void KillNodeptr(Node *ptr){//�ͷ�Nodeָ����ڴ� 
	free(ptr);
}
