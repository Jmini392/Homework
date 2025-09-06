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
	cout << "+ : 좌표 추가 \n- : 좌표 삭제 \ne : 아래부터 추가\nd : 아래부터 삭제\na : 저장된 리스트 갯수\nb : 저장위치를 한칸씩 감소\nc : 리스트 리셋\nf : 원점과의 거리정렬\nq : 프로그램 종료\n원하시는 명령어를 입력해주세요: ";
}

void Print() {
	for (int i = 9; i >= 0; i--) {
		if (p[i].empty) cout << i << "번째 좌표: ( , , )" << endl;
		else cout << i << "번째 좌표: (" << p[i].x << ", " << p[i].y << ", " << p[i].z << ")" << endl;
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
	cout << "리스트 리셋 완료!" << endl;
}

void Add() {
	int x, y, z;
	if(inspect()) {
		cout << "추가할 좌표를 입력하세요: ";
		cin >> x >> y >> z;
		p[0].x = x;
		p[0].y = y;
		p[0].z = z;
		p[0].empty = false;
		cout << "추가 완료!" << endl;
		return;
	}
	else {
		for (int i = 9; i >= 0; i--) {
			if (!p[i].empty) {
				if (i == 9) break;
				cout << "추가할 좌표를 입력하세요: ";
				cin >> x >> y >> z;
				p[i + 1].x = x;
				p[i + 1].y = y;
				p[i + 1].z = z;
				p[i + 1].empty = false;
				cout << "추가 완료!" << endl;
				return;
			}
		}
		cout << "더이상 추가할 수 없습니다." << endl;
	}
}

void Sub() {
	if (inspect()) {
		cout << "삭제할 좌표가 없습니다." << endl;
	}
	else {
		for (int i = 9; i >= 0; i--) {
			if (!p[i].empty) {
				p[i].empty = true;
				cout << "삭제 완료!" << endl;
				return;
			}
		}
	}	
}

void EAdd() {
	int x, y, z;
	if (inspect()) {
		cout << "추가할 좌표를 입력하세요: ";
		cin >> x >> y >> z;
		p[0].x = x;
		p[0].y = y;
		p[0].z = z;
		p[0].empty = false;
		cout << "추가 완료!" << endl;
		return;
	}
	else {
		for (int i = 0; i < 10; i++) {
			if (p[i].empty && !p[i + 1].empty) {
				cout << "추가할 좌표를 입력하세요: ";
				cin >> x >> y >> z;
				p[i].x = x;
				p[i].y = y;
				p[i].z = z;
				p[i].empty = false;
				cout << "추가 완료!" << endl;
				return;
			}
			else if (!p[i].empty && p[i + 1].empty) {
				for (int j = i; j >= 0; j--) {
					p[j + 1] = p[j];
				}
				cout << "추가할 좌표를 입력하세요: ";
				cin >> x >> y >> z;
				p[0].x = x;
				p[0].y = y;
				p[0].z = z;
				p[0].empty = false;
				cout << "추가 완료!" << endl;
				return;
			}
		}
	}
}

void ESub() {
	if(inspect()) {
		cout << "삭제할 좌표가 없습니다." << endl;
	}
	else {
		for (int i = 0; i < 10; i++) {
			if (!p[i].empty) {
				p[i].empty = true;
				cout << "삭제 완료!" << endl;
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
	cout << "저장된 좌표 갯수: " << cnt << endl;
}

void Move() {
	point temp = p[0];
	for (int i = 0; i < 9; i++) {
		p[i] = p[i + 1];
	}
	p[9] = temp;
	cout << "저장위치 한칸 이동 완료!" << endl;
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
		if (o[i].empty) cout << i << "번째 좌표: ( , , )" << endl;
		else cout << i << "번째 좌표: (" << o[i].x << ", " << o[i].y << ", " << o[i].z << ")" << endl;
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
