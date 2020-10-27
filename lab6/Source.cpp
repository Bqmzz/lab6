#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y); 
	setcolor(2, 4); 
	printf(" <-0-> ");
}
void erase_ship(int x, int y) {
	gotoxy(x, y); 
	setcolor(0, 0); 
	printf("       ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); 
	setcolor(7, 5); 
	printf("^");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); 
	setcolor(0, 0); 
	printf(" ");
}
void draw_enemy(int x, int y) {
	gotoxy(x, y);
	setcolor(7, 0);
	printf("*");
}
void clear_enemy(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void draw_score(int score) 
{
	gotoxy(110, 0);
	setcolor(14, 5);
	printf("%d", score);
}
void erase_score() 
{
	gotoxy(110, 0);
	setcolor(0, 10);
	printf(" ");
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];
}

int main()
{
	setcursor(0);
	char ch = '.';
	int x = 38, y = 20;
	int bx, by;
	int i, px, py;
	int bullet = 0;
	int score = 0;
	draw_score(score);
	srand(time(NULL));

	for (i = 0; i < 20; i++) {
		px = rand() % 70 + 10;
		py = rand() % 5 + 2;
		draw_enemy(px, py);
	}
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { erase_ship(x, y); 
			    draw_ship(--x, y); 
			}
			if (ch == 's') { erase_ship(x, y); 
			    draw_ship(++x, y); 
			}
			if (bullet != 1 && ch == ' ') { 
				Beep(300, 100); 
			bullet = 1; 
			bx = x + 3; 
			by = y - 1; 
			}
			fflush(stdin);
		}
		if (bullet == 1) {
			clear_bullet(bx, by);
			if (by == 2) { bullet = 0; }
			else {
				if (cursor(bx, by - 1) == '*') {
					erase_score();

					clear_enemy(bx, by);
					px = rand() % 70 + 10, py = rand() % 5 + 2;
					draw_enemy(px, py);
					clear_bullet(bx, by - 1);
					score+=5;
					draw_score(score);

					Beep(500, 100);
					bullet = 0;

				}
				else { draw_bullet(bx, --by); 
				}
			}
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}
