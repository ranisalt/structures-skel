#include <chrono>
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

TEST_F(QueueTest, stressInsertion)
{
	using us = std::chrono::microseconds;
	using clock = std::chrono::high_resolution_clock;

	const int qty = 1 << 20;
	queue<int, qty> r;

	auto start = clock::now();
	for (auto i = 0; i < qty; ++i) {
		r.push(i);
		ASSERT_EQ(i, r.back());
	}
	auto duration = std::chrono::duration_cast<us>(clock::now() - start);

	EXPECT_GE(100000, duration.count());
}

TEST_F(QueueTest, stressRemoval)
{
	/**
	 * This test is a bit more stressful than stack's removal or queue's
	 * insertion because array queues need to shift the entire container
	 * left when popping, thus we use a smaller array and increased timeout
	 * accordingly.
	 */

	using us = std::chrono::microseconds;
	using clock = std::chrono::high_resolution_clock;

	const int qty = 1 << 15;
	queue<int, qty> r;

	for (auto i = 0; i < qty; ++i) {
		r.push(i);
	}

	auto start = clock::now();
	for (auto i = 0; i < qty; ++i) {
		ASSERT_EQ(i, r.front());
		r.pop();
	}
	auto duration = std::chrono::duration_cast<us>(clock::now() - start);

	EXPECT_GE(120000, duration.count());
}
