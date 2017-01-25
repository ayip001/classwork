#include <iostream>
#include <sstream>

using namespace std;

int main(){
    
    const int REDEEM_COST = 10;
    const int REWARD = 1;
    const int PURCHASE_LIMIT_MAX = 100;
    
    string input;
    int purchaseQty, totalStamps = 0;
    bool valid;
    
    // main loop
    while(true){ // loops forever until 's' or alike is entered
        // menu and error check
        do{
            // menu
            cout << "Menu:\n    P (Process Purchase)\n    S (Shut down)\n\n"
                << "Your Choice: ";
            getline(cin, input);
            // check if input is valid
            if((input[0] == 'p' || input[0] == 'P') || (input[0] == 's' || 
            input[0] == 'S'))
                valid = true;
            else
                valid = false;
            // error message when input invalid and not empty
            if(!valid && input.length() > 0)
                cout << "\n  *** Please use P or S ***\n\n";
            
        }
        while(!valid);
        // main loop exit if input is s, i.e. shutting down
        if(input[0] == 's' || input[0] == 'S')
            break;
        // opt in check
        if(totalStamps >= REDEEM_COST){
            cout << "\nYou qualify for a free yogurt. Would you like to use "
                << "your credits? (Y or N) ";
            getline(cin, input);
            if(input[0] == 'y' || input[0] == 'Y'){
                totalStamps -= REDEEM_COST;
                
                cout << "\nYou have just used " << REDEEM_COST << " credits "
                    << "and have " << totalStamps << " left.\nEnjoy your free "
                    << "yogurt.\n\n";
                // goes to top of main loop if redeem
                continue;
            }
        }
        // normal purchase
        cout << "\nHow many yogurts would you like to buy? ";
        getline(cin, input);
        istringstream(input) >> purchaseQty;
        // out of range error check
        if(purchaseQty <= 0 || purchaseQty > PURCHASE_LIMIT_MAX){
            cout << "\n  *** Please enter a value between 1 and " 
                << PURCHASE_LIMIT_MAX << ". ***\n\n";
            continue;
        }
        
        totalStamps += purchaseQty * REWARD;
        
        cout << "\nYou just earned " 
            << purchaseQty * REWARD // storing this as a new var is excessive
            << " stamps and have a total of " << totalStamps << " to use.\n\n";
        
    }
    
    cout << "exiting...\n";
    return 0;
}

/* ---------------------------SAMPLE RUN-------------------------------------

Menu:
    P (Process Purchase)
    S (Shut down)

Your Choice: error check

  *** Please use P or S ***

Menu:
    P (Process Purchase)
    S (Shut down)

Your Choice: p 

How many yogurts would you like to buy? -1

  *** Please enter a value between 1 and 100. ***

Menu:
    P (Process Purchase)
    S (Shut down)

Your Choice: p

How many yogurts would you like to buy? 100

You just earned 100 stamps and have a total of 100 to use.

Menu:
    P (Process Purchase)
    S (Shut down)

Your Choice: p

You qualify for a free yogurt. Would you like to use your credits? (Y or N) n

How many yogurts would you like to buy? 101

  *** Please enter a value between 1 and 100. ***

Menu:
    P (Process Purchase)
    S (Shut down)

Your Choice: p

You qualify for a free yogurt. Would you like to use your credits? (Y or N) y

You have just used 10 credits and have 90 left.
Enjoy your free yogurt.

Menu:
    P (Process Purchase)
    S (Shut down)

Your Choice: s
exiting...


Process exited with code: 0

--------------------------END OF SAMPLE RUN------------------------------ */