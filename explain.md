# Encapsulation and Invariants

## 1. Concept Overview

**Encapsulation** is the practice of bundling data and the methods that operate on that data into a single unit (a class), while restricting direct access to the data from outside.

**Class invariants** are conditions that must always hold true for every object of a class, from the moment it is constructed until it is destroyed. If an invariant is ever violated, the object is in an invalid state.

Together, encapsulation and invariants form the foundation of **defensive programming**: you write classes that actively protect themselves from misuse.

## 2. Key Concepts

- **Private data members**: Internal state is hidden using the `private` access specifier. External code cannot read or modify them directly.
- **Public interface**: The class exposes a controlled set of `public` methods (getters, setters, operations) that the outside world uses.
- **Constructor validation**: The constructor is the first line of defense. It must check all invariants before the object is fully created.
- **Setter validation**: Any method that changes state must re-check invariants before applying the change.
- **Exception-based rejection**: When invalid input is detected, throw an exception (e.g., `std::invalid_argument`) to signal the error and prevent the state change.
- **Selective exposure**: Not every piece of data needs a getter. Sensitive information (like passwords) should be verifiable but not readable.

## 3. Important Keywords

| Keyword | Explanation |
|---------|-------------|
| `private` | Access specifier; members are only accessible within the class |
| `public` | Access specifier; members are accessible from anywhere |
| `const` method | A member function that promises not to modify the object's state |
| `explicit` | Prevents implicit conversions in single-argument constructors |
| `throw` | Raises an exception to signal an error condition |
| `std::invalid_argument` | Exception type for invalid input values |
| `std::runtime_error` | Exception type for errors detectable only at runtime |
| Invariant | A condition that must always be true for a valid object |
| Getter | A method that returns internal state without modifying it |
| Setter | A method that modifies internal state after validation |

## 4. Common Mistakes

- **Making data public**: Defeats the entire purpose of encapsulation. Always use `private`.
- **Forgetting constructor validation**: An object must be valid from birth. Never skip checks in the constructor.
- **Modifying state before validating**: If you change `balance_` and then check if it's valid, you've already corrupted the object. Validate first, then modify.
- **Using `cout` for errors instead of `throw`**: Printing an error message does not stop execution. Use exceptions to enforce invariants.
- **Exposing everything with getters**: Just because you can write `getX()` doesn't mean you should. Ask: "Does the caller need this?"
- **Not using `const` on getters**: A getter like `double getBalance()` should be `double getBalance() const` to signal it doesn't change state.

## 5. Mini Examples

### Enforcing an invariant in a constructor

```cpp
class Age {
private:
    int age_;
public:
    explicit Age(int a) {
        if (a < 0 || a > 150)
            throw std::invalid_argument("Invalid age");
        age_ = a;
    }
    int get() const { return age_; }
};
```

### Setter with validation

```cpp
void setAge(int a) {
    if (a < 0 || a > 150)
        throw std::invalid_argument("Invalid age");
    age_ = a;  // only reached if valid
}
```

### Selective exposure (no raw getter)

```cpp
class Secret {
private:
    std::string code_;
public:
    explicit Secret(const std::string& c) : code_(c) {}
    bool verify(const std::string& attempt) const {
        return attempt == code_;
    }
    // No getCode() — the value is never exposed
};
```

## 6. When to Use This

- **Any class that holds data with rules**: ages, temperatures, percentages, scores, balances — if there are valid ranges or conditions, use invariants.
- **Security-sensitive classes**: passwords, tokens, encryption keys — use encapsulation to prevent exposure.
- **Financial or transactional systems**: bank accounts, inventory counts — invariants prevent impossible states (negative stock, overdrafts).
- **Configuration objects**: settings with minimum/maximum values, required fields, or mutual constraints.
- **Any collaborative codebase**: encapsulation protects your class from being accidentally broken by other developers.
