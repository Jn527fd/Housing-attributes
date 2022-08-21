//===============================================================
// housing.cpp
// YOUR HEADER HERE
//
// IMPORTATNT NOTE: Only write where the starter indicates YOUR CODE GOES HERE.
// Do not change anything unless comments tell you to do so, OR YOU MAY GET
// NO CREDIT ON THIS ASSIGNMENT
//
//===============================================================

#include <iostream>
#include <fstream>

using namespace std;

// DO NOT CHANGE THE FOLLOWING CONSTANTS. WHEN YOU SUBMIT,
// THEY MUST HAVE THESE VALUES AND THEY MUST BE USED
// AS THE DIMENSIONS FOR YOUR all_houses ARRAY.
const int ROWS = 50;
const int COLS = 20;

//===============================================================
//
//                             House
//
//     Each House struct records the information about one
//     house.  Three of the fields are declared for you and
//     you MUST use them as given.  You should declare below
//     them any additional members that you need.
//
//     Note that if the "no_house_here" member field is set
//     to true, then the other fields are not used.  Of course,
//     if no_house_here is false; then all the fields should
//     be set.
//
//===============================================================

struct House {
        bool   no_house_here;  // true if there is NO house on this location
        int    id;             // id from the data file, converted to int
        string lot_code;       // lot_code string from the data file

        // DO NOT CHANGE ANYTHING ABOVE THIS LINE
        // ===================================================
        float price; 
        int bedrooms;
        string color;
        string avl_or_bokd;

        // ===================================================

};


/*===============================================================
                   Required Function Prototypes

        DO NOT CHANGE ANYTHING IN THIS SECTION. YOUR CODE
        MUST ADHERE TO THESE FUNCTION DECLARATIONS OR YOU WILL
        RECEIVE NO CREDIT.
  ===============================================================*/

// - -  - - - - - - - - - - - - -  - - - - - - - - - - -
//   Functions operating on a single house
// - -  - - - - - - - - - - - - -  - - - - - - - - - - -
House read_one_house(ifstream& input_file);
void print_house(House h);

// - -  - - - - - - - - - - - - -  - - - - - - - - - - -
//   Functions relating to the array of houses
// - -  - - - - - - - - - - - - -  - - - - - - - - - - -
int col_from_lot(string lot);
int row_from_lot(string lot);
void fill_with_no_houses(int rows, int cols, House all_houses[ROWS][COLS]);
bool read_all_house_data(string filename, House all_houses[ROWS][COLS]);

// - -  - - - - - - - - - - - - -  - - - - - - - - - - -
//   Functions for week 2 (ignore during week 1)
// - -  - - - - - - - - - - - - -  - - - - - - - - - - -
bool is_available(int house_id, House all_houses[ROWS][COLS]);
int matching_houses(float max_price, string desired_color,
                       int desired_bedrooms, House all_houses[ROWS][COLS],
                       House results[ROWS * COLS]);
int num_neighbors(int house_id, House all_houses[ROWS][COLS]);
int rent_house(int house_id, House all_houses[ROWS][COLS]);


/*===============================================================
                   Additional Function Prototypes

        Write any additional function prototypes that you
        define here. You may not need any, or you may choose
        to write several
  ===============================================================*/
string query(void);
void run_command_loop(House all_houses[ROWS][COLS], 
        House results[ROWS * COLS]);
string id (int house_id, House all_houses[ROWS][COLS]);

//======================================================================
//                              main
//======================================================================

int main(int argc, char *argv[]) {
        
        // If you have function arguments that aren't used yet
        // the g++ compiler complains. The following lines are
        // harmless and they suppress the complaint. You can remove
        // the (void) lines and this comment once you start using
        // the arguments

        //   =======================================================
        
        // uses argv to use command line stated in termainal
        if (argc != 2) {
                cerr << "ERROR: You must provide the name of the file." 
                << endl;
                return 1;
        }
        
        string filename = argv[1];
        
        House all_houses[ROWS][COLS];
        House results[ROWS * COLS];
        
        string lot;
        
        int rows = row_from_lot(lot);
        int cols = col_from_lot(lot);
        
        fill_with_no_houses(rows, cols, all_houses);
        read_all_house_data(filename, all_houses);
        run_command_loop(all_houses, results);
        //   =======================================================
        return 0;
}

