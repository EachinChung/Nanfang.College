#include "minesweeper.h"

DWORD WINAPI Timing(LPVOID lpParameter) {
	//线程函数，建立一个计时器
	while (true) {
		s++;
		if (s == 60) {
			s = 0;
			if (win || fail)
				return 0L;
			TimeUI(Time);
			m++;
		}
		if (m == 60) {
			m = 0;
			if (win || fail)
				return 0L;
			TimeUI(Time);
			h++;
		}
		_stprintf_s(Time, _T("%d:%d:%d"), h, m, s);
		Sleep(1000);
		if (win || fail)
			return 0L;
		TimeUI(Time);
	}
}

void TimeUI(TCHAR Time[]) {
	//打印时间
	LOGFONT Typeface;
	settextcolor(LIGHTGRAY);
	setfillcolor(BLACK);
	setbkmode(OPAQUE);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 10;
	Typeface.lfWeight = FW_DEMIBOLD;
	settextstyle(&Typeface);
	if (MapSize == 1) {
		solidrectangle(100, 197, 148, 215);
		outtextxy(100, 197, Time);
	}
	if (MapSize == 2) {
		solidrectangle(240, 337, 288, 355);
		outtextxy(240, 337, Time);
	}
	if (MapSize == 3) {
		solidrectangle(520, 337, 568, 355);
		outtextxy(520, 337, Time);
	}
}

void InitBomb(int SquareX, int SquareY) {
	int bomb_max, boomX, boomY;
	//随机种子为当前系统时间
	srand((unsigned)time(NULL));
	if (MapSize == 1)
		bomb_max = 81;
	if (MapSize == 2)
		bomb_max = 256;
	if (MapSize == 3)
		bomb_max = 480;

	if (bomb < bomb_max / 2) {
		for (int i = 0; i < bomb; i++) {
			boomX = rand() % square_x, boomY = rand() % square_y;
			//开局第一次点击方格 不设雷
			if (SquareX = boomX && SquareY == boomY) {
				i--; continue;
			}
			//防止设雷重复
			if (Square[boomX][boomY] == 1) {
				i--; continue;
			}
			Square[boomX][boomY] = 1;
		}
	}
	else {
		for (int Y = 0; Y < 16; Y++)
			for (int X = 0; X < 30; X++)
				Square[X][Y] = 1;
		Square[SquareX][SquareY] = 0;
		for (int i = 1; i < bomb_max - bomb; i++) {
			boomX = rand() % square_x, boomY = rand() % square_y;
			//防止设雷重复
			if (Square[boomX][boomY] == 0) {
				i--; continue;
			}
			Square[boomX][boomY] = 0;
		}
	}
}

int Calculation(int SquareX, int SquareY) {
	int boom = 0;

	//计算方格周围的雷数 并返回
	if (SquareY != 0)
		if (Square[SquareX][SquareY - 1] == 1 || Square[SquareX][SquareY - 1] == 4 || Square[SquareX][SquareY - 1] == 6) boom++;
	if (SquareY != max_y)
		if (Square[SquareX][SquareY + 1] == 1 || Square[SquareX][SquareY + 1] == 4 || Square[SquareX][SquareY - 1] == 6) boom++;

	if (SquareX != max_x) {
		if (Square[SquareX + 1][SquareY] == 1 || Square[SquareX + 1][SquareY] == 4 || Square[SquareX][SquareY - 1] == 6) boom++;
		if (SquareY != 0)
			if (Square[SquareX + 1][SquareY - 1] == 1 || Square[SquareX + 1][SquareY - 1] == 4 || Square[SquareX][SquareY - 1] == 6) boom++;
		if (SquareY != max_y)
			if (Square[SquareX + 1][SquareY + 1] == 1 || Square[SquareX + 1][SquareY + 1] == 4 || Square[SquareX][SquareY - 1] == 6) boom++;
	}

	if (SquareX != 0) {
		if (Square[SquareX - 1][SquareY] == 1 || Square[SquareX - 1][SquareY] == 4 || Square[SquareX][SquareY - 1] == 6) boom++;
		if (SquareY != 0)
			if (Square[SquareX - 1][SquareY - 1] == 1 || Square[SquareX - 1][SquareY - 1] == 4 || Square[SquareX][SquareY - 1] == 6) boom++;
		if (SquareY != max_y)
			if (Square[SquareX - 1][SquareY + 1] == 1 || Square[SquareX - 1][SquareY + 1] == 4 || Square[SquareX][SquareY - 1] == 6) boom++;
	}

	return boom;
}

