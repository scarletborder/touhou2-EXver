#include"menuh.h"
/************************************/
//������gamecmd��2022��11��17��
//��;���ܴ�����Ϸ������������ƶ����������巢�������ļ��ʹ���
//���ߣ�scarletborder
/************************************/

//������Ϸ�������õ���Ԫ��
#if 1
//��ʱ����ʱ����

//��ǰʱ��
extern DWORD currentticktime;

//�ƶ����
extern DWORD oldtickmovetime;

//����������
extern DWORD oldtickshoottime;

//��Ļ���¼��
extern DWORD oldtickbullettime;

//�������
extern DWORD oldtickreaptime;

//��������ټ��
extern DWORD oldtickslowtime;

//��Ϸ���ֿ�ʼǰ��ʱ����������й���������ʱ��
extern DWORD timeflow;

//��һ�η���ؿ����ⵯĻʱ�䣬��8��
//0�̶�Ϊ�ͷ���Ļ��1-7Ϊ���/��¥
extern DWORD oldspbullettime[8];

//���������Ƿ���

//�Ƿ���ǽ������ײ
extern short int iscontinuecrashwall;
extern short int iscrashverwall;

extern int bombhurt;//ը���˺�

extern int reimumove;//�����Ƿ��ƶ����Լ�����

extern int iscontinuecard;//����������Ƭ����
extern int maxiscontinuecard;//������Ϸ�У����������


extern short int stage;//��ǰ�ؿ�

//�ṹ��


//��Ļ
//�е��ṹ
extern struct bullets enemybullet[maxbullet];


//����е��ṹ
extern struct lasers enemylaser[128];


//�з�
extern struct enemycards card[207];
extern struct TOWER tower[32];
extern struct BOSS boss;
extern struct WALL wall[8];

//��Ϸ�и��ֽ����ṹ
extern struct rewards reward[32];


//���λ��͵������Լ��ڳ��ϵ�λ��
extern struct player_status reimu;


//��Ϸ�Ϸ��ļƷְ�
extern struct game_score cscore;


//�����ṹ
//�ܴ�С20*28
extern struct REIMUBULLET YUZHA[maxYUZHA];


//����������ṹ
//�ܴ�С49*49���뾶ΪRADIUS
extern struct yinyang_orb ORB;
#endif


