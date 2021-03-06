#include "EnginePCH.h"
#include "AssetManager.h"

#include "IO/FileSystem/Paths.h"

#include <stb_image.h>

#include "Profiler/Instrumentor.h"

namespace QED
{
	namespace Engine
	{
		namespace Asset
		{
			AssetManager::AssetManager()
			{
				QED_PROFILE_FUNCTION();

				db = Core::Type::CreateScope<Database::Database>(IO::FileSystem::AssetDatabasePath);

				db->CreateTable("EngineAssets", { {"path", Database::DataTypes::Text}, {"data", Database::DataTypes::Blob} });

				std::string filePath;
				int x, y, channels, size;
				stbi_uc* image;

				{
					QED_PROFILE_SCOPE("twitter file IO");

					filePath = IO::FileSystem::AssetsDirectory + "twitter.png";
					image = stbi_load(filePath.c_str(), &x, &y, &channels, 4);
					size = x * y * channels;
					db->Insert("EngineAssets", filePath, image, size);
				}

				{
					QED_PROFILE_SCOPE("glider file IO");

					filePath = IO::FileSystem::AssetsDirectory + "glider.png";
					image = stbi_load(filePath.c_str(), &x, &y, &channels, 4);
					size = x * y * channels;
					db->Insert("EngineAssets", filePath, image, size);
				}

				{
					QED_PROFILE_SCOPE("missingTexture file IO");

					filePath = IO::FileSystem::AssetsDirectory + "missingTexture.png";
					image = stbi_load(filePath.c_str(), &x, &y, &channels, 4);
					size = x * y * channels;
					db->Insert("EngineAssets", filePath, image, size);
				}

				db->TraceTableRecords("EngineAssets");
			}

			void* AssetManager::GetImageData(int id, int* size)
			{
				QED_PROFILE_FUNCTION();

				void* data = nullptr;

				db->GetBlobData("EngineAssets", "data", 1, &data, size);
				return data;
			}
		}
	}
}


