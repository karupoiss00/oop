#include <catch2/catch.hpp>
#include <string>
#include "../StringList/StringList.h"

using namespace std;

void CheckListsEquality(const CStringList& lhs, const CStringList rhs)
{
	auto lhsIt = lhs.cbegin();
	auto rhsIt = rhs.cbegin();

	REQUIRE(lhs.GetSize() == rhs.GetSize());

	while (lhsIt != lhs.cend())
	{
		CHECK(*lhsIt == *rhsIt);
		lhsIt++;
		rhsIt++;
	}
}

struct ListFixture
{
	CStringList list;
};

TEST_CASE_METHOD(ListFixture, "List of strings")
{
	WHEN("created")
	{
		SECTION("is empty")
		{
			CHECK(list.IsEmpty());
		}

		SECTION("has zero size")
		{
			CHECK(!list.GetSize());
		}
	}

	WHEN("copied")
	{
		CStringList copy(list);
		REQUIRE(copy.GetSize() == 0);
	}

	WHEN("assigned")
	{
		CStringList copy = list;
		REQUIRE(copy.GetSize() == 0);
	}
}

struct ListPushFrontFixture : public ListFixture
{
	ListPushFrontFixture()
	{
		list.PushFront("added str");
	}
};

TEST_CASE_METHOD(ListPushFrontFixture, "list after string inserted to beginning")
{
	SECTION("is not empty")
	{
		CHECK(!list.IsEmpty());
	}

	SECTION("has size equal 1")
	{
		CHECK(list.GetSize() == 1);
	}

	SECTION("begin iterator point to added element")
	{
		CStringList::Iterator it = list.begin();
		CHECK(*it == "added str");
	}

	SECTION("get access from end iterator")
	{
		CStringList::Iterator it = list.end();
		--it;
		CHECK(*it == "added str");
	}

}

struct ListFilledFixture : public ListFixture
{
	ListFilledFixture()
	{
		list.PushBack("first");
		list.PushBack("second");
		list.PushBack("third");
	}
};

TEST_CASE_METHOD(ListFilledFixture, "iterator returns")
{
	SECTION("begin")
	{
		CStringList::Iterator it = list.begin();
		CStringList::ConstIterator ñit = list.cbegin();
		CHECK(*it == "first");
		++it;
		CHECK(*it == "second");
		--it;
		CHECK(*it == "first");
	}

	SECTION("cbegin")
	{
		CStringList::ConstIterator it = list.cbegin();

		CHECK(*it == "first");
		++it;
		CHECK(*it == "second");
		--it;
		CHECK(*it == "first");
	}

	SECTION("rbegin")
	{
		CStringList::ReverseIterator it = list.rbegin();

		CHECK(*it == "third");
		++it;
		CHECK(*it == "second");
	}

	SECTION("rcbegin")
	{
		CStringList::ConstReverseIterator it = list.rcbegin();

		CHECK(*it == "third");
		++it;
		CHECK(*it == "second");
	}

	SECTION("end")
	{
		CStringList::Iterator it = list.end();

		--it;
		CHECK(*it == "third");
		--it;
		CHECK(*it == "second");
	}

	SECTION("cend")
	{
		CStringList::ConstIterator it = list.cend();

		--it;
		CHECK(*it == "third");
		--it;
		CHECK(*it == "second");
	}

	SECTION("rend")
	{
		CStringList::ReverseIterator it = list.rend();

		--it;
		CHECK(*it == "first");
		--it;
		CHECK(*it == "second");
	}

	SECTION("rcend")
	{
		CStringList::ConstReverseIterator it = list.rcend();

		--it;
		CHECK(*it == "first");
		--it;
		CHECK(*it == "second");
	}

	WHEN("copied")
	{
		CStringList copy(list);

		CheckListsEquality(list, copy);
	}

	WHEN("assigned")
	{
		CStringList copy;
		copy = list;

		CheckListsEquality(list, copy);
	}
}

TEST_CASE_METHOD(ListFixture, "")
{
	list.PushBack("first");
	list.PushBack("third");

	CStringList::Iterator it = list.begin();
	it = list.Insert(++it, "second");

	CHECK(list.GetSize() == 3);
	CHECK(*it == "second");
	--it;
	CHECK(*it == "first");
	++it;
	++it;
	CHECK(*it == "third");
}

TEST_CASE_METHOD(ListFixture, "removes specified element from the container")
{
	list.PushBack("first");
	list.PushBack("second");
	list.PushBack("third");

	CStringList::Iterator it = list.begin();
	++it;

	it = list.Erase(it);

	CHECK(list.GetSize() == 2);
	CHECK(*it == "third");
	--it;
	CHECK(*it == "first");
}

TEST_CASE_METHOD(ListFixture, "remove all elements")
{
	list.PushBack("first");
	list.PushBack("second");
	list.PushBack("third");

	CHECK(!list.IsEmpty());
	CHECK(list.GetSize() == 3);

	list.Clear();

	CHECK(list.IsEmpty());
	CHECK(list.GetSize() == 0);
}

TEST_CASE_METHOD(ListFixture, "move constructor")
{
	CStringList movedList(std::move(list));

	CHECK(list.IsEmpty());
	CHECK(list.GetSize() == 0);
}