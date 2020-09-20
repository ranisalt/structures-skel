#include <gtest/gtest.h>
#include "doubly_linked_list.h"

class doubly_linked_list_test: public testing::Test {
public:
	doubly_linked_list<int> list;
};

TEST_F(doubly_linked_list_test, isCreatedEmpty) {
	EXPECT_EQ(0, list.size());
}

TEST_F(doubly_linked_list_test, pushBackPushesOnBack) {
	list.push_back(42);
	EXPECT_EQ(1, list.size());
	EXPECT_EQ(42, list.at(0));
	list.push_back(1963);
	EXPECT_EQ(42, list.at(0));
	EXPECT_EQ(1963, list.at(1));
	EXPECT_EQ(2, list.size());
}

TEST_F(doubly_linked_list_test, pushFrontPushesOnFront) {
	list.push_front(42);
	EXPECT_EQ(1, list.size());
	EXPECT_EQ(42, list.at(0));
	list.push_front(1963);
	EXPECT_EQ(1963, list.at(0));
	EXPECT_EQ(42, list.at(1));
	EXPECT_EQ(2, list.size());
}

TEST_F(doubly_linked_list_test, insert) {
	list.push_back(42);
	list.push_back(13);
	list.push(1, 1963);
	EXPECT_EQ(42, list.at(0));
	EXPECT_EQ(1963, list.at(1));
	EXPECT_EQ(13, list.at(2));
	EXPECT_EQ(3, list.size());
}

TEST_F(doubly_linked_list_test, popBack) {
	list.push_back(42);
	list.push_back(1963);
	EXPECT_EQ(1963, list.pop_back());
	EXPECT_EQ(1, list.size());
}

TEST_F(doubly_linked_list_test, popFront) {
	list.push_back(42);
	list.push_back(1963);
	EXPECT_EQ(42, list.pop_front());
	EXPECT_EQ(1, list.size());
}

TEST_F(doubly_linked_list_test, remove) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);
	EXPECT_EQ(1963, list.pop(1));
	EXPECT_EQ(2, list.size());
}

TEST_F(doubly_linked_list_test, accessOutOfRange) {
	EXPECT_THROW(list.at(13), std::out_of_range);
	EXPECT_THROW(list.push(13, 42), std::out_of_range);
	EXPECT_THROW(list.pop(13), std::out_of_range);
}

TEST_F(doubly_linked_list_test, boundariesWithNoProblems) {
	list.push(0, 42);
	EXPECT_EQ(1, list.size());
	EXPECT_EQ(42, list.at(0));
	EXPECT_EQ(42, list.pop(0));
	EXPECT_EQ(0, list.size());
}

TEST_F(doubly_linked_list_test, removalsFromEmptyThrow) {
	EXPECT_THROW(list.pop_back(), std::out_of_range);
	EXPECT_THROW(list.pop_front(), std::out_of_range);
	EXPECT_THROW(list.pop(13), std::out_of_range);
}

TEST_F(doubly_linked_list_test, equalReferenceOperatorIsCorrect) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);

	auto other = doubly_linked_list<int> { };
	other.push_back(42);
	other.push_back(1963);
	other.push_back(13);

	EXPECT_EQ(list, other);
}

TEST_F(doubly_linked_list_test, equalInitializerListOperatorIsCorrect) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);

	EXPECT_EQ(list, std::initializer_list<int>({ 42, 1963, 13 }));
}

TEST_F(doubly_linked_list_test, copyConstructIsCreatedCorrect) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);

	auto copy = doubly_linked_list<int> { list };
	EXPECT_EQ(list, copy);
}

TEST_F(doubly_linked_list_test, moveConstructIsCreatedCorrect) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);

	auto move = doubly_linked_list<int> { std::move(list) };
	EXPECT_EQ(0, list.size());
	EXPECT_EQ(42, move.at(0));
	EXPECT_EQ(1963, move.at(1));
	EXPECT_EQ(13, move.at(2));
	EXPECT_EQ(3, move.size());
}

TEST_F(doubly_linked_list_test, constructByInitializerList) {
	auto list = doubly_linked_list<int> { 42, 1963, 13 };
	EXPECT_EQ(42, list.at(0));
	EXPECT_EQ(1963, list.at(1));
	EXPECT_EQ(13, list.at(2));
	EXPECT_EQ(3, list.size());
}

TEST_F(doubly_linked_list_test, forwardIteratorIsCreatedCorrect) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);
	auto it = list.begin();
	EXPECT_EQ(42, *it);
}

TEST_F(doubly_linked_list_test, forwardIteratorAdvance) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);
	auto it = list.begin();
	EXPECT_EQ(42, *it);
	++it;
	EXPECT_EQ(1963, *it);
	++it;
	EXPECT_EQ(13, *it);
	++it;
	EXPECT_EQ(list.end(), it);
}

TEST_F(doubly_linked_list_test, backwardIteratorIsCreatedCorrect) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);
	auto it = list.rbegin();
	EXPECT_EQ(13, *it);
}

TEST_F(doubly_linked_list_test, backwardIteratorRegress) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);
	auto it = list.rbegin();
	EXPECT_EQ(13, *it);
	--it;
	EXPECT_EQ(1963, *it);
	--it;
	EXPECT_EQ(42, *it);
	--it;
	EXPECT_EQ(list.rend(), it);
}
