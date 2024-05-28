#include <gtest/gtest.h>

#include <filesystem>

#include "../src/FinderSettings.h"
#include "../src/PathCrawler.h"

TEST(PathCrawler, Basic) {
  Finder::SearchParameters settings = {false, false, "X", "." };
  PathCrawler pc(settings);
  /*pc.
  EXPECT_FALSE(st.has_value());*/
}