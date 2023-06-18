#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include "GameBoard.h"
#include "PCNPC.h"
#include "Color.h"
#include "ItemData.h"
#include "KeyInput.h"
#include "Cursor.h"
int ChainsawTouched[6] = { 0 };
int NpcInfo[maxmob][2] = { 0 };
int RangeNpcInfo[maxmob][2] = { 0 };
int StopRangeNpcInfo[maxmob][3] = { 0 };
int PCPoint[2] = { 10,10 };
int ProjectileInfo[maxProjectile][3] = { 0 };

int TimeCount = 0;
int AttackCount = 0;
int item = 0; //��� ������ ��ȣ
int CHAINSAWindex;
COORD pc; //pc ��ǥ


COORD RandomSideXY() {
    COORD side;
    int ran;
    while (1) {
        ran = rand() % 4;

        //npc ���� ��ǥ ����
        switch (ran)
        {
        default:
            side.X = 1;
            side.Y = 1;
            break;
        case 0: //�޺�
            side.X = 1;
            side.Y = rand() % (GBOARD_HEIGHT - 1) + 1;
            break;
        case 1: //�캯
            side.X = GBOARD_WIDTH - 1;
            side.Y = rand() % (GBOARD_HEIGHT - 1) + 1;
            break;
        case 2: //��
            side.X = rand() % (GBOARD_WIDTH - 1) + 1;
            side.Y = 1;
            break;
        case 3: //�Ϻ�
            side.X = rand() % (GBOARD_WIDTH - 1) + 1;
            side.Y = GBOARD_HEIGHT - 1;
            break;
        }

        if (GameBoardInfo[side.Y][side.X] == 0) {
            /*SetCurrentCursorPos(0, 0);
            printf("%d, %d", side.X, side.Y);*/
            return side;
        }
    }
}

