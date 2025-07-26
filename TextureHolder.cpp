#include "TextureHolder.h"
// Include the assert feature
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;
TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename)
{
	// Get a reference to m_texture using m_s_Instance
	auto& m = m_s_Instance->m_Texture;
	// auto is the equivalent of map<string, Texture>
	// Create an iterator to hold a key-value-pair (kvp)
	// and search for the required kvp
	// using the passed in file name
	auto keyValuePair = m.find(filename);
	// Auto is eqivalent of map<string, Texture>::interator


	// Did we find a match?
	if (keyValuePair != m.end())
	{
		// Yes
		// Return the texture,
		// the second part of the kvp, the texture
		return keyValuePair->second;
	}
	else
	{
		//filename not found
		// create a new key value pair using the filename
		auto& texture = m[filename];
		//load the texture from file in the usual way
		texture.loadFromFile(filename);
		// return the texture to the calling code
		return texture;
	}
}