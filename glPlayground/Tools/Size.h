#pragma once

namespace Tools
{
  template<typename Type>
  class Size
  {
  public:
    Size(Type width, Type height)
      : Width(width)
      , Heigth(height)
    {      
    }

    Size(const Size& Other)
      : Width(Other.Width)
      , Heigth(Other.Heigth)
    {
    }

    Size& operator=(const Size& Other)
    {
      if (this == &Other)
        return *this;
      Width = Other.Width;
      Heigth = Other.Heigth;
      return *this;
    }

    Type Width;
    Type Heigth;
  };
}
