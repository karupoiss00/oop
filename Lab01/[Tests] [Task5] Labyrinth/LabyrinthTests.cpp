#include <iostream>
#include <catch2/catch.hpp>
#include <sstream>
#include "[Task5] Labyrinth/Labyrinth.h"

TEST_CASE("Labyrinth: empty input")
{
	std::istringstream inputLabyrinth("");

	auto labyrinth = ReadLabyrinth(inputLabyrinth);

	REQUIRE(labyrinth);

	if (labyrinth)
	{
		bool wasError = false;

		PaveShortestWay(labyrinth.value(), wasError);
		REQUIRE(wasError);
	}
}

TEST_CASE("Labyrinth: Invalid character")
{
	std::istringstream inputLabyrinth(
		"###############\n"
		"#            B#\n"
		"#             #\n"
		"#      H      #\n"
		"#             #\n"
		"#A            #\n"
		"###############\n");

	auto labyrinth = ReadLabyrinth(inputLabyrinth);

	REQUIRE(!labyrinth);
}

TEST_CASE("Labyrinth: No start point")
{
	std::istringstream inputLabyrinth(
		"###############\n"
		"#            B#\n"
		"#             #\n"
		"#             #\n"
		"#             #\n"
		"#             #\n"
		"###############\n");

	auto labyrinth = ReadLabyrinth(inputLabyrinth);

	REQUIRE(labyrinth);

	if (labyrinth)
	{
		bool wasError = false;

		PaveShortestWay(labyrinth.value(), wasError);
		REQUIRE(wasError);
	}
}

TEST_CASE("Labyrinth: No end point")
{
	std::istringstream inputLabyrinth(
		"###############\n"
		"#             #\n"
		"#             #\n"
		"#             #\n"
		"#             #\n"
		"#A            #\n"
		"###############\n");

	auto labyrinth = ReadLabyrinth(inputLabyrinth);

	REQUIRE(labyrinth);

	if (labyrinth)
	{
		bool wasError = false;

		PaveShortestWay(labyrinth.value(), wasError);
		REQUIRE(wasError);
	}
}

TEST_CASE("Labyrinth: Two start points")
{
	std::istringstream inputLabyrinth(
		"###############\n"
		"#A           B#\n"
		"#             #\n"
		"#             #\n"
		"#             #\n"
		"#A            #\n"
		"###############\n");

	auto labyrinth = ReadLabyrinth(inputLabyrinth);

	REQUIRE(labyrinth);

	if (labyrinth)
	{
		bool wasError = false;

		PaveShortestWay(labyrinth.value(), wasError);
		REQUIRE(wasError);
	}
}

TEST_CASE("Labyrinth: Two end points")
{
	std::istringstream inputLabyrinth(
		"###############\n"
		"#B           B#\n"
		"#             #\n"
		"#             #\n"
		"#             #\n"
		"#A            #\n"
		"###############\n");

	auto labyrinth = ReadLabyrinth(inputLabyrinth);

	REQUIRE(labyrinth);

	if (labyrinth)
	{
		bool wasError = false;

		PaveShortestWay(labyrinth.value(), wasError);
		REQUIRE(wasError);
	}
}

TEST_CASE("Labyrinth: No way")
{
	std::istringstream inputLabyrinth(
		"###############\n"
		"#            B#\n"
		"#             #\n"
		"###############\n"
		"#             #\n"
		"#A            #\n"
		"###############\n");
	std::ostringstream outputLabyrinthWithWay;
	const std::string labyrinthWithWay =
		"###############\n"
		"#            B#\n"
		"#             #\n"
		"###############\n"
		"#             #\n"
		"#A            #\n"
		"###############\n";
	auto labyrinth = ReadLabyrinth(inputLabyrinth);

	REQUIRE(labyrinth);

	if (labyrinth)
	{
		bool wasError = false;

		PaveShortestWay(labyrinth.value(), wasError);
		WriteLabyrinth(outputLabyrinthWithWay, labyrinth.value(), wasError);

		REQUIRE(!wasError);
		REQUIRE(labyrinthWithWay == outputLabyrinthWithWay.str());
	}
}

TEST_CASE("Labyrinth: Simple labyrinth")
{
	std::istringstream inputLabyrinth(
		"###############\n"
		"#            B#\n"
		"#             #\n"
		"#             #\n"
		"#             #\n"
		"#A            #\n"
		"###############\n");
	std::ostringstream outputLabyrinthWithWay;
	const std::string labyrinthWithWay =
		"###############\n"
		"#            B#\n"
		"#            .#\n"
		"#            .#\n"
		"#            .#\n"
		"#A............#\n"
		"###############\n";
	auto labyrinth = ReadLabyrinth(inputLabyrinth);

	REQUIRE(labyrinth);

	if (labyrinth)
	{
		bool wasError = false;

		PaveShortestWay(labyrinth.value(), wasError);
		WriteLabyrinth(outputLabyrinthWithWay, labyrinth.value(), wasError);

		REQUIRE(!wasError);
		REQUIRE(labyrinthWithWay == outputLabyrinthWithWay.str());
	}
}

TEST_CASE("Labyrinth: Complicated labyrinth")
{
	std::istringstream inputLabyrinth(
		"###############\n"
		"#B     #      #\n"
		"###### # ### ##\n"
		"#    #   #    #\n"
		"# ## #####    #\n"
		"# A#          #\n"
		"###############\n");
	std::ostringstream outputLabyrinthWithWay;
	const std::string labyrinthWithWay =
		"###############\n"
		"#B.....#..... #\n"
		"######.#.###.##\n"
		"#....#...#  . #\n"
		"#.##.#####  . #\n"
		"#.A#......... #\n"
		"###############\n";
	auto labyrinth = ReadLabyrinth(inputLabyrinth);

	REQUIRE(labyrinth);

	if (labyrinth)
	{
		bool wasError = false;

		PaveShortestWay(labyrinth.value(), wasError);
		WriteLabyrinth(outputLabyrinthWithWay, labyrinth.value(), wasError);
		
		REQUIRE(!wasError);
		REQUIRE(labyrinthWithWay == outputLabyrinthWithWay.str());
	}
}