// - -  - - - - - - - - - - - - -  - - - - - - - - - - -
//   Functions operating on a single house
// - -  - - - - - - - - - - - - -  - - - - - - - - - - -

// read one line of the input_file; return corresponding House
House read_one_house(ifstream& input_file) {
        
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        House h;
       
        input_file >> h.id;
        input_file >> h.lot_code;
        input_file >> h.price;
        input_file >> h.bedrooms;
        input_file >> h.color;
        input_file >> h.avl_or_bokd;
       
       // h is set to false so that it identifies a house is in that array
        h.no_house_here = false;
        // ===================================================

        return h;
}

// print information about a single house
void print_house(House h) {
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        if (h.no_house_here == 1) {
                cout << "No house" << endl;
                
        } else if (h.avl_or_bokd == "available") {
                cout << "Id: " << h.id << " Lot: " << h.lot_code <<
                " Color: " << h.color << " Price: " << h.price << 
                " Bedrooms: " << h.bedrooms << " Available: Yes" << endl;
                
        } else if (h.avl_or_bokd == "booked") {
                cout << "Id: " << h.id << " Lot: " << h.lot_code <<
                " Color: " << h.color << " Price: " << h.price << 
                " Bedrooms: " << h.bedrooms << " Available: No" << endl;
                
        } else {
                cout << "No house" << endl;
        }
        // ===================================================
}

// - -  - - - - - - - - - - - - -  - - - - - - - - - - -
//   Functions relating to the array of houses
// - -  - - - - - - - - - - - - -  - - - - - - - - - - -

// given a lot code, return the column and row (respectively)
// in the all_houses array
int col_from_lot(string lot) {
        
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        int final_col_value;
        int count = 0;
        int column = 0;
        string integers_in_string;

        // establishes a count to see how many letters are in the given string
        for (unsigned int i = 0; i < lot.length(); i++) {
                if (isalpha (lot[i])) {
                        count++;
                }
        }
        
        // if the count is greater then zero the integer is taken in 
        // sent into a array and converted to a integer wherer A = 0 and so on
        if (count > 0) {
                for (unsigned int i = 0; i < lot.length (); i++){
                        if (isalpha (lot[i])) {
	                               integers_in_string += lot[i];
	               }
                }

                for (unsigned int i = 0; i < integers_in_string.length (); 
                i++) {
                        column = column * 10 + (integers_in_string[i] - '0');
                }

        } else {
                column = 0;
        }
        
        //subtracts 17 from the column to establish that A = 0;
        final_col_value = column - 17;
        // ===================================================

        return final_col_value;
}

int row_from_lot(string lot) {
        
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        
        // establishes variable to keep a account of how many digits are in 
        // the string and what that converts to in rows
        int final_row_value;
        int count = 0;
        int row = 0;
        string integers_in_string;

        // checks if there is digits in the string and count them 
        for (unsigned int i = 0; i < lot.size (); i++) {
                if (isdigit (lot[i])) {
                        count++;
                }
        }

        // takes the digits and buts then in a array and then adds the string 
        // into a small integer
        if (count > 0) {
                for (unsigned int i = 0; i < lot.length (); i++) {
                        if (isdigit (lot[i])) {   
                                integers_in_string += lot[i];
                        }
                }

                for (unsigned int i = 0; i < integers_in_string.length ();
                i++) {
                        row = row * 10 + (integers_in_string[i] - '0');
                }

        } else {
                row = 0;
        }
        
        // subtracts 1 to turn 1 to 0 as A1 is equal to 00
        final_row_value = row - 1;
        // ===================================================

        return final_row_value;
}

//  set the no_house_here marker for every position
//  in the array
void fill_with_no_houses(int rows, int cols, House all_houses[ROWS][COLS]) {
        
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        
        // goes through every array and sets them to true to prove that 
        // there is no house in that location
        for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                        
                        House no_houses;
                        
                        no_houses.no_house_here = true;
                    
                        all_houses[i][j] = no_houses;
                }
        } 
        // ===================================================
}

