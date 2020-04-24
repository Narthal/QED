#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"

namespace QED
{
	namespace Engine
	{
		namespace Database
		{
			class Database
			{
			public:
				Database(std::string path);
				~Database();

			private:
				sqlite3* db = nullptr;
				int errorCode = 0;
			};
		}
	}
}


#endif // !DATABASE_H
