#include <gtest/gtest.h>
#include "UserDBManager.h"
#include "TaskDBManager.h"
#include "MessageDBManager.h"





int main(int argc, char **argv) {
    Connection();
    static UserDBManager user_manager;
    static TaskDBManager task_manager;
    static MessageDBManager message_manager;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(USER, add) {
    user_manager.add_user(User("AAA"));
    user_manager.add_user(User("BBB"));
    user_manager.add_user(User("CCC"));
    EXPECT_EQ(array[0].height_spire, 12.3);
}