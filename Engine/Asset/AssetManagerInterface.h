#ifndef ASSET_MANAGER_INTERFACE_H
#define ASSET_MANAGER_INTERFACE_H

#include "Module/QEDApi.h"

namespace QED::Engine::Asset
{
	class AssetManager;
}

namespace QED
{
	namespace Interface
	{
		namespace Asset
		{
			class QED_ENGINE_API AssetManager
			{
			public:
				static AssetManager& GetAssetManagerInstance();

			public:
				void* GetImageData(int id, int* size);

			private:
				Engine::Asset::AssetManager* assetManager;
			};
		}
	}
}




#endif // !ASSET_MANAGER_INTERFACE_H
