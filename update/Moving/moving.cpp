#include "moving.h"
const Position Position::npos = Position(-1, -1);
/*
 * CLASS: MapElement
 */
MapElement::MapElement(ElementType in_type)
{
    this->type = in_type;
}

MapElement::~MapElement() {}

ElementType MapElement::getType() const
{
    return type;
}
/*
 * CLASS: Path
 */
Path::Path()
    : MapElement(PATH) {}
/*
 * CLASS: Wall
 */
Wall::Wall()
    : MapElement(WALL) {}
/*
 * CLASS: FakeWall
 */
FakeWall::FakeWall(int in_req_exp)
    : MapElement(ElementType::FAKE_WALL), req_exp(in_req_exp)
{
}
int FakeWall::getReqExp() const
{
    return this->req_exp;
}
/*
 * CLASS: Position
 */

Position::Position(int r, int c)
{
    this->r = r;
    this->c = c;
}

Position::Position(const string &str_pos)
{
    int r_get, c_get = 0;
    findCoordinates(str_pos, r_get, c_get);
    this->r = r_get;
    this->c = c_get;
}
void Position::findCoordinates(string s, int &x, int &y)
{
    size_t commaPos = s.find(',');
    string xStr = s.substr(1, commaPos - 1);
    string yStr = s.substr(commaPos + 1, s.size() - commaPos - 2);
    x = stoi(xStr);
    y = stoi(yStr);
}
int Position::getRow() const
{
    return this->r;
}
int Position::getCol() const
{
    return this->c;
}
void Position::setRow(int r)
{
    this->r = r;
}
void Position::setCol(int c)
{
    this->c = c;
}
string Position::str() const
{
    string x = to_string(this->r);
    string y = to_string(this->c);
    string result = "(" + x + "," + y + ")";
    return result;
}
bool Position::isEqual(Position position) const
{
    if (this->r == position.getRow() && this->c == position.getCol())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
 * CLASS: MovingObject
 */
MovingObject::MovingObject(int index, const Position pos, Map *map, const string &name)
    : index(index), pos(pos), map(map), name(name)
{
    // Constructor
}

Position MovingObject::getCurrentPosition() const
{
    return pos;
}
/*
 * CLASS: Character kế thừa class MovingObject
 */
Character::Character(int index, const Position pos, Map *map, const string &name)
    : MovingObject(index, pos, map, name)
{
    // Constructor
}
/*
 * CLASS: Sherlock kế thừa class Character
 */

Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "SHERLOCK")
{
    this->moving_rule = moving_rule;
    this->HP = init_hp;
    this->EXP = init_exp;
}

Position Sherlock::getNextPosition()
{
    // TODO: tính vị trí tiếp theo dựa theo nước đi kế tiếp
    if (moving_rule.empty())
        return pos; // Nếu không có, trả về vị trí hiện tại

    // Lấy ký tự tiếp theo trong moving_rule
    char direction = moving_rule[index_moving_rule % moving_rule.size()];

    // Tính vị trí tiếp theo dựa trên direction
    int next_row = pos.getRow();
    int next_col = pos.getCol();

    switch (direction)
    {
    case 'L':
        next_col--;
        break;
    case 'R':
        next_col++;
        break;
    case 'U':
        next_row--;
        break;
    case 'D':
        next_row++;
        break;
    }

    // Kiểm tra xem vị trí tiếp theo có hợp lệ không
    Position next_pos(next_row, next_col);
    if (map->isValid(next_pos, this))
    {
        // Nếu hợp lệ, tăng index_moving_rule lên để lấy ký tự tiếp theo ở lần gọi sau
        index_moving_rule++;
        return next_pos;
    }
    else
    {
        return pos;
    }
}
void Sherlock::move()
{
    Position next_pos = getNextPosition();

    if (!pos.isEqual(next_pos))
    {
        pos = next_pos;

        MapElement *next_element = map->getElementAtPosition(pos);

        if (next_element != nullptr && next_element->getType() == ElementType::FAKE_WALL)
        {
            FakeWall *fakeWall = dynamic_cast<FakeWall *>(next_element);
            int required_exp = fakeWall->getReqExp();

            EXP += required_exp;
        }
    }
}

string Sherlock::str() const
{
    return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}

