#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <vector>
#include <string>

class Item;

namespace core
{
	struct Slots
	{
		Item helmet;
		Item armor;
		Item mHand;
		Item oHand;
		Item misc1;
		Item misc2;
	};

	class Inventory
	{
	public:
		Inventory();
		~Inventory();
		void Equip(std::string itemName, std::string slotName = "");
		std::vector<Item> GetItems();
	private:
		Slots m_slots;
		std::vector<Item> m_items;
	};
}
#endif