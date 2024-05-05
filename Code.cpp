#include <iostream>
#include <fstream>  // Include the necessary header for file handling
using namespace std;

// Base class representing an item in the invoice and Encapsulation 
    class InvoiceItem {
    public:
        int id; 
        string name;
        double unitPrice;
        int quantity;
        double totalPrice;

        InvoiceItem() : id(0), unitPrice(0), quantity(0), totalPrice(0) {} ///used to avoid the use of uninitialized variables and ensures that the object starts with a known and consistent state and set the default values to 0 
    };

    // Derived class with additional functionality or properties
    class ExtendedInvoiceItem : public InvoiceItem {
    public://inheritance from invouceitems to extendedinvouceitems
        string category;
        ExtendedInvoiceItem() : category("") {} // Initialize category with an empty string
    };

    // Base class for calculating the total amount //inheritance 
    class TotalAmountCalculator {
    public:
        // Virtual function for polymorphism
        virtual double calculateTotal(double subtotal) const = 0;
        virtual ~TotalAmountCalculator() {}  // Virtual destructor for polymorphism
    };

    // Derived class for calculating tax
    class TaxCalculator : public TotalAmountCalculator { //inheritance 
    public:
        double calculateTotal(double subtotal) const override {
            // Apply tax rate (e.g., 10%)
            return subtotal * 1.10;
        }
    };                                                              //totalamountclaculator - tax calculator and vatcalculator

    // Derived class for calculating VAT 
    class VATCalculator : public TotalAmountCalculator { //inheritance 
    public:
        double calculateTotal(double subtotal) const override {
            // Apply VAT rate (e.g., 13%)
            return subtotal * 1.13;
        }
    };

    // Class representing an invoice
    class Invoice {
    private:
        string date;
        ExtendedInvoiceItem invoiceItems[10]; //inheritance
        int itemCount;
        TotalAmountCalculator* totalAmountCalculator;  // Pointer to the base class for polymorphism

    // Function to get the unit price based on the item code
        double getUnitPrice(int itemCode) {
            double price;
            switch (itemCode) {
                case 1: price = 100; break;
                case 2: price = 200; break;
                case 3: price = 300; break;
                case 4: price = 400; break;
                case 5: price = 500; break;
            }
            return price;
        }
    // Function to get the item name based on the item code
        string getItemName(int itemCode) {
            string name;
            switch (itemCode) {
                case 1: name = "Apple"; break;
                case 2: name = "Orange"; break;
                case 3: name = "Banana"; break;
                case 4: name = "Grapes"; break;
                case 5: name = "Watermelon"; break;
            }
            return name;
        }

    public:
        Invoice() : itemCount(0), totalAmountCalculator(nullptr) {}//created invoice object with itemcount with deafault value 0


        // Function to display available items and their prices
        void displayAvailableItems() {
            cout << "\n\n********* Here are the Item prices for your information********** \n\nItem code\tItem Name\tUnitPrice\n\n1\t\tApple\t\t100\n2\t\tOrange\t\t200\n3\t\tBanana\t\t300\n4\t\tGrapes\t\t400\n5\t\tWatermelon\t500\n";
        }

        // Function to input details of the invoice
        void inputDetails() {
            char more;
            cout << "Enter the date: ";
            cin >> date;

            do {
                displayAvailableItems();
                cout << "\n\nItem code: ";
                cin >> invoiceItems[itemCount].id;

                while (invoiceItems[itemCount].id > 5 || invoiceItems[itemCount].id < 1) { //while itemcode > 5 or 0 < code runs 
                    cout << "Invalid Item Code. Please enter a valid item code.\n";//if the item code is wrong 0 or more than 5
                    cout << "\n\nItem code: ";
                    cin >> invoiceItems[itemCount].id;
                }

                invoiceItems[itemCount].name = getItemName(invoiceItems[itemCount].id); //updating the name of the current item in the invoice by calling the getItemName function with the item code (id) of that item

                cout << "Quantity : ";//ask qualtity
                cin >> invoiceItems[itemCount].quantity;
                invoiceItems[itemCount].unitPrice = getUnitPrice(invoiceItems[itemCount].id);//input transferd to getuniteprice
                invoiceItems[itemCount].totalPrice = invoiceItems[itemCount].quantity * invoiceItems[itemCount].unitPrice;

                cout << "Do you have any other items to be entered next (y/n) ? ";
                cin >> more;//ask if they have more items to add or not

                itemCount++;
            } while (more == 'y');//countinue till unitil and unless it is not y
        }

        // Function to display the invoice
        void displayInvoice() { //inheritance
            cout << "\t\t\t\t*** Batsal Store *** \n";//store name
            cout << "Date   : " << date << endl;//date
            cout << "\n\n--------------------------------------------------------------------------------------------\n";
            cout << "Item Code\tItem Name\tQuantity\tUnit Price\tTotal Price\n";//headline
            cout << "--------------------------------------------------------------------------------------------\n";
            int total = 0;
            for (int k = 0; k < itemCount; k++) {
                cout << invoiceItems[k].id << "\t\t" << invoiceItems[k].name << "\t\t" << invoiceItems[k].quantity << "\t\t" << invoiceItems[k].unitPrice << "\t\t" << invoiceItems[k].totalPrice << "\n";
                total += invoiceItems[k].totalPrice;
            } //recipt
            cout << "--------------------------------------------------------------------------------------------\n";
            cout << "Subtotal\t\t" << total << "\n";

            double grandTotal = totalAmountCalculator->calculateTotal(total);
            cout << "VAT (13%)\t\t" << grandTotal - total << "\n";
            cout << "Grand Total\t\t" << grandTotal << "\n\n"; //total
        }

        // Function to save recipient details to a file
    // Function to save recipient details to a file
    void saveToRecipientsFile() {
        ofstream outFile("recipients.txt"); // Provide the file name with the .txt extension
        if (outFile.is_open()) {
            outFile << "Date: " << date << "\n";
            for (int k = 0; k < itemCount; k++)///it will save file until itemcount which we entered before is euqal to k
            {
                outFile << "Item: " << invoiceItems[k].name << "\tQuantity: " << invoiceItems[k].quantity << "\tTotal Price: " << invoiceItems[k].totalPrice << "\n";
                //to save it in file
            }
            outFile << "Subtotal: " << getTotal() << "\n";
            outFile << "Grand Total: " << totalAmountCalculator->calculateTotal(getTotal()) << "\n";
            outFile << "------------------------------------------\n";
            outFile.close();
            cout << "Recipient details saved to file.\n";
        } else {
            cout << "Unable to open file for writing.\n";
        }
    }

        // Function to calculate the total amount of the invoice
        double getTotal() const {
            int total = 0;
            for (int k = 0; k < itemCount; k++) {
                total += invoiceItems[k].totalPrice; //increments the total variable by the total price of the k-th item.
                //total cost of all items in the invoice and store it in the total variable, which is then displayed as the grand total in the invoice.
            }
            return total;
        }

        // Function to set the total amount calculator (tax or VAT)
        void setTotalAmountCalculator(TotalAmountCalculator* calculator) {
            totalAmountCalculator = calculator;
        }

        // Destructor to clean up memory
        ~Invoice() {
            delete totalAmountCalculator;
        }
    };

int main() {
    Invoice myInvoice;
    myInvoice.inputDetails();//ask user input such as date item code quantity 

    // Use TaxCalculator for tax or VATCalculator for VAT
    myInvoice.setTotalAmountCalculator(new TaxCalculator());

    myInvoice.displayInvoice();//display invoice

    myInvoice.saveToRecipientsFile();//save to file

    return 0;
}
