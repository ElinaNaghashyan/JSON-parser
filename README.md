# JSON Parser in C++

This project is a robust JSON parser implemented in C++. It provides functionality to parse, query, and manipulate JSON data, making it ideal for various applications where structured data handling is required.

## Features

1. **JSON Parsing**: Supports parsing JSON objects, arrays, strings, numbers, booleans, and null values.

2. **Validation**: Validates JSON syntax to ensure input conforms to the JSON standard.

3. **Serialization**: Converts JSON data back into a string representation.

4. **Querying**: Supports querying JSON values using JSONPath-like syntax.

5. **Modification**:
   - Update values within JSON objects.
   - Merge multiple JSON objects.
   - Delete keys from JSON objects.

6. **Utilities**:
   - Pretty printing for formatted JSON output.
   - Flattening and unflattening JSON structures.
   - Benchmarking JSON parsing performance.

7. **Schema Validation**: Validates JSON objects against a defined schema.

## Usage

### Parsing JSON
```cpp
#include "JSONParser.h"

std::string json = R"({"name": "Elina", "age": 23, "skills": ["Coding", "Music"], "active": true})";
JSONParser parser(json);
JSONValue result = parser.parse();
printJSON(result); // Outputs the parsed JSON
```

### Serializing JSON
```cpp
std::string serialized = serializeJSON(result);
std::cout << serialized << std::endl;
```

### Querying JSON
```cpp
JSONValue name = queryJSON(result, "name");
std::cout << "Name: " << name.stringValue << std::endl;
```

### Modifying JSON
```cpp
updateJSON(result, "age", JSONValue(24));
deleteKey(result, "active");
```

### Flattening JSON
```cpp
std::unordered_map<std::string, JSONValue> flattened;
flattenJSON(result, flattened);
for (const auto& [key, value] : flattened) {
    std::cout << key << ": " << serializeJSON(value) << std::endl;
}
```

### Schema Validation
```cpp
JSONValue schema = JSONParser(R"({"name": "string", "age": "number"})").parse();
bool isValid = validateSchema(result, schema);
if (isValid) {
    std::cout << "JSON matches schema." << std::endl;
} else {
    std::cout << "JSON does not match schema." << std::endl;
}
```

### Benchmarking
```cpp
benchmark(json);
```

## File Operations

### Reading JSON from File
```cpp
std::string json = readFile("input.json");
```

### Writing JSON to File
```cpp
writeFile("output.json", serialized);
```

## Error Handling
All parsing and manipulation functions throw `std::runtime_error` with descriptive error messages if an operation fails. Use try-catch blocks to handle exceptions.

### Example
```cpp
try {
    JSONParser parser(json);
    JSONValue result = parser.parse();
    std::cout << "Parsing successful!" << std::endl;
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

## Testing
The project includes a `testJSONParser` function to validate basic functionality. Customize this function to add more test cases.

## Dependencies
- Standard C++ libraries: `<iostream>`, `<string>`, `<unordered_map>`, `<vector>`, `<stdexcept>`, `<fstream>`, `<sstream>`, `<cctype>`, `<cassert>`, and `<chrono>`.

## Building the Project
Use any C++ compiler (e.g., GCC, Clang, MSVC). Compile with the following command:

```bash
g++ -std=c++17 -o json_parser main.cpp
```

## Future Improvements
1. Add support for custom error codes.
2. Extend schema validation with detailed types and constraints.
3. Optimize performance for large JSON inputs.
4. Integrate with external JSON libraries for comparison.
5. Add multithreading support for parallel parsing.
---
