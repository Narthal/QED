#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"

namespace QED
{
	namespace Engine
	{
		namespace Database
		{
			enum class DataTypes
			{
				Null	= 0,
				Int		= 1,
				Text	= 2,
				Blob	= 3,
			};

			static std::string GetDataTypeString(DataTypes dataType)
			{
				switch (dataType)
				{
					case QED::Engine::Database::DataTypes::Null:
					// TODO: crash here
					return "";
					case QED::Engine::Database::DataTypes::Int:
					return "INT";
					case QED::Engine::Database::DataTypes::Text:
					return "TEXT";
					case QED::Engine::Database::DataTypes::Blob:
					return "BLOB";
					default:
					// TODO: crash here
					return "";
				}
			}

			struct Column
			{
				std::string name;
				DataTypes dataType;
			};

			class Database
			{
			public:
				Database(std::string path);
				~Database();

			public:
				void CreateTable(std::string tableName, std::vector<Column> columns);
				
				void Insert(std::string tableName, std::string value1, void* value2, int value2Size);

				void GetBlobData(std::string tableName, std::string columnName, int row, void** data, int* size);

			public: // Debug
				void TraceTableRecords(std::string tableName);

			private:
				sqlite3* db = nullptr;
				int errorCode = 0;
				char* errorMsg = 0;
			};
		}
	}
}


#endif // !DATABASE_H
