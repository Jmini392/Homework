#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <windows.h>
#pragma warning(disable: 4996)
using namespace std;

char original[10][100]{ 0 }; // ����
char work[10][100]{ 0 };     // �۾���
int lineCount = 0;

void Copy(char dst[10][100], char src[10][100]) {
    for (int i = 0; i < 10; ++i)
        strcpy(dst[i], src[i]);
}

void Print(char t[10][100]) {
    for (int i = 0; i < lineCount; ++i)
        cout << t[i] << endl;
}

void Manu() {
    cout << "\n�빮�ڷ� �ٲٱ�: a \n���峻 �ܾ�� ���: b \n�빮�ڴܾ� ã��: c \n�Ųٷ� ����ϱ�: d \n������ ������(/)�� ����: e \n������� �ܾ� �Ųٷ����: f \nƯ������ ����: g \n���ڱ���: h \n���������ϱ�: i \n�ܾ�ã��: j \n���α׷� ����: q \n���Ͻô� ��ɾ �Է����ּ���: ";
}

// ���� ���� ���� �ϳ��� ���̱�
void NormalizeSpaces(char t[10][100]) {
    for (int i = 0; i < lineCount; ++i) {
        char temp[100] = { 0 };
        int idx = 0;
        bool prevSpace = false;
        for (int j = 0; t[i][j]; ++j) {
            if (t[i][j] == ' ') {
                if (!prevSpace) {
                    temp[idx++] = ' ';
                    prevSpace = true;
                }
            }
            else {
                temp[idx++] = t[i][j];
                prevSpace = false;
            }
        }
        temp[idx] = 0;
        strcpy(t[i], temp);
    }
}

// a: �빮�� ��ȯ ���
void ToUpperToggle() {
    for (int i = 0; i < lineCount; ++i) {
        for (int j = 0; work[i][j]; ++j) {
            if (work[i][j] >= 'a' && work[i][j] <= 'z')
                work[i][j] -= 32;
        }
    }
    Print(work);
}

// b: �� ���� �ܾ� ���� ���
void CountWords() {
    NormalizeSpaces(work);
    for (int i = 0; i < lineCount; ++i) {
        int cnt = 0;
        bool inWord = false;
        for (int j = 0; work[i][j]; ++j) {
            if (work[i][j] != ' ' && !inWord) {
                inWord = true;
                cnt++;
            }
            else if (work[i][j] == ' ') {
                inWord = false;
            }
            cout << work[i][j];
        }
        cout << " �ܾ�: " << cnt << "��" << endl;
    }
}

