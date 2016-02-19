#pragma once

#include <filesystem>

namespace std
{
  namespace experimental
  {
    namespace filesystem
    {
      template<>
      inline path& path::append<path::iterator>(iterator begin, iterator end)
      {
        for (; begin != end; ++begin)
        {
          *this /= *begin;
        }

        return *this;
      }

      inline path make_relative(path from, path to)
      {
        from = absolute(from); to = absolute(to);
        path ret;
        auto itrFrom(from.begin());
        auto itrTo(to.begin());

        for (auto toEnd(to.end()), fromEnd(from.end()); itrFrom != fromEnd && itrTo != toEnd && *itrFrom == *itrTo; ++itrFrom, ++itrTo);
        for (auto fromEnd(from.end()); itrFrom != fromEnd; ++itrFrom);

        ret.append(itrTo, to.end());

        auto toStr = to.string();
        auto fromStr = from.string();
        if (toStr.find_first_of(fromStr) == 0)
        {
          ret = toStr.substr(fromStr.length(), toStr.length() - fromStr.length());
        }

        return ret;
      }
    }
  }
}
