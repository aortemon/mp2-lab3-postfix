#include <gtest.h>
#include "Stack.h"

TEST(Stack, default_ctor_creates_object) {
	ASSERT_NO_THROW(Stack<int> st);
}

TEST(Stack, length_ctor_creates_object) {
	ASSERT_NO_THROW(Stack<int> st(5));
}

TEST(Stack, length_ctor_throws_when_negative_length) {
	ASSERT_ANY_THROW(Stack<int> st(-5));
}

TEST(Stack, push_adds_new_elem) {
	Stack<int> st;
	ASSERT_NO_THROW(st.push(5));
}

TEST(Stack, getsize_returns_size) {
	Stack<int> st;
	st.push(1);
	EXPECT_EQ(1, st.getSize());
}

TEST(Stack, enlarges_when_overflows) {
	Stack<int> st(2);
	st.push(1);
	st.push(2);
	ASSERT_NO_THROW(st.push(3));
}

TEST(Stack, top_returns_latest_elem) {
	Stack<int> st;
	st.push(5);
	EXPECT_EQ(st.top(), 5);
}

TEST(Stack, pop_removes_latest_elem) {
	Stack<int> st;
	st.push(5);
	st.pop();
	EXPECT_EQ(st.getSize(), 0);
}

TEST(Stack, pop_returns_removed_elem) {
	Stack<int> st;
	st.push(7);
	EXPECT_EQ(st.pop(), 7);
}

TEST(Stack, is_empty_returns_true_on_empty_stack) {
	Stack<int> st;
	EXPECT_TRUE(st.isEmpty());
}

TEST(Stack, is_empty_returns_false_on_nonempty_stack) {
	Stack<int> st;
	st.push(7);
	EXPECT_FALSE(st.isEmpty());
}

TEST(Stack, throws_when_top_on_empty_stack) {
	Stack<int> st;
	ASSERT_ANY_THROW(st.top());
}

TEST(Stack, throws_when_pop_on_empty_stack) {
	Stack<int> st;
	ASSERT_ANY_THROW(st.pop());
}
