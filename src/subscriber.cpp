/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2015, Helio Perroni Filho.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

#include <cv_video/subscriber.h>

namespace cv_video
{

Subscriber::Subscriber(image_transport::ImageTransport& transport,
                       std::string &topic,
                       uint32_t queue_size,
                       Video::Callback callback,
                       Video *video):
  subscriber_(transport.subscribe(topic, queue_size, &Subscriber::imageCallback, this)),
  callback_(callback),
  video_(video)
{
  // Nothing to do.
}

Subscriber::~Subscriber()
{
  // Nothing to do.
}

void Subscriber::imageCallback(const sensor_msgs::ImageConstPtr& message)
{
  try
  {
    Frame frame(message);
    callback_(*video_, frame);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
  }
  catch (cv::Exception& e)
  {
    ROS_ERROR("OpenCV exception: %s", e.what());
  }
  catch (...)
  {
    ROS_ERROR("Unknown error");
  }
}

} // namespace cv_video