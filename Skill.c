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

#include "Skill.h"
#include "Stage.h"
#include "InitGameData.h"
#include "ItemData.h"
skill skillList[SKILL_TYPE][SKILL_LEVEL]; //��ų ���
int selectedSkill[SELECT_SIZE]; //������ ��ų ��ȣ(110, 120, 130, 210, ...)
skillEffect skillEffectInfo[GBOARD_HEIGHT * GBOARD_WIDTH]; //��ų ����Ʈ ��ǥ ���� �迭
int skillTop = -1; //skillEffectInfo �ִ� �ε���
int flag;
COORD old_cursor; //�������� ���� pc ��ġ
int old_dir; //�������� ���� pc ����
void sub_AddEffectByDirection(COORD cursor, int type, int level, int x, int y, int nx, int ny, int dir) {
	COORD arrCur;
	//���� ó�� 
	if (skillList[type - 1][level - 1].effect[nx][ny] == 0) return; //��ų����Ʈ�� ���� ��� �ѱ��
	if (cursor.X + x < GBOARD_ORIGIN_X - 1 || cursor.X + x > GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 || cursor.Y + y < GBOARD_ORIGIN_Y || cursor.Y + y > GBOARD_ORIGIN_Y + GBOARD_HEIGHT) return; //Ŀ���� ������ ���θ� ����� �ѱ��

	arrCur = ConvertCursorIntoArrCur(cursor);

	//�浹 �˻� �� ����Ʈ ��ȣ�� ������ �迭�� ����
	if (type == 1 || type == 2 || type == 3) {
		switch (GameBoardInfo[arrCur.Y + y][arrCur.X + x])
		{
		default:
			//��Ÿ
			//������ ��ų ����Ʈ ��ǥ�� �迭�� ����
			skillTop++;
			skillEffectInfo[skillTop].X = arrCur.X + x;
			skillEffectInfo[skillTop].Y = arrCur.Y + y;
			skillEffectInfo[skillTop].dir = dir;
			skillEffectInfo[skillTop].level = level;
			skillEffectInfo[skillTop].type = type;
			skillEffectInfo[skillTop].ef = skillList[type - 1][level - 1].effect[nx][ny];
			break;
		case 0:
			//������� ��� ����Ʈ ����ϰ� �����ǿ� �߰��ϰ� ��ų����Ʈ�迭�� ��ǥ ����
			//����Ʈ ���
			SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
			drawSkillShape(type, level);
			//�����ǿ� �߰�
			GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
			//������ ��ų ����Ʈ ��ǥ�� �迭�� ����
			skillTop++;
			skillEffectInfo[skillTop].X = arrCur.X + x;
			skillEffectInfo[skillTop].Y = arrCur.Y + y;
			skillEffectInfo[skillTop].dir = dir;
			skillEffectInfo[skillTop].level = skillList[type - 1][level - 1].level;
			skillEffectInfo[skillTop].type = skillList[type - 1][level - 1].type;
			skillEffectInfo[skillTop].ef = skillList[type - 1][level - 1].effect[nx][ny];
			break;
		case WALL:
			//���̸� �������� �ʰ� �ѱ��
			break;
		case CHAINSAW:
			break;
		case NPC:
			//npc�� npcdie�ϰ� �ѱ��
			NpcDie(arrCur.X + x, arrCur.Y + y);
			IncreaseScore();
			if (type == 3) {
				//����Ʈ ���
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//�����ǿ� �߰�
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				//������ ��ų ����Ʈ ��ǥ�� �迭�� ����
				skillTop++;
				skillEffectInfo[skillTop].X = arrCur.X + x;
				skillEffectInfo[skillTop].Y = arrCur.Y + y;
				skillEffectInfo[skillTop].dir = dir;
				skillEffectInfo[skillTop].level = skillList[type - 1][level - 1].level;
				skillEffectInfo[skillTop].type = skillList[type - 1][level - 1].type;
				skillEffectInfo[skillTop].ef = skillList[type - 1][level - 1].effect[nx][ny];
			}
			break;
		case MOVINGRANGENPC:
			//npc�� ����
			RangeNpcDie(arrCur.X + x, arrCur.Y + y);
			IncreaseScore();
			if (type == 3) {
				//����Ʈ ���
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//�����ǿ� �߰�
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				//������ ��ų ����Ʈ ��ǥ�� �迭�� ����
				skillTop++;
				skillEffectInfo[skillTop].X = arrCur.X + x;
				skillEffectInfo[skillTop].Y = arrCur.Y + y;
				skillEffectInfo[skillTop].dir = dir;
				skillEffectInfo[skillTop].level = skillList[type - 1][level - 1].level;
				skillEffectInfo[skillTop].type = skillList[type - 1][level - 1].type;
				skillEffectInfo[skillTop].ef = skillList[type - 1][level - 1].effect[nx][ny];
			}
			break;
		case STOPPEDRANGENPC:
			//npc�� ����
			StopRangeNpcDie(arrCur.X + x, arrCur.Y + y);
			IncreaseScore();
			if (type == 3) {
				//����Ʈ ���
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//�����ǿ� �߰�
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				//������ ��ų ����Ʈ ��ǥ�� �迭�� ����
				skillTop++;
				skillEffectInfo[skillTop].X = arrCur.X + x;
				skillEffectInfo[skillTop].Y = arrCur.Y + y;
				skillEffectInfo[skillTop].dir = dir;
				skillEffectInfo[skillTop].level = skillList[type - 1][level - 1].level;
				skillEffectInfo[skillTop].type = skillList[type - 1][level - 1].type;
				skillEffectInfo[skillTop].ef = skillList[type - 1][level - 1].effect[nx][ny];
			}
			break;
		case NPCBULLET:
			//npc�� ����
			ProjectileExtinction(arrCur.X + x, arrCur.Y + y);
			if (type == 3) {
				//����Ʈ ���
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//�����ǿ� �߰�
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				//������ ��ų ����Ʈ ��ǥ�� �迭�� ����
				skillTop++;
				skillEffectInfo[skillTop].X = arrCur.X + x;
				skillEffectInfo[skillTop].Y = arrCur.Y + y;
				skillEffectInfo[skillTop].dir = dir;
				skillEffectInfo[skillTop].level = skillList[type - 1][level - 1].level;
				skillEffectInfo[skillTop].type = skillList[type - 1][level - 1].type;
				skillEffectInfo[skillTop].ef = skillList[type - 1][level - 1].effect[nx][ny];
			}
			break;
		case BossNum:
			//�������� �ʰ� ���� hp ����
			DecreaseBossHP();
			break;
		}
	}
	//��
	else if (type == 4) {
		if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2) {
			//���
			switch (GameBoardInfo[arrCur.Y + y][arrCur.X + x])
			{
			default:
				//��Ÿ
				break;
			case 0:
				//������� ��� ����Ʈ ����ϰ� �����ǿ� �߰��ϰ� ��ų����Ʈ�迭�� ��ǥ ����
				//����Ʈ ���
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//�����ǿ� �߰�
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				break;
			case WALL:
				//���̸� �������� �ʰ� �ѱ��
				break;
			case CHAINSAW:
				break;
			case NPC:
				//npc�� npcdie�ϰ� �ѱ��
				NpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case MOVINGRANGENPC:
				//npc�� ����
				RangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case STOPPEDRANGENPC:
				//npc�� ����
				StopRangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case NPCBULLET:
				//npc�� ����
				ProjectileExtinction(arrCur.X + x, arrCur.Y + y);
				break;
			case BossNum:
				//����Ʈ ������� �ʰ� ���� hp ����
				DecreaseBossHP();
				break;
			case BossSkillEffect:
				//����Ʈ ������� �ʰ� ��������Ʈ ����
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = 0;
				break;
			}

			//�̹� pc ��ǥ �� ���� ���
			old_cursor = cursor;
			old_dir = dir;
		}
		else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 1) {
			//���� ����Ʈ �����
			if (flag == 0) {
				switch (old_dir)
				{
				case EAST:
					for (int y = EFFECT_SIZE - 1; y >= 0; y--) {
						for (int x = EFFECT_SIZE - 1; x >= 0; x--) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, EFFECT_SIZE - 1 - y, EFFECT_SIZE - 1 - x, old_dir);
						}
					}
					break;
				case WEST:
					for (int y = 0; y < EFFECT_SIZE; y++) {
						for (int x = 0; x < EFFECT_SIZE; x++) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, y, x, old_dir);
						}
					}
					break;
				case NORTH:
					for (int y = 0; y < EFFECT_SIZE; y++) {
						for (int x = EFFECT_SIZE - 1; x >= 0; x--) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, EFFECT_SIZE - 1 - x, y, old_dir);
						}
					}
					break;
				case SOUTH:
					for (int y = EFFECT_SIZE - 1; y >= 0; y--) {
						for (int x = 0; x < EFFECT_SIZE; x++) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, x, EFFECT_SIZE - 1 - y, old_dir);
						}
					}
					break;
				}
				flag = 1;
			}

			//���
			switch (GameBoardInfo[arrCur.Y + y][arrCur.X + x])
			{
			default:
				//��Ÿ
				break;
			case 0:
				//������� ��� ����Ʈ ����ϰ� �����ǿ� �߰��ϰ� ��ų����Ʈ�迭�� ��ǥ ����
				//����Ʈ ���
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//�����ǿ� �߰�
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				break;
			case WALL:
				//���̸� �������� �ʰ� �ѱ��
				break;
			case CHAINSAW:
				break;
			case NPC:
				//npc�� npcdie�ϰ� �ѱ��
				NpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case MOVINGRANGENPC:
				//npc�� ����
				RangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case STOPPEDRANGENPC:
				//npc�� ����
				StopRangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case NPCBULLET:
				//npc�� ����
				ProjectileExtinction(arrCur.X + x, arrCur.Y + y);
				break;
			case BossNum:
				//����Ʈ ������� �ʰ� ���� hp ����
				DecreaseBossHP();
				break;
			case BossSkillEffect:
				//����Ʈ ������� �ʰ� ��������Ʈ ����
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = 0;
				break;
			}

			//�̹� pc ��ǥ �� ���� ���
			old_cursor = cursor;
			old_dir = dir;
		}
		else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 2) {
			//���� ����Ʈ �����
			if (flag == 0) {
				switch (old_dir)
				{
				case EAST:
					for (int y = EFFECT_SIZE - 1; y >= 0; y--) {
						for (int x = EFFECT_SIZE - 1; x >= 0; x--) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, EFFECT_SIZE - 1 - y, EFFECT_SIZE - 1 - x, old_dir);
						}
					}
					break;
				case WEST:
					for (int y = 0; y < EFFECT_SIZE; y++) {
						for (int x = 0; x < EFFECT_SIZE; x++) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, y, x, old_dir);
						}
					}
					break;
				case NORTH:
					for (int y = 0; y < EFFECT_SIZE; y++) {
						for (int x = EFFECT_SIZE - 1; x >= 0; x--) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, EFFECT_SIZE - 1 - x, y, old_dir);
						}
					}
					break;
				case SOUTH:
					for (int y = EFFECT_SIZE - 1; y >= 0; y--) {
						for (int x = 0; x < EFFECT_SIZE; x++) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, x, EFFECT_SIZE - 1 - y, old_dir);
						}
					}
					break;
				}
				flag = 1;
			}

			//���
			switch (GameBoardInfo[arrCur.Y + y][arrCur.X + x])
			{
			default:
				//��Ÿ
				break;
			case 0:
				//������� ��� ����Ʈ ����ϰ� �����ǿ� �߰��ϰ� ��ų����Ʈ�迭�� ��ǥ ����
				//����Ʈ ���
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//�����ǿ� �߰�
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				break;
			case WALL:
				//���̸� �������� �ʰ� �ѱ��
				break;
			case CHAINSAW:
				break;
			case NPC:
				//npc�� npcdie�ϰ� �ѱ��
				NpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case MOVINGRANGENPC:
				//npc�� ����
				RangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case STOPPEDRANGENPC:
				//npc�� ����
				StopRangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case NPCBULLET:
				//npc�� ����
				ProjectileExtinction(arrCur.X + x, arrCur.Y + y);
				break;
			case BossNum:
				//����Ʈ ������� �ʰ� ���� hp ����
				DecreaseBossHP();
				break;
			case BossSkillEffect:
				//����Ʈ ������� �ʰ� ��������Ʈ ����
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = 0;
				break;
			}

			//�̹� pc ��ǥ �� ���� ���
			old_cursor = cursor;
			old_dir = dir;
		}
		else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 3) {
			//���� ����Ʈ �����
			if (flag == 0) {
				switch (old_dir)
				{
				case EAST:
					for (int y = EFFECT_SIZE - 1; y >= 0; y--) {
						for (int x = EFFECT_SIZE - 1; x >= 0; x--) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, EFFECT_SIZE - 1 - y, EFFECT_SIZE - 1 - x, old_dir);
						}
					}
					break;
				case WEST:
					for (int y = 0; y < EFFECT_SIZE; y++) {
						for (int x = 0; x < EFFECT_SIZE; x++) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, y, x, old_dir);
						}
					}
					break;
				case NORTH:
					for (int y = 0; y < EFFECT_SIZE; y++) {
						for (int x = EFFECT_SIZE - 1; x >= 0; x--) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, EFFECT_SIZE - 1 - x, y, old_dir);
						}
					}
					break;
				case SOUTH:
					for (int y = EFFECT_SIZE - 1; y >= 0; y--) {
						for (int x = 0; x < EFFECT_SIZE; x++) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, x, EFFECT_SIZE - 1 - y, old_dir);
						}
					}
					break;
				}
				flag = 1;
			}
		}
	}
	//�溮
	else if (type == 5) {
		if (TimeCount % (Diff.attackSpeed * 2) == Diff.attackSpeed / 2) {
			//���
			switch (GameBoardInfo[arrCur.Y + y][arrCur.X + x])
			{
			default:
				//��Ÿ
				break;
			case 0:
				//������� ��� ����Ʈ ����ϰ� �����ǿ� �߰��ϰ� ��ų����Ʈ�迭�� ��ǥ ����
				//����Ʈ ���
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//�����ǿ� �߰�
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				break;
			case WALL:
				//���̸� �������� �ʰ� �ѱ��
				break;
			case CHAINSAW:
				break;
			case NPC:
				//npc�� npcdie�ϰ� �ѱ��
				NpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case MOVINGRANGENPC:
				//npc�� ����
				RangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case STOPPEDRANGENPC:
				//npc�� ����
				StopRangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case NPCBULLET:
				//npc�� ����
				ProjectileExtinction(arrCur.X + x, arrCur.Y + y);
				break;
			case BossNum:
				//����Ʈ ������� �ʰ� ���� hp ����
				DecreaseBossHP();
				break;
			case BossSkillEffect:
				//����Ʈ ������� �ʰ� ��������Ʈ ����
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = 0;
				break;
			}
		}
	}
	//��ġ
	else if (type == 6) {
		if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2) {
			//���
			switch (GameBoardInfo[arrCur.Y + y][arrCur.X + x])
			{
			default:
				//��Ÿ
				break;
			case 0:
				//������� ��� ����Ʈ ����ϰ� �����ǿ� �߰��ϰ� ��ų����Ʈ�迭�� ��ǥ ����
				//����Ʈ ���
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//�����ǿ� �߰�
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				break;
			case WALL:
				//���̸� �������� �ʰ� �ѱ��
				break;
			case CHAINSAW:
				break;
			case NPC:
				//npc�� npcdie�ϰ� �ѱ��
				NpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case MOVINGRANGENPC:
				//npc�� ����
				RangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case STOPPEDRANGENPC:
				//npc�� ����
				StopRangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case NPCBULLET:
				//npc�� ����
				ProjectileExtinction(arrCur.X + x, arrCur.Y + y);
				break;
			case BossNum:
				//����Ʈ ������� �ʰ� ���� hp ����
				DecreaseBossHP();
				break;
			case BossSkillEffect:
				//����Ʈ ������� �ʰ� ��������Ʈ ����
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = 0;
				break;
			}

			//�̹� pc ��ǥ �� ���� ���
			old_cursor = cursor;
			old_dir = dir;
		}
		else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 1) {
			//���� ����Ʈ �����
			if (flag == 0) {
				switch (old_dir)
				{
				case EAST:
					for (int y = EFFECT_SIZE - 1; y >= 0; y--) {
						for (int x = EFFECT_SIZE - 1; x >= 0; x--) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, EFFECT_SIZE - 1 - y, EFFECT_SIZE - 1 - x, old_dir);
						}
					}
					break;
				case WEST:
					for (int y = 0; y < EFFECT_SIZE; y++) {
						for (int x = 0; x < EFFECT_SIZE; x++) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, y, x, old_dir);
						}
					}
					break;
				case NORTH:
					for (int y = 0; y < EFFECT_SIZE; y++) {
						for (int x = EFFECT_SIZE - 1; x >= 0; x--) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, EFFECT_SIZE - 1 - x, y, old_dir);
						}
					}
					break;
				case SOUTH:
					for (int y = EFFECT_SIZE - 1; y >= 0; y--) {
						for (int x = 0; x < EFFECT_SIZE; x++) {
							erase_AddEffectByDirection(old_cursor, type, level, x, y, x, EFFECT_SIZE - 1 - y, old_dir);
						}
					}
					break;
				}
				flag = 1;
			}
		}
	}
}
void erase_AddEffectByDirection(COORD cursor, int type, int level, int x, int y, int nx, int ny, int dir) {
	//���� ó��
	if (skillList[type - 1][level - 1].effect[nx][ny] == 0) return; //��ų����Ʈ�� ���� ��� �ѱ��
	if (cursor.X + x < GBOARD_ORIGIN_X - 1 || cursor.X + x > GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 || cursor.Y + y < GBOARD_ORIGIN_Y || cursor.Y + y > GBOARD_ORIGIN_Y + GBOARD_HEIGHT) return; //Ŀ���� ������ ���θ� ����� �ѱ��

	COORD arrCur = ConvertCursorIntoArrCur(cursor);

	//���� ���� ����Ʈ �����
	if (GameBoardInfo[arrCur.Y + y][arrCur.X + x] >= 400) {
		GameBoardInfo[arrCur.Y + y][arrCur.X + x] = 0;
		SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
		printf("  ");
	}
}
void AddEffectByDirection(int skillNum, int dir) {
	if (skillNum == 0) return; //��ų�� ������ ����

	COORD cursor;
	int type = (skillNum / 100) % 10;
	int level = (skillNum / 10) % 10;

	if (type < 1 || type > 9 || level < 1 || level > 3) return; //���� ó��

	pc.X = PCPoint[0];
	pc.Y = PCPoint[1];

	flag = 0;

	//���� ����Ʈ �׸���
	switch (dir)
	{
	default:
		break;
	case EAST:
		cursor.X = GBOARD_ORIGIN_X + (pc.X + EFFECT_SIZE - 2) * 2;
		cursor.Y = GBOARD_ORIGIN_Y + pc.Y - 1;
		SetCurrentCursorPos(cursor.X, cursor.Y);
		for (int y = EFFECT_SIZE - 1; y >= 0; y--) {
			for (int x = EFFECT_SIZE - 1; x >= 0; x--) {
				sub_AddEffectByDirection(cursor, type, level, x, y, EFFECT_SIZE - 1 - y, EFFECT_SIZE - 1 - x, dir);
			}
		}
		break;
	case WEST:
		cursor.X = GBOARD_ORIGIN_X + (pc.X - EFFECT_SIZE) * 2;
		cursor.Y = GBOARD_ORIGIN_Y + pc.Y - 1;
		SetCurrentCursorPos(cursor.X, cursor.Y);
		for (int y = 0; y < EFFECT_SIZE; y++) {
			for (int x = 0; x < EFFECT_SIZE; x++) {
				sub_AddEffectByDirection(cursor, type, level, x, y, y, x, dir);
			}
		}
		break;
	case NORTH:
		cursor.X = GBOARD_ORIGIN_X + (pc.X - 1) * 2;
		cursor.Y = GBOARD_ORIGIN_Y + pc.Y - 4;
		SetCurrentCursorPos(cursor.X, cursor.Y);
		for (int y = 0; y < EFFECT_SIZE; y++) {
			for (int x = EFFECT_SIZE - 1; x >= 0; x--) {
				sub_AddEffectByDirection(cursor, type, level, x, y, EFFECT_SIZE - 1 - x, y, dir);
			}
		}
		break;
	case SOUTH:
		cursor.X = GBOARD_ORIGIN_X + (pc.X - 1) * 2;
		cursor.Y = GBOARD_ORIGIN_Y + pc.Y + 2;
		SetCurrentCursorPos(cursor.X, cursor.Y);
		for (int y = EFFECT_SIZE - 1; y >= 0; y--) {
			for (int x = 0; x < EFFECT_SIZE; x++) {
				sub_AddEffectByDirection(cursor, type, level, x, y, x, EFFECT_SIZE - 1 - y, dir);
			}
		}
		break;
	}

	//�����
	/*SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 4, 25);
	printf("���%d", TimeCount);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + (x + 2) * 4, 26 + y);
			printf("%03d,", skillList[type - 1][level - 1].effect[y][x]);
		}
	}*/
}
