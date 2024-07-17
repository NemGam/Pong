#include "asset_database.h"

#include "logger.h"
#include "unique_ptrs_destructors.h"

namespace pong {
	AssetDatabase::AssetDatabase(const SDL_Renderer* renderer) :
		renderer_(renderer)
	{}

	const Texture* AssetDatabase::GetTexture(const std::string& name) const {
		if (textures_.find(name) != textures_.end()) {
			return &textures_.at(name);
		}

		if (!LoadTexture(name, "resources/Textures/" + name)) {
			logger::LogAndShowError(SDL_GetError());
			return nullptr;
		}
		
		return &textures_.at(name);
	}

	const TTF_Font* AssetDatabase::GetFont(const std::string& name, int size) const {
		if (fonts_.find(name) != fonts_.end()) {
			return fonts_.at(name).get();
		}

		if (!LoadFont(name, size, "resources/Fonts/" + name)) {
			logger::LogAndShowError(SDL_GetError());
			return nullptr;
		}

		return fonts_.at(name).get();
	}

	bool AssetDatabase::LoadTexture(const std::string& name, const std::string& path) const {
		Texture tex = Texture(renderer_);

		if (!tex.CreateFromFile(path)) {
			logger::LogAndShowError(SDL_GetError());
			return false;
		}


		
		textures_.insert(std::make_pair(name, tex));
		return true;
	}

	bool AssetDatabase::LoadFont(const std::string& name, int size, const std::string& path) const {
		TTF_Font* font = TTF_OpenFont(path.c_str(), size);

		if (!font) {
			logger::LogAndShowError(TTF_GetError());
			return false;
		}

		fonts_.emplace(name, std::unique_ptr<TTF_Font, TtfFontDestructor>(font));
		return true;
	}
}


