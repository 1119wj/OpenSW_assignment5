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
            case W: //�Ͻ�����
                //PauseGame();
                break;
                //case A:   // A ������ Alldie
                //    AllDie();
                //    break;
            }
        }

    }
    if(stage != 3) {
    //�Ϲ���

    //pc ���Ÿ� ��ų ����
    /*if (TimeCount % Diff.attackSpeed == 0) {
        AddEffectByDirection(selectedSkill[0], dir);
    }

    //pc �ٰŸ� ��ų ����
    if (TimeCount % Diff.attackSpeed >= Diff.attackSpeed / 2) {
        if (selectedSkill[1] / 100 % 10 == 4) {
            switch (dir)
            {
            case EAST:
                if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2) AddEffectByDirection(selectedSkill[1], NORTH);
                else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 1) AddEffectByDirection(selectedSkill[1], EAST);
                else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 2) AddEffectByDirection(selectedSkill[1], SOUTH);
                else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 3) AddEffectByDirection(selectedSkill[1], dir);
                break;
            case NORTH:
                if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2) AddEffectByDirection(selectedSkill[1], WEST);
                else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 1) AddEffectByDirection(selectedSkill[1], NORTH);
                else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 2) AddEffectByDirection(selectedSkill[1], EAST);
                else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 3) AddEffectByDirection(selectedSkill[1], dir);
                break;
            case WEST:
                if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2) AddEffectByDirection(selectedSkill[1], SOUTH);
                else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 1) AddEffectByDirection(selectedSkill[1], WEST);
                else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 2) AddEffectByDirection(selectedSkill[1], NORTH);
                else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 3) AddEffectByDirection(selectedSkill[1], dir);
                break;
            case SOUTH:
                if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2) AddEffectByDirection(selectedSkill[1], EAST);
                else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 1) AddEffectByDirection(selectedSkill[1], SOUTH);
                else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 2) AddEffectByDirection(selectedSkill[1], WEST);
                else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 3) AddEffectByDirection(selectedSkill[1], dir);
                break;
            }
        }
        else AddEffectByDirection(selectedSkill[1], dir);
    }
    */
    //�����ǿ� �ִ� ��� �̵�
    //SkillEffectMove();
    if (TimeCount % Diff.npcSpeed == 0) {
        NpcMove();
        RangeNpcMove();
    }
    ProjectileMove();

    SetCurrentCursorPos(133, 15);
    textcolor(WHITE);
    for (int i = 0; i < TimeCount % Diff.attackSpeed; i++)printf("��");
    for (int i = 0; i < Diff.attackSpeed - TimeCount % Diff.attackSpeed - 1; i++)printf("��");




    //������ ������ �ӵ� ����
    if (TimeCount % Diff.spawnSpeed == 0) NpcSpawn();
    if (TimeCount % Diff.spawnSpeed == 0) RangeNpcSpawn();
    if (TimeCount % Diff.projectileSpawnSpeed == 2) RangeNpcAttack();
    }
}