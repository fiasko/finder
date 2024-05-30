#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <filesystem>
#include <string_view>

#include "../src/FinderSettings.h"
#include "../src/ContentFinder.h"

using namespace ::testing;
using ::testing::AtLeast;

class MockContentFinder : public ContentFinder {
public:
  MockContentFinder(const Finder::SearchParameters& settings) : ContentFinder(settings) {

  }

  void SearchFileContent(const std::filesystem::path& file) {
    active_thread_count_++;
    ContentSerchThread(file);
  }

  MOCK_METHOD(void, PrintOutput, (const std::filesystem::path& file, const std::string_view& content), (const, override));
};

TEST(ContentFinder, Basic) {
  Finder::SearchParameters settings = { false, false, "WriteX", "test-dbenc-1-cfq.txt" };
  const std::filesystem::path expected_path("testdata/test-dbenc-1-cfq.txt");
  const std::string expected_content(" WriteX       2647203     0.029    42.693");

  MockContentFinder cf(settings);

  EXPECT_CALL(cf, PrintOutput(expected_path, expected_content)).Times(AtLeast(1));

  cf.SearchFileContent(expected_path);
}

