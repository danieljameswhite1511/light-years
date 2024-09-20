#pragma once
#include "Core.h"
#include "SFML/Graphics/Texture.hpp"

namespace ly
{
	class AssetManager
	{
	public:
		static AssetManager& Get();
		shared<sf::Texture> LoadTexture(const std::string& path);
		void CleanCycle();
		void SetAssetRootDirectory(const std::string& rootDirectory);
	protected:
		AssetManager();

	private:
		static unique<AssetManager> assetManager;
		dictionary< std::string, shared<sf::Texture>> mLoadedTextureMap;
		std::string mRootDirectory;


	};
}
