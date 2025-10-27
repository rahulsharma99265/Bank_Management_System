# 🏦 Bank Management System

A Bank Management System project developed to enhance understanding of C++, Object-Oriented Programming (OOP) concepts, and file handling through a practical banking simulation.

## ✨ Features

* **Employee Section (Admin):**
    * Create new bank accounts (Savings or Current).
    * Modify existing account details (Name, Address, Business/Occupation).
    * Delete accounts.
    * View details of all account holders.
* **Customer Section:**
    * View individual account details.
    * Withdraw money (with balance check).
    * Deposit money.
    * Change account PIN.
* **Account Types:** Supports **Current (c)** and **Saving (s)** accounts with different minimum deposit requirements.
    * Current Account minimum deposit: **5000**.
    * Saving Account minimum deposit: **100**.
* **Authentication:** Separate login screens for **Employee** and **Customer**.
* **Data Persistence:** Account data is saved to a binary file named `account.dat`.

## 🛠️ Technology Used

* **Language:** C++
* **Libraries:** `iostream`, `cstring`, `fstream`, `conio.h` (primarily for `system("cls")` and `system("Pause")`, which may only work on Windows).
* **Data Storage:** Binary file handling (`fstream`).

## 🔑 Default Credentials

| User Type | ID/Account Number | Password/PIN |
| :---: | :---: | :---: |
| **Employee** | `RK@123` | `RK#123` |

Customers must use their created account number and 4-digit PIN.

## 🚀 Getting Started

### Prerequisites

You need a C++ compiler (like g++ or a compiler integrated into an IDE like Code::Blocks or Visual Studio) to build and run this project.

### Compilation and Execution

1.  **Save the code:** Save the provided C++ code as a file (e.g., `RKBANK.cpp`).
2.  **Compile:** Open your terminal or command prompt and compile the file using a C++ compiler.
    ```bash
    g++ RKBANK.cpp -o RKBANK
    ```
    *(Note: You may need to replace `conio.h` functions like `system("cls")` with platform-specific alternatives if compiling on Linux/macOS, or you might encounter compilation warnings/errors as `conio.h` is non-standard.)*
3.  **Run:** Execute the compiled file.
    ```bash
    ./RKBANK
    ```

## 📂 File Structure

The project primarily consists of a single C++ file:

| File | Description |
| :--- | :--- |
| `RKBANK.cpp` | Contains the `RKBANK` class definition and all application logic (main menu, employee/customer menus, and supporting functions). |
| `account.dat` | **(Generated during runtime)** A binary file used to store all account holder data. |

## 📝 Project Details

* **Class:** `RKBANK` - encapsulates all account-related data and methods.
* **File Handling:** Uses `fstream` for reading and writing objects directly to the binary file, ensuring data persists across application runs.
