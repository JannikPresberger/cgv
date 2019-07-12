#pragma once

#include "rgbd_driver.h"

#include "lib_begin.h"

namespace rgbd {

/** interface to provided access to rgbd devices. This is independent of device driver. 
    Different plugins can implement the rgbd_driver and rgbd_device classes and seemlessly
	integrate into the rgbd_input class. */
class CGV_API rgbd_input
{
public:
	/**@name driver registration */
	//@{
protected:
	/// internal function to provide a list of drivers
	static std::vector<rgbd_driver*>& ref_driver_list();
public:
	/// call to register a new driver
	static void register_driver(rgbd_driver* drv, const std::string& driver_name);
	/// call to unregister a driver - not implemented yet!
	static void unregister_driver(rgbd_driver* drv);
	//@}

	/**@name enumeration of devices*/
	//@{
	/// return the number of rgbd devices
	static unsigned get_nr_devices();
	/// return the serial of the i-th rgbd devices
	static std::string get_serial(int i);
	//@}

	/**@name device attachment */
	//@{
	/// create a rgbd input device object
	rgbd_input();
	/// destruct rgbd device object and automatically detach if necessary
	~rgbd_input();
	/// create a rgbd input device object and attach to device with given serial
	rgbd_input(const std::string& serial);
	/// attach to the rgbd input device of the given serial
	bool attach(const std::string& serial);
	/// return the serial of the device
	const std::string& get_serial() const;
	/// return whether device object is attached to a rgbd input device
	bool is_attached() const;
	/// detach from serial (done automatically in destructor)
	bool detach();
	//@}

	/**@name file io */
	//@{
	/// read a frame from file
	static bool read_frame(const std::string& file_name, void* data_ptr, unsigned frame_size);
	/// write a frame to a file
	static bool write_frame(const std::string& file_name, const void* data_ptr, unsigned frame_size);
	/// attach to a directory that contains saved frames
	bool attach_path(const std::string& path);
	/// enable protocolation of all frames acquired by the attached rgbd input device
	void enable_protocol(const std::string& path);
	/// disable protocolation
	void disable_protocol();
	//@}

	/**@name base control*/
	//@{
	/// set the pitch position of the kinect_input base, range of values is [-1, 1]
	bool set_pitch(float y);
	/// query the current measurement of the acceleration sensors within the given time_out in milliseconds; return whether a measurement has been retrieved
	bool put_IMU_measurement(IMU_measurement& m, unsigned time_out) const;
	//@}

	/**@name camera control*/
	//@{
	/// check whether the device supports the given combination of input streams
	bool check_input_stream_configuration(InputStreams is) const;
	///
	bool set_near_mode(bool on = true);
	/// start the rgbd input device
	bool start(InputStreams);
	/// check whether device is started
	bool is_started() const;
	/// stop the rgbd input device
	bool stop();
	/// return the image width of the frames
	unsigned get_width() const;
	/// return the image width of the frames
	unsigned get_height() const;
	/// compute the frame size of the given format
	unsigned get_frame_size(FrameFormat ff) const;
	/// query a frame in the given format from color or depth camera
	bool get_frame(FrameFormat ff, void* data_ptr, int timeOut = 2000);
	/// map a depth map to color pixel where color_pixel_data_ptr points to an array of short int pairs
	void map_depth_to_color_pixel(FrameFormat depth_ff, const void* depth_data_ptr, void* color_pixel_data_ptr) const;
	/// map a color frame to the image coordinates of the depth image
	void map_color_to_depth(FrameFormat depth_ff, const void* depth_data_ptr, FrameFormat color_ff, void* color_data_ptr) const;
	/// map pixel coordinate and depth in given format to 3D point
	bool map_pixel_to_point(int x, int y, unsigned depth, FrameFormat depth_ff, float point[3]);
protected:
	/// store whether camera has been started
	bool started;
	/// store attached serial
	std::string serial;
	/// pointer to rgbd input device
	rgbd_device* rgbd;
	/// path where the frame protocol should be saved in order to create an emulation device
	std::string protocol_path;
	/// file index of protocol
	int protocol_idx;
	/// flags used to determine which frames have been saved to file for current index
	unsigned protocol_flags;
};

/// helper template to register a driver
template <class T>
struct driver_registration
{
	driver_registration(const std::string& driver_name)
	{
		rgbd_input::register_driver(new T, driver_name);
	}
};

}

#include <cgv/config/lib_end.h>