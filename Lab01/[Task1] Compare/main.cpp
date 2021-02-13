#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

using namespace std;

void Compare(string& firstFileName, string& secondFileName);

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "RUSSIAN");

	if (argc < 2)
	{
		cout << "Неверные входные параметры!" << endl;
		cout << "Используйте: Compare.exe <имя первого файла> <имя второго файла>" << endl;

		return 1;
	}

	string firstFileName = argv[1];
	string secondFileName = argv[2];
	Compare(firstFileName, secondFileName);
}

void Compare(string& firstFileName, string& secondFileName)
{
	ifstream firstFile(firstFileName, ios_base::in);
	ifstream secondFile(secondFileName, ios_base::in);
	streamoff firstLength;
	streamoff secondLength;

	char* firstbuffer;
	char* secondbuffer;

	if (!firstFile.is_open() && !secondFile.is_open())
	{
		cout << "Ошибка открытия одного из файлов" << endl;
		exit(1);
	}

	firstFile.seekg(0, firstFile.end);
	firstLength = firstFile.tellg();
	firstFile.seekg(0, firstFile.beg);
	firstbuffer = new char[static_cast<unsigned int>(firstLength)];

	secondFile.seekg(0, secondFile.end);
	secondLength = secondFile.tellg();
	secondFile.seekg(0, secondFile.beg);
	secondbuffer = new char[static_cast<unsigned int>(secondLength)];

	for (int i = 0; i < firstLength; i++)
	{
		if (firstbuffer[i] != secondbuffer[i] || secondbuffer[i] != firstbuffer[i])
		{
			cout << "Файлы различны начиная с сивмвола номер " << i << endl;
			exit(1);
		}
	}
	cout << "Файлы одинкавы" << endl;
};
