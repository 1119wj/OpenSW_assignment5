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

Item itemList[2];

void defineItem() {
    for (int i = 0; i < ITEMNUM; i++) {
        switch (i)
        {
        default:
            break;
        case 0: //������
            itemList[i].num = LIFE;
            strcpy(itemList[i].shape, "��");
            itemList[i].color = RED;
            break;
        case 1: //��ź
            itemList[i].num = BOMB;
            strcpy(itemList[i].shape, "��");
            itemList[i].color = darkGRAY;
            break;
        }
    }
}

void UseItem(int num) {
    int i;

    for (i = 0; i < ITEMNUM; i++) {
        if (itemList[i].num == num) break;
    }

    switch (i)
    {
    case 0: //LIFE
        if (HP < maxHP) {
            HP++; //�ִ� ��� �ȿ��� ���+1
            drawHP();
        }
        break;
    case 1: //BOMB
        Bomb(PCPoint[0], PCPoint[1]);
        AllDie(); //��� ��� ���� ���ֱ�
        drawScore();
        LevelUp();
        break;
    }
}

int DropItem() {
    //���� ������ �׸��� �� �����۹�ȣ ��ȯ
    int type = rand() % ITEMNUM; //������ ��ȣ ���� ����
    drawItemShape(type);
    return itemList[type].num;
}

