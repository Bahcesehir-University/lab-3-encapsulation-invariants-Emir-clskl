# Lab: Encapsulation and Invariants

**Course:** CMP1002  
**Level:** 2nd Year Engineering  
**Duration:** 60 minutes  
**Topic:** Encapsulation, class invariants, access control, and defensive programming in C++

---

## Learning Objectives

By completing this lab, you will be able to:

1. Apply encapsulation by using private data members and public accessor/mutator methods.
2. Define and enforce class invariants through constructors and setters.
3. Use exception handling (`throw`, `try/catch`) to reject invalid state.
4. Design classes that protect their internal state from external misuse.
5. Understand why some data should never be exposed (e.g., raw passwords).

---

## Prerequisites

- Basic C++ syntax (variables, functions, loops, conditionals)
- Familiarity with classes, constructors, and member functions
- Basic understanding of exceptions (`throw`, `try`, `catch`)

---

## File Structure

```
lab-encapsulation/
├── MainProgram.cpp    # Your working file (student version)
├── test.cpp           # Catch2 test file (do not modify)
├── catch.hpp          # Catch2 header (provided)
├── Makefile           # Build system
├── README.md          # This file
├── explain.txt        # Quick revision sheet
└── explain.md         # Structured concept guide
```

---

## Instructions

### Step 1: Read the Materials

Read `explain.txt` for a quick overview, then review `explain.md` for deeper understanding.

### Step 2: Open MainProgram.cpp

Look for `// TODO` comments. Each marks a section you need to implement.

### Step 3: Implement the Classes

You will implement three classes:

1. **Temperature** — Enforces that no temperature goes below absolute zero (-273.15°C).
2. **BankAccount** — Enforces non-negative balance and non-empty owner name.
3. **Password** — Enforces minimum length and digit requirements; never exposes the raw password.

### Step 4: Compile and Run

```bash
# Build the program
make

# Run it
./MainProgram
```

### Step 5: Run the Tests

```bash
# Build and run tests
make test
```

All tests must pass for full marks.

### Step 6: Clean Up

```bash
make clean
```

---

## Compilation Details

- Compiler: `g++`
- Standard: C++17
- Flags: `-Wall --std=c++17`

---

## Submission Instructions

1. Submit only your `MainProgram.cpp` file.
2. Do **not** modify `test.cpp`, `catch.hpp`, or `Makefile`.
3. Ensure `make test` passes all tests before submitting.
4. Include your name and student ID as a comment at the top of your file.

---

## Common Mistakes

| Mistake | How to Avoid |
|---------|-------------|
| Forgetting to validate in the constructor | Always check invariants in constructors AND setters |
| Using `cout` instead of `throw` for errors | Use `throw std::invalid_argument(...)` or `throw std::runtime_error(...)` |
| Making data members public | Keep all data `private`; provide getters/setters |
| Adding a `getPassword()` method | The whole point is that some data should NOT be exposed |
| Not checking edge cases (zero, negative) | Test boundaries: zero deposit, exact balance withdrawal, etc. |
| Changing state before validating | Validate first, then modify. If validation fails, state should be unchanged |

---

## Academic Integrity

This lab must be completed individually. You may consult course materials and the C++ reference documentation. Do not share code with other students or use AI-generated solutions. Plagiarism detection tools will be used.