//  given a file with a count n at the top
//  read the count and then n lines of house data
//  into appropriate positions in the array
//
//   return true if file was successfully read
//          false if file could not be opened
bool read_all_house_data(string filename, House all_houses[ROWS][COLS]) {
        
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        
        // calls the file with the data and opens it
        // if the file can not open it sends a error, if it does then 
        // the houses are populated into in a array
        ifstream input_file;

        input_file.open(filename);

        if (not input_file.is_open()) {
                return false;     
                     
        } else {
                int num_house;
        
                input_file >> num_house;
        
                for (int i = 0; i < num_house; i++) {
                
                        House test_house = read_one_house  (input_file);
                
                        int test_col = col_from_lot(test_house.lot_code);
                
                        int test_row = row_from_lot(test_house.lot_code);
                
                        all_houses[test_row][test_col] = test_house;
                 
                }
        }
        
        input_file.close();
        // ===================================================

        return true;  
}


// - -  - - - - - - - - - - - - -  - - - - - - - - - - -
//   Functions for week 2 (ignore during week 1)
// - -  - - - - - - - - - - - - -  - - - - - - - - - - -

/*
 * Purpose:   to return true or false depending on if the house avaliable 
 *            or not
 * Arg:       house_id and 2D array "all_houses"
 * Returns:   bool false or true      
 */
bool is_available(int house_id, House all_houses[ROWS][COLS])
{
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        
        // goes through the populated array. and finds when a house is 
        //  avaliable or not by looking at avl_or_bokd and see if the 
        // string is either "booked" or " avaliable"
        for (int i = 0; i < COLS; i++ ) {
                for (int j = 0; j < ROWS; j++) {
                        if (all_houses[i][j].id == house_id) {
                                if (all_houses[i][j].avl_or_bokd == "booked") { 
                                        return false;
                                        
                                } else { 
                                        
                                        return true;
                                }
                        }
                }
        }
        
        // ===================================================
        return false; 
}

/*
 * Purpose:   to return a array full with houses that match given criteria by 
 *            user
 *            
 * Arg:       a max_price, color, number of bedrooms a array filled with 
 *            filled with given information and one empty to be popualted
 * Returns:   size of the array created      
 */
int matching_houses(float max_price, string desired_color,
                    int desired_bedrooms, House all_houses[ROWS][COLS],
                   House results[ROWS * COLS]) {
                           

        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        int size = 0; 
        
        //loops through the popluated array to find houses that match the 
        // max price color and bedrooms by the user and then populates 
        // a array with those house
        for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++ ) {
                        if (max_price >= all_houses[i][j].price) {
                                if (desired_color == all_houses[i][j].color) {
                                        if (desired_bedrooms <= 
                                            all_houses[i][j].bedrooms) {
                                                
                                                results[size] =
                                                all_houses[i][j];
                                                
                                                size ++;
                                        }
                                }
                        }
                }
        }
        // ===================================================
        return size;
}

/*
 * Purpose:   to return the number of neighbors accosicted with the house 
 *            chosen by finding which houses are booked around the chosen house 
 * Arg:       house id, all_houses 2D array
 * Returns:   number of neighbors accosicted with the house
 */
int num_neighbors(int house_id, House all_houses[ROWS][COLS]) {
        
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        int row_id = 0;
        int col_id = 0;
        int num_of_n = 0;
        
        string lot_id = id(house_id, all_houses);
        
        row_id = row_from_lot(lot_id);
        col_id = col_from_lot(lot_id);
        
        //loops through the given lot_id's and identifies if they are 
        // neightbors or not taking into account they only have to be 1
        // number around them
        for (int col_n = col_id - 1; col_n <= col_id + 1; col_n++){
                for(int row_n = row_id - 1; row_n <= row_id + 1; 
                        row_n++){
                        if (!((row_n < 0) || (row_n >= 50) || (col_n < 0) || 
                           (col_n >= 20) || (row_id == row_n
                           && col_id == col_n))){
                                if ((all_houses[row_n][col_n].no_house_here == 
                                false) && (all_houses[row_n][col_n].avl_or_bokd 
                                == "booked")) {
                                        num_of_n ++;
                                }
                        }
                }
        }
        // ===================================================
        return num_of_n; 
}

/*
 * Purpose:   to return a integer that indicates whether a house is avaliable 
 *            to be rented or not or if it does not exist
 *             
 * Arg:       house id, all_houses 2D array
 * Returns:   a number either 0,1,2
 */
