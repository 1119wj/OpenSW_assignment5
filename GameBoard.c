#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include "GameBoard.h"
#include "Color.h"
#include "PCNPC.h"
#include "KeyInput.h"
#include "Cursor.h"
#include"Stage.h"

int GameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 1];
int score = 0;
int finalScore = 0;
int HP = 5;
int maxHP = 5;
int stage = 0;
COORD pos_time;
COORD pos_stage;
COORD pos_score;
COORD pos_hp;
COORD pos_skillList;
COORD pos_skillSelect;
COORD cursor;
COORD center;
int maxExpScore;


void DrawBoard() {
    int x, y;

    textcolor(WHITE);
    textcolor(YELLOW);

    //상단
    for (x = 1; x < GBOARD_WIDTH; x++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y);
        printf("■");
        GameBoardInfo[0][x] = 1;

    }

    //하단
    for (x = 1; x < GBOARD_WIDTH * 2; x++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
        printf("■");
        GameBoardInfo[GBOARD_HEIGHT][x] = 1;
    }

    //우변
    for (y = 0; y <= GBOARD_HEIGHT; y++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2, GBOARD_ORIGIN_Y + y);
        if (y == 0) printf("■");
        else if (y == GBOARD_HEIGHT) printf("■");
        else printf("■");
        GameBoardInfo[y][GBOARD_WIDTH] = 1;
    }

    //좌변
    for (y = 0; y <= GBOARD_HEIGHT; y++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
        if (y == 0) printf("■");
        else if (y == GBOARD_HEIGHT) printf("■");
        else printf("■");
        GameBoardInfo[y][0] = 1;

    }
    //알림창
    //상단
    for (x = 1; x < GBOARD_WIDTH * 2; x++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x, GBOARD_ORIGIN_Y + GBOARD_HEIGHT + 1);
        printf("─");
    }

    //우변
    for (y = GBOARD_HEIGHT + 1; y <= GBOARD_HEIGHT + 3; y++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2, GBOARD_ORIGIN_Y + y);
        if (y == GBOARD_HEIGHT + 1) printf("┐");
        else if (y == GBOARD_HEIGHT + 3) printf("┘");
        else printf("│");
    }

    //좌변
    for (y = GBOARD_HEIGHT + 1; y <= GBOARD_HEIGHT + 3; y++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
        if (y == GBOARD_HEIGHT + 1) printf("┌");
        else if (y == GBOARD_HEIGHT + 3) printf("└");
        else printf("│");
    }

    //하단
    for (x = 1; x < GBOARD_WIDTH * 2; x++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x, GBOARD_ORIGIN_Y + GBOARD_HEIGHT + 3);
        printf("─");
    }
}

//보드 전부 지우기
void ClearBoard() {
    system("cls"); //콘솔창 전부 지우는 명령어
}
//게임판 영역 지우기; 스테이지 표시 지우기용
void ClearGameBoard() {
    int x, y;
    for (y = 1; y < GBOARD_HEIGHT; y++) {
        for (x = 1; x < GBOARD_WIDTH; x++) {
            if (GameBoardInfo[y][x] == 0) {
                SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
                printf("  ");
            }
        }
    }
}
void EraseGameBoard() {
    //각종 npc 및 투사체 제거하고 스코어 복구
    finalScore = score;
    //AllDie();
    score = finalScore;

    //pc 제거
    if (stage == 2 || stage == 3) {
        erasePC();
    }

    //스킬 제거
    /*for (int i = 0; i <= skillTop; i++) {
        GameBoardInfo[skillEffectInfo[i].Y][skillEffectInfo[i].X] = 0;
        SetCurrentCursorPos(GBOARD_ORIGIN_X + skillEffectInfo[i].X * 2, GBOARD_ORIGIN_Y + skillEffectInfo[i].Y);
        printf("  ");
    }
    skillTop = -1;
    */
    //아이템 등 나머지 제거
    for (int y = 1; y < GBOARD_HEIGHT; y++) {
        for (int x = 1; x < GBOARD_WIDTH; x++) {
            if (GameBoardInfo[y][x] != 0) {
                GameBoardInfo[y][x] = 0;
                SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
                printf("  ");
            }
        }
    }
}
//PC 그리기
void drawPC() {
    textcolor(WHITE);
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            GameBoardInfo[PCPoint[1] + y][PCPoint[0] + x] = PC;
            SetCurrentCursorPos((PCPoint[0] + x) * 2 + GBOARD_ORIGIN_X, (PCPoint[1] + y) + GBOARD_ORIGIN_Y);

            switch (lastDir)
            {
            case EAST:
                if (x == 1 && y == 1) textcolor(RED), printf("▶");
                else if (x == 1 && y == 0) textcolor(WHITE), printf("▶");
                else textcolor(YELLOW), printf("■");
                break;
            case WEST:
                if (x == 0 && y == 0) textcolor(RED), printf("◀");
                else if (x == 0 && y == 1) textcolor(WHITE), printf("◀");
                else textcolor(YELLOW), printf("■");
                break;
            case NORTH:
                if (y == 0 && x == 1) textcolor(RED), printf("▲");
                else if (y == 0 && x == 0) textcolor(WHITE), printf("▲");
                else textcolor(YELLOW), printf("■");
                break;
            case SOUTH:
                if (y == 1 && x == 0) textcolor(RED), printf("▼");
                else if (y == 1 && x == 1) textcolor(WHITE), printf("▼");
                else textcolor(YELLOW), printf("■");
                break;
                break;
            }
        }
    }
}

//PC 지우기
void erasePC() {
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            GameBoardInfo[PCPoint[1] + y][PCPoint[0] + x] = 0;
            SetCurrentCursorPos((PCPoint[0] + x) * 2 + GBOARD_ORIGIN_X, (PCPoint[1] + y) + GBOARD_ORIGIN_Y);
            printf("  ");
        }
    }
}
//시간 표시
void drawTime() {
    SetCurrentCursorPos(pos_time.X, pos_time.Y);
    textcolor(WHITE);
    printf("▶ 남은 시간 : %-4d", (STAGETIME - (TimeCount % STAGETIME)) / 6);
}
//NPC 그리기
void drawNpcShape() {
    textcolor(darkGREEN);
    printf("●");
}
