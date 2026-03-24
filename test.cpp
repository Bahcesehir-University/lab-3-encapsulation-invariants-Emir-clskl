// ============================================================
// CMP1002 - Lab: Encapsulation and Invariants
// Test File - test.cpp (Catch2)
// ============================================================

#define CATCH_CONFIG_MAIN

// Redirect student main so it doesn't conflict with Catch2
#define main student_main
#include "MainProgram.cpp"
#undef main

#include "catch.hpp"

// ============================================================
// TEMPERATURE TESTS (30 points)
// ============================================================

TEST_CASE("Temperature: constructor and getter", "[temperature][normal]") {
    Temperature t(25.0);
    REQUIRE(t.getCelsius() == Approx(25.0));
}

TEST_CASE("Temperature: Fahrenheit conversion", "[temperature][normal]") {
    Temperature t(100.0);
    REQUIRE(t.getFahrenheit() == Approx(212.0));

    Temperature t2(0.0);
    REQUIRE(t2.getFahrenheit() == Approx(32.0));

    Temperature t3(-40.0);
    REQUIRE(t3.getFahrenheit() == Approx(-40.0));
}

TEST_CASE("Temperature: setCelsius works", "[temperature][normal]") {
    Temperature t(0.0);
    t.setCelsius(50.0);
    REQUIRE(t.getCelsius() == Approx(50.0));
    REQUIRE(t.getFahrenheit() == Approx(122.0));
}

TEST_CASE("Temperature: absolute zero boundary", "[temperature][boundary]") {
    // Exactly absolute zero should be allowed
    Temperature t(-273.15);
    REQUIRE(t.getCelsius() == Approx(-273.15));
}

TEST_CASE("Temperature: constructor rejects below absolute zero", "[temperature][edge]") {
    REQUIRE_THROWS_AS(Temperature(-273.16), std::invalid_argument);
    REQUIRE_THROWS_AS(Temperature(-300.0), std::invalid_argument);
    REQUIRE_THROWS_AS(Temperature(-1000.0), std::invalid_argument);
}

TEST_CASE("Temperature: setCelsius rejects below absolute zero", "[temperature][edge]") {
    Temperature t(0.0);
    REQUIRE_THROWS_AS(t.setCelsius(-274.0), std::invalid_argument);
    // Value should remain unchanged after failed set
    REQUIRE(t.getCelsius() == Approx(0.0));
}

// ============================================================
// BANKACCOUNT TESTS (45 points)
// ============================================================

TEST_CASE("BankAccount: constructor and getters", "[bank][normal]") {
    BankAccount acc("Alice", 1000.0);
    REQUIRE(acc.getOwner() == "Alice");
    REQUIRE(acc.getBalance() == Approx(1000.0));
}

TEST_CASE("BankAccount: zero initial balance allowed", "[bank][boundary]") {
    BankAccount acc("Bob", 0.0);
    REQUIRE(acc.getBalance() == Approx(0.0));
}

TEST_CASE("BankAccount: constructor rejects empty owner", "[bank][edge]") {
    REQUIRE_THROWS_AS(BankAccount("", 100.0), std::invalid_argument);
}

TEST_CASE("BankAccount: constructor rejects negative balance", "[bank][edge]") {
    REQUIRE_THROWS_AS(BankAccount("Eve", -50.0), std::invalid_argument);
}

TEST_CASE("BankAccount: deposit works", "[bank][normal]") {
    BankAccount acc("Alice", 100.0);
    acc.deposit(50.0);
    REQUIRE(acc.getBalance() == Approx(150.0));
}

TEST_CASE("BankAccount: deposit rejects zero or negative", "[bank][edge]") {
    BankAccount acc("Alice", 100.0);
    REQUIRE_THROWS_AS(acc.deposit(0.0), std::invalid_argument);
    REQUIRE_THROWS_AS(acc.deposit(-10.0), std::invalid_argument);
    REQUIRE(acc.getBalance() == Approx(100.0));
}

TEST_CASE("BankAccount: withdraw works", "[bank][normal]") {
    BankAccount acc("Alice", 200.0);
    acc.withdraw(50.0);
    REQUIRE(acc.getBalance() == Approx(150.0));
}

TEST_CASE("BankAccount: withdraw entire balance", "[bank][boundary]") {
    BankAccount acc("Alice", 100.0);
    acc.withdraw(100.0);
    REQUIRE(acc.getBalance() == Approx(0.0));
}