int rent_house(int house_id, House all_houses[ROWS][COLS]) {
        
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        
        // loops through the all_houses array and chekc if there is a house 
        //  if so then checkes if its booked if not then the house is changed
        // to booked and rented, if already booked the user is given a 
        // certain message
        for (int j = 0; j < ROWS; j++) {
                for (int i = 0; i < COLS; i++) {
                        if (house_id == all_houses[j][i].id) {
                                if (all_houses[j][i].no_house_here == true){
                                        return 0;
                                
                                } else if (is_available(house_id, all_houses) 
                                           == true) {
                                                   
                                        all_houses[j][i].avl_or_bokd = 
                                        "booked";
                                        return 1;
                                
                                } else if ((all_houses[j][i].no_house_here 
                                        == false ) && (all_houses[j][i]
                                        .avl_or_bokd == "booked")) {
                                                
                                        return 2;
                                }
                        }
                }
        }
        // ===================================================
        return 0;
}

/*
 * Purpose:   to return the first entery given by the user
 * Arg:       action " the given letter by the user"
 * Returns:   a letter to the run command loop
 */
string query(void) {
        string action;
        cout << "query-> ";
        cin >> action;
        return action;
}

/*
 * Purpose:   to return the lot code that is accocated with with a house to 
 *            be used find other neighboring houses
 * Arg:       house id, all_houses 2D array
 * Returns:   the lot code of the house found through the given house id
 */
string id (int house_id, House all_houses[ROWS][COLS]) {
        int i = -1;
        int j = 0;
        
        while (all_houses[i][j].id != house_id) {
                i++;
                        while (all_houses[i][j].id != house_id) {
                                j++;
                        }       
        }
        
        return all_houses[i][j].lot_code;
}

/* run_command_loop(as a print/void function)
* Parameters: the query or action variabl and a 2D array
* Purpose:    to print out the the outcome depending on the aciton varaible 
*             given by the user in the beginnning, while keeping a interactive 
*              loop
* Effects:    Prints message with certain details depending on the query
*/
void run_command_loop(House all_houses[ROWS][COLS], 
                      House results[ROWS * COLS]){
        
        string action;
        int house_id;
        float max_price;        
        string desired_color;    
        int desired_bedrooms; 
        int size;
        
        do{
                action = query();
                
                if (action == "a") {
                        cin >> house_id;
                        
                        if (is_available(house_id, all_houses) == true) {
                                cout << "House " << house_id << " is available"
                                << endl;
                                
                        } else {
                                cout << "House " << house_id 
                                << " is not available" << endl;
                        }
                        
                } else if (action == "m") { 
                        cin >> max_price >> desired_color >> desired_bedrooms;
                        
                        size = matching_houses(max_price, desired_color, 
                        desired_bedrooms, all_houses, results);
                        
                        cout << "Matching Houses: " << endl;
                        
                        for (int i = 0; i < size; i++) {
                                print_house(results[i]);
                        }
                        
                
                } else if (action == "n") {
                        cin >> house_id;
                        int num_of_n = num_neighbors(house_id, all_houses);
                        
                        if ( num_of_n == 0) {
                                cout << " You have no neighbors, "
                                << "practice your drums!" << endl;
                        } else {
                                cout << "You have " << num_of_n 
                                << " neighbors!" << endl;
                        }
                
                } else if (action == "r") {
                        cin >> house_id;
                        int houses  = rent_house(house_id, all_houses);
                        
                        if (houses == 0) {
                                cout << "You can't rent a house that " 
                                << "doesnt exist, but good try" << endl;
                        
                        } else if (houses == 1) {
                                cout << "Congrats, you rented a house! "
                                << "Hope your door knobs don't" <<
                                " fall off" << endl;
                                
                        } else if (houses == 2) {
                                cout << "Too late..i hear the dumpster"
                                << " behind hill has some spaces "
                                << "open" << endl;
                        } else{
                                cout << "Unkown command " << action << endl;
                        }
                
                }
                        
        } while (action != "q");       
                
}

// ============================================================
//     INCLUDE CS11 TESTING CODE
//
//   LEAVE THIS STATEMENT IN PLACE. IT MUST COME
//   BE THE LAST LINE OF CODE IN YOUR housing.cpp FILE
// ============================================================

#include "housing_hooks.hpp"
