#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "Core/Type/Reference.h"
#include "Database/Database.h"

namespace QED
{
	namespace Engine
	{
		namespace Asset
		{
			class AssetManager
			{
			private:
				AssetManager();

			public:
				inline static AssetManager& GetInstance()
				{
					static AssetManager instance;
					return instance;
				}

			public:
				void* GetImageData(int id, int* size);

			private:
				Scope<Database::Database> db;
			};
		}
	}
}


#endif // !ASSET_MANAGER_H
