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
#include "MainMenu.h"
#include "Skill.h"
#include "Stage.h"
#include "InitGameData.h"
#include "ItemData.h"
#include "Boss.h"

//보스 좌표
int BossPoint[2] = { 17,6 };

//보스 모델 7
int BossModel[7][7] = {
  { 0, BossNum, BossNum, BossNum, BossNum, BossNum, 0  },
  { BossNum, BossNum, BossNum, BossNum, BossNum, BossNum, BossNum  },
  { BossNum, BossNum, BossNum, BossNum, BossNum, BossNum, BossNum  },
  { BossNum ,BossNum, BossNum, BossNum, BossNum, BossNum, BossNum  },
  { BossNum, BossNum, BossNum, BossNum, BossNum, BossNum, BossNum  },
  { BossNum, BossNum, 0, 0, 0, BossNum, BossNum  },
  { 0, BossNum, BossNum, BossNum, BossNum, BossNum, 0  },
};

//보스 스킬 6
int BossSkillModel[3][3] = {
    {BossSkillEffect,BossSkillEffect,BossSkillEffect},
    {BossSkillEffect,BossSkillEffect,BossSkillEffect},
    {BossSkillEffect,BossSkillEffect,BossSkillEffect},
};

int BossHP;
int BossMaxHP;
int bossFlag = 0;
int x3 = 1, y3 = 1;
int random = 5;
int TimeCount2 = 0;
int XX1, YY1, XX2, YY2; //보스모델의 왼쪽위 ,오른쪽아래 좌표

void ShowBoss() {
    for (int y = 0; y < 7; y++) {
        for (int x = 0; x < 7; x++) {
            SetCurrentCursorPos(BossPoint[0] * 2 + GBOARD_ORIGIN_X + x * 2, BossPoint[1] + GBOARD_ORIGIN_Y + y);
            if (BossModel[y][x] == BossNum) {
                GameBoardInfo[BossPoint[1] + y][BossPoint[0] + x] = BossNum;
                if (y == 2 && (x == 1 || x == 5)) {
                    textcolor(RED);
                    //printf("●");
                }
                else if (y == 3 && x == 3) {
                    textcolor(GREEN);
                    //  printf("▲");
                }
                else {
                    if (random == 1) {
                        if (x == 0) {
                            textcolor(BLUE);
                            printf("■");
                        }
                        else {
                            textcolor(darkGRAY);
                            printf("■");
                        }
                    }
                    else if (random == 2) {
                        if (y == 0) {
                            textcolor(BLUE);
                            printf("■");
                        }
                        else {
                            textcolor(darkGRAY);
                            printf("■");
                        }
                    }
                    else if (random == 3) {
                        if (x == 6) {
                            textcolor(BLUE);
                            printf("■");
                        }
                        else {
                            textcolor(darkGRAY);
                            printf("■");
                        }
                    }
                    else if (random == 4) {
                        if (y == 6) {
                            textcolor(BLUE);
                            printf("■");
                        }
                        else {
                            textcolor(darkGRAY);
                            printf("■");
                        }
                    }
                    else {
                        textcolor(darkGRAY);
                        printf("■");
                    }
                }
            }
        }
    }
}

