/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2023
 * Author: Vu Van Tien
 * Date: 02.02.2023
 */

// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"
////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;
// addition
class Character;
class Watson;
class Sherlock;

class TestStudyInPink;

enum ItemType
{
    MAGIC_BOOK,
    ENERGY_DRINK,
    FIRST_AID,
    EXEMPTION_CARD,
    PASSING_CARD
};
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
// addition
enum MovingObjectType
{
    SHERLOCK,
    WATSON,
    CRIMINAL,
    ROBOT
};

class MapElement
{
    friend class TestStudyPink;

protected:
    ElementType type;

public:
    MapElement(ElementType in_type);
    virtual ~MapElement();
    virtual ElementType getType() const;
};

class Path : public MapElement
{
    friend class TestStudyPink;

public:
    Path();
};

class Wall : public MapElement
{
    friend class TestStudyPink;

public:
    Wall();
};

class FakeWall : public MapElement
{
    friend class TestStudyPink;

private:
    int req_exp;

public:
    FakeWall(int in_req_exp);
    int getReqExp() const;
};

class Map
{
    friend class TestStudyPink;

private:
    int num_rows, num_cols;
    // addition
    MapElement ***map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls);
    ~Map();
    bool isValid(const Position &pos, MovingObject *mv_obj) const;
    int getNumRows() const;
    int getNumCols() const;
    ElementType getElementType(int i, int j) const;
    MapElement *getElementAtPosition(const Position &pos) const;

    // bool isValid(const Position pos, MovingObject *mv_obj) const;
};

class Position
{
    friend class TestStudyPink;

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
    bool isEqual(Position pos) const;
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
    std::array<Position, 8> eightDirectionOfRobotSW() const
    {
        std::array<Position, 8> adjacentPositions;
        adjacentPositions[0] = Position(r - 2, c);     // Bên U
        adjacentPositions[1] = Position(r - 1, c + 1); // Bên UR
        adjacentPositions[2] = Position(r, c + 2);     // Bên R
        adjacentPositions[3] = Position(r + 1, c + 1); // Bên DR
        adjacentPositions[4] = Position(r + 2, c);     // Bên D
        adjacentPositions[5] = Position(r + 1, c - 1); // Bên DL
        adjacentPositions[6] = Position(r, c - 2);     // Bên L
        adjacentPositions[7] = Position(r - 1, c - 1); // Bên LU
        return adjacentPositions;
    }
};

class MovingObject
{
    friend class TestStudyPink;

protected:
    int index;
    Position pos;
    Map *map;
    string name;

public:
    MovingObject(int index, const Position pos, Map *map, const string &name = "");
    virtual ~MovingObject() {};
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
    // addition
    virtual MovingObjectType getObjectType() const = 0;
};

class Character : public MovingObject
{
    friend class TestStudyPink;

public:
    Character(int index, const Position pos, Map *map, const string &name = "");
    // addition
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual MovingObjectType getObjectType() const = 0;
};

class Sherlock : public Character
{
    friend class TestStudyPink;

private:
    // TODO
    int hp, exp;
    // addition
    string moving_rule;
    int index_moving_rule;
    BaseBag *bag;

public:
    Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);
    Position getNextPosition();
    void move();
    string str() const;
    // addition
    MovingObjectType getObjectType() const;
    BaseBag *getBag() const;
    int getHP() const;
    int getEXP() const;
    void setHP(int hp);
    void setEXP(int exp);
    void setPos(Position pos);
    bool meet(RobotS *robotS);
    bool meet(RobotW *robotW);
    bool meet(RobotSW *robotSW);
    bool meet(RobotC *robotC);
    bool meet(Watson *watson);
    ~Sherlock() {}
};

class Watson : public Character
{
    friend class TestStudyPink;

private:
    int hp, exp;
    // addition
    string moving_rule;
    int index_moving_rule;
    BaseBag *bag;

public:
    Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);
    Position getNextPosition();
    void move();
    string str() const;
    // addition
    MovingObjectType getObjectType() const;
    BaseBag *getBag() const;
    int getHP() const;
    int getEXP() const;
    void setHP(int hp);
    void setEXP(int exp);
    bool meet(RobotS *robotS);
    bool meet(RobotW *robotW);
    bool meet(RobotSW *robotSW);
    bool meet(RobotC *robotC);
    bool meet(Sherlock *sherlock);
    ~Watson() {};
};

