#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <filesystem>

#include "../src/FinderSettings.h"
#include "../src/ContentFinder.h"

using namespace ::testing;

class MyContentFinder : public ContentFinder {
public:
  //using PathCrawler::StringReplace;

  //// Genering replace method for strings
  //void StringReplace(std::string& input, const std::string& fromWhat, const std::string& toWhat) const;

  //// Convert path string to regexp search patter string
  //std::string ConvertPathStringToRegexp(const std::string& path) const;

  //// Check if file path matches the search criteries
  //bool MathcFile(const std::filesystem::path& path) const;
};

//class MockPathCrawler : public ContentFinder {
//public:
//  MOCK_METHOD(void, StringReplace, (std::string&, const std::string&, const std::string&), (const));
//  MOCK_METHOD(std::string, ConvertPathStringToRegexp, (const std::string&), (const));
//  MOCK_METHOD(bool, MathcFile, (const std::filesystem::path&), (const));
//
//  //// Genering replace method for strings
//  //void StringReplace(std::string& input, const std::string& fromWhat, const std::string& toWhat) const;
//
//  //// Convert path string to regexp search patter string
//  //std::string ConvertPathStringToRegexp(const std::string& path) const;
//
//  //// Check if file path matches the search criteries
//  //bool MathcFile(const std::filesystem::path& path) const;
//};
//
//TEST(ContentFinder, StringReplace) {
//  Finder::SearchParameters settings = { false, false, "X", "." };
//  //MockPathCrawler pc(settings);
//  MyPathCrawler pc(settings);
//
//  std::string str = "test\\string_:&aa";
//  //EXPECT_CALL(pc, StringReplace).Times(AtLeast(1));
//  //pc.StringReplace(str, "\\", " ");
//  //EXPECT_STREQ(str.c_str(), "test string_:&aa");
//  /*pc.
//  *
//  EXPECT_FALSE(st.has_value());*/
//}
//
//TEST(ContentFinder, BasicTestdataListing) {
//  Finder::SearchParameters settings = { false, false, "X", "testdata" };
//
//  // get static list of test files expected to be found from the test data directory
//  const auto& tf = GetTestfileList();
//
//  PathCrawler pc(settings);
//
//  int count_of_test_files = 0;
//  std::optional<std::filesystem::path> p;
//  while ((p = pc.GetNextFile()).has_value()) {
//    std::cout << "file: " << p.value().string() << std::endl;
//    EXPECT_TRUE(std::find(tf.cbegin(), tf.cend(), p.value().string().c_str()) != tf.cend()) << "file not found: " << p.value().string() << std::endl;
//    count_of_test_files++;
//  }
//
//  ASSERT_EQ(count_of_test_files, 4);
//
//  /*testing::internal::CaptureStdout();
//  testing::internal::CaptureStderr();*/
//  /*pc.
//  *
//  EXPECT_FALSE(st.has_value());*/
//}
