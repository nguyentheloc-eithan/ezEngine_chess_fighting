#include "main.h"

enum ElementType
{
    PATH,
    WALL,
    FAKE_WALL
};
enum MovingObject
{
    SHERLOCK,
    WATSON,
    CRIMINAL,
    ROTBOT
};

class Position
{
private:
    int r, c;

public:
    Position(int r = 0, int c = 0)
    {
        this->r = r;
        this->c = c;
    }
    Position(const string &str_pos)
    {
        int r_get, c_get = 0;
        findCoordinates(str_pos, r_get, c_get);
        this->r = r_get;
        this->c = c_get;
    }
    void findCoordinates(string s, int &x, int &y)
    {
        size_t commaPos = s.find(',');
        string xStr = s.substr(1, commaPos - 1);
        string yStr = s.substr(commaPos + 1, s.size() - commaPos - 2);
        x = stoi(xStr);
        y = stoi(yStr);
    }
    int getRow() const
    {
        return this->r;
    };
    int getCol() const
    {
        return this->c;
    }
    void setRow(int r)
    {
        this->r = r;
    }
    void setCol(int c)
    {
        this->c = c;
    }
    string str() const
    {
        string x = to_string(this->r);
        string y = to_string(this->c);
        string result = "(" + x + "," + y + ")";
        return result;
    }
    bool isEqual(int in_r, int in_c) const
    {
        if (this->r == in_r && this->c == in_c)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class MapElement
{
protected:
    ElementType type;

public:
    MapElement(ElementType in_type) : type(in_type) {}
    virtual ~MapElement() {}
    virtual ElementType getType() const { return type; }
};

class Path : public MapElement
{
public:
    Path() : MapElement(PATH) {}
};

class Wall : public MapElement
{
public:
    Wall() : MapElement(WALL) {}
};

class FakeWall : public MapElement
{
private:
    int req_exp; //! EXP tối thiểu mà Watson cần có để phát hiện ra bức tường.
public:
    FakeWall(int in_req_exp = 0) : MapElement(FAKE_WALL), req_exp(in_req_exp) {}
    int getReqExp() const
    {
        return this->req_exp;
    }
    void setReqExp(int req_exp)
    {
        this->req_exp = req_exp;
    }
};

class Map
{
private:
    int num_rows, num_cols;
    MapElement ***map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls)
        : num_rows(num_rows), num_cols(num_cols)
    {
        // Initialize the map with nullptrs
        map = new MapElement **[num_rows];
        for (int i = 0; i < num_rows; ++i)
        {
            map[i] = new MapElement *[num_cols];
            for (int j = 0; j < num_cols; ++j)
            {
                map[i][j] = nullptr;
            }
        }

        // Place walls
        for (int i = 0; i < num_walls; ++i)
        {
            int wall_row = array_walls[i].getRow();
            int wall_col = array_walls[i].getCol();
            if (wall_row >= 0 && wall_row < num_rows && wall_col >= 0 && wall_col < num_cols)
            {
                if (map[wall_row][wall_col] == nullptr || map[wall_row][wall_col]->getType() == PATH)
                {
                    delete map[wall_row][wall_col];
                    map[wall_row][wall_col] = new Wall();
                }
            }
        }

        // Place fake walls
        for (int i = 0; i < num_fake_walls; ++i)
        {
            int fake_wall_row = array_fake_walls[i].getRow();
            int fake_wall_col = array_fake_walls[i].getCol();
            if (fake_wall_row >= 0 && fake_wall_row < num_rows && fake_wall_col >= 0 && fake_wall_col < num_cols)
            {
                if (map[fake_wall_row][fake_wall_col] == nullptr || map[fake_wall_row][fake_wall_col]->getType() == PATH)
                {
                    int reqNew = (fake_wall_row * 257 + fake_wall_col * 139) % 900 + 1;
                    map[fake_wall_row][fake_wall_col] = new FakeWall(reqNew);
                }
            }
        }
        // Fill remaining positions with paths
        for (int i = 0; i < num_rows; ++i)
        {
            for (int j = 0; j < num_cols; ++j)
            {
                if (map[i][j] == nullptr)
                {
                    map[i][j] = new Path();
                }
            }
        }
    }

    ~Map()
    {
        for (int i = 0; i < num_rows; ++i)
        {
            for (int j = 0; j < num_cols; ++j)
            {
                delete map[i][j];
            }
            delete[] map[i];
        }
        delete[] map;
    }

    int getNumRows() const
    {
        return this->num_rows;
    }
    int getNumCols() const
    {
        return this->num_cols;
    }
    ElementType getElementType(int i, int j) const
    {
        return map[i][j]->getType();
    }

    bool isValid(int i, int j, MovingObject object, int exp) const
    {
        // Check if position (i, j) is within the bounds of the matrix
        if (i < 0 || i >= num_rows || j < 0 || j >= num_cols)
        {
            return false; // Position is outside the matrix
        }

        // Get the type of MapElement at position (i, j)
        ElementType elementType = getElementType(i, j);

        switch (object)
        {
        case SHERLOCK:
            return (elementType == PATH || elementType == FAKE_WALL);
        case WATSON:
            if (elementType == PATH)
            {
                return true;
            }
            else if (elementType == FAKE_WALL)
            {
                // Watson can move onto FAKE_WALL if its experience level is sufficient
                FakeWall *fakeWall = dynamic_cast<FakeWall *>(map[i][j]);
                if (fakeWall && exp >= fakeWall->getReqExp())
                {
                    return true;
                }
            }
            return false;
        case CRIMINAL:
            return (elementType == PATH || elementType == FAKE_WALL);
        case ROTBOT:
            return (elementType == PATH || elementType == FAKE_WALL);
        default:
            return false; // Invalid MovingObject
        }
    }
};

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
            // cout << config << endl;
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
}