class Criminal : public Character
{
    friend class TestStudyPink;

private:
    // TODO
    Sherlock *sherlock;
    Watson *watson;
    // addition
    int count;
    Position prev_pos;

public:
    Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson);
    Position getNextPosition();
    Position getPrevPos()
    {
        return this->prev_pos;
    }
    void move();
    int getCount() const;
    string str() const;
    // addition
    int manhattanDistance(const Position &pos1, const Position &pos2) const;
    MovingObjectType getObjectType() const;

    bool isCreatedRobotNext() const
    {
        if (this->count % 3 == 0 && this->count != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class ArrayMovingObject
{
    friend class TestStudyPink;

private:
    // TODO
    MovingObject **arr_mv_objs;
    int count;
    int capacity;

public:
    ArrayMovingObject(int capacity);
    ~ArrayMovingObject();
    bool isFull() const;
    bool add(MovingObject *mv_obj);
    string str() const;
    // addition
    bool checkMeet(int index) const;
    MovingObject *get(int index) const;
    int size() const;
};

class Configuration
{
    friend class TestStudyPink;
    friend class StudyPinkProgram;

private:
    // TODO
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

// Robot, BaseItem, BaseBag,...
class Robot : public MovingObject
{
    friend class TestStudyPink;

protected:
    RobotType robot_type;
    BaseItem *item;
    Criminal *criminal;
    Position posHead;

public:
    Robot(int index,
          const Position &pos,
          Map *map,
          Criminal *criminal,
          const string &name = "");
    MovingObjectType getObjectType() const;
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;

    virtual RobotType getType() const
    {
        return this->robot_type;
    }

    // addition
    static Robot *create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson);
    virtual int getDistance() const
    {
        return 0;
    }
    BaseItem *NewItem();
    ~Robot() {};
};

class RobotC : public Robot
{
    friend class TestStudyPink;

private:
public:
    RobotC(int index,
           const Position &init_pos,
           Map *map,
           Criminal *criminal);
    Position getNextPosition();
    void move();
    int getDistance(Sherlock *sherlock);
    int getDistance(Watson *watson);
    string str() const;
    // addition
    RobotType getType() const;

    Position getCriminalPosition()
    {
        return this->criminal->getCurrentPosition();
    }
};

class RobotS : public Robot
{
    friend class TestStudyPink;

private:
    Sherlock *sherlock;

public:
    RobotS(int index,
           const Position &init_pos,
           Map *map,
           Criminal *criminal,
           Sherlock *sherlock);

    Position getNextPosition();
    void move();
    int getDistance() const;
    string str() const;
    // addition
    RobotType getType() const;
};

class RobotW : public Robot
{
    friend class TestStudyPink;

private:
    Watson *watson;

public:
    RobotW(int index,
           const Position &init_pos,
           Map *map,
           Criminal *criminal,
           Watson *watson);
    Position getNextPosition();
    void move();
    int getDistance() const;
    string str() const;
    // addition
    RobotType getType() const;
};

class RobotSW : public Robot
{
    friend class TestStudyPink;

private:
    Sherlock *sherlock;
    Watson *watson;

public:
    RobotSW(int index,
            const Position &init_pos,
            Map *map,
            Criminal *criminal,
            Sherlock *sherlock,
            Watson *watson);

    Position getNextPosition();
    string str() const;
    int getDistance() const;
    void move();
    // addition
    RobotType getType() const;
};

class BaseItem
{
    friend class TestStudyPink;

public:
    virtual bool canUse(Character *obj, Robot *robot) = 0;
    virtual void use(Character *obj, Robot *robot) = 0;
    // addition
    BaseItem()
    {
    }
    virtual ItemType getType() const = 0;
    virtual string str() const = 0;
    ~BaseItem() {}
};

class MagicBook : public BaseItem
{
    friend class TestStudyPink;

public:
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    // addition
    ItemType getType() const;
    string str() const;
};

class EnergyDrink : public BaseItem
{
    friend class TestStudyPink;

public:
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    // addition
    ItemType getType() const;
    string str() const;
};

class FirstAid : public BaseItem
{
    friend class TestStudyPink;

public:
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    // addition
    ItemType getType() const;
    string str() const;
};

class ExcemptionCard : public BaseItem
{
    friend class TestStudyPink;

public:
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    // addition
    ItemType getType() const;
    string str() const;
};

class PassingCard : public BaseItem
{
    friend class TestStudyPink;

private:
    string challenge;

public:
    PassingCard(int i, int j);
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    void setChallenge(string challenge);
    // addition
    ItemType getType() const;
    string str() const;
};

class BaseBag
{
    friend class TestStudyPink;

protected:
    // addition
    class Node
    {
    public:
        BaseItem *item;
        Node *next;

    public:
        Node(BaseItem *item, Node *next = nullptr) : item(item), next(next) {}
    };

protected:
    Character *obj;
    // addition
    int size;
    int capacity;
    Node *head;

public:
    virtual bool insert(BaseItem *item);
    virtual BaseItem *get()
    {

        if (obj->getObjectType() == SHERLOCK)
        {
            Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
            if (head == nullptr)
            {
                return nullptr;
            }

            Node *current = head;
            Node *prev = nullptr;

            while (current != nullptr)
            {
                if (current->item->getType() != EXEMPTION_CARD && current->item->getType() != PASSING_CARD &&
                    current->item->canUse(sherlock, nullptr))
                {
                    break;
                }
                prev = current;
                current = current->next;
            }
            // If no usable item is found, return nullptr
            if (current == nullptr)
            {
                return nullptr;
            }
            // Swap the found node with the head node if it is not already the head
            if (current != head)
            {
                if (prev != nullptr)
                {
                    prev->next = head;
                }
                Node *temp = head->next;
                head->next = current->next;
                current->next = temp;
                std::swap(head, current);
            }
            // Now head is the node containing the item to be removed
            BaseItem *returnItem = head->item;
            Node *temp = head;
            head = head->next;
            delete temp;
            size--;

            return returnItem;
        }
        else if (obj->getObjectType() == WATSON)
        {
            Watson *watson = dynamic_cast<Watson *>(obj);
            if (head == nullptr)
            {
                return nullptr;
            }

            Node *current = head;
            Node *prev = nullptr;

            while (current != nullptr)
            {
                if (current->item->getType() != EXEMPTION_CARD && current->item->getType() != PASSING_CARD &&
                    current->item->canUse(watson, nullptr))
                {
                    break;
                }
                prev = current;
                current = current->next;
            }
            if (current == nullptr)
            {
                return nullptr;
            }
            if (current != head)
            {
                if (prev != nullptr)
                {
                    prev->next = head;
                }
                Node *temp = head->next;
                head->next = current->next;
                current->next = temp;
                std::swap(head, current);
            }
            BaseItem *returnItem = head->item;
            Node *temp = head;
            head = head->next;
            delete temp;
            size--;
            return returnItem;
        }
        return nullptr;
    }

    virtual BaseItem *get(ItemType itemType);
    virtual string str() const;

    // addition
    BaseBag(int capacity);
    virtual ~BaseBag();
    bool checkItem(ItemType itemType);
    bool isFull() const
    {
        return (size == capacity);
    }
};
// addition
class SherlockBag : public BaseBag
{
    friend class TestStudyPink;

private:
    Sherlock *sherlock;

public:
    SherlockBag(Sherlock *character)
        : BaseBag(13),
          sherlock(character)
    {
    }
    BaseItem *get();
};
// addition
class WatsonBag : public BaseBag
{
    friend class TestStudyPink;

private:
    Watson *watson;

public:
    WatsonBag(Watson *character)
        : BaseBag(15),
          watson(character)
    {
    }
    BaseItem *get();
};

class StudyPinkProgram
{
    friend class TestStudyPink;

private:
    // Sample attributes
    Configuration *config;
    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;
    Map *map;
    ArrayMovingObject *arr_mv_objs;
    // addition
    string outputFile;

public:
    StudyPinkProgram(const string &config_file_path);
    bool isStop() const
    {
        if (this->watson->getHP() == 0 || this->sherlock->getHP() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void printResult() const
    {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Watson caught the criminal" << endl;
        }
        else
        {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const
    {
        cout << "Step: " << setw(4) << setfill('0') << si
             << "--"
             << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }
    void run(bool verbose);
    ~StudyPinkProgram();
    // addition
    void run(bool verbose, ofstream &OUTPUT)
    {
        for (int i = 0; i < this->config->num_steps; i++)
        {

            for (int j = 0; j < arr_mv_objs->size(); j++)
            {
                if (isStop())
                {
                    printResult();
                    return;
                }
                arr_mv_objs->get(j)->move();
                bool stop = arr_mv_objs->checkMeet(j);
                if (stop || this->isStop())
                {
                    printStep(i);
                    printResult();
                    return;
                }
                if (arr_mv_objs->get(j)->getObjectType() == CRIMINAL)
                {
                    if (this->criminal->isCreatedRobotNext())
                    {
                        MovingObject *robot = Robot::create(arr_mv_objs->size(), this->map, this->criminal, this->sherlock, this->watson);
                        arr_mv_objs->add(robot);
                    }
                }
                printStep(i);
            }
        }
        printResult();
    }
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
