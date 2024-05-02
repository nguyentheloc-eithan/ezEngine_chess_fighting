#include "main.h"
using namespace std;

string getVar(string tp)
{
    string variable = "";
    int i = 0;
    while (tp[i] != '=')
    {
        i++;
    }
    i++;
    while (tp[i] != '\0' && tp[i] != ' ')
    {
        variable += tp[i];
        i++;
    }
    return variable;
}
string getCommand(string tp)
{
    string command = "";
    int i = 0;
    while (tp[i] != '=')
    {
        command += tp[i];
        i++;
    }
    return command;
}

// Function to calculate the number of positions in the ARRAY_WALLS
int calculatePositions(string input)
{
    int count = 0;
    bool inPair = false;

    for (char c : input)
    {
        if (c == '(')
        {
            // Entering a coordinate pair
            inPair = true;
        }
        else if (c == ')')
        {
            // Exiting a coordinate pair
            inPair = false;
            ++count;
        }
        else if (c == ';' && inPair)
        {
            ++count;
        }
    }

    return count;
}
void extractCoordinates(const string &input, int **arr_walls, int size)
{
    int index = 1;
    for (int i = 0; i < size; ++i)
    {
        int start_pos = input.find('(', index);
        int end_pos = input.find(')', start_pos);

        string coordinate = input.substr(start_pos + 1, end_pos - start_pos - 1);

        int comma_pos = coordinate.find(',');

        int x = stoi(coordinate.substr(0, comma_pos));
        int y = stoi(coordinate.substr(comma_pos + 1));

        arr_walls[i] = new int[2];
        arr_walls[i][0] = x;
        arr_walls[i][1] = y;

        index = end_pos + 2;
    }
}
void getInitPos(string input, int &x, int &y)
{
    stringstream ss(input);
    char ch;
    ss >> ch;
    ss >> x;
    ss >> ch;
    ss >> y;
}

void configuration(string fileName)
{
    fstream newFile;
    newFile.open(fileName, ios::in);
    if (newFile.is_open())
    {
        string tp;
        while (getline(newFile, tp))
        {
            string config = getCommand(tp);
            if (config == "MAP_NUM_ROWS")
            {
                string var = getVar(tp);
                map_num_rows = std::stoi(var);
            }
            else if (config == "MAP_NUM_COLS")
            {
                string var = getVar(tp);
                map_num_cols = std::stoi(var);
            }
            else if (config == "MAX_NUM_MOVING_OBJECTS")
            {
                string var = getVar(tp);
                max_num_moving_objects = std::stoi(var);
            }
            else if (config == "ARRAY_WALLS")
            {
                string var = getVar(tp);
                num_walls = calculatePositions(var);
                int **arr_wallsT = new int *[num_walls];
                extractCoordinates(var, arr_wallsT, num_walls);
                arr_walls = arr_wallsT;
            }
            else if (config == "ARRAY_FAKE_WALLS")
            {
                string var = getVar(tp);
                num_fake_walls = calculatePositions(var);
                int **arr_fake_walls_temp = new int *[num_fake_walls];
                extractCoordinates(var, arr_fake_walls_temp, num_fake_walls);
                arr_fake_walls = arr_fake_walls_temp;
            }
            else if (config == "SHERLOCK_MOVING_RULE")
            {
                sherlock_moving_rule = getVar(tp);
            }
            else if (config == "SHERLOCK_INIT_POS")
            {
                string var = getVar(tp);
                int x, y = 0;
                getInitPos(var, sherlock_init_pos[0], sherlock_init_pos[1]);
            }
            else if (config == "SHERLOCK_INIT_HP")
            {
                string var = getVar(tp);
                sherlock_init_hp = std::stoi(var);
            }
            else if (config == "SHERLOCK_INIT_EXP")
            {
                string var = getVar(tp);
                sherlock_init_exp = std::stoi(var);
            }
            else if (config == "WATSON_MOVING_RULE")
            {
                watson_moving_rule = getVar(tp);
            }
            else if (config == "WATSON_INIT_POS")
            {
                string var = getVar(tp);
                // int x, y = 0;
                getInitPos(var, watson_init_pos[0], watson_init_pos[1]);
            }
            else if (config == "WATSON_INIT_HP")
            {
                string var = getVar(tp);
                watson_init_hp = std::stoi(var);
            }
            else if (config == "WATSON_INIT_EXP")
            {
                string var = getVar(tp);
                watson_init_exp = std::stoi(var);
            }
            else if (config == "CRIMINAL_INIT_POS")
            {
                string var = getVar(tp);
                // int x, y = 0;
                getInitPos(var, criminal_init_pos[0], criminal_init_pos[1]);
            }
            else if (config == "NUM_STEPS")
            {
                string var = getVar(tp);
                num_steps = std::stoi(var);
            }
        }
        newFile.close();
    }
    // TODO:
}