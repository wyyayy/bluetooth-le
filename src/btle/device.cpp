
#include "btle/device.h"
#include "btle/gatt_services/gattservicefactory.h"

#include <sstream>

using namespace btle;
using namespace btle::gatt_services;

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

device::device(const bda &addr)
: base(),
  advertisement_data_(),
  name_(),
  db_(),
  state_(DEVICE_DISCONNECTED),
  bda_(addr),
  rssifilter_(),
  gatt_services_()
{
    gattservicefactory::instance().populate(gatt_services_);
}

device::~device()
{
    gattservicefactory::instance().deplete(gatt_services_);
}

/**
 * @brief device::name, name from advertisement data, if any
 * @return
 */
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

bool device::is_service_advertiset(const uuid& uid) const
{
    if(uid.is16bit())
    {
        if( advertisement_data_.find(btle::GAP_ADTYPE_16BIT_COMPLETE) == advertisement_data_.end() )
        {
            if( advertisement_data_.find(btle::GAP_ADTYPE_16BIT_MORE) != advertisement_data_.end() )
            {
                return uuid(advertisement_data_.find(btle::GAP_ADTYPE_16BIT_MORE)->second.string_value()) == uid;
            }
        }
//        else return advertisement_data_[btle::GAP_ADTYPE_16BIT_COMPLETE] == uid;
    }
    else
    {
        if( advertisement_data_.find(btle::GAP_ADTYPE_128BIT_COMPLETE) == advertisement_data_.end() )
        {
            if( advertisement_data_.find(btle::GAP_ADTYPE_128BIT_MORE) != advertisement_data_.end() )
            {
//                return advertisement_data_[btle::GAP_ADTYPE_128BIT_MORE] == uid;
            }
        }
//        else return advertisement_data_[btle::GAP_ADTYPE_128BIT_COMPLETE] == uid;
    }
    return false;
}

const gatt_services::gattservicebase* device::gatt_service(const uuid& uid) const
{
    for( gatt_service_iterator_const it = gatt_services_.begin(); it != gatt_services_.end(); ++it )
    {
        if( (*it)->service_uuid() == uid )
        {
            return (const gattservicebase*)&(*it);
        }
    }
    return NULL;
}

gatt_services::gattservicebase* device::gatt_service(const uuid& uid)
{
    for( gatt_service_iterator it = gatt_services_.begin(); it != gatt_services_.end(); ++it )
    {
        if( (*it)->service_uuid() == uid )
        {
            return (gattservicebase*)&(*it);
        }
    }
    return NULL;
}

connectionparameters& device::parameters()
{
    return parameters_;
}

bool device::operator == (const device& other) const
{
    return bda_ == other.addr();
}

std::string device::description() const
{
    std::stringstream ss;
    ss << "Device addr: " << bda_.description() << "\n In connection state: " << state_string();
    return ss.str();
}

void device::set_state(connection_state state)
{
    state_ = state;
}

