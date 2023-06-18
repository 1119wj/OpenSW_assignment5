#pragma once
#define GBOARD_WIDTH 60 //������ ���� ũ��
#define GBOARD_HEIGHT 40 //������ ���� ũ��
#define GBOARD_ORIGIN_X 4 //�⺻ ���� ��� ���� X��ǥ
#define GBOARD_ORIGIN_Y 2 //�⺻ ���� ��� ���� Y��ǥ

//[0 ~ GBOARD_HEIGHT][0 ~ GBOARD_WIDTH]
//�׵θ�: 0, GBOARD_HEIGHT, 0, GBOARD_WIDTH
extern int GameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 1];
extern int score; //����
extern int finalScore; //���� ����
extern int HP; //ü��
extern int maxHP; //�ִ� ü��
extern int stage; //�������� ��ȣ
extern COORD pos_time; //�ð� ��ġ
extern COORD pos_stage; //�������� ��ȣ ��ġ
extern COORD pos_score; //���ھ� ��ġ
extern COORD pos_hp; //ü�� ��ġ
extern COORD pos_skillList; //���� ��ų ��ġ
extern COORD pos_skillSelect; //��ų ����â ��ġ
extern COORD cursor; //Ŀ��
extern int maxExpScore; //�������� �ʿ��� ����ġ ���ھ�

void ClearBoard();
void DrawBoard();
void displayNotice(char* str);
void eraseNotice();
void LevelUp();
void IncreaseScore();
void Debug_GameBoardInfo();
void initPosUI();
void DrawIngameUI();
void drawStage();
void drawTime();
void drawScore();
void drawHP();
void drawSelectedSkillList();
void ClearGameBoard();

void drawSkillShape(int type, int level);
void drawPC();
void erasePC();
void drawNpcShape();
void drawItemShape(int num);
void drawRangeNpcShape();
void drawStopRangeNpcShape();

int GameOver();
void GameClear();
void EraseGameBoard();
void DecreaseHP();
void DecreaseBossHP();
void UpdateScoreboard();
void UpdateMemoryList();