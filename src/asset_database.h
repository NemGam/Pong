#ifndef ASSET_DATABASE_H
#define ASSET_DATABASE_H
#include <map>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "texture.h"
#include "unique_ptrs_destructors.h"

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
		const Texture* GetTexture(const std::string& name) const;
		//Returns a pointer to a font. Loads it if it wasn't loaded before
		const TTF_Font* GetFont(const std::string& name, int size) const;

	private:
		//To load textures
		const SDL_Renderer* renderer_;

		//Loads the texture from disk
		bool LoadTexture(const std::string& name, const std::string& path) const;
		//Loads the font from disk
		bool LoadFont(const std::string& name, int size, const std::string& path) const;

		mutable std::map<std::string, Texture> textures_;
		mutable std::map<std::string, std::unique_ptr<TTF_Font, TtfFontDestructor>> fonts_;

	};
}
#endif // ASSET_DATABASE_H
