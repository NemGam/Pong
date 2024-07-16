#include "asset_database.h"

#include "logger.h"

namespace pong {
	AssetDatabase::AssetDatabase(const SDL_Renderer* renderer) :
		renderer_(renderer)
	{}

	const Texture* AssetDatabase::GetTexture(std::string name) const {
		if (textures_.find(name) != textures_.end()) {
			return &textures_.at(name);
		}

		if (!LoadTexture(name, "resources/Textures/" + name)) {
			logger::LogAndShowError(SDL_GetError());
			return nullptr;
		}
		
		return &textures_.at(name);
	}

	bool AssetDatabase::LoadTexture(const std::string& name, const std::string& path) const {
		Texture tex = Texture(renderer_);

		if (!tex.LoadFromFile(path)) {
			logger::LogAndShowError(SDL_GetError());
			return false;
		}
		auto gf = std::make_pair(name, tex);


		
		textures_.insert(std::make_pair(name, tex));
		return true;
	}
}


