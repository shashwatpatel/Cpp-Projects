#include <iostream>
#include <stdexcept>
#include <string>
#include "GroceryCheckout.h"

using namespace std;

bool GroceryInventory::AddItem(const string& name, int quantity,
							   float price, bool taxable)
{
	iterator = map.find(name); // Declaration of iterator that will go through data structure to find if the named item exists

	if (iterator != map.end()) // Condition to test if the item already exists
		return false;

	GroceryItem newItem(name, quantity, price, taxable); // Creates item if the item is non existent in the data structure
	map[name] = newItem;
	return true;
}

void GroceryInventory::CreateFromFile(const string& fileName)
{
    ifstream	file(fileName);
	string		name;
	float		price;
	int			quantity;
	bool		taxable;

	if (file.is_open())
	{
		while (true)
		{
			file >> name >> quantity >> price >> taxable;
			if (!file.fail())
			{
				AddItem(name, quantity, price, taxable);
			}
			else
			{
				break;
			}
         }
        file.close();
    }
	else
	{
        cout << "Could not open file " + fileName << endl;
    }

	return;
}

Receipt GroceryInventory::CreateReceipt(const string& fileName)
{
	ifstream file(fileName);
	Receipt r; //Object r
	r.subtotal_ = 0.0;
	r.taxAmount_ = 0.0;

	string name;

	while (file >> name) {
		GroceryItem* item = FindItem(name); //Get item
		item->quantity_--; //Decrease quantity if purchase is made
		r.subtotal_ += item->price_;
	//Check if the item is taxable and update the tax info
		if (item->taxable_) { r.taxAmount_ += item->price_ * tax; }
	//Add other data to the receipt, calculate the total and return receipt
		ReceiptItem anyItem(name, item->price_);
		r.item_.push_back(anyItem);
	}
	r.total_ = r.subtotal_ + r.taxAmount_;
	return r;
}

GroceryItem* GroceryInventory::FindItem(const string& name)
{
	iterator = map.find(name);

	if (iterator == map.end()) // The iterator returns the end of the map only if the item is not found
		return nullptr;
	return &iterator->second;

}

bool GroceryInventory::RemoveItem(const string& name)
{
	iterator = map.find(name);

	if (iterator == map.end()) // The iterator returns the end of the map only if the item is not found
		return false;

	else {
		map.erase(name);
		return true;
	}
}

void GroceryInventory::SetTaxRate(float taxRate) { tax = taxRate / 100; }//Setter to tax rate (.01)



size_t GroceryInventory::Size() { return map.size(); } //Returns the size of the map
