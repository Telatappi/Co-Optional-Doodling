#include "Inventory.h"

core::Inventory::Inventory()
{
}

core::Inventory::~Inventory()
{
}

void core::Inventory::Equip(std::string _itemName, std::string _slotName)
{
	std::vector<Item>::iterator item = m_items.begin();
	for (; item != m_items.end(); ++item)
	{
		if ((*item).GetName() == _itemName)
		{
			//if slot is not specified
			//use mHand for weapon oHand for Shield
			//and default to misc1
			if (_slotName == "")
			{				
				if ((*item).GetType() == "weapon")
				{
					m_items.push_back(m_slots.mHand);
					m_slots.mHand = (*item);
					m_items.erase(item);
					break;
				}
				else if ((*item).GetType() == "shield")
				{
					m_items.push_back(m_slots.oHand);
					m_slots.oHand = (*item);
					m_items.erase(item);
					break;
				}
				else if ((*item).GetType() == "misc")
				{
					m_items.push_back(m_slots.misc1);
					m_slots.misc1 = (*item);
					m_items.erase(item);
					break;
				}
			}
			else
			{
				if (_slotName == "helmet")
				{
					m_items.push_back(m_slots.helmet);
					m_slots.helmet = (*item);
					m_items.erase(item);
					break;
				}
				else if (_slotName == "armor")
				{
					m_items.push_back(m_slots.armor);
					m_slots.armor = (*item);
					m_items.erase(item);
					break;
				}
				else if (_slotName == "mHand")
				{
					m_items.push_back(m_slots.mHand);
					m_slots.mHand = (*item);
					m_items.erase(item);
					break;
				}
				else if (_slotName == "oHand")
				{
					m_items.push_back(m_slots.oHand);
					m_slots.oHand = (*item);
					m_items.erase(item);
					break;
				}
				else if (_slotName == "misc1")
				{
					m_items.push_back(m_slots.misc1);
					m_slots.misc1 = (*item);
					m_items.erase(item);
					break;
				}
				else if (_slotName == "misc2")
				{
					m_items.push_back(m_slots.misc2);
					m_slots.misc2 = (*item);
					m_items.erase(item);
					break;
				}
			}
		}
	}
}

std::vector<Item> core::Inventory::GetItems()
{
	return m_items;
}