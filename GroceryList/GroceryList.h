#ifndef GROCERYLIST_H
#define GROCERYLIST_H

#include "globals.h"

/*******************************************************************************
 *
 *  File name:  GroceryList.h
 *
 *  The "GroceryList" class represents a list of item and quantity for
 *  ingredients that need to be purchased.
 *
 *  PUBLIC METHOD SPECIFICATION:
 *
 *    contains:
 *       Input:   the name of an item
 *       Action:  the list will be searched for this item and if found true will
 *                be returned; otherwise false will be returned.
 *       Assumptions:  the input argument is a valid c-string
 *
 *       NOTES:
 *       1. this operation must be called prior to any of the other member functions
 *
 *    getQuantity:
 *       Input:   the name of an item
 *       Action:  the quantity of this item on the GroceryList will be returned
 *       Assumptions:  this method should only be called if the item is on the list.
 *                     If the item is not on the list the value returned is undefined.
 *
 *    updateQuantity:
 *       Input:   the name of the item and an integer value of the quantity
 *       Action:  the integer value can be positive or negative, and the method updates
 *                the quantity accordingly. If the item is not on the list the method has
 *                no effect
 *
 *    insertItem:
 *       Input:   a name and a integer quantity
 *       Action:  adds the name and quantity to the GroceryList maintaining the lists
 *                sorted order.
 *                Inserting a name already existing on the list will result in
 *                two versions of this name/quantity on the GroceryList.
 *       Assumptions:
 *       1. the name is a valid c-string
 *       2. the quantity is a positive integer value
 *
 *    removeItem:
 *       Input:   a name
 *       Action:  removes the given name / quantity item from the GroceryList
 *                maintaining the lists sorted order.
 *                The function returns true if the item is removed from the list;
 *                otherwise it returns false.
 *       Assumptions:
 *       1. the name is a valid c-string
 *
 *    write:
 *       Input:   an ostream
 *       Action:  displays the entire GroceryList to the specified stream in the
 *                format quantity name, with a single space between the quantity
 *                and name
 *       Assumptions:  the ostream is valid and open
 *
 ******************************************************************************/

class GroceryList
{
 public:
  GroceryList();
  ~GroceryList();
  bool contains (const NAME aName);
  int getQuantity (const NAME aName);
  void updateQuantity (const NAME aName, int quantity);
  void insertItem(const NAME aName, int quantity);
  bool removeItem(const NAME aName);
  void write(ostream &out);

 private:

  struct GroceryNode
  {
    GroceryNode *next;
    GroceryNode *prev;
    int quantity;
    NAME name;                   // NAME type declared in global.h
  };
  typedef GroceryNode *GroceryPtr;

  void search (const NAME aName, GroceryPtr &here, bool &found) const;

  GroceryNode head, tail; // dummy nodes

};



#endif
