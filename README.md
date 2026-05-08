# Logic Gate Circuit Simulator

A C++ command-line tool that evaluates and compares Boolean logic circuits. Enter two circuits — an original and a simplified version — and the program generates truth tables, checks logical equivalence, finds satisfying inputs, and detects tautologies or unsatisfiable expressions.

---

## Features

- Supports **6 gate types**: AND, OR, NOT, NAND, NOR, XOR
- Accepts up to **3 inputs** (A, B, C) and up to **10 gates** per circuit
- Gates can chain — the output of one gate feeds into the next
- Generates a **full truth table** for both circuits
- Checks whether the two circuits are **logically equivalent**
- Lists all **satisfying input combinations** (where output = 1)
- Detects **tautologies** (always 1) and **unsatisfiable** circuits (always 0), and prompts you to fix them

---

## Gate Codes

| Code | Gate |
|------|------|
| 1    | AND  |
| 2    | OR   |
| 3    | NOT  |
| 4    | NAND |
| 5    | NOR  |
| 6    | XOR  |

---

## Input Format

### Inputs
- `0` = A, `1` = B, `2` = C
- `10` = output of Gate 0, `11` = output of Gate 1, and so on

### NOT Gate
Only takes one input (Input 1). Input 2 is skipped.

---

## Build & Run

```bash
g++ -o circuit_sim main.cpp
./circuit_sim
```

---

## Test Cases

### Test 1 — AND vs AND (Equivalent)

**Circuit:** A AND B

| Input | Gates | Type | In1 | In2 |
|-------|-------|------|-----|-----|
| Original   | 1 | AND (1) | 0 (A) | 1 (B) |
| Simplified | 1 | AND (1) | 0 (A) | 1 (B) |

**Expected output:**
```
A B C | F
0 0 0 | 0
0 0 1 | 0
0 1 0 | 0
0 1 1 | 0
1 0 0 | 0
1 0 1 | 0
1 1 0 | 1
1 1 1 | 1

Equivalence: YES

Satisfying inputs for ORIGINAL circuit:
  A=1 B=1 C=0
  A=1 B=1 C=1

  Original circuit is SATISFIABLE
```

---

### Test 2 — AND vs OR (Not Equivalent)

**Original:** A AND B  
**Simplified:** A OR B

| Circuit    | Gates | Type | In1 | In2 |
|------------|-------|------|-----|-----|
| Original   | 1 | AND (1) | 0 (A) | 1 (B) |
| Simplified | 1 | OR  (2) | 0 (A) | 1 (B) |

**Expected output:**
```
Equivalence: NO
```

---

### Test 3 — NOT Gate (single input)

**Circuit:** NOT A

| Circuit    | Gates | Type   | In1 | In2   |
|------------|-------|--------|-----|-------|
| Original   | 1 | NOT (3) | 0 (A) | (skipped) |
| Simplified | 1 | NOT (3) | 0 (A) | (skipped) |

**Expected output:**
```
A B C | F
0 0 0 | 1
0 0 1 | 1
0 1 0 | 1
0 1 1 | 1
1 0 0 | 0
1 0 1 | 0
1 1 0 | 0
1 1 1 | 0

Equivalence: YES
```

---

### Test 4 — Chained Gates (2-gate circuit)

**Circuit:** (A AND B) OR C

| Gate | Type     | In1       | In2  |
|------|----------|-----------|------|
| 0    | AND (1)  | 0 (A)     | 1 (B) |
| 1    | OR  (2)  | 10 (Gate 0) | 2 (C) |

Enter this as the **original** circuit (2 gates). Use the same for simplified.

**Expected output:**
```
A B C | F
0 0 0 | 0
0 0 1 | 1
0 1 0 | 0
0 1 1 | 1
1 0 0 | 0
1 0 1 | 1
1 1 0 | 1
1 1 1 | 1

Equivalence: YES

Satisfying inputs for ORIGINAL circuit:
  A=0 B=0 C=1
  A=0 B=1 C=1
  A=1 B=0 C=1
  A=1 B=1 C=0
  A=1 B=1 C=1
```

---

### Test 5 — Tautology Detection (triggers retry loop)

**Circuit:** A OR (NOT A) — always true

| Gate | Type    | In1   | In2       |
|------|---------|-------|-----------|
| 0    | NOT (3) | 0 (A) | (skipped) |
| 1    | OR  (2) | 0 (A) | 10 (Gate 0) |

**Expected output:**
```
A B C | F
0 0 0 | 1
0 0 1 | 1
...
1 1 1 | 1

  Original circuit is TAUTOLOGY (always 1)
Please change ONE gate and re-enter BOTH circuits.
```
The program will loop and prompt for re-entry.

---

### Test 6 — Unsatisfiable Detection (triggers retry loop)

**Circuit:** A AND (NOT A) — always false

| Gate | Type    | In1   | In2           |
|------|---------|-------|---------------|
| 0    | NOT (3) | 0 (A) | (skipped)     |
| 1    | AND (1) | 0 (A) | 10 (Gate 0)   |

**Expected output:**
```
  Original circuit is UNSATISFIABLE (always 0)
Please change ONE gate and re-enter BOTH circuits.
```

---

### Test 7 — XOR Gate

**Circuit:** A XOR B

| Circuit    | Gates | Type    | In1   | In2   |
|------------|-------|---------|-------|-------|
| Original   | 1 | XOR (6) | 0 (A) | 1 (B) |
| Simplified | 1 | XOR (6) | 0 (A) | 1 (B) |

**Expected output:**
```
A B C | F
0 0 0 | 0
0 0 1 | 0
0 1 0 | 1
0 1 1 | 1
1 0 0 | 1
1 0 1 | 1
1 1 0 | 0
1 1 1 | 0

Equivalence: YES

Satisfying inputs for ORIGINAL circuit:
  A=0 B=1 C=0
  A=0 B=1 C=1
  A=1 B=0 C=0
  A=1 B=0 C=1
```

---

### Test 8 — De Morgan's Law (NAND = NOT A OR NOT B)

**Original:** A NAND B (1 gate)  
**Simplified:** (NOT A) OR (NOT B) — 3 gates

| Gate | Type    | In1       | In2       |
|------|---------|-----------|-----------|
| 0    | NOT (3) | 0 (A)     | (skipped) |
| 1    | NOT (3) | 1 (B)     | (skipped) |
| 2    | OR  (2) | 10 (Gate 0) | 11 (Gate 1) |

**Expected output:**
```
Equivalence: YES
```

---

## Notes

- Only the **original** circuit triggers tautology/unsatisfiable detection. The simplified circuit is not checked.
- Gate outputs are accessed as `10 + gate_index` (e.g., Gate 0 → `10`, Gate 3 → `13`).
- Input C (index 2) is available but doesn't need to be used in every circuit.
