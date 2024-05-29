#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <filesystem>
#include <regex>
#include <string>

#include "../src/FinderSettings.h"
#include "../src/PathCrawler.h"

using namespace ::testing;

// static list of test files expected to be found in the test data directory
const std::vector<std::string>& GetTestfileList() {
  static std::vector<std::string> list = {
    "testdata\\test-dbenc-1-cfq.txt",
    "testdata\\test-dbenc-1-noop.txt",
    "testdata\\test-dbenc-32-cfq.txt",
    "testdata\\test-dbenc-32-noop.txt",
    "testdata\\aa\\test-dbenc-1-cfq.txt",
    "testdata\\aa\\test-dbenc-1-noop.txt",
    "testdata\\aa\\test-dbenc-32-cfq.txt",
    "testdata\\aa\\test-dbenc-32-noop.txt",
    "testdata\\bb\\test-dbenc-1-cfq.txt",
    "testdata\\bb\\test-dbenc-1-noop.txt",
    "testdata\\bb\\test-dbenc-32-cfq.txt",
    "testdata\\bb\\test-dbenc-32-noop.txt"
  };
  return list;
}

//TEST(PathCrawler, StringReplace) {
//  Finder::SearchParameters settings = { false, false, "X", "." };
//
//  std::string str = "test\\string_:&aa";
//  //EXPECT_CALL(pc, StringReplace).Times(AtLeast(1));
//  //pc.StringReplace(str, "\\", " ");
//  //EXPECT_STREQ(str.c_str(), "test string_:&aa");
// }
TEST(PathCrawler, BasicTestdataListing) {
  Finder::SearchParameters settings = {false, false, "X", "testdata" };

  // get static list of test files expected to be found from the test data directory
  const auto& tf = GetTestfileList();

  PathCrawler pc(settings);

  int count_of_test_files = 0;
  std::optional<std::filesystem::path> p;
  while ((p = pc.GetNextFile()).has_value()) {
    //std::cout << "file: " << p.value().string() << std::endl;
    EXPECT_NE(std::find(tf.cbegin(), tf.cend(), p.value().string().c_str()), tf.cend()) << "file not found: " << p.value().string() << std::endl;
    count_of_test_files++;
  }

  ASSERT_EQ(count_of_test_files, 4);
}

TEST(PathCrawler, RecursiveTestdataListing) {
  Finder::SearchParameters settings = { true, false, "X", "testdata" };
  const auto& tf = GetTestfileList();

  PathCrawler pc(settings);

  int count_of_test_files = 0;
  std::optional<std::filesystem::path> p;
  while ((p = pc.GetNextFile()).has_value()) {
    //std::cout << "file: " << p.value().string() << std::endl;
    EXPECT_NE(std::find(tf.cbegin(), tf.cend(), p.value().string().c_str()), tf.cend()) << "file not found: " << p.value().string() << std::endl;
    count_of_test_files++;
  }

  ASSERT_EQ(count_of_test_files, 12);
}

TEST(PathCrawler, FilteredTestdataListing) {
  std::string file_name_filter = "*32*.txt"; // file name filter applied to PathCrawler file search
  std::regex  path_name_filter_r(R"(.*testdata[/\\][^/\\]*32.*\.txt$)");
  Finder::SearchParameters settings = { false, false, "X", std::filesystem::path("testdata") / file_name_filter };

  // get filtered test file list expected to be found from the filtered test data directory
  std::vector<std::string> tf;
  std::remove_copy_if(GetTestfileList().begin(), GetTestfileList().end(),
    std::back_inserter(tf), [&path_name_filter_r](const std::string& s) { return !std::regex_match(s, path_name_filter_r); });

  PathCrawler pc(settings);

  int count_of_test_files = 0;
  std::optional<std::filesystem::path> p;
  while ((p = pc.GetNextFile()).has_value()) {
    //std::cout << "file: " << p.value().string() << std::endl;
    EXPECT_NE(std::find(tf.cbegin(), tf.cend(), p.value().string().c_str()), tf.cend()) << "file not found: " << p.value().string() << std::endl;
    count_of_test_files++;
  }

  ASSERT_EQ(count_of_test_files, 2);
}
