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


int key = 0;
Difficulty Diff;
int lastDir = EAST;

void ProcessKeyInput() {
    int key, dir = lastDir;
    for (int i = 0; i < 10; i++, AttackCount++) {
        if (_kbhit() != 0) {
            key = _getch();
            switch (key)
            {
            default:
                dir = lastDir;
                break;
            case KEY_LEFT:
                dir = WEST;
                lastDir = dir;
                PcShiftLeft();
                break;
            case KEY_RIGHT:
                dir = EAST;
                lastDir = dir;
                PcShiftRight();
                break;
            case KEY_UP:
                dir = NORTH;
                lastDir = dir;
                PcShiftUp();
                break;
            case KEY_DOWN:
                dir = SOUTH;
                lastDir = dir;
                PcShiftDown();
                break;
            case W: //일시정지
                //PauseGame();
                break;
                //case A:   // A 누르면 Alldie
                //    AllDie();
                //    break;
            }
        }

    }
}