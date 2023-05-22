#include <bits/stdc++.h>
#include <Windows.h>
#include <mmsystem.h>

using namespace std;

const int MAX_BAD_GUESSES = 7;
const char DATA_FILE[] = "DATA_FILE.txt";

string getLowerCaseString(const string& s) // lấy chữ viết thường
{
    string res = s;
    transform(s.begin(), s.end(), res.begin(), ::tolower);
    return res;
}

string chooseWord(const char* fileName) //chọn từ trong file DATA_FILE.txt
{
    vector<string> wordList;
    ifstream file(fileName);
    if (file.is_open()) {

        string word;
        while (file >> word) {
            wordList.push_back(word);
        }
        file.close();
    }
    if (wordList.size() > 0) {
        int randomIndex = rand() % wordList.size();
        return getLowerCaseString(wordList[randomIndex]);
    } else return "";
}

char readAGuess()   //  in ra màn hình
{
    char input;
    cout << "Your guess: ";
    cin >> input;
    return tolower(input);
}

bool contains(const string& word, char c)   //kiểm tra xem có xuất hiện chữ cái trong từ cần đoán không
{
    return (word.find_first_of(c) != string::npos);
}

void updateGuessedWord(string& guessedWord, const string& word, char guess) //hiện ra chữ đã đoán đúng
{
    for (int i = word.length() - 1; i >= 0; i--) {
        if (word[i] == guess) {
            guessedWord[i] = guess;
        }
    }
}

void clearScreen() {
    const int PATCH_LINES = 30;
    for (int i = 0; i < PATCH_LINES; i++) cout << endl;
}

const string FIGURE[] = {
        "   -------------    \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        " -----              \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        " -----              \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        " -----              \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |           |    \n"
        "   |                \n"
        "   |                \n"
        " -----              \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|    \n"
        "   |                \n"
        "   |                \n"
        " -----              \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |                \n"
        "   |                \n"
        " -----              \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |          /     \n"
        "   |                \n"
        " -----              \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |          / \\  \n"
        "   |                \n"
        " -----              \n"
    };

void renderGame(const string& guessedWord, const string& badGuesses)        // in ra  các mục
{
    clearScreen();
    int badGuessCount = badGuesses.length();
    cout << FIGURE[badGuessCount] << endl;
    cout << "Secret word: " << guessedWord << endl;
    if (badGuessCount > 0) {
        cout << "You've made " << badGuessCount << " wrong ";
        cout << (badGuessCount == 1 ? "guess" : "guesses");
        cout << ": " << badGuesses << endl;
    }
}

const string& getNextDancingMan() {
    const static string figure[] = {
    "     O     \n"
    "    /|\\   \n"
    "    | |    \n",
    "     O     \n"
    "    /|\\   \n"
    "    / \\   \n",
    "   __O__   \n"
    "     |     \n"
    "    / \\   \n",
    "    \\O/   \n"
    "     |     \n"
    "    / \\   \n",
    "   __O__   \n"
    "     |     \n"
    "    / \\   \n",
    "     O     \n"
    "    /|\\   \n"
    "    / \\   \n",
    "    O      \n"
    "    /|\\   \n"
    "    / \\   \n",
    "     O     \n"
    "    /|\\   \n"
    "    / \\   \n",
    "      O    \n"
    "    /|\\   \n"
    "    / \\   \n",
    "     O     \n"
    "    /|\\   \n"
    "    / \\   \n",
    };
    const static int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

const string& getNextHangMan() {
    const static string figure[] = {
    "   ------------+     \n"
    "   |    /            \n"
    "   |    O            \n"
    "   |   /|\\          \n"
    "   |   / \\          \n"
    "   |                 \n"
    " -----               \n",
    "   ------------+     \n"
    "   |     |           \n"
    "   |     O           \n"
    "   |    /|\\         \n"
    "   |    / \\         \n"
    "   |                 \n"
    " -----               \n",
    "   ------------+     \n"
    "   |      \\         \n"
    "   |      O          \n"
    "   |     /|\\        \n"
    "   |     / \\        \n"
    "   |                 \n"
    " -----               \n",
    "   ------------+     \n"
    "   |     |           \n"
    "   |     O           \n"
    "   |    /|\\         \n"
    "   |    / \\         \n"
    "   |                 \n"
    " -----               \n"
    };
    const static int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

void displayFinalResult(bool won, const string& word) { //hiển thị kết quả
    cout << (won ? PlaySound(TEXT("thang.wav"),NULL,SND_ASYNC) : PlaySound(TEXT("thua.wav"),NULL,SND_ASYNC));
    while (true) {
        clearScreen();
        if (won)
            cout << "---Congratulations!---\n      You win!" << endl;
        else{
            cout  << "---------------GAME OVER---------------\n\n\n" << "You lost. The correct word is: " << word <<  endl;
        }
        cout << (won ? getNextDancingMan() : getNextHangMan());
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int main()
{
    srand(time(0));
    string word = chooseWord(DATA_FILE);
    if (word.length() < 1) {
        cout << "Error reading vocabulary file " << DATA_FILE;
        return -1;
    }
    string guessedWord = string(word.length(), '-');
    string badGuesses = "";
    renderGame(guessedWord, badGuesses);
    PlaySound(TEXT("nhacnen.wav"),NULL,SND_ASYNC);
    while (badGuesses.length() < MAX_BAD_GUESSES && word != guessedWord){
        renderGame(guessedWord, badGuesses);
        char guess = readAGuess();
        if (contains(word, guess)){  // kiểm tra xem đoán đúng chưa
            updateGuessedWord(guessedWord, word, guess);  // đúng thì cập nhật lại
            PlaySound(TEXT("traloidung.wav"),NULL,SND_SYNC);
            }
        else {
            badGuesses += guess;    // chưa đúng thì tăng số từ đã đoán sai
            PlaySound(TEXT("traloisai.wav"),NULL,SND_SYNC);
        }
    }
    displayFinalResult(badGuesses.length() < MAX_BAD_GUESSES, word); // hiển thị kết quả ra màn hình

    return 0;
}



