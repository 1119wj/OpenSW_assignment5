#pragma once
#define SKILL_LEVEL 3 //��ų ���� ũ��
#define SKILL_TYPE 9 //��ų ���� ����
#define EFFECT_SIZE 4 //����Ʈ �迭 ũ��
#define SKILL_LEN 16 //��ų ���ڿ� ����
#define SELECT_SIZE 3 //��ų ���� ����

#define EAST 1 //����: ������
#define NORTH 2 //����: ����
#define WEST 3 //����: ����
#define SOUTH 4 //����: �Ʒ���

typedef struct skill {
	char name[SKILL_LEN]; //��ų �̸�
	char e[3]; //��ų ����Ʈ = ����� Ư������
	//int effect[EFFECT_SIZE][EFFECT_SIZE]; //��ų ����Ʈ �迭
	int effect[EFFECT_SIZE][EFFECT_SIZE];
	int type;
	int level;
} skill;

typedef struct skillEffect {
	int X, Y;
	int type;
	int level;
	int dir;
	int ef;
} skillEffect;

extern skill skillList[SKILL_TYPE][SKILL_LEVEL];
extern int selectedSkill[SELECT_SIZE];
extern skillEffect skillEffectInfo[GBOARD_HEIGHT * GBOARD_WIDTH];
extern int skillTop;
extern int flag;
extern COORD old_cursor;
extern int old_dir;

void sub_AddEffectByDirection(COORD cursor, int type, int level, int x, int y, int nx, int ny, int dir);
void erase_AddEffectByDirection(COORD cursor, int type, int level, int x, int y, int nx, int ny, int dir);
void AddEffectByDirection(int skillNum, int dir); //skillList[type-1][level-1]�� PC ���� dir(EAST, NORTH, WEST, SOUTH)�� ���� �߰�
void RemoveSkillEffect(int idx);
void SkillEffectMove();
void UpdateSkillEffect(int idx);
void SelectNewSkill();
void defineSkill(int type); //��ų1 ����; �⺻ ���� = �������� �߻� ����; �̿ϼ