#include <engine/assets/AssetData.hpp>
#include <engine/assets/AssetLoader.hpp>
#include <engine/assets/AssetParser.hpp>
#include <engine/renderer/ShaderDataType.hpp>

#include <memory>
#include <stdexcept>
#include <utility>

namespace Engine {

namespace {

const AssetValue &getRender(const AssetData &data) {
  auto it = data.sections.find("RENDER");

  if (it == data.sections.end())
    throw std::runtime_error("AssetLoader: missing RENDER section");

  return it->second;
}

const AssetValue &getMeshes(const AssetData &data) {
  const AssetValue &render = getRender(data);

  return render.get("meshes");
}

std::unique_ptr<Mesh> loadFirstMesh(const AssetData &data) {
  const AssetValue &meshes = getMeshes(data);

  if (!meshes.isArray())
    throw std::runtime_error("AssetLoader: RENDER.meshes must be an array");

  if (meshes.array.empty())
    return nullptr;

  const AssetValue &mesh = meshes.array.front();

  if (!mesh.isObject())
    throw std::runtime_error("AssetLoader: mesh must be an object");

  const AssetValue &values = mesh.get("__values");

  if (!values.isArray())
    throw std::runtime_error("AssetLoader: mesh __values must be an array");

  if (values.array.empty())
    throw std::runtime_error("AssetLoader: mesh contains no data");

  const AssetValue &counts = values.array[0];

  if (!counts.isArray() || counts.array.size() != 2) {
    throw std::runtime_error("AssetLoader: invalid mesh header");
  }

  if (!counts.array[0].isNumber() || !counts.array[1].isNumber()) {
    throw std::runtime_error("AssetLoader: mesh header must contain numbers");
  }

  const std::size_t vertexCount =
      static_cast<std::size_t>(counts.array[0].number);

  const std::size_t indexCount =
      static_cast<std::size_t>(counts.array[1].number);

  std::vector<float> vertices;
  vertices.reserve(vertexCount * 3);

  std::size_t current = 1;

  for (std::size_t i = 0; i < vertexCount; ++i) {
    if (current >= values.array.size()) {
      throw std::runtime_error("AssetLoader: not enough vertices");
    }

    const AssetValue &vertex = values.array[current++];

    if (!vertex.isArray() || vertex.array.size() != 3) {
      throw std::runtime_error("AssetLoader: vertex must contain 3 values");
    }

    for (const AssetValue &value : vertex.array) {
      if (!value.isNumber()) {
        throw std::runtime_error("AssetLoader: vertex value must be a number");
      }

      vertices.push_back(static_cast<float>(value.number));
    }
  }

  std::vector<uint32_t> indices;
  indices.reserve(indexCount);

  while (current < values.array.size() && indices.size() < indexCount) {

    const AssetValue &indexGroup = values.array[current++];

    if (!indexGroup.isArray()) {
      throw std::runtime_error("AssetLoader: index group must be an array");
    }

    for (const AssetValue &value : indexGroup.array) {
      if (!value.isNumber()) {
        throw std::runtime_error("AssetLoader: index must be a number");
      }

      indices.push_back(static_cast<uint32_t>(value.number));

      if (indices.size() == indexCount)
        break;
    }
  }

  if (vertices.size() != vertexCount * 3) {
    throw std::runtime_error("AssetLoader: invalid vertex count");
  }

  if (indices.size() != indexCount) {
    throw std::runtime_error("AssetLoader: invalid index count");
  }

  return Mesh::create(vertices.data(), vertices.size() * sizeof(float),
                      indices.data(), indices.size(),
                      {{ShaderDataType::Float3, "a_Position"}});
}

} // namespace

std::unique_ptr<Entity> AssetLoader::load(const std::string &path) {

  const AssetData data = AssetParser::parse(path);

  auto entity = std::make_unique<Entity>();

  auto mesh = loadFirstMesh(data);

  if (mesh)
    entity->setMesh(std::move(mesh));

  return entity;
}

std::unique_ptr<Entity> AssetLoader::load(const std::string &path,
                                          const std::string &vertexPath,
                                          const std::string &fragPath,
                                          const glm::vec4 &color) {

  const AssetData data = AssetParser::parse(path);

  auto entity = std::make_unique<Entity>();

  auto mesh = loadFirstMesh(data);

  if (mesh) {
    entity->setMesh(std::move(mesh));

    auto material =
        std::make_unique<Material>(Shader::create(vertexPath, fragPath), color);

    entity->setMaterial(std::move(material));
  }

  return entity;
}

} // namespace Engine
