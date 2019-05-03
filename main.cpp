#include <iostream>
#include <vector>
#include <set>

using namespace std;



int turnCount(vector<int> mass)
{
    int res = 0;
    for (int i = 0; i < 9; i++)
    {
        if (mass[i] != 0)
            res++;
    }
    return res;
}

bool isGameEnded(vector<int> mass)
{
    if (turnCount(mass) == 9)
        return true;
    for (int i = 0; i < 3; i++)
    {
        if ((mass[i] != 0) && (mass[i] == mass[i + 3]) && (mass[i] == mass[i + 6]))
        {
            return true;
        }
        if ((mass[i * 3] != 0) && (mass[i * 3] == mass[i * 3 + 1]) && (mass[i * 3] == mass[i * 3 + 2]))
        {
            return true;
        }
    }
    if ((mass[0] != 0) && (mass[0] == mass[4]) && (mass[0] == mass[8]))
    {
        return true;
    }
    if ((mass[2] != 0) && (mass[2] == mass[4]) && (mass[2] == mass[6]))
    {
        return true;
    }
    return false;
}

void print(vector<int> mass)
{
    for (int i = 0; i < 9; i++)
    {
        cout << mass[i] << " ";
        if((i == 2) || (i == 5) || (i == 8))
            cout << endl;
    }
}

int whoIsNext(vector<int> mass)
{
    int res = 0;
    for (int i = 0; i < 9; i++)
    {
        if (mass[i] != 0)
            res++;
    }
    if (res % 2 == 0)
        return 1;
    else
        return 2;
    return 0;
}

set <vector<int>> *generateSetOfNextTurns(vector<int> mass)
{
    int turn = whoIsNext(mass);

    set <vector<int>> * setRes = new set <vector<int>>();
    if (isGameEnded(mass))
    {
        return setRes;
    }
    for (int i = 0; i < 9; i++)
    {
        if (mass[i] == 0)
        {
            mass[i] = turn;
            setRes->insert(mass);
            mass[i] = 0;
        }
    }
    return setRes;
}

void calculate(vector<int> mass, set <vector<int>>* allSet)
{
    set <vector<int>> *setTmp = generateSetOfNextTurns(mass);
    for(auto i = setTmp->begin(); i != setTmp->end(); i++)
    {
        //if (isGameEnded(*i))
            if (turnCount(*i) <= 9)
                allSet->insert(*i);
        calculate(*i, allSet);
    }
}

int main() // 1=X  2=O
{
    vector<int> mass = {0, 0, 0,    0, 0, 0,    0, 0, 0};

    set <vector<int>> * setMain = new set <vector<int>>();
    calculate(mass, setMain);

    for(auto i : *setMain)
    {
        print(i);
        cout << "---" << endl;
    }
    cout << "size " << setMain->size() << endl;
    cout << "Hello World!" << endl;
    return 0;
}
