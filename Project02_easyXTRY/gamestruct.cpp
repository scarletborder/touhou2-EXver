#include"menuh.h"


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
