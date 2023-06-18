#pragma once
#include <stdbool.h>
#define SCOREBOARD__SIZE 10 //���ھ�� ũ��
#define MEMORY_SIZE 20 //��� ��� ũ��
#define MEMORY_LEN 100 //��� ���ڿ� ����

typedef struct memory {
	char locked[MEMORY_LEN]; //��� ���: �ر� ����
	char unlocked[MEMORY_LEN]; //�رݵ� ���
	bool check; //����� �رݵǾ����� üũ: TRUE=�ر�, FALSE=���ر�
} memory;

extern int scoreboard[SCOREBOARD__SIZE]; //���ھ��
extern memory memoryList[MEMORY_SIZE]; //��� ���

void GetKeyboardInput(); //Ű���� �Է¹޴� �Լ�
void ShowMainMenu(); //���� �޴� ���
void StartGame(); //1. ���� ����; ������ �����Ӹ� ����
void DisplayScoreBoard(); //2. ���ھ��
void DisplayMemory(); //3. ��� ���; �����Ӹ� ����
void DisplayGameRule(); //4. ���� ���; �����Ӹ� ����
void ExitGame(); //5. ���� ����