void DeleteBoss() {
    for (int y = 0; y < 7; y++) {
        for (int x = 0; x < 7; x++) {
            SetCurrentCursorPos(BossPoint[0] * 2 + GBOARD_ORIGIN_X + x * 2, BossPoint[1] + GBOARD_ORIGIN_Y + y);
            if (BossModel[y][x] == BossNum) {
                printf("  ");
                GameBoardInfo[BossPoint[1] + y][BossPoint[0] + x] = 0;
            }
        }
    }
}
void ShowBossSkill_Circle() {                //스킬궤도 왼쪽위 좌표 (BossX-5,BossY-5)
    int X, Y;
    int TC = ((TimeCount - 1) % 5) * 3;         //움직임 구현

    textcolor(darkYELLOW); //색상 설정
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            SetCurrentCursorPos(GBOARD_ORIGIN_X + (BossPoint[0] - 5 + TC + x) * 2, GBOARD_ORIGIN_Y + BossPoint[1] - 5 + y);
            if (BossSkillModel[y][x] == BossSkillEffect) {
                X = BossPoint[0] - 5 + TC + x;
                Y = BossPoint[1] - 5 + y;
                if ((X >= 1 && X < GBOARD_WIDTH) && (Y >= 1 && Y < GBOARD_HEIGHT)) {
                    if (GameBoardInfo[Y][X] == PC) {
                        //pc 충돌 시 보스 스킬 삭제 및 pc hp 감소
                        DecreaseHP();
                    }
                    else if (GameBoardInfo[Y][X] > 100) {
                        //pc 스킬 충돌 시 보스 스킬 및 pc 스킬 삭제
                        for (int idx = 0; idx <= skillTop; idx++) {
                            if (skillEffectInfo[idx].X == X && skillEffectInfo[idx].Y == Y) {
                                RemoveSkillEffect(idx);
                                break;
                            }
                        }
                    }
                    else {
                        //나머지 경우 보스 스킬 저장 및 그리기
                        GameBoardInfo[Y][X] = BossSkillEffect;
                        printf("□");
                    }
                }
            }
        }
    }
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            SetCurrentCursorPos(GBOARD_ORIGIN_X + (BossPoint[0] + 9 + x) * 2, GBOARD_ORIGIN_Y + BossPoint[1] - 5 + y + TC);
            if (BossSkillModel[y][x] == BossSkillEffect) {
                X = BossPoint[0] + 9 + x;
                Y = BossPoint[1] - 5 + y + TC;
                if ((X >= 1 && X < GBOARD_WIDTH) && (Y >= 1 && Y < GBOARD_HEIGHT)) {
                    if (GameBoardInfo[Y][X] == PC) {
                        //pc 충돌 시 보스 스킬 삭제 및 pc hp 감소
                        DecreaseHP();
                    }
                    else if (GameBoardInfo[Y][X] > 100) {
                        //pc 스킬 충돌 시 보스 스킬 및 pc 스킬 삭제
                        for (int idx = 0; idx <= skillTop; idx++) {
                            if (skillEffectInfo[idx].X == X && skillEffectInfo[idx].Y == Y) {
                                RemoveSkillEffect(idx);
                                break;
                            }
                        }
                    }
                    else {
                        //나머지 경우 보스 스킬 저장 및 그리기
                        GameBoardInfo[Y][X] = BossSkillEffect;
                        printf("□");
                    }
                }
            }
        }
    }
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            SetCurrentCursorPos(GBOARD_ORIGIN_X + (BossPoint[0] + 9 - TC + x) * 2, GBOARD_ORIGIN_Y + BossPoint[1] + 9 + y);
            if (BossSkillModel[y][x] == BossSkillEffect) {
                X = BossPoint[0] + 9 - TC + x;
                Y = BossPoint[1] + 9 + y;
                if ((X >= 1 && X < GBOARD_WIDTH) && (Y >= 1 && Y < GBOARD_HEIGHT)) {
                    if (GameBoardInfo[Y][X] == PC) {
                        //pc 충돌 시 보스 스킬 삭제 및 pc hp 감소
                        DecreaseHP();
                    }
                    else if (GameBoardInfo[Y][X] > 100) {
                        //pc 스킬 충돌 시 보스 스킬 및 pc 스킬 삭제
                        for (int idx = 0; idx <= skillTop; idx++) {
                            if (skillEffectInfo[idx].X == X && skillEffectInfo[idx].Y == Y) {
                                RemoveSkillEffect(idx);
                                break;
                            }
                        }
                    }
                    else {
                        //나머지 경우 보스 스킬 저장 및 그리기
                        GameBoardInfo[Y][X] = BossSkillEffect;
                        printf("□");
                    }
                }
            }
        }
    }
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            SetCurrentCursorPos(GBOARD_ORIGIN_X + (BossPoint[0] - 5 + x) * 2, GBOARD_ORIGIN_Y + BossPoint[1] + 9 - TC + y);
            if (BossSkillModel[y][x] == BossSkillEffect) {
                X = BossPoint[0] - 5 + x;
                Y = BossPoint[1] + 9 - TC + y;
                if ((X >= 1 && X < GBOARD_WIDTH) && (Y >= 1 && Y < GBOARD_HEIGHT)) {
                    if (GameBoardInfo[Y][X] == PC) {
                        //pc 충돌 시 보스 스킬 삭제 및 pc hp 감소
                        DecreaseHP();
                    }
                    else if (GameBoardInfo[Y][X] > 100) {
                        //pc 스킬 충돌 시 보스 스킬 및 pc 스킬 삭제
                        for (int idx = 0; idx <= skillTop; idx++) {
                            if (skillEffectInfo[idx].X == X && skillEffectInfo[idx].Y == Y) {
                                RemoveSkillEffect(idx);
                                break;
                            }
                        }
                    }
                    else {
                        //나머지 경우 보스 스킬 저장 및 그리기
                        GameBoardInfo[Y][X] = BossSkillEffect;
                        printf("□");
                    }
                }
            }
        }
    }
}