void Game() {
	FlagUI();
	int x, y;
	bool begin = false;
	win = false, fail = false;
	MOUSEMSG Msg;

	while (true) {
		Msg = GetMouseMsg();
		//计算鼠标的方格坐标
		x = (Msg.x - 10) / 20, y = (Msg.y - 10) / 20;

		switch (Msg.uMsg) {
		case WM_MOUSEMOVE:
			if (MapSize == 1) {
				if (8 < Msg.x && Msg.x < 27 && 194 < Msg.y && Msg.y < 209) {
					setlinecolor(DARKGRAY);
					MenuUI();
				}
				else {
					setlinecolor(LIGHTGRAY);
					MenuUI();
				} break;
			}
			else {
				if (8 < Msg.x && Msg.x < 27 && 337 < Msg.y && Msg.y < 352) {
					setlinecolor(DARKGRAY);
					MenuUI();
				}
				else {
					setlinecolor(LIGHTGRAY);
					MenuUI();
				} break;
			}

		case WM_LBUTTONDOWN:
			if (MapSize == 1) {
				if (8 < Msg.x && Msg.x < 27 && 197 < Msg.y && Msg.y < 212) {
					bool mainInterface = Menu();
					if (mainInterface) {
						fail = true;
						return;
					}
					break;
				}
			}
			else {
				if (8 < Msg.x && Msg.x < 27 && 337 < Msg.y && Msg.y < 352) {
					bool mainInterface = Menu();
					if (mainInterface) {
						fail = true;
						return;
					}
					break;
				}
			}
			//判断是否在边界内点击
			if (x < 0 || x>max_x || y < 0 || y>max_y) break;
			//如果是第一次点击，初始化地雷
			if (!begin) {
				InitBomb(x, y);
				s = 0, m = 0, h = 0;
				//开启计时器线程
				HANDLE thread = CreateThread(NULL, 0, Timing, NULL, 0, NULL);
				CloseHandle(thread);
				begin = true;
			}
			if (Square[x][y] == 2 || Square[x][y] == 3 || Square[x][y] == 4 || Square[x][y] == 5 || Square[x][y] == 6) break;
			if (Square[x][y] == 1) {
				fail = true; break;
			}
			Open(x, y); break;
		case WM_RBUTTONUP:
			if (!begin) break;
			if (x < 0 || x>max_x || y < 0 || y>max_y) break;
			if (Square[x][y] == 2) break;
			if (Square[x][y] == 5 || Square[x][y] == 6) {
				CancelTab(x, y); break;
			}
			if (Square[x][y] == 3 || Square[x][y] == 4) {
				Uncertain(x, y);
				FlagUI();
				break;
			}
			Tab(x, y);
			FlagUI();
			break;
		}

		int get = 0;

		//判断游戏是否胜利：方块全部翻开且地雷全部标记，无标记空方块
		for (int boomY = 0; boomY < square_y; boomY++)
			for (int boomX = 0; boomX < square_x; boomX++) {
				if (Square[boomX][boomY] == 4 || Square[boomX][boomY] == 6) get++;
				if (get == bomb) win = true;
			}
		for (int boomY = 0; boomY < square_y; boomY++)
			for (int boomX = 0; boomX < square_x; boomX++) {
				if (Square[boomX][boomY] == 0 || Square[boomX][boomY] == 1 || Square[boomX][boomY] == 3) win = false;
				if (Square[boomX][boomY] == 5) win = false;
			}
		if (win) {
			Win();
			return;
		}
		if (fail) {
			GameOver();
			return;
		}
	}
}

int Flag() {
	int flag = 0;
	for (int boomY = 0; boomY < square_y; boomY++)
		for (int boomX = 0; boomX < square_x; boomX++)
			if (Square[boomX][boomY] == 3 || Square[boomX][boomY] == 4) flag++;
	return bomb - flag;
}

void FlagUI() {
	LOGFONT Typeface;
	settextcolor(LIGHTGRAY);
	setfillcolor(BLACK);
	setbkmode(OPAQUE);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 10;
	Typeface.lfWeight = FW_DEMIBOLD;
	settextstyle(&Typeface);

	TCHAR flag[4];
	int number = Flag();
	_stprintf_s(flag, _T("%d"), number);
	if (MapSize == 1) {
		solidrectangle(160, 197, 199, 215);
		outtextxy(160, 197, flag);
	}
	if (MapSize == 2) {
		solidrectangle(300, 337, 339, 355);
		outtextxy(300, 337, flag);
	}
	if (MapSize == 3) {
		solidrectangle(580, 337, 619, 355);
		outtextxy(580, 337, flag);
	}
}

