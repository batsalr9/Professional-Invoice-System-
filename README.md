
Invoice Management System README

Description:
This program is an Invoice Management System implemented in C++. It allows users to input details of items purchased, calculates the total amount including tax or VAT, displays the invoice, and saves recipient details to a file.

Features:

Input Details: Users can input the date of the invoice and details of items purchased, including item code, quantity, and unit price.
Display Invoice: The program displays the invoice with item details, quantity, unit price, total price, subtotal, tax or VAT amount, and grand total.
Save to File: Recipient details, including the date, item names, quantities, total prices, subtotal, and grand total, can be saved to a file named "recipients.txt".
Classes:

InvoiceItem: Represents an item in the invoice, including its ID, name, unit price, quantity, and total price.
ExtendedInvoiceItem: Inherits from InvoiceItem and adds a category property.
TotalAmountCalculator: Base class for calculating the total amount, with virtual functions for polymorphism.
TaxCalculator: Derived class for calculating tax, overrides the calculateTotal function.
VATCalculator: Derived class for calculating VAT, overrides the calculateTotal function.
Invoice: Represents an invoice, with functions for inputting details, displaying the invoice, saving recipient details, calculating the total amount, and setting the total amount calculator.
Usage:

Run the program.
Input the date and details of items purchased when prompted.
Choose whether to enter more items (y/n).
The program displays the invoice with the calculated totals.
Recipient details are saved to "recipients.txt".
Notes:

Ensure that the item codes entered by the user are valid (1 to 5).
The program uses a TaxCalculator by default. Modify the main function to use a VATCalculator if needed.
The maximum number of items per invoice is currently set to 10. Modify the code if more items are needed.
Author:
This program was created by Batsal Nath Shrestha.

Version:
1.0
