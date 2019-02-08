// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file battery_status_PubSubTypes.h
 * This header file contains the declaration of the serialization functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#ifndef _BATTERY_STATUS__PUBSUBTYPES_H_
#define _BATTERY_STATUS__PUBSUBTYPES_H_

#include <fastrtps/config.h>
#include <fastrtps/TopicDataType.h>

#include "battery_status_.hpp"

#if !defined(GEN_API_VER) || (GEN_API_VER != 1)
#error Generated battery_status_ is not compatible with current installed Fast-RTPS. Please, regenerate it with fastrtpsgen.
#endif






/*!
 * @brief This class represents the TopicDataType of the type battery_status_ defined by the user in the IDL file.
 * @ingroup BATTERY_STATUS_
 */
class battery_status_PubSubType : public eprosima::fastrtps::TopicDataType {
public:
        typedef battery_status_ type;

	battery_status_PubSubType();
	virtual ~battery_status_PubSubType();
	virtual bool serialize(void *data, eprosima::fastrtps::rtps::SerializedPayload_t *payload) override;
	virtual bool deserialize(eprosima::fastrtps::rtps::SerializedPayload_t *payload, void *data) override;
    virtual std::function<uint32_t()> getSerializedSizeProvider(void* data) override;
	virtual bool getKey(void *data, eprosima::fastrtps::rtps::InstanceHandle_t *ihandle,
		bool force_md5 = false) override;
	virtual void* createData() override;
	virtual void deleteData(void * data) override;
	MD5 m_md5;
	unsigned char* m_keyBuffer;
};

#endif // _BATTERY_STATUS__PUBSUBTYPES_H_
