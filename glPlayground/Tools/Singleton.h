#pragma once

namespace Tools
{
  template <typename Type>
  class Singleton
  {
  public:
    static Type* GetInstancePtr()
    {
      return &s_Instance;
    }

    static Type& GetInstance()
    {
      return s_Instance;
    }

    Singleton(const Type&) = delete;
    Singleton(Type&&) = delete;
    Type& operator =(const Type&) = delete;
    Type& operator =(Type&&) = delete;

  protected:
    Singleton() = default;
    ~Singleton() = default;
    
    static Type s_Instance;
  };

  template <typename Type>
  Type Singleton<Type>::s_Instance;
}

