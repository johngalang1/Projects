 /*  PROGRAM: a4p2 - Grocery List Management Program
 *
 *  PURPOSE: the program builds a grocery list, sorted by item name,
 *           given a meal plan and an inventory of existing items.
 *
 *  DETAILS: The program processes a meal plan file which specifies the
 *           ingredients for a number of meals. These items are added to
 *           a grocery list that consist of item and quantity. Duplicate
 *           items result in the quantity being updated. An inventory file
 *           is then processed which consists of ingredients that are present.
 *           For each ingredient item if it is present on the grocery list
 *           results in either the quantity being reduced or the item being
 *           completely removed from the list.
 *           Once both files are processed the grocery list is written to a
 *           file.
 *
 *           The program allows the user to specify the name of each file.
 *
 *           All three files have the same format which is:
 *
 *                <item quantity><space><item name>
 *
 *           Blank lines are allowed in the input files and are ignored.
 *
 *****/


#include <iostream>
#include <fstream>
#include <cstring>
// 1
// #include "groclist.h"
#include "GroceryList.h"

using namespace std;


const int MAX_FILENAME_LEN = 30;

void open_input_file(ifstream &in, const char prompt[]);
// 2
//void process_meal_plan(ifstream &meal_plan, Grocery_Item_Ptr &head);
//void process_inventory(ifstream &inventory, Grocery_Item_Ptr &head);
void process_meal_plan(ifstream &meal_plan, GroceryList &list);
void process_inventory(ifstream &inventory, GroceryList &list);
void read_input_line(ifstream &in, int &quantity, char item[], bool &success);
void read_filename(const char prompt[], char str[]);

int main()
{
// 3
//  Grocery_Item_Ptr head = NULL;
  GroceryList list;

  char grocery_list_filename[MAX_FILENAME_LEN + 1];

  ifstream meal_plan;
  ifstream inventory;
  ofstream grocery_list;

  open_input_file(meal_plan, "enter ingredients file name  : ");
// 4
//  process_meal_plan(meal_plan, head);
  process_meal_plan(meal_plan, list);
  meal_plan.close();

  open_input_file(inventory, "enter inventory file name    : ");
// 5
//  process_inventory(inventory, head);
  process_inventory(inventory, list);
  inventory.close();

  read_filename("enter name of grocery list file to create   : ",
                grocery_list_filename);

  grocery_list.open(grocery_list_filename);
  if (grocery_list.fail())
  {
    cout << "unable to open " << grocery_list_filename
         << " grocery list not saved" << endl;
  }
  else
  {
// 6
//    write_list(head, grocery_list);
    list.write(grocery_list);
    grocery_list.close();

    cout << endl << "grocery list produced in file '"
         << grocery_list_filename
         << "'" << endl << endl;
  }
// 7
//  remove_all_items(head);

  return 0;
}


/*****
 *
 *  FUNCTION: open_input_file
 *
 *  PURPOSE:  reliably opens an input file of the user's choice.
 *
 *  INPUT:    prompt - the message which askes for the file name
 *
 *  OUTPUT:   in - the successfully opened input file
 *
 *  DETAILS:  the function forces the successful opening of
 *            the user specified file.
 *
 *****/

void open_input_file(ifstream &in, const char prompt[])
{
  char filename[MAX_FILENAME_LEN + 1];

  do
  {

    read_filename(prompt, filename);

    in.open(filename);

    if (in.fail())
      cout << "couldn't open file "
           << filename << endl;
  }
  while (in.fail());
}


/*****
 *
 *  FUNCTION: process_meal_plan
 *
 *  PURPOSE: to read each line in the meal plan file and build the
 *           corresponding sorted grocery list.
 *
 *  INPUT: meal_plan - the previously opened meal plan file
 *         head      - the grocery list (initially empty) to fill
 *
 *  OUTPUT: meal_plan - at EOF
 *          head      - the filled grocery list, sorted by item name with
 *                      no duplicates
 *
 *  DETAILS: each pair of items read is added to the list, which is maintained
 *           in alphabetical order. New items are inserted into the list,
 *           whereas duplicate items result in the quantity being updated.
 *
 *****/