void MenuUI() {
	//画三条横线，作为菜单按钮
	if (MapSize == 1) {
		line(10, 199, 25, 199);
		line(10, 200, 25, 200);
		line(10, 204, 25, 204);
		line(10, 205, 25, 205);
		line(10, 209, 25, 209);
		line(10, 210, 25, 210);
	}
	else {
		line(10, 339, 25, 339);
		line(10, 340, 25, 340);
		line(10, 344, 25, 344);
		line(10, 345, 25, 345);
		line(10, 349, 25, 349);
		line(10, 350, 25, 350);
	}
}

bool Menu() {
	bool mainInterface = false;

	if (MapSize == 1) {
		setfillcolor(LIGHTGRAY);
		solidrectangle(10, 195, 85, 215);
		setlinecolor(BLACK);
		MenuUI();
	}
	else {
		setfillcolor(LIGHTGRAY);
		solidrectangle(10, 335, 85, 355);
		setlinecolor(BLACK);
		MenuUI();
	}

	LOGFONT Typeface;
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 8;
	Typeface.lfWeight = 0;
	settextstyle(&Typeface);
	TCHAR esc[] = _T("主菜单");
	if (MapSize == 1)
		outtextxy(34, 198, esc);
	else
		outtextxy(34, 338, esc);;

	MOUSEMSG Msg;
	while (true) {
		Msg = GetMouseMsg();
		switch (Msg.uMsg) {
		case WM_MOUSEMOVE:
			if (MapSize == 1) {
				if (10 < Msg.x && Msg.x < 85 && 195 < Msg.y && Msg.y < 215)
					break;
			}
			else {
				if (10 < Msg.x && Msg.x < 85 && 335 < Msg.y && Msg.y < 355)
					break;
			}
		case WM_LBUTTONDOWN:
			if (MapSize == 1) {
				setfillcolor(BLACK);
				solidrectangle(10, 195, 85, 215);
				setlinecolor(LIGHTGRAY);
				MenuUI();
				if (30 < Msg.x && Msg.x < 85 && 195 < Msg.y && Msg.y < 215)
					return mainInterface = true;
				return mainInterface = false;
			}
			else {
				setfillcolor(BLACK);
				solidrectangle(10, 335, 85, 355);
				setlinecolor(LIGHTGRAY);
				MenuUI();
				if (30 < Msg.x && Msg.x < 85 && 335 < Msg.y && Msg.y < 355)
					return mainInterface = true;
				return mainInterface = false;
			}
		}
	}
}

void Open(int SquareX, int SquareY) {
	setfillcolor(DARKGRAY);
	solidrectangle(10 + SquareX * 20, 10 + SquareY * 20, 28 + SquareX * 20, 28 + SquareY * 20);
	Square[SquareX][SquareY] = 2;

	TCHAR s[2];
	LOGFONT Typeface;
	int boom = Calculation(SquareX, SquareY);
	_stprintf_s(s, _T("%d"), boom);

	if (boom != 0) {
		//周围不同地雷数，不同颜色
		if (boom == 1) settextcolor(GREEN);
		if (boom == 2) settextcolor(BLUE);
		if (boom == 3) settextcolor(MAGENTA);
		if (boom == 4) settextcolor(YELLOW);
		if (boom > 4) settextcolor(RED);
		setbkmode(TRANSPARENT);
		gettextstyle(&Typeface);
		Typeface.lfHeight = 17;
		Typeface.lfWeight = FW_DEMIBOLD;
		settextstyle(&Typeface);
		outtextxy(15 + SquareX * 20, 12 + SquareY * 20, s);
	}
	else {
		//若周围地雷数为零，向八个方向递归展开
		if (SquareX > 0 && Square[SquareX - 1][SquareY] == 0)
			Open(SquareX - 1, SquareY);
		if (SquareX > 0 && SquareY > 0 && Square[SquareX - 1][SquareY - 1] == 0)
			Open(SquareX - 1, SquareY - 1);
		if (SquareX > 0 && SquareY < max_y && Square[SquareX - 1][SquareY + 1] == 0)
			Open(SquareX - 1, SquareY + 1);
		if (SquareX < max_x && Square[SquareX + 1][SquareY] == 0)
			Open(SquareX + 1, SquareY);
		if (SquareX < max_x && SquareY > 0 && Square[SquareX + 1][SquareY - 1] == 0)
			Open(SquareX + 1, SquareY - 1);
		if (SquareX < max_x && SquareY < max_y && Square[SquareX + 1][SquareY + 1] == 0)
			Open(SquareX + 1, SquareY + 1);
		if (SquareY > 0 && Square[SquareX][SquareY - 1] == 0)
			Open(SquareX, SquareY - 1);
		if (SquareY < max_y && Square[SquareX][SquareY + 1] == 0)
			Open(SquareX, SquareY + 1);
	}
}

