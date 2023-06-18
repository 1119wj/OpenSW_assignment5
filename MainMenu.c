#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>
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
int scoreboard[SCOREBOARD__SIZE]; //���ھ��
memory memoryList[MEMORY_SIZE]; //��� ���
void GetKeyboardInput() {
	key = 0;
	key = _getch();
}
void ShowMainMenu() {
	ClearBoard();
	textcolor(WHITE);
	PlaySound(TEXT("���θ޴�.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //�Ҹ����� ������Ʈ ������ ������ �Ҹ� ��
	//SetCurrentCursorPos(startX, startY);
	textcolor(YELLOW);
	puts("                                                     @@          @@");
	puts("                                                  (@@              @@)");
	puts("                    @                 :#            @@@@@@0@@0@@@@@@            #:                 @");
	puts("                   (##@@#:      (#@#<--(@@@@      _-@@            @@-_      @@@@)-->#@#)     :#@@##)");
	puts("                        (@@@@@@@@@         @@@@@@@                    @@@@@@@         @@@@@@@@@)\n");
	textcolor(GRAY);
	puts("                          ����������           ������������      ��������������    ��������������   ");
	puts("                          �� ��������          ������������  ������   ����������������������    ������������������     ");
	puts("                            ������          ��������       ������  ��������           �Ŧ��� ������ �Ŧ���       ");
	puts("                            ������          ������        ������  �Ţ���                ������      ");
	puts("                            ������          ������        ������   �Ţ���������          ������      ");
	puts("                            ������          ������        ������         ������         ������        ");
	puts("                            ������          ������        ������          ������        ������      ");
	puts("                            ������   ����     �Ţ���       ������        ��������        ������     ");
	puts("                          ��������������       �Ţ�������������     ��������������        ������       ");
	puts("                          �Ŧ�����������������������        �Ŧ�������������������      �Ŧ�������������������         �Ŧ�������         ");
	textcolor(YELLOW);
	puts("            @@)               @@                      * HIT & RUN *                     @@               (@@");
	puts("           @     @@         @@@)                                                        (@@@         @@     @");
	puts("          @    _@  @       @          @@@@@@    _____@@#<<(==)>>#@@_____    @@@@@@          @       @  @_    @");
	puts("          (#@@#@       @@@@:@@@@@@@@@@  || @@@@@  | @ << (-==-) >> @ |  @@@@@ ||  @@@@@@@@@@:@@@@       @#@@#)");
	puts("               @@@@@@@@              @@@@@   |  @@@@ --<< (==) >>-- @@@@  |   @@@@@              @@@@@@@@");
	puts("                                      @   @###@@@  @@@@_        _@@@@  @@@###@   @");
	puts("                                                       @-  ()  -@");
	puts("                                                        @------@");
	puts("                                                         @@__@@\n\n\n");
	textcolor(WHITE);
	puts("                                                     1. Game Start \n");
	puts("                                                     2. Scoreboard \n");
	puts("                                                     3. Memory \n");
	puts("                                                     4. How to Play \n");
	puts("                                                     5. Exit \n");

	//�޴� ����
	while (1) {
		GetKeyboardInput();
		switch (key)
		{
		default:
			break;
		case ONE:
			StartGame();
			break;
		case TWO:
			DisplayScoreBoard();
			break;
		case THREE:
			DisplayMemory();
			break;
		case FOUR:
			DisplayGameRule();
			break;
		case FIVE:
			ExitGame();
			break;
		}
	}
}
void StartGame() {
	//������ �ʱ�ȭ
	ClearBoard();
	stage = 1;
	//���� ���� �� ������ �ʱ�ȭ
	initData_Variable();
	initData_SkillEffectInfo();
	initData_SelectedSkill();

	//���̵� �ʱ�ȭ
	initDifficulty(12, 20, 20, 10, 10);

	//HP �ʱ�ȭ
	initHP(5);
	initBossHP(100);

	//�������� ȣ��
	for (int i = 1; i <= 3; i++) {
		//�������� ���� �� ������ �ʱ�ȭ
		initData_Time();
		initData_GameBoardInfo();

		//�������� ����
		StartStage(i);
	}
}