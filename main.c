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
#include"GameBoard.h"


//���� �Լ�
void main() {
	system("mode con cols=180 lines=48"); //�ܼ�â ũ�� ����, 200, 48
	//system("mode con cols=280 lines=47"); //����׿� ũ��
	RemoveCursor(); //Ŀ�� �����
	srand((int)time(NULL)); //���� ���� ����

	//EraseGameBoard();
	//UI ���
	//DrawIngameUI();

	//PC ��ġ ���ӿ� �߰�
	//init_PCPoint();
	SetCurrentCursorPos(GBOARD_ORIGIN_X + PCPoint[0] * 2, GBOARD_ORIGIN_Y + PCPoint[1]);
	drawPC();

	//������ �׸���
	DrawBoard();
	while (1) {
		ProcessKeyInput();
	}

	//������ �ʱ�ȭ
	//initMemory();
	//initSkill();
	//initPosUI();
	//defineItem();

	//������ �߾� ��ġ
	//center.X = GBOARD_ORIGIN_X + GBOARD_WIDTH;
	//enter.Y = GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 2 - 1;

	//���� �޴� ȣ��
	//ShowMainMenu();
}


