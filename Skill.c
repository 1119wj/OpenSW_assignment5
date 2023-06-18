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

#include "Skill.h"
#include "Stage.h"
#include "InitGameData.h"
#include "ItemData.h"
skill skillList[SKILL_TYPE][SKILL_LEVEL]; //스킬 목록
int selectedSkill[SELECT_SIZE]; //보유한 스킬 번호(110, 120, 130, 210, ...)
skillEffect skillEffectInfo[GBOARD_HEIGHT * GBOARD_WIDTH]; //스킬 이펙트 좌표 저장 배열
int skillTop = -1; //skillEffectInfo 최대 인덱스
int flag;
COORD old_cursor; //근접공격 이전 pc 위치
int old_dir; //근접공격 이전 pc 방향
void sub_AddEffectByDirection(COORD cursor, int type, int level, int x, int y, int nx, int ny, int dir) {
	COORD arrCur;
	//예외 처리 
	if (skillList[type - 1][level - 1].effect[nx][ny] == 0) return; //스킬이펙트가 없을 경우 넘기기
	if (cursor.X + x < GBOARD_ORIGIN_X - 1 || cursor.X + x > GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 || cursor.Y + y < GBOARD_ORIGIN_Y || cursor.Y + y > GBOARD_ORIGIN_Y + GBOARD_HEIGHT) return; //커서가 게임판 내부를 벗어나면 넘기기

	arrCur = ConvertCursorIntoArrCur(cursor);

	//충돌 검사 및 이펙트 번호를 게임판 배열에 저장
	if (type == 1 || type == 2 || type == 3) {
		switch (GameBoardInfo[arrCur.Y + y][arrCur.X + x])
		{
		default:
			//기타
			//게임판 스킬 이펙트 좌표를 배열에 저장
			skillTop++;
			skillEffectInfo[skillTop].X = arrCur.X + x;
			skillEffectInfo[skillTop].Y = arrCur.Y + y;
			skillEffectInfo[skillTop].dir = dir;
			skillEffectInfo[skillTop].level = level;
			skillEffectInfo[skillTop].type = type;
			skillEffectInfo[skillTop].ef = skillList[type - 1][level - 1].effect[nx][ny];
			break;
		case 0:
			//비어있을 경우 이펙트 출력하고 게임판에 추가하고 스킬이펙트배열에 좌표 저장
			//이펙트 출력
			SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
			drawSkillShape(type, level);
			//게임판에 추가
			GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
			//게임판 스킬 이펙트 좌표를 배열에 저장
			skillTop++;
			skillEffectInfo[skillTop].X = arrCur.X + x;
			skillEffectInfo[skillTop].Y = arrCur.Y + y;
			skillEffectInfo[skillTop].dir = dir;
			skillEffectInfo[skillTop].level = skillList[type - 1][level - 1].level;
			skillEffectInfo[skillTop].type = skillList[type - 1][level - 1].type;
			skillEffectInfo[skillTop].ef = skillList[type - 1][level - 1].effect[nx][ny];
			break;
		case WALL:
			//벽이면 생성하지 않고 넘기기
			break;
		case CHAINSAW:
			break;
		case NPC:
			//npc면 npcdie하고 넘기기
			NpcDie(arrCur.X + x, arrCur.Y + y);
			IncreaseScore();
			if (type == 3) {
				//이펙트 출력
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//게임판에 추가
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				//게임판 스킬 이펙트 좌표를 배열에 저장
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
			//npc와 동일
			RangeNpcDie(arrCur.X + x, arrCur.Y + y);
			IncreaseScore();
			if (type == 3) {
				//이펙트 출력
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//게임판에 추가
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				//게임판 스킬 이펙트 좌표를 배열에 저장
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
			//npc와 동일
			StopRangeNpcDie(arrCur.X + x, arrCur.Y + y);
			IncreaseScore();
			if (type == 3) {
				//이펙트 출력
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//게임판에 추가
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				//게임판 스킬 이펙트 좌표를 배열에 저장
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
			//npc와 동일
			ProjectileExtinction(arrCur.X + x, arrCur.Y + y);
			if (type == 3) {
				//이펙트 출력
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//게임판에 추가
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				//게임판 스킬 이펙트 좌표를 배열에 저장
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
			//생성하지 않고 보스 hp 감소
			DecreaseBossHP();
			break;
		}
	}
	//검
	else if (type == 4) {
		if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2) {
			//출력
			switch (GameBoardInfo[arrCur.Y + y][arrCur.X + x])
			{
			default:
				//기타
				break;
			case 0:
				//비어있을 경우 이펙트 출력하고 게임판에 추가하고 스킬이펙트배열에 좌표 저장
				//이펙트 출력
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//게임판에 추가
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				break;
			case WALL:
				//벽이면 생성하지 않고 넘기기
				break;
			case CHAINSAW:
				break;
			case NPC:
				//npc면 npcdie하고 넘기기
				NpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case MOVINGRANGENPC:
				//npc와 동일
				RangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case STOPPEDRANGENPC:
				//npc와 동일
				StopRangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case NPCBULLET:
				//npc와 동일
				ProjectileExtinction(arrCur.X + x, arrCur.Y + y);
				break;
			case BossNum:
				//이펙트 출력하지 않고 보스 hp 감소
				DecreaseBossHP();
				break;
			case BossSkillEffect:
				//이펙트 출력하지 않고 보스이펙트 제거
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = 0;
				break;
			}

			//이번 pc 좌표 및 방향 백업
			old_cursor = cursor;
			old_dir = dir;
		}
		else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 1) {
			//이전 이펙트 지우기
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

			//출력
			switch (GameBoardInfo[arrCur.Y + y][arrCur.X + x])
			{
			default:
				//기타
				break;
			case 0:
				//비어있을 경우 이펙트 출력하고 게임판에 추가하고 스킬이펙트배열에 좌표 저장
				//이펙트 출력
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//게임판에 추가
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				break;
			case WALL:
				//벽이면 생성하지 않고 넘기기
				break;
			case CHAINSAW:
				break;
			case NPC:
				//npc면 npcdie하고 넘기기
				NpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case MOVINGRANGENPC:
				//npc와 동일
				RangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case STOPPEDRANGENPC:
				//npc와 동일
				StopRangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case NPCBULLET:
				//npc와 동일
				ProjectileExtinction(arrCur.X + x, arrCur.Y + y);
				break;
			case BossNum:
				//이펙트 출력하지 않고 보스 hp 감소
				DecreaseBossHP();
				break;
			case BossSkillEffect:
				//이펙트 출력하지 않고 보스이펙트 제거
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = 0;
				break;
			}

			//이번 pc 좌표 및 방향 백업
			old_cursor = cursor;
			old_dir = dir;
		}
		else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 2) {
			//이전 이펙트 지우기
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

			//출력
			switch (GameBoardInfo[arrCur.Y + y][arrCur.X + x])
			{
			default:
				//기타
				break;
			case 0:
				//비어있을 경우 이펙트 출력하고 게임판에 추가하고 스킬이펙트배열에 좌표 저장
				//이펙트 출력
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//게임판에 추가
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				break;
			case WALL:
				//벽이면 생성하지 않고 넘기기
				break;
			case CHAINSAW:
				break;
			case NPC:
				//npc면 npcdie하고 넘기기
				NpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case MOVINGRANGENPC:
				//npc와 동일
				RangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case STOPPEDRANGENPC:
				//npc와 동일
				StopRangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case NPCBULLET:
				//npc와 동일
				ProjectileExtinction(arrCur.X + x, arrCur.Y + y);
				break;
			case BossNum:
				//이펙트 출력하지 않고 보스 hp 감소
				DecreaseBossHP();
				break;
			case BossSkillEffect:
				//이펙트 출력하지 않고 보스이펙트 제거
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = 0;
				break;
			}

			//이번 pc 좌표 및 방향 백업
			old_cursor = cursor;
			old_dir = dir;
		}
		else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 3) {
			//이전 이펙트 지우기
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
	//방벽
	else if (type == 5) {
		if (TimeCount % (Diff.attackSpeed * 2) == Diff.attackSpeed / 2) {
			//출력
			switch (GameBoardInfo[arrCur.Y + y][arrCur.X + x])
			{
			default:
				//기타
				break;
			case 0:
				//비어있을 경우 이펙트 출력하고 게임판에 추가하고 스킬이펙트배열에 좌표 저장
				//이펙트 출력
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//게임판에 추가
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				break;
			case WALL:
				//벽이면 생성하지 않고 넘기기
				break;
			case CHAINSAW:
				break;
			case NPC:
				//npc면 npcdie하고 넘기기
				NpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case MOVINGRANGENPC:
				//npc와 동일
				RangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case STOPPEDRANGENPC:
				//npc와 동일
				StopRangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case NPCBULLET:
				//npc와 동일
				ProjectileExtinction(arrCur.X + x, arrCur.Y + y);
				break;
			case BossNum:
				//이펙트 출력하지 않고 보스 hp 감소
				DecreaseBossHP();
				break;
			case BossSkillEffect:
				//이펙트 출력하지 않고 보스이펙트 제거
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = 0;
				break;
			}
		}
	}
	//망치
	else if (type == 6) {
		if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2) {
			//출력
			switch (GameBoardInfo[arrCur.Y + y][arrCur.X + x])
			{
			default:
				//기타
				break;
			case 0:
				//비어있을 경우 이펙트 출력하고 게임판에 추가하고 스킬이펙트배열에 좌표 저장
				//이펙트 출력
				SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
				drawSkillShape(type, level);
				//게임판에 추가
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = skillList[type - 1][level - 1].effect[nx][ny] + dir;
				break;
			case WALL:
				//벽이면 생성하지 않고 넘기기
				break;
			case CHAINSAW:
				break;
			case NPC:
				//npc면 npcdie하고 넘기기
				NpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case MOVINGRANGENPC:
				//npc와 동일
				RangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case STOPPEDRANGENPC:
				//npc와 동일
				StopRangeNpcDie(arrCur.X + x, arrCur.Y + y);
				IncreaseScore();
				break;
			case NPCBULLET:
				//npc와 동일
				ProjectileExtinction(arrCur.X + x, arrCur.Y + y);
				break;
			case BossNum:
				//이펙트 출력하지 않고 보스 hp 감소
				DecreaseBossHP();
				break;
			case BossSkillEffect:
				//이펙트 출력하지 않고 보스이펙트 제거
				GameBoardInfo[arrCur.Y + y][arrCur.X + x] = 0;
				break;
			}

			//이번 pc 좌표 및 방향 백업
			old_cursor = cursor;
			old_dir = dir;
		}
		else if (TimeCount % Diff.attackSpeed == Diff.attackSpeed / 2 + 1) {
			//이전 이펙트 지우기
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
	//예외 처리
	if (skillList[type - 1][level - 1].effect[nx][ny] == 0) return; //스킬이펙트가 없을 경우 넘기기
	if (cursor.X + x < GBOARD_ORIGIN_X - 1 || cursor.X + x > GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 || cursor.Y + y < GBOARD_ORIGIN_Y || cursor.Y + y > GBOARD_ORIGIN_Y + GBOARD_HEIGHT) return; //커서가 게임판 내부를 벗어나면 넘기기

	COORD arrCur = ConvertCursorIntoArrCur(cursor);

	//이전 근접 이펙트 지우기
	if (GameBoardInfo[arrCur.Y + y][arrCur.X + x] >= 400) {
		GameBoardInfo[arrCur.Y + y][arrCur.X + x] = 0;
		SetCurrentCursorPos(cursor.X + x * 2, cursor.Y + y);
		printf("  ");
	}
}
void AddEffectByDirection(int skillNum, int dir) {
	if (skillNum == 0) return; //스킬이 없으면 리턴

	COORD cursor;
	int type = (skillNum / 100) % 10;
	int level = (skillNum / 10) % 10;

	if (type < 1 || type > 9 || level < 1 || level > 3) return; //예외 처리

	pc.X = PCPoint[0];
	pc.Y = PCPoint[1];

	flag = 0;

	//현재 이펙트 그리기
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

	//디버그
	/*SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 4, 25);
	printf("출력%d", TimeCount);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + (x + 2) * 4, 26 + y);
			printf("%03d,", skillList[type - 1][level - 1].effect[y][x]);
		}
	}*/
}
