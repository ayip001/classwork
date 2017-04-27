#include <iostream>
#include <string>
#include <math.h>
#include <sstream>

using namespace std;

// main client --------------------------------------------------------
int main(){
    // food #1 constants
    const string FOOD_1_NAME = "banana";
    const double FOOD_1_CALORIES_P100G = 88.89; // in calories
    const double FOOD_1_DIT_FIBER_P100G = 2.67; // in grams
    const double FOOD_1_SUGARS_P100G = 12.44; // in grams
    const double FOOD_1_PROTEIN_P100G = .89; // in grams
    
    // food #2 constants
    const string FOOD_2_NAME = "strawberry";
    const double FOOD_2_CALORIES_P100G = 31.93; // in calories
    const double FOOD_2_DIT_FIBER_P100G = 1.96; // in grams
    const double FOOD_2_SUGARS_P100G = 4.76; // in grams
    const double FOOD_2_PROTEIN_P100G = .56; // in grams
    
    // food #3 constants
    const string FOOD_3_NAME = "apple";
    const double FOOD_3_CALORIES_P100G = 48.15; // in calories
    const double FOOD_3_DIT_FIBER_P100G = 1.39; // in grams
    const double FOOD_3_SUGARS_P100G = 10.19; // in grams
    const double FOOD_3_PROTEIN_P100G = .46; // in grams
    
    // food #4 constants
    const string FOOD_4_NAME = "pineapple";
    const double FOOD_4_CALORIES_P100G = 49.94; // in calories
    const double FOOD_4_DIT_FIBER_P100G = 1.43; // in grams
    const double FOOD_4_SUGARS_P100G = 9.83; // in grams
    const double FOOD_4_PROTEIN_P100G = .55; // in grams
    
    // error message constants to increase legibility
    const string ERR_GRAMS = "---------- Error: Please enter a valid number "
        "of grams between 0 and 1000 ----------\nExiting...";
    const string ERR_SERVINGS = "---------- Error: Please enter a valid number"
        " of servings between 1 and 10 ----------\nExiting...";
    
    // create/initialize variables
    string recipeName, userInputStr;
    int userInputInt, servings;
    double totalProtein = 0, totalSugars = 0, totalDitFiber = 0, totalCals = 0;
    
    // print menu
    cout << "---------- List of Possible Ingredients ---------" << endl;
    cout << " Food #1: " << FOOD_1_NAME << endl;
    cout << " Food #2: " << FOOD_2_NAME << endl;
    cout << " Food #3: " << FOOD_3_NAME << endl;
    cout << " Food #4: " << FOOD_4_NAME << endl << endl;
    
    // name of recipe
    cout << "Name of recipe? ";
    getline(cin, userInputStr);
    recipeName = userInputStr;
    
    // servings
    cout << "# servings? ";
    getline(cin, userInputStr);
    // error check
    if(!(istringstream(userInputStr) >> userInputInt)){
        cout << ERR_SERVINGS;
        return 0;
    }
    if(userInputInt < 1 || userInputInt > 10){
        cout << ERR_SERVINGS;
        return 0;
    }
    servings = userInputInt;
    
    // food #1 ---------------------------------------------------------
    cout << "\n#grams of " << FOOD_1_NAME << "? ";
    getline(cin, userInputStr);
    // error check
    if(!(istringstream(userInputStr) >> userInputInt)){
        cout << ERR_GRAMS;
        return 0;
    }
    if(userInputInt < 0 || userInputInt > 1000){
        cout << ERR_GRAMS;
        return 0;
    }
    // update accumulators
    totalCals += userInputInt * (FOOD_1_CALORIES_P100G / 100);
    totalDitFiber += userInputInt * (FOOD_1_DIT_FIBER_P100G / 100);
    totalSugars += userInputInt * (FOOD_1_SUGARS_P100G / 100);
    totalProtein += userInputInt * (FOOD_1_PROTEIN_P100G / 100);
    
    // food #2 ---------------------------------------------------------
    cout << "\n#grams of " << FOOD_2_NAME << "? ";
    getline(cin, userInputStr);
    // error check
    if(!(istringstream(userInputStr) >> userInputInt)){
        cout << ERR_GRAMS;
        return 0;
    }
    if(userInputInt < 0 || userInputInt > 1000){
        cout << ERR_GRAMS;
        return 0;
    }
    // update accumulators
    totalCals += userInputInt * (FOOD_2_CALORIES_P100G / 100);
    totalDitFiber += userInputInt * (FOOD_2_DIT_FIBER_P100G / 100);
    totalSugars += userInputInt * (FOOD_2_SUGARS_P100G / 100);
    totalProtein += userInputInt * (FOOD_2_PROTEIN_P100G / 100);
    
    // food #3 ---------------------------------------------------------
    cout << "\n#grams of " << FOOD_3_NAME << "? ";
    getline(cin, userInputStr);
    // error check
    if(!(istringstream(userInputStr) >> userInputInt)){
        cout << ERR_GRAMS;
        return 0;
    }
    if(userInputInt < 0 || userInputInt > 1000){
        cout << ERR_GRAMS;
        return 0;
    }
    // update accumulators
    totalCals += userInputInt * (FOOD_3_CALORIES_P100G / 100);
    totalDitFiber += userInputInt * (FOOD_3_DIT_FIBER_P100G / 100);
    totalSugars += userInputInt * (FOOD_3_SUGARS_P100G / 100);
    totalProtein += userInputInt * (FOOD_3_PROTEIN_P100G / 100);
    
    // food #4 ---------------------------------------------------------
    cout << "\n#grams of " << FOOD_4_NAME << "? ";
    getline(cin, userInputStr);
    // error check
    if(!(istringstream(userInputStr) >> userInputInt)){
        cout << ERR_GRAMS;
        return 0;
    }
    if(userInputInt < 0 || userInputInt > 1000){
        cout << ERR_GRAMS;
        return 0;
    }
    // update accumulators
    totalCals += userInputInt * (FOOD_4_CALORIES_P100G / 100);
    totalDitFiber += userInputInt * (FOOD_4_DIT_FIBER_P100G / 100);
    totalSugars += userInputInt * (FOOD_4_SUGARS_P100G / 100);
    totalProtein += userInputInt * (FOOD_4_PROTEIN_P100G / 100);
    
    // final calculations
    totalCals /= servings;
    totalDitFiber /= servings;
    totalProtein /= servings;
    totalSugars /= servings;
    
    // report results --------------------------------------------------
    cout << "\nThe nutritional value per serving of " << recipeName << " is:\n";
    cout << " Calories: " << totalCals << endl;
    cout << " Dietary fiber in grams: " << totalDitFiber << endl;
    cout << " Sugars in grams: " << totalSugars << endl;
    cout << " Protein in grams: " << totalProtein << endl;
    
    return 0;
}

