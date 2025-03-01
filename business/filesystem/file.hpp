#pragma once
#include <vector>
#include <memory>
#include <string>
#include "quark/models/files/File.hpp"
#include "quark/build.h"

namespace quark
{

    class CXAPI FileServerBusiness
    {
    public:
		struct SelectFilesOptions {
			SelectFilesOptions();
			bool directories;
			bool files;
			bool hidden;
			bool ignore;
	    };
        [[nodiscard]] static std::vector<PSFileModel> selectFilesVector(std::string parentPath,
		    SelectFilesOptions options = SelectFilesOptions());
    };
}
