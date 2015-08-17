#include <gtest/gtest.h>
#include "queue.h"

class QueueTest : public testing::Test {
public:
	queue<int, 30> q;
};

TEST_F(QueueTest, isCreatedEmpty)
{
	EXPECT_TRUE(q.empty());
	EXPECT_EQ(0, q.size());
}

TEST_F(QueueTest, front)
{
	q.push(42);
	EXPECT_EQ(q.front(), 42);
	q.push(1963);
	EXPECT_EQ(q.front(), 42);
	q.pop();
	EXPECT_EQ(q.front(), 1963);
}

TEST_F(QueueTest, back)
{
	q.push(42);
	EXPECT_EQ(q.front(), 42);
	q.push(1963);
	EXPECT_EQ(q.back(), 1963);
	q.pop();
	EXPECT_EQ(q.front(), 1963);
}

TEST_F(QueueTest, size)
{
	q.push(42);
	EXPECT_EQ(1, q.size());
	q.push(1963);
	EXPECT_EQ(2, q.size());
}

TEST_F(QueueTest, pushLvalueReference)
{
	int n = 42;
	q.push(n);
	EXPECT_EQ(1, q.size());
	EXPECT_EQ(q.front(), n);
}

TEST_F(QueueTest, pushRvalueReference)
{
	q.push(42);
	EXPECT_EQ(1, q.size());
	EXPECT_EQ(q.front(), 42);
}

TEST_F(QueueTest, pop)
{
	q.push(42);
	q.push(1963);
	ASSERT_EQ(2, q.size());
	q.pop();
	EXPECT_EQ(1, q.size());
}

TEST_F(QueueTest, pushLvalueToFullQueueThrows)
{
	int n = 42;
	for (auto i = 0; i < 30; ++i) {
		q.push(n);
	}
	EXPECT_THROW(q.push(n), std::out_of_range);
}

TEST_F(QueueTest, pushRvalueToFullQueueThrows)
{
	for (auto i = 0; i < 30; ++i) {
		q.push(42);
	}
	EXPECT_THROW(q.push(42), std::out_of_range);
}

TEST_F(QueueTest, swap)
{
	q.push(42);

	queue<int, 30> r;
	r.push(1963);

	std::swap(q, r);
	EXPECT_EQ(q.front(), 1963);
	EXPECT_EQ(r.front(), 42);
}
