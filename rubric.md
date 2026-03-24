# Grading Rubric — Encapsulation and Invariants Lab

**Course:** CMP1002  
**Total:** 100 points

---

## Temperature Class (30 points)

| Test | Points | Description |
|------|--------|-------------|
| Constructor + getCelsius | 5 | Object created with valid value; getter returns it |
| getFahrenheit conversion | 5 | Correct formula: C × 9/5 + 32 |
| setCelsius works | 5 | Updates value; both getters reflect change |
| Absolute zero boundary | 5 | -273.15 is accepted (boundary case) |
| Constructor rejects invalid | 5 | Throws `invalid_argument` for values < -273.15 |
| setCelsius rejects invalid | 5 | Throws `invalid_argument`; state unchanged after failure |

## BankAccount Class (45 points)

| Test | Points | Description |
|------|--------|-------------|
| Constructor + getters | 5 | Owner and balance correctly stored and returned |
| Zero initial balance | 3 | Balance of 0.0 is allowed |
| Rejects empty owner | 4 | Throws `invalid_argument` for empty string |
| Rejects negative balance | 4 | Throws `invalid_argument` for negative initial balance |
| Deposit works | 4 | Balance increases correctly |
| Deposit rejects invalid | 4 | Throws for zero and negative amounts; balance unchanged |
| Withdraw works | 4 | Balance decreases correctly |
| Withdraw entire balance | 3 | Withdrawing exact balance leaves 0 |
| Withdraw rejects invalid | 4 | Throws for zero, negative, and overdrawn amounts |
| Transfer works | 5 | Both accounts updated correctly |
| Transfer rejects invalid | 5 | Throws for invalid amounts; both accounts unchanged |

## Password Class (25 points)

| Test | Points | Description |
|------|--------|-------------|
| Valid construction + matches | 4 | Password created; `matches()` returns true for correct input |
| matches returns false | 3 | Wrong input, wrong case, empty string all return false |
| Rejects short password | 4 | Throws `invalid_argument` for length < 8 |
| Rejects no-digit password | 4 | Throws `invalid_argument` for password without digits |
| Boundary: exactly 8 chars | 2 | 8-char password with digit is accepted |
| Change with correct old | 3 | New password works; old no longer matches |
| Change rejects wrong old | 3 | Throws; password unchanged |
| Change rejects invalid new | 2 | Throws for short or digit-less new password; original unchanged |

---

## Summary

| Section | Points |
|---------|--------|
| Temperature | 30 |
| BankAccount | 45 |
| Password | 25 |
| **Total** | **100** |
