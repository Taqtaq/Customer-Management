# Customer Management System

This is a simple console-based Customer Management System written in C.  
It allows you to add, view, modify, search, and delete customer records, as well as view customer payments based on usage.

## Features

- Add new customer records (name, phone number, usage in minutes)
- View all customer records
- Modify usage data for a customer
- View total bill for a customer
- Search customers by phone number
- Delete customer records
- Save and load data from a binary file (`customers.dat`)

## Usage

Run the program and choose from the menu options by entering the corresponding number:

1. Add New Record  
2. View List of Records  
3. Modify Record  
4. View Payment  
5. Search Record  
6. Delete Record  
7. Quit

When quitting, all data is saved automatically to `customers.dat` and loaded on program start.

## Requirements

- C compiler (e.g. `gcc`)
- Console environment

## How to compile

```bash
gcc -o customer_manager main.c
