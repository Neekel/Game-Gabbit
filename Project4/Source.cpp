#include <iostream>
#include <Windows.h>  
#include <string>
#include <vector>
#include <ctime>       
using namespace std;




class Game
{
private:

    vector <string> words{ "�����", "�����", "���������", "�����", "������", "�����", "��������", "���������", "�����", "�������" };
    int fails = 6;
    int failsNum = 0;
    string word;
    vector <char> calledLetters = {};

    bool wasCalled(const char letter)       // ����� ��� ����������
    {
        return (find(calledLetters.begin(), calledLetters.end(), letter) < calledLetters.end());
    }

    void showWord()            //�������� �����
    {
        cout << "�����: ";
        for (const auto& letter : word)
        {
            if (wasCalled(letter))
                cout << letter << ' ';
            else
                cout << "_ ";
        }
        cout << endl;
    }

    char getLetter()         //���� ����
    {
        cout << "�������� �����: ";
        string usersInput{ "" };
        getline(cin, usersInput);      // ��������� ���� ����
        char letter = usersInput[0];   // �������� ������ �����
        while (wasCalled(letter) || (usersInput.length() > 1))
        {
            if (usersInput.length() > 1)
                cin.clear();
            cout << "��������� ����: ";
            getline(cin, usersInput);
            letter = usersInput[0];
        }
        calledLetters.push_back(letter);
        return letter;
    }

    bool win()                         //������
    {
        for (const auto& letterInWord : word)
            if (!wasCalled(letterInWord))
                return false;
        return true;
    }


    void oneTurn()                    //�������� ����� �����
    {
        showWord();
        char letter = getLetter();                 // �������� �����
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
            cout << "����� ����� � ����� ����!\n";
        else
        {
            cout << "����� ����� � ����� ���! ";
            ++failsNum;
            if (fails > failsNum)
                cout << "� ��� �������� " << (fails - failsNum) << " ������� ������� ������� �����!\n";
            else
                cout << "� ��� �� �������� ������� ������� ������� �����.\n";
        }
    }
public:
    Game(const string wordToGuess = "", const int maxFails = 6) : fails(maxFails)         //�����������
    {
        (wordToGuess == "") ? (word = words[rand() % words.size()]) : (word = wordToGuess);     //�������� �����

        cout << "��������� ������� �����, � �� ������ ��� �������, ������� �����."
            << "� ��� ���� " << fails << " �������.\n\n";

        while (!win() && (failsNum <= fails))
            oneTurn();
        if (win())
            cout << "\n�� ������� ����� <<" << word << ">>. �����������!" << endl;
        else
            cout << "\n�� �� ������� ����� <<" << word << ">>. ����� ����! " << endl;
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
        cout << "\n������� 1 ��� ������ ���� ��� 2 ��� ������ " << endl;
        cin >> play;
        if (play == 1) Game game;
        else if (play == 2) exit(0);
        else cout << "\n������������ ������ " << endl;
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