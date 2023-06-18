#pragma once
#define ITEMNUM 2
#define LIFE 21
#define BOMB 22

//������ ����ü
typedef struct Item {
	char shape[3]; //������ ��� ���
	int num; //������ ���� ��ȣ
	int color; //������ ����
} Item;

extern Item itemList[ITEMNUM];

void defineItem();
void UseItem(int num);
int DropItem();
void Bomb(int x, int y);