void NpcMove()   // NPC �̵�
{
    int x, y;
    int a = 0, b = 0;    //a,b �� 1�� 0�� ��  
    int ran;
    int PCPointX = 0;
    int PCPointY = 0;

    for (int i = 0; i < maxmob; i++)
    {
        if (NpcInfo[i][0] != 0)
        {
            PCPointX = PCPoint[0];
            PCPointY = PCPoint[1];

            x = NpcInfo[i][0], y = NpcInfo[i][1];  //npc�� �̵��� ��ġ x,y
            SetCurrentCursorPos(NpcInfo[i][0] * 2 + GBOARD_ORIGIN_X, NpcInfo[i][1] + GBOARD_ORIGIN_Y);
            printf("  ");
            GameBoardInfo[NpcInfo[i][1]][NpcInfo[i][0]] = 0;

            if (PCPointX + 1 <= x)PCPointX++;
            if (PCPointY + 1 <= y)PCPointY++;

            if (PCPointX > NpcInfo[i][0])x++;
            else if (PCPointX < NpcInfo[i][0])x--;
            if (PCPointY > NpcInfo[i][1])y++;
            else if (PCPointY < NpcInfo[i][1])y--;

            if (GameBoardInfo[y][x] == PC)
            {
                NpcDie(NpcInfo[i][0], NpcInfo[i][1]);
                // pc�� �浹 -> pc HP ���̳ʽ� ��Ű��
                //DecreaseHP();
                continue;
            }
            //npc, rangenpc, stoprangenpc, wall, life, bomb �浹 �� ������ �������� ���ư���
            else if (GameBoardInfo[y][x] == NPC || GameBoardInfo[y][x] == MOVINGRANGENPC || GameBoardInfo[y][x] == STOPPEDRANGENPC || GameBoardInfo[y][x] == WALL || GameBoardInfo[y][x] == LIFE || GameBoardInfo[y][x] == BOMB || GameBoardInfo[y][x] == CHAINSAW)
            {
                ran = rand() % 4;
                if (ran == 0) { a = 1; b = 0; }
                else if (ran == 1) { a = 0; b = 1; }
                else if (ran == 2) { a = -1; b = 0; }
                else if (ran == 3) { a = 0; b = -1; }
                x = NpcInfo[i][0] + a;
                y = NpcInfo[i][1] + b;

                //npc, rangenpc, stoprangenpc, wall, life, bomb �浹
                if (GameBoardInfo[y][x] == NPC || GameBoardInfo[y][x] == MOVINGRANGENPC || GameBoardInfo[y][x] == STOPPEDRANGENPC || GameBoardInfo[y][x] == WALL || GameBoardInfo[y][x] == LIFE || GameBoardInfo[y][x] == BOMB || GameBoardInfo[y][x] == CHAINSAW)
                {
                    x = NpcInfo[i][0] + b;
                    y = NpcInfo[i][1] + a;
                }
                if (GameBoardInfo[y][x] == NPC || GameBoardInfo[y][x] == MOVINGRANGENPC || GameBoardInfo[y][x] == STOPPEDRANGENPC || GameBoardInfo[y][x] == WALL || GameBoardInfo[y][x] == LIFE || GameBoardInfo[y][x] == BOMB || GameBoardInfo[y][x] == CHAINSAW)
                {
                    x = NpcInfo[i][0] - a;
                    y = NpcInfo[i][1] - b;
                }
                if (GameBoardInfo[y][x] == NPC || GameBoardInfo[y][x] == MOVINGRANGENPC || GameBoardInfo[y][x] == STOPPEDRANGENPC || GameBoardInfo[y][x] == WALL || GameBoardInfo[y][x] == LIFE || GameBoardInfo[y][x] == BOMB || GameBoardInfo[y][x] == CHAINSAW)
                {
                    x = NpcInfo[i][0] - b;
                    y = NpcInfo[i][1] - a;           //���󺹱�  �ƹ� ���⿡ �� �� ������ ������ �ֱ� 
                }
                if (GameBoardInfo[y][x] == NPC || GameBoardInfo[y][x] == MOVINGRANGENPC || GameBoardInfo[y][x] == STOPPEDRANGENPC || GameBoardInfo[y][x] == WALL || GameBoardInfo[y][x] == LIFE || GameBoardInfo[y][x] == BOMB || GameBoardInfo[y][x] == CHAINSAW)
                {
                    x = NpcInfo[i][0];
                    y = NpcInfo[i][1];
                }
            }
            /*else if (GameBoardInfo[y][x] > 100) {
                //��ų ����Ʈ�� �浹
                if (GameBoardInfo[y][x] < 300) {
                    if (GameBoardInfo[y][x] < 400) {
                        for (int i = 0; i <= skillTop; i++) {
                            if (skillEffectInfo[i].X == x && skillEffectInfo[i].Y == y) {
                                RemoveSkillEffect(i);
                                break;
                            }
                        }
                    }
                    else {
                        GameBoardInfo[y][x] = 0;
                        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
                        printf("  ");
                    }
                }
                NpcDie(NpcInfo[i][0], NpcInfo[i][1]);
                continue;
            }*/
            NpcInfo[i][0] = x;
            NpcInfo[i][1] = y;

            GameBoardInfo[NpcInfo[i][1]][NpcInfo[i][0]] = NPC;
            SetCurrentCursorPos(NpcInfo[i][0] * 2 + GBOARD_ORIGIN_X, NpcInfo[i][1] + GBOARD_ORIGIN_Y);
            drawNpcShape();
        }
    }
}

void NpcSpawn()  //�������� npc ���� (1~width-1),(1~height-1) ��ǥ��
{
    COORD side = RandomSideXY();

    for (int i = 0; i < maxmob; i++) //npc�ִ� ����ŭ ���� �� �̻� ���� x
    {
        if (NpcInfo[i][0] != 0) continue;

        NpcInfo[i][0] = side.X, NpcInfo[i][1] = side.Y;
        GameBoardInfo[side.Y][side.X] = NPC;

        SetCurrentCursorPos(NpcInfo[i][0] * 2 + GBOARD_ORIGIN_X, NpcInfo[i][1] + GBOARD_ORIGIN_Y);
        drawNpcShape();
        break;
    }
}
void NpcDie(int Npc_X, int Npc_Y) // �� �ڸ��� npc ���̰�  npc���� �ֽ�ȭ
{
    int ran = rand();
    if (Npc_X == 0 || Npc_X == GBOARD_WIDTH || Npc_Y == 0 || Npc_Y == GBOARD_HEIGHT) return;

    //������ ���
    SetCurrentCursorPos(Npc_X * 2 + GBOARD_ORIGIN_X, Npc_Y + GBOARD_ORIGIN_Y);
    if (ran % 100 < Diff.itemRate) {
        //������ �׸��� �����ǿ� �߰�
        //GameBoardInfo[Npc_Y][Npc_X] = DropItem();
    }
    else {
        //ĭ ���� �����ǿ��� ����
        printf("  ");
        GameBoardInfo[Npc_Y][Npc_X] = 0;
    }

    for (int i = 0; i < maxmob; i++)
    {
        if (NpcInfo[i][0] == Npc_X && NpcInfo[i][1] == Npc_Y)
        {
            NpcInfo[i][0] = 0;
            break;
        }
    }
}
int DistanceSquare(int x1, int y1, int x2, int y2)  //�Ÿ� ���
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

