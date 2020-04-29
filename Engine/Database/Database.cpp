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
			static int callback(void* data, int argc, char** argv, char** azColName)
			{
				for (int i = 0; i < argc; i++)
				{
					QED_CORE_LOG_TRACE(std::string(azColName[i]) + " = " + std::string(argv[i] ? argv[i] : "NULL"));
				}
				return 0;
			}

			Database::Database(std::string path)
			{
				errorCode = sqlite3_open(path.c_str(), &db);

				if (errorCode)
				{
					QED_CORE_LOG_ERROR("Can't open database: " + std::string(sqlite3_errmsg(db)));
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

				errorCode = sqlite3_exec(db, command.c_str(), nullptr, nullptr, &errorMsg);
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

			void Database::GetBlobData(std::string tableName, std::string columnName, int row, void** data, int* size)
			{
				sqlite3_blob* blob;
				sqlite3_blob_open(db, "main", tableName.c_str(), columnName.c_str(), row, 0, &blob);
				int blobSize = sqlite3_blob_bytes(blob);

				void* blobData = malloc(blobSize);

				sqlite3_blob_read(blob, blobData, blobSize, 0);

				sqlite3_blob_close(blob);

				*size = blobSize;
				*data = blobData;
			}

			void Database::TraceTableRecords(std::string tableName)
			{
				std::string command;

				command += "SELECT * from " + tableName;

				errorCode = sqlite3_exec(db, command.c_str(), callback, nullptr, &errorMsg);
			}
		}
	}
}
