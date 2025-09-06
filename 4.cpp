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
	cout << "��������: " << score << " ���� �޺� X" << combo << endl;
}

void Manu() {
	cout << "(�Է�: e ��Ʈ����: h(����Ƚ��: " << h << ") ���ӹ��: b �ٽ��ϱ�: r ����: q)\n���Ͻô� ��ɾ �Է��� �ּ���.: ";
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
	cout << "���� ���: \n";
	cout << "1. 5x5 �����ǿ� 12���� ���ĺ��� 1���� Ư�����ڰ� �������� ��ġ�˴ϴ�.\n";
	cout << "2. �÷��̾�� �� ĭ�� �����Ͽ� ���ڸ� Ȯ���� �� �ֽ��ϴ�.\n";
	cout << "3. ���� ���ڸ� �����ϸ� 10���� ���, �������� ����� �޺������� ����˴ϴ�. Ʋ���� �޺��� ������ϴ�.\n";
	cout << "4. @�� ���ý� ���� ������ �ٸ������� ��ġ�� �����ϰ� 10���� ����ϴ�. �޺��� ������ �ʽ��ϴ�.\n";
	cout << "5. ��Ʈ�� 3������ ����� �� ������, ��� �� ��� ���ڰ� ��� �����˴ϴ�. �޺��� ������ϴ�.\n";
	cout << "6. ��� ¦�� ���߸� ���ӿ��� �¸��մϴ�.\n";
	cout << "7. ���� ���� �������� �ٽ� �����ϰų� ������ �� �ֽ��ϴ�.\n";
	cout << "��ſ� ���� �Ǽ���!\n\n";
}

int main() {
	CreateBoard();
	cout << "������ �����մϴ�. \n";
	while (1) {
		char c;
		PrintBoard();
		Manu();
		if (CheckWin()) {
			cout << "��� ¦�� ���߼̽��ϴ�! ��������:" << score << endl;
			cout << "������ �����մϴ�.";
			break;
		}
		cin >> c;
		switch (c) {
			case 'e':
				int r,r1;
				char ch,ch1;
				cout << "������� �ڸ� �Է����ּ���[ex)a1 c3]: ";
				cin >> ch >> r >> ch1 >> r1;
				Open(ch, r, ch1, r1);
				break;
			case 'r':
				system("cls");
				ResetBoard();
				CreateBoard();
				cout << "������ �ٽ� �����մϴ�. \n";
				break;
			case 'h':
				if(h == 0) {
					cout << "��Ʈ Ƚ���� ��� ����ϼ̽��ϴ�.\n";
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
				cout << "������ �����մϴ�.";
				return 0;
				break;
		}
	}
	
	return 0;
}