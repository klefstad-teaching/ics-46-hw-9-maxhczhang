#include "ladder.h"
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main()
{
    set<string> word_list;
    string dictionary_file = "words.txt";

    load_words(word_list, dictionary_file);

    string start_word;
    string end_word;

    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;

    if (start_word == end_word)
    {
        cout << "Error: Start and end words must be different." << endl;
        return 1;
    }
    if (word_list.find(end_word) == word_list.end())
    {
        cout << "Error: End word must be in the dictionary." << endl;
        return 1;
    }

    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(ladder);

    return 0;
}