// c: �빮�ڷ� �����ϴ� �ܾ� ���� ��� �� ����
void FindUpperToggle() {
    int total = 0, cnt = 0;
    NormalizeSpaces(work);
    for (int i = 0; i < lineCount; ++i) {
        int j = 0;
        while (work[i][j]) {
            // �ܾ� ����
            if ((j == 0 || work[i][j - 1] == ' ') && (work[i][j] >= 'A' && work[i][j] <= 'Z')) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                int k = j;
                while (work[i][k] && work[i][k] != ' ') {
                    cout << work[i][k];
                    k++;
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cnt++;
                j = k;
            }
            else {
                cout << work[i][j];
                j++;
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << " �ܾ� ����: " << cnt << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        total += cnt;
        cnt = 0;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "�빮�ڷ� �����ϴ� �ܾ� ����: " << total << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

// d: ���� �� �� ��ü �Ųٷ� ��� ���
void ReverseToggle() {
    for (int i = 0; i < lineCount; ++i) {
        int len = strlen(work[i]);
        for (int j = 0; j < len / 2; ++j)
            swap(work[i][j], work[i][len - 1 - j]);
    }
    Print(work);
}

// e: ��� ������ �����÷� ���� ���
void SlashToggle() {
    for (int i = 0; i < lineCount; ++i) {
        for (int j = 0; work[i][j]; ++j) {
            if (work[i][j] == ' ')
                work[i][j] = '/';
        }
    }
    Print(work);
}

// f: �ܾ� �Ųٷ� ��� ���
void WordReverseToggle() {
    for (int i = 0; i < lineCount; ++i) {
        vector<string> words;
        string temp;
        for (int j = 0; work[i][j]; ++j) {
            if (work[i][j] == ' ' || work[i][j] == '/') {
                if (!temp.empty()) {
                    words.push_back(temp);
                    temp.clear();
                }
            }
            else {
                temp += work[i][j];
            }
        }
        if (!temp.empty()) words.push_back(temp);
        string result;
        for (int k = words.size() - 1; k >= 0; --k) {
            result += words[k];
            if (k != 0) result += ' ';
        }
        strcpy(work[i], result.c_str());
    }
    Print(work);
}

// g: Ư�� ���� ���� ���
void ReplaceToggle() {
    char from, to;
    cout << "�ٲ� ���� �Է�: ";
    cin >> from;
    cout << "�� ���� �Է�: ";
    cin >> to;
    for (int i = 0; i < lineCount; ++i) {
        for (int j = 0; work[i][j]; ++j) {
            if (work[i][j] == from)
                work[i][j] = to;
        }
    }
    Print(work);
}

// h: ���� �ڿ� ���� ������ ���� �ٷ� �ѱ�� ���
void NumberSplitToggle() {
    for (int i = 0; i < lineCount; ++i) {
        for (int j = 0; work[i][j]; ++j) {
            cout << work[i][j];
            if (work[i][j] >= '0' && work[i][j] <= '9') cout << endl;
        }
        cout << endl;
    }
}

// i: ���ĺ� ������ ���� (����/����/����) ���
void SortToggle(int mode) {
    static vector<string> backup;
    vector<pair<int, int>> alphaCount; // <���ĺ���, �ε���>
    for (int i = 0; i < lineCount; ++i) {
        int cnt = 0;
        for (int j = 0; work[i][j]; ++j) {
            if ((work[i][j] >= 'A' && work[i][j] <= 'Z') || (work[i][j] >= 'a' && work[i][j] <= 'z')) cnt++;
        }
        alphaCount.push_back({ cnt, i });
    }
    if (mode % 3 == 1) {
        sort(alphaCount.begin(), alphaCount.end());
		cout << "�������� ����" << endl;
    }
    else if (mode % 3 == 2) {
        sort(alphaCount.rbegin(), alphaCount.rend());
		cout << "�������� ����" << endl;
    }
    char temp[10][100]{ 0 };
    for (int i = 0; i < lineCount; ++i) {
        strcpy(temp[i], work[alphaCount[i].second]);
    }
    Copy(work, temp);
    Print(work);
}

// j: �ܾ� ã��(����) �� ����(��ҹ��� ����X)
void WordFind() {
    string findWord;
    cout << "ã�� �ܾ �Է��ϼ���: ";
    cin >> findWord;
    int total = 0;
    for (int i = 0; i < lineCount; ++i) {
        string line = work[i];
        string lowerLine = line, lowerFind = findWord;
        transform(lowerLine.begin(), lowerLine.end(), lowerLine.begin(), ::tolower);
        transform(lowerFind.begin(), lowerFind.end(), lowerFind.begin(), ::tolower);
        size_t pos = 0;
        int last = 0;
        while ((pos = lowerLine.find(lowerFind, last)) != string::npos) {
            cout << line.substr(last, pos - last);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << line.substr(pos, findWord.length());
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            last = pos + findWord.length();
            total++;
        }
        cout << line.substr(last) << endl;
    }
    cout << "ã�� �ܾ� ����: " << total << endl;
}

int main() {
    string str, line;
    char text[10][100]{ 0 };

    cout << "�����̸��� �Է����ּ���: ";
    cin >> str;
    if (str != "data.txt") {
        cout << "���ϸ��� �߸��Ǿ����ϴ�.";
        return 0;
    }
    ifstream inFile(str);
    if (inFile.is_open()) {
        while (getline(inFile, line) && lineCount < 10) {
            string temp;
            bool prevSpace = false;
            for (char ch : line) {
                if (ch == ' ') {
                    if (!prevSpace) {
                        temp += ch;
                        prevSpace = true;
                    }
                }
                else {
                    temp += ch;
                    prevSpace = false;
                }
            }
            strcpy(text[lineCount], temp.c_str());
            lineCount++;
        }
        inFile.close();
        cout << "���� ���� ����!" << endl;
        Copy(original, text);
        Copy(work, text);
        Print(work);

        char c, active = 0;
        int sort = 1;
		bool activeToggle = true;
        
        while (1) {
            Manu();
            cin >> c;
            if (!activeToggle) {
                if (c == active) {
                    if (c == 'i') {
                        if (sort % 3 == 2) {
                            system("cls");
                            SortToggle(sort);
                            sort++;
                            continue;
                        }
                        else if (sort % 3 == 0) {
                            system("cls");
							sort++;
                            Copy(work, original);
                            Print(work);
                            activeToggle = true;
						}
					}
                    system("cls");
                    Copy(work, original);
					Print(work);
                    activeToggle = true;
                }
                else {
					system("cls");
                    cout << "���� '" << active << "' ��ɾ Ȱ��ȭ�Ǿ� �ֽ��ϴ�. ���� ��ɾ �ٽ� �Է��� �����ϼ���." << endl;
                }
                continue;
            }
			system("cls");
            switch (c) {
                case 'a':
                    ToUpperToggle();
                    active = c;
                    activeToggle = false;
                    break;
                case 'b':
                    CountWords();
                    break;
                case 'c':
                    FindUpperToggle();
                    active = c;
                    activeToggle = false;
                    break;
                case 'd':
                    ReverseToggle();
                    active = c;
                    activeToggle = false;
                    break;
                case 'e':
                    SlashToggle();
                    active = c;
                    activeToggle = false;
                    break;
                case 'f':
                    WordReverseToggle();
                    active = c;
                    activeToggle = false;
                    break;
                case 'g': 
                    ReplaceToggle();
                    active = c;
                    activeToggle = false;
                    break;
                case 'h':
                    NumberSplitToggle();
                    active = c;
                    activeToggle = false;
                    break;
                case 'i':
                    SortToggle(sort);
                    sort++;
                    active = c;
					activeToggle = false;
                    break;
                case 'j':
                    WordFind();
                    break;
                case 'q':
                    return 0;
            }
        }
    }
    else {
        cerr << "������ �� �� �����ϴ�.\n���α׷��� �����մϴ�.\n";
        return 0;
    }
}