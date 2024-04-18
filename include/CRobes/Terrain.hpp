#ifndef CRB_TERRAIN_HPP
#define CRB_TERRAIN_HPP

#include <cmath>
#include <algorithm>
#include <vector>

#include "Graphics.hpp"
#include "Space.hpp"

namespace crb::Solids {
  class SolidFactory;
  class Solid;
}

namespace crb
{
  namespace Terrain
  {
    /**
     * @brief Abstract base class for defining chunk generation strategies.
     */
    class ChunkStrategy
    {
      public:
        /**
         * @brief Generates the position of a chunk based on its coordinates.
         * 
         * @param x The x-coordinate of the chunk.
         * @param z The z-coordinate of the chunk.
         * @return The generated position of the chunk.
         */
        virtual float generatePosition(float x, float z) const = 0;
    };

    /**
     * @brief Chunk generation strategy that generates flat terrain.
     */
    class FlatChunkStrategy : public ChunkStrategy
    {
      public:
        /**
         * @brief Generates the position of a chunk, always returning 0.
         * 
         * @param x The x-coordinate of the chunk.
         * @param z The z-coordinate of the chunk.
         * @return The generated position of the chunk (always 0).
         */
        float generatePosition(float x, float z) const
        { return 0.f; }
    };

    /**
     * @brief Chunk generation strategy that generates terrain using sine function.
     */
    class SinChunkStrategy : public ChunkStrategy
    {
      public:
        /**
         * @brief Generates the position of a chunk using sine function.
         * 
         * @param x The x-coordinate of the chunk.
         * @param z The z-coordinate of the chunk.
         * @return The generated position of the chunk using sine function.
         */
        float generatePosition(float x, float y) const
        {
          return sinf(x);
        }
    };

    /**
     * @brief Class for managing chunks and their generation.
     */
    class ChunkManager
    {
      public:
        /**
         * @brief Constructs a ChunkManager object.
         * 
         * @param chunkSize The size of each chunk.
         * @param renderDistance The rendering distance for chunks.
         * @param solidFactory Pointer to a SolidFactory object for creating solids.
         * @param chunkStrategy Pointer to a ChunkStrategy object for generating chunks.
         */
        ChunkManager(
          const float chunkSize,
          const unsigned int renderDistance,
          crb::Solids::SolidFactory* solidFactory,
          crb::Terrain::ChunkStrategy* chunkStrategy
        )
        : chunkSize(chunkSize), renderDistance(renderDistance), solidFactory(solidFactory), chunkStrategy(chunkStrategy)
        {
          this->chunks.reserve(pow(renderDistance * 2 - 1, 2));
        }

        /**
         * @brief Updates the chunks based on the camera position.
         * 
         * @param cameraPosition The position of the camera.
         */
        void updateChunks(const crb::Space::Vec3& cameraPosition);
        /**
         * @brief Renders the visible chunks using the specified shader.
         * 
         * @param shader The shader to use for rendering.
         */
        void renderChunks(const crb::Graphics::Shader& shader);

      private:
        float chunkSize {0.f};
        unsigned int renderDistance {1};
        crb::Solids::SolidFactory* solidFactory {NULL};
        crb::Terrain::ChunkStrategy* chunkStrategy {NULL};

        std::vector<crb::Solids::Solid> chunks;

        std::vector<std::pair<int, int>> _calculateVisibleChunks(const crb::Space::Vec3& cameraPosition);
    };
  }
}

#endif // CRB_TERRAIN_HPP