void Tab(int SquareX, int SquareY) {
	//标记旗子
	setlinecolor(RED);
	line(17 + SquareX * 20, 14 + SquareY * 20, 17 + SquareX * 20, 25 + SquareY * 20);
	setfillcolor(RED);
	solidrectangle(17 + SquareX * 20, 14 + SquareY * 20, 22 + SquareX * 20, 19 + SquareY * 20);
	if (Square[SquareX][SquareY] == 1)
		Square[SquareX][SquareY] = 4;
	else Square[SquareX][SquareY] = 3;
}

void Uncertain(int SquareX, int SquareY) {
	//标记问号
	LOGFONT Typeface;
	setbkmode(TRANSPARENT);
	settextcolor(DARKGRAY);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 17;
	Typeface.lfWeight = FW_DEMIBOLD;
	settextstyle(&Typeface);
	TCHAR Title[] = _T("？");

	setfillcolor(LIGHTGRAY);
	solidrectangle(10 + SquareX * 20, 10 + SquareY * 20, 28 + SquareX * 20, 28 + SquareY * 20);
	outtextxy(13 + SquareX * 20, 12 + SquareY * 20, Title);
	if (Square[SquareX][SquareY] == 4)
		Square[SquareX][SquareY] = 6;
	else Square[SquareX][SquareY] = 5;
}

void CancelTab(int SquareX, int SquareY) {
	//取消标记
	setfillcolor(LIGHTGRAY);
	solidrectangle(10 + SquareX * 20, 10 + SquareY * 20, 28 + SquareX * 20, 28 + SquareY * 20);
	if (Square[SquareX][SquareY] == 6)
		Square[SquareX][SquareY] = 1;
	else Square[SquareX][SquareY] = 0;
}

void SmilingFace(int boomX, int boomY) {
	//画笑脸：填充圆，和像素点
	setlinecolor(YELLOW);
	setfillcolor(YELLOW);
	fillcircle(19 + boomX * 20, 19 + boomY * 20, 8);
	setfillcolor(BLACK);
	fillcircle(16 + boomX * 20, 17 + boomY * 20, 2);
	fillcircle(22 + boomX * 20, 17 + boomY * 20, 2);
	putpixel(15 + boomX * 20, 22 + boomY * 20, BLACK);
	putpixel(15 + boomX * 20, 23 + boomY * 20, BLACK);
	putpixel(16 + boomX * 20, 23 + boomY * 20, BLACK);
	putpixel(17 + boomX * 20, 24 + boomY * 20, BLACK);
	putpixel(18 + boomX * 20, 24 + boomY * 20, BLACK);
	putpixel(19 + boomX * 20, 24 + boomY * 20, BLACK);
	putpixel(20 + boomX * 20, 24 + boomY * 20, BLACK);
	putpixel(21 + boomX * 20, 24 + boomY * 20, BLACK);
	putpixel(22 + boomX * 20, 23 + boomY * 20, BLACK);
	putpixel(23 + boomX * 20, 23 + boomY * 20, BLACK);
	putpixel(23 + boomX * 20, 22 + boomY * 20, BLACK);
	Sleep(100);
}

void Win() {
	//游戏结束后，已标记地雷以笑脸状态一一显示
	for (int boomY = 0; boomY < square_y; boomY++)
		for (int boomX = 0; boomX < square_x; boomX++)
			if (Square[boomX][boomY] == 4 || Square[boomX][boomY] == 6) SmilingFace(boomX, boomY);
	if (!custom)
		Settlement();
	GameEsc();
}

