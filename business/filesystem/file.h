#pragma once

#include "quark/build.h"

#ifdef __cplusplus

extern "C" {
#endif

CXAPI bool IsFileExist(const char* filePath);

#ifdef __cplusplus
}

#include <vector>
#include "quark/business/models/files/file.h"

namespace quark
{
	class CXAPI FileServerBusiness
	{
	public:
		struct SelectFilesOptions
		{
			SelectFilesOptions();

			bool directories;
			bool files;
			bool hidden;
			bool ignore;
		};

		[[nodiscard]] static std::vector<PSFileModel> selectFilesVector(std::string parentPath,
		                                                                SelectFilesOptions options =
			                                                                SelectFilesOptions());
	};
}

#endif
