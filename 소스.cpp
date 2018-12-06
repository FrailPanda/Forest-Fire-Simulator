#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<stddef.h>
#include<locale.h>
#include<time.h>

#pragma warning(disable:4996)

/*
< Map Data >
using python IDLE

/---- code ----/
import random
for i in range(20):
	for j in range(20):
		print("%d "%random.randint(0,3), end="")
	print()

*/


/*
< Print Map element >
- Fire :: �� / Tree :: �� / Stone :: �� / Water :: ~
   -> Fire :: $ / Tree :: + / Stone :: @ / Water :: ~
- Empty Data :: ^

< After Burning >
- Dust :: *

< Wind Data >
- 1 : ���ʿ��� �Ҿ���� �ٶ�
- 2 : �ϼ��ʿ��� �Ҿ���� �ٶ�
- 3 : ���ʿ��� �Ҿ���� �ٶ�
- 4 : �ϵ��ʿ��� �Ҿ���� �ٶ�
- 5 : ���ʿ��� �Ҿ���� �ٶ�
- 6 : �����ʿ��� �Ҿ���� �ٶ�
- 7 : ���ʿ��� �Ҿ���� �ٶ�
- 8 : �����ʿ��� �Ҿ���� �ٶ�

< Init - Input map data >
- 0 : Empty Place
- 1 : Tree
- 2 : Water
- 3 : Stone
*/

wchar_t **map; // map[y][x]
int turntime = 0; // The step of forest fire
int wind; // Random data of wind direction
int option; // Option Data
int n; // Size of map
int remain; // Is tree remaining

void ShowMap() {
	int x, y;

	for (y = 1; y <= n; y++)
	{
		for (x = 1; x <= n; x++) {
			if (map[y][x] == '$') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("%lc ", map[y][x]); // Print Map Data
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (map[y][x] == '+') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("%lc ", map[y][x]); // Print Map Data
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (map[y][x] == '@') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
				printf("%lc ", map[y][x]); // Print Map Data
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (map[y][x] == '~') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				printf("%lc ", map[y][x]); // Print Map Data
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (map[y][x] == '*') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				printf("%lc ", map[y][x]); // Print Map Data
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else {
				printf("%lc ", map[y][x]);
			}
		}
		printf("\n");
	}
}

void processFire() {
	int x, y;
	remain = 0;

	for (y = 1; y <= n; y++) {
		for (x = 1; x <= n; x++) {
			if (map[y][x] == '$') {
				map[y][x] = '#'; // �ӽ÷� '#'���� �ٲ�

				if (map[y][x - 1] == '+' && x - 1 >= 0) // ���ʿ� ������ �ִٸ�
					map[y][x - 1] = L'&'; // �ӽ÷� '&'���� �ٲ�

				if (map[y - 1][x - 1] == '+' && y - 1 >= 0 && x - 1 >= 0)  // �ϼ��ʿ� ������ �ִٸ�
					map[y - 1][x - 1] = L'&'; // �ӽ÷� '&'���� �ٲ�

				if (map[y - 1][x] == '+' && y - 1 >= 0) // ���ʿ� ������ �ִٸ�
					map[y - 1][x] = L'&'; // �ӽ÷� '&'���� �ٲ�

				if (map[y - 1][x + 1] == '+' && y - 1 >= 0 && x + 1 <= n) // �ϵ��ʿ� ������ �ִٸ�
					map[y - 1][x + 1] = L'&'; // �ӽ÷� '&'���� �ٲ�

				if (map[y][x + 1] == '+' && x + 1 <= n) // ���ʿ� ������ �ִٸ�
					map[y][x + 1] = L'&'; // �ӽ÷� '&'���� �ٲ�

				if (map[y + 1][x + 1] == '+' && y + 1 <= n && x + 1 <= n) // �����ʿ� ������ �ִٸ�
					map[y + 1][x + 1] = L'&'; // �ӽ÷� '&'���� �ٲ�

				if (map[y + 1][x] == '+' && y + 1 <= n) // ���ʿ� ������ �ִٸ�
					map[y + 1][x] = L'&'; // �ӽ÷� '&'���� �ٲ�

				if (map[y + 1][x - 1] == '+' && y + 1 <= n && x - 1 >= 0) // �����ʿ� ������ �ִٸ�
					map[y + 1][x - 1] = L'&'; // �ӽ÷� '&'���� �ٲ�
			}
		}
	}

	for (y = 1; y <= n; y++) {
		for (x = 1; x <= n; x++) {
			if (map[y][x] == '$' || map[y][x] == '&') {
				switch (wind) {
				case 1: // �ٶ��� ���ʿ��� �Ҿ�´ٸ�
					if (map[y][x + 1] == '+' && x + 1 <= n)
						map[y][x + 1] = '!';
					break;
				case 2: // �ٶ��� �ϼ��ʿ��� �Ҿ�´ٸ�
					if (map[y + 1][x + 1] == '+' && x + 1 <= n && y + 1 <= n)
						map[y + 1][x + 1] = '!';
					break;
				case 3: // �ٶ��� ���ʿ��� �Ҿ�´ٸ�
					if (map[y + 1][x] == '+' && y + 1 <= n)
						map[y + 1][x] = '!';
					break;
				case 4: // �ٶ��� �ϵ��ʿ��� �Ҿ�´ٸ�
					if (map[y + 1][x - 1] == '+' && x - 1 >= 0 && y + 1 <= n)
						map[y + 1][x - 1] = '!';
					break;
				case 5: // �ٶ��� ���ʿ��� �Ҿ�´ٸ�
					if (map[y][x - 1] == '+' && x - 1 >= 0)
						map[y][x - 1] = '!';
					break;
				case 6: // �ٶ��� �����ʿ��� �Ҿ�´ٸ�
					if (map[y - 1][x - 1] == '+' && x - 1 >= 0 && y - 1 >= 0)
						map[y - 1][x - 1] = '!';
					break;
				case 7: // �ٶ��� ���ʿ��� �Ҿ�´ٸ�
					if (map[y - 1][x] == '+' && y - 1 >= 0)
						map[y - 1][x] = '!';
					break;
				case 8: // �ٶ��� �����ʿ��� �Ҿ�´ٸ�
					if (map[y - 1][x + 1] == '+' && x + 1 <= n && y - 1 >= 0)
						map[y - 1][x + 1] = '!';
					break;
				default:
					break;
				}
			}
		}
	}

	for (y = 1; y <= n; y++)
	{
		for (x = 1; x <= n; x++)
		{
			if (map[y][x] == '&' || map[y][x] == '!') // ������ �ӽ÷� !�� &ǥ���� ����
				map[y][x] = '$'; // *ǥ��� ����

			if (map[y][x] == '#')
				map[y][x] = '*';

			if (map[y][x] == '$') // �����ִ� �Ҿ��� �ִ��� üũ
				remain++; // ���� �ִٸ� remain ������ �������Ѽ� �Ҿ��� �����ִٴ� ���� �˸�
		}
	}
}

