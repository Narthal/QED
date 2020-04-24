#include "EnginePCH.h"
#include "Database.h"

#include "Core/Log/Log.h"

#include "sqlite3.h"

namespace QED
{
	namespace Engine
	{
		namespace Database
		{
			Database::Database(std::string path)
			{
				errorCode = sqlite3_open(path.c_str(), &db);

				if (errorCode)
				{
					QED_CORE_LOG_ERROR("Can't open database: {0}\n", sqlite3_errmsg(db));
				}
				else
				{
					QED_CORE_LOG_INFO("Opened database successfully");
				}
			}

			Database::~Database()
			{
				sqlite3_close(db);
			}
		}
	}
}
