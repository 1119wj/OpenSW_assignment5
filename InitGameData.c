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



void initSkill() {
	initData_SkillEffectInfo();
	initData_SelectedSkill();

	//게임판 배열에 저장할 스킬 종류별 이펙트 번호 = SKILL_TYPE*100 + SKILL_LEVEL*10 = 110,120,130,210,220,230,...
	//방향을 자리수로 표시: 스킬 110 >>>  왼쪽)111  위쪽)112  오른쪽)113  아래쪽)114
	for (int i = 1; i <= SKILL_TYPE; i++) {
		defineSkill(i);
	}
}

void initData_Variable() {
	//score 초기화
	score = 0;
	finalScore = 0;
	maxExpScore = 500;
	//lastDir 초기화
	lastDir = NORTH;
}

void initDifficulty(int speed, int spawnSpeed, int projectileSpawnSpeed, int attackSpeed, int itemRate) {
	//난이도 설정
	Diff.speed = speed;
	Diff.spawnSpeed = spawnSpeed;
	Diff.projectileSpawnSpeed = projectileSpawnSpeed;
	Diff.attackSpeed = attackSpeed;
	Diff.itemRate = itemRate;
}

void initHP(int hp) {
	//HP 설정
	HP = hp;
	maxHP = HP;
}

void initData_SkillEffectInfo() {
	//skillEffectInfo 초기화
	for (int i = 0; i <= skillTop; i++) {
		skillEffectInfo[i].X = 0, skillEffectInfo[i].Y = 0;
		skillEffectInfo[i].dir = 0;
		skillEffectInfo[i].ef = 0;
		skillEffectInfo[i].level = 0;
		skillEffectInfo[i].type = 0;
	}
	skillTop = -1;
}

void initData_SelectedSkill() {
	//SselectedSkill 초기화
	for (int i = 0; i < 3; i++) selectedSkill[i] = 0;
}

void initData_Time() {
	//TimeCount 초기화
	TimeCount = 0;
}

void init_PCPoint() {
	//PC 위치 중앙으로 초기화
	pc = ConvertCursorIntoArrCur(center);

	if (stage == 3) {
		//보스전 위치
		pc.Y += 8;
	}

	PCPoint[0] = pc.X;
	PCPoint[1] = pc.Y;

	GameBoardInfo[pc.Y][pc.X] = PC;
}

void initData_GameBoardInfo() {
	//GameBoardInfo 초기화
	for (int y = 1; y < GBOARD_HEIGHT; y++) {
		for (int x = 1; x < GBOARD_WIDTH; x++) {
			GameBoardInfo[y][x] = 0;
		}
	}
}

void initBossHP(int hp) {
	//HP 설정
	BossHP = hp;
	BossMaxHP = BossHP;
}

void initBossPoint() {
	BossPoint[0] = 28;
	BossPoint[1] = 10;
}

//NpcInfo, RangeNpcInfo, StopRangeNpcInfo, ProjectileInfo 초기화 함수 작성하기