#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


typedef struct Node
{
	int x;
	int y;
	struct Node *pnext;
}NODE;

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 680
#define WIDTH 480

//�һ�ͼƬ�ߴ�
#define pw 86
#define ph 82

//�л�ͼƬ�ߴ�
#define aw 70
#define ah 70

#define boss1w 192
#define boss1h 290


//�л��س��ֵ�y����
#define APStart -ah-20





NODE *p_bullet = NULL;
//MyPlane
NODE *p_MP = NULL;
//AttackPlane
NODE* p_AP = NULL;
//�ӵ�ʱ���
NODE* p_AP2 = NULL;
DWORD b1, b2, b3, b4, b5, b6;

IMAGE i_MP, i_MPS, i_AP, i_APS;
IMAGE i_backeve, i_backxing, i_backduicheng, i_backguan, i_backcontrol, i_backgo;
IMAGE i_boss1_1, i_boss1_1S, i_boss1_2, i_boss1_2S;

//backxing�������ƶ�
int left = (WINDOW_WIDTH / 2 - WIDTH / 2);
//����
int score = 0;
//���ٵл�������
int kill = 0;
//boss�Ƿ����
int boss1show = 0;
//boss1��ͼ����
int boss1image = 0;
int boss1hp = 20;

int line1_x = WINDOW_WIDTH / 2 - 20;
int line1_y = boss1h;
int line2_x = WINDOW_WIDTH / 2 + 20;
int line2_y = boss1h;

//Beamֻ����һ��
int test = 1;
int MP_HP = 1;



void CreateList()
{
	p_MP = (NODE*)malloc(sizeof(NODE));
	p_MP->x = WINDOW_WIDTH / 2 - pw / 2;
	p_MP->y = WINDOW_HEIGHT - 100;
	p_MP->pnext = NULL;


	p_bullet = (NODE*)malloc(sizeof(NODE));
	p_bullet->pnext = NULL;
	b1 = GetTickCount();


	p_AP = (NODE*)malloc(sizeof(NODE));
	srand((unsigned)time(NULL));
	p_AP->x = rand() % (WIDTH - aw) + (WINDOW_WIDTH / 2 - WIDTH / 2);
	p_AP->y = APStart;
	p_AP->pnext = NULL;
	b3 = GetTickCount();

	p_AP2 = (NODE*)malloc(sizeof(NODE));
	p_AP2->x = rand() % (WIDTH - aw) + (WINDOW_WIDTH / 2 - WIDTH / 2);
	p_AP2->y = -350;
	p_AP2->pnext = NULL;
	b5 = GetTickCount();
}

void GameBackInit()
{
	loadimage(&i_MP, L"mp.jpg");
	loadimage(&i_MPS, L"mpbit.jpg");
	loadimage(&i_backeve, L"backeve.jpg");
	loadimage(&i_backxing, L"backtaikong.jpg");
	loadimage(&i_AP, L"AP.jpg", aw, ah);
	loadimage(&i_APS, L"APS.jpg", aw, ah);
	loadimage(&i_backduicheng, L"backduicheng.jpg");
	loadimage(&i_backguan, L"backguan.jpg", WIDTH, WINDOW_HEIGHT);
	loadimage(&i_backcontrol, L"backcontrol.jpg", WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&i_boss1_1, L"boss1_1.jpg");
	loadimage(&i_boss1_1S, L"boss1_1S.jpg");
	loadimage(&i_boss1_2, L"boss1_2.jpg");
	loadimage(&i_boss1_2S, L"boss1_1S.jpg");
	loadimage(&i_backgo, L"Gameover.jpg", WINDOW_WIDTH, WINDOW_HEIGHT);


	putimage(0, 30, &i_backeve);
	Sleep(1000);
	PlaySound(L"baozou.wav", NULL, SND_FILENAME | SND_ASYNC);

	putimage(0, 0, &i_backcontrol);
	outtextxy(600, 540, L"��PRESS�� �������������Ϸ");
	system("pause");

	mciSendString(L"open bgmusic.mp3 alias bg", NULL, 0, NULL);
	mciSendString(L"play bg repeat", NULL, 0, NULL);

	putimage((WINDOW_WIDTH / 2 - WIDTH / 2), 0, WIDTH, WINDOW_HEIGHT, &i_backguan, 0, 0, SRCCOPY);
	putimage(0, 0, (WINDOW_WIDTH / 2 - WIDTH / 2), WINDOW_HEIGHT, &i_backduicheng, 0, 100, SRCCOPY);
	putimage((WINDOW_WIDTH / 2 + WIDTH / 2), 0, (WINDOW_WIDTH / 2 - WIDTH / 2), WINDOW_HEIGHT, &i_backduicheng, 1200 - (WINDOW_WIDTH / 2 - WIDTH / 2), 100, SRCCOPY);
	//������ֵĸ߶�
	int text_h = WINDOW_HEIGHT / 2;
	Sleep(300);
	BeginBatchDraw();
	for (int i = 0; i < text_h; i++)
	{
		clearrectangle((WINDOW_WIDTH / 2 - WIDTH / 2), 0, (WINDOW_WIDTH / 2 + WIDTH / 2), WINDOW_HEIGHT);
		putimage((WINDOW_WIDTH / 2 - WIDTH / 2), 0 - i, WIDTH, text_h, &i_backguan, 0, 0, SRCCOPY);
		putimage((WINDOW_WIDTH / 2 - WIDTH / 2), text_h + i, WIDTH, WINDOW_HEIGHT - (text_h + i), &i_backguan, 0, text_h, SRCCOPY);
		putimage((WINDOW_WIDTH / 2 - WIDTH / 2), text_h - i, WIDTH, 2 * i, &i_backxing, left, text_h - i, SRCCOPY);
		FlushBatchDraw();
		Sleep(5);
	}
	EndBatchDraw();


	Sleep(100);


}


void Boss1show()
{

	p_AP->y = WINDOW_HEIGHT + 100;
	p_AP2->y = WINDOW_HEIGHT + 100;

	if (boss1hp > 14)
	{
		putimage(WINDOW_WIDTH / 2 - boss1w / 2, -boss1h + boss1image, &i_boss1_1S, NOTSRCERASE);
		putimage(WINDOW_WIDTH / 2 - boss1w / 2, -boss1h + boss1image, &i_boss1_1, SRCINVERT);
	}
	else if (boss1hp >= 9 && boss1hp <= 14)
	{

		if (boss1hp % 2 == 0)
		{
			setlinecolor(0x996666);
			setlinestyle(PS_DOT, 3);
			line(line1_x, line1_y, line1_x, WINDOW_HEIGHT);
			line(line2_x, line2_y, line2_x, WINDOW_HEIGHT);

			putimage(WINDOW_WIDTH / 2 - boss1w / 2, -boss1h + boss1image, &i_boss1_2S, NOTSRCERASE);
			putimage(WINDOW_WIDTH / 2 - boss1w / 2, -boss1h + boss1image, &i_boss1_2, SRCINVERT);

		}
		else
		{
			setlinecolor(0xCC6666);
			setlinestyle(PS_DOT, 3);
			line(line1_x, line1_y, line1_x, WINDOW_HEIGHT);
			line(line2_x, line2_y, line2_x, WINDOW_HEIGHT);


			putimage(WINDOW_WIDTH / 2 - boss1w / 2, -boss1h + boss1image, &i_boss1_1S, NOTSRCERASE);
			putimage(WINDOW_WIDTH / 2 - boss1w / 2, -boss1h + boss1image, &i_boss1_1, SRCINVERT);
		}


	}
	else
	{

		if (test == 1)
		{
			PlaySound(L"Beam.wav", NULL, SND_FILENAME | SND_ASYNC);
			test++;
		}
		setlinecolor(0xFF6666);
		setlinestyle(PS_DASH, 5);
		line(line1_x, line1_y, line1_x, WINDOW_HEIGHT);
		line(line2_x, line2_y, line2_x, WINDOW_HEIGHT);
		line(WINDOW_WIDTH / 2 - boss1w / 2, boss1h - 90, 482, boss1h + 50);
		line(WINDOW_WIDTH / 2 + boss1w / 2, boss1h - 90, 542, boss1h + 50);
		putimage(WINDOW_WIDTH / 2 - boss1w / 2, -boss1h + boss1image, &i_boss1_2S, NOTSRCERASE);
		putimage(WINDOW_WIDTH / 2 - boss1w / 2, -boss1h + boss1image, &i_boss1_2, SRCINVERT);
		if ((boss1hp != 8) && (p_MP->x - line1_x) > -pw && (p_MP->x - line2_x) < 0 && (p_MP->y - line1_y) > -ph)			MP_HP = 0;
	}


	if (boss1image <= boss1h)	boss1image += 2;

}

void AddNode(int flag)
{
	//��巨�����µڶ���λ��
	if (flag == 0)
	{
		NODE* p_new = (NODE*)malloc(sizeof(NODE));

		p_new->x = p_MP->x + 35;
		p_new->y = p_MP->y - 45;

		p_new->pnext = p_bullet->pnext;
		p_bullet->pnext = p_new;
	}
}



int main()
{
	//create a window
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	setfillcolor(0xFF9999);

	GameBackInit();

	char key;
	CreateList();
	//������ͼ

	clock_t a = clock();

	int flag = 0;  //�Ƿ����Զ�������0Ϊδ������1Ϊ����

	BeginBatchDraw();
	while (1)
	{
		clock_t b = clock();

		//�廭��,Ҫ��Ȼ�ͳ��ص��Ĳ�Ӱ��
		cleardevice();



		putimage((WINDOW_WIDTH / 2 - WIDTH / 2), 0, WIDTH, WINDOW_HEIGHT, &i_backxing, left, 0, SRCCOPY);
		putimage(0, 0, (WINDOW_WIDTH / 2 - WIDTH / 2), WINDOW_HEIGHT, &i_backduicheng, 0, 100, SRCCOPY);
		putimage((WINDOW_WIDTH / 2 + WIDTH / 2), 0, (WINDOW_WIDTH / 2 - WIDTH / 2), WINDOW_HEIGHT, &i_backduicheng, 1200 - (WINDOW_WIDTH / 2 - WIDTH / 2), 100, SRCCOPY);


		putimage(p_MP->x, p_MP->y, &i_MPS, NOTSRCERASE);
		putimage(p_MP->x, p_MP->y, &i_MP, SRCINVERT);
		putimage(p_AP->x, p_AP->y, &i_APS, NOTSRCERASE);
		putimage(p_AP->x, p_AP->y, &i_AP, SRCINVERT);
		putimage(p_AP2->x, p_AP2->y, &i_APS, NOTSRCERASE);
		putimage(p_AP2->x, p_AP2->y, &i_AP, SRCINVERT);

		outtextxy(80, 200, L"��Y��ʼ�Զ�����");

		//MP��λʱ�䷢���ӵ�������
		b2 = GetTickCount();
		//���ܵ��ڣ���ƫ��
		if (b2 - b1 >= 600)
		{
			AddNode(0);
			b1 = b2;
		}




		//�ҷ�ս���ӵ�����
		NODE* P = p_bullet->pnext;


		while (P != NULL)
		{
			if (boss1show == 0)
			{

				//ȷ���л�����λ�ò�����ԭλ��
				int mid;
				//10���ӵ����,������ӵ�����Ҳ�㣬Ҫ��Ȼ̫���ˣ����ұ���-3�������-7
				if ((P->y - p_AP->y) < ah && (P->y - p_AP->y) >= 0 && (P->x - p_AP->x) < aw - 3 && (P->x - p_AP->x) >= -7)
				{
					P->y = APStart - 100;
					P = P->pnext;
					p_AP->y = APStart;
					kill++;

					PlaySound(L"Bomb.wav", NULL, SND_FILENAME | SND_ASYNC);
					while (1)
					{
						mid = rand() % (WIDTH - aw) + (WINDOW_WIDTH / 2 - WIDTH / 2);
						if (abs(mid - p_AP->x) > aw)
						{
							p_AP->x = mid;
							break;
						}
					}


				}
				else if ((P->y - p_AP2->y) < ah && (P->y - p_AP2->y) >= 0 && (P->x - p_AP2->x) < aw - 3 && (P->x - p_AP2->x) >= -7)
				{
					P->y = APStart - 100;
					P = P->pnext;
					p_AP2->y = APStart;
					kill++;

					while (1)
					{
						mid = rand() % (WIDTH - aw) + (WINDOW_WIDTH / 2 - WIDTH / 2);
						if (abs(mid - p_AP2->x) > aw)
						{
							p_AP2->x = mid;
							break;
						}
					}
					PlaySound(L"Bomb.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				else
				{
					fillroundrect(P->x, P->y, P->x + 10, P->y + 35, 10, 30);
					P->y -= 5;
					P = P->pnext;
				}
			}
			else if (boss1show == 1)
			{
				if (boss1image > boss1h)
				{
					if ((P->y) < boss1h && (P->y) >= 0 && (P->x - (WINDOW_WIDTH / 2 - boss1w / 2)) < boss1w - 3 && (P->x - (WINDOW_WIDTH / 2 - boss1w / 2)) >= -7)
					{
						P->y = APStart - 100;
						P = P->pnext;
						boss1hp--;
						if (boss1hp > 9 || boss1hp < 7)	PlaySound(L"Bomb.wav", NULL, SND_FILENAME | SND_ASYNC);
					}
					else
					{
						fillroundrect(P->x, P->y, P->x + 10, P->y - 35, 10, 30);
						P->y -= 10;
						P = P->pnext;
					}

					TCHAR s_boss1hp[100];
					_stprintf(s_boss1hp, _T("��Boss��HP��%d"), boss1hp);
					outtextxy((WINDOW_WIDTH / 2 + WIDTH / 2) + 45, 200, s_boss1hp);

					if (boss1hp <= 0)
					{
						boss1show = 0;
						kill += 50;
					}
				}
				else
				{
					fillroundrect(P->x, P->y, P->x + 10, P->y + 35, 10, 30);
					P->y -= 5;
					P = P->pnext;
				}
			}
		}





		//AP���е��ٶ�
		b4 = GetTickCount();
		//���ܵ��ڣ���ƫ��
		if (b4 - b3 >= 60)
		{
			if (p_AP->y < WINDOW_HEIGHT)
			{
				p_AP->y += 5;
			}
			else
			{
				p_AP->y = 0;
				p_AP->x = rand() % (WIDTH - aw) + (WINDOW_WIDTH / 2 - WIDTH / 2);
			}
			b3 = b4;
		}




		//AP2���е��ٶ�
		b6 = GetTickCount();
		//���ܵ��ڣ���ƫ��
		if (b6 - b5 >= 60)
		{
			if (p_AP2->y < WINDOW_HEIGHT)
			{
				p_AP2->y += 5;
			}
			else
			{
				p_AP2->y = 0;
				p_AP2->x = rand() % (WIDTH - aw) + (WINDOW_WIDTH / 2 - WIDTH / 2);
			}
			b5 = b6;
		}





		if (kill == 10 && boss1hp > 0) boss1show = 1;




		if (boss1show == 1)
		{
			Boss1show();
		}




		if ((p_MP->x - p_AP->x) > -pw && (p_MP->x - p_AP->x) < pw && (p_MP->y - p_AP->y) > -ph && (p_MP->y - p_AP->y) < ph)			MP_HP = 0;
		else if ((p_MP->x - p_AP2->x) > -pw && (p_MP->x - p_AP2->x) < pw && (p_MP->y - p_AP2->y) > -ph && (p_MP->y - p_AP2->y) < ph)	MP_HP = 0;
		else if (boss1show == 1 && boss1image > boss1h && (p_MP->x - (WINDOW_WIDTH / 2 - boss1w / 2)) > -pw && (p_MP->x - (WINDOW_WIDTH / 2 + boss1w / 2)) < pw && p_MP->y < boss1h)		MP_HP = 0;

		if (MP_HP == 0 || boss1hp == 0)
		{
			mciSendString(L"close bg", NULL, 0, NULL);
			mciSendString(L"open bggo.mp3 alias bg", NULL, 0, NULL);
			mciSendString(L"play bg repeat", NULL, 0, NULL);
			putimage(0, 0, &i_backgo, SRCCOPY);
			outtextxy(430, 540, L"3����Զ��˳�");
			EndBatchDraw();
			Sleep(3000);
			closegraph();
			return 0;
		}


		TCHAR s_score[100];
		_stprintf(s_score, _T("��ķ���:%d"), kill);
		outtextxy((WINDOW_WIDTH / 2 + WIDTH / 2) + 50, WINDOW_HEIGHT / 2, s_score);




		FlushBatchDraw();


		//�ӵ������ٶ��Լ������ӳٵ�
		Sleep(15);


		/*
		//_kbhit()��һ���ӳ�
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case 72://��
				p_MP->y -= 5;
				break;
			case 80://��
				p_MP->y += 5;
				break;
			case 75://��
				p_MP->x -= 5;
				left -= 5;
				break;
			case 77://��
				p_MP->x += 5;
				left += 5;
				break;
			}
		}
		*/


		if (GetAsyncKeyState(0x59))
		{
			flag = (flag + 1) % 2;
		}

		if (flag == 1)
		{
			int sel = 0; //ѡ��Ŀ��
			int dis; //Ŀ�����һ���λ��
			int i,j;

			if (boss1show != 1)
			{
				if ((p_AP->y) > (p_AP2->y) && p_AP->y > 30)
				{
					sel = 1;
				}
				else if ((p_AP->y) < (p_AP2->y) && p_AP2->y > 30)
				{
					sel = 2;
				}

				if (sel == 1)
				{
					dis = (p_AP->x) - (p_MP->x);
					if (dis < 0)
					{
						//if ((b - a) % 5 == 0)
						//{
							//for (i = 0; i >= dis; i -= 5)
							//{
								p_MP->x -= 2;
								left -= 2;
								if (p_MP->x < (WINDOW_WIDTH / 2 - WIDTH / 2))
									p_MP->x = (WINDOW_WIDTH / 2 - WIDTH / 2);
								if (p_MP->x > (WINDOW_WIDTH / 2 + WIDTH / 2 - pw))
									p_MP->x = (WINDOW_WIDTH / 2 + WIDTH / 2 - pw);
								if (left < 0)
									left = 0;
								if (left > 1280 - WIDTH)
									left = 1280 - WIDTH;
								FlushBatchDraw();
							//}
						//}
					}
					else if (dis > 0)
					{
						//if ((b - a) % 5 == 0)
						//{
							//for (i = 0; i <= dis; i += 5)
							//{
								p_MP->x += 2;
								left += 2;
								if (p_MP->x < (WINDOW_WIDTH / 2 - WIDTH / 2))
									p_MP->x = (WINDOW_WIDTH / 2 - WIDTH / 2);
								if (p_MP->x > (WINDOW_WIDTH / 2 + WIDTH / 2 - pw))
									p_MP->x = (WINDOW_WIDTH / 2 + WIDTH / 2 - pw);
								if (left < 0)
									left = 0;
								if (left > 1280 - WIDTH)
									left = 1280 - WIDTH;
								FlushBatchDraw();
							//}
						//}
					}
				}
				else if (sel == 2)
				{
					dis = (p_AP2->x) - (p_MP->x);
					if (dis < 0)
					{
						//if ((b - a) % 5 == 0)
						//{
							//for (i = 0; i >= dis; i -= 5)
							//{
								p_MP->x -= 2;
								left -= 2;
								if (p_MP->x < (WINDOW_WIDTH / 2 - WIDTH / 2))
									p_MP->x = (WINDOW_WIDTH / 2 - WIDTH / 2);
								if (p_MP->x > (WINDOW_WIDTH / 2 + WIDTH / 2 - pw))
									p_MP->x = (WINDOW_WIDTH / 2 + WIDTH / 2 - pw);
								if (left < 0)
									left = 0;
								if (left > 1280 - WIDTH)
									left = 1280 - WIDTH;
								FlushBatchDraw();
							//}
						//}
					}
					else if (dis > 0)
					{
						//if ((b - a) % 5 == 0)
						//{
							//for (i = 0; i <= dis; i += 5)
							//{
								p_MP->x += 2;
								left += 2;
								if (p_MP->x < (WINDOW_WIDTH / 2 - WIDTH / 2))
									p_MP->x = (WINDOW_WIDTH / 2 - WIDTH / 2);
								if (p_MP->x > (WINDOW_WIDTH / 2 + WIDTH / 2 - pw))
									p_MP->x = (WINDOW_WIDTH / 2 + WIDTH / 2 - pw);
								if (left < 0)
									left = 0;
								if (left > 1280 - WIDTH)
									left = 1280 - WIDTH;
								FlushBatchDraw();
							//}
						//}
					}
				}
				else
				{
					p_MP->x = p_MP->x;
				}
			}
			else if (boss1show == 1)
			{
				dis = (WINDOW_WIDTH / 2 - 115) - p_MP->x;
				if (dis > 0)
				{
					p_MP->x += 2;
					left += 2;
					if (p_MP->x < (WINDOW_WIDTH / 2 - WIDTH / 2))
						p_MP->x = (WINDOW_WIDTH / 2 - WIDTH / 2);
					if (p_MP->x > (WINDOW_WIDTH / 2 + WIDTH / 2 - pw))
						p_MP->x = (WINDOW_WIDTH / 2 + WIDTH / 2 - pw);
					if (left < 0)
						left = 0;
					if (left > 1280 - WIDTH)
						left = 1280 - WIDTH;
					FlushBatchDraw();
				}
				else if (dis < 0)
				{
					p_MP->x -= 2;
					left -= 2;
					if (p_MP->x < (WINDOW_WIDTH / 2 - WIDTH / 2))
						p_MP->x = (WINDOW_WIDTH / 2 - WIDTH / 2);
					if (p_MP->x > (WINDOW_WIDTH / 2 + WIDTH / 2 - pw))
						p_MP->x = (WINDOW_WIDTH / 2 + WIDTH / 2 - pw);
					if (left < 0)
						left = 0;
					if (left > 1280 - WIDTH)
						left = 1280 - WIDTH;
					FlushBatchDraw();
				}
			}
		}
		else
		{
			if (GetAsyncKeyState(VK_UP))
				p_MP->y -= 5;
			else if (GetAsyncKeyState(VK_DOWN))
				p_MP->y += 5;
			else if (GetAsyncKeyState(VK_LEFT))
			{
				p_MP->x -= 5;
				left -= 5;
			}
			else if (GetAsyncKeyState(VK_RIGHT))
			{
				p_MP->x += 5;
				left += 5;
			}
		}
			

		if (p_MP->x < (WINDOW_WIDTH / 2 - WIDTH / 2))
			p_MP->x = (WINDOW_WIDTH / 2 - WIDTH / 2);
		if (p_MP->x > (WINDOW_WIDTH / 2 + WIDTH / 2 - pw))
			p_MP->x = (WINDOW_WIDTH / 2 + WIDTH / 2 - pw);
		if (p_MP->y < 0)
			p_MP->y = 0;
		if (p_MP->y > WINDOW_HEIGHT - ph)
			p_MP->y = WINDOW_HEIGHT - ph;


		if (left < 0)
			left = 0;
		if (left > 1280 - WIDTH)
			left = 1280 - WIDTH;

	}

	EndBatchDraw();
	closegraph();
	return 0;
}
