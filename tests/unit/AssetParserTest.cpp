#include <catch2/catch_test_macros.hpp>

#include <engine/assets/AssetParser.hpp>

#include <filesystem>
#include <fstream>
#include <string>

namespace {

std::string createTestAsset(const std::string &name,
                            const std::string &content) {

  const std::filesystem::path path =
      std::filesystem::path(TEST_ASSET_DIR) / name;

  std::ofstream file(path);

  REQUIRE(file.is_open());

  file << content;

  return path.string();
}

} // namespace

TEST_CASE("AssetParser parses sections", "[AssetParser]") {

  const std::string path = createTestAsset("sections.asset",
                                           R"(
STANDARD={
    save=true
}

GAMEPLAY={
    type="car"
}
)");

  const Engine::AssetData data = Engine::AssetParser::parse(path);

  REQUIRE(data.sections.contains("STANDARD"));
  REQUIRE(data.sections.contains("GAMEPLAY"));

  const auto &standard = data.sections.at("STANDARD");

  REQUIRE(standard.isObject());
  REQUIRE(standard.get("save").isBoolean());
  REQUIRE(standard.get("save").boolean == true);

  const auto &gameplay = data.sections.at("GAMEPLAY");

  REQUIRE(gameplay.get("type").isString());
  REQUIRE(gameplay.get("type").string == "car");
}

TEST_CASE("AssetParser parses numbers", "[AssetParser]") {

  const std::string path = createTestAsset("numbers.asset",
                                           R"(
PHYSICS={
    mass=1200
    friction=0.8
}
)");

  const Engine::AssetData data = Engine::AssetParser::parse(path);

  const auto &physics = data.sections.at("PHYSICS");

  REQUIRE(physics.get("mass").isNumber());
  REQUIRE(physics.get("mass").number == 1200);

  REQUIRE(physics.get("friction").isNumber());
  REQUIRE(physics.get("friction").number == 0.8);
}

TEST_CASE("AssetParser parses compact numeric values", "[AssetParser]") {

  const std::string path = createTestAsset("mesh.asset",
                                           R"(
RENDER={
    meshes=[
        {
            3;3

            -0.5;-0.5;0
            0.5;-0.5;0
            0;0.5;0

            0;1;2
        }
    ]
}
)");

  const Engine::AssetData data = Engine::AssetParser::parse(path);

  const auto &render = data.sections.at("RENDER");

  const auto &meshes = render.get("meshes");

  REQUIRE(meshes.isArray());
  REQUIRE(meshes.array.size() == 1);

  const auto &mesh = meshes.array[0];

  REQUIRE(mesh.isObject());

  const auto &values = mesh.get("__values");

  REQUIRE(values.isArray());
  REQUIRE(values.array.size() == 5);

  // Header: 3 vertices, 3 indices
  REQUIRE(values.array[0].isArray());
  REQUIRE(values.array[0].array[0].number == 3);
  REQUIRE(values.array[0].array[1].number == 3);

  // First vertex
  REQUIRE(values.array[1].isArray());
  REQUIRE(values.array[1].array.size() == 3);

  REQUIRE(values.array[1].array[0].number == -0.5);
  REQUIRE(values.array[1].array[1].number == -0.5);
  REQUIRE(values.array[1].array[2].number == 0);

  // First triangle
  REQUIRE(values.array[4].isArray());
  REQUIRE(values.array[4].array[0].number == 0);
  REQUIRE(values.array[4].array[1].number == 1);
  REQUIRE(values.array[4].array[2].number == 2);
}

TEST_CASE("AssetParser supports comments", "[AssetParser]") {

  const std::string path = createTestAsset("comments.asset",
                                           R"(
 // This is a comment

 STANDARD={
     save=true // another comment
 }

 RENDER={
     meshes=[]
 }
)");

  const Engine::AssetData data = Engine::AssetParser::parse(path);

  REQUIRE(data.sections.contains("STANDARD"));
  REQUIRE(data.sections.contains("RENDER"));

  REQUIRE(data.sections.at("STANDARD").get("save").boolean == true);
}

TEST_CASE("AssetParser parses multiple meshes", "[AssetParser]") {

  const std::string path = createTestAsset("multiple_meshes.asset",
                                           R"(
RENDER={
    meshes=[
        {
            3;3

            0;0;0
            1;0;0
            0;1;0

            0;1;2
        }

        {
            3;3

            0;0;0
            2;0;0
            0;2;0

            0;1;2
        }
    ]
}
)");

  const Engine::AssetData data = Engine::AssetParser::parse(path);

  const auto &meshes = data.sections.at("RENDER").get("meshes");

  REQUIRE(meshes.isArray());
  REQUIRE(meshes.array.size() == 2);
}
