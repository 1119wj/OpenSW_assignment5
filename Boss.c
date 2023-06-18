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