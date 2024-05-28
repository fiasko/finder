#include <gtest/gtest.h>

#include <filesystem>

#include "../src/FinderSettings.h"

TEST(ArgumentParser, NoArguments) {
  const char* argv[] = { "finder.exe", NULL };
  auto st = Finder::ParseArguments(1, argv);
  EXPECT_FALSE(st.has_value());
}

TEST(ArgumentParser, BasicArguments) {
  const char* argv[] = { "finder.exe", "X", "*.*", NULL };
  auto st = Finder::ParseArguments(3, argv);
  EXPECT_TRUE(st.has_value());
  if (st.has_value()) {
    const auto& v = st.value();
    EXPECT_FALSE(v.recursive_search);
    EXPECT_FALSE(v.use_reg_exp);
    EXPECT_STREQ(v.search_pattern.c_str(), "X");
    EXPECT_STREQ(v.search_path.string().c_str(), "*.*");
  }
}

TEST(ArgumentParser, RegExpEnabled) {
  const char* argv[] = { "finder.exe", "-r", "AAAA", "testi\\", NULL};
  auto st = Finder::ParseArguments(4, argv);
  EXPECT_TRUE(st.has_value());
  if (st.has_value()) {
    const auto& v = st.value();
    EXPECT_TRUE(v.recursive_search);
    EXPECT_FALSE(v.use_reg_exp);
    EXPECT_STREQ(v.search_pattern.c_str(), "AAAA");
    EXPECT_STREQ(v.search_path.string().c_str(), "testi\\");
  }
}

TEST(ArgumentParser, RegExpAndRecursiveEnabled) {
  const char* argv[] = { "finder.exe", "-r", "-G", "AAAA", "testi\\", NULL };
  auto st = Finder::ParseArguments(5, argv);
  EXPECT_TRUE(st.has_value());
  if (st.has_value()) {
    const auto& v = st.value();
    EXPECT_TRUE(v.recursive_search);
    EXPECT_TRUE(v.use_reg_exp);
    EXPECT_STREQ(v.search_pattern.c_str(), "AAAA");
    EXPECT_STREQ(v.search_path.string().c_str(), "testi\\");
  }
}

TEST(ArgumentParser, RecursiveEnabled) {
  const char* argv[] = { "finder.exe", "-G", "AAAA", "testi\\", NULL };
  auto st = Finder::ParseArguments(4, argv);
  EXPECT_TRUE(st.has_value());
  if (st.has_value()) {
    const auto& v = st.value();
    EXPECT_FALSE(v.recursive_search);
    EXPECT_TRUE(v.use_reg_exp);
    EXPECT_STREQ(v.search_pattern.c_str(), "AAAA");
    EXPECT_STREQ(v.search_path.string().c_str(), "testi\\");
  }
}
