#include <catch2/catch.hpp>
#include <string>
#include "../my_list/CMyList.h"

using namespace std;

struct ListFixture
{
	CList<string> list;
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
		CList<string>::Iterator it = list.begin();
		CHECK(*it == "added str");
	}

	SECTION("get access from end iterator")
	{
		CList<string>::Iterator it = list.end();
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
		CList<string>::Iterator it = list.begin();

		CHECK(*it == "first");
		++it;
		CHECK(*it == "second");
		--it;
		CHECK(*it == "first");
	}

	SECTION("cbegin")
	{
		CList<string>::ConstIterator it = list.cbegin();

		CHECK(*it == "first");
		++it;
		CHECK(*it == "second");
		--it;
		CHECK(*it == "first");
	}

	SECTION("rbegin")
	{
		CList<string>::ReverseIterator it = list.rbegin();

		CHECK(*it == "third");
		++it;
		CHECK(*it == "second");
	}

	SECTION("rcbegin")
	{
		CList<string>::ConstReverseIterator it = list.rcbegin();

		CHECK(*it == "third");
		++it;
		CHECK(*it == "second");
	}

	SECTION("end")
	{
		CList<string>::Iterator it = list.end();

		--it;
		CHECK(*it == "third");
		--it;
		CHECK(*it == "second");
	}

	SECTION("cend")
	{
		CList<string>::ConstIterator it = list.cend();

		--it;
		CHECK(*it == "third");
		--it;
		CHECK(*it == "second");
	}

	SECTION("rend")
	{
		CList<string>::ReverseIterator it = list.rend();

		--it;
		CHECK(*it == "first");
		--it;
		CHECK(*it == "second");
	}

	SECTION("rcend")
	{
		CList<string>::ConstReverseIterator it = list.rcend();

		--it;
		CHECK(*it == "first");
		--it;
		CHECK(*it == "second");
	}
}

TEST_CASE_METHOD(ListFixture, "")
{
	list.PushBack("first");
	list.PushBack("third");

	CList<string>::Iterator it = list.begin();
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

	CList<string>::Iterator it = list.begin();
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