/*****************�ж��������Ƿ���ĳ������������ײ************************
�������ܴ�С49*49���뾶ΪRADIUS
���룺���εĿ����εĸ�, ���ζ�λ��x, ���ζ�λ��y;Բ�����꣬Բ�İ뾶
���������1=YES,0=NO*/
int iscrash(int width, int height, int jx, int jy, double cirx, double ciry, double r)
{
	if (cirx - r >= XSIZE || cirx + r <= 0 || ciry - r >= YSIZE || ciry + r <= 0)
	{
		return 0;
	}

	//������Բ��


	double cx = static_cast<double>(jx) + width / 2;
	double cy = static_cast<double>(jy) + height / 2;
	double hx = width / static_cast<double>(2);
	double hy = height / static_cast<double>(2);

	// ��1����ת������1����
	double vx = cirx - cx;
	double vy = ciry - cy;
	if (vx < 0)
	{
		vx *= -1;
	}
	if (vy < 0)
	{
		vy *= -1;
	}
	// ��2������Բ�������ε���̾���ʸ��
	double ux = vx - hx;
	double uy = vy - hy;
	if (ux < 0 && uy < 0)
	{
		return 1;
	}
	else if (ux < 0 && uy >= 0)
	{
		ux = 0;
		uy = uy;
	}
	else if (ux >= 0 && uy < 0)
	{
		ux = ux;
		uy = 0;
	}
	// ��3��������ƽ����뾶ƽ���Ƚ�
	if (((ux) * (ux)+(uy) * (uy)) <= r * r + 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/***************��������ĳ������������ײ������ƶ�״̬******************/
//���룺��ȫ�֣��������ٶȣ��Ƕȣ���λ�����ꣻ���ֲ��������������Ķ�λ�����꣬��ȣ�����;���������һ������
// ������������25�����߶���35
//���: (ȫ��)����������ٶȣ��Ƕ�
//����360�ж�
void aftercrash(double jjx, double jjy, double width, double height, double jp)
{
	//������Բ��
	double cx = ORB.x;
	double cy = ORB.y;

	//��������
	double jx = jjx + width / 2;
	double jy = jjy + height / 2;

	//�нǵ����Ǻ���
	//����
	int xiangxian = 0;
	if (jx - cx >= 0 && jy - cy >= 0)
		xiangxian = 1;
	else if (jx - cx < 0 && jy - cy > 0)
		xiangxian = 2;
	else if (jx - cx < 0 && jy - cy < 0)
		xiangxian = 3;
	else
		xiangxian = 4;

	double sin_a;
	double cos_a;

	if (jx != cx)
	{
		double tan_a = (jy - cy) / (jx - cx);


		int isfu = 1;//�Ƿ�Ϊ����������-1������1

		if (xiangxian == 2 || xiangxian == 3)
			isfu = (-1);
		cos_a = isfu * sqrt(abs(1 / (1 + tan_a * tan_a)));

		isfu = 1;
		if (xiangxian == 3 || xiangxian == 4)
			isfu = (-1);
		sin_a = isfu * sqrt(abs(1 - 1 / (1 + tan_a * tan_a)));
	}
	else
	{
		if (jy >= cy)
		{
			sin_a = 1;
		}
		else
		{
			sin_a = -1;
		}
		cos_a = 0;
	}
	//���ζ�������Ķ���
	double jpx = -(jp * cos_a);
	double jpy = jp * sin_a;

	//������ԭ�����ֽ�
	double orbcos = cos(ORB.degree);
	double cpx = ORB.speed * orbcos;
	double cpy = ORB.speed * sin(ORB.degree);

	//�����µ��ٶȺͽǶ�
	ORB.speed = sqrt(abs((cpx + jpx) * (cpx + jpx) + (cpy + jpy) * (cpy + jpy)));
	if (cpy + jpy == 0 && cpx + jpx == 0)
	{
		ORB.degree = PI / 2;
		return;
	}

	double newabsdegree;
	if (cpx + jpx != 0)
	{
		newabsdegree = abs(atan((cpy + jpy) / (cpx + jpx)));


		if (jpx + cpx >= 0 && jpy + cpy >= 0)//1
			ORB.degree = 2 * PI - newabsdegree;//4
		else if (jpx + cpx < 0 && jpy + cpy > 0)//2
			ORB.degree = PI + newabsdegree;//3
		else if (jpx + cpx < 0 && jpy + cpy < 0)//3
			ORB.degree = PI - newabsdegree;//2	
		else//4
			ORB.degree = newabsdegree;//1
	}
	else
	{
		if (cpy + jpy >= 0)
		{
			ORB.degree = PI / 2;
		}
		else
		{
			ORB.degree = 3 * PI / 2;
		}
	}

	return;
}
//�ײ�180�ж�
void botcrash(double jjx, double jjy, double width, double height, double jp)
{
	//������Բ��
	double cx = ORB.x;
	double cy = ORB.y;

	//��������
	double jx = jjx + width / 2;
	double jy = jjy + height / 2;

	//�нǵ����Ǻ���
	//����
	int xiangxian = 0;
	if (jx - cx >= 0 && jy - cy >= 0)
		xiangxian = 1;
	else if (jx - cx < 0 && jy - cy > 0)
		xiangxian = 2;
	else if (jx - cx < 0 && jy - cy < 0)
		xiangxian = 2;
	else
		xiangxian = 1;

	double sin_a;
	double cos_a;

	if (jx != cx)
	{
		double tan_a = (jy - cy) / (jx - cx);


		int isfu = 1;//�Ƿ�Ϊ����������-1������1

		if (xiangxian == 2 || xiangxian == 3)
			isfu = (-1);
		cos_a = isfu * sqrt(abs(1 / (1 + tan_a * tan_a)));

		isfu = 1;
		if (xiangxian == 3 || xiangxian == 4)
			isfu = (-1);
		sin_a = isfu * sqrt(abs(1 - 1 / (1 + tan_a * tan_a)));
	}
	else
	{
		if (jy >= cy)
		{
			sin_a = 1;
		}
		else
		{
			sin_a = -1;
		}
		cos_a = 0;
	}
	//���ζ�������Ķ���
	double jpx = -(jp * cos_a);
	double jpy = jp * sin_a;

	//������ԭ�����ֽ�
	double orbcos = cos(ORB.degree);
	double cpx = ORB.speed * orbcos;
	double cpy = ORB.speed * sin(ORB.degree);

	//�����µ��ٶȺͽǶ�
	ORB.speed = sqrt(abs((cpx + jpx) * (cpx + jpx) + (cpy + jpy) * (cpy + jpy)));
	if (cpy + jpy == 0 && cpx + jpx == 0)
	{
		ORB.degree = PI / 2;
		return;
	}

	double newabsdegree;
	if (cpx + jpx != 0)
	{
		newabsdegree = abs(atan((cpy + jpy) / (cpx + jpx)));


		if (jpx + cpx >= 0 && jpy + cpy >= 0)//1
			ORB.degree = 2 * PI - newabsdegree;//4
		else if (jpx + cpx < 0 && jpy + cpy > 0)//2
			ORB.degree = PI + newabsdegree;//3
		else if (jpx + cpx < 0 && jpy + cpy < 0)//3
			ORB.degree = PI - newabsdegree;//2	
		else//4
			ORB.degree = newabsdegree;//1
	}
	else
	{
		if (cpy + jpy >= 0)
		{
			ORB.degree = PI / 2;
		}
		else
		{
			ORB.degree = 3 * PI / 2;
		}
	}

	return;
}




/*******************��������������������˶�״̬�ı�******************/
//����ǽ�ڣ���״��
#if 1
//ˮƽײ�� ���and�ұ�=
void crashvertical()
{
	ORB.degree = 2 * PI - ORB.degree;
}
//��ֱײ�� �ϱ�and�±�
void crashlevel()
{
	ORB.degree = 3 * PI - ORB.degree;
}

#endif



void moveorb()
{
	//����Ƿ������򵽶���ɽǶȺ��ٶȸı�
	for (short int i = 0; i <= maxYUZHA - 1; i++)
	{
		if (YUZHA[i].islive == 0)
		{
			continue;
		}
		if (iscrash(20, 28, YUZHA[i].x, YUZHA[i].y, ORB.x, ORB.y, RADIUS) == 1)
		{
			YUZHA[i].islive = 0;//ԭ�ȵ�����ʧ��
			//���ˣ����и��¼��ټ�ʱ��
			oldtickslowtime = GetTickCount();
			//��һ����ײ����();
			botcrash(YUZHA[i].x, YUZHA[i].y, 20, 28, 30);

			break;
		}
	}

	//����Ƿ񱻻�������ɽǶȺ��ٶȸı�


	//������������Ե�Ƿ�Ӵ�ǽ�ڶ���ɽǶȺ��ٶȸı�
	//ˮƽ
	if (ORB.x - RADIUS + ORB.speed * cos(ORB.degree) < 2 || ORB.x + RADIUS + ORB.speed * cos(ORB.degree) > XSIZE - 2)
	{

		ORB.speed *= 0.8;
		crashlevel();

	}
	//��ֱ
	else if (ORB.y - RADIUS + ORB.speed * sin(ORB.degree) < 52 || ORB.y + RADIUS + ORB.speed * sin(ORB.degree) > YSIZE - 2)
	{
		if (ORB.y + RADIUS + ORB.speed * sin(ORB.degree) > YSIZE - 2)
		{
			iscontinuecard = 0;
		}
		ORB.speed *= 0.8;
		crashvertical();

	}
	//ˮƽǽ��
	for (short int i = 0; i < 8; i++)
	{
		if (wall[i].islive == 1)
		{
			if (iscontinuecrashwall == 0 && wall[i].levver == 0 && (ORB.y + ORB.speed * sin(ORB.degree) + RADIUS <= wall[i].y2 + 2 && ORB.y + ORB.speed * sin(ORB.degree) - RADIUS >= wall[i].y1 - 2) && (wall[i].x1 >= ORB.x + ORB.speed * cos(ORB.degree) - RADIUS - 2 && wall[i].x1 <= ORB.x + ORB.speed * cos(ORB.degree) + RADIUS + 2))
			{
				crashlevel();
				ORB.speed *= 1.3;
				iscontinuecrashwall = 1;
			}
			else if (iscontinuecrashwall == 0 && wall[i].levver == 0 && (ORB.x + ORB.speed * cos(ORB.degree) + RADIUS <= wall[i].x2 + 2 && ORB.x + ORB.speed * cos(ORB.degree) - RADIUS >= wall[i].x1 - 2) && (wall[i].y1 >= ORB.y + ORB.speed * sin(ORB.degree) - RADIUS - 2 && wall[i].y1 <= ORB.y + ORB.speed * sin(ORB.degree) + RADIUS + 2))
			{
				if (ORB.speed < 4)
				{
					ORB.speed = 0;
				}
				crashvertical();
				ORB.speed *= 1.3;
				iscontinuecrashwall = 1;
				iscrashverwall = 1;
			}
			else
			{
				iscontinuecrashwall = 0;
				iscrashverwall = 0;
			}
		}
		else
		{
			break;
		}
	}



	int tempdegree = abs(ORB.degree);
	while (tempdegree > 2 * PI)
	{
		tempdegree -= 2 * PI;
	}

	//����������һ�����µķ��ٶ�
#if 1
	if (ORB.y + ORB.speed * sin(ORB.degree) < YSIZE - RADIUS - 8 && iscrashverwall == 0 && iscontinuecrashwall == 0)
	{
		if (ORB.speed < 3)
		{
			ORB.y += 8;
		}
		if (ORB.speed >= 3 && ORB.speed <= 6)
		{
			ORB.y += 5;
		}
	}
#endif
	//��ʱ�����Ŷ�����ٶ�˥��if(>0)
#if 1
	if (currentticktime - oldtickslowtime >= 5000)
	{
		ORB.speed *= 0.98;
	}
#endif

	//����ٶ�����
	if (ORB.speed > 40)
	{
		ORB.speed = 40;
	}
}



//�ܿ����е�Ļ���ƶ�
void moveallbullet()
{

	//�����ƶ�
	for (int i = 0; i <= maxYUZHA - 1; i++)
	{
		if (YUZHA[i].islive & 1)
		{
			YUZHA[i].y -= 30;

			//��������
			for (int ji = 0; ji < maxbullet; ji++)
			{
				if (enemybullet[ji].islive == 1);//type
				{


					if (enemybullet[ji].isunbreak == 0 && iscrash(20, 28, YUZHA[i].x, YUZHA[i].y, enemybullet[ji].x, enemybullet[ji].y, enemybullet[ji].radius) == 1)
					{
						enemybullet[ji].islive = 0;
						YUZHA[i].islive = 0;
					}


				}
			}
		}


		//�������뿪����������
		if (YUZHA[i].y <= 42)
		{
			YUZHA[i].islive = 0;
		}
	}



	//�������ƶ�
	if (ORB.islive & 1)
	{
		moveorb();
		ORB.x += ORB.speed * cos(ORB.degree);
		ORB.y += ORB.speed * sin(ORB.degree);
	}

	//boss�ƶ�
	if (boss.hp >= 1)
	{
		boss.x += boss.speed * cos(boss.degree);
		boss.y += boss.speed * sin(boss.degree);
	}

	//�е��ƶ�
	for (int bulletid = 0; bulletid < maxbullet; bulletid++)
	{
		if (enemybullet[bulletid].islive & 1)
		{
			enemybullet[bulletid].x += enemybullet[bulletid].speed * cos(enemybullet[bulletid].degree);
			enemybullet[bulletid].y += enemybullet[bulletid].speed * sin(enemybullet[bulletid].degree);

			//�е��Ƴ���Ļ
			if (enemybullet[bulletid].x <= 0 || enemybullet[bulletid].x > XSIZE || enemybullet[bulletid].y > YSIZE)
			{
				enemybullet[bulletid].islive = 0;
			}

			if ((currentticktime - enemybullet[bulletid].oldunbreaktime > 200) && ((enemybullet[bulletid].x - ORB.x) * (enemybullet[bulletid].x - ORB.x) + (enemybullet[bulletid].y - ORB.y) * (enemybullet[bulletid].y - ORB.y) <= (RADIUS + enemybullet[bulletid].radius) * (RADIUS + enemybullet[bulletid].radius)) && enemybullet[bulletid].isunbreak == 0)
			{
				enemybullet[bulletid].islive = 0;
			}

			//���е��Ƿ������
			//�����ж�����뾶��
			if (iscrash(32, 42, reimu.x + 5, reimu.y + 14, enemybullet[bulletid].x, enemybullet[bulletid].y, enemybullet[bulletid].radius) == 1)
			{
				if (currentticktime - reimu.oldunbreaktime >= 2500)
				{
					enemybullet[bulletid].islive = 0;
					enemybullet[bulletid].y = YSIZE + 100;
					reimu.oldunbreaktime = GetTickCount();
					respawn();

				}
			}
		}
		else
		{
			enemybullet[bulletid].y = YSIZE + 100;
		}
	}


	//reward�ƶ�
	moverewarditem();
}





//����������Ƿ�Ӵ����Σ�ʹ������
#if 1
void ishurtreimu()
{
	if (iscrash(32, 42, reimu.x + 5, reimu.y + 14, ORB.x, ORB.y, RADIUS) == 1)
	{
		if (currentticktime - reimu.oldunbreaktime >= 2500)//���Ҳ����޵�ʱ����
		{
			reimu.oldunbreaktime = GetTickCount();
			respawn();
		}
	}
}
#endif

//�ж��Ƿ��˺����˵з���Ƭ
void ishurtcard()
{
	for (int i = 0; i < 207; i++)
	{
		//�жϸÿ�Ƭ�Ƿ��ڳ�
		if (card[i].hp >= 1)
		{
			if (card[i].havebeencrashed == 0)//�������ڿ�Ƭ״̬���ú����½Ӵ���Ƭ
			{
				//�����Ƭ�������������Ӵ������һ��Ѫ
				if (iscrash(40, 50, card[i].x, card[i].y, ORB.x, ORB.y, RADIUS) == 1)
				{
					card[i].havebeencrashed = 1;
					card[i].hp--;
					iscontinuecard++;
					rewardhurtcard(iscontinuecard, stage);
					if (iscontinuecard > maxiscontinuecard)
					{
						maxiscontinuecard = iscontinuecard;
					}

					//���䵯Ļ/�е��������޸ĵ�Ļ����
					//void makebullet(���ݹؿ�)
					short int bulletid = 0;

					switch (stage)
					{
						//���ɶ���е�ע�⣬Ҫ��bulleti + n
					case 1:case 2:
						jexbullet
							initbullet(bulletid++, card[i].x + 20, card[i].y + 25, 10, reimu.x + 21, reimu.y + 50, 3, 0);//type
						break;
					case 3:case 4:
						jexbullet
							initbullet(bulletid++, card[i].x + 20, card[i].y + 25, 10, reimu.x + 21, reimu.y + 50, 3, 0);//type
						jexbullet
							initbullet(bulletid++, card[i].x + 20, card[i].y + 25, 5, reimu.x + 21, reimu.y + 50, 9, 0);//type
						break;
					case 6:case 7:case 8: case 9:
						break;
					}


					//��Ƭ�������꣬�Ƴ�
					if (card[i].hp == 0)
					{
						if (i == 0 && stage == 4)
						{
							initreward(2, card[i].x, card[i].y);
						}

						else if (rand() % 8 == 0)
						{
							initreward(1, card[i].x, card[i].y);
						}

					}
				}

			}
			if (iscrash(40, 50, card[i].x, card[i].y, ORB.x, ORB.y, RADIUS) != 1)//������Ӹÿ�Ƭ���ƿ����ָ��ȴ��Ӵ�״̬
			{

				card[i].havebeencrashed = 0;
			}
		}
	}
}


