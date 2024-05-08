#include "main.h"
enum ElementType
{
    PATH,
    WALL,
    FAKE_WALL
};
enum RobotType
{
    C = 0,
    S,
    W,
    SW
};
enum MovingObjectType
{
    SHERLOCK,
    WATSON,
    CRIMINAL,
    ROBOT
};

class MapElement
{
protected:
    ElementType type;

public:
    MapElement(ElementType in_type);
    virtual ~MapElement();
    virtual ElementType getType() const;
};

class Path : public MapElement
{
public:
    Path();
};

class Wall : public MapElement
{
public:
    Wall();
};

class FakeWall : public MapElement
{
private:
    int req_exp;

public:
    FakeWall(int in_req_exp);
    int getReqExp() const;
};
class Position
{
private:
    int r, c;

public:
    static const Position npos;
    Position(int r = 0, int c = 0);
    Position(const string &str_pos);
    int getRow() const;
    int getCol() const;

    void setRow(int r);
    void setCol(int c);
    string str() const;
    bool isEqual(Position position) const;
    void findCoordinates(string s, int &x, int &y)
    {
        size_t commaPos = s.find(',');
        string xStr = s.substr(1, commaPos - 1);
        string yStr = s.substr(commaPos + 1, s.size() - commaPos - 2);
        x = stoi(xStr);
        y = stoi(yStr);
    }
    std::array<Position, 4> getAdjacentPositions() const
    {
        std::array<Position, 4> adjacentPositions;
        // theo chiều kim đồng hồ
        adjacentPositions[0] = Position(r - 1, c); // Bên U
        adjacentPositions[1] = Position(r, c + 1); // Bên R
        adjacentPositions[2] = Position(r + 1, c); // Bên D
        adjacentPositions[3] = Position(r, c - 1); // Bên L

        return adjacentPositions;
    }
    std::array<Position, 4> getAdjacentPositionsULDR() const
    {
        std::array<Position, 4> adjacentPositions;
        // theo chiều kim đồng hồ
        adjacentPositions[0] = Position(r - 1, c); // Bên U
        adjacentPositions[1] = Position(r, c - 1); // Bên L
        adjacentPositions[2] = Position(r + 1, c); // Bên D
        adjacentPositions[3] = Position(r, c + 1); // Bên R

        return adjacentPositions;
    }
    std::array<Position, 8> getAdjacentPositions2Steps() const
    {
        std::array<Position, 8> adjacentPositions;
        adjacentPositions[0] = Position(r - 2, c);     // Bên U
        adjacentPositions[1] = Position(r - 1, c + 1); // Bên UR

        adjacentPositions[2] = Position(r, c + 2);     // Bên R
        adjacentPositions[3] = Position(r + 1, c + 1); // Bên DR

        adjacentPositions[4] = Position(r + 2, c);     // Bên D
        adjacentPositions[5] = Position(r + 1, c - 1); // Bên DL

        adjacentPositions[6] = Position(r, c - 2);      // Bên L
        adjacentPositions[7] = Position(r - 1, c - -1); // Bên LU

        return adjacentPositions;
    }
};

class Map;

class MovingObject
{
protected:
    int index;
    Position pos;
    Map *map;
    string name;

public:
    MovingObject(int index, const Position pos, Map *map, const string &name = "");
    Position getCurrentPosition() const;
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual MovingObjectType getObjectType() const = 0;
};

class Character : public MovingObject
{

public:
    Character(int index, const Position pos, Map *map, const string &name = "");

    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual MovingObjectType getObjectType() const = 0;
};

class Sherlock : public Character
{
private:
    string moving_rule;
    int HP;
    int EXP;
    int index_moving_rule;

public:
    Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);

    Position getNextPosition() override;
    void move();
    void updatePos(Position new_pos)
    {
        this->pos = new_pos;
    }
    string str() const;

    MovingObjectType getObjectType() const;

    int getHP() const;
    int getEXP() const;
    void setHP(int hp);
    void setEXP(int exp);
};

class Watson : public Character
{
private:
    string moving_rule;
    int HP;
    int EXP;
    int index_moving_rule;

public:
    Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);

    Position getNextPosition() override;
    void updatePos(Position new_pos)
    {
        this->pos = new_pos;
    }
    void move();
    string str() const override;

    MovingObjectType getObjectType() const override;

    int getHP() const;
    int getEXP() const;

    void setHP(int hp);

    void setEXP(int exp);
};

