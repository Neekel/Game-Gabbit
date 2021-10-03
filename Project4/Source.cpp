#include <iostream>
#include <Windows.h>  
#include <string>
#include <vector>
#include <ctime>       
using namespace std;




class Game
{
private:

    vector <string> words{ "волна", "берег", "программа", "волос", "машина", "дудка", "нотариус", "компьютер", "мышка", "монитор" };
    int fails = 6;
    int failsNum = 0;
    string word;
    vector <char> calledLetters = {};

    bool wasCalled(const char letter)       // буква уже называлась
    {
        return (find(calledLetters.begin(), calledLetters.end(), letter) < calledLetters.end());
    }

    void showWord()            //показать слово
    {
        cout << "слово: ";
        for (const auto& letter : word)
        {
            if (wasCalled(letter))
                cout << letter << ' ';
            else
                cout << "_ ";
        }
        cout << endl;
    }

    char getLetter()         //ввод букв
    {
        cout << "Назовите букву: ";
        string usersInput{ "" };
        getline(cin, usersInput);      // принимаем весь ввод
        char letter = usersInput[0];   // получаем первую букву
        while (wasCalled(letter) || (usersInput.length() > 1))
        {
            if (usersInput.length() > 1)
                cin.clear();
            cout << "Повторите ввод: ";
            getline(cin, usersInput);
            letter = usersInput[0];
        }
        calledLetters.push_back(letter);
        return letter;
    }

    bool win()                         //победа
    {
        for (const auto& letterInWord : word)
            if (!wasCalled(letterInWord))
                return false;
        return true;
    }


    void oneTurn()                    //проверка ввода буквы
    {
        showWord();
        char letter = getLetter();                 // получаем букву
        bool rightLetter = false;

        for (const auto& letterInWord : word)
        {
            if (letter == letterInWord)
            {
                rightLetter = true;
                break;
            }
        }
        if (rightLetter)
            cout << "Такая буква в слове есть!\n";
        else
        {
            cout << "Такой буквы в слове нет! ";
            ++failsNum;
            if (fails > failsNum)
                cout << "У вас осталось " << (fails - failsNum) << " попытки неверно угадать букву!\n";
            else
                cout << "У вас не осталось попыток неверно угадать букву.\n";
        }
    }
public:
    Game(const string wordToGuess = "", const int maxFails = 6) : fails(maxFails)         //конструктор
    {
        (wordToGuess == "") ? (word = words[rand() % words.size()]) : (word = wordToGuess);     //выбираем слово

        cout << "Компьютер загадал слово, и Вы должны его угадать, называя буквы."
            << "У вас есть " << fails << " попыток.\n\n";

        while (!win() && (failsNum <= fails))
            oneTurn();
        if (win())
            cout << "\nВы угадали слово <<" << word << ">>. Поздравляем!" << endl;
        else
            cout << "\nВы не угадали слово <<" << word << ">>. Очень жаль! " << endl;
    }
};


class GameStart
{
public:
    GameStart();
    ~GameStart();
};

GameStart::GameStart()
{
    int play;
    for (;;)
    {
        cout << "\nНажмите 1 для начала игры или 2 для выхода " << endl;
        cin >> play;
        if (play == 1) Game game;
        else if (play == 2) exit(0);
        else cout << "\nНеправильный символ " << endl;
    }
}

GameStart::~GameStart()
{
}

int main()
{
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    srand(static_cast<unsigned int>(time(0)));
    GameStart game;
    return 0;
}