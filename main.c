#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
//��� ����
#include "Cursor.h"
#include "KeyInput.h"
#include "GameBoard.h"
#include "PCNPC.h"
#include "Color.h"
#include "MainMenu.h"
#include "Skill.h"
#include "Stage.h"
#include "InitGameData.h"
#include "ItemData.h"
#include "Boss.h"

//�Լ�
//void FindKeyboardValue(); //Ű���� �Է°� ã��

//���� �Լ�
void main() {
	system("mode con cols=180 lines=48"); //�ܼ�â ũ�� ����, 200, 48
	//system("mode con cols=280 lines=47"); //����׿� ũ��
	RemoveCursor(); //Ŀ�� �����
	srand((int)time(NULL)); //���� ���� ����

	//Ű���� �ڵ� Ȯ��
	//FindKeyboardValue();
	//������ �߾� ��ġ
	center.X = GBOARD_ORIGIN_X + GBOARD_WIDTH;
	center.Y = GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 2 - 1;
	//������ �ʱ�ȭ
	initMemory();
	initSkill();
	initPosUI();
	defineItem();

	//���� �޴� ȣ��
	ShowMainMenu();
}

//��Ÿ �Լ�
void FindKeyboardValue() {
	while (1) {
		GetKeyboardInput();
		printf("%d", key);
	}
}