class Map
{
private:
    int num_rows, num_cols;
    MapElement ***map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls);
    ~Map();

    int getNumRows() const;
    int getNumCols() const;
    ElementType getElementType(int i, int j) const;
    MapElement *getElementAtPosition(const Position &pos) const;
    bool isValid(const Position pos, MovingObject *mv_obj) const;
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
    void extractCoordinates(const string &input, Position *&arr_walls, int size)
    {
        arr_walls = new Position[size];

        int index = 1;
        for (int i = 0; i < size; ++i)
        {
            int start_pos = input.find('(', index);
            int end_pos = input.find(')', start_pos);

            string coordinate = input.substr(start_pos + 1, end_pos - start_pos - 1);

            int comma_pos = coordinate.find(',');

            int x = stoi(coordinate.substr(0, comma_pos));
            int y = stoi(coordinate.substr(comma_pos + 1));

            arr_walls[i] = Position(x, y);

            index = end_pos + 2;
        }
    }
    void getInitPos(string input, Position &pos)
    {
        stringstream ss(input);
        char ch;
        ss >> ch; // discard '('
        int x, y;
        ss >> x;
        ss >> ch; // discard ','
        ss >> y;
        pos.setRow(x);
        pos.setCol(y);
    }
};

class Criminal : public Character
{
private:
    Sherlock *sherlock;
    Watson *watson;
    int count;

public:
    int manhattanDistance(const Position &pos1, const Position &pos2) const;
    bool isCreatedRobotNext() const;
    Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson);
    Position getNextPosition() override;
    void move();
    string str() const;
    MovingObjectType getObjectType() const;
    int getCount() const;
    void increaseCount()
    {
        this->count++;
    }
};

class Robot : public MovingObject
{
protected:
    Criminal *criminal;
    // BaseItem * item;
    RobotType robot_type;

public:
    Robot(int index, const Position &pos, Map *map, RobotType robot_type, Criminal *criminal, const string &name = "");
    void setCurrentPosition(const Position &newPos)
    {
        pos = newPos;
    }
    static Robot *create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson);
    MovingObjectType getObjectType() const;
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual RobotType getType() const = 0;
    virtual int getDistance() const = 0;
};
class RobotC : public Robot
{
private:
    Position nextPosition;

public:
    RobotC(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal);

    int getDistance(Sherlock *sherlock);

    int getDistance(Watson *watson);
    Position getNextPosition() override;
    void move();
    string str() const override;
    int getDistance() const override;
    RobotType getType() const override;
};

class RobotW : public Robot
{
private:
    Watson *watson;

public:
    RobotW(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal, Watson *watson);

    Position getNextPosition() override;

    void move() override;

    string str() const override;

    RobotType getType() const override;

    int getDistance() const override;
};

class RobotS : public Robot
{
private:
    Sherlock *sherlock;

public:
    RobotS(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal, Sherlock *sherlock);

    Position
    getNextPosition() override;
    void move() override;

    string str() const override;
    RobotType getType() const override;

    int getDistance() const override;
};

class RobotSW : public Robot
{
private:
    Sherlock *sherlock;
    Watson *watson;

public:
    RobotSW(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal, Sherlock *sherlock, Watson *watson);

    Position getNextPosition() override;
    string str() const;
    RobotType getType() const override;
    int getDistance() const override;
    void move() override;
};

class ArrayMovingObject
{
private:
    MovingObject **arr_mv_objs;
    int count;
    int capacity;

public:
    ArrayMovingObject(int capacity);
    ~ArrayMovingObject();
    bool isFull() const;
    bool add(MovingObject *mv_obj);
    MovingObject *get(int index) const;
    int size() const;
    string str() const;
};

class Configuration
{
    friend class StudyPinkProgram;

private:
    int map_num_rows;
    int map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position *arr_walls;
    int num_fake_walls;
    Position *arr_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;

public:
    Configuration(const string &filepath);

    ~Configuration();
    string str() const;
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
    void extractCoordinates(const string &input, Position *&arr_walls, int size)
    {
        arr_walls = new Position[size];

        int index = 1;
        for (int i = 0; i < size; ++i)
        {
            int start_pos = input.find('(', index);
            int end_pos = input.find(')', start_pos);

            string coordinate = input.substr(start_pos + 1, end_pos - start_pos - 1);

            int comma_pos = coordinate.find(',');

            int x = stoi(coordinate.substr(0, comma_pos));
            int y = stoi(coordinate.substr(comma_pos + 1));

            arr_walls[i] = Position(x, y);

            index = end_pos + 2;
        }
    }
    void getInitPos(string input, Position &pos)
    {
        stringstream ss(input);
        char ch;
        ss >> ch; // discard '('
        int x, y;
        ss >> x;
        ss >> ch; // discard ','
        ss >> y;
        pos.setRow(x);
        pos.setCol(y);
    }
};

class StudyPinkProgram
{
private:
    // Sample attributes
    Configuration *config;

    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;

    Map *map;
    ArrayMovingObject *arr_mv_objs;

public:
    StudyPinkProgram(const string &config_file_path);
    void printMap(ofstream &OUTPUT, int roundSize) const;
    bool isStop() const;
    void printResult() const;
    void printStep(int si) const;
    void run(bool verbose);
    void run(ofstream &OUTPUT);
    ~StudyPinkProgram();
};
