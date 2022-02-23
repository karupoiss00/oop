#pragma once
#include <array>
#include <optional>

constexpr unsigned SERVICE_CELL_SLOT = 1;
constexpr unsigned LABYRINTH_MAX_SIZE = 100;
constexpr unsigned REAL_LABYRINTH_MAX_SIZE = LABYRINTH_MAX_SIZE + SERVICE_CELL_SLOT;

constexpr char EMPTY_CELL_CHAR = ' ';
constexpr char WALL_CELL_CHAR = '#';
constexpr char START_POS_CELL_CHAR = 'A';
constexpr char END_POS_CELL_CHAR = 'B';
constexpr char WAY_CELL_CHAR = '.';

constexpr int LABYRINTH_CELL_EMPTY = 0;
constexpr int LABYRINTH_CELL_WALL = -1;
constexpr int LABYRINTH_CELL_START = -2;
constexpr int LABYRINTH_CELL_END = -3;
constexpr int LABYRINTH_CELL_WAY = -4;
constexpr int LABYRINTH_CELL_EOL = -5;
constexpr int LABYRINTH_CELL_EOF = -6;

using Cell = int;

struct Coordinates
{
	unsigned m_x;
	unsigned m_y;

	Coordinates()
		: m_x(0), m_y(0) {};
	Coordinates(unsigned x, unsigned y)
		: m_x(x), m_y(y) {};
};

struct CellData
{
	Coordinates m_coords;
	Cell m_value;

	CellData(Coordinates coords, Cell value)
		: m_coords(coords), m_value(value) {};
};

using LabyrinthLine = std::array<Cell, REAL_LABYRINTH_MAX_SIZE>;
using Labyrinth = std::array<LabyrinthLine, REAL_LABYRINTH_MAX_SIZE>;

std::optional<Labyrinth> ReadLabyrinth(std::istream& input);
void WriteLabyrinth(std::ostream& output, const Labyrinth& labyrinth, bool& wasError);
void PaveShortestWay(Labyrinth& labyrinth, bool& wasError);