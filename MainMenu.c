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
//헤더 파일
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
int scoreboard[SCOREBOARD__SIZE]; //스코어보드
memory memoryList[MEMORY_SIZE]; //기억 목록
void GetKeyboardInput() {
	key = 0;
	key = _getch();
}
void ShowMainMenu() {
	ClearBoard();
	textcolor(WHITE);
	PlaySound(TEXT("메인메뉴.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //소리파일 프로젝트 폴더에 넣으면 소리 남
	//SetCurrentCursorPos(startX, startY);
	textcolor(YELLOW);
	puts("                                                     @@          @@");
	puts("                                                  (@@              @@)");
	puts("                    @                 :#            @@@@@@0@@0@@@@@@            #:                 @");
	puts("                   (##@@#:      (#@#<--(@@@@      _-@@            @@-_      @@@@)-->#@#)     :#@@##)");
	puts("                        (@@@@@@@@@         @@@@@@@                    @@@@@@@         @@@@@@@@@)\n");
	textcolor(GRAY);
	puts("                          ∏∏∏∏┓           ∏∏∏∏∏┓      ∏∏∏∏∏∏┓    ∏∏∏∏∏∏┓   ");
	puts("                          ┖ ∏∏┌┚          ∏∏┌───  ∏∏┓   ∏∏∏┌──────┚    ∏┌─∏∏┌─∏│     ");
	puts("                            ∏∏│          ∏∏┌┚       ∏∏┓  ∏∏┌┚           ┖─┚ ∏∏│ ┖─┚       ");
	puts("                            ∏∏│          ∏∏│        ∏∏│  ┖∏∏                ∏∏│      ");
	puts("                            ∏∏│          ∏∏│        ∏∏│   ┖∏∏∏∏┓          ∏∏│      ");
	puts("                            ∏∏│          ∏∏│        ∏∏│         ∏∏┓         ∏∏│        ");
	puts("                            ∏∏│          ∏∏│        ∏∏│          ∏∏┓        ∏∏│      ");
	puts("                            ∏∏│   ∏┓     ┖∏∏       ∏∏┚        ∏∏∏│        ∏∏│     ");
	puts("                          ∏∏∏∏∏∏│       ┖∏∏∏∏∏┌┚     ∏∏∏∏∏┌┚        ∏∏│       ");
	puts("                          ┖━━━━━━━━━━━┚        ┖━────────┚      ┖─────────┚         ┖───┚         ");
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

	//메뉴 선택
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
	//게임판 초기화
	ClearBoard();
	stage = 1;
	//게임 시작 전 데이터 초기화
	initData_Variable();
	initData_SkillEffectInfo();
	initData_SelectedSkill();

	//난이도 초기화
	initDifficulty(12, 20, 20, 10, 10);

	//HP 초기화
	initHP(5);
	initBossHP(100);

	//스테이지 호출
	for (int i = 1; i <= 3; i++) {
		//스테이지 시작 전 데이터 초기화
		initData_Time();
		initData_GameBoardInfo();

		//스테이지 시작
		StartStage(i);
	}
}