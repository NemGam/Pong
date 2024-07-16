#ifndef ASSET_DATABASE_H
#define ASSET_DATABASE_H
#include <map>
#include <string>

#include "texture.h"

namespace pong {

	class AssetDatabase
	{
	public:
		explicit AssetDatabase(const SDL_Renderer* renderer);
		AssetDatabase(AssetDatabase&) = delete;
		AssetDatabase(AssetDatabase&&) = delete;
		AssetDatabase& operator=(AssetDatabase&) = delete;
		AssetDatabase&& operator=(AssetDatabase&&) = delete;


		~AssetDatabase() = default;


		//Returns a pointer to a texture. Loads it if it wasn't loaded before
		const Texture* GetTexture(std::string name) const;

	private:
		//To load textures
		const SDL_Renderer* renderer_;

		//Loads texture located at path relative to the resources folder
		bool LoadTexture(const std::string& name, const std::string& path) const;

		mutable std::map<std::string, Texture> textures_;

	};
}
#endif // ASSET_DATABASE_H
