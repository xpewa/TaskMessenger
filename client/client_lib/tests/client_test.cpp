#include <gtest/gtest.h>
#include "client.h"

TEST(Client, Connect) {
  ClientBoostAsio client;
  ASSERT_TRUE(client.Connect());
  ASSERT_TRUE(client.Disconnect());
}