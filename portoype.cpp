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
// bool is_available(int house_id, House all_houses[ROWS][COLS]);
/* int matching_houses(float max_price, string desired_color,
                       int desired_bedrooms, House all_houses[ROWS][COLS],
                       House results[ROWS * COLS]); */
// int num_neighbors(int house_id, House all_houses[ROWS][COLS]);
// int rent_house(int house_id, House all_houses[ROWS][COLS]);


/*===============================================================
                   Additional Function Prototypes

        Write any additional function prototypes that you
        define here. You may not need any, or you may choose
        to write several
  ===============================================================*/

// YOUR FUNCTION PROTOTYPES HERE



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
        
        if (argc != 2) {
                cerr << "ERROR: You must provide the name of the file." 
                << endl;
                return 1;
        }

        string filename = argv[1];
         
        while (true ) {
                
                int row;
                cout << "Enter row: ";
                cin >> row;

                if (row < 0) break;

                int col;
                cout << "Enter col: ";
                cin >> col;
            
                string lot = "A2";
                
                int rows = row_from_lot(lot);
                
                int cols = col_from_lot(lot);

                House all_houses[ROWS][COLS];

                fill_with_no_houses(rows, cols, all_houses);
                
                read_all_house_data(filename, all_houses);

                print_house(all_houses[col][row]);
        }
        
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
                
        } else if(h.avl_or_bokd == "available") {
                cout << "Id: " << h.id << " Lot: " << h.lot_code <<
                " Color: " << h.color << " Price: " << h.price << 
                " Bedrooms: " << h.bedrooms << " Avaliable: Yes" << endl;
                
        } else if(h.avl_or_bokd == "booked") {
               cout << "Id: " << h.id << " Lot: " << h.lot_code <<
                " Color: " << h.color << " Price: " << h.price << 
               " Bedrooms: " << h.bedrooms << " Avaliable: No" << endl;
                
        } else {
                
              cout << "No house" << endl;
        }
     
        // ===================================================
}

int col_from_lot(string lot) {
        
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        
        int final_col_value;
        int count = 0;
        int column = 0;
        string integers_in_string;

        for (unsigned int i = 0; i < lot.length(); i++) {
                if (isalpha (lot[i])) {
                        count++;
	        }
        }

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

        final_col_value = column - 17;

        // ===================================================

        return final_col_value;
}

int row_from_lot(string lot) {
        
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        
        int final_row_value;
        int count = 0;
        int row = 0;
        string integers_in_string;

        for (unsigned int i = 0; i < lot.size (); i++) {
                if (isdigit (lot[i])) {
                        count++;
                }
        }

  
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

        final_row_value = row - 1;

        // ===================================================

        return final_row_value;
}   

void fill_with_no_houses(int rows, int cols, House all_houses[ROWS][COLS]) {
        
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        
        for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                        
                        House no_houses;
                        
                        no_houses.no_house_here = true;
                    
                        all_houses[i][j] = no_houses;
                }
        } 
        
        // ===================================================
        
}

bool read_all_house_data(string filename, House all_houses[ROWS][COLS]) {
        
        // DO NOT CHANGE THE LINE IMMEDIATELY ABOVE
        // ===================================================
        
        ifstream input_file;

        input_file.open(filename);

        if (not input_file.is_open()) {
                cerr << "fileread.cpp: could not open file: "
                << filename << endl;
                return 1;      
                     
        } else {
                int num_house;
        
                input_file >> num_house;
        
                for (int i = 0; i < num_house; i++) {
                
                        House test_house = read_one_house  (input_file);
                
                        int test_col = col_from_lot(test_house.lot_code);
                
                        int test_row = row_from_lot(test_house.lot_code);
                
                        all_houses[test_col][test_row] = test_house;
                 
                }
        }
        
        input_file.close();
        
        // ===================================================

        return true;  
}