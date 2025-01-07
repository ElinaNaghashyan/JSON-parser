//
// Created by Elina Naghashyan on 03.01.25.
// JSON Parser in C++
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <fstream>

// Represent a JSON value
class JSONValue {
public:
    enum class Type { OBJECT, ARRAY, STRING, NUMBER, BOOLEAN, NULLVALUE };

    Type type;
    std::string stringValue;
    double numberValue;
    bool boolValue;
    std::unordered_map<std::string, JSONValue> objectValue;
    std::vector<JSONValue> arrayValue;

    // Default constructor
    JSONValue() : type(Type::NULLVALUE) {}

    // Constructor for strings
    explicit JSONValue(std::string val) : type(Type::STRING), stringValue(std::move(val)) {}

    // Constructor for numbers
    explicit JSONValue(double val) : type(Type::NUMBER), numberValue(val) {}

    // Constructor for booleans
    explicit JSONValue(bool val) : type(Type::BOOLEAN), boolValue(val) {}

    // Constructor for object and array types
    explicit JSONValue(Type val) : type(val) {}
};

class JSONParser {
private:
    std::string input;
    size_t position;

    char peek() {
        return input[position];
    }

    char consume() {
        return input[position++];
    }

    void skipWhitespace() {
        while (position < input.size() && std::isspace(input[position])) {
            position++;
        }
    }

    JSONValue parseValue();
    JSONValue parseObject();
    JSONValue parseArray();
    JSONValue parseString();
    JSONValue parseNumber();
    JSONValue parseLiteral(const std::string& literal, JSONValue value);

public:
    explicit JSONParser(std::string json) : input(std::move(json)), position(0) {}
    JSONValue parse();
};

JSONValue JSONParser::parse() {
    skipWhitespace();
    JSONValue result = parseValue();
    skipWhitespace();
    if (position != input.size()) {
        throw std::runtime_error("Unexpected characters at end of JSON input");
    }
    return result;
}

JSONValue JSONParser::parseValue() {
    skipWhitespace();
    char current = peek();
    if (current == '{') return parseObject();
    if (current == '[') return parseArray();
    if (current == '"') return parseString();
    if (std::isdigit(current) || current == '-') return parseNumber();
    if (input.compare(position, 4, "true") == 0) return parseLiteral("true", JSONValue(true));
    if (input.compare(position, 5, "false") == 0) return parseLiteral("false", JSONValue(false));
    if (input.compare(position, 4, "null") == 0) return parseLiteral("null", JSONValue());

    throw std::runtime_error("Invalid JSON value");
}

JSONValue JSONParser::parseObject() {
    consume(); // Consume '{'
    skipWhitespace();
    JSONValue object(JSONValue::Type::OBJECT);

    while (peek() != '}') {
        skipWhitespace();
        JSONValue key = parseString();
        skipWhitespace();
        if (consume() != ':') {
            throw std::runtime_error("Expected ':' in object");
        }
        skipWhitespace();
        JSONValue value = parseValue();
        object.objectValue[key.stringValue] = value;
        skipWhitespace();

        if (peek() == ',') {
            consume(); // Consume ','
        } else if (peek() == '}') {
            break;
        } else {
            throw std::runtime_error("Expected ',' or '}' in object");
        }
    }
    consume(); // Consume '}'
    return object;
}

JSONValue JSONParser::parseArray() {
    consume(); // Consume '['
    skipWhitespace();
    JSONValue array(JSONValue::Type::ARRAY);

    while (peek() != ']') {
        skipWhitespace();
        array.arrayValue.push_back(parseValue());
        skipWhitespace();

        if (peek() == ',') {
            consume(); // Consume ','
        } else if (peek() == ']') {
            break;
        } else {
            throw std::runtime_error("Expected ',' or ']' in array");
        }
    }
    consume(); // Consume ']'
    return array;
}