/* ----------------------------RUN 1-------------------------------------------

---------- List of Possible Ingredients ---------
 Food #1: banana
 Food #2: strawberry
 Food #3: apple
 Food #4: pineapple

Name of recipe? asdf
# servings? 0
---------- Error: Please enter a valid number of servings between 1 and 10 ----------
Exiting...

Process exited with code: 0

-----------------------------------------------------------------------------*/

/* ----------------------------RUN 2-------------------------------------------

---------- List of Possible Ingredients ---------
 Food #1: banana
 Food #2: strawberry
 Food #3: apple
 Food #4: pineapple

Name of recipe? qwer  
# servings? 5

#grams of banana? many
---------- Error: Please enter a valid number of grams between 0 and 1000 ----------
Exiting...

Process exited with code: 0

-----------------------------------------------------------------------------*/

/* ----------------------------RUN 3-------------------------------------------

---------- List of Possible Ingredients ---------
 Food #1: banana
 Food #2: strawberry
 Food #3: apple
 Food #4: pineapple

Name of recipe? literally just bananas
# servings? 8

#grams of banana? 0

#grams of strawberry? 600

#grams of apple? 500

#grams of pineapple? 400

The nutritional value per serving of literally just bananas is:
 Calories: 79.0112
 Dietary fiber in grams: 3.05375
 Sugars in grams: 14.8537
 Protein in grams: 0.9825


Process exited with code: 0

-----------------------------------------------------------------------------*/

/* ----------------------------RUN 4-------------------------------------------

---------- List of Possible Ingredients ---------
 Food #1: banana
 Food #2: strawberry
 Food #3: apple
 Food #4: pineapple

Name of recipe? ayy lmao
# servings? 10

#grams of banana? 1000

#grams of strawberry? 0

#grams of apple? 0

#grams of pineapple? 0

The nutritional value per serving of ayy lmao is:
 Calories: 88.89
 Dietary fiber in grams: 2.67
 Sugars in grams: 12.44
 Protein in grams: 0.89


Process exited with code: 0

-----------------------------------------------------------------------------*/

/* ----------------------------RUN 5-------------------------------------------

---------- List of Possible Ingredients ---------
 Food #1: banana
 Food #2: strawberry
 Food #3: apple
 Food #4: pineapple

Name of recipe? distilled water     
# servings? 1

#grams of banana? 189

#grams of strawberry? 543

#grams of apple? 999

#grams of pineapple? 7

The nutritional value per serving of distilled water is:
 Calories: 825.896
 Dietary fiber in grams: 29.6753
 Sugars in grams: 151.845
 Protein in grams: 9.3568


Process exited with code: 0

-----------------------------------------------------------------------------*/