void ShowBossSkill_Rect(int X1, int Y1, int X2, int Y2) {
    int x, y;

    textcolor(darkGREEN);
    for (x = X1; x <= X2; x++) {
        y = Y1;
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
        if ((x >= 1 && x < GBOARD_WIDTH) && (y >= 1 && y < GBOARD_HEIGHT)) {
            if (GameBoardInfo[y][x] == PC) {
                //pc 충돌 시 보스 스킬 삭제 및 pc hp 감소
                DecreaseHP();
            }
            else if (GameBoardInfo[y][x] > 100) {
                //pc 스킬 충돌 시 보스 스킬 및 pc 스킬 삭제
                for (int idx = 0; idx <= skillTop; idx++) {
                    if (skillEffectInfo[idx].X == x && skillEffectInfo[idx].Y == y) {
                        RemoveSkillEffect(idx);
                        break;
                    }
                }
            }
            else {
                //나머지 경우 보스 스킬 저장 및 그리기
                GameBoardInfo[y][x] = BossSkillEffect;
                printf("□");
            }
        }
    }
    for (y = Y1; y <= Y2; y++) {
        x = X1;
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
        if ((x >= 1 && x < GBOARD_WIDTH) && (y >= 1 && y < GBOARD_HEIGHT)) {
            if (GameBoardInfo[y][x] == PC) {
                //pc 충돌 시 보스 스킬 삭제 및 pc hp 감소
                DecreaseHP();
            }
            else if (GameBoardInfo[y][x] > 100) {
                //pc 스킬 충돌 시 보스 스킬 및 pc 스킬 삭제
                for (int idx = 0; idx <= skillTop; idx++) {
                    if (skillEffectInfo[idx].X == x && skillEffectInfo[idx].Y == y) {
                        RemoveSkillEffect(idx);
                        break;
                    }
                }
            }
            else {
                //나머지 경우 보스 스킬 저장 및 그리기
                GameBoardInfo[y][x] = BossSkillEffect;
                printf("□");
            }
        }
    }
    for (y = Y1; y <= Y2; y++) {
        x = X2;
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
        if ((x >= 1 && x < GBOARD_WIDTH) && (y >= 1 && y < GBOARD_HEIGHT)) {
            if (GameBoardInfo[y][x] == PC) {
                //pc 충돌 시 보스 스킬 삭제 및 pc hp 감소
                DecreaseHP();
            }
            else if (GameBoardInfo[y][x] > 100) {
                //pc 스킬 충돌 시 보스 스킬 및 pc 스킬 삭제
                for (int idx = 0; idx <= skillTop; idx++) {
                    if (skillEffectInfo[idx].X == x && skillEffectInfo[idx].Y == y) {
                        RemoveSkillEffect(idx);
                        break;
                    }
                }
            }
            else {
                //나머지 경우 보스 스킬 저장 및 그리기
                GameBoardInfo[y][x] = BossSkillEffect;
                printf("□");
            }
        }
    }
    for (x = X1; x <= X2; x++) {
        y = Y2;
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
        if ((x >= 1 && x < GBOARD_WIDTH) && (y >= 1 && y < GBOARD_HEIGHT)) {
            if (GameBoardInfo[y][x] == PC) {
                //pc 충돌 시 보스 스킬 삭제 및 pc hp 감소
                DecreaseHP();
            }
            else if (GameBoardInfo[y][x] > 100) {
                //pc 스킬 충돌 시 보스 스킬 및 pc 스킬 삭제
                for (int idx = 0; idx <= skillTop; idx++) {
                    if (skillEffectInfo[idx].X == x && skillEffectInfo[idx].Y == y) {
                        RemoveSkillEffect(idx);
                        break;
                    }
                }
            }
            else {
                //나머지 경우 보스 스킬 저장 및 그리기
                GameBoardInfo[y][x] = BossSkillEffect;
                printf("□");
            }
        }
    }
    XX1 -= 4;                   //사각형 크기 조절
    YY1 -= 4;
    XX2 += 4;
    YY2 += 4;
    if ((XX1 < 1 && YY1 < 1) && (XX2 > GBOARD_WIDTH && YY2 > GBOARD_HEIGHT)) {
        DeleteBossSkill();
        bossFlag = 0;
    }
}

