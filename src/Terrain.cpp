#include "CRobes/Terrain.hpp"
#include "CRobes/Solids.hpp"

void crb::Terrain::ChunkManager::updateChunks(const crb::Space::Vec3& cameraPosition)
{
  std::vector<std::pair<int, int>> visibleChunks = this->_calculateVisibleChunks(cameraPosition);

  this->chunks.erase(std::remove_if(
    this->chunks.begin(),
    this->chunks.end(),
    [&](const crb::Solids::Solid& chunk)
    {
      for (const auto& chunkPosition : visibleChunks)
      {
        if (
          crb::Space::getChunkX(chunk.getPosition().x) == chunkPosition.first &&
          crb::Space::getChunkZ(chunk.getPosition().z) == chunkPosition.second
        ) return false;
      }
      return true;
    }
  ), this->chunks.end());

  for (const auto& chunkPosition : visibleChunks)
  {
    bool chunkFound {false};
    for (const auto& chunk : this->chunks)
    {
      if (
        crb::Space::getChunkX(chunk.getPosition().x) == chunkPosition.first &&
        crb::Space::getChunkZ(chunk.getPosition().z) == chunkPosition.second
      ) chunkFound = true;
    }
    if (!chunkFound)
    {
      this->chunks.emplace_back(solidFactory->createPlane(
        {chunkPosition.first * crb::CHUNK_SIZE, 0.f, chunkPosition.second * crb::CHUNK_SIZE},
        crb::CHUNK_SIZE,
        crb::CHUNK_SIZE,
        crb::CHUNK_SEGMENTS,
        *this->chunkStrategy
      ));
    }
  }
}

void crb::Terrain::ChunkManager::renderChunks(const crb::Graphics::Shader& shader)
{
  for (const crb::Solids::Solid& chunk : this->chunks)
  {
    chunk.render(shader, GL_TRIANGLE_STRIP);
  }
}

std::vector<std::pair<int, int>> crb::Terrain::ChunkManager::_calculateVisibleChunks(const crb::Space::Vec3& cameraPosition)
{
  std::vector<std::pair<int, int>> chunks;

  int cameraChunkX = crb::Space::getChunkX(cameraPosition);
  int cameraChunkZ = crb::Space::getChunkZ(cameraPosition);

  for (int z = 0; z < this->renderDistance * 2 - 1; z++)
  {
    for (int x = 0; x < this->renderDistance * 2 - 1; x++)
    {
      chunks.push_back(std::pair(
        x - this->renderDistance + cameraChunkX + 1,
        z - this->renderDistance + cameraChunkZ + 1
      ));
    }
  }

  return chunks;
}
