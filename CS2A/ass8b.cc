#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <ctype.h>
#include <string>

using namespace std;

const int DISPLAY_PRECISION = 3;

class DateProfile{
private:
    char gender;
    char searchGender;
    double romance;
    double finance;
    string name;
    
    double determineGenderFit(DateProfile partner);
    double determineRomanceFit(DateProfile partner);
    double determineFinanceFit(DateProfile partner);
    
public:
    static const double MIN_ROMANCE;
    static const double MAX_ROMANCE;
    static const double MIN_FINANCE;
    static const double MAX_FINANCE;
    static const int PARAMETERS_COUNT;
    static const int MIN_NAME_LEN;
    static const int MAX_NAME_LEN;
    static const char DEFAULT_GEND;
    static const char DEFAULT_SEARCH_GEND;
    static const double DEFAULT_ROMANCE;
    static const double DEFAULT_FINANCE;
    static const string DEFAULT_NAME;
    
    DateProfile();
    DateProfile(char gender, char searchGender, double romance, double finance, 
        string name);
    
    bool setGender(char Gender);
    bool setSearchGender(char searchGender);
    bool setRomance(double romance);
    bool setFinance(double finance);
    bool setName(string name);
    char getGender();
    char getSearchGender();
    double getRomance();
    double getFinance();
    string getName();
    void setAll(char gender, char searchGender, double romance, double finance, 
        string name);
    void setDefaults();
    double fitValue(DateProfile partner);
};

const double DateProfile::MIN_ROMANCE = 1;
const double DateProfile::MAX_ROMANCE = 10;
const double DateProfile::MIN_FINANCE = 1;
const double DateProfile::MAX_FINANCE = 10;
const int DateProfile::PARAMETERS_COUNT = 2;
const int DateProfile::MIN_NAME_LEN = 1;
const int DateProfile::MAX_NAME_LEN = 30;
const char DateProfile::DEFAULT_GEND = 'M';
const char DateProfile::DEFAULT_SEARCH_GEND = 'F';
const double DateProfile::DEFAULT_ROMANCE = 1;
const double DateProfile::DEFAULT_FINANCE = 1;
const string DateProfile::DEFAULT_NAME = "John Doe";

void displayTwoProfiles(DateProfile profile1, DateProfile profile2);

int main(){
    DateProfile applicant1 = DateProfile();
    DateProfile applicant2 = DateProfile('f', 'M', 1.01, 1.01, "Jane Doe");
    DateProfile applicant3 = DateProfile('m', 'm', 8, 5, "Gaytsby");
    DateProfile applicant4 = DateProfile();
    applicant4.setAll('G', 'M', 2, 5, "Gayman Sachs");
    
    displayTwoProfiles(applicant1, applicant1);
    displayTwoProfiles(applicant1, applicant2);
    displayTwoProfiles(applicant1, applicant3);
    displayTwoProfiles(applicant1, applicant4);
    
    displayTwoProfiles(applicant2, applicant1);
    displayTwoProfiles(applicant2, applicant2);
    displayTwoProfiles(applicant2, applicant3);
    displayTwoProfiles(applicant2, applicant4);
    
    displayTwoProfiles(applicant3, applicant1);
    displayTwoProfiles(applicant3, applicant2);
    displayTwoProfiles(applicant3, applicant3);
    displayTwoProfiles(applicant3, applicant4);
    
    displayTwoProfiles(applicant4, applicant1);
    displayTwoProfiles(applicant4, applicant2);
    displayTwoProfiles(applicant4, applicant3);
    displayTwoProfiles(applicant4, applicant4);
    
    return 0;
}

double DateProfile::determineGenderFit(DateProfile partner){
    return (searchGender == partner.getGender() && 
        gender == partner.getSearchGender());
}

double DateProfile::determineRomanceFit(DateProfile partner){
    return 1 - abs(romance - partner.getRomance()) / (MAX_ROMANCE - MIN_ROMANCE);
}

double DateProfile::determineFinanceFit(DateProfile partner){
    return 1 - abs(finance - partner.getFinance()) / (MAX_FINANCE - MIN_FINANCE);
}

DateProfile::DateProfile(){
    setDefaults();
}

DateProfile::DateProfile(char gender, char searchGender, double romance, 
    double finance, string name){
    setDefaults();
    setGender(gender);
    setSearchGender(searchGender);
    setRomance(romance);
    setFinance(finance);
    setName(name);
}

bool DateProfile::setGender(char gender){
    if(!(toupper(gender) == 'M' || toupper(gender) == 'F'))
        return false;
    this->gender = toupper(gender);
    return true;
}

bool DateProfile::setSearchGender(char searchGender){
    if(!(toupper(searchGender) == 'M' || toupper(searchGender) == 'F'))
        return false;
    this->searchGender = toupper(searchGender);
    return true;
}

bool DateProfile::setRomance(double romance){
    if(!(romance >= MIN_ROMANCE && romance <= MAX_ROMANCE))
        return false;
    this->romance = romance;
    return true;
}

bool DateProfile::setFinance(double finance){
    if(!(finance >= MIN_FINANCE && finance <= MAX_FINANCE))
        return false;
    this->finance = finance;
    return true;
}

bool DateProfile::setName(string name){
    if(!(name.length() >= MIN_NAME_LEN && name.length() <= MAX_NAME_LEN))
        return false;
    this->name = name;
    return true;
}

char DateProfile::getGender(){
    return gender;
}

char DateProfile::getSearchGender(){
    return searchGender;
}

double DateProfile::getRomance(){
    return romance;
}

double DateProfile::getFinance(){
    return finance;
}

string DateProfile::getName(){
    return name;
}

void DateProfile::setAll(char gender, char searchGender, double romance, double
    finance, string name){
    setGender(gender);
    setSearchGender(searchGender);
    setRomance(romance);
    setFinance(finance);
    setName(name);
}

void DateProfile::setDefaults(){
    gender = DEFAULT_GEND;
    searchGender = DEFAULT_SEARCH_GEND;
    romance = DEFAULT_ROMANCE;
    finance = DEFAULT_FINANCE;
    name = DEFAULT_NAME;
}

double DateProfile::fitValue(DateProfile partner){
    if((int) determineGenderFit(partner))
        return (determineRomanceFit(partner) + determineFinanceFit(partner)) 
            / PARAMETERS_COUNT;
    return 0;
}

void displayTwoProfiles(DateProfile profile1, DateProfile profile2){
    cout << fixed << setprecision(DISPLAY_PRECISION);
    cout << "Person 1 Name: " << profile1.getName() << endl 
        << "Person 2 Name: " << profile2.getName() << endl
        << "Fit value (0 to 1): " << profile1.fitValue(profile2) << endl << endl;
}

/* ---------------------------------TEST RUN----------------------------------

Person 1 Name: John Doe
Person 2 Name: John Doe
Fit value (0 to 1): 0.000

Person 1 Name: John Doe
Person 2 Name: Jane Doe
Fit value (0 to 1): 0.999

Person 1 Name: John Doe
Person 2 Name: Gaytsby
Fit value (0 to 1): 0.000

Person 1 Name: John Doe
Person 2 Name: Gayman Sachs
Fit value (0 to 1): 0.000

Person 1 Name: Jane Doe
Person 2 Name: John Doe
Fit value (0 to 1): 0.999

Person 1 Name: Jane Doe
Person 2 Name: Jane Doe
Fit value (0 to 1): 0.000

Person 1 Name: Jane Doe
Person 2 Name: Gaytsby
Fit value (0 to 1): 0.000

Person 1 Name: Jane Doe
Person 2 Name: Gayman Sachs
Fit value (0 to 1): 0.000

Person 1 Name: Gaytsby
Person 2 Name: John Doe
Fit value (0 to 1): 0.000

Person 1 Name: Gaytsby
Person 2 Name: Jane Doe
Fit value (0 to 1): 0.000

Person 1 Name: Gaytsby
Person 2 Name: Gaytsby
Fit value (0 to 1): 1.000

Person 1 Name: Gaytsby
Person 2 Name: Gayman Sachs
Fit value (0 to 1): 0.667

Person 1 Name: Gayman Sachs
Person 2 Name: John Doe
Fit value (0 to 1): 0.000

Person 1 Name: Gayman Sachs
Person 2 Name: Jane Doe
Fit value (0 to 1): 0.000

Person 1 Name: Gayman Sachs
Person 2 Name: Gaytsby
Fit value (0 to 1): 0.667

Person 1 Name: Gayman Sachs
Person 2 Name: Gayman Sachs
Fit value (0 to 1): 1.000



Process exited with code: 0

--------------------------------------------------------------------------- */