void ShowBossSkill_RectOrbit(int X1, int Y1, int X2, int Y2) {                   //스킬궤도
    int x, y;
    textcolor(WHITE);
    while (!((X1 < 1 && Y1 < 1) && (X2 > GBOARD_WIDTH && Y2 > GBOARD_HEIGHT))) {
        for (x = X1; x <= X2; x++) {
            y = Y1;
            SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
            if ((x >= 1 && x < GBOARD_WIDTH) && (y >= 1 && y < GBOARD_HEIGHT)) {
                if (GameBoardInfo[y][x] > 100) {
                    //pc 스킬 충돌 시 보스 스킬 및 pc 스킬 삭제
                    for (int idx = 0; idx <= skillTop; idx++) {
                        if (skillEffectInfo[idx].X == x && skillEffectInfo[idx].Y == y) {
                            RemoveSkillEffect(idx);
                            break;
                        }
                    }
                }
                else {
                    //나머지 경우 보스 스킬 저장 및 그리기
                    if (GameBoardInfo[y][x] != PC) {
                        GameBoardInfo[y][x] = 800;
                        printf("□");
                    }
                }
            }
            PC;
        }
        for (y = Y1; y <= Y2; y++) {
            x = X1;
            SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
            if ((x >= 1 && x < GBOARD_WIDTH) && (y >= 1 && y < GBOARD_HEIGHT)) {
                if (GameBoardInfo[y][x] > 100) {
                    //pc 스킬 충돌 시 보스 스킬 및 pc 스킬 삭제
                    for (int idx = 0; idx <= skillTop; idx++) {
                        if (skillEffectInfo[idx].X == x && skillEffectInfo[idx].Y == y) {
                            RemoveSkillEffect(idx);
                            break;
                        }
                    }
                }
                else {
                    //나머지 경우 보스 스킬 저장 및 그리기
                    if (GameBoardInfo[y][x] != PC) {
                        GameBoardInfo[y][x] = 800;
                        printf("□");
                    }
                }
            }
        }
        for (y = Y1; y <= Y2; y++) {
            x = X2;
            SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
            if ((x >= 1 && x < GBOARD_WIDTH) && (y >= 1 && y < GBOARD_HEIGHT)) {
                if (GameBoardInfo[y][x] > 100) {
                    //pc 스킬 충돌 시 보스 스킬 및 pc 스킬 삭제
                    for (int idx = 0; idx <= skillTop; idx++) {
                        if (skillEffectInfo[idx].X == x && skillEffectInfo[idx].Y == y) {
                            RemoveSkillEffect(idx);
                            break;
                        }
                    }
                }
                else {
                    //나머지 경우 보스 스킬 저장 및 그리기
                    if (GameBoardInfo[y][x] != PC) {
                        GameBoardInfo[y][x] = 800;
                        printf("□");
                    }
                }
            }
        }
        for (x = X1; x <= X2; x++) {
            y = Y2;
            SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
            if ((x >= 1 && x < GBOARD_WIDTH) && (y >= 1 && y < GBOARD_HEIGHT)) {
                if (GameBoardInfo[y][x] > 100) {
                    //pc 스킬 충돌 시 보스 스킬 및 pc 스킬 삭제
                    for (int idx = 0; idx <= skillTop; idx++) {
                        if (skillEffectInfo[idx].X == x && skillEffectInfo[idx].Y == y) {
                            RemoveSkillEffect(idx);
                            break;
                        }
                    }
                }
                else {
                    //나머지 경우 보스 스킬 저장 및 그리기
                    if (GameBoardInfo[y][x] != PC) {
                        GameBoardInfo[y][x] = 800;
                        printf("□");
                    }
                }
            }
        }
        X1 -= 4;                   //사각형 크기 조절
        Y1 -= 4;
        X2 += 4;
        Y2 += 4;
    }
}