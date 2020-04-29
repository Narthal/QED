#include "EnginePCH.h"
#include "AssetManagerInterface.h"

#include "AssetManager.h"

namespace QED
{
	namespace Interface
	{
		namespace Asset
		{
			AssetManager& AssetManager::GetAssetManagerInstance()
			{
				static AssetManager assetManagerInterface;
				assetManagerInterface.assetManager = &Engine::Asset::AssetManager::GetInstance();
				return assetManagerInterface;
			}

			void* AssetManager::GetImageData(int id, int* size)
			{
				return assetManager->GetImageData(id, size);
			}
		}
	}
}
