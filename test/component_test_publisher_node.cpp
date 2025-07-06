// Copyright 2025 kenyam.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>

#include "auto_utest/publisher_node.hpp"

class ComponentTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    rclcpp::init(0, nullptr);
    node_ = std::make_shared<auto_utest::PublisherNode>();
    subscription_ = node_->create_subscription<std_msgs::msg::Float32>(
      "float_topic", 30, [&](const std_msgs::msg::Float32::SharedPtr msg) {
        last_received_value_ = msg->data;
        std::cout << "Received value: " << last_received_value_ << std::endl;
      });
  }

  void TearDown() override {rclcpp::shutdown();}

  std::shared_ptr<auto_utest::PublisherNode> node_;
  std::shared_ptr<rclcpp::Subscription<std_msgs::msg::Float32>> subscription_;
  float last_received_value_;
};

// Test case for publishing and receiving a positive value
TEST_F(ComponentTest, PublishAndReceivePositiveValue) {
  node_->publishMessage(5.0);
  rclcpp::spin_some(node_);
  EXPECT_EQ(last_received_value_, 5.0);
}
