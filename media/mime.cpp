#include <filesystem>
#include "mime.hpp"

#include "quark/types/string.h"

#include <boost/algorithm/string/predicate.hpp>

std::string quark::mime_type(const std::string& path)
{
  auto const ext = [&path]
  {
    auto const pos = path.rfind('.');
    if (pos == std::string::npos)
      return std::string();

    return path.substr(pos);
  }();
  if(boost::iequals(ext, ".htm"))  return "text/html";
  if(boost::iequals(ext, ".html")) return "text/html";
  if(boost::iequals(ext, ".php"))  return "text/html";
  if(boost::iequals(ext, ".css"))  return "text/css";
  if(boost::iequals(ext, ".txt"))  return "text/plain";
  if(boost::iequals(ext, ".js"))   return "application/javascript";
  if(boost::iequals(ext, ".json")) return "application/json";
  if(boost::iequals(ext, ".xml"))  return "application/xml";
  if(boost::iequals(ext, ".swf"))  return "application/x-shockwave-flash";
  if(boost::iequals(ext, ".flv"))  return "video/x-flv";
  if(boost::iequals(ext, ".png"))  return "image/png";
  if(boost::iequals(ext, ".jpe"))  return "image/jpeg";
  if(boost::iequals(ext, ".jpeg")) return "image/jpeg";
  if(boost::iequals(ext, ".jpg"))  return "image/jpeg";
  if(boost::iequals(ext, ".gif"))  return "image/gif";
  if(boost::iequals(ext, ".bmp"))  return "image/bmp";
  if(boost::iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
  if(boost::iequals(ext, ".tiff")) return "image/tiff";
  if(boost::iequals(ext, ".tif"))  return "image/tiff";
  if(boost::iequals(ext, ".svg"))  return "image/svg+xml";
  if(boost::iequals(ext, ".svgz")) return "image/svg+xml";
  return "application/text";
}


bool quark::MTMime::isImage(const std::string& path)
{
    const auto stdPath = std::filesystem::path(path);
    auto ext = stdPath.extension().string();
    ext = MTString::toLower(ext);
    if (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".gif" || ext == ".webp")
        return true;
    return false;
}


std::string quark::MTMime::getMimeType(const std::string& path)
{
    const auto stdPath = std::filesystem::path(path);
    auto ext = stdPath.extension().string();
    ext = MTString::toLower(ext);

    if (ext == ".txt")
        return "text/plain";
    if (ext == ".htm" || ext == ".html")
        return "text/html";
    if (ext == ".js")
        return "application/javascript";
    if (ext == ".css")
        return "text/css";
    if (ext == ".jpg" || ext == ".jpeg")
        return "image/jpeg";
    if (ext == ".png")
        return "image/png";
    if (ext == ".json")
        return "application/json";
    if (ext == ".gif")
        return "image/gif";
    if (ext == ".webp")
        return "application/webp";

    return "application/octet-stream";
}
