/****************************************************************************
 *
 * Copyright 2017 Proyectos y Sistemas de Mantenimiento SL (eProsima).
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

// Originally based on:
// https://github.com/PX4/px4_ros_com/blob/69bdf6e70f3832ff00f2e9e7f17d9394532787d6/templates/microRTPS_transport.h
// but split out of there.

#ifndef ROS2_SERIAL_EXAMPLE__UDP_TRANSPORTER_HPP_
#define ROS2_SERIAL_EXAMPLE__UDP_TRANSPORTER_HPP_

// C++ includes
#include <cstdint>
#include <string>

#include <netinet/in.h>
#include <poll.h>

// Local includes
#include "ros2_serial_example/transporter.hpp"

namespace ros2_to_serial_bridge
{

namespace transport
{

/**
 * The UDPTransporter class is an implementation of the abstract Transporter
 * class specifically for talking to UDP sockets.
 */
class UDPTransporter final : public Transporter
{
public:
    /**
     * Construct a UDPTransporter object with the given UDP parameters.
     *
     * @param[in] protocol The backend protocol to use; see Transporter docs for
     *                     more information about supported protocols.
     * @param[in] recv_port The UDP port to receive on.
     * @param[in] send_port The UDP port to send from.
     * @param[in] read_poll_ms The amount of time to wait for the read file
     *                         descriptor to become ready before timing out.
     *                         Larger numbers mean less CPU time is spent, but
     *                         also mean that the calls to read block longer.
     *                         It is recommended to start with 100 milliseconds.
     * @param[in] ring_buffer_size The number of bytes to allocate to the
     *                             underlying ring buffer that is used to
     *                             accept data from the UDP socket.  Larger
     *                             numbers will allow the transport to accept
     *                             larger packets (or more of them), at the
     *                             expense of memory.  It is recommended to
     *                             start with 8192.
     */
    UDPTransporter(const std::string & protocol,
                   uint16_t recv_port,
                   uint16_t send_port,
                   uint32_t read_poll_ms,
                   size_t ring_buffer_size);
    ~UDPTransporter() override;

    UDPTransporter(UDPTransporter const &) = delete;
    UDPTransporter& operator=(UDPTransporter const &) = delete;
    UDPTransporter(UDPTransporter &&) = delete;
    UDPTransporter& operator=(UDPTransporter &&) = delete;

    /**
     * Do UDP specific initialization.
     *
     * This method is an override of the one provided by the Transporter class
     * and does the setup of the underlying UDP socket.
     *
     * @returns 0 on success, -1 on error.
     */
    int init() override;

    /**
     * Do UDP specific de-initialization.
     *
     * This method is an override of the one provided by the Transporter class
     * and undoes the steps that the init() method does.
     *
     * @returns 0 on success, -1 on error.
     */
    int close() override;

private:
    /**
     * Read data from the underlying UDP socket and store it in the ring buffer.
     *
     * This method is an override of the abstract one in the Transporter class
     * and attempts to read data from the underlying UDP socket.  If no data
     * becomes available before the read_timeout_ms set in the constructor, it
     * returns 0 with no action taken.  If data is available on the UDP socket,
     * it is read into the ring buffer and the method returns the number of
     * bytes read.
     */
    ssize_t node_read() override;

    /**
     * Write data to the underlying UDP socket.
     *
     * This method is an override of the abstract one in the Transporter class
     * and attempts to write data to the underlying UDP socket.  This method
     * will block until all of the data is sent, or until an error occurs.
     *
     * @params[in] buffer The buffer containing the data to write.
     * @params[in] len The number of bytes in the buffer to write.
     * @returns The number of bytes written on success (which must be equal to
     *          len), or -1 on error.
     */
    ssize_t node_write(void *buffer, size_t len) override;

    /**
     * Detect whether the UDP sockets are ready to send and receive data.
     *
     * @returns true if the underlying UDP sockets are configured and ready,
     *          false otherwise.
     */
    bool fds_OK() override;

    uint16_t recv_port_{0};
    uint16_t send_port_{0};
    uint32_t read_poll_ms_{0};
    int recv_fd_{-1};
    int send_fd_{-1};
    uint32_t write_timeout_us_{20};
    struct sockaddr_in send_outaddr{};
    struct pollfd poll_fd_[1] = {};
};

}  // namespace transport
}  // namespace ros2_to_serial_bridge

#endif