void LoadForestData() {
	FILE *fp;
	int ix, iy; // Initial (x, y) data of fire
	int value; // First Map Data

	fp = fopen("input.txt", "r"); // File Open

	fscanf(fp, "%d", &n);
	fscanf(fp, "%d", &ix);
	fscanf(fp, "%d", &iy);

	map = (wchar_t **)malloc(sizeof(wchar_t *)*(n + 2));
	for (int i = 0; i < n+2; i++) {
		map[i] = (wchar_t *)malloc(sizeof(wchar_t)*(n + 2));
	}

	setlocale(LC_ALL, "");

	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			fscanf(fp, "%d ", &value);

			if (value == 1) // Tree Data
				map[y][x] = L'+';
			else if (value == 2) // Water Data
				map[y][x] = L'~';
			else if (value == 3) // Stone Data
				map[y][x] = L'@';
			else // Empty Place Data
				map[y][x] = L'^';
		}
	}

	map[iy+1][ix+1] = L'$';

	fclose(fp); // File Close
}

void simulatingFire() {
	srand((unsigned)time(NULL)); // Init srand()

	printf("Step 0\n"); // Step 0.
	printf("Wind : None\n\n");
	ShowMap(); // Show Initial Map
	printf("\n\nPress Any Key..");
	getch(); // Enter

	while (1) {
		wind = rand() % 8 + 1; // random 1~8 wind direction
		//wind = 1;

		system("CLS");
		printf("Step %d\n", ++turntime); // Print step turntime
		switch (wind) {
		case 1:
			printf("Wind : ��\n\n");
			break;
		case 2:
			printf("Wind : ��\n\n");
			break;
		case 3:
			printf("Wind : ��\n\n");
			break;
		case 4:
			printf("Wind : ��\n\n");
			break;
		case 5:
			printf("Wind : ��\n\n");
			break;
		case 6:
			printf("Wind : ��\n\n");
			break;
		case 7:
			printf("Wind : ��\n\n");
			break;
		case 8:
			printf("Wind : ��\n\n");
			break;
		default:
			break;
		}

		processFire(); // process of fire
		ShowMap(); // show updated map

		if (!remain) { // all forest burned
			printf("\n\nFinished..\n");
			break;
		}
		printf("\n\nPress Any Key..");
		getch(); // Press any key
	}
}

void showDirection() {

}

void calculatingSteps() {

}

void main() {
	/* Handle the size of console */
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 400, 550, TRUE);

	/* Set the element of Map */
	LoadForestData();


	printf("/*========================================*/\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|          Forest Fire Simulator           |\n");
	printf("|    (Application of Cellular Automata)    |\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|                            Sejong Univ.  |\n");
	printf("|                 Departement of Software  |\n");
	printf("|                    18011673 Rho Hyo Sik  |\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|   1: Simulating Forest Fire              |\n");
	printf("|                                          |\n");
	printf("|   2: Show Direction of Forest Fire       |\n");
	printf("|                                          |\n");
	printf("|   3: Calculating Steps & Burned Tree     |\n");
	printf("|                                          |\n");
	printf("|   0: Exit                                |\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("/*========================================*/\n");
	printf("\n");
	printf("Select Option : ");

	scanf("%d", &option);

	switch (option) {
	case 1:
		system("CLS");
		simulatingFire();
		break;
	case 2:
		showDirection();
		break;
	case 3:
		calculatingSteps();
		break;
	case 0:
		exit(1);
	default:
		exit(1);
	}
}