#include <filesystem>
#include "mime.hpp"

#include "quark/types/String.h"


boost::beast::string_view quark::mime_type(boost::beast::string_view path)
{
  using boost::beast::iequals;
  auto const ext = [&path]
  {
    auto const pos = path.rfind(".");
    if(pos == boost::beast::string_view::npos)
      return boost::beast::string_view{};
    return path.substr(pos);
  }();
  if(iequals(ext, ".htm"))  return "text/html";
  if(iequals(ext, ".html")) return "text/html";
  if(iequals(ext, ".php"))  return "text/html";
  if(iequals(ext, ".css"))  return "text/css";
  if(iequals(ext, ".txt"))  return "text/plain";
  if(iequals(ext, ".js"))   return "application/javascript";
  if(iequals(ext, ".json")) return "application/json";
  if(iequals(ext, ".xml"))  return "application/xml";
  if(iequals(ext, ".swf"))  return "application/x-shockwave-flash";
  if(iequals(ext, ".flv"))  return "video/x-flv";
  if(iequals(ext, ".png"))  return "image/png";
  if(iequals(ext, ".jpe"))  return "image/jpeg";
  if(iequals(ext, ".jpeg")) return "image/jpeg";
  if(iequals(ext, ".jpg"))  return "image/jpeg";
  if(iequals(ext, ".gif"))  return "image/gif";
  if(iequals(ext, ".bmp"))  return "image/bmp";
  if(iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
  if(iequals(ext, ".tiff")) return "image/tiff";
  if(iequals(ext, ".tif"))  return "image/tiff";
  if(iequals(ext, ".svg"))  return "image/svg+xml";
  if(iequals(ext, ".svgz")) return "image/svg+xml";
  return "application/text";
}


bool quark::MTMime::isImage(const std::string& path)
{
    const auto stdPath = std::filesystem::path(path);
    auto ext = stdPath.extension().string();
    ext = PSString::toLower(ext);
    if (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".gif" || ext == ".webp")
        return true;
    return false;
}


std::string quark::MTMime::getMimeType(const std::string& path)
{
    const auto stdPath = std::filesystem::path(path);
    auto ext = stdPath.extension().string();
    ext = PSString::toLower(ext);

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
