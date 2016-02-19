#include "DataBuffer.h"
#include <cstring>
#include "Log/Logger.h"

namespace Tools
{
  DataBuffer::DataBuffer(void* data, size_t size, bool copy)
    : DataBuffer()
  {
    _size = size;

    if(copy)
    {
      _data = static_cast<void*>(new char[size]);
      memcpy(_data, data, size);
      *_writeable = true;
      _wasWriteableInitially = true;
      _delete = true;
    }
    else
    {
      _data = data;
      *_writeable = false;
      _wasWriteableInitially = false;
      _delete = false;
    }
  }

  DataBuffer::DataBuffer(size_t size)
    : DataBuffer()
  {
    _size = size;
    _data = static_cast<void*>(new char[size]);
    memset(_data, 0, _size);
    *_writeable = true;
    _wasWriteableInitially = true;
    _delete = true;
  }

  DataBuffer::~DataBuffer()
  {
    if(_delete && _data != nullptr)
    {
      delete _data;
    }

    if(_writeable != nullptr)
    {
      delete _writeable;
    }
  }

  bool DataBuffer::Unlock() const
  {
    if(!_wasWriteableInitially)
    {
      LOG_ERROR("Tried to unlock buffer that was readonly initially");
      return false;
    }

    *_writeable = false;
      
    return true;
  }

  DataBuffer::DataBuffer()
    : _data(nullptr)
    , _size(0)
    , _writeable(new bool)
    , _wasWriteableInitially(false)
    , _delete(false)
  {
    *_writeable = false;
  }
}
