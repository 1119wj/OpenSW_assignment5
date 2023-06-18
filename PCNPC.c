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
int item = 0; //드랍 아이템 번호
int CHAINSAWindex;
COORD pc; //pc 좌표


COORD RandomSideXY() {
    COORD side;
    int ran;
    while (1) {
        ran = rand() % 4;

        //npc 생성 좌표 지정
        switch (ran)
        {
        default:
            side.X = 1;
            side.Y = 1;
            break;
        case 0: //왼변
            side.X = 1;
            side.Y = rand() % (GBOARD_HEIGHT - 1) + 1;
            break;
        case 1: //우변
            side.X = GBOARD_WIDTH - 1;
            side.Y = rand() % (GBOARD_HEIGHT - 1) + 1;
            break;
        case 2: //상변
            side.X = rand() % (GBOARD_WIDTH - 1) + 1;
            side.Y = 1;
            break;
        case 3: //하변
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

void NpcMove()   // NPC 이동
{
    int x, y;
    int a = 0, b = 0;    //a,b 는 1과 0의 쌍  
    int ran;
    int PCPointX = 0;
    int PCPointY = 0;

    for (int i = 0; i < maxmob; i++)
    {
        if (NpcInfo[i][0] != 0)
        {
            PCPointX = PCPoint[0];
            PCPointY = PCPoint[1];

            x = NpcInfo[i][0], y = NpcInfo[i][1];  //npc가 이동할 위치 x,y
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
                // pc와 충돌 -> pc HP 마이너스 시키기
                //DecreaseHP();
                continue;
            }
            //npc, rangenpc, stoprangenpc, wall, life, bomb 충돌 시 랜덤의 방향으로 돌아가기
            else if (GameBoardInfo[y][x] == NPC || GameBoardInfo[y][x] == MOVINGRANGENPC || GameBoardInfo[y][x] == STOPPEDRANGENPC || GameBoardInfo[y][x] == WALL || GameBoardInfo[y][x] == LIFE || GameBoardInfo[y][x] == BOMB || GameBoardInfo[y][x] == CHAINSAW)
            {
                ran = rand() % 4;
                if (ran == 0) { a = 1; b = 0; }
                else if (ran == 1) { a = 0; b = 1; }
                else if (ran == 2) { a = -1; b = 0; }
                else if (ran == 3) { a = 0; b = -1; }
                x = NpcInfo[i][0] + a;
                y = NpcInfo[i][1] + b;

                //npc, rangenpc, stoprangenpc, wall, life, bomb 충돌
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
                    y = NpcInfo[i][1] - a;           //원상복구  아무 방향에 갈 곳 없으면 가만히 있기 
                }
                if (GameBoardInfo[y][x] == NPC || GameBoardInfo[y][x] == MOVINGRANGENPC || GameBoardInfo[y][x] == STOPPEDRANGENPC || GameBoardInfo[y][x] == WALL || GameBoardInfo[y][x] == LIFE || GameBoardInfo[y][x] == BOMB || GameBoardInfo[y][x] == CHAINSAW)
                {
                    x = NpcInfo[i][0];
                    y = NpcInfo[i][1];
                }
            }
            /*else if (GameBoardInfo[y][x] > 100) {
                //스킬 이펙트와 충돌
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

void NpcSpawn()  //랜덤으로 npc 생성 (1~width-1),(1~height-1) 좌표에
{
    COORD side = RandomSideXY();

    for (int i = 0; i < maxmob; i++) //npc최대 수만큼 차면 더 이상 생성 x
    {
        if (NpcInfo[i][0] != 0) continue;

        NpcInfo[i][0] = side.X, NpcInfo[i][1] = side.Y;
        GameBoardInfo[side.Y][side.X] = NPC;

        SetCurrentCursorPos(NpcInfo[i][0] * 2 + GBOARD_ORIGIN_X, NpcInfo[i][1] + GBOARD_ORIGIN_Y);
        drawNpcShape();
        break;
    }
}
void NpcDie(int Npc_X, int Npc_Y) // 그 자리에 npc 죽이고  npc인포 최신화
{
    int ran = rand();
    if (Npc_X == 0 || Npc_X == GBOARD_WIDTH || Npc_Y == 0 || Npc_Y == GBOARD_HEIGHT) return;

    //아이템 드랍
    SetCurrentCursorPos(Npc_X * 2 + GBOARD_ORIGIN_X, Npc_Y + GBOARD_ORIGIN_Y);
    if (ran % 100 < Diff.itemRate) {
        //아이템 그리고 게임판에 추가
        //GameBoardInfo[Npc_Y][Npc_X] = DropItem();
    }
    else {
        //칸 비우고 게임판에서 삭제
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
int DistanceSquare(int x1, int y1, int x2, int y2)  //거리 계산
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

void PcShiftNext(int x, int y) {
    //예외 처리
    if (x < 0 || x > GBOARD_WIDTH || y < 0 || y > GBOARD_HEIGHT) return; //게임판 내부를 벗어나면 이동하지 않기

    //충돌 처리
    for (int ny = y; ny < y + 2; ny++) {
        for (int nx = x; nx < x + 2; nx++) {
            switch (GameBoardInfo[ny][nx])
            {
            default: //기타; PC, 이펙트 등
                //아이템 사용
                ////if (GameBoardInfo[ny][nx] == LIFE || GameBoardInfo[ny][nx] == BOMB) UseItem(GameBoardInfo[ny][nx]);
                //스킬 그대로 두고 밑으로 이동
                break;
            case 0: //아무것도 없을 경우 밑으로 이동
                break;
            case WALL: //벽일 경우 함수 종료
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
            case NPC: //npc일 경우 NpcDie 실행하고 hp 감소하고 밑으로 이동
                NpcDie(nx, ny);
                //DecreaseHP();
                //아이템 사용
                ////if (GameBoardInfo[ny][nx] == LIFE || GameBoardInfo[ny][nx] == BOMB) UseItem(GameBoardInfo[ny][nx]);
                break;
                /*case MOVINGRANGENPC: //npc와 동일
                    RangeNpcDie(nx, ny);
                    DecreaseHP();
                    //아이템 사용
                    ////if (GameBoardInfo[ny][nx] == LIFE || GameBoardInfo[ny][nx] == BOMB) UseItem(GameBoardInfo[ny][nx]);
                    break;
                case STOPPEDRANGENPC: //npc와 동일
                    StopRangeNpcDie(nx, ny);
                    DecreaseHP();
                    //아이템 사용
                    ////if (GameBoardInfo[ny][nx] == LIFE || GameBoardInfo[ny][nx] == BOMB) UseItem(GameBoardInfo[ny][nx]);
                    break;
                case NPCBULLET: //적 투사체일 경우 투사체 없애고 hp 감소하고 밑으로 이동
                    ProjectileExtinction(nx, ny);
                    DecreaseHP();
                    break;
                case BossNum: //보스일 경우 pc hp 감소하고 종료
                    DecreaseHP();
                    return;
                    break;
                case BossSkillEffect: //보스 스킬일 경우 스킬 없어지고 pc hp 감소하고 밑으로 이동
                    DecreaseHP();
                    break;
                }*/
            }
        }

        //pc 이동 구현
        //현재 pc 지우기
        erasePC();

        //다음 pc 그리기
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
