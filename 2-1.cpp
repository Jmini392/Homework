#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <windows.h>
#pragma warning(disable: 4996)
using namespace std;

char original[10][100]{ 0 }; // 원본
char work[10][100]{ 0 };     // 작업용
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
    cout << "\n대문자로 바꾸기: a \n문장내 단어갯수 출력: b \n대문자단어 찾기: c \n거꾸로 출력하기: d \n공백을 슬래시(/)로 변경: e \n공백기준 단어 거꾸로출력: f \n특정문자 변경: g \n숫자구분: h \n문장정렬하기: i \n단어찾기: j \n프로그램 종료: q \n원하시는 명령어를 입력해주세요: ";
}

// 공백 여러 개를 하나로 줄이기
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

// a: 대문자 변환 토글
void ToUpperToggle() {
    for (int i = 0; i < lineCount; ++i) {
        for (int j = 0; work[i][j]; ++j) {
            if (work[i][j] >= 'a' && work[i][j] <= 'z')
                work[i][j] -= 32;
        }
    }
    Print(work);
}

// b: 각 줄의 단어 개수 출력
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
        cout << " 단어: " << cnt << "개" << endl;
    }
}

// c: 대문자로 시작하는 단어 색상 출력 및 개수
void FindUpperToggle() {
    int total = 0, cnt = 0;
    NormalizeSpaces(work);
    for (int i = 0; i < lineCount; ++i) {
        int j = 0;
        while (work[i][j]) {
            // 단어 시작
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
        cout << " 단어 개수: " << cnt << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        total += cnt;
        cnt = 0;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "대문자로 시작하는 단어 개수: " << total << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

// d: 문장 한 줄 전체 거꾸로 출력 토글
void ReverseToggle() {
    for (int i = 0; i < lineCount; ++i) {
        int len = strlen(work[i]);
        for (int j = 0; j < len / 2; ++j)
            swap(work[i][j], work[i][len - 1 - j]);
    }
    Print(work);
}

// e: 모든 공백을 슬래시로 변경 토글
void SlashToggle() {
    for (int i = 0; i < lineCount; ++i) {
        for (int j = 0; work[i][j]; ++j) {
            if (work[i][j] == ' ')
                work[i][j] = '/';
        }
    }
    Print(work);
}

// f: 단어 거꾸로 출력 토글
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

// g: 특정 문자 변경 토글
void ReplaceToggle() {
    char from, to;
    cout << "바꿀 문자 입력: ";
    cin >> from;
    cout << "새 문자 입력: ";
    cin >> to;
    for (int i = 0; i < lineCount; ++i) {
        for (int j = 0; work[i][j]; ++j) {
            if (work[i][j] == from)
                work[i][j] = to;
        }
    }
    Print(work);
}

// h: 숫자 뒤에 오는 문장을 다음 줄로 넘기기 토글
void NumberSplitToggle() {
    for (int i = 0; i < lineCount; ++i) {
        for (int j = 0; work[i][j]; ++j) {
            cout << work[i][j];
            if (work[i][j] >= '0' && work[i][j] <= '9') cout << endl;
        }
        cout << endl;
    }
}

// i: 알파벳 개수로 정렬 (오름/내림/원본) 토글
void SortToggle(int mode) {
    static vector<string> backup;
    vector<pair<int, int>> alphaCount; // <알파벳수, 인덱스>
    for (int i = 0; i < lineCount; ++i) {
        int cnt = 0;
        for (int j = 0; work[i][j]; ++j) {
            if ((work[i][j] >= 'A' && work[i][j] <= 'Z') || (work[i][j] >= 'a' && work[i][j] <= 'z')) cnt++;
        }
        alphaCount.push_back({ cnt, i });
    }
    if (mode % 3 == 1) {
        sort(alphaCount.begin(), alphaCount.end());
		cout << "오름차순 정렬" << endl;
    }
    else if (mode % 3 == 2) {
        sort(alphaCount.rbegin(), alphaCount.rend());
		cout << "내림차순 정렬" << endl;
    }
    char temp[10][100]{ 0 };
    for (int i = 0; i < lineCount; ++i) {
        strcpy(temp[i], work[alphaCount[i].second]);
    }
    Copy(work, temp);
    Print(work);
}

// j: 단어 찾기(색상) 및 개수(대소문자 구분X)
void WordFind() {
    string findWord;
    cout << "찾을 단어를 입력하세요: ";
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
    cout << "찾은 단어 개수: " << total << endl;
}

int main() {
    string str, line;
    char text[10][100]{ 0 };

    cout << "파일이름을 입력해주세요: ";
    cin >> str;
    if (str != "data.txt") {
        cout << "파일명이 잘못되었습니다.";
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
        cout << "파일 열기 성공!" << endl;
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
                    cout << "현재 '" << active << "' 명령어가 활성화되어 있습니다. 같은 명령어를 다시 입력해 해제하세요." << endl;
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
        cerr << "파일을 열 수 없습니다.\n프로그램을 종료합니다.\n";
        return 0;
    }
}