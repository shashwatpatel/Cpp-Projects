#ifndef GroceryCheckout_h
#define GroceryCheckout_h

#include <fstream>
#include <map>
#include <vector>

using namespace std;

struct GroceryItem
{
	GroceryItem() { }
	GroceryItem(const string& name, int quantity, float price, bool taxable)
	: name_(name), quantity_(quantity), price_(price), taxable_(taxable) { }
	
	string	name_;
	int		quantity_;
	float	price_;
	bool	taxable_;
};

struct ReceiptItem
{
	ReceiptItem() { }
	ReceiptItem(const string& name, float price)
	: name_(name), price_(price) { }
	
	string	name_;
	float	price_;
};

struct	Receipt
{
	vector<ReceiptItem>	item_;
	float				subtotal_;
	float				taxAmount_;
	float				total_;
};

class GroceryInventory
{
	public:
		bool			AddItem(const string& name, int quantity,
								float price, bool taxable);
		void			CreateFromFile(const string& fileName);
		Receipt			CreateReceipt(const string& checkoutFile);
		GroceryItem*	FindItem(const string& name);
		bool			RemoveItem(const string& name);
		void			SetTaxRate(float taxRate);
		size_t			Size();

	private:
		std::map<string, GroceryItem> map; //Map holding the name and the key
		std::map<string, GroceryItem>::iterator iterator; 
		float tax;
		
};

#endif
