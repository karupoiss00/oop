#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <climits>
#include <optional>

using namespace std;

typedef double Matrix2x2[2][2];
typedef double Matrix3x3[3][3];

struct Args
{
	string matrixFileName;
};

optional<Args> ParseArgs(int argc, char* argv[]);
bool ReadMatrixFromFile(const string& fileName, Matrix3x3& matrix);
bool Invert(const Matrix3x3& matrix, Matrix3x3& invertMatrix);
void PrintMatrix(const Matrix3x3& matrix);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	Matrix3x3 matrix;
	Matrix3x3 invertedMatrix;

	if (!ReadMatrixFromFile(args->matrixFileName, matrix))
	{
		cout << "Failed to read matrix" << endl;
		return 1;
	}

	if (!Invert(matrix, invertedMatrix))
	{
		cout << "Failed to invert matrix" << endl;
		return 1;
	}

	PrintMatrix(invertedMatrix);

	return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count" << endl;
		cout << "Usage: Invert.exe <matrix file name>" << endl;
		return nullopt;
	}

	Args args;
	args.matrixFileName = argv[1];
	return args;
}

void PrintMatrix(const Matrix3x3& matrix)
{
	cout << fixed << setprecision(3);
	cout << endl;
	for (unsigned line = 0; line < 3; ++line)
	{
		for (unsigned column = 0; column < 3; ++column)
		{
			cout << fixed << matrix[line][column] << "\t";
		}
		cout << endl;
	}
}

bool __fastcall StrToFloat(const string& str, double& number)
{
	number = strtod(str.c_str(), NULL);

	//проверка на переполнение после перевода строки в число
	if (errno == ERANGE)
	{
		return false;
	}

	return true;
}

bool ReadMatrixFromFile(const string& fileName, Matrix3x3& matrix)
{
	ifstream input;
	input.open(fileName);

	if (!input.is_open())
	{
		cout << "Failed to open '" << fileName << "' for reading\n";
		return false;
	}

	smatch searchResult;
	regex rgx("-{0,1}\\d+");

	string matrixLine;
	unsigned matrixLineNum = 0;
	double element;
	
	while (getline(input, matrixLine))
	{
		for (unsigned i = 0; i < 3; i++)
		{
			if (!regex_search(matrixLine, searchResult, rgx))
			{
				return false;
			}
			
			if (!StrToFloat(searchResult.str(), element))
			{
				return false;
			}

			matrix[matrixLineNum][i] = element;
			matrixLine = searchResult.suffix().str();
		}

		++matrixLineNum;
		
		if (matrixLineNum > 2)
		{
			break;
		}
	}

	if (matrixLineNum != 3)
	{
		return false;
	}

	return true;
}

double MatrixDeterminant(const Matrix3x3& matrix)
{
	double determinant = 0;

	determinant = matrix[0][0] * matrix[1][1] * matrix[2][2];
	determinant += matrix[2][0] * matrix[0][1] * matrix[1][2];
	determinant += matrix[1][0] * matrix[2][1] * matrix[0][2];
	determinant -= matrix[2][0] * matrix[1][1] * matrix[0][2];
	determinant -= matrix[0][0] * matrix[2][1] * matrix[1][2];
	determinant -= matrix[1][0] * matrix[0][1] * matrix[2][2];

	return determinant;
}

float MinorOfElement(const Matrix3x3& matrix, unsigned elemLineNumber, unsigned elemColumnNumber)
{
	Matrix2x2 matrix2x2;
	unsigned line2x2 = 0;
	unsigned column2x2;

	for (unsigned line = 0; line < 3; ++line)
	{
		if (line == elemLineNumber)
		{
			continue;
		}

		column2x2 = 0;

		for (unsigned column = 0; column < 3; ++column)
		{
			if (column == elemColumnNumber)
			{
				continue;
			}

			matrix2x2[line2x2][column2x2] = matrix[line][column];
			++column2x2;
		}

		++line2x2;
	}

	return matrix2x2[0][0] * matrix2x2[1][1] - matrix2x2[1][0] * matrix2x2[0][1];
}

void MinorOfMatrix(const Matrix3x3& matrix, Matrix3x3& minorMatrix)
{
	for (unsigned line = 0; line < 3; ++line)
	{
		for (unsigned column = 0; column < 3; ++column)
		{
			minorMatrix[line][column] = MinorOfElement(matrix, line, column);
		}
	}
}

void CloneMatrix(const Matrix3x3& matrix, Matrix3x3& matrixClone)
{
	for (unsigned line = 0; line < 3; ++line)
	{
		for (unsigned column = 0; column < 3; ++column)
		{
			matrixClone[line][column] = matrix[line][column];
		}
	}
}

void AdjugateOfMatrix(const Matrix3x3& matrix, Matrix3x3& addMatrix)
{
	CloneMatrix(matrix, addMatrix);

	addMatrix[0][1] = -addMatrix[0][1];
	addMatrix[1][0] = -addMatrix[1][0];
	addMatrix[1][2] = -addMatrix[1][2];
	addMatrix[2][1] = -addMatrix[2][1];
}

void TransposeMatrix(const Matrix3x3& matrix, Matrix3x3& transposedMatrix)
{
	for (unsigned line = 0; line < 3; ++line)
	{
		for (unsigned column = 0; column < 3; ++column)
		{
			transposedMatrix[column][line] = matrix[line][column];
		}
	}
}

bool Invert(const Matrix3x3& matrix, Matrix3x3& invertMatrix)
{
	double determinant = MatrixDeterminant(matrix);

	if (!determinant)
	{
		return false;
	}

	Matrix3x3 minor;
	MinorOfMatrix(matrix, minor);

	Matrix3x3 additionsMinor;
	AdjugateOfMatrix(minor, additionsMinor);

	Matrix3x3 transpAddMinor;
	TransposeMatrix(additionsMinor, transpAddMinor);

	for (unsigned line = 0; line < 3; ++line)
	{
		for (unsigned column = 0; column < 3; ++column)
		{
			invertMatrix[line][column] = transpAddMinor[line][column] / determinant;
		}
	}

	return true;
}