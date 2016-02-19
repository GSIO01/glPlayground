#pragma once

namespace Tools
{
  class DataBuffer
  {
  public:
    DataBuffer();
    DataBuffer(void* data, size_t size, bool copy = true);
    explicit DataBuffer(size_t size);
    ~DataBuffer();

    DataBuffer(const DataBuffer& Other)
      : DataBuffer()
    {
      _data = Other._data;
      _size = Other._size;
      _writeable = Other._writeable;
      _wasWriteableInitially = Other._wasWriteableInitially;
      _delete = false;
    }

    DataBuffer(DataBuffer&& Other)
      : DataBuffer()
    {
      _data = Other._data;
      _size = Other._size;
      _writeable = Other._writeable;
      _wasWriteableInitially = Other._wasWriteableInitially;
      _delete = Other._delete;

      Other._writeable = nullptr;
      Other._data = nullptr;
    }

    DataBuffer& operator=(const DataBuffer& Other)
    {
      if (this == &Other)
        return *this;
      _data = Other._data;
      _size = Other._size;
      _writeable = Other._writeable;
      _wasWriteableInitially = Other._wasWriteableInitially;
      _delete = false;
      return *this;
    }

    DataBuffer& operator=(DataBuffer&& Other)
    {
      if (this == &Other)
        return *this;
      _data = Other._data;
      _size = Other._size;
      _writeable = Other._writeable;
      _wasWriteableInitially = Other._wasWriteableInitially;
      _delete = Other._delete;

      Other._writeable = nullptr;
      Other._data = nullptr;

      return *this;
    }

    bool IsWriteable() const { return *_writeable; }
    void Lock() const { *_writeable = false; }
    bool Unlock() const;
    void* GetData() const { return _data; }
    void* GetWriteableData() { return _data; }
    size_t GetSize() const { return _size; }

    operator const char*() const { return static_cast<char*>(_data); }

  protected:

    void* _data;
    size_t _size;
    bool* _writeable;
    bool _wasWriteableInitially;
    bool _delete;
  };
}
