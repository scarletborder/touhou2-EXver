#include"menuh.h"
/**************************************/
//������gamecmd.cpp
//�״ζ�����Ϸ���õ���Ԫ��
//�Ӷ��������ļ������ⲿ����
/**************************************/


//��Ļ
//�е��ṹ
struct bullets enemybullet[maxbullet] = { 0 };

//����е��ṹ
struct lasers enemylaser[128] = { 0 };

//�����ṹ
//�ܴ�С20*28
struct REIMUBULLET YUZHA[maxYUZHA] = { 0 };


//����������ṹ
//�ܴ�С49*49���뾶ΪRADIUS
struct yinyang_orb ORB = { 0 };


//����
//�з����ƿ�Ƭ
struct enemycards card[207] = { 0 };
//boss
struct BOSS boss = { 0 };
//��¥
struct TOWER tower[32] = { 0 };
//ǽ��
struct WALL wall[8] = { 0 };


//��Ϸ�и��ֽ����ṹ
struct rewards reward[32] = { 0 };


//���λ��͵������Լ��ڳ��ϵ�λ��
struct player_status reimu = { 310,445,10,0 };


//��Ϸ�Ϸ��ļƷְ�
struct game_score cscore = { 0,0,0,0,1 };

unsigned int iscontinuepoint = 0;


//�����Ƿ��ƶ����Լ�����
int reimumove = 0; 
short int stage = 1; 
int maxiscontinuecard = 0;

int ctimeflow = 0; 
char hiscore[15];

DWORD currentticktime;//��ǰʱ��

short int hasplaycharge = 0;

unsigned short int punishmode = 0;
int punishtime = 0;

int iscontinuecard = 0;//����������Ƭ����

//�ƶ����
DWORD oldtickmovetime;

//����������
DWORD oldtickshoottime;

//��Ļ���¼��
DWORD oldtickbullettime;

//�������
DWORD oldtickreaptime;

//��������ټ��
DWORD oldtickslowtime;

//��Ϸ���ֿ�ʼǰ��ʱ����������й���������ʱ��
DWORD timeflow;

//��һ�η���ؿ����ⵯĻʱ�䣬��8��
//0�̶�Ϊ�ͷ���Ļ��1-7Ϊ���/��¥
DWORD oldspbullettime[8];

//wall
short int iscontinuecrashwall;
short int iscrashverwall;

int bombhurt = 1;//ը���˺�

