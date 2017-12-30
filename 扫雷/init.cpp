#include "minesweeper.h"

int bomb;
int flag;
int MapSize;
int max_x, max_y;
int square_x, square_y;
int s = 0, m = 0, h = 0;
//Square 0 ����Ϊ��ʼ״̬
//Square 1 ����Ϊ��ʼ����
//Square 2 ����Ϊ����״̬
//Square 3 ����Ϊ���״̬
//Square 4 ����Ϊ�������
//Square 5 ����Ϊ����ʺ�
//Square 6 ����Ϊ�����ʺ�
int Square[30][16] = { 0 };
bool custom, TwoInterface, fail = false, win = false;
LIST record[11] = { 0 };
TCHAR Time[50];

void Init() {
	initgraph(768, 480);
	cleardevice();

	LOGFONT Typeface;
	gettextstyle(&Typeface);
	Typeface.lfHeight = 140;
	_tcscpy_s(Typeface.lfFaceName, _T("΢���ź�"));
	Typeface.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&Typeface);
	TCHAR Title[] = _T("ɨ��");
	outtextxy(60, 90, Title);

	gettextstyle(&Typeface);
	Typeface.lfHeight = 30;
	settextstyle(&Typeface);
	TCHAR title[] = _T("Minesweeper");
	outtextxy(60, 240, title);

	settextcolor(LIGHTGRAY);
	gettextstyle(&Typeface);
	_tcscpy_s(Typeface.lfFaceName, _T("����"));
	Typeface.lfHeight = 15;
	settextstyle(&Typeface);
	TCHAR Version[] = _T("Version��2.0");
	outtextxy(3, 462, Version);

	//��ʼ���˵�����
	settextcolor(WHITE);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 40;
	_tcscpy_s(Typeface.lfFaceName, _T("΢���ź�"));
	settextstyle(&Typeface);
}

void MainInterface() {
	//��ӡ������Ϸ ���а� ����
	TCHAR newgame[] = _T("����Ϸ");
	TCHAR rankinglist[] = _T("���а�");
	TCHAR about[] = _T("����");
	outtextxy(590, 260, newgame);
	outtextxy(590, 320, rankinglist);
	outtextxy(617, 380, about);

	//ѡ������Ϸ ���а� ����
	MOUSEMSG Msg;
	while (true) {
		Msg = GetMouseMsg();
		switch (Msg.uMsg) {
		case WM_MOUSEMOVE:
			if (590 < Msg.x && Msg.x < 680 && 260 < Msg.y && Msg.y < 300) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 260, newgame);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 260, newgame);
			}
			if (590 < Msg.x && Msg.x < 680 && 320 < Msg.y && Msg.y < 360) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 320, rankinglist);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 320, rankinglist);
			}
			if (617 < Msg.x && Msg.x < 680 && 380 < Msg.y && Msg.y < 420) {
				settextcolor(LIGHTGRAY);
				outtextxy(617, 380, about);
			}
			else {
				settextcolor(WHITE);
				outtextxy(617, 380, about);
			}
			break;

		case WM_LBUTTONDOWN:
			if (590 < Msg.x && Msg.x < 680 && 260 < Msg.y && Msg.y < 300) {
				NewGame();
				//����Ϸ ����
				//���´�ӡ������Ϸ ���а� ����
				settextcolor(WHITE);
				outtextxy(590, 260, newgame);
				outtextxy(590, 320, rankinglist);
				outtextxy(617, 380, about);
				break;
			}
			if (590 < Msg.x && Msg.x < 680 && 320 < Msg.y && Msg.y < 360) {
				RankingList();//���а� ����
				settextcolor(WHITE);
				outtextxy(590, 260, newgame);
				outtextxy(590, 320, rankinglist);
				outtextxy(617, 380, about);
				break;
			}
			if (617 < Msg.x && Msg.x < 680 && 380 < Msg.y && Msg.y < 420) {
				About();//���� ����
				settextcolor(WHITE);
				outtextxy(590, 260, newgame);
				outtextxy(590, 320, rankinglist);
				outtextxy(617, 380, about);
				break;
			}
		}
	}
}

void NewGame() {
	//��� �Ұ����Ļ
	setfillcolor(BLACK);
	solidrectangle(384, 0, 768, 480);

	LOGFONT Typeface;
	settextcolor(WHITE);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 40;
	settextstyle(&Typeface);
	TCHAR simple[] = _T("��");
	TCHAR commonly[] = _T("һ��");
	TCHAR difficulty[] = _T("����");
	TCHAR custom[] = _T("�Զ���");
	TCHAR esc[] = _T("����");
	outtextxy(590, 140, simple);
	outtextxy(590, 200, commonly);
	outtextxy(590, 260, difficulty);
	outtextxy(590, 320, custom);
	outtextxy(590, 380, esc);

	MOUSEMSG Msg;
	while (true) {
		Msg = GetMouseMsg();
		switch (Msg.uMsg) {
		case WM_MOUSEMOVE:
			if (590 < Msg.x && Msg.x < 653 && 140 < Msg.y && Msg.y < 180) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 140, simple);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 140, simple);
			}
			if (590 < Msg.x && Msg.x < 653 && 200 < Msg.y && Msg.y < 240) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 200, commonly);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 200, commonly);
			}
			if (590 < Msg.x && Msg.x < 653 && 260 < Msg.y && Msg.y < 300) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 260, difficulty);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 260, difficulty);
			}
			if (590 < Msg.x && Msg.x < 680 && 320 < Msg.y && Msg.y < 360) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 320, custom);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 320, custom);
			}
			if (590 < Msg.x && Msg.x < 653 && 380 < Msg.y && Msg.y < 420) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 380, esc);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 380, esc);
			}
			break;

		case WM_LBUTTONDOWN:
			if (590 < Msg.x && Msg.x < 653 && 140 < Msg.y && Msg.y < 180) {
				Simple();
				Game();
				Init();
				return;
			}
			if (590 < Msg.x && Msg.x < 653 && 200 < Msg.y && Msg.y < 240) {
				Commonly();
				Game();
				Init();
				return;
			}
			if (590 < Msg.x && Msg.x < 653 && 260 < Msg.y && Msg.y < 300) {
				Difficulty();
				Game();
				Init();
				return;
			}
			if (590 < Msg.x && Msg.x < 680 && 320 < Msg.y && Msg.y < 360) {
				TwoInterface = false;
				Custom();
				settextcolor(WHITE);
				outtextxy(590, 140, simple);
				outtextxy(590, 200, commonly);
				outtextxy(590, 260, difficulty);
				outtextxy(590, 320, custom);
				outtextxy(590, 380, esc);
				if (TwoInterface) {
					setfillcolor(BLACK);
					solidrectangle(384, 0, 768, 480);
					return;
				}
				break;
			}
			if (590 < Msg.x && Msg.x < 653 && 380 < Msg.y && Msg.y < 420) {
				setfillcolor(BLACK);
				solidrectangle(384, 0, 768, 480);
				return;
			}
		}
	}
}

void Custom() {
	setfillcolor(BLACK);
	solidrectangle(384, 0, 768, 480);

	LOGFONT Typeface;
	settextcolor(WHITE);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 40;
	settextstyle(&Typeface);
	TCHAR simple[] = _T("��");
	TCHAR commonly[] = _T("һ��");
	TCHAR difficulty[] = _T("����");
	TCHAR esc[] = _T("����");
	outtextxy(590, 200, simple);
	outtextxy(590, 260, commonly);
	outtextxy(590, 320, difficulty);
	outtextxy(590, 380, esc);

	MOUSEMSG Msg;
	while (true) {
		Msg = GetMouseMsg();
		switch (Msg.uMsg) {
		case WM_MOUSEMOVE:
			if (590 < Msg.x && Msg.x < 653 && 200 < Msg.y && Msg.y < 240) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 200, simple);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 200, simple);
			}
			if (590 < Msg.x && Msg.x < 653 && 260 < Msg.y && Msg.y < 300) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 260, commonly);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 260, commonly);
			}
			if (590 < Msg.x && Msg.x < 680 && 320 < Msg.y && Msg.y < 360) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 320, difficulty);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 320, difficulty);
			}
			if (590 < Msg.x && Msg.x < 653 && 380 < Msg.y && Msg.y < 420) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 380, esc);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 380, esc);
			}
			break;

		case WM_LBUTTONDOWN:
			if (590 < Msg.x && Msg.x < 653 && 200 < Msg.y && Msg.y < 240) {
				TwoInterface = true;
				custom = true;
				Simple();
				Game();
				Init();
				custom = false;
				return;
			}
			if (590 < Msg.x && Msg.x < 653 && 260 < Msg.y && Msg.y < 300) {
				TwoInterface = true;
				custom = true;
				Commonly();
				Game();
				Init();
				custom = false;
				return;
			}
			if (590 < Msg.x && Msg.x < 680 && 320 < Msg.y && Msg.y < 360) {
				TwoInterface = true;
				custom = true;
				Difficulty();
				Game();
				Init();
				custom = false;
				return;
			}
			if (590 < Msg.x && Msg.x < 653 && 380 < Msg.y && Msg.y < 420) {
				setfillcolor(BLACK);
				solidrectangle(384, 0, 768, 480);
				return;
			}
		}
	}
}

void RankingList() {
	setfillcolor(BLACK);
	solidrectangle(384, 0, 768, 480);

	LOGFONT Typeface;
	settextcolor(WHITE);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 40;
	settextstyle(&Typeface);
	TCHAR simple[] = _T("��");
	TCHAR commonly[] = _T("һ��");
	TCHAR difficulty[] = _T("����");
	TCHAR esc[] = _T("����");
	outtextxy(590, 200, simple);
	outtextxy(590, 260, commonly);
	outtextxy(590, 320, difficulty);
	outtextxy(590, 380, esc);

	MOUSEMSG Msg;
	while (true) {
		Msg = GetMouseMsg();
		switch (Msg.uMsg) {
		case WM_MOUSEMOVE:
			if (590 < Msg.x && Msg.x < 653 && 200 < Msg.y && Msg.y < 240) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 200, simple);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 200, simple);
			}
			if (590 < Msg.x && Msg.x < 653 && 260 < Msg.y && Msg.y < 300) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 260, commonly);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 260, commonly);
			}
			if (590 < Msg.x && Msg.x < 680 && 320 < Msg.y && Msg.y < 360) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 320, difficulty);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 320, difficulty);
			}
			if (590 < Msg.x && Msg.x < 653 && 380 < Msg.y && Msg.y < 420) {
				settextcolor(LIGHTGRAY);
				outtextxy(590, 380, esc);
			}
			else {
				settextcolor(WHITE);
				outtextxy(590, 380, esc);
			}
			break;

		case WM_LBUTTONDOWN:
			if (590 < Msg.x && Msg.x < 653 && 200 < Msg.y && Msg.y < 240) {
				MapSize = 1;
				RankingListMenu();
				settextcolor(WHITE);
				outtextxy(590, 200, simple);
				outtextxy(590, 260, commonly);
				outtextxy(590, 320, difficulty);
				outtextxy(590, 380, esc);
				break;
			}
			if (590 < Msg.x && Msg.x < 653 && 260 < Msg.y && Msg.y < 300) {
				MapSize = 2;
				RankingListMenu();
				settextcolor(WHITE);
				outtextxy(590, 200, simple);
				outtextxy(590, 260, commonly);
				outtextxy(590, 320, difficulty);
				outtextxy(590, 380, esc);
				break;
			}
			if (590 < Msg.x && Msg.x < 680 && 320 < Msg.y && Msg.y < 360) {
				MapSize = 3;
				RankingListMenu();
				settextcolor(WHITE);
				outtextxy(590, 200, simple);
				outtextxy(590, 260, commonly);
				outtextxy(590, 320, difficulty);
				outtextxy(590, 380, esc);
				break;
			}
			if (590 < Msg.x && Msg.x < 653 && 380 < Msg.y && Msg.y < 420) {
				setfillcolor(BLACK);
				solidrectangle(384, 0, 768, 480);
				return;
			}
		}
	}
}

int Input() {
	//����������ĶԻ���
	bool inputfalse = false;
	TCHAR number[10];
	while (true) {
		if (!inputfalse) {
			if (MapSize == 1)
				InputBox(number, 10, _T("�����������(0<n<81)"));
			if (MapSize == 2)
				InputBox(number, 10, _T("�����������(0<n<256)"));
			if (MapSize == 3)
				InputBox(number, 10, _T("�����������(0<n<480)"));
		}
		else {
			if (MapSize == 1)
				InputBox(number, 10, _T("�������ע�⣺������(0<n<81)"));
			if (MapSize == 2)
				InputBox(number, 10, _T("�������ע�⣺������(0<n<256)"));
			if (MapSize == 3)
				InputBox(number, 10, _T("�������ע�⣺������(0<n<480)"));
		}
		int answer = _ttoi(number);
		if (MapSize == 1) {
			if (0 < answer && answer < 81)
				return answer;
		}
		else inputfalse = true;
		if (MapSize == 2) {
			if (0 < answer && answer < 256)
				return answer;
		}
		else inputfalse = true;
		if (MapSize == 3) {
			if (0 < answer && answer < 486)
				return answer;
		}
		else inputfalse = true;
	}
}

void InitMap() {
	//��ʼ����ͼ����
	for (int Y = 0; Y < 16; Y++)
		for (int X = 0; X < 30; X++)
			Square[X][Y] = 0;
}

void Simple() {
	//���ѶȵĻ���
	InitMap();
	MapSize = 1;
	if (custom)
		bomb = Input();
	else
		bomb = 10;
	closegraph();
	initgraph(200, 220);

	TCHAR text[] = _T("0:0:0");
	TimeUI(text);

	square_x = 9, square_y = 9;
	max_x = square_x - 1, max_y = square_y - 1;
	//����㿪ʼ���ʵ�ͼ���߽��square_x, square_y��һ

	setlinecolor(LIGHTGRAY);
	MenuUI();

	setfillcolor(LIGHTGRAY);
	int x1, y1, x2, y2;
	for (int x = 0; x < square_x; x++)
		for (int y = 0; y < square_y; y++) {
			x1 = 10 + 20 * x;
			y1 = 10 + 20 * y;
			x2 = x1 + 18;
			y2 = y1 + 18;
			solidrectangle(x1, y1, x2, y2);
		}
}

void Commonly() {
	//һ���ѶȵĻ���
	InitMap();
	MapSize = 2;
	if (custom)
		bomb = Input();
	else
		bomb = 40;
	closegraph();
	initgraph(340, 360);

	TCHAR text[] = _T("0:0:0");
	TimeUI(text);

	square_x = 16, square_y = 16;
	max_x = square_x - 1, max_y = square_y - 1;

	setlinecolor(LIGHTGRAY);
	MenuUI();

	setfillcolor(LIGHTGRAY);
	int x1, y1, x2, y2;
	for (int x = 0; x < square_x; x++)
		for (int y = 0; y < square_y; y++) {
			x1 = 10 + 20 * x;
			y1 = 10 + 20 * y;
			x2 = x1 + 18;
			y2 = y1 + 18;
			solidrectangle(x1, y1, x2, y2);
		}
}

void Difficulty() {
	//�����ѶȵĻ���
	InitMap();
	MapSize = 3;
	if (custom)
		bomb = Input();
	else
		bomb = 99;
	closegraph();
	initgraph(620, 360);

	TCHAR text[] = _T("0:0:0");
	TimeUI(text);

	square_x = 30, square_y = 16;
	max_x = square_x - 1, max_y = square_y - 1;

	setlinecolor(LIGHTGRAY);
	MenuUI();

	setfillcolor(LIGHTGRAY);
	int x1, y1, x2, y2;
	for (int x = 0; x < square_x; x++)
		for (int y = 0; y < square_y; y++) {
			x1 = 10 + 20 * x;
			y1 = 10 + 20 * y;
			x2 = x1 + 18;
			y2 = y1 + 18;
			solidrectangle(x1, y1, x2, y2);
		}
}

void RankingListMenu() {
	char file[50];
	setfillcolor(BLACK);
	solidrectangle(384, 0, 768, 480);

	if (MapSize == 1)
		strcpy_s(file, "RankingList_simple.txt");
	if (MapSize == 2)
		strcpy_s(file, "RankingList_commonly.txt");
	if (MapSize == 3)
		strcpy_s(file, "RankingList_difficulty.txt");

	//��ȡ���а���Ϣ
	FILE *RankingList;
	fopen_s(&RankingList, file, "a+");
	for (int i = 0; i < 10; i++)
		fscanf_s(RankingList, "%d:%d:%d",
			&record[i].hour,
			&record[i].minute,
			&record[i].second);
	fclose(RankingList);

	LOGFONT Typeface;
	settextcolor(LIGHTGRAY);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 25;
	settextstyle(&Typeface);

	for (int i = 0; i < 10; i++)
		PrintRankingList(i);

	//��ջ�������
	for (int i = 0; i < 11; i++) {
		record[i].second = 0;
		record[i].minute = 0;
		record[i].hour = 0;
	}

	settextcolor(WHITE);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 40;
	settextstyle(&Typeface);
	TCHAR esc[] = _T("����");
	outtextxy(620, 400, esc);

	MOUSEMSG Msg;
	while (true) {
		Msg = GetMouseMsg();
		switch (Msg.uMsg) {
		case WM_MOUSEMOVE:
			if (620 < Msg.x && Msg.x < 683 && 400 < Msg.y && Msg.y < 440) {
				settextcolor(LIGHTGRAY);
				outtextxy(620, 400, esc);
			}
			else {
				settextcolor(WHITE);
				outtextxy(620, 400, esc);
			}
			break;

		case WM_LBUTTONDOWN:
			if (620 < Msg.x && Msg.x < 683 && 400 < Msg.y && Msg.y < 440) {
				setfillcolor(BLACK);
				solidrectangle(384, 0, 768, 480);
				gettextstyle(&Typeface);
				Typeface.lfHeight = 40;
				settextstyle(&Typeface);
				return;
			}
		}
	}
}

void PrintRankingList(int node) {
	//��ӡ���а�
	TCHAR rankinglist[50];
	_stprintf_s(rankinglist, _T("%d.    %d  :  %d  :  %d"), node + 1,
		record[node].hour,
		record[node].minute,
		record[node].second);
	outtextxy(520, 120 + node * 27, rankinglist);
}

void About() {
	setfillcolor(BLACK);
	solidrectangle(384, 0, 768, 480);

	LOGFONT Typeface;
	settextcolor(LIGHTGRAY);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 30;
	settextstyle(&Typeface);
	RECT Text = { 480,115,768, 480 };
	drawtext(_T("v2.0\r1.ȫ�µ���Ϸ����\r2.���ӳ�����\r�м����߼���\r�Զ����Ѷ�ѡ��\r4.��ʱ����\r6.���а���\r\r"), &Text, DT_WORDBREAK);
	TCHAR By[] = _T("EachinChung");
	outtextxy(550, 340, By);

	settextcolor(WHITE);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 40;
	settextstyle(&Typeface);
	TCHAR esc[] = _T("����");
	outtextxy(560, 400, esc);

	//���ذ�ť
	MOUSEMSG Msg;
	while (true) {
		Msg = GetMouseMsg();
		switch (Msg.uMsg) {
		case WM_MOUSEMOVE:
			if (560 < Msg.x && Msg.x < 623 && 400 < Msg.y && Msg.y < 440) {
				settextcolor(LIGHTGRAY);
				outtextxy(560, 400, esc);
			}
			else {
				settextcolor(WHITE);
				outtextxy(560, 400, esc);
			}
			break;

		case WM_LBUTTONDOWN:
			if (560 < Msg.x && Msg.x < 623 && 400 < Msg.y && Msg.y < 440) {
				setfillcolor(BLACK);
				solidrectangle(384, 0, 768, 480);
				gettextstyle(&Typeface);
				Typeface.lfHeight = 40;
				settextstyle(&Typeface);
				return;
			}
		}
	}
}
