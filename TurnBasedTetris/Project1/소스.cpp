#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

char form[7][4][8] =
{
	{ { 1,0,1,1,1,2,1,3 },{ 0,1,1,1,2,1,3,1 },{ 1,0,1,1,1,2,1,3 },{ 0,1,1,1,2,1,3,1 } },
	{ { 1,1,2,1,1,2,2,2 },{ 1,1,2,1,1,2,2,2 },{ 1,1,2,1,1,2,2,2 },{ 1,1,2,1,1,2,2,2 } },
	{ { 2,1,0,2,1,2,1,1 },{ 1,0,1,1,2,1,2,2 },{ 2,1,0,2,1,2,1,1 },{ 1,0,1,1,2,1,2,2 } },
	{ { 0,1,1,1,1,2,2,2 },{ 2,0,2,1,1,1,1,2 },{ 0,1,1,1,1,2,2,2 },{ 2,0,2,1,1,1,1,2 } },
	{ { 1,0,1,1,1,2,2,2 },{ 0,1,1,1,2,1,0,2 },{ 1,0,2,0,2,1,2,2 },{ 2,1,2,2,1,2,0,2 } },
	{ { 2,0,2,1,2,2,1,2 },{ 0,1,0,2,1,2,2,2 },{ 1,0,2,0,1,1,1,2 },{ 0,1,1,1,2,1,2,2 } },
	{ { 0,1,1,1,2,1,1,2 },{ 2,0,2,1,2,2,1,1 },{ 1,1,1,2,0,2,2,2 },{ 1,0,1,1,1,2,2,1 } },
};

void CurrentXY(int x, int y);
void CursorOff(void);
void CursorOn(void);
void Ending_scene();

void Show_form();
void Hide_form();
void Show_form_1();
void Hide_form_1();

int stopgame = 0;
int color;

int tetris[21][12];
int form_kind;
int next_form_kind;
int rotate_kind;
int screen_x, screen_y;
int score = 0;

void Print_form();
void Delete_form();
void Initial();
int  Check_board(int location_x, int location_y);
void Print_data();
void Move_data(int row);
int  Check_line2(int row);
void Check_line();
void Write_board();
int  Go_down();
int  Select(void);
void Timing(void);

int tetris_1[21][12];
int form_kind_1;
int next_form_kind_1;
int rotate_kind_1;
int screen_x_1, screen_y_1;
int score_1 = 0;

void Print_form_1();
void Delete_form_1();
void Initial_1();
int  Check_board_1(int location_x, int location_y);
void Print_data_1();
void Move_data_1(int row);
int  Check_line2_1(int row);
void Check_line_1();
void Write_board_1();
int  Go_down_1();
int  Select_1(void);
void Timing_1(void);

void Player1();
void Player2();

int confirm;
int confirm_1;
int curTurnOrder = 0;

int main() {

	CursorOff();
	Initial();
	Initial_1();

	form_kind = rand() % 7;
	form_kind_1 = rand() % 7;

	while (1)
	{
		if (stopgame == 1)
		{
			if (score == 3)
			{
				color = 12; // RED
				Ending_scene();
			}
			else if (score_1 == 3)
			{
				color = 9; // BLUE
				Ending_scene();
			}

			if (score > score_1)
			{
				color = 12; // RED
				Ending_scene();
			}
			else if (score < score_1)
			{
				color = 9; // BLUE
				Ending_scene();
			}

			if (score == score_1)
			{
				color = 8; //drawcolor
				Ending_scene();
			}

			break;
		}
		else
		{
			CurrentXY(20, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); printf("점수 : %d", score);
			CurrentXY(96, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); printf("점수 : %d", score_1);

			if (curTurnOrder == 0)
			{
				CurrentXY(55, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); printf("현재 턴 : 레드");
			}
			else
			{
				CurrentXY(55, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); printf("현재 턴 : 블루");
			}

			if (curTurnOrder == 0)
			{
				Player1();
				CurrentXY(20, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); printf("점수 : %d", score);
			}
			else 
			{
				Player2();
				CurrentXY(96, 8); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); printf("점수 : %d", score_1);
			}
		}
	}
	
	CursorOn();

	return 0;
}

void Ending_scene()
{
	system("cls");

	if (score == score_1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); printf("■ DRAW");
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); printf("■ WIN");
	}
};

