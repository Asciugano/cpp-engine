#include <engine/assets/AssetParser.hpp>

#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace Engine {

namespace {

class Parser {
public:
  explicit Parser(const std::string &source) : m_source(source) {}

  AssetData parse() {
    AssetData data;

    skipWhitespace();

    while (!eof()) {
      const std::string name = parseIdentifier();

      skipWhitespace();
      expect('=');
      skipWhitespace();

      AssetValue value = parseValue();

      data.sections[name] = std::move(value);

      skipWhitespace();
    }

    return data;
  }

private:
  bool eof() const { return m_position >= m_source.size(); }

  char current() const {
    if (eof())
      return '\0';

    return m_source[m_position];
  }

  char peek(std::size_t offset = 1) const {
    const std::size_t position = m_position + offset;

    if (position >= m_source.size())
      return '\0';

    return m_source[position];
  }

  void advance() {
    if (!eof())
      ++m_position;
  }

  void skipWhitespace() {
    while (!eof()) {
      const char c = current();

      if (std::isspace(static_cast<unsigned char>(c))) {
        advance();
        continue;
      }

      // INFO: Commento //
      if (c == '/' && peek() == '/') {
        advance();
        advance();

        while (!eof() && current() != '\n')
          advance();

        continue;
      }

      break;
    }
  }

  void expect(char expected) {
    skipWhitespace();

    if (current() != expected) {
      error(std::string("Expected '") + expected + "', found '" + current() +
            "'");
    }

    advance();
  }

  void error(const std::string &message) const {
    throw std::runtime_error("AssetParser error at position " +
                             std::to_string(m_position) + ": " + message);
  }

  std::string parseIdentifier() {
    skipWhitespace();

    if (eof())
      error("Expected identifier, found EOF");

    const char first = current();

    if (!std::isalpha(static_cast<unsigned char>(first)) && first != '_') {
      error("Expected identifier");
    }

    const std::size_t start = m_position;

    advance();

    while (!eof()) {
      const char c = current();

      if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_') {
        break;
      }

      advance();
    }

    return m_source.substr(start, m_position - start);
  }

  AssetValue parseValue() {
    skipWhitespace();

    if (eof())
      error("Expected value");

    const char c = current();

    if (c == '"')
      return AssetValue::makeString(parseString());

    if (c == '{')
      return AssetValue::makeObject(parseObject());

    if (c == '[')
      return AssetValue::makeArray(parseArray());

    if (c == '-' || c == '+' || std::isdigit(static_cast<unsigned char>(c))) {
      return parseNumberList();
    }

    if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
      const std::string identifier = parseIdentifier();

      if (identifier == "true")
        return AssetValue::makeBoolean(true);

      if (identifier == "false")
        return AssetValue::makeBoolean(false);

      return AssetValue::makeString(identifier);
    }

    error("Unexpected character");

    return {};
  }

  std::string parseString() {
    skipWhitespace();

    expect('"');

    std::string result;

    while (!eof()) {
      const char c = current();

      if (c == '"') {
        advance();
        return result;
      }

      // Escape
      if (c == '\\') {
        advance();

        if (eof())
          error("Unexpected EOF inside string");

        const char escaped = current();

        switch (escaped) {
        case 'n':
          result += '\n';
          break;

        case 't':
          result += '\t';
          break;

        case 'r':
          result += '\r';
          break;

        case '\\':
          result += '\\';
          break;

        case '"':
          result += '"';
          break;

        default:
          result += escaped;
          break;
        }

        advance();
        continue;
      }

      result += c;
      advance();
    }

    error("Unterminated string");

    return {};
  }

  double parseNumber() {
    skipWhitespace();

    const std::size_t start = m_position;

    if (current() == '-' || current() == '+')
      advance();

    while (std::isdigit(static_cast<unsigned char>(current()))) {
      advance();
    }

    if (current() == '.') {
      advance();

      while (std::isdigit(static_cast<unsigned char>(current()))) {
        advance();
      }
    }

    if (current() == 'e' || current() == 'E') {
      advance();

      if (current() == '+' || current() == '-')
        advance();

      while (std::isdigit(static_cast<unsigned char>(current()))) {
        advance();
      }
    }

    const std::string value = m_source.substr(start, m_position - start);

    try {
      return std::stod(value);
    } catch (...) {
      error("Invalid number: " + value);
    }

    return 0.0;
  }

  AssetValue parseNumberList() {
    AssetValue::Array values;

    values.push_back(AssetValue::makeNumber(parseNumber()));

    skipWhitespace();

    while (current() == ';') {
      advance();
      skipWhitespace();

      values.push_back(AssetValue::makeNumber(parseNumber()));

      skipWhitespace();
    }

    if (values.size() == 1)
      return values.front();

    return AssetValue::makeArray(std::move(values));
  }

  AssetValue::Object parseObject() {
    AssetValue::Object object;

    expect('{');
    skipWhitespace();

    while (!eof() && current() != '}') {

      if (isKeyValue()) {

        const std::string key = parseIdentifier();

        skipWhitespace();
        expect('=');
        skipWhitespace();

        object[key] = parseValue();

      } else {

        AssetValue value = parseValue();

        auto it = object.find("__values");

        if (it == object.end()) {

          AssetValue::Array values;

          values.push_back(std::move(value));

          object["__values"] = AssetValue::makeArray(std::move(values));

        } else {

          it->second.array.push_back(std::move(value));
        }
      }

      skipWhitespace();
    }

    expect('}');

    return object;
  }

  AssetValue::Array parseArray() {
    AssetValue::Array array;

    expect('[');
    skipWhitespace();

    while (!eof() && current() != ']') {

      array.push_back(parseValue());

      skipWhitespace();

      if (current() == ';') {
        advance();
        skipWhitespace();
      }
    }

    expect(']');

    return array;
  }

private:
  bool isKeyValue() const {
    if (eof())
      return false;

    const char c = current();

    if (!std::isalpha(static_cast<unsigned char>(c)) && c != '_') {
      return false;
    }

    std::size_t position = m_position;

    while (position < m_source.size()) {
      const char character = m_source[position];

      if (!std::isalnum(static_cast<unsigned char>(character)) &&
          character != '_') {
        break;
      }

      ++position;
    }

    while (position < m_source.size() &&
           std::isspace(static_cast<unsigned char>(m_source[position]))) {
      ++position;
    }

    return position < m_source.size() && m_source[position] == '=';
  }

  const std::string &m_source;
  std::size_t m_position = 0;
};

} // anonymous namespace

AssetData AssetParser::parse(const std::string &path) {
  std::ifstream file(path);

  if (!file.is_open()) {
    throw std::runtime_error("AssetParser: unable to open file: " + path);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  // INFO: IMPORTANTE:
  // Parser contiene una reference alla stringa.
  // Quindi dobbiamo mantenere source vivo.
  const std::string source = buffer.str();

  Parser parser(source);

  return parser.parse();
}

} // namespace Engine
