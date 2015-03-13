
#include "btle/device.h"

using namespace btle;

namespace{
    const char* state2string(connection_state state)
    {
        switch(state){
            case DEVICE_CONNECTED:          return "DEVICE_CONNECTED";
            case DEVICE_CONNECTING:         return "DEVICE_CONNECTING";
            case DEVICE_CONNECTION_PARK:    return "DEVICE_CONNECTION_PARK";
            case DEVICE_DISCONNECTED:       return "DEVICE_DISCONNECTED";
            case DEVICE_DISCONNECTING:      return "DEVICE_DISCONNECTING";
            case DEVICE_DISCONNECTION_PARK: return "DEVICE_DISCONNECTION_PARK";
            default: return "UNKNOWN";
        }
    }
}

device::device()
{
}

device::~device()
{
}

const std::string& device::name()
{
    return name_;
}

const advertisementdata* device::advertisement_data_for_key(btle::advertisement_type key) const
{
    if( advertisement_data_.find(key) != advertisement_data_.end() ){
        return (const advertisementdata*)&advertisement_data_.find(key)->second;
    }
    else return NULL;
}

gattdatabase& device::db()
{
    return db_;
}

const gattdatabase& device::db() const
{
    return db_;
}

rssifilter& device::rssi_filter()
{
    return rssifilter_;
}

const rssifilter& device::rssi_filter() const
{
    return rssifilter_;
}

connection_state device::state() const
{
    return state_;
}

std::string device::state_string() const
{
    return state2string(state_);
}

const bda& device::addr() const
{
    return bda_;
}

bool device::operator == (const device& other) const
{
    return bda_ == other.addr();
}

void device::set_state(connection_state state)
{
    state_ = state;
}