void Player1() 
{
	int chk, chk2;
	while (1) {
		screen_y = 0;
		screen_x = 4;

		next_form_kind = rand() % 7;

		rotate_kind = 0;

		Print_form();
		Show_form();


		chk = Check_board(screen_x, screen_y);
		chk2 = Check_board(screen_x, screen_y + 1);

		if (chk == FALSE && chk2 == TRUE) {
			Write_board();
			Check_line();
			stopgame = 1;
			system("cls");
			break;
		}
		else if (chk == TRUE && chk2 == TRUE) {
			stopgame = 1;
			system("cls");
			break;
		}

		do {
			Timing();
		} while (Select());

		if (confirm == TRUE) {
			curTurnOrder = 1;
			break;
		}
	}
}


void Player2()
{
	int chk_1, chk2_1;
	while (1)
	{
		screen_y_1 = 0;
		screen_x_1 = 4;

		next_form_kind_1 = rand() % 7;

		rotate_kind_1 = 0;

		Print_form_1();
		Show_form_1();


		chk_1 = Check_board_1(screen_x_1, screen_y_1);
		chk2_1 = Check_board_1(screen_x_1, screen_y_1 + 1);

		if (chk_1 == FALSE && chk2_1 == TRUE) {
			Write_board_1();
			Check_line_1();
			stopgame = 1;
			system("cls");
			break;
		}
		else if (chk_1 == TRUE && chk2_1 == TRUE)
		{
			stopgame = 1;
			system("cls");
			break;
		}

		do {
			Timing_1();
		} while (Select_1());

		if (confirm_1 == TRUE)
		{
			curTurnOrder = 0;
			break;
		}
	}
}

void CurrentXY(int x, int y) {
	COORD Location;
	Location.X = x;
	Location.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Location);
}

void CursorOff(void) {
	CONSOLE_CURSOR_INFO Information;
	Information.dwSize = 1;
	Information.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Information);
}

void CursorOn(void) {
	CONSOLE_CURSOR_INFO Information;

	Information.dwSize = 20;
	Information.bVisible = TRUE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Information);
}

void Show_form() {
	for (int i = 0; i < 4; i++) {

		CurrentXY(20 + (form[next_form_kind][0][i * 2]) * 2,
			2 + form[next_form_kind][0][i * 2 + 1]);

		tetris[10 + form[next_form_kind][0][i * 2 + 1]]
			[20 + form[next_form_kind][0][i * 2]] = 1;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		printf("■");
	}
}

void Hide_form() {
	for (int i = 0; i < 4; i++) {

		CurrentXY(20 + (form[next_form_kind][0][i * 2]) * 2,
			2 + form[next_form_kind][0][i * 2 + 1]);

		tetris[10 + form[next_form_kind][0][i * 2 + 1]]
			[20 + form[next_form_kind][0][i * 2]] = 1;

		printf(" ");
	}
}

void Show_form_1() {
	for (int i = 0; i < 4; i++) {

		CurrentXY(96 + (form[next_form_kind_1][0][i * 2]) * 2,
			2 + form[next_form_kind_1][0][i * 2 + 1]);

		tetris[10 + form[next_form_kind_1][0][i * 2 + 1]]
			[20 + form[next_form_kind_1][0][i * 2]] = 1;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("■");
	}
}

void Hide_form_1() {
	for (int i = 0; i < 4; i++) {

		CurrentXY(96 + (form[next_form_kind_1][0][i * 2]) * 2,
			2 + form[next_form_kind_1][0][i * 2 + 1]);

		tetris[10 + form[next_form_kind_1][0][i * 2 + 1]]
			[20 + form[next_form_kind_1][0][i * 2]] = 1;

		printf(" ");
	}
}



void Print_form() {
	for (int i = 0; i < 4; i++) {

		CurrentXY(30 + (screen_x + form[form_kind][rotate_kind][i * 2]) * 2,
			screen_y + form[form_kind][rotate_kind][i * 2 + 1]);

		tetris[screen_y + form[form_kind][rotate_kind][i * 2 + 1]]
			[screen_x + form[form_kind][rotate_kind][i * 2]] = 1;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		printf("■");
	}
}

void Delete_form() {
	for (int i = 0; i < 4; i++) {

		CurrentXY(30 + (screen_x + form[form_kind][rotate_kind][i * 2]) * 2,
			screen_y + form[form_kind][rotate_kind][i * 2 + 1]);

		tetris[screen_y + form[form_kind][rotate_kind][i * 2 + 1]]
			[screen_x + form[form_kind][rotate_kind][i * 2]] = 0;

		printf(" ");
	}
}


void Initial() {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 12; j++) {
			if (i == 20 || j == 0 || j == 11)
				tetris[i][j] = 3;
			else
				tetris[i][j] = 0;
		}
	}

	for (int i = 0; i < 21; i++) {
		CurrentXY(30, i);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		printf("│");

		CurrentXY(52, i);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		printf("│");
	}

	CurrentXY(30, 20);
	printf("└");
	for (int j = 1; j < 11; j++) {
		CurrentXY(30 + j * 2, 20);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		printf("─");
	}
	CurrentXY(52, 20);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("┘");

	srand((unsigned int)time(NULL));
}