MovingObjectType Sherlock::getObjectType() const
{
    return SHERLOCK;
}

int Sherlock::getHP() const
{
    return this->HP;
}
int Sherlock::getEXP() const
{
    return this->EXP;
}
void Sherlock::setHP(int hp)
{
    this->HP = hp;
}

void Sherlock::setEXP(int exp)
{
    this->EXP = exp;
}
/*
 * CLASS: Watson kế thừa class Character
 */

Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "WATSON")
{
    this->EXP = init_exp;
    this->HP = init_hp;
    this->moving_rule = moving_rule;
}

Position Watson::getNextPosition()
{
    // TODO: tính vị trí tiếp theo dựa theo nước đi kế tiếp
}

void Watson::move()
{
    // TODO: di chuyển đến vị trí tiếp theo và cập nhật nước đi tiếp theo
}
string Watson::str() const
{
    //  TODO: trả về chuỗi "Watson[index=<index>;pos=<pos>;moving_rule=<moving_rule>]"
}

MovingObjectType Watson::getObjectType() const
{
    return WATSON;
}

int Watson::getHP() const
{
    return this->HP;
}

int Watson::getEXP() const
{
    return this->EXP;
}

void Watson::setHP(int hp)
{

    this->HP = hp;
}

void Watson::setEXP(int exp)
{
    this->EXP = exp;
}
/*
 * CLASS: Map
 */
Map::Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls)
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

Map::~Map()
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

int Map::getNumRows() const
{
    return this->num_rows;
}
int Map::getNumCols() const
{
    return this->num_cols;
}
MapElement *Map::getElementAtPosition(const Position &pos) const
{
    if (pos.getRow() < 0 || pos.getRow() >= num_rows || pos.getCol() < 0 || pos.getCol() >= num_cols)
    {
        return nullptr;
    }

    return map[pos.getRow()][pos.getCol()];
}
ElementType Map::getElementType(int i, int j) const
{
    return map[i][j]->getType();
}
bool Map::isValid(const Position pos, MovingObject *mv_obj) const
{
    if (pos.getRow() < 0 || pos.getRow() >= num_rows || pos.getCol() < 0 || pos.getCol() >= num_cols)
    {
        return false; // Position is outside the matrix
    }

    ElementType elementType = getElementType(pos.getRow(), pos.getCol());

    switch (mv_obj->getObjectType())
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
            Watson *watson = dynamic_cast<Watson *>(mv_obj);
            // Watson can move onto FAKE_WALL if its experience level is sufficient
            FakeWall *fakeWall = dynamic_cast<FakeWall *>(map[pos.getRow()][pos.getCol()]);
            if (fakeWall && watson->getEXP() >= fakeWall->getReqExp())
            {
                return true;
            }
        }
        return false;
    case CRIMINAL:
        return (elementType == PATH || elementType == FAKE_WALL);
    case ROBOT:
        return (elementType == PATH || elementType == FAKE_WALL);
    default:
        return false; // Invalid MovingObject
    }
}
/*
 * CLASS: Criminal kế thừa class Character
 */

Criminal::Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson)
    : Character(index, init_pos, map, "CRIMINAL")
{
    // Call the constructor of the base class Character
}
Position Criminal::getNextPosition()
{
    // TODO: tính vị trí tiếp theo dựa theo nước đi kế tiếp
}
void Criminal::move()
{
    // TODO: di chuyển đến vị trí tiếp theo và cập nhật nước đi tiếp theo
}

string Criminal::str() const
{
    // TODO: trả về chuỗi "Watson[index=<index>;pos=<pos>]"
}

MovingObjectType Criminal::getObjectType() const
{
    // TODO: get
}
int Criminal::getCount() const
{
    // TODO: get
}

/*
 * CLASS: Robot kế thừa class MovingObject
 */
Robot::Robot(int index, const Position &pos, Map *map, RobotType robot_type, Criminal *criminal, const string &name)
    : MovingObject(index, pos, map, name), robot_type(robot_type), criminal(criminal)
{
    // Constructor specific to the Robot class
}
Robot *Robot::create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson)
{
    // TODO: trả về đối tượng class kế thừa từ Robot phù hợp
}
MovingObjectType Robot::getObjectType() const
{
    // TODO: get
}
/*
 *CLASS: RobotC kế thừa class Robot
 */
