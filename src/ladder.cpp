#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <unordered_set>

using namespace std;

void error(string word1, string word2, string msg)
{
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d)
{
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > d) return false;

    int diff = 0;
    int i = 0;
    int j = 0;

    while (i < len1 && j < len2)
    {
        if (str1[i] != str2[j])
        {
            if (++diff > d) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++, j++; }
        }
        else
        {
            i++;
            j++;
        }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

void load_words(set<string>& word_list, const string& file_name)
{
    ifstream file(file_name);
    if (!file)
    {
        cerr << "Error: Could not open file " << file_name << endl;
        exit(1);
    }

    string word;
    while (file >> word)
    {
        word_list.insert(word);
    }
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    queue<vector<string>> ladder_queue;
    unordered_set<string> visited;

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        for (const string& word : word_list)
        {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end())
            {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                if (word == end_word) return new_ladder;

                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};
}

void print_word_ladder(const vector<string>& ladder)
{
    if (ladder.empty())
    {
        cout << "No ladder found." << endl;
        return;
    }

    for (size_t i = 0; i < ladder.size(); i++)
    {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << " ";
    }
    cout << endl;
}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "words.txt");

    vector<string> ladder1 = generate_word_ladder("cat", "dog", word_list);
    print_word_ladder(ladder1);

    vector<string> ladder2 = generate_word_ladder("marty", "curls", word_list);
    print_word_ladder(ladder2);

    vector<string> ladder3 = generate_word_ladder("code", "data", word_list);
    print_word_ladder(ladder3);
}