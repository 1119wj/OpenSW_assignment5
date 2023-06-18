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



void initSkill() {
	initData_SkillEffectInfo();
	initData_SelectedSkill();

	//������ �迭�� ������ ��ų ������ ����Ʈ ��ȣ = SKILL_TYPE*100 + SKILL_LEVEL*10 = 110,120,130,210,220,230,...
	//������ �ڸ����� ǥ��: ��ų 110 >>>  ����)111  ����)112  ������)113  �Ʒ���)114
	for (int i = 1; i <= SKILL_TYPE; i++) {
		defineSkill(i);
	}
}

void initData_Variable() {
	//score �ʱ�ȭ
	score = 0;
	finalScore = 0;
	maxExpScore = 500;
	//lastDir �ʱ�ȭ
	lastDir = NORTH;
}

void initDifficulty(int speed, int spawnSpeed, int projectileSpawnSpeed, int attackSpeed, int itemRate) {
	//���̵� ����
	Diff.speed = speed;
	Diff.spawnSpeed = spawnSpeed;
	Diff.projectileSpawnSpeed = projectileSpawnSpeed;
	Diff.attackSpeed = attackSpeed;
	Diff.itemRate = itemRate;
}

void initHP(int hp) {
	//HP ����
	HP = hp;
	maxHP = HP;
}

void initData_SkillEffectInfo() {
	//skillEffectInfo �ʱ�ȭ
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
	//SselectedSkill �ʱ�ȭ
	for (int i = 0; i < 3; i++) selectedSkill[i] = 0;
}

void initData_Time() {
	//TimeCount �ʱ�ȭ
	TimeCount = 0;
}

void init_PCPoint() {
	//PC ��ġ �߾����� �ʱ�ȭ
	pc = ConvertCursorIntoArrCur(center);

	if (stage == 3) {
		//������ ��ġ
		pc.Y += 8;
	}

	PCPoint[0] = pc.X;
	PCPoint[1] = pc.Y;

	GameBoardInfo[pc.Y][pc.X] = PC;
}

void initData_GameBoardInfo() {
	//GameBoardInfo �ʱ�ȭ
	for (int y = 1; y < GBOARD_HEIGHT; y++) {
		for (int x = 1; x < GBOARD_WIDTH; x++) {
			GameBoardInfo[y][x] = 0;
		}
	}
}

void initBossHP(int hp) {
	//HP ����
	BossHP = hp;
	BossMaxHP = BossHP;
}

void initBossPoint() {
	BossPoint[0] = 28;
	BossPoint[1] = 10;
}

//NpcInfo, RangeNpcInfo, StopRangeNpcInfo, ProjectileInfo �ʱ�ȭ �Լ� �ۼ��ϱ