RobotC::RobotC(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal)
    : Robot(index, init_pos, map, robot_type, criminal, "C")
{
    // Constructor specific to the RobotC class
}

int RobotC::getDistance(Sherlock *sherlock)
{
    // TODO: get
}

int RobotC::getDistance(Watson *watson)
{
    // TODO: get
}
// TODO implement các phương thức getNextPosition, move, str, getType, getDistance
Position RobotC::getNextPosition()
{
    // TODO: tìm vị trí liền sau của Criminal
}
void RobotC::move()
{
    // TODO: di chuyển theo Criminal
}
string RobotC::str() const
{
    // TODO: trả về chuỗi "RobotC[pos=<pos>;type=C;dist=<distance>]"
}
int RobotC::getDistance() const
{
    // TODO: get
}
RobotType RobotC::getType() const
{
    // TODO: get
}
/*
 * CLASS: RobotW kế thừa class Robot
 */

RobotW::RobotW(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal, Watson *watson)
    : Robot(index, init_pos, map, robot_type, criminal, "W"), watson(watson)
{
    // Constructor specific to the RobotW class
}

Position RobotW::getNextPosition()
{
    // TODO: tìm vị trí tiếp theo gần Watson nhất
}

void RobotW::move()
{
    // TODO: di chuyển về phía Watson
}

string RobotW::str() const
{
    // TODO: trả về chuỗi "RobotW[pos=<pos>;type=W;dist=<distance>]"
}

RobotType RobotW::getType() const
{
    // TODO: get
}

int RobotW::getDistance() const
{
    // TODO: get
}
/*
 * CLASS: RobotS kế thừa class Robot
 */
RobotS::RobotS(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal, Sherlock *sherlock)
    : Robot(index, init_pos, map, robot_type, criminal, "S"), sherlock(sherlock)
{
    // Constructor specific to the RobotS class
}

Position RobotS::getNextPosition()
{
    // TODO: tìm vị trí tiếp theo gần Sherlock nhất
}
void RobotS::move()
{
    // TODO: di chuyển về phía Sherlock
}

string RobotS::str() const
{
    // TODO: trả về chuỗi "RobotS[pos=<pos>;type=S;dist=<distance>]"
}

RobotType RobotS::getType() const
{
    // TODO: get
}

int RobotS::getDistance() const
{
    // TODO: get
}
/*
 * CLASS: RobotSW kế thừa class Robot
 */
RobotSW::RobotSW(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal, Sherlock *sherlock, Watson *watson)
    : Robot(index, init_pos, map, robot_type, criminal, "SW"), sherlock(sherlock), watson(watson)
{
    // Constructor specific to the RobotSW class
}

// TODO implement các phương thức getNextPosition, move, str, getType, getDistance
Position RobotSW::getNextPosition()
{
    // TODO: tìm vị trí tổng giá trị khoảng cách Sherlock và Watson nhỏ nhất
}
string RobotSW::str() const
{
    // TODO: trả về chuỗi "RobotS[pos=<pos>;type=S;dist=<distance>]"
}
RobotType RobotSW::getType() const
{
    // TODO: get
}
int RobotSW::getDistance() const
{
    // TODO: get tổng khoảng cách đến Sherlock và Watson
}
void RobotSW::move()
{
    // TODO: di chuyển đến gần cả Sherlock và Watson
}
/*
 * CLASS: ArrayMovingObject
 */

ArrayMovingObject::ArrayMovingObject(int capacity)
{
    // TODO: constructor
}
ArrayMovingObject::~ArrayMovingObject()
{
    // TODO: destructor
}
bool ArrayMovingObject::isFull() const
{
    // TODO: kiểm tra số lượng đối tượng đã đầy hay chưa
}
bool ArrayMovingObject::add(MovingObject *mv_obj)
{
    // TODO: thêm đối tượng mới vào cuối mảng đối tượng
}
MovingObject *ArrayMovingObject::get(int index) const
{
    // TODO: trả về đối tượng có index tương ứng
}

int ArrayMovingObject::size() const
{
    // TODO: trả về số lượng đối tượng trong mảng
}

string ArrayMovingObject::str() const
{
    // TODO: trả về chuỗi biểu diễn mảng
}
/*
 * CLASS: Configuration
 */
