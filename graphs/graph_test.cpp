#include <chrono>
#include <gtest/gtest.h>
#include "graph.h"

class GraphTest : public testing::Test {
public:
	Graph<std::string, int> g;
};

TEST_F(GraphTest, isCreatedEmpty)
{
	EXPECT_EQ(0, g.vertexes().size());
}

TEST_F(GraphTest, add) {
	EXPECT_TRUE(g.add("a"));
	EXPECT_EQ(1, g.vertexes().size());
}

TEST_F(GraphTest, addRepeated) {
	EXPECT_TRUE(g.add("a"));
	EXPECT_FALSE(g.add("a"));
	EXPECT_EQ(1, g.vertexes().size());
}

TEST_F(GraphTest, connect)
{
    ASSERT_TRUE(g.add("a"));
    ASSERT_TRUE(g.add("b"));
    EXPECT_TRUE(g.connect("a", "b", 5));
    EXPECT_EQ(1, g.connections("a").size());
}

TEST_F(GraphTest, remove) {
	ASSERT_TRUE(g.add("a"));
	ASSERT_TRUE(g.add("b"));
	ASSERT_TRUE(g.connect("a", "b", 1));
	ASSERT_EQ(2, g.vertexes().size());
    ASSERT_EQ(1, g.connections("a").size());
	EXPECT_NO_THROW(g.remove("b"));
	EXPECT_EQ(1, g.vertexes().size());
    EXPECT_EQ(0, g.connections("a").size());
}
