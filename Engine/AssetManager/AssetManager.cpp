#include "EnginePCH.h"
#include "AssetManager.h"

#include "Database/Database.h"
#include "IO/FileSystem/Paths.h"

#include <stb_image.h>

namespace QED
{
	namespace Engine
	{
		namespace AssetManager
		{
			void Initialize()
			{
				Database::Database db(IO::FileSystem::AssetDatabasePath);

				db.CreateTable("EngineAssets", { {"path", Database::DataTypes::Text}, {"data", Database::DataTypes::Blob} });

				std::string filePath = IO::FileSystem::AssetsDirectory + "twitter.png";
				int x, y, channels;
				auto image = stbi_load(filePath.c_str(), &x, &y, &channels, 4);
				int size = x * y * channels;
				db.Insert("EngineAssets", filePath, image, size);
			}
		}
	}
}


