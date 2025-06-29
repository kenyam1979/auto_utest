// Copyright 2025 kenyam.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#ifndef AUTO_UTEST__PUBLISHER_NODE_HPP_
#define AUTO_UTEST__PUBLISHER_NODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>

namespace auto_utest
{

class PublisherNode : public rclcpp::Node
{
public:
  PublisherNode();
  void publish_message(float data);

private:
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
};

}  // namespace auto_utest

#endif  // AUTO_UTEST__PUBLISHER_NODE_HPP_