void PcShiftNext(int x, int y) {
    //���� ó��
    if (x < 0 || x > GBOARD_WIDTH || y < 0 || y > GBOARD_HEIGHT) return; //������ ���θ� ����� �̵����� �ʱ�

    //�浹 ó��
    for (int ny = y; ny < y + 2; ny++) {
        for (int nx = x; nx < x + 2; nx++) {
            switch (GameBoardInfo[ny][nx])
            {
            default: //��Ÿ; PC, ����Ʈ ��
                //������ ���
                ////if (GameBoardInfo[ny][nx] == LIFE || GameBoardInfo[ny][nx] == BOMB) UseItem(GameBoardInfo[ny][nx]);
                //��ų �״�� �ΰ� ������ �̵�
                break;
            case 0: //�ƹ��͵� ���� ��� ������ �̵�
                break;
            case WALL: //���� ��� �Լ� ����
                return;
                break;
            case CHAINSAW:
               /* DecreaseHP();
                if (x < 20)
                {
                    if (y < 20)CHAINSAWindex = 0;
                    else CHAINSAWindex = 3;
                }
                else if (x < 40)
                {
                    if (y < 20)CHAINSAWindex = 1;
                    else CHAINSAWindex = 4;
                }
                else
                {
                    if (y < 20)CHAINSAWindex = 2;
                    else CHAINSAWindex = 5;
                }
                ChainsawTouched[CHAINSAWindex] = 4;
                return;
                break;*/
            case NPC: //npc�� ��� NpcDie �����ϰ� hp �����ϰ� ������ �̵�
                NpcDie(nx, ny);
                //DecreaseHP();
                //������ ���
                ////if (GameBoardInfo[ny][nx] == LIFE || GameBoardInfo[ny][nx] == BOMB) UseItem(GameBoardInfo[ny][nx]);
                break;
                /*case MOVINGRANGENPC: //npc�� ����
                    RangeNpcDie(nx, ny);
                    DecreaseHP();
                    //������ ���
                    ////if (GameBoardInfo[ny][nx] == LIFE || GameBoardInfo[ny][nx] == BOMB) UseItem(GameBoardInfo[ny][nx]);
                    break;
                case STOPPEDRANGENPC: //npc�� ����
                    StopRangeNpcDie(nx, ny);
                    DecreaseHP();
                    //������ ���
                    ////if (GameBoardInfo[ny][nx] == LIFE || GameBoardInfo[ny][nx] == BOMB) UseItem(GameBoardInfo[ny][nx]);
                    break;
                case NPCBULLET: //�� ����ü�� ��� ����ü ���ְ� hp �����ϰ� ������ �̵�
                    ProjectileExtinction(nx, ny);
                    DecreaseHP();
                    break;
                case BossNum: //������ ��� pc hp �����ϰ� ����
                    DecreaseHP();
                    return;
                    break;
                case BossSkillEffect: //���� ��ų�� ��� ��ų �������� pc hp �����ϰ� ������ �̵�
                    DecreaseHP();
                    break;
                }*/
            }
        }

        //pc �̵� ����
        //���� pc �����
        erasePC();

        //���� pc �׸���
        PCPoint[0] = x;
        PCPoint[1] = y;
        drawPC();
    }

}
void PcShiftLeft() {
    PcShiftNext(PCPoint[0] - 1, PCPoint[1]);
}

void PcShiftRight() {
    PcShiftNext(PCPoint[0] + 1, PCPoint[1]);
}

void PcShiftUp() {
    PcShiftNext(PCPoint[0], PCPoint[1] - 1);
}

void PcShiftDown() {
    PcShiftNext(PCPoint[0], PCPoint[1] + 1);
}