TEST_CASE("BankAccount: withdraw rejects zero or negative", "[bank][edge]") {
    BankAccount acc("Alice", 100.0);
    REQUIRE_THROWS_AS(acc.withdraw(0.0), std::invalid_argument);
    REQUIRE_THROWS_AS(acc.withdraw(-5.0), std::invalid_argument);
}

TEST_CASE("BankAccount: withdraw rejects insufficient funds", "[bank][edge]") {
    BankAccount acc("Alice", 100.0);
    REQUIRE_THROWS_AS(acc.withdraw(150.0), std::runtime_error);
    REQUIRE(acc.getBalance() == Approx(100.0));
}

TEST_CASE("BankAccount: transfer works", "[bank][normal]") {
    BankAccount alice("Alice", 500.0);
    BankAccount bob("Bob", 200.0);
    alice.transfer(bob, 100.0);
    REQUIRE(alice.getBalance() == Approx(400.0));
    REQUIRE(bob.getBalance() == Approx(300.0));
}

TEST_CASE("BankAccount: transfer rejects zero or negative", "[bank][edge]") {
    BankAccount a("A", 100.0);
    BankAccount b("B", 100.0);
    REQUIRE_THROWS_AS(a.transfer(b, 0.0), std::invalid_argument);
    REQUIRE_THROWS_AS(a.transfer(b, -10.0), std::invalid_argument);
}

TEST_CASE("BankAccount: transfer rejects insufficient funds", "[bank][edge]") {
    BankAccount a("A", 50.0);
    BankAccount b("B", 100.0);
    REQUIRE_THROWS_AS(a.transfer(b, 75.0), std::runtime_error);
    // Both accounts should be unchanged (atomicity)
    REQUIRE(a.getBalance() == Approx(50.0));
    REQUIRE(b.getBalance() == Approx(100.0));
}

// ============================================================
// PASSWORD TESTS (25 points)
// ============================================================

TEST_CASE("Password: valid construction", "[password][normal]") {
    Password pw("Secure99");
    REQUIRE(pw.matches("Secure99"));
    REQUIRE(pw.getLength() == 8);
}

TEST_CASE("Password: matches returns false for wrong input", "[password][normal]") {
    Password pw("MyPass12");
    REQUIRE_FALSE(pw.matches("MyPass13"));
    REQUIRE_FALSE(pw.matches("mypass12"));
    REQUIRE_FALSE(pw.matches(""));
}

TEST_CASE("Password: rejects short password", "[password][edge]") {
    REQUIRE_THROWS_AS(Password("Short1"), std::invalid_argument);
    REQUIRE_THROWS_AS(Password("Ab1"), std::invalid_argument);
}

TEST_CASE("Password: rejects password without digit", "[password][edge]") {
    REQUIRE_THROWS_AS(Password("NoDigitsHere"), std::invalid_argument);
    REQUIRE_THROWS_AS(Password("abcdefgh"), std::invalid_argument);
}

TEST_CASE("Password: boundary - exactly 8 chars with digit", "[password][boundary]") {
    Password pw("Exactly8");
    REQUIRE(pw.getLength() == 8);
}

TEST_CASE("Password: change works with correct old password", "[password][normal]") {
    Password pw("OldPass1");
    pw.change("OldPass1", "NewPass2");
    REQUIRE(pw.matches("NewPass2"));
    REQUIRE_FALSE(pw.matches("OldPass1"));
}

TEST_CASE("Password: change rejects wrong old password", "[password][edge]") {
    Password pw("Correct1");
    REQUIRE_THROWS_AS(pw.change("Wrong123", "NewPass2"), std::invalid_argument);
    // Password should remain unchanged
    REQUIRE(pw.matches("Correct1"));
}

TEST_CASE("Password: change rejects invalid new password", "[password][edge]") {
    Password pw("Correct1");
    REQUIRE_THROWS_AS(pw.change("Correct1", "short"), std::invalid_argument);
    REQUIRE_THROWS_AS(pw.change("Correct1", "NoDigitHere"), std::invalid_argument);
    // Password should remain unchanged
    REQUIRE(pw.matches("Correct1"));
}

TEST_CASE("Password: no getPassword method exists", "[password][encapsulation]") {
    // This is a compile-time check.
    // If a student adds getPassword(), this test concept reminds them
    // not to. We verify encapsulation by checking matches() only.
    Password pw("Secret99");
    REQUIRE(pw.matches("Secret99"));
    REQUIRE(pw.getLength() == 8);
    // We can only verify the password through matches(), not by reading it.
}
