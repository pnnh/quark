
#include "codes.h"

const char* quark::CodeMessage(int code)
{
  switch (code)
  {
  case quark::codes::Ok:
    return "Ok";
  case quark::codes::Error:
    return "Error";
  default:
    return "Unknown";
  }
}