void GameOver() {
	for (int boomY = 0; boomY < square_y; boomY++)
		for (int boomX = 0; boomX < square_x; boomX++)
			if (Square[boomX][boomY] == 1) {
				setfillcolor(BLACK);
				solidrectangle(10 + boomX * 20, 10 + boomY * 20, 28 + boomX * 20, 28 + boomY * 20);
				setfillcolor(RED);
				solidcircle(19 + boomX * 20, 19 + boomY * 20, 8);
			}
	for (int boomY = 0; boomY < square_y; boomY++)
		for (int boomX = 0; boomX < square_x; boomX++)
			if (Square[boomX][boomY] == 4 || Square[boomX][boomY] == 6) SmilingFace(boomX, boomY);
	GameEsc();
}

void GameEsc() {
	if (MapSize == 1) {
		setfillcolor(LIGHTGRAY);
		solidrectangle(10, 195, 85, 215);
		setlinecolor(BLACK);
		MenuUI();
	}
	else {
		setfillcolor(LIGHTGRAY);
		solidrectangle(10, 335, 85, 355);
		setlinecolor(BLACK);
		MenuUI();
	}

	LOGFONT Typeface;
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	gettextstyle(&Typeface);
	Typeface.lfHeight = 8;
	Typeface.lfWeight = 0;
	settextstyle(&Typeface);
	TCHAR esc[] = _T("主菜单");
	if (MapSize == 1)
		outtextxy(34, 198, esc);
	else
		outtextxy(34, 338, esc);;

	MOUSEMSG Msg;
	while (true) {
		Msg = GetMouseMsg();
		switch (Msg.uMsg) {
		case WM_MOUSEMOVE:
			if (MapSize == 1) {
				if (10 < Msg.x && Msg.x < 85 && 195 < Msg.y && Msg.y < 215) {
					settextcolor(DARKGRAY);
					setlinecolor(DARKGRAY);
					outtextxy(34, 198, esc);
					MenuUI();
				}
				else {
					settextcolor(BLACK);
					setlinecolor(BLACK);
					outtextxy(34, 198, esc);
					MenuUI();
				}
			}
			else {
				if (10 < Msg.x && Msg.x < 85 && 335 < Msg.y && Msg.y < 355) {
					settextcolor(DARKGRAY);
					setlinecolor(DARKGRAY);
					outtextxy(34, 338, esc);
					MenuUI();
				}
				else {
					settextcolor(BLACK);
					setlinecolor(BLACK);
					outtextxy(34, 338, esc);
					MenuUI();
				}
			} break;
		case WM_LBUTTONDOWN:
			if (MapSize == 1) {
				if (10 < Msg.x && Msg.x < 85 && 195 < Msg.y && Msg.y < 215)
					return;
			}
			else {
				if (10 < Msg.x && Msg.x < 85 && 335 < Msg.y && Msg.y < 355)
					return;
			}
		}
	}
}

int Fraction(int node) {
	//计算时间 化为秒
	int fraction = record[node].hour * 360 + record[node].minute * 60 + record[node].second;
	return fraction;
}

void Sort() {
	//对排行榜结构体 冒泡
	LIST cache;
	int n = 10;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			if (Fraction(j) > Fraction(j + 1)) {
				cache = record[j];
				record[j] = record[j + 1];
				record[j + 1] = cache;
			}
		}
	}
	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n - i; j++) {
			if (!Fraction(j)) {
				cache = record[j];
				record[j] = record[j + 1];
				record[j + 1] = cache;
			}
		}
	}
}

void Settlement() {
	TimeUI(Time);
	char file[50];
	if (MapSize == 1)
		strcpy_s(file, "RankingList_simple.txt");
	if (MapSize == 2)
		strcpy_s(file, "RankingList_commonly.txt");
	if (MapSize == 3)
		strcpy_s(file, "RankingList_difficulty.txt");

	record[10].second = s;
	record[10].minute = m;
	record[10].hour = h;

	//读取排行榜信息
	FILE *RankingList;
	fopen_s(&RankingList, file, "a+");
	for (int i = 0; i < 10; i++)
		fscanf_s(RankingList, "%d:%d:%d",
			&record[i].hour,
			&record[i].minute,
			&record[i].second);
	fclose(RankingList);

	Sort();

	//只保留前十
	fopen_s(&RankingList, file, "w");
	for (int i = 0; i < 10; i++) {
		fprintf(RankingList, "%d:%d:%d\n",
			record[i].hour,
			record[i].minute,
			record[i].second);
	}
	fclose(RankingList);

	//清空缓存数据
	for (int i = 0; i < 11; i++) {
		record[i].second = 0;
		record[i].minute = 0;
		record[i].hour = 0;
	}
}