// 8
//void process_meal_plan(ifstream &meal_plan, Grocery_Item_Ptr &head)
void process_meal_plan(ifstream &meal_plan, GroceryList &list)
{
  int quantity;
  bool success;
  char name[MAX_ITEM_NAME_LEN + 1];

  read_input_line(meal_plan, quantity, name, success);

  while (success)
  {
// 9
//    insert_item(head, quantity, name);
    if (list.contains(name))
      list.updateQuantity(name, quantity);
    else
      list.insertItem(name, quantity);

    read_input_line(meal_plan, quantity, name, success);
  }
}


/*****
 *
 *  FUNCTION: process_inventory
 *
 *  PURPOSE: to read each line in the inventory file and remove
 *           the corresponding items from the sorted grocery list.
 *
 *  INPUT: inventory - the previously opened inventory file
 *         head      - the grocery list with items to cross out
 *
 *  OUTPUT: inventory - at EOF
 *          head      - the updated grocery list, without the
 *                      inventory items
 *
 *  DETAILS: each pair of items read is removed from the list, with the
 *           alphabetical order beign maintained. The count of the item on
 *           the list is reduced by the inventory quantity. If the list quantity
 *           becomes less than or equal to 0 the item is removed from the list.
 *
 *****/

// 10
//void process_inventory(ifstream &inventory, Grocery_Item_Ptr &head)
void process_inventory(ifstream &inventory, GroceryList &list)
{
// 11
  int want;
  int quantity;
  char name[MAX_ITEM_NAME_LEN + 1];
  bool success;

  read_input_line(inventory, quantity, name, success);

  while (success)
  {
// 12
//    remove_item(head, quantity, name);
    if (list.contains(name))
    {
      want = list.getQuantity(name);
      if (want - quantity <= 0)
        list.removeItem(name);
      else
        list.updateQuantity(name, -1*quantity);
    }
    read_input_line(inventory, quantity, name, success);
  }
}


/*****
 *
 *  FUNCTION: read_input_line
 *
 *  PURPOSE: to read one item line (quantity + name) from the meal plan file.
 *
 *  INPUT: in - the previously opened meal plan file
 *
 *  OUTPUT: in       - the file position has been advanced
 *          quantity - the quantity of the item, if valid line was read
 *          name     - the name of the item, if valid line was read
 *          success  - indicates if the line was valid or not
 *
 *  DETAILS: Two item pairs, quantity and description are attempted to be
 *           read from the file. If a pair of items is read the success flag
 *           will be returned with a value of true; otherwise encountering the
 *           EOF will result in success being returned with a value of false.
 *           The two items are separated by a single space, which needs to be
 *           read and discarded.
 *
 *           The data is assumed to be valid as no error checking is done.
 *
 *****/

void read_input_line(ifstream &in, int &quantity, char name[], bool &success)
{
  char space;

  success = true;
  in >> quantity;
  if (in.eof())
    success = false;
  else
  {
    in.get(space);
    in.getline(name, MAX_ITEM_NAME_LEN + 1);
  }
}


/*****
 *
 *  FUNCTION: read_filename
 *
 *  PURPOSE:  reliably reads from the user a c-string representing a filename
 *
 *  INPUT:    prompt - the message which askes for the file name
 *
 *  OUTPUT:   str - a non-empty c-string
 *
 *  DETAILS:  the function forces the user to enter a non-empty c-string,
 *            representing a filename. The filename must also be less than
 *            or equal to the specified maximum for a filename.
 *
 *****/
void read_filename(const char prompt[], char str[])
{
  bool good_read = false;

  do {
    cout << prompt;
    cin.getline(str, MAX_FILENAME_LEN + 1);

    if (strlen(str) > 0)
      good_read = true;
    else
      cout << "The empty string is an invalid filename" << endl;
  } while (!good_read);

  return;
}
