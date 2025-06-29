// Copyright 2025 kenyam.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include "auto_utest/publisher_node.hpp"

namespace auto_utest
{

PublisherNode::PublisherNode()
: Node("publisher_node")
{
  publisher_ = this->create_publisher<std_msgs::msg::Float32>("topic", 10);
}

void PublisherNode::publish_message(float value)
{
  auto message = std_msgs::msg::Float32();

  if (value > 0.0) {
    RCLCPP_INFO(this->get_logger(), "Publishing positive value: '%f'", value);
    message.data = value;
  } else if (value < 0.0) {
    RCLCPP_INFO(this->get_logger(), "Publishing negative value: '%f'", value);
    message.data = value;
  } else {
    RCLCPP_INFO(this->get_logger(), "Publishing zero: '%f'", value);
    message.data = 0.0;
  }
  publisher_->publish(message);
}
}  // namespace auto_utest