Configuration::Configuration(const string &fileName)
{
    //    TODO: constructor

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
                Position *arr_wallsT;                           // Change type to Position*
                extractCoordinates(var, arr_wallsT, num_walls); // Pass as Position* &
                arr_walls = arr_wallsT;
            }
            else if (config == "ARRAY_FAKE_WALLS")
            {
                string var = getVar(tp);
                num_fake_walls = calculatePositions(var);
                Position *arr_fake_walls_temp;                                // Change type to Position*
                extractCoordinates(var, arr_fake_walls_temp, num_fake_walls); // Pass as Position* &
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
                getInitPos(var, sherlock_init_pos);
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
                getInitPos(var, watson_init_pos);
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
                getInitPos(var, criminal_init_pos);
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

Configuration::~Configuration()
{
    // TODO: destructor
}
string Configuration::str() const
{
    // TODO: trả về chuỗi mô tả file
}
/*
 * CLASS: StudyPinkProgram
 */
StudyPinkProgram::StudyPinkProgram(const string &config_file_path)
{
    config = new Configuration(config_file_path);
    map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);
    arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
    sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);

    arr_mv_objs->add(criminal);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
}
StudyPinkProgram::~StudyPinkProgram()
{
    delete map;
    delete config;
    delete arr_mv_objs;
}

void StudyPinkProgram::printMap(ofstream &OUTPUT) const
{
    for (int i = -1; i < config->map_num_cols; i++)
    {
        if (i == -1)
            OUTPUT << setw(5) << ""
                   << "|";
        else
            OUTPUT << setw(5) << i << "|";
    }
    OUTPUT << endl;
    for (int i = 0; i < config->map_num_rows; i++)
    {
        OUTPUT << setw(5) << i << "|";
        for (int j = 0; j < config->map_num_cols; j++)
        {
            int idx = map->getElementType(i, j);
            string nameElement[3] = {"     ", "IIIII", "-----"};
            string nameChar[4] = {"S", "W", "C", "R"};
            string robotName[4] = {"c", "s", "w", "2"};
            string cellValue = nameElement[idx];
            Position charPos(i, j);
            for (int k = 0; k < arr_mv_objs->size(); k++)
            {
                if (arr_mv_objs->get(k)->getCurrentPosition().isEqual(charPos))
                {
                    if (cellValue == "     " || cellValue == "-----" || cellValue == "IIIII")
                        cellValue = "";
                    idx = arr_mv_objs->get(k)->getObjectType();
                    if (idx == 3)
                    {
                        MovingObject *temp = arr_mv_objs->get(k);
                        while (cellValue[cellValue.length() - 1] == ' ')
                        {
                            cellValue = cellValue.substr(0, cellValue.length() - 1);
                        }
                        cellValue += robotName[dynamic_cast<Robot *>(temp)->getType()];
                        continue;
                    }
                    cellValue += nameChar[idx];
                }
            }
            if (!(cellValue == "     " || cellValue == "-----" || cellValue == "IIIII"))
                cellValue = "(" + cellValue + ")";
            OUTPUT << setw(5) << cellValue << "|";
        }
        OUTPUT << endl;
    }
}
void StudyPinkProgram::run(ofstream &OUTPUT)
{
    if (!OUTPUT.is_open())
    {
        cout << "Can't open file" << endl;
        return;
    }
    OUTPUT << config->str() << endl;
    for (int istep = 0; istep < config->num_steps; ++istep)
    {
        for (int i = 0; i < arr_mv_objs->size(); ++i)
        {
            OUTPUT << "*********************************************************" << endl;
            OUTPUT << "ROUND : " << istep << " - TURN : " << i << endl;
            MovingObject *robot = nullptr;
            if (arr_mv_objs->get(i)->getObjectType() == MovingObjectType::CRIMINAL)
            {
                robot = Robot::create(arr_mv_objs->size(), map, criminal, sherlock, watson);
            }
            arr_mv_objs->get(i)->move();
            if (robot != nullptr)
            {
                if (criminal->getCount() % 3 == 0 && criminal->getCount() > 0)
                {
                    arr_mv_objs->add(robot);
                }
                else
                {
                    delete robot;
                }
            }
            printMap(OUTPUT);
        }
    }
}