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

void Copyfile(string& inputFileName, string& outputFileName);
 
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "RU");

	if (argc < 2)
	{
		cout << "Неверные входные параметры!" << endl;
		cout << "Используйте: Copyfile.exe <имя входного файла> <имя выходного файла>" << endl;
		return 1;
	}

	string inputFileName = argv[1];
	string outputFileName = argv[2];

	Copyfile(inputFileName, outputFileName);
}

void Copyfile(string& inputFileName, string& outputFileName)
{
	ifstream inputFile(inputFileName, ios_base::in);
	ofstream outputFile(outputFileName, ios_base::out, ios_base::trunc);

	int length;
	char* buffer;

	if (!inputFile.is_open() && !outputFile.is_open())
	{
		cout << "Ошибка открытия одного из файлов" << endl;
		exit(1);
	}

	inputFile.seekg(0, inputFile.end);
	length = static_cast<unsigned int>(inputFile.tellg());
	inputFile.seekg(0, inputFile.beg);
	buffer = new char[length];

	inputFile.read(buffer, length);
	outputFile.write(buffer, static_cast<streamoff>(length));

	outputFile.close();
	inputFile.close();
	cout << "Файл " << inputFileName << " скопирован " << outputFileName << endl;
}