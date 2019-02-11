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

/*!
 * @file battery_status_Subscriber.h
 * This header file contains the declaration of the subscriber functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#ifndef _battery_status__SUBSCRIBER_H_
#define _battery_status__SUBSCRIBER_H_

#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/subscriber/SubscriberListener.h>
#include <fastrtps/subscriber/SampleInfo.h>
#include "battery_status_PubSubTypes.hpp"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

class battery_status_Subscriber
{
public:
    battery_status_Subscriber();
    virtual ~battery_status_Subscriber();
    bool init();
    void run();
    bool hasMsg();
    battery_status_ getMsg();
private:
    Participant *mp_participant;
    Subscriber *mp_subscriber;

    class SubListener : public SubscriberListener
    {
    public:
        SubListener() : n_matched(0), n_msg(0){};
        ~SubListener(){};
        void onSubscriptionMatched(Subscriber* sub, MatchingInfo& info);
        void onNewDataMessage(Subscriber* sub);
        SampleInfo_t m_info;
        int n_matched;
        int n_msg;
        battery_status_ msg;
        bool has_msg = false;

    } m_listener;
    battery_status_PubSubType myType;
};

#endif // _battery_status__SUBSCRIBER_H_
