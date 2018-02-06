/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include "ignition/transport/log/QueryOptions.hh"
#include "gtest/gtest.h"

using namespace ignition::transport;
using namespace std::chrono_literals;

//////////////////////////////////////////////////
TEST(QueryOptionsTimeRange, GetRange)
{
  log::QualifiedTime beginTime(1s, log::QualifiedTime::Qualifier::Inclusive);
  log::QualifiedTime endTime(2s, log::QualifiedTime::Qualifier::Exclusive);
  log::QualifiedTimeRange range(beginTime, endTime);
  log::TimeRangeOption rangeOption(range);
  EXPECT_EQ(range, rangeOption.TimeRange());
}

//////////////////////////////////////////////////
TEST(QueryOptionsTimeRange, GetRangeConst)
{
  log::QualifiedTime beginTime(1s, log::QualifiedTime::Qualifier::Inclusive);
  log::QualifiedTime endTime(2s, log::QualifiedTime::Qualifier::Exclusive);
  log::QualifiedTimeRange range(beginTime, endTime);
  log::TimeRangeOption rangeOption(range);
  const log::TimeRangeOption &constRangeOption = rangeOption;
  EXPECT_EQ(range, constRangeOption.TimeRange());
}

//////////////////////////////////////////////////
TEST(QueryOptionsTopicList, TopicList)
{
  std::set<std::string> topicList = {"/topic/one", "/topic/two"};
  log::TopicList topicOption(topicList);
  EXPECT_EQ(topicList, topicOption.Topics());
}

//////////////////////////////////////////////////
TEST(QueryOptionsTopicList, TopicListConst)
{
  std::set<std::string> topicList = {"/topic/one", "/topic/two"};
  log::TopicList topicOption(topicList);
  const auto &constTopicOption = topicOption;
  EXPECT_EQ(topicList, constTopicOption.Topics());
}

//////////////////////////////////////////////////
TEST(QueryOptionsTopicList, CopyTopicList)
{
  std::set<std::string> topicList = {"/topic/one", "/topic/two"};
  log::TopicList topicOptionOrig(topicList);
  log::TopicList topicOption(topicOptionOrig);
  EXPECT_EQ(topicList, topicOption.Topics());
}

//////////////////////////////////////////////////
TEST(QueryOptionsTopicList, CopyTopicListConst)
{
  std::set<std::string> topicList = {"/topic/one", "/topic/two"};
  log::TopicList topicOptionOrig(topicList);
  const auto &constTopicOption = topicOptionOrig;
  log::TopicList topicOption(constTopicOption);
  EXPECT_EQ(topicList, topicOption.Topics());
}

//////////////////////////////////////////////////
TEST(QueryOptionsTopicList, CopyTopicPattern)
{
  std::regex topicPattern("foo");
  log::TopicPattern topicOptionOrig(topicPattern);
  log::TopicPattern topicOption(topicOptionOrig);
  std::regex uutPattern = topicOption.Pattern();

  EXPECT_TRUE(std::regex_match("foo", uutPattern));
  EXPECT_FALSE(std::regex_match("bar", uutPattern));
}

//////////////////////////////////////////////////
TEST(QueryOptionsTopicList, CopyTopicPatternConst)
{
  std::regex topicPattern("foo");
  log::TopicPattern topicOptionOrig(topicPattern);
  const auto &constTopicOption = topicOptionOrig;
  log::TopicPattern topicOption(constTopicOption);
  std::regex uutPattern = topicOption.Pattern();

  EXPECT_TRUE(std::regex_match("foo", uutPattern));
  EXPECT_FALSE(std::regex_match("bar", uutPattern));
}

//////////////////////////////////////////////////
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
