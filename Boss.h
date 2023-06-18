#pragma once
#define BossNum 7
#define BossSkillEffect 6

extern int bossFlag; //���� ���� ��Ÿ��
extern int random;
extern int XX1, YY1, XX2, YY2; //�������� ������ ,�����ʾƷ� ��ǥ
extern int x3; //���ý�ų����Ҷ����
extern int y3; //���ý�ų����Ҷ����

//���� ��ǥ
extern int BossPoint[2];

//���� �� 7
extern int BossModel[7][7];

//���� ��ų 6
extern int BossSkillModel[3][3];

//���� HP
extern int BossHP;
extern int BossMaxHP;

void ShowBoss();
void DeleteBoss();
void ShowBossSkill_Rect(int X1, int Y1, int X2, int Y2); //������ų1-�׸��
void ShowBossSkill_RectOrbit(int X1, int Y1, int X2, int Y2); //������ų1-�׸������
void ShowBossSkill_Waffle_Left(int x1); //������ų2-���ʿ���
void ShowBossSkill_Waffle_Up(int y1); //������ų2-���ʿ���
void ShowBossSkill_Waffle_Right(int x1); //������ų2-�����ʿ���
void ShowBossSkill_Waffle_Down(int y1); //������ų2-�Ʒ��ʿ���
void ShowBossSkill_WaffleOrbit();//������ų2-���ñ���
void BossMove();
void ShowBossSkill_Circle(); //�⺻��ų-��������(�����߿� ���� ���°�)
void DeleteBossSkill();
void DeleteBossSkill2();