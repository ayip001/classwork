#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Student{
private: 
    static int sortKey;
    
    string lastName;
    string firstName;
    int totalPoints;
    
    static bool validString(string testStr);
    static bool validPoints(int testPoints);
    
public:
    static const int SORT_BY_FIRST = 88;
    static const int SORT_BY_LAST = 98;
    static const int SORT_BY_POINTS = 108;
    static const int DEFAULT_SORT_KEY = SORT_BY_LAST;
    
    static const string DEFAULT_NAME;
    static const int DEFAULT_POINTS = 0;
    static const int MAX_POINTS = 1000;
    
    Student(string lst = DEFAULT_NAME, string fst = DEFAULT_NAME,
        long pts = DEFAULT_POINTS);
    
    static int getSortKey(){return sortKey;}
    
    static bool setSortKey(int key);
    
    string getLastName(){return lastName;}
    string getFirstName(){return firstName;} 
    int getTotalPoints(){return totalPoints;}
    
    bool setLastName(string last);
    bool setFirstName(string first);
    bool setPoints(int pts);
    
    static int compareTwoStudents(Student firstStud, Student secondStud);
    string toString();
};

int Student::sortKey = Student::DEFAULT_SORT_KEY;

const string Student::DEFAULT_NAME = "zz-error";

class StudentArrayUtilities{
public:
    static string toString(string title, Student data[], int arraySize);
    static void arraySort(Student array[], int arraySize);
    static double getMedianDestructive(Student array[], int arraySize);

private:
    static bool floatLargestToTop(Student data[], int top);
    static void mySwap(Student &a, Student &b);
};

// public method prototypes
void display(string str);

int main(){
    Student oddClass[] = {  
        Student("Thomas", "Martinez", 94), Student("Larry", "Simmons", 122),
        Student("Brenda", "Morris", 194), Student("Daniel", "Ramirez", 147),
        Student("Michael", "Foster", 107), Student("Keith", "Phillips", 224),
        Student("Chris", "Flores", 43), Student("Harry", "Nelson", 451),
        Student("Gerald", "Lee", 294), Student("Ashley", "Powell", 320),
        Student("Ruth", "Gonzales", 224), Student("Donald", "Edwards", 43), 
        Student("Terry", "Parker", 451), Student("Shawn", "Richardson", 294), 
        Student("Jennifer", "Perez", 320)
    }; // JUST PRETEND SOMEONE'S FIRST NAME IS ACTUALLY MARTINEZ AND THOMAS IS
       // HIS LAST NAME IT'S 23:54 TOO LATE TO GO BACK
    
    Student evenClass[] = {  
        Student("Thomas", "Martinez", 94), Student("Larry", "Simmons", 122),
        Student("Brenda", "Morris", 194), Student("Daniel", "Ramirez", 147),
        Student("Michael", "Foster", 107), Student("Keith", "Phillips", 224),
        Student("Chris", "Flores", 43), Student("Harry", "Nelson", 451),
        Student("Gerald", "Lee", 294), Student("Ashley", "Powell", 320),
        Student("Ruth", "Gonzales", 224), Student("Donald", "Edwards", 43), 
        Student("Terry", "Parker", 451), Student("Shawn", "Richardson", 294), 
        Student("Jennifer", "Perez", 320), Student("Shawn", "Edwards", 100)
    };
    
    Student oneClass[] = {  
        Student("Thomas", "Martinez", 94)
    };

    int oddArraySize = sizeof(oddClass) / sizeof(oddClass[0]);
    int evenArraySize = sizeof(evenClass) / sizeof(evenClass[0]);
    int oneArraySize = sizeof(oneClass) / sizeof(oneClass[0]);
    
    display(StudentArrayUtilities::toString("Before: ", oddClass, 
        oddArraySize));
    StudentArrayUtilities::arraySort(oddClass, oddArraySize);
    display(StudentArrayUtilities::toString("\nAfter default sort: ", 
        oddClass, oddArraySize));
    Student::setSortKey(Student::SORT_BY_FIRST);
    display(StudentArrayUtilities::toString("\nAfter sort by first: ", 
        oddClass, oddArraySize));
    Student::setSortKey(Student::SORT_BY_POINTS);
    display(StudentArrayUtilities::toString("\nAfter sort by points: ", 
        oddClass, oddArraySize));
    Student::setSortKey(Student::SORT_BY_FIRST);
    display("\nMedian of oddClass = " + 
        to_string(StudentArrayUtilities::getMedianDestructive(oddClass, 
        oddArraySize)) + "\n");
    display("Sort by first key: " + to_string(Student::SORT_BY_FIRST) + "\n");
    display("Current sort key: " + to_string(Student::getSortKey()) + "\n");
    display("Median of evenClass = " + 
        to_string(StudentArrayUtilities::getMedianDestructive(evenClass, 
        evenArraySize)) + "\n");
    display("Median of oneClass = " + 
        to_string(StudentArrayUtilities::getMedianDestructive(oneClass, 
        oneArraySize)) + "\n");
    
}

// method definitions
void display(string str){
    cout << str;
}

// Student methods
bool Student::validString(string testStr){
    if(testStr.length() > 0 && isalpha(testStr[0]))
        return true;
    return false;
}

bool Student::validPoints(int testPoints){
    if(testPoints >= 0 && testPoints <= MAX_POINTS)
        return true;
    return false;
}

Student::Student( string last, string first, long points){
    if(!setLastName(last))
        lastName = DEFAULT_NAME;
    if(!setFirstName(first))
        firstName = DEFAULT_NAME;
    if(!setPoints(points))
        totalPoints = DEFAULT_POINTS;  
}

bool Student::setSortKey(int key){
    sortKey = key;
    return true;
}

bool Student::setLastName(string last){
    if(!validString(last))
        return false;
    lastName = last;
    return true;
}

bool Student::setFirstName(string first){
    if(!validString(first))
        return false;
    firstName = first;
    return true;
}

bool Student::setPoints(int pts){
    if(!validPoints(pts))
        return false;
    totalPoints = pts;
    return true;
}

// could be an instance method and, if so, would take one parameter
int Student::compareTwoStudents(Student firstStud, Student secondStud){
    int result;
    
    switch(getSortKey()){
        case SORT_BY_FIRST:
            result = firstStud.firstName.compare(secondStud.firstName);
            break;
        case SORT_BY_LAST:
            result = firstStud.lastName.compare(secondStud.lastName);
            break;
        case SORT_BY_POINTS:
            result = (firstStud.totalPoints > secondStud.totalPoints) ? 1 : -1;
            if(firstStud.totalPoints == secondStud.totalPoints)
                result = 0;
            break;
    }

    return result;
}

string Student::toString(){
    string resultString;
    ostringstream cnvrtFirst, cnvrtLast, cnvrtPoints;

    cnvrtFirst << firstName;
    cnvrtLast << lastName;
    cnvrtPoints << totalPoints;

    resultString = " " + cnvrtLast.str() 
        + ", " + cnvrtFirst.str()
        + " points: " + cnvrtPoints.str()
        + "\n";
    return resultString;
}


// StudentArrayUtilities methods
string StudentArrayUtilities::toString(string title, Student data[], 
    int arraySize){
    string output = "";

    cout << title << endl;

    // build the output string from the individual Students:
    for(int k = 0; k < arraySize; k++)
        output += " " + data[k].toString();
    return output;
}

void StudentArrayUtilities::arraySort(Student array[], int arraySize){
    for(int k = 0; k < arraySize; k++)
        // compare with method def to see where inner loop stops
        if(!floatLargestToTop(array, arraySize - 1 - k))
            return;
}

double StudentArrayUtilities::getMedianDestructive(Student array[], int 
    arraySize){
    int originalKey = Student::getSortKey();
    Student::setSortKey(Student::SORT_BY_POINTS);
    
    int median;
    
    StudentArrayUtilities::arraySort(array, arraySize);
    median = (arraySize % 2 == 1) ? array[(arraySize - 1) / 2].getTotalPoints()
        : (array[arraySize / 2].getTotalPoints() + 
        array[arraySize / 2 - 1].getTotalPoints()) / 2;
        
    Student::setSortKey(originalKey);
    
    return median;
}

// returns true if a modification was made to the array
bool StudentArrayUtilities::floatLargestToTop(Student data[], int top){
    bool changed = false;

    // compare with client call to see where the loop stops
    for(int k = 0; k < top; k++)
        if(Student::compareTwoStudents(data[k], data[k + 1]) > 0)
        {
            mySwap(data[k], data[k + 1]);
            changed = true;
        }
    return changed;
}

void StudentArrayUtilities::mySwap(Student &a, Student &b){
    Student temp("", "", 0);

    temp = a;
    a = b;
    b = temp;
}

/* ---------------------------- RUN -------------------------------------------

Before: 
  Thomas, Martinez points: 94
  Larry, Simmons points: 122
  Brenda, Morris points: 194
  Daniel, Ramirez points: 147
  Michael, Foster points: 107
  Keith, Phillips points: 224
  Chris, Flores points: 43
  Harry, Nelson points: 451
  Gerald, Lee points: 294
  Ashley, Powell points: 320
  Ruth, Gonzales points: 224
  Donald, Edwards points: 43
  Terry, Parker points: 451
  Shawn, Richardson points: 294
  Jennifer, Perez points: 320

After default sort: 
  Ashley, Powell points: 320
  Brenda, Morris points: 194
  Chris, Flores points: 43
  Daniel, Ramirez points: 147
  Donald, Edwards points: 43
  Gerald, Lee points: 294
  Harry, Nelson points: 451
  Jennifer, Perez points: 320
  Keith, Phillips points: 224
  Larry, Simmons points: 122
  Michael, Foster points: 107
  Ruth, Gonzales points: 224
  Shawn, Richardson points: 294
  Terry, Parker points: 451
  Thomas, Martinez points: 94

After sort by first: 
  Ashley, Powell points: 320
  Brenda, Morris points: 194
  Chris, Flores points: 43
  Daniel, Ramirez points: 147
  Donald, Edwards points: 43
  Gerald, Lee points: 294
  Harry, Nelson points: 451
  Jennifer, Perez points: 320
  Keith, Phillips points: 224
  Larry, Simmons points: 122
  Michael, Foster points: 107
  Ruth, Gonzales points: 224
  Shawn, Richardson points: 294
  Terry, Parker points: 451
  Thomas, Martinez points: 94

After sort by points: 
  Ashley, Powell points: 320
  Brenda, Morris points: 194
  Chris, Flores points: 43
  Daniel, Ramirez points: 147
  Donald, Edwards points: 43
  Gerald, Lee points: 294
  Harry, Nelson points: 451
  Jennifer, Perez points: 320
  Keith, Phillips points: 224
  Larry, Simmons points: 122
  Michael, Foster points: 107
  Ruth, Gonzales points: 224
  Shawn, Richardson points: 294
  Terry, Parker points: 451
  Thomas, Martinez points: 94

Median of oddClass = 224.000000
Sort by first key: 88
Current sort key: 88
Median of evenClass = 209.000000
Median of oneClass = 94.000000


Process exited with code: 0

---------------------------------------------------------------------------- */