#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
//헤더 파일
#include "Cursor.h"
#include "KeyInput.h"
#include "GameBoard.h"
#include "PCNPC.h"
#include "Color.h"
#include"GameBoard.h"


//메인 함수
void main() {
	system("mode con cols=180 lines=48"); //콘솔창 크기 지정, 200, 48
	//system("mode con cols=280 lines=47"); //디버그용 크기
	RemoveCursor(); //커서 지우기
	srand((int)time(NULL)); //랜덤 변수 시작

	//EraseGameBoard();
	//UI 출력
	//DrawIngameUI();

	//PC 위치 게임에 추가
	//init_PCPoint();
	SetCurrentCursorPos(GBOARD_ORIGIN_X + PCPoint[0] * 2, GBOARD_ORIGIN_Y + PCPoint[1]);
	drawPC();

	//게임판 그리기
	DrawBoard();
	while (1) {
		ProcessKeyInput();
	}

	//데이터 초기화
	//initMemory();
	//initSkill();
	//initPosUI();
	//defineItem();

	//게임판 중앙 위치
	//center.X = GBOARD_ORIGIN_X + GBOARD_WIDTH;
	//enter.Y = GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 2 - 1;

	//메인 메뉴 호출
	//ShowMainMenu();
}