int Check_board(int location_x, int location_y) {
	int temp = 0;

	for (int i = 0; i < 4; i++) {
		temp = tetris[location_y + form[form_kind][rotate_kind][i * 2 + 1]]
			[location_x + form[form_kind][rotate_kind][i * 2]];

		if (temp > 1) return TRUE;
	}
	return FALSE;
}

void Print_data() {
	for (int i = 0; i < 20; i++) {
		for (int j = 1; j < 11; j++) {
			if (tetris[i][j] == 2) {
				CurrentXY(30 + j * 2, i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("■");
			}
			else {
				CurrentXY(30 + j * 2, i);
				printf(" ");
			}
		}
	}
}

void Move_data(int row) {
	for (int i = row - 1; i >= 0; i--)
		for (int j = 1; j < 11; j++)
			tetris[i + 1][j] = tetris[i][j];

	score++;
}

int Check_line2(int row) {
	int chk = 0;
	int j;


	for (j = 1; j < 11; j++) chk += tetris[row][j];

	if (chk == 20) return TRUE;
	else return FALSE;
}

void Check_line() {
	int rst;



	for (int i = screen_y; i < screen_y + 4; i++) {
		rst = Check_line2(i);

		if (rst == TRUE) {
			Move_data(i);
			Print_data();
			i--;
		}
	}
}

void Write_board() {
	for (int i = 0; i < 4; i++) {
		tetris[screen_y + form[form_kind][rotate_kind][i * 2 + 1]]
			[screen_x + form[form_kind][rotate_kind][i * 2]] = 2;
	}
}

int Go_down() {
	int chk2;

	chk2 = Check_board(screen_x, screen_y + 1);

	if (chk2 == TRUE) {
		Write_board();
		Check_line();
		form_kind = next_form_kind;
		Hide_form_1();
		confirm = chk2;
		return TRUE;
	}

	Delete_form();
	screen_y++;
	Print_form();
	return FALSE;
}

int Select(void) {
	int chk1;
	int prev_rotate;
	int new_rotate;
	int rtn_value;

	//A
	if (GetAsyncKeyState(0x41) & 0x8000) {

		chk1 = Check_board(screen_x - 1, screen_y);

		if (chk1 == FALSE) {
			Delete_form();
			screen_x--;
			Print_form();
			return TRUE;
		}
	}

	//D
	if (GetAsyncKeyState(0x44) & 0x8000) {
		chk1 = Check_board(screen_x + 1, screen_y);

		if (chk1 == FALSE) {
			Delete_form();
			screen_x++;
			Print_form();
			return TRUE;
		}
	}

	//W
	if (GetAsyncKeyState(0x57) & 0x8000) {
		prev_rotate = rotate_kind;

		if (rotate_kind == 3) rotate_kind = 0;
		else				rotate_kind++;

		new_rotate = rotate_kind;

		chk1 = Check_board(screen_x, screen_y);

		if (chk1 == FALSE) {
			rotate_kind = prev_rotate;
			Delete_form();

			rotate_kind = new_rotate;
			Print_form();
			return TRUE;
		}
		else {
			rotate_kind = prev_rotate;
		}
	}

	//S
	if (GetAsyncKeyState(0x53) & 0x8000) {
		while (!Go_down());
		return FALSE;
	}

	rtn_value = Go_down();

	if (rtn_value == TRUE) return FALSE;
	else return TRUE;
}

void Timing(void) {
	DWORD				thisTickCount;
	static DWORD		lastTickCount = 0;
	DWORD				delay = 150;

	thisTickCount = GetTickCount();

	while (1) {
		if ((thisTickCount - lastTickCount) > delay) {
			lastTickCount = thisTickCount;
			return;
		}

		thisTickCount = GetTickCount();
	}
}


void Print_form_1() {
	for (int i = 0; i < 4; i++) {

		CurrentXY(70 + (screen_x_1 + form[form_kind_1][rotate_kind_1][i * 2]) * 2,
			screen_y_1 + form[form_kind_1][rotate_kind_1][i * 2 + 1]);

		tetris_1[screen_y_1 + form[form_kind_1][rotate_kind_1][i * 2 + 1]]
			[screen_x_1 + form[form_kind_1][rotate_kind_1][i * 2]] = 1;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("■");
	}
}

void Delete_form_1() {
	for (int i = 0; i < 4; i++) {

		CurrentXY(70 + (screen_x_1 + form[form_kind_1][rotate_kind_1][i * 2]) * 2,
			screen_y_1 + form[form_kind_1][rotate_kind_1][i * 2 + 1]);

		tetris_1[screen_y_1 + form[form_kind_1][rotate_kind_1][i * 2 + 1]]
			[screen_x_1 + form[form_kind_1][rotate_kind_1][i * 2]] = 0;

		printf(" ");
	}
}


void Initial_1() {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 12; j++) {
			if (i == 20 || j == 0 || j == 11)
				tetris_1[i][j] = 3;
			else
				tetris_1[i][j] = 0;
		}
	}

	for (int i = 0; i < 21; i++) {
		CurrentXY(70, i);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("│");

		CurrentXY(92, i);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("│");
	}

	CurrentXY(70, 20);
	printf("└");
	for (int j = 1; j < 11; j++) {
		CurrentXY(70 + j * 2, 20);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("─");
	}
	CurrentXY(92, 20);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("┘");

	srand((unsigned int)time(NULL));
}

int Check_board_1(int location_x, int location_y) {
	int temp = 0;

	for (int i = 0; i < 4; i++) {
		temp = tetris_1[location_y + form[form_kind_1][rotate_kind_1][i * 2 + 1]]
			[location_x + form[form_kind_1][rotate_kind_1][i * 2]];

		if (temp > 1) return TRUE;
	}
	return FALSE;
}

void Print_data_1() {
	for (int i = 0; i < 20; i++) {
		for (int j = 1; j < 11; j++) {
			if (tetris_1[i][j] == 2) {
				CurrentXY(70 + j * 2, i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				printf("■");
			}
			else {
				CurrentXY(70 + j * 2, i);
				printf(" ");
			}
		}
	}
}

void Move_data_1(int row) {
	for (int i = row - 1; i >= 0; i--)
		for (int j = 1; j < 11; j++)
			tetris_1[i + 1][j] = tetris_1[i][j];

	score_1++;
}

int Check_line2_1(int row) {
	int chk = 0;
	int j;

	for (j = 1; j < 11; j++) chk += tetris_1[row][j];

	if (chk == 20) return TRUE;
	else return FALSE;
}

void Check_line_1() {
	int rst;

	for (int i = screen_y_1; i < screen_y_1 + 4; i++) {
		rst = Check_line2_1(i);

		if (rst == TRUE) {
			Move_data_1(i);
			Print_data_1();
			i--;
		}
	}
}

void Write_board_1() {
	for (int i = 0; i < 4; i++) {
		tetris_1[screen_y_1 + form[form_kind_1][rotate_kind_1][i * 2 + 1]]
			[screen_x_1 + form[form_kind_1][rotate_kind_1][i * 2]] = 2;
	}
}

int Go_down_1() {
	int chk2;

	chk2 = Check_board_1(screen_x_1, screen_y_1 + 1);

	if (chk2 == TRUE) {
		Write_board_1();
		Check_line_1();
		form_kind_1 = next_form_kind_1;
		Hide_form();
		confirm_1 = chk2;
		return TRUE;
	}

	Delete_form_1();
	screen_y_1++;
	Print_form_1();
	return FALSE;
}

int Select_1(void) {
	int chk1;
	int prev_rotate;
	int new_rotate;
	int rtn_value;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {

		chk1 = Check_board_1(screen_x_1 - 1, screen_y_1);

		if (chk1 == FALSE) {
			Delete_form_1();
			screen_x_1--;
			Print_form_1();
			return TRUE;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		chk1 = Check_board_1(screen_x_1 + 1, screen_y_1);

		if (chk1 == FALSE) {
			Delete_form_1();
			screen_x_1++;
			Print_form_1();
			return TRUE;
		}
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		prev_rotate = rotate_kind_1;

		if (rotate_kind_1 == 3) rotate_kind_1 = 0;
		else				rotate_kind_1++;

		new_rotate = rotate_kind_1;

		chk1 = Check_board_1(screen_x_1, screen_y_1);

		if (chk1 == FALSE) {
			rotate_kind_1 = prev_rotate;
			Delete_form_1();

			rotate_kind_1 = new_rotate;
			Print_form_1();
			return TRUE;
		}
		else {
			rotate_kind_1 = prev_rotate;
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		while (!Go_down_1());
		return FALSE;
	}

	rtn_value = Go_down_1();

	if (rtn_value == TRUE) return FALSE;
	else return TRUE;
}

void Timing_1(void) {
	DWORD				thisTickCount;
	static DWORD		lastTickCount = 0;
	DWORD				delay = 150;

	thisTickCount = GetTickCount();

	while (1) {
		if ((thisTickCount - lastTickCount) > delay) {
			lastTickCount = thisTickCount;
			return;
		}

		thisTickCount = GetTickCount();
	}
}