void Bomb(int x, int y) {
    int startx;
    int finishx;
    int starty;
    int finishy;

    for (int i = 1; i <= 70; i++)
    {
        textcolor(RED);
        startx = x - i;
        finishx = x + i;
        starty = y - i;
        finishy = y + i;
        for (int X = startx; X <= finishx; X++)
        {
            SetCurrentCursorPos(GBOARD_ORIGIN_X + X * 2, GBOARD_ORIGIN_Y + starty);
            if (1 <= X && X < GBOARD_WIDTH && 1 <= starty && starty <= GBOARD_HEIGHT && GameBoardInfo[starty][X] != PC && GameBoardInfo[starty][X] != WALL && GameBoardInfo[starty][X] != BOMB && GameBoardInfo[starty][X] != LIFE && GameBoardInfo[starty][X] != CHAINSAW)printf("��");
            SetCurrentCursorPos(GBOARD_ORIGIN_X + X * 2, GBOARD_ORIGIN_Y + finishy);
            if (1 <= X && X < GBOARD_WIDTH && 1 <= finishy && finishy <= GBOARD_HEIGHT && GameBoardInfo[finishy][X] != PC && GameBoardInfo[finishy][X] != WALL && GameBoardInfo[finishy][X] != BOMB && GameBoardInfo[finishy][X] != LIFE && GameBoardInfo[finishy][X] != CHAINSAW)printf("��");
        }
        for (int Y = starty; Y <= finishy; Y++)
        {
            SetCurrentCursorPos(GBOARD_ORIGIN_X + startx * 2, GBOARD_ORIGIN_Y + Y);
            if (1 <= Y && Y <= GBOARD_HEIGHT && 1 <= startx && startx < GBOARD_WIDTH && GameBoardInfo[Y][startx] != PC && GameBoardInfo[Y][startx] != WALL && GameBoardInfo[Y][startx] != BOMB && GameBoardInfo[Y][startx] != LIFE && GameBoardInfo[Y][startx] != CHAINSAW)printf("��");
            SetCurrentCursorPos(GBOARD_ORIGIN_X + finishx * 2, GBOARD_ORIGIN_Y + Y);
            if (1 <= Y && Y <= GBOARD_HEIGHT && 1 <= finishx && finishx < GBOARD_WIDTH && GameBoardInfo[Y][finishx] != PC && GameBoardInfo[Y][finishx] != WALL && GameBoardInfo[Y][finishx] != BOMB && GameBoardInfo[Y][finishx] != LIFE && GameBoardInfo[Y][finishx] != CHAINSAW)printf("��");
        }
        Sleep(5);

        if (i >= 4)
        {
            textcolor(YELLOW);
            startx += 4;
            finishx -= 4;
            starty += 4;
            finishy -= 4;
            for (int X = startx; X <= finishx; X++)
            {
                SetCurrentCursorPos(GBOARD_ORIGIN_X + X * 2, GBOARD_ORIGIN_Y + starty);
                if (1 <= X && X < GBOARD_WIDTH && 1 <= starty && starty <= GBOARD_HEIGHT && GameBoardInfo[starty][X] != PC && GameBoardInfo[starty][X] != WALL && GameBoardInfo[starty][X] != BOMB && GameBoardInfo[starty][X] != LIFE && GameBoardInfo[starty][X] != CHAINSAW)printf("��");
                SetCurrentCursorPos(GBOARD_ORIGIN_X + X * 2, GBOARD_ORIGIN_Y + finishy);
                if (1 <= X && X < GBOARD_WIDTH && 1 <= finishy && finishy <= GBOARD_HEIGHT && GameBoardInfo[finishy][X] != PC && GameBoardInfo[finishy][X] != WALL && GameBoardInfo[finishy][X] != BOMB && GameBoardInfo[finishy][X] != LIFE && GameBoardInfo[finishy][X] != CHAINSAW)printf("��");
            }
            for (int Y = starty; Y <= finishy; Y++)
            {
                SetCurrentCursorPos(GBOARD_ORIGIN_X + startx * 2, GBOARD_ORIGIN_Y + Y);
                if (1 <= Y && Y <= GBOARD_HEIGHT && 1 <= startx && startx < GBOARD_WIDTH && GameBoardInfo[Y][startx] != PC && GameBoardInfo[Y][startx] != WALL && GameBoardInfo[Y][startx] != BOMB && GameBoardInfo[Y][startx] != LIFE && GameBoardInfo[Y][startx] != CHAINSAW)printf("��");
                SetCurrentCursorPos(GBOARD_ORIGIN_X + finishx * 2, GBOARD_ORIGIN_Y + Y);
                if (1 <= Y && Y <= GBOARD_HEIGHT && 1 <= finishx && finishx < GBOARD_WIDTH && GameBoardInfo[Y][finishx] != PC && GameBoardInfo[Y][finishx] != WALL && GameBoardInfo[Y][finishx] != BOMB && GameBoardInfo[Y][finishx] != LIFE && GameBoardInfo[Y][finishx] != CHAINSAW)printf("��");
            }
        }
        if (i >= 6)
        {
            startx += 6;
            finishx -= 6;
            starty += 6;
            finishy -= 6;
            for (int X = startx; X <= finishx; X++)
            {
                SetCurrentCursorPos(GBOARD_ORIGIN_X + X * 2, GBOARD_ORIGIN_Y + starty);
                if (1 <= X && X < GBOARD_WIDTH && 1 <= starty && starty <= GBOARD_HEIGHT && GameBoardInfo[starty][X] != PC && GameBoardInfo[starty][X] != WALL && GameBoardInfo[starty][X] != BOMB && GameBoardInfo[starty][X] != LIFE && GameBoardInfo[starty][X] != CHAINSAW)printf("  ");
                SetCurrentCursorPos(GBOARD_ORIGIN_X + X * 2, GBOARD_ORIGIN_Y + finishy);
                if (1 <= X && X < GBOARD_WIDTH && 1 <= finishy && finishy <= GBOARD_HEIGHT && GameBoardInfo[finishy][X] != PC && GameBoardInfo[finishy][X] != WALL && GameBoardInfo[finishy][X] != BOMB && GameBoardInfo[finishy][X] != LIFE && GameBoardInfo[finishy][X] != CHAINSAW)printf("  ");
            }
            for (int Y = starty; Y <= finishy; Y++)
            {
                SetCurrentCursorPos(GBOARD_ORIGIN_X + startx * 2, GBOARD_ORIGIN_Y + Y);
                if (1 <= Y && Y <= GBOARD_HEIGHT && 1 <= startx && startx < GBOARD_WIDTH && GameBoardInfo[Y][startx] != PC && GameBoardInfo[Y][startx] != WALL && GameBoardInfo[Y][startx] != BOMB && GameBoardInfo[Y][startx] != LIFE && GameBoardInfo[Y][startx] != CHAINSAW)printf("  ");
                SetCurrentCursorPos(GBOARD_ORIGIN_X + finishx * 2, GBOARD_ORIGIN_Y + Y);
                if (1 <= Y && Y <= GBOARD_HEIGHT && 1 <= finishx && finishx < GBOARD_WIDTH && GameBoardInfo[Y][finishx] != PC && GameBoardInfo[Y][finishx] != WALL && GameBoardInfo[Y][finishx] != BOMB && GameBoardInfo[Y][finishx] != LIFE && GameBoardInfo[Y][finishx] != CHAINSAW)printf("  ");
            }
        }

    }

}