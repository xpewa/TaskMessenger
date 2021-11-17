#include <gtest/gtest.h>
#include "user.h"

TEST(User, init_null) {
  User user;

  EXPECT_EQ(user.getId(), 0);
  EXPECT_EQ(user.getName(), "");
}

TEST(User, init_not_null) {
  User user(50, "Spoon");

  EXPECT_EQ(user.getId(), 50);
  EXPECT_EQ(user.getName(), "Spoon");
}

TEST(User, set_id) {
  User user;
  user.setId(332);

  EXPECT_EQ(user.getId(), 332);
}

TEST(User, set_name) {
  User user;
  user.setName("userSetName");

  EXPECT_EQ(user.getName(), "userSetName");
}