JSONValue JSONParser::parseString() {
    consume(); // Consume '"'
    std::string result;
    while (peek() != '"') {
        char current = consume();
        if (current == '\\') {
            char escaped = consume();
            if (escaped == '"') result += '"';
            else if (escaped == '\\') result += '\\';
            else if (escaped == '/') result += '/';
            else if (escaped == 'b') result += '\b';
            else if (escaped == 'f') result += '\f';
            else if (escaped == 'n') result += '\n';
            else if (escaped == 'r') result += '\r';
            else if (escaped == 't') result += '\t';
            else throw std::runtime_error("Invalid escape character");
        } else {
            result += current;
        }
    }
    consume(); // Consume '"'
    return JSONValue(result);
}

JSONValue JSONParser::parseNumber() {
    size_t start = position;
    while (position < input.size() && (std::isdigit(peek()) || peek() == '.' || peek() == '-' || peek() == '+')) {
        position++;
    }
    double value = std::stod(input.substr(start, position - start));
    return JSONValue(value);
}

JSONValue JSONParser::parseLiteral(const std::string& literal, JSONValue value) {
    if (input.compare(position, literal.size(), literal) != 0) {
        throw std::runtime_error("Invalid literal: " + literal);
    }
    position += literal.size();
    return value;
}

void printJSON(const JSONValue& value, int indent = 0) {
    std::string indentation(indent, ' ');
    switch (value.type) {
        case JSONValue::Type::OBJECT:
            std::cout << "{\n";
        for (const auto& [key, val] : value.objectValue) {
            std::cout << indentation << "  \"" << key << "\": ";
            printJSON(val, indent + 2);
        }
        std::cout << indentation << "}\n";
        break;
        case JSONValue::Type::ARRAY:
            std::cout << "[\n";
        for (const auto& val : value.arrayValue) {
            printJSON(val, indent + 2);
        }
        std::cout << indentation << "]\n";
        break;
        case JSONValue::Type::STRING:
            std::cout << "\"" << value.stringValue << "\"\n";
        break;
        case JSONValue::Type::NUMBER:
            std::cout << value.numberValue << "\n";
        break;
        case JSONValue::Type::BOOLEAN:
            std::cout << (value.boolValue ? "true" : "false") << "\n";
        break;
        case JSONValue::Type::NULLVALUE:
            std::cout << "null\n";
        break;
    }
}

bool validateJSON(const std::string& json) {
    try {
        JSONParser parser(json);
        parser.parse();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Validation Error: " << e.what() << std::endl;
        return false;
    }
}

std::string serializeJSON(const JSONValue& value) {
    switch (value.type) {
        case JSONValue::Type::OBJECT: {
            std::string result = "{";
            for (const auto& [key, val] : value.objectValue) {
                result += "\"" + key + "\":" + serializeJSON(val) + ",";
            }
            if (!value.objectValue.empty()) result.pop_back(); // Remove trailing comma
            result += "}";
            return result;
        }
        case JSONValue::Type::ARRAY: {
            std::string result = "[";
            for (const auto& val : value.arrayValue) {
                result += serializeJSON(val) + ",";
            }
            if (!value.arrayValue.empty()) result.pop_back();
            result += "]";
            return result;
        }
        case JSONValue::Type::STRING:
            return "\"" + value.stringValue + "\"";
        case JSONValue::Type::NUMBER:
            return std::to_string(value.numberValue);
        case JSONValue::Type::BOOLEAN:
            return value.boolValue ? "true" : "false";
        case JSONValue::Type::NULLVALUE:
            return "null";
    }
    return "";
}

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Failed to open file");
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

void writeFile(const std::string& filename, const std::string& data) {
    std::ofstream file(filename);
    if (!file) throw std::runtime_error("Failed to write to file");
    file << data;
}

int main() {
    std::string json = R"({"name": "Elina", "age": 23, "skills": ["Coding", "Music"], "active": true})";

    try {
        JSONParser parser(json);
        JSONValue result = parser.parse();
        std::cout << "JSON parsed successfully!" << std::endl;
        printJSON(result);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

