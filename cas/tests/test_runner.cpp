//
// Created by Abd-El-Aziz Zayed on 2022-08-29.
//

#include "gtest/gtest.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int testsResult = RUN_ALL_TESTS();
    return testsResult;
}