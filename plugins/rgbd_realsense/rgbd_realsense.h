#pragma once

#include <rgbd_input.h>
#include "lib_begin.h"

namespace rgbd {

	class CGV_API rgbd_realsense : public rgbd_device
	{
	public:
		/// create a detached realsense device object
		rgbd_realsense();
		~rgbd_realsense();
		
		/// attach to the realsense device of the given serial, the expected serial is the same as returned by rgbd_realsense_driver::get_serial
		bool attach(const std::string& serial);
		/// return whether device object is attached to a realsense device
		bool is_attached() const;
		/// detaches the object from the realsense device
		bool detach();
		/// check whether the device supports the given combination of input streams
		bool check_input_stream_configuration(InputStreams is) const;
		void query_stream_formats(InputStreams is, std::vector<stream_format>& stream_formats) const;
		bool start_device(InputStreams is, std::vector<stream_format>& stream_formats);
		bool start_device(const std::vector<stream_format>& stream_formats);
		bool stop_device();
		bool is_running() const;
		bool get_frame(InputStreams is, frame_type& frame, int timeOut);
		void map_color_to_depth(const frame_type& depth_frame, const frame_type& color_frame,
			frame_type& warped_color_frame) const;
		bool map_depth_to_point(int x, int y, int depth, float* point_ptr) const;

	protected:
		rs2::context* ctx;
		rs2::device* dev;
		rs2::pipeline* pipe;
		std::string serial;
		stream_format color_stream, depth_stream, ir_stream;
		rs2::frameset frame_cache;
		bool got_color_frame, got_depth_frame, got_ir_frame;
		double last_color_frame_time, last_depth_frame_time, last_ir_frame_time;
	};

	class CGV_API rgbd_realsense_driver : public rgbd_driver
	{
	public:
		/// construct CLNUI driver
		rgbd_realsense_driver();
		/// destructor
		~rgbd_realsense_driver();
		/// return the number of realsense devices found by driver
		unsigned get_nr_devices();
		/// return the serial of the i-th realsense devices
		std::string get_serial(int i);
		/// create a kinect device
		rgbd_device* create_rgbd_device();
	};

}
#include <cgv/config/lib_end.h>