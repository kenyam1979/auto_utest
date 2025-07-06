// Copyright 2025 kenyam.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>

#include "auto_utest/publisher_node.hpp"

class PublisherNodeTest : public auto_utest::PublisherNode
{
public:
  using PublisherNode::PublisherNode;
  float last_published_value_;

  PublisherNodeTest()
  : PublisherNode() {}

  void test_publish_message(float value)
  {
    publishMessage(value);
    last_published_value_ = value;
  }
};

// 1. Test positive value
TEST(PublisherNodeTest, PositiveValue) {
  int argc = 0;
  char ** argv = nullptr;
  rclcpp::init(argc, argv);

  auto node = std::make_shared<PublisherNodeTest>();

  // Test positive value
  node->test_publish_message(5.0f);
  EXPECT_EQ(node->last_published_value_, 5.0f);

  rclcpp::shutdown();
}

// 2. Test negative value
TEST(PublisherNodeTest, NegativeValue) {
  int argc = 0;
  char ** argv = nullptr;
  rclcpp::init(argc, argv);

  auto node = std::make_shared<PublisherNodeTest>();

  node->test_publish_message(-3.0f);
  EXPECT_EQ(node->last_published_value_, -3.0f);

  rclcpp::shutdown();
}

// 3. Test zero value
TEST(PublisherNodeTest, ZeroValue) {
  int argc = 0;
  char ** argv = nullptr;
  rclcpp::init(argc, argv);

  auto node = std::make_shared<PublisherNodeTest>();

  node->test_publish_message(0.0f);
  EXPECT_EQ(node->last_published_value_, 0.0f);

  rclcpp::shutdown();
}
