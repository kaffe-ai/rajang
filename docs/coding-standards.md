# Coding Standards

This document outlines the coding standards and best practices for this codebase. Adhering to these guidelines ensures consistency, readability, and maintainability across all projects.
1. General Guidelines
1.1. Code Formatting

    Use 4 spaces for indentation (no tabs).

    Limit lines to 80 characters for readability.

    Use consistent spacing around operators and after commas.
    c
    Copy

    int sum = a + b;  // Good
    int sum=a+b;      // Bad

1.2. Naming Conventions

    Use snake_case or camelCase for variable and function names. Be consistent within a project.

    Use UPPER_SNAKE_CASE for constants and macros.

    Use PascalCase for type definitions (e.g., struct, typedef) and append _t to struct type names.
    c
    Copy

    typedef struct Node_t Node_t;     // Struct type with _t suffix
    typedef struct HashTable_t HashTable_t;
    int max_value = 100;             // snake_case variable
    int maxValue = 100;              // camelCase variable
    #define MAX_VALUE 100            // Constant

1.3. Comments

    Use single-line comments (//) for short explanations.

    Use multi-line comments (/* ... */) for detailed descriptions.

    Document all public functions with a brief description, parameters, and return values.
    c
    Copy

    // Calculate the sum of two integers
    int add(int a, int b) {
        return a + b;
    }

2. Language-Specific Guidelines
2.1. C/C++

    Always initialize variables before use.

    Use const for variables that should not be modified.

    Avoid global variables; prefer local scope or function parameters.

    Use #pragma once or include guards in header files.
    c
    Copy

    #ifndef MY_HEADER_H
    #define MY_HEADER_H

    typedef struct Example_t {
        int data;
    } Example_t;

    #endif // MY_HEADER_H

2.2. Python

    Follow PEP 8 guidelines.

    Use snake_case for variable and function names.

    Use PascalCase for class names (no _t suffix).

    Include a docstring for all public functions and classes.
    python
    Copy

    def calculate_sum(a, b):
        """Return the sum of two numbers."""
        return a + b

3. Version Control
3.1. Commit Messages

    Use the Conventional Commits format:
    Copy

    <type>(<scope>): <description>

    Example:
    Copy

    feat(linked-list): add list_remove function
    fix(hash-table): resolve memory leak in hash_destroy

3.2. Branching

    Use feature branches for new functionality.

    Prefix branch names with the type of work:

        feature/ for new features.

        bugfix/ for bug fixes.

        docs/ for documentation updates.

4. Testing
4.1. Unit Tests

    Write unit tests for all public functions.

    Use a testing framework appropriate for the language:

        C: Use assert.h or a framework like Check.

        Python: Use unittest or pytest.

4.2. Test Coverage

    Aim for 80%+ test coverage for critical code.

    Use tools like gcov (C) or coverage.py (Python).

5. Documentation
5.1. README Files

    Include a README.md in every project directory.

    Use the provided README template for consistency.

5.2. Inline Documentation

    Document all public APIs, including parameters, return values, and examples.

    Use Doxygen for C/C++ or Sphinx for Python.

6. Code Reviews
6.1. Review Process

    All pull requests must be reviewed by at least one other developer.

    Focus on:

        Code readability and maintainability.

        Adherence to coding standards.

        Proper error handling and edge cases.

6.2. Feedback

    Provide constructive feedback.

    Use GitHub comments to suggest improvements.

7. Tools
7.1. Linting and Formatting

    Use the following tools to enforce coding standards:

        C/C++: clang-format, clang-tidy.

        Python: black, flake8.

7.2. CI/CD

    Set up GitHub Actions or GitLab CI for automated testing and linting.

8. License

All code in this repository is licensed under the MIT License. Include the license header in all source files:
c
Copy

// Copyright (c) [Year] [Your Name]
// Licensed under the MIT License.

9. References

    Google C++ Style Guide

    PEP 8 — Python Style Guide

    Conventional Commits

By following these standards, we can maintain a clean, consistent, and professional codebase. Happy coding! 🚀
