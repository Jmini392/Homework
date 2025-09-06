#include <iostream>
using namespace std;

struct point {
	int x;
	int y;
	int z;
	bool empty = true;
}p[10];

point o[10];
bool f = 1;

void Manu() {
	cout << "+ : ��ǥ �߰� \n- : ��ǥ ���� \ne : �Ʒ����� �߰�\nd : �Ʒ����� ����\na : ����� ����Ʈ ����\nb : ������ġ�� ��ĭ�� ����\nc : ����Ʈ ����\nf : �������� �Ÿ�����\nq : ���α׷� ����\n���Ͻô� ��ɾ �Է����ּ���: ";
}

void Print() {
	for (int i = 9; i >= 0; i--) {
		if (p[i].empty) cout << i << "��° ��ǥ: ( , , )" << endl;
		else cout << i << "��° ��ǥ: (" << p[i].x << ", " << p[i].y << ", " << p[i].z << ")" << endl;
	}
}

bool inspect() {
	for (int i = 0; i < 10; i++) {
		if (p[i].empty);
		else return 0;
	}
	return 1;
}

void Reset() {
	for (int i = 0; i < 10; i++) {
		p[i].empty = true;
		o[i].empty = true;
	}
	cout << "����Ʈ ���� �Ϸ�!" << endl;
}

void Add() {
	int x, y, z;
	if(inspect()) {
		cout << "�߰��� ��ǥ�� �Է��ϼ���: ";
		cin >> x >> y >> z;
		p[0].x = x;
		p[0].y = y;
		p[0].z = z;
		p[0].empty = false;
		cout << "�߰� �Ϸ�!" << endl;
		return;
	}
	else {
		for (int i = 9; i >= 0; i--) {
			if (!p[i].empty) {
				if (i == 9) break;
				cout << "�߰��� ��ǥ�� �Է��ϼ���: ";
				cin >> x >> y >> z;
				p[i + 1].x = x;
				p[i + 1].y = y;
				p[i + 1].z = z;
				p[i + 1].empty = false;
				cout << "�߰� �Ϸ�!" << endl;
				return;
			}
		}
		cout << "���̻� �߰��� �� �����ϴ�." << endl;
	}
}

void Sub() {
	if (inspect()) {
		cout << "������ ��ǥ�� �����ϴ�." << endl;
	}
	else {
		for (int i = 9; i >= 0; i--) {
			if (!p[i].empty) {
				p[i].empty = true;
				cout << "���� �Ϸ�!" << endl;
				return;
			}
		}
	}	
}

void EAdd() {
	int x, y, z;
	if (inspect()) {
		cout << "�߰��� ��ǥ�� �Է��ϼ���: ";
		cin >> x >> y >> z;
		p[0].x = x;
		p[0].y = y;
		p[0].z = z;
		p[0].empty = false;
		cout << "�߰� �Ϸ�!" << endl;
		return;
	}
	else {
		for (int i = 0; i < 10; i++) {
			if (p[i].empty && !p[i + 1].empty) {
				cout << "�߰��� ��ǥ�� �Է��ϼ���: ";
				cin >> x >> y >> z;
				p[i].x = x;
				p[i].y = y;
				p[i].z = z;
				p[i].empty = false;
				cout << "�߰� �Ϸ�!" << endl;
				return;
			}
			else if (!p[i].empty && p[i + 1].empty) {
				for (int j = i; j >= 0; j--) {
					p[j + 1] = p[j];
				}
				cout << "�߰��� ��ǥ�� �Է��ϼ���: ";
				cin >> x >> y >> z;
				p[0].x = x;
				p[0].y = y;
				p[0].z = z;
				p[0].empty = false;
				cout << "�߰� �Ϸ�!" << endl;
				return;
			}
		}
	}
}

void ESub() {
	if(inspect()) {
		cout << "������ ��ǥ�� �����ϴ�." << endl;
	}
	else {
		for (int i = 0; i < 10; i++) {
			if (!p[i].empty) {
				p[i].empty = true;
				cout << "���� �Ϸ�!" << endl;
				return;
			}
		}
	}
}

void PPrint() {
	int cnt = 0;
	for (int i = 0; i < 10; i++) {
		if (!p[i].empty) cnt++;
	}
	cout << "����� ��ǥ ����: " << cnt << endl;
}

void Move() {
	point temp = p[0];
	for (int i = 0; i < 9; i++) {
		p[i] = p[i + 1];
	}
	p[9] = temp;
	cout << "������ġ ��ĭ �̵� �Ϸ�!" << endl;
}

void Sort() {
	int cnt = 0;
	for (int i = 0; i < 10; ++i) {
		if (!p[i].empty) {
			o[cnt] = p[i];
			cnt++;
		}
	}
	for (int i = 0; i < cnt - 1; ++i) {
		for (int j = 0; j < cnt - i - 1; ++j) {
			int dist1 = o[j].x * o[j].x + o[j].y * o[j].y + o[j].z * o[j].z;
			int dist2 = o[j + 1].x * o[j + 1].x + o[j + 1].y * o[j + 1].y + o[j + 1].z * o[j + 1].z;
			if (dist1 > dist2) {
				point temp = o[j];
				o[j] = o[j + 1];
				o[j + 1] = temp;
			}
		}
	}
	for (int i = 9; i >= 0; i--) {
		if (o[i].empty) cout << i << "��° ��ǥ: ( , , )" << endl;
		else cout << i << "��° ��ǥ: (" << o[i].x << ", " << o[i].y << ", " << o[i].z << ")" << endl;
	}
}

int main() {
	int x, y, z;
	char c;
	while (1) {
		if(f) Print();
		Manu();
		cin >> c;
		switch (c) {
			case '+':
				Add();
				break;
			case '-':
				Sub();
				break;
			case 'e':
				EAdd();
				break;
			case 'd':
				ESub();
				break;
			case 'a':
				PPrint();
				break;
			case 'b':
				Move();
				break;
			case 'c':
				Reset();
				f = 1;
				break;
			case 'f':
				if (f) {
					f = 0;
					Sort();
				}
				else f = 1;
				break;
			case 'q':
				return 0;
		}
	}
}
