#include <../gtest/gtest.h>
#include "MultiStack.h"

TEST(multistack, can_create_default_multistack)
{
	ASSERT_NO_THROW(MultiStack<int> A);
}

TEST(multistack, cannot_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(MultiStack<int> A(-1, -1));
}

TEST(multistack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(MultiStack<int> A(3, 6));
}

TEST(multistack, can_copy_stack)
{
	MultiStack <int> B(3, 6);
	ASSERT_NO_THROW(MultiStack<int> A(B));
}

TEST(multistack, can_push_and_pull)
{
	MultiStack<int> A(1, 1);
	A.push(0, 1);

	EXPECT_EQ(1, A.pop(0));
}

TEST(multistack, can_push_and_pull_all_size)
{
	MultiStack<int> A(1, 3);

	A.push(0, 1);
	A.push(0, 2);
	A.push(0, 7);

	EXPECT_EQ(7, A.pop(0));
	EXPECT_EQ(2, A.pop(0));
	EXPECT_EQ(1, A.pop(0));
}

TEST(multistack, can_not_push_out_of_size)
{
	MultiStack<int> A(1, 3);

	A.push(0, 1);
	A.push(0, 2);
	A.push(0, 7);

	ASSERT_ANY_THROW(A.push(0, 99));
}

TEST(multistack, can_not_pull_out_of_size)
{
	MultiStack<int> A(1, 1);

	ASSERT_ANY_THROW(A.pop(0));
}

TEST(multistack, can_copy_stack_with_any_elements)
{
	MultiStack<int> A(1, 3);

	A.push(0, 1);
	A.push(0, 2);
	A.push(0, 7);

	MultiStack<int> B(A);
	EXPECT_EQ(7, B.pop(0));
	EXPECT_EQ(2, B.pop(0));
	EXPECT_EQ(1, B.pop(0));
}

TEST(multistack, reallocation_works)
{
	MultiStack<int> a(3, 10);
	a.push(0, 99);
	a.push(0, 99);
	a.push(0, 99);

	a.push(1, 11);
	a.push(1, 11);

	a.push(2, 22);
	a.push(2, 22);

	a.push(0, 66);
	a.push(0, 9);

	a.push(1, 10);
}