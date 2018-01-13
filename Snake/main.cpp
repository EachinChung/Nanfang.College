#include <graphics.h>
#include <conio.h>
#include <time.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define R 114
#define W 119
#define S 115
#define Space 32
#define Turn 224

int len;
int foodX, foodY;
int map[25][25];
void Init();//初始化
void Boundary();//为蛇画一个边界
void Snake();//打印蛇
void Food();//随机食物
void Move(int direction);//移动蛇
void Game();//游戏函数
bool GameOver();//游戏结束

int main() {
	initgraph(420, 420);
	Game();
}

void Init() {
	setbkcolor(WHITE);
	cleardevice();
	Boundary();
	for (int y = 0; y < 25; y++)
		for (int x = 0; x < 25; x++)
			map[x][y] = 0;
	len = 3;
	map[0][0] = 3;
	map[1][0] = 2;
	map[2][0] = 1;
	Snake();
}

void Boundary() {
	setlinecolor(BLACK);
	line(9, 9, 410, 9);
	line(9, 410, 410, 410);
	line(9, 9, 9, 410);
	line(410, 9, 410, 410);
}

void Snake() {
	int x1, y1, x2, y2;
	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 20; x++)
			if (map[x][y] != 0) {
				setfillcolor(BLACK);
				solidrectangle(10 + x * 20, 10 + y * 20, 10 + x * 20 + 19, 10 + y * 20 + 19);
			}
}

void Food() {
	srand((unsigned)time(NULL));
	while (true) {
		foodX = rand() % 20, foodY = rand() % 20;
		if (!map[foodX][foodY]) break;
	}
	setfillcolor(RED);
	solidrectangle(10 + foodX * 20, 10 + foodY * 20, 10 + foodX * 20 + 19, 10 + foodY * 20 + 19);
}

void Move(int direction) {
	int length = len;
	int tail_x, tail_y;

	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 20; x++)
			if (map[x][y] == len) {
				map[x][y] = 0;
				tail_x = x, tail_y = y;
				setfillcolor(WHITE);
				solidrectangle(10 + x * 20, 10 + y * 20, 10 + x * 20 + 19, 10 + y * 20 + 19);
			}

	while (--length) {
		for (int y = 0; y < 20; y++)
			for (int x = 0; x < 20; x++)
				if (map[x][y] == length) map[x][y] = length + 1;
	}

	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 20; x++)
			if (map[x][y] == 2) {
				if (direction == 1) {
					if (map[x][y - 1] > 2) break;
					map[x][y - 1] = 1;
				}
				if (direction == 2) {
					if (map[x][y + 1] > 2) break;
					map[x][y + 1] = 1;
				}
				if (direction == 3) {
					if (map[x - 1][y] > 2) break;
					map[x - 1][y] = 1;
				}
				if (direction == 4) {
					if (map[x + 1][y] > 2) break;
					map[x + 1][y] = 1;
				}
			}

	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 20; x++)
			if (map[x][y] == 1 && x == foodX && y == foodY) {
				len++;
				map[tail_x][tail_y] = len;
				Food();
			}

	Snake();
}

void Game() {
	while (true) {
		int key = 0, direction = 4, speed = 200;
		Init();
		Food();

		while (true) {
			key = _getch();
			if (key == Space) break;
		}

		while (!GameOver()) {
			if (_kbhit()) {
				key = _getch();
				if (key == Turn) {
					if (_kbhit()) key = _getch();
					if (key == UP) if (direction != 2) direction = 1;
					if (key == DOWN) if (direction != 1) direction = 2;
					if (key == LEFT) if (direction != 4) direction = 3;
					if (key == RIGHT) if (direction != 3) direction = 4;
				}
				if (key == R) break;
				if (key == W) if (speed != 20) speed -= 20;
				if (key == S) speed += 20;
			}
			Move(direction);
			Sleep(speed);
		}

		while (true) {
			if (_kbhit()) key = _getch();
			if (key == R) break;
		}
	}
}

bool GameOver() {
	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 20; x++)
			if (map[x][y] == 1)
				return false;
	return true;
}