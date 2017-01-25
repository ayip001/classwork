#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

using namespace std;

// class prototype
class ITunes{
private:
    string name;
    string artist;
    int bitrate;
    int totalTime;
    
    // private helper methods
    static bool validString(string str);
    
public:
    static const int MIN_BITRATE;
    static const int MAX_BITRATE;
    static const int MIN_STR_LENGTH;
    static const int MAX_STR_LENGTH;
    static const int MIN_PLAY_TIME;
    static const int MAX_PLAY_TIME;
    static const int DEFAULT_BITRATE;
    static const int DEFAULT_PLAY_TIME;
    static const string DEFAULT_STRING;
    static const string ERROR_MESSAGE_BITRATE;
    static const string ERROR_MESSAGE_LENGTH;
    static const string ERROR_MESSAGE_PLAY_TIME;

    //constructors
    ITunes();
    ITunes(string Name, string Artist, int Bitrate, int TotalTime);
    
    // mutators and accessors
    bool setName(string Name);
    bool setArtist(string Artist);
    bool setBitrate(int Bitrate);
    bool setTotalTime(int TotalTime);
    string getName();
    string getArtist();
    int getBitrate();
    int getTotalTime();
    string toString();
    void setDefaults();
    void display();
    static void displayError(string errorMessage);
};

// initialize static members
const int ITunes::MIN_BITRATE = 64;
const int ITunes::MAX_BITRATE = 705;
const int ITunes::MIN_STR_LENGTH = 1;
const int ITunes::MAX_STR_LENGTH = 128;
const int ITunes::MIN_PLAY_TIME = 1000;
const int ITunes::MAX_PLAY_TIME = 1000 * 60 * 60;
const int ITunes::DEFAULT_BITRATE = 64;
const int ITunes::DEFAULT_PLAY_TIME = 1000;
const string ITunes::DEFAULT_STRING = "(undefined)";
const string ITunes::ERROR_MESSAGE_BITRATE = "bitrate of " + 
    to_string(MIN_BITRATE) + " to " + to_string(MAX_BITRATE) + " kbps.";
const string ITunes::ERROR_MESSAGE_LENGTH = "length of " + 
    to_string(MIN_STR_LENGTH) + " to " + to_string(MAX_STR_LENGTH) + 
    " charaters.";
const string ITunes::ERROR_MESSAGE_PLAY_TIME = "play time of " + 
    to_string(MIN_PLAY_TIME) + " to " + to_string(MAX_PLAY_TIME) + 
    " milliseconds.";

// main loop
int main(){
    // instantiate four ITunes objects and immediately display all objects
    ITunes track1 = ITunes();
    track1.display();
    
    ITunes track2 = ITunes("track 2", "Artist 2", 64, 1000);
    track2.display();
    
    ITunes track3 = ITunes("track 3", "Artist 3", 705, 1000 * 60 * 60);
    track3.display();
    
    ITunes track4 = ITunes("track 4", "", 300, 90);
    track4.display();
    
    // mutate one or more members of every object and display afterwards
    track1.setName("track 1 set");
    track1.setArtist("Artist 1 set");
    track1.setBitrate(100);
    track1.setTotalTime(1000);
    track1.display();
    
    track2.setName("track 2 set");
    track2.display();
    
    track3.setName("");
    track3.setArtist("");
    track3.setBitrate(30);
    track3.setTotalTime(300);
    track3.display();
    
    track4.setName("track 4 set");
    track4.setArtist("Artist 4 set");
    track4.setBitrate(0);
    track4.setTotalTime(0);
    track4.setBitrate(400);
    track4.setTotalTime(4000);
    track4.display();
    
    // reset all objects to their default values and display afterwards
    track1.setDefaults();
    track1.display();
    
    track2.setDefaults();
    track2.display();
    
    track3.setDefaults();
    track3.display();
    
    track4.setDefaults();
    track4.display();
    
    return 0;
}

// class methods definition
bool ITunes::validString(string str){
    return (str.length() >= MIN_STR_LENGTH && str.length() <= MAX_STR_LENGTH);
}

ITunes::ITunes(){
    setDefaults();
}

ITunes::ITunes(string Name, string Artist, int Bitrate, int TotalTime){
    setDefaults();
    setName(Name);
    setArtist(Artist);
    setBitrate(Bitrate);
    setTotalTime(TotalTime);
}

bool ITunes::setName(string Name){
    if(!validString(Name)){
        displayError(ERROR_MESSAGE_LENGTH);
        return false;
    }
    this->name = Name;
    return true;
}

bool ITunes::setArtist(string Artist){
    if(!validString(Artist)){
        displayError(ERROR_MESSAGE_LENGTH);
        return false;
    }
    this->artist = Artist;
    return true;
}

bool ITunes::setBitrate(int Bitrate){
    if(!(Bitrate >= MIN_BITRATE && Bitrate <= MAX_BITRATE)){
        displayError(ERROR_MESSAGE_BITRATE);
        return false;
    }
    this->bitrate = Bitrate;
    return true;
}

bool ITunes::setTotalTime(int TotalTime){
    if(!(TotalTime >= MIN_PLAY_TIME && TotalTime <= MAX_PLAY_TIME)){
        displayError(ERROR_MESSAGE_PLAY_TIME);
        return false;
    }
    this->totalTime = TotalTime;
    return true;
}

string ITunes::getName(){
    return name;
}

string ITunes::getArtist(){
    return artist;
}

int ITunes::getBitrate(){
    return bitrate;
}

int ITunes::getTotalTime(){
    return totalTime;
}

string ITunes::toString(){
    return "Title: " + name + " / Artist: " + artist + " / Playing Time: " +
        to_string(totalTime / DEFAULT_PLAY_TIME) + " second(s) / Bit rate: " + 
        to_string(bitrate) + "kbps";
}

void ITunes::setDefaults(){
    name = DEFAULT_STRING;
    artist = DEFAULT_STRING;
    bitrate = DEFAULT_BITRATE;
    totalTime = DEFAULT_PLAY_TIME;
}

void ITunes::display(){
    cout << toString() << endl;
}

void ITunes::displayError(string errorMessage){
    cout << "  Error: please enter a legal value for " << errorMessage << endl;
}

/* ---------------------------- RUN -------------------------------------------

Title: (undefined) / Artist: (undefined) / Playing Time: 1 second(s) / Bit rate: 64kbps
Title: track 2 / Artist: Artist 2 / Playing Time: 1 second(s) / Bit rate: 64kbps
Title: track 3 / Artist: Artist 3 / Playing Time: 3600 second(s) / Bit rate: 705kbps
  Error: please enter a legal value for length of 1 to 128 charaters.
  Error: please enter a legal value for play time of 1000 to 3600000 milliseconds.
Title: track 4 / Artist: (undefined) / Playing Time: 1 second(s) / Bit rate: 300kbps
Title: track 1 set / Artist: Artist 1 set / Playing Time: 1 second(s) / Bit rate: 100kbps
Title: track 2 set / Artist: Artist 2 / Playing Time: 1 second(s) / Bit rate: 64kbps
  Error: please enter a legal value for length of 1 to 128 charaters.
  Error: please enter a legal value for length of 1 to 128 charaters.
  Error: please enter a legal value for bitrate of 64 to 705 kbps.
  Error: please enter a legal value for play time of 1000 to 3600000 milliseconds.
Title: track 3 / Artist: Artist 3 / Playing Time: 3600 second(s) / Bit rate: 705kbps
  Error: please enter a legal value for bitrate of 64 to 705 kbps.
  Error: please enter a legal value for play time of 1000 to 3600000 milliseconds.
Title: track 4 set / Artist: Artist 4 set / Playing Time: 4 second(s) / Bit rate: 400kbps
Title: (undefined) / Artist: (undefined) / Playing Time: 1 second(s) / Bit rate: 64kbps
Title: (undefined) / Artist: (undefined) / Playing Time: 1 second(s) / Bit rate: 64kbps
Title: (undefined) / Artist: (undefined) / Playing Time: 1 second(s) / Bit rate: 64kbps
Title: (undefined) / Artist: (undefined) / Playing Time: 1 second(s) / Bit rate: 64kbps

---------------------------------------------------------------------------- */