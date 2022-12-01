#pragma once

//��Ϸ���õ��Ľṹ���˵��
//�ṹ������ĳ��ζ�����gamestruct��
/***************�ṹ�嶨��***********************/


//�з����ƿ�Ƭ
struct enemycards
{
	short int x;
	short int y;
	unsigned int hp;//����ֵ&�Ƿ��ڳ�
	unsigned int havebeencrashed :1;//�жϿ�Ƭ���Ƿ�һֱ�������񣬷�ֹһֱ���

};


//�з���¥�ṹ
struct TOWER
{
	short int x;
	short int y;
	unsigned int islive : 1;
};


//���ڶ�����Ϸ�������õ���Ԫ��
//��Ļ
//�е��ṹ
struct bullets
{
	unsigned int islive : 1;//�Ƿ��ڳ�
	double x;//x����
	double y;//y����
	double degree;//ƫ�ƽǶ�
	double speed;//��Ļ�ٶ�
	int radius;//��Ļ�뾶
	int isunbreak;//�Ƿ񲻿�����
	DWORD oldunbreaktime;//����ʱ�䣬������ʱ����������
};


//����е��ṹ
struct lasers
{
	unsigned int islive : 1;//�Ƿ��ڳ�
	double x;//x����
	double y;//y����
	double length;//���ⳤ��
	double moverad;//ƫ�ƽǶ�
	double speed;//�����ٶ�
	int type;//��������
};

//��Ϸ�и��ֽ����ṹ
struct rewards
{
	unsigned int islive :1;//�Ƿ��ڳ�
	unsigned int downorup :1;//��׹�����ϵ�״̬��0Ϊ�£�1Ϊ��
	unsigned int isup : 1;//�Ƿ��Ѿ��ϵ�,1Ϊ�Ѿ���
	short int x;//x����
	short int y;//y����
	unsigned short int type;//����������,1=��,2=B,3=��
};

//���λ��͵������Լ��ڳ��ϵ�λ��
struct player_status
{
	double x;////���ϽǶ�λ��x
	double y;////���ϽǶ�λ��y
	double speed;//���ε��ٶȣ���ͬ�����ٶȲ�ͬ
	unsigned short int type;//����
	DWORD oldunbreaktime;//��һ�α�������/��Ļ�����ʱ��

};

//��Ϸ�Ϸ��ļƷְ�
struct game_score
{
	unsigned int c_score;//��ǰ����
	unsigned int hi_score;//��ʷ��߷�
	short int heartnum;//�л�����
	short int bombnum;//ը������
	short int stagenum;//��ǰ�ؿ���
};

//�����ṹ
//�ܴ�С20*28
struct REIMUBULLET
{
	unsigned int islive :1;//�ж���������Ƿ��ڳ���1�ڳ���0����
	short int x;//���ϽǶ�λ��
	short int y;//���ϽǶ�λ��

};

//����������ṹ
//�ܴ�С49*49���뾶ΪRADIUS
struct yinyang_orb
{
	unsigned int islive : 1;//�ж��������Ƿ��ڳ���1�ڳ���0����
	double x;//��ʵԲ��
	double y;//��ʵԲ��
	double degree;
	double speed;
};


//����boss�ṹ
//Boss������ͳһ����spbullet�ļ�ʱ
//����λ����boss.x,boss.y+���ͣ�switch stage��
struct BOSS
{
	double x;//
	double y;
	unsigned short int speed;
	double degree;
	short int hp;
	unsigned int havebeencrashed : 1;//�ж�boss���Ƿ�һֱ�������񣬷�ֹһֱ���
};


//����ǽwall�ṹ�����ƻ����Ե
//Ԥ�����ؿ��Ϊ5����ɫ
struct WALL
{
	//��ʼ��
	unsigned short int x1;
	unsigned short int y1;

	//��ֹ��
	unsigned short int x2;
	unsigned short int y2;

	unsigned int islive : 1;//�Ƿ��ڳ�
	unsigned int levver : 1;//��lev=0,ver=1
};

