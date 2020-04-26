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
			static int callback(void* data, int numberOfColumns, char** fields, char** columnNames)
			{
				for (int i = 0; i < numberOfColumns; i++)
				{
					printf("%s = %s\n", columnNames[i], fields[i] ? fields[i] : "NULL");
				}
				printf("\n");
				return 0;
			}

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

			void Database::CreateTable(std::string tableName, std::vector<Column> columns)
			{
				std::string command;

				command += "CREATE TABLE " + tableName + "(";

				command += "ID INTEGER PRIMARY KEY NOT NULL, ";

				int counter = 0;
				for (auto& column : columns)
				{
					counter++;
					command += column.name + ' ';
					command += GetDataTypeString(column.dataType);
					if (counter == columns.size())
					{
						command += ");";
					}
					else
					{
						command += ',';
					}
				}

				errorCode = sqlite3_exec(db, command.c_str(), callback, 0, &errorMsg);
			}

			void Database::Insert(std::string tableName, std::string value1, void* value2, int value2Size)
			{
				sqlite3_stmt* compiledStatement;
				std::string command;

				command += "INSERT INTO " + tableName + "(ID, path, data) ";
				command += "VALUES (NULL, ?, ?); ";

				errorCode = sqlite3_prepare_v2(db, command.c_str(), -1, &compiledStatement, NULL);

				errorCode = sqlite3_bind_text(compiledStatement, 1, value1.c_str(), -1, NULL);
				errorCode = sqlite3_bind_blob(compiledStatement, 2, value2, value2Size, NULL);

				errorCode = sqlite3_step(compiledStatement);

				errorCode = sqlite3_finalize(compiledStatement);
			}
		}
	}
}
