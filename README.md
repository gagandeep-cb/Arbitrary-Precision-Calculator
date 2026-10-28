# Arbitrary Precision Calculator (APC)

A high-performance **Arbitrary Precision Calculator** implemented in **C** using **Doubly Linked Lists (DLL)**. This calculator handles arithmetic operations on arbitrarily large signed integers—far exceeding the standard limits of 64-bit integer types (`long long int`).

---

## 📌 Project Overview

In standard C, primitive numeric data types overflow after 19–20 digits (`unsigned long long` max is $1.84 \times 10^{19}$). This project overcomes hardware limitations by dynamically allocating memory and representing large numbers digit-by-digit using a bidirectional **Doubly Linked List**.

### 🌟 Key Features
- **Arbitrary Length Arithmetic**: Compute numbers with hundreds or thousands of digits.
- **Full Signed Arithmetic**: Native support for positive and negative numbers (`+` and `-`).
  - Addition automatically applies the **greater-value sign rule** (e.g., `-1002 + +453 = -549`).
  - Multiplication & Division strictly respect sign rules (`+*- = -`, `-*- = +`, `-*+ = -`, `+*+ = +`).
  - No negative zero bug (`-0` is automatically normalized to `0`).
- **High-Performance Long Division**: Schoolbook digit-by-digit long division with $O(N)$ digit subtractions, making division instantaneous even for massive dividends.
- **Grade-School Multiplication**: Shifts partial products with zero padding and accumulates results.
- **Robust CLA Validation**: Strict command-line argument validation verifying operand formats, operator validity, and preventing division by zero.
- **Clean Memory Management**: Complete dynamic allocation lifecycle (`malloc`/`free`) with zero memory leaks.

---

## 🏗️ Data Structure & Architecture

Each digit of a number is stored as a single node in a **Doubly Linked List**:

```
      +------+      +------+      +------+
NULL <| prev |<---->| prev |<---->| prev |
      | data |      | data |      | data |
      | next |<---->| next |<---->| next |> NULL
      +------+      +------+      +------+
       (Head/MSB)                  (Tail/LSB)
```

- **Head**: Points to the Most Significant Digit (MSB).
- **Tail**: Points to the Least Significant Digit (LSB).
- **Bidirectional Traversal**: Enables efficient right-to-left addition and subtraction (LSB to MSB) with natural carry and borrow propagation using `prev` pointers.

---

## 📂 File Structure

```text
├── apc.h         # Header: Struct definitions, status macros, and function prototypes
├── main.c        # Main driver: CLA parsing, sign extraction, operator dispatch, cleanup
├── apc.c         # Core utilities: CLA validation, DLL node operations, list comparison
├── add.c         # Addition algorithm with carry propagation
├── sub.c         # Subtraction algorithm with borrow propagation & tail tracking
├── mul.c         # Grade-school multiplication with position shifts & running sum
├── div.c         # High-speed long division algorithm
├── Makefile      # Build automation script
└── .gitignore    # Ignores intermediate object files (.o) and executables
```

---

## ⚙️ Compilation & Build

### In Linux / WSL / macOS:
```bash
# Build the project
make

# Clean object files and binaries
make clean
```

### In Windows (MinGW / GCC):
```powershell
gcc -Wall -Wextra main.c apc.c add.c sub.c mul.c div.c -o apc.exe
```

---

## 🚀 Usage & Examples

Run the compiled executable by passing three command-line arguments:
```bash
./a.out <operand1> <operator> <operand2>
```

Supported operators:
* `+` : Addition
* `-` : Subtraction
* `x`, `X`, `'*'` : Multiplication *(Note: in bash, quote `'*'` or use `x` to avoid wildcard file expansion)*
* `/` : Division

### Example Commands:

#### 1. Addition (with greater magnitude negative sign)
```bash
./a.out -1002 + +453
# Result: -549
```

#### 2. Subtraction
```bash
./a.out +453 - +1002
# Result: -549

./a.out -1002 - -453
# Result: -549
```

#### 3. Multiplication (Signed Matrix)
```bash
./a.out +1002 x -453
# Result: -453906

./a.out -1002 x -453
# Result: 453906
```

#### 4. Long Division
```bash
./a.out -1002 / +453
# Result: -2

./a.out 1000000000000000000000 / 2
# Result: 500000000000000000000
```

#### 5. Arbitrary Precision Numbers (20+ Digits)
```bash
./a.out 12345678901234567890 + 98765432109876543210
# Result: 111111111011111111100
```

#### 6. Error & Safety Checks
```bash
./a.out 12345 / 0
# Error: Division by zero is not allowed.

./a.out 12a3 + 456
# Error: Operand 1 contains non-digit character 'a'.
```

---

## 🧪 Algorithms Implemented

1. **Addition (`add.c`)**:  
   Traverses backwards from tail to head. At each node, computes `sum = digit1 + digit2 + carry`. Computes `carry = sum / 10` and `digit = sum % 10`, then inserts the digit at the front of the result list.

2. **Subtraction (`sub.c`)**:  
   Traverses backwards from tail to head. If `digit1 < digit2`, borrows 10 from the next higher position (`borrow = 1`), and subtracts. Leading zeros in the result are safely trimmed.

3. **Multiplication (`mul.c`)**:  
   For each digit in operand 2, multiplies across all digits of operand 1, attaches shifting zeros, and accumulates the intermediate products using `addition()`.

4. **Division (`div.c`)**:  
   Iterates through the digits of the dividend, pulling digits one-by-one into a working buffer. Counts how many times the divisor fits into the buffer via repeated subtraction (at most 9 subtractions per digit). Appends the single-digit quotient to the result list.

---

