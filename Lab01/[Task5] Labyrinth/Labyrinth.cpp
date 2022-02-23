#include <iostream> 
#include <queue>
#include <algorithm>
#include <sstream>
#include <istream>
#include <fstream>
#include "Labyrinth.h"

using namespace std;

optional<Cell> MapCharToCell(char ch)
{
	switch (ch)
	{
		case START_POS_CELL_CHAR:
			return LABYRINTH_CELL_START;
		case END_POS_CELL_CHAR:
			return LABYRINTH_CELL_END;
		case EMPTY_CELL_CHAR:
			return LABYRINTH_CELL_EMPTY;
		case WALL_CELL_CHAR:
			return LABYRINTH_CELL_WALL;	
		default:
			cout << "Error! Unknown symbol: " << ch << endl;
			return nullopt;
	}
}

optional<char> MapCellToChar(Cell cell)
{
	switch (cell)
	{
		case LABYRINTH_CELL_EMPTY:
			return EMPTY_CELL_CHAR;
		case LABYRINTH_CELL_WALL:
			return WALL_CELL_CHAR;
		case LABYRINTH_CELL_WAY:
			return WAY_CELL_CHAR;
		case LABYRINTH_CELL_START:
			return START_POS_CELL_CHAR;
		case LABYRINTH_CELL_END:
			return END_POS_CELL_CHAR;
		case LABYRINTH_CELL_EOL:
			return '\n';
		case LABYRINTH_CELL_EOF:
			return EOF;
		default:
			cout << "Unexpected cell value" << endl;
			return nullopt;
	}
}

bool IsValidLabyrinth(const Labyrinth& labyrinth)
{
	unsigned countOfStartCells = 0;
	unsigned countOfEndCells = 0;

	for (LabyrinthLine labLine : labyrinth)
	{
		for (Cell cell : labLine)
		{
			if (cell == LABYRINTH_CELL_EOF)
			{
				return countOfStartCells == 1 && countOfEndCells == 1;
			}
			if (cell == LABYRINTH_CELL_EOL)
			{
				break;
			}
			if (cell == LABYRINTH_CELL_START)
			{
				countOfStartCells++;
			}
			if (cell == LABYRINTH_CELL_END)
			{
				countOfEndCells++;
			}
		}
	}
	return countOfStartCells == 1 && countOfEndCells == 1;
}

optional<LabyrinthLine> ReadLabyrinthLine(const string& line)
{
	LabyrinthLine labyrinthLine;
	unsigned i = 0;

	for (char ch : line)
	{
		auto cell = MapCharToCell(ch);
		if (!cell)
		{
			return nullopt;
		}
		labyrinthLine[i] = cell.value();
		i++;
	}
	 
	return labyrinthLine;
}

optional<Labyrinth> ReadLabyrinth(istream& input)
{
	Labyrinth labyrinth;
	string line;
	unsigned y = 0;

	while (getline(input, line))
	{
		line.erase(remove(line.begin(), line.end(), '\r'), line.end());

		if (y > LABYRINTH_MAX_SIZE)
		{
			cout << "Error! Labyrinth height bigger than " << LABYRINTH_MAX_SIZE << endl;
			return nullopt;
		}

		if (line.length() > LABYRINTH_MAX_SIZE)
		{
			cout << "Error! Labyrinth width bigger than " << LABYRINTH_MAX_SIZE << endl;
			return nullopt;
		}

		auto labyrinthLine = ReadLabyrinthLine(line);

		if (!labyrinthLine)
		{
			return nullopt;
		}

		labyrinth[y] = labyrinthLine.value();
		labyrinth[y][line.length()] = LABYRINTH_CELL_EOL;
		y++;
	}
	labyrinth[y][0] = LABYRINTH_CELL_EOF;

	if (input.bad())
	{
		cout << "Falied to read data from input file" << endl;
		return nullopt;
	}

	return labyrinth;
}

void WriteLabyrinth(ostream& output, const Labyrinth& labyrinth, bool& wasError)
{
	for (LabyrinthLine labLine : labyrinth)
	{
		for (Cell cell : labLine)
		{
			if (cell == LABYRINTH_CELL_EOF)
			{
				return;
			}
			if (cell == LABYRINTH_CELL_EOL)
			{
				output << endl;
				break;
			}

			auto ch = MapCellToChar(cell);
			if (!ch)
			{
				wasError = true;
				return;
			}
			output << ch.value();
		}
	}

	if (output.flush())
	{
		wasError = true;
		cout << "Failed to write data to output file" << endl;
	}

	return;
};

optional<Coordinates> FindFirstCellByType(const Labyrinth& labyrinth, Cell cellType)
{
	unsigned x = 0;
	unsigned y = 0;

	for (LabyrinthLine labLine : labyrinth)
	{
		for (Cell cell : labLine)
		{
			if (cell == LABYRINTH_CELL_EOL)
			{
				x = 0;
				break;
			}
			if (cell == LABYRINTH_CELL_EOF)
			{
				return nullopt;
			}
			if (cell == cellType)
			{
				return Coordinates(x, y);
			}
			x++;
		}
		y++;
	}

	return nullopt;
}

void SpreadWave(std::queue<CellData>& queue, const CellData & waveCell)
{
	if (waveCell.m_coords.m_x - 1 >= 0)
	{
		CellData markedCell = CellData
		{
			Coordinates(waveCell.m_coords.m_x - 1, waveCell.m_coords.m_y),
			waveCell.m_value + 1
		};
		queue.push(markedCell);
	}
	if (waveCell.m_coords.m_y - 1 >= 0)
	{
		CellData markedCell = CellData
		{
			Coordinates(waveCell.m_coords.m_x, waveCell.m_coords.m_y - 1),
			waveCell.m_value + 1
		};
		queue.push(markedCell);
	}
	if (waveCell.m_coords.m_x + 1 < LABYRINTH_MAX_SIZE)
	{
		CellData markedCell = CellData
		{
			Coordinates(waveCell.m_coords.m_x + 1, waveCell.m_coords.m_y),
			waveCell.m_value + 1
		};
		queue.push(markedCell);
	}
	if (waveCell.m_coords.m_y + 1 < LABYRINTH_MAX_SIZE)
	{
		CellData markedCell = CellData
		{
			Coordinates(waveCell.m_coords.m_x, waveCell.m_coords.m_y + 1),
			waveCell.m_value + 1
		};
		queue.push(markedCell);
	}
}

Labyrinth LabyrinthWaveFill(Labyrinth labyrinth)
{
	Labyrinth filledLabyrinth = labyrinth;
	std::queue<CellData> waveQueue;

	auto startCoordinates = FindFirstCellByType(labyrinth, LABYRINTH_CELL_START);
	
	waveQueue.push({ startCoordinates.value(), 0 });

	while (!waveQueue.empty())
	{
		auto waveCell = waveQueue.front();
		waveQueue.pop();

		Cell& labyrinthCellValue = filledLabyrinth[waveCell.m_coords.m_y][waveCell.m_coords.m_x];
		if (labyrinthCellValue == LABYRINTH_CELL_END)
		{
			break;
		}
		if (labyrinthCellValue == LABYRINTH_CELL_WALL)
		{
			continue;
		}
		if (labyrinthCellValue == LABYRINTH_CELL_START)
		{
			SpreadWave(waveQueue, waveCell);
		}
		if (labyrinthCellValue == LABYRINTH_CELL_EMPTY)
		{
			labyrinthCellValue = waveCell.m_value;
			SpreadWave(waveQueue, waveCell);
		}
	}
	return filledLabyrinth;
}

optional<Cell> GetCellValue(const Labyrinth& labyrinth, int x, int y)
{
	if (x < 0 
		|| x >= LABYRINTH_MAX_SIZE
		|| y < 0 
		|| y >= LABYRINTH_MAX_SIZE)
	{
		return nullopt;
	}
	return labyrinth[y][x];
}


optional<Coordinates> SearchNextNeighbour(const Labyrinth& labyrinth, const Coordinates& curCell)
{
	Cell minCell = 0;
	Coordinates minCellCoordinates;
	bool isMinFound = false;

	auto upperCell = GetCellValue(labyrinth, curCell.m_x, curCell.m_y - 1);
	if (upperCell && upperCell.value() > 0 || upperCell.value() == LABYRINTH_CELL_START)
	{
		isMinFound = true;
		minCellCoordinates = Coordinates(curCell.m_x, curCell.m_y - 1);
		minCell = upperCell.value();
	}

	auto rightCell = GetCellValue(labyrinth, curCell.m_x + 1, curCell.m_y);
	if (rightCell && rightCell.value() > 0 || rightCell.value() == LABYRINTH_CELL_START)
	{
		if (!isMinFound || (rightCell < minCell))
		{
			minCellCoordinates = Coordinates(curCell.m_x + 1, curCell.m_y);
			minCell = rightCell.value();
			isMinFound = true;
		}
	}

	auto lowerCell = GetCellValue(labyrinth, curCell.m_x, curCell.m_y + 1);
	if (lowerCell && lowerCell.value() > 0 || lowerCell.value() == LABYRINTH_CELL_START)
	{
		if (!isMinFound || (lowerCell < minCell))
		{
			minCellCoordinates = Coordinates(curCell.m_x, curCell.m_y + 1);
			minCell = lowerCell.value();
			isMinFound = true;
		}
	}

	auto leftCell = GetCellValue(labyrinth, curCell.m_x - 1, curCell.m_y);
	if (leftCell && leftCell.value() > 0 || leftCell.value() == LABYRINTH_CELL_START)
	{
		if (!isMinFound || (leftCell < minCell))
		{
			minCellCoordinates = Coordinates(curCell.m_x - 1, curCell.m_y);
			minCell = leftCell.value();
			isMinFound = true;
		}
	}

	return isMinFound ? optional<Coordinates>(minCellCoordinates) : nullopt;
}

void PaveShortestWay(Labyrinth & labyrinth, bool & wasError)
{
	if (!IsValidLabyrinth(labyrinth))
	{
		cout << "Cannot find start or end cell or count of they more than 1" << endl;
		wasError = true;
		return;
	}

	Labyrinth wavedLabyrinth = LabyrinthWaveFill(labyrinth);
	Labyrinth labyrinthWithWay = labyrinth;

	auto exitCellCoordinates = FindFirstCellByType(wavedLabyrinth, LABYRINTH_CELL_END);
	if (!exitCellCoordinates)
	{
		cout << "Error: end cell not found" << endl;
		return;
	}

	Coordinates currentCell = exitCellCoordinates.value();

	while (true)
	{
		auto nextCell = SearchNextNeighbour(wavedLabyrinth, currentCell);

		if (!nextCell)
		{
			return;
		}

		if (labyrinthWithWay[nextCell->m_y][nextCell->m_x] == LABYRINTH_CELL_START)
		{
			labyrinth = labyrinthWithWay;
			return;
		}
		labyrinthWithWay[nextCell->m_y][nextCell->m_x] = LABYRINTH_CELL_WAY;

		currentCell = nextCell.value();
	}
};