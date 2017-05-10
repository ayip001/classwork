// Assignment 5 - Final
//
#include <iostream>
#include <string>
using namespace std;

// My taget string sentence: One apple a day keep the doctor AWAY.
// Setup methods prototypes
char getKeyCharacter();
string getSentence();
int numberOfCharacter(string sentence, int keyChar);
string replaceKeyChar(char keyCharacter, string sentence);
string removeKeyChar(char keyCharacter, string sentence);

int main()
{
	char keyChar;
	string sen;
	int numChar;
	string replaceKey;
	string newSen;
	string newSen1;
	// Call functions
	keyChar = getKeyCharacter();
	sen = getSentence();
	numChar = numberOfCharacter(sen, keyChar);
	cout << "\nNumber of characters: " << numChar << endl;
	newSen = replaceKeyChar(keyChar, sen);
	cout << "\nReplace Key Char: " << newSen << endl;
	newSen1 = removeKeyChar(keyChar, sen);
	cout << "\nRemove Key Chararacter: " << newSen1 << endl;
}

// Setup instruction asking to user to enter one-letter key character
char getKeyCharacter()
{
	string userIn;
	char keyCharacter;

	while (1)
	{
		cout << "Enter a SINGLE letter to act as key: " << userIn << endl;
		getline(cin, userIn);

		// If the user enter a single key character then it is true and continue
		// Otherwise, it is false and the program will be terminated.
		if (userIn.length() > 1)
			continue;
		else
		{
			keyCharacter = userIn[0];
			break;
		}
	}
	return keyCharacter;
}

// Setup instruction asking to user to enter one-sentence
string getSentence()
{
	string userIn;
	string Sentence;

	// Ask the user to enter a sentence of more than 4 letters
	while (1)
	{
		cout << "Enter a phrase or sentence bigger 4 letters: " << endl;
		getline(cin, userIn);

		if (userIn.length() < 4)
			continue;
		else
		{
			Sentence = userIn;
			break;
		}
	}
	return Sentence;
}

// Calculate the number of character in the given sentence
int numberOfCharacter(string sentence, int keyCharacter)
{
	int numberOfCharacter = 0;

	for (int i = 0; i < sentence.length(); i++) 
	{
		if (sentence[i] == keyCharacter)
			numberOfCharacter++;
	}
	return numberOfCharacter;
}

// Replace key character 'a' with a '-'
string replaceKeyChar(char keyCharacter, string sentence)
{
	string newSen = "";
	for (int i = 0; i < sentence.length(); i++)
	{
		if (sentence[i] == keyCharacter)
			newSen = newSen + "-";
		else
			newSen = newSen + sentence[i];
	}
		return newSen;
}

// Remove key character 'a'
string removeKeyChar(char keyCharacter, string sentence)
{
	string newSen1 = "";
	for (int i = 0; i < sentence.length(); i++)
	{
		if (sentence[i] == keyCharacter)
			newSen1 = newSen1 + "";
		else
			newSen1 = newSen1 + sentence[i];
	}
	return newSen1;
}