#include "../gtest/gtest.h"
#include "stack.h"

class StackTest : public testing::Test {
public:
	stack<int, 30> q;
};

TEST_F(StackTest, defaultCtor) {
	EXPECT_EQ(0, q.size());
}
