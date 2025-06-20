# typename-array

A C++20 template metaprogramming library for manipulating types as collections. This library enables functional-style operations on types at compile time.

## 🔍 Overview

`typename-array` provides a set of metaprogramming utilities for treating types as values that can be stored in collections, transformed, and manipulated through various operations. The library implements a compile-time "array of types" that functions similarly to standard containers, but operates entirely at compile time.

This project was primarily created as a learning exercise in template metaprogramming.

I mainly use AI to generate the tests and documentation, so they might be not ideal.

## ✨ Featured

- **Type Collections**: Store and manipulate collections of types with `typename_array<Types...>`
- **Type Manipulation**: Transform, filter, find, and combine types using functional-style operations
- **Compile-time Calculations**: 'static_calc' is not actually useful because C++ already has constexpr, but it is a good example of how to use the library
- **Type Binding**: Bind types to template placeholders with `typename_binder`

## 🧩 Key Components

### 🧰 Basic Operations

- **`typename_array<Types...>`**: The core container for storing multiple types
- **`combine<Array1, Array2>`**: Concatenates two type arrays
- **`get<Index, Array>`**: Retrieves a type at a specific index
- **`find<Array, Type>`**: Finds the index of a type in an array
- **`count<Array, Type>`**: Counts occurrences of a type in an array

### 🚀 Advanced Operations

- **`apply<Array, Function>`**: Maps a transformation function to each type in an array
- **`cut<Start, End, Array>`**: Extracts a subrange of types from an array
- **`replace<Index, Array, NewType>`**: Replaces a type at a specific index
- **`insert<Index, Array, Type>`**: Inserts a type at a specific position
- **`check_for_allowed_types<Array, AllowedTypes>`**: Validates types against a whitelist

### 🛠️ Specialized Utilities

- **`typename_binder<Template, Types...>`**: Creates flexible templates with placeholder substitution
- **`symbols_to_int<Symbols...>`**: Converts character value types to integers
- **`int_to_symbols<Value>`**: Converts integers to character value types

### ➕ And more...


## 📋 Requirements

- C++20 compatible compiler
- Initially depended on MSVC++ quirks, but now should compile with clang and gcc as well
