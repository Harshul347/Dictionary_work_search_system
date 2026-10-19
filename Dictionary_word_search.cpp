
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cctype>
using namespace std;

class Word {
public:
    string name;
    string meaning;
    string synonym;
    string antonym;
    string example;

    Word(string w, string m, string s, string a, string e)
        : name(w), meaning(m), synonym(s), antonym(a), example(e) {}
};

class Dictionary {
private:
    vector<Word> words;

    string toLower(string text) const {
        transform(text.begin(), text.end(), text.begin(),
            [](unsigned char c) {
                return static_cast<char>(tolower(c));
            });
        return text;
    }

    int findWord(const string& name) const {
        string target = toLower(name);

        for (int i = 0; i < (int)words.size(); i++) {
            if (toLower(words[i].name) == target)
                return i;
        }

        return -1;
    }

    string readText(const string& prompt) {
        string text;
        cout << prompt;
        getline(cin, text);
        return text;
    }

public:
    Dictionary() {
        words.emplace_back(
            "Abundant",
            "Available in large quantities",
            "Plentiful",
            "Scarce",
            "The garden has abundant flowers."
        );

        words.emplace_back(
            "Brave",
            "Ready to face danger or difficulty",
            "Courageous",
            "Cowardly",
            "The brave firefighter saved the child."
        );

        words.emplace_back(
            "Diligent",
            "Showing careful and hard work",
            "Hardworking",
            "Lazy",
            "She is a diligent student."
        );

        words.emplace_back(
            "Eager",
            "Very interested or excited to do something",
            "Enthusiastic",
            "Uninterested",
            "He is eager to learn programming."
        );

        words.emplace_back(
            "Honest",
            "Truthful and sincere",
            "Truthful",
            "Dishonest",
            "An honest person tells the truth."
        );
    }

    void searchWord() const {
        string name;
        cout << "Enter word to search: ";
        getline(cin, name);

        int index = findWord(name);

        if (index == -1) {
            cout << "Word not found in dictionary.\n";
            return;
        }

        const Word& w = words[index];

        cout << "\n========== WORD DETAILS ==========\n";
        cout << "Word      : " << w.name << '\n';
        cout << "Meaning   : " << w.meaning << '\n';
        cout << "Synonym   : " << w.synonym << '\n';
        cout << "Antonym   : " << w.antonym << '\n';
        cout << "Example   : " << w.example << '\n';
    }

    void addWord() {
        string name = readText("Enter new word: ");

        if (name.empty()) {
            cout << "Word cannot be empty.\n";
            return;
        }

        if (findWord(name) != -1) {
            cout << "Word already exists!\n";
            return;
        }

        string meaning = readText("Enter meaning: ");
        string synonym = readText("Enter synonym: ");
        string antonym = readText("Enter antonym: ");
        string example = readText("Enter example sentence: ");

        if (meaning.empty()) {
            cout << "Meaning cannot be empty.\n";
            return;
        }

        words.emplace_back(name, meaning, synonym, antonym, example);
        cout << "Word added successfully!\n";
    }

    void updateWord() {
        string name = readText("Enter word to update: ");
        int index = findWord(name);

        if (index == -1) {
            cout << "Word not found!\n";
            return;
        }

        string meaning = readText("Enter new meaning: ");
        string synonym = readText("Enter new synonym: ");
        string antonym = readText("Enter new antonym: ");
        string example = readText("Enter new example: ");

        if (meaning.empty()) {
            cout << "Meaning cannot be empty.\n";
            return;
        }

        words[index].meaning = meaning;
        words[index].synonym = synonym;
        words[index].antonym = antonym;
        words[index].example = example;

        cout << "Word updated successfully!\n";
    }

    void deleteWord() {
        string name = readText("Enter word to delete: ");
        int index = findWord(name);

        if (index == -1) {
            cout << "Word not found!\n";
            return;
        }

        words.erase(words.begin() + index);
        cout << "Word deleted successfully!\n";
    }

    void displayAllWords() const {
        if (words.empty()) {
            cout << "Dictionary is empty.\n";
            return;
        }

        vector<const Word*> sortedWords;
        for (const auto& w : words)
            sortedWords.push_back(&w);

        sort(sortedWords.begin(), sortedWords.end(),
            [this](const Word* a, const Word* b) {
                return toLower(a->name) < toLower(b->name);
            });

        cout << "\n========== ALL WORDS ==========\n";

        for (const Word* w : sortedWords)
            cout << w->name << " - " << w->meaning << '\n';

        cout << "Total words: " << words.size() << '\n';
    }

    void searchPrefix() const {
        string prefix = readText("Enter starting letters: ");
        string target = toLower(prefix);
        bool found = false;

        cout << "\nWords starting with \"" << prefix << "\":\n";

        for (const auto& w : words) {
            string name = toLower(w.name);

            if (name.find(target) == 0) {
                cout << w.name << " - " << w.meaning << '\n';
                found = true;
            }
        }

        if (!found)
            cout << "No matching words found.\n";
    }
};

int main() {
    Dictionary dictionary;
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "       DICTIONARY WORD SEARCH\n";
        cout << "====================================\n";
        cout << "1. Search Word\n";
        cout << "2. Add New Word\n";
        cout << "3. Update Word\n";
        cout << "4. Delete Word\n";
        cout << "5. Display All Words\n";
        cout << "6. Search by Starting Letters\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: dictionary.searchWord(); break;
            case 2: dictionary.addWord(); break;
            case 3: dictionary.updateWord(); break;
            case 4: dictionary.deleteWord(); break;
            case 5: dictionary.displayAllWords(); break;
            case 6: dictionary.searchPrefix(); break;
            case 0: cout << "Dictionary closed.\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
