#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>

using namespace std;

void welcomeMessage();
void readWord(const int, ifstream &, string []);
int wordLetters(const string [], char [], const int);
int hangmanFigure(int, const string[], int);
int guessLetters(const string[], char [], int &);

int main()
{
    const int MAX_LIST = 100;
    const int MAX_SIZE = 100;

    string words[MAX_SIZE];

    welcomeMessage();

    ifstream inputFile;
    inputFile.open("WordList.txt");

    if (!inputFile)
        cout << "Word list error.\n";
    else
    {
        int word_index, game_score;
        int try_index = 0;
        char blank_for_word[MAX_SIZE];
        string words_list[MAX_LIST];
        char option;

        readWord(MAX_LIST, inputFile, words);

        do
        {
            word_index = wordLetters(words, blank_for_word, MAX_LIST);
            game_score = guessLetters(words, blank_for_word, word_index);

            cout << "\nDo you want to play again (press Y):";
            cin >> option;

            system("cls");

            words_list[try_index] = words[word_index];

            try_index++;

        }while (option == 'y' || option == 'Y');

        inputFile.close();

    }

    return 0;
}

void welcomeMessage()
{
    char ch;
    cout << "\t\t\tWelcome to Hangman\n\n";
    cout << "\tEnter Y to continue: ";
    cin >> ch;

    if (ch == 'Y')
        system("cls");
}

int wordLetters(const string words[], char blank_for_word[], const int MAX_LIST)
{
    int random_word = rand() % 50;

    for (int blanks = 0; blanks < words[random_word].length(); blanks++)
    {
        blank_for_word[blanks] = '_';
        cout << blank_for_word[blanks] << " ";
    }
    return random_word;
}

void readWord(const int MAX_LIST, ifstream &inputFile, string words[])
{
    int i = 0;

    while (i < MAX_LIST && getline(inputFile, words[i]))
    {
        i++;
    }
}

int guessLetters(const string words[], char blank_for_word[], int &word_index)
{
    char letter;
    int i = 0;
    int wrong_choice = 0;
    int score = 0, rounded_score = 0;
    const int MAX_GUESS = 26;

    while (i < MAX_GUESS)
    {
        cout << "\n\nEnter a letter: ";
        cin >> letter;

        int search_letter = 0;
        int count_letter = 0;
        bool found_letter = false;

        while (search_letter < words[word_index].length())
        {
            if (blank_for_word[search_letter] == letter)
            {
                cout << "You already guessed that letter!";
                score--;
            }
            if (words[word_index][search_letter] == letter)
            {
                blank_for_word[search_letter] = letter;
                found_letter = true;
                score++;
            }
            search_letter++;
        }
        i++;

        int j = 0;
        while (j < words[word_index].length())
        {
            if (blank_for_word[j] != '_')
                count_letter++;
            j++;
        }

        system("cls");

        int k = 0;
        while (k < words[word_index].length())
        {
            cout << blank_for_word[k] << " ";
            k++;
        }

        if (!found_letter)
        {
            cout << "\n\nWrong letter!\n";
            wrong_choice++;
            score--;
        }

        cout << "\n\n\t   == Hangman ==\n\n";
        int check = hangmanFigure(wrong_choice, words, word_index);

        rounded_score = static_cast<double>(score) / words[word_index].length() * 10;

        if (count_letter == words[word_index].length() && check == 0)
        {
            cout << "\nYou guessed the word!";
            rounded_score += 2;

            if (wrong_choice == 0)
            {
                cout << "\nCONGRATS ON FIRST TRY!!";
                rounded_score++;
            }

            break;
        }
        else if (check == -1)
        {
            if (rounded_score < 0)
                rounded_score = 0;
            break;
        }
    }

    cout << "\nYour score is: " << rounded_score << "/10" ;

    return rounded_score;
}

int hangmanFigure(int wrong_choice, const string words[], int word_index)
{
    char head = 'O', left_body = '/', right_body = '\\', body = '|';

    if (wrong_choice > 0)
        cout << "\t\t " << head << endl;
    if (wrong_choice == 2)
        cout << "\t\t " << body;
    else if (wrong_choice > 2)
        cout << "\t\t" << left_body << body;
    if (wrong_choice > 3)
        cout << right_body << endl;
    if (wrong_choice > 4)
        cout << "\t\t" << left_body;
    if (wrong_choice > 5)
        cout << " " << right_body;
    if (wrong_choice > 6)
    {
        cout << "\n\nGAME OVER!!";
        cout << "\nYour word was " << words[word_index];

        return -1;
    }
    return 0;
}