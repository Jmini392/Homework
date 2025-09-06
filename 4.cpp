#include <iostream>
#include <random>
#include <windows.h>
using namespace std;

struct Borad {
	char a;
	bool open = 0;
	int color;
}borad[5][5];

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dis(0, 4);

int h = 3, score = 0, combo = 1;

void ResetBoard() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			borad[i][j].a = 0;
			borad[i][j].open = 0;
		}
	}
	h = 3;
	score = 0;
	combo = 1;
}

void CreateBoard() {
	int x = dis(gen), y = dis(gen), ct = 0;
	for (int i = 0; i < 24; i++) {
		if (borad[x][y].a == 0) {
			borad[x][y].a = ct + 97;
			borad[x][y].color = ct + 1;
			if (i % 2 == 1) ct++;
		}
		else {
			x = dis(gen);
			y = dis(gen);
			i--;
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (borad[i][j].a == 0) {
				borad[i][j].a = '@';
				borad[i][j].color = 15;
			}
		}
	}
}


void PrintBoard() {
	cout << "  a b c d e\n";
	for (int i = 0; i < 5; i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < 5; j++) {
			if (borad[i][j].open) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), borad[i][j].color);
				cout << borad[i][j].a << " ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else cout << "*" << " ";
		}
		cout << endl;
	}
	cout << "현재점수: " << score << " 현재 콤보 X" << combo << endl;
}

void Manu() {
	cout << "(입력: e 힌트보기: h(남은횟수: " << h << ") 게임방법: b 다시하기: r 종료: q)\n원하시는 명령어를 입력해 주세요.: ";
}

void ShowHint() {
	cout << "  a b c d e\n";
	for (int i = 0; i < 5; i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < 5; j++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), borad[i][j].color);
			cout << borad[i][j].a << " ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		cout << endl;
	}
	Sleep(3000);
	system("cls");

}

void Open(char c, int r, char c1, int r1) {
	borad[r - 1][c - 'a'].open = 1;
	borad[r1 - 1][c1 - 'a'].open = 1;
	PrintBoard();
	Sleep(1000);
	if (borad[r - 1][c - 'a'].a == borad[r1 - 1][c1 - 'a'].a) {
		borad[r - 1][c - 'a'].a -= ' ';
		borad[r1 - 1][c1 - 'a'].a -= ' ';
		score += 10 * combo;
		combo++;
	}
	else if (borad[r - 1][c - 'a'].a == '@' || borad[r1 - 1][c1 - 'a'].a == '@') {
		for (int i = 0; i < 5; ++i)	{
			for (int j = 0; j < 5; ++j) {
				if (borad[i][j].a == borad[r - 1][c - 'a'].a || borad[i][j].a == borad[r1 - 1][c1 - 'a'].a) {
					if (i == r - 1 && j == c - 'a') continue;
					if (i == r1 - 1 && j == c1 - 'a') continue;
					borad[i][j].open = 1;
					borad[i][j].a -= ' ';
				}
			}
		}
		borad[r - 1][c - 'a'].a -= ' ';
		borad[r1 - 1][c1 - 'a'].a -= ' ';
		score += 10;
	}
	else {
		borad[r - 1][c - 'a'].open = 0;
		borad[r1 - 1][c1 - 'a'].open = 0;
		combo = 1;
	}
	system("cls");
}

bool CheckWin() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (borad[i][j].open == 0) return 0;
		}
	}
	return 1;
}

void Rule() {
	cout << "게임 방법: \n";
	cout << "1. 5x5 보드판에 12쌍의 알파벳과 1개의 특수문자가 무작위로 배치됩니다.\n";
	cout << "2. 플레이어는 두 칸을 선택하여 문자를 확인할 수 있습니다.\n";
	cout << "3. 같은 문자를 선택하면 10점을 얻고, 연속으로 맞출시 콤보점수가 적용됩니다. 틀릴시 콤보가 사라집니다.\n";
	cout << "4. @가 나올시 같이 선택한 다른문자의 위치를 공개하고 10점을 얻습니다. 콤보는 오르지 않습니다.\n";
	cout << "5. 힌트는 3번까지 사용할 수 있으며, 사용 시 모든 문자가 잠시 공개됩니다. 콤보가 사라집니다.\n";
	cout << "6. 모든 짝을 맞추면 게임에서 승리합니다.\n";
	cout << "7. 게임 도중 언제든지 다시 시작하거나 종료할 수 있습니다.\n";
	cout << "즐거운 게임 되세요!\n\n";
}

int main() {
	CreateBoard();
	cout << "게임을 시작합니다. \n";
	while (1) {
		char c;
		PrintBoard();
		Manu();
		if (CheckWin()) {
			cout << "모든 짝을 맞추셨습니다! 최종점수:" << score << endl;
			cout << "게임을 종료합니다.";
			break;
		}
		cin >> c;
		switch (c) {
			case 'e':
				int r,r1;
				char ch,ch1;
				cout << "열고싶은 자리 입력해주세요[ex)a1 c3]: ";
				cin >> ch >> r >> ch1 >> r1;
				Open(ch, r, ch1, r1);
				break;
			case 'r':
				system("cls");
				ResetBoard();
				CreateBoard();
				cout << "게임을 다시 시작합니다. \n";
				break;
			case 'h':
				if(h == 0) {
					cout << "힌트 횟수를 모두 사용하셨습니다.\n";
					break;
				}
				else {
					system("cls");
					ShowHint();
					h--;
				}
				break;
			case 'b':
				system("cls");
				Rule();
				break;
			case 'q':
				cout << "게임을 종료합니다.";
				return 0;
				break;
		}
	}
	
	return 0;
}