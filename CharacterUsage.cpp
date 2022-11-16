#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

struct entry           //basic entry that holds the data and number of appearances of each item
{
    entry()
    {
        appearances = 1;
        word = "";
    }
    entry& operator=(const entry& e)
    {
        word = e.word;
        appearances = e.appearances;
        return *this;
    }
    string word;       //used if storing a word or num
    int appearances;   //number of appearances
};

void sort(vector<entry>& entries);
void mergeSort(vector<entry>& entries, vector<entry>& temp, int left, int right);
void merge(vector<entry>& entries, vector<entry>& temp, int leftPos, int rightPos, int rightEnd);

int main()
{
    //these vectors keep track of each word and the number of times it appears
    vector<entry> words;
    vector<entry> nums;
    vector<entry> letters;
    //keeps track of the current info
    char curLetter;
    string curNum;
    string curWord;

    while (!cin.eof())
    {
        //looks if end of number or end of word
        bool endNum = false;
        bool endWord = false;

        //keeps track of characters
        cin.get(curLetter);

        entry charEntry;
        charEntry.word = curLetter;
        letters.push_back(charEntry);

        if (curLetter >= 48 && curLetter <= 57)     //digit
        {
            curNum += curLetter;
            //pushesWord
            if (curWord.size())
                endWord = true;
        }
        else if (curLetter >= 65 && curLetter <= 90) //uppercase
        {
            curLetter += 32;                         //make lowercase
            curWord += curLetter;
            if (curNum.size())
                endNum = true;
        }
        else if (curLetter >= 97 && curLetter <= 122) //uppercase
        {
            curWord += curLetter;
            if (curNum.size())
                endNum = true;
        }
        //other characters
        else
        {
            if (curNum.size())
                endNum = true;
            if (curWord.size())
                endWord = true;
        }
        //push word and number if complete
        if (endWord)
        {
            entry wordEntry;
            wordEntry.word = curWord;
            words.push_back(wordEntry);
            curWord = "";

        }

        if (endNum)
        {
            entry numEntry;
            numEntry.word = curNum;
            nums.push_back(numEntry);
            curNum = "";
        }
    }
    //do the last word and num
    if (curNum.size())
    {
        entry numEntry;
        numEntry.word = curNum;
        nums.push_back(numEntry);
    }
    if (curWord.size())
    {
        entry wordEntry;
        wordEntry.word = curWord;
        words.push_back(wordEntry);
    }


    //sort the results
    if(letters.size() > 0)
        sort(letters);
    if(words.size()>0)
        sort(words);
    if(nums.size() > 0)
        sort(nums);

    int size = 10; //calculate the smount of results to display

    //print the results for characters
    cout << "Total" << letters.size() << " different characters, 10 most used characters:" << endl;
    if (letters.size() < 10)
        size = letters.size();
    for (int i = size - 1; i >= 0; i--)
    {
        if (letters[i].word == "\t")
            letters[i].word = "/t";
        if (letters[i].word == "\n")
            letters[i].word = "/n";
        cout << "No. " << size - i - 1 << ": " << letters[i].word << "\t\t" << letters[i].appearances << endl;
    }

    //print the list for words
    cout << "Total" << words.size() << " different words, 10 most used words:" << endl;
    if (words.size() < 10)
        size = words.size();
    else
        size = 10;
    if (size > 0)
    {
        for (int i = size - 1; i >= 0; i--)
        {
            cout << "No. " << size - i - 1 << ": " << words[i].word << "\t\t" << words[i].appearances << endl;
        }
    }


    //print the list for numbers
    cout << "Total" << nums.size() << " different numbers, 10 most used numbers:" << endl;
    if (nums.size() < 10)
        size = nums.size();
    else
        size = 10;
    if (size > 0)
    {
        for (int i = size - 1; i >= 0; i--)
        {
            cout << "No. " << size - i - 1 << ": " << nums[i].word << "\t\t" << nums[i].appearances << endl;
        }
    }
    
    return 0;
}

void sort(vector<entry>& entries)
{
    for (int i = 0; i < entries.size() - 1; i++)
    {
        string current = entries[i].word;
        //merge results where the chars are equal
        for (int j = i + 1; j < entries.size(); j++)
        {
            if (current == entries[j].word)
            {
                entries[i].appearances++;
                entries.erase(entries.begin() + j);
            }
        }
    }
    //merge sort the data
    vector<entry> temp(entries.size());
    mergeSort(entries, temp, 0, entries.size()-1);
}

//uses merge sort from textbook
void mergeSort(vector<entry>& entries, vector<entry>& temp, int left, int right)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        mergeSort(entries, temp, left, center);
        mergeSort(entries, temp, center + 1, right);
        merge(entries, temp, left, center + 1, right);
    }
}

void merge(vector<entry>& entries, vector<entry>& temp, int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;
    // Merging
    while (leftPos <= leftEnd && rightPos <= rightEnd)
        if (entries[leftPos].appearances <= entries[rightPos].appearances)
            temp[tmpPos++] = move(entries[leftPos++]);
        else
            temp[tmpPos++] = move(entries[rightPos++]);
    while (leftPos <= leftEnd)                              // Copy rest of first half
        temp[tmpPos++] = move(entries[leftPos++]);
    while (rightPos <= rightEnd)                            // Copy rest of right half
        temp[tmpPos++] = move(entries[rightPos++]);

    // Copy the temp array to the main array
    for (int i = 0; i < numElements; ++i, --rightEnd)
        entries[rightEnd] = move(temp[rightEnd]);
}
