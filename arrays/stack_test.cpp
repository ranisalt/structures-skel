#include <gtest/gtest.h>
#include "stack.h"

class StackTest : public testing::Test {
public:
	stack<int, 30> s;
};

TEST_F(StackTest, isCreatedEmpty)
{
	EXPECT_TRUE(s.empty());
	EXPECT_EQ(0, s.size());
}

TEST_F(StackTest, top)
{
	s.push(42);
	EXPECT_EQ(s.top(), 42);
	s.push(1963);
	EXPECT_EQ(s.top(), 1963);
}

TEST_F(StackTest, size)
{
	s.push(42);
	EXPECT_EQ(1, s.size());
	s.push(1963);
	EXPECT_EQ(2, s.size());
}

TEST_F(StackTest, pushLvalueReference)
{
	int n = 42;
	s.push(n);
	EXPECT_EQ(1, s.size());
	EXPECT_EQ(s.top(), n);
}

TEST_F(StackTest, pushRvalueReference)
{
	s.push(42);
	EXPECT_EQ(1, s.size());
	EXPECT_EQ(s.top(), 42);
}

TEST_F(StackTest, pop)
{
	s.push(42);
	s.push(1963);
	ASSERT_EQ(2, s.size());
	s.pop();
	EXPECT_EQ(1, s.size());
}

TEST_F(StackTest, pushLvalueToFullStackThrows)
{
	int n = 42;
	for (auto i = 0; i < 30; ++i) {
		s.push(n);
	}
	EXPECT_THROW(s.push(n), std::out_of_range);
}

TEST_F(StackTest, pushRvalueToFullStackThrows)
{
	for (auto i = 0; i < 30; ++i) {
		s.push(42);
	}
	EXPECT_THROW(s.push(42), std::out_of_range);
}

TEST_F(StackTest, swap)
{
	s.push(42);

	stack<int, 30> t;
	t.push(1963);

	std::swap(s, t);
	EXPECT_EQ(s.top(), 1963);
	EXPECT_EQ(t.top(), 42);
}
