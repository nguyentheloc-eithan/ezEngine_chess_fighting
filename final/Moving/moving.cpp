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
    return this->pos;
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
    if (moving_rule.empty())
        return pos;

    char direction = moving_rule[index_moving_rule % moving_rule.size()];

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

    Position next_pos(next_row, next_col);
    if (map->isValid(next_pos, this))
    {
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
    : Character(index, init_pos, map, " ")
{
    this->EXP = init_exp;
    this->HP = init_hp;
    this->moving_rule = moving_rule;
}

Position Watson::getNextPosition()
{

    if (moving_rule.empty())
        return pos;

    char direction = moving_rule[index_moving_rule % moving_rule.size()];

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

    Position next_pos(next_row, next_col);
    if (map->isValid(next_pos, this))
    {
        index_moving_rule++;
        return next_pos;
    }
    else
    {
        return pos;
    }
}

void Watson::move()
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
string Watson::str() const
{
    return "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
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
MapElement *Map::getElementAtPosition(const Position &pos) const
{
    if (pos.getRow() < 0 || pos.getRow() >= num_rows || pos.getCol() < 0 || pos.getCol() >= num_cols)
    {
        return nullptr;
    }

    return map[pos.getRow()][pos.getCol()];
}
/*
 * CLASS: Criminal kế thừa class Character
 */

Criminal::Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson)
    : Character(index, init_pos, map, "CRIMINAL"), sherlock(sherlock), watson(watson)
{
}
Position Criminal::getNextPosition()
{
    vector<char> directions = {'U', 'L', 'D', 'R'};
    Position nextPos = pos;
    int maxDistance = INT_MIN;
    char bestDirection = '\0'; // Initialize with null character

    // Iterate through all possible directions
    for (char direction : directions)
    {
        int nextRow = pos.getRow();
        int nextCol = pos.getCol();

        // Calculate the next position based on the current direction
        switch (direction)
        {
        case 'U':
            nextRow--;
            break;
        case 'L':
            nextCol--;
            break;
        case 'D':
            nextRow++;
            break;
        case 'R':
            nextCol++;
            break;
        }

        Position newPos(nextRow, nextCol);

        // Check if the new position is valid
        if (map->isValid(newPos, this))
        {
            // Calculate the Manhattan distance to both Sherlock and Watson
            int distanceToSherlock = abs(newPos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(newPos.getCol() - sherlock->getCurrentPosition().getCol());
            int distanceToWatson = abs(newPos.getRow() - watson->getCurrentPosition().getRow()) + abs(newPos.getCol() - watson->getCurrentPosition().getCol());
            int totalDistance = distanceToSherlock + distanceToWatson;

            // Update the next position if the total distance is greater than the current maximum
            if (totalDistance > maxDistance || (totalDistance == maxDistance && direction < bestDirection))
            {
                maxDistance = totalDistance;
                nextPos = newPos;
                bestDirection = direction;
            }
        }
    }

    return nextPos;
}

void Criminal::move()
{
    Position nextPos = getNextPosition();

    // Check if the next position is valid
    if (map->isValid(nextPos, this))
    {
        // Move to the next position
        pos = nextPos;
    }
}

string Criminal::str() const
{
    return "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
}

MovingObjectType Criminal::getObjectType() const
{
    return CRIMINAL;
}
int Criminal::getCount() const
{
    return this->count;
}
bool Criminal::isCreatedRobotNext() const
{
    return (count > 0 && count % 3 == 0);
}
int Criminal::manhattanDistance(const Position &pos1, const Position &pos2) const
{
    // Tính khoảng cách Manhattan giữa hai vị trí
    int distance = abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
    return distance;
}

/*
 * CLASS: Robot kế thừa class MovingObject
 */
Robot::Robot(int index, const Position &pos, Map *map, RobotType robot_type, Criminal *criminal, const string &name)
    : MovingObject(index, pos, map, name), robot_type(robot_type), criminal(criminal)
{
    // Constructor body
}
Robot *Robot::create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson)
{
    // Check if this is the first robot created on the map
    if (index == 0)
    {
        // Create RobotC
        return new RobotC(index, criminal->getCurrentPosition(), map, C, criminal);
    }
    else
    {
        // Calculate distances to Sherlock and Watson manually
        int criminalRow = criminal->getCurrentPosition().getRow();
        int criminalCol = criminal->getCurrentPosition().getCol();
        int sherlockRow = sherlock->getCurrentPosition().getRow();
        int sherlockCol = sherlock->getCurrentPosition().getCol();
        int watsonRow = watson->getCurrentPosition().getRow();
        int watsonCol = watson->getCurrentPosition().getCol();

        // Calculate Manhattan distances
        int distanceToSherlock = abs(criminalRow - sherlockRow) + abs(criminalCol - sherlockCol);
        int distanceToWatson = abs(criminalRow - watsonRow) + abs(criminalCol - watsonCol);

        // Compare distances and create appropriate type of robot
        if (distanceToSherlock < distanceToWatson)
        {
            // Create RobotS
            return new RobotS(index, criminal->getCurrentPosition(), map, S, criminal, sherlock);
        }
        else if (distanceToSherlock > distanceToWatson)
        {
            // Create RobotW
            return new RobotW(index, criminal->getCurrentPosition(), map, W, criminal, watson);
        }
        else
        {
            // Create RobotSW
            return new RobotSW(index, criminal->getCurrentPosition(), map, SW, criminal, sherlock, watson);
        }
    }
}

MovingObjectType Robot::getObjectType() const
{
    return ROBOT;
}
/*
 *CLASS: RobotC kế thừa class Robot
 */
RobotC::RobotC(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal)
    : Robot(index, init_pos, map, robot_type, criminal)
{
    // Initialize any additional attributes specific to RobotC
    // OPTIONAL: Initialize nextPosition attribute with the next position of the criminal
    // For example:
    // nextPosition = criminal->getNextPosition();
}
int RobotC::getDistance(Sherlock *sherlock)
{
    // Get the current position of Sherlock
    int sherlockRow = sherlock->getCurrentPosition().getRow();
    int sherlockCol = sherlock->getCurrentPosition().getCol();
    int distanceToSherlock = abs(pos.getRow() - sherlockRow) + abs(pos.getCol() - sherlockCol);
    return distanceToSherlock;
}

int RobotC::getDistance(Watson *watson)
{
    // Get the current position of Watson
    Position sherlockPos = watson->getCurrentPosition();
    int watsonRow = watson->getCurrentPosition().getRow();
    int watsonCol = watson->getCurrentPosition().getCol();
    int distanceToWatson = abs(pos.getRow() - watsonRow) + abs(pos.getCol() - watsonCol);
    return distanceToWatson;
}

Position RobotC::getNextPosition()
{
    Position criminalPos = criminal->getCurrentPosition();

    // Trả về vị trí của tội phạm làm vị trí tiếp theo cho robot
    return criminalPos;
}
void RobotC::move()
{
    // Lấy vị trí tiếp theo
    Position nextPos = getNextPosition();

    // Kiểm tra xem vị trí tiếp theo có hợp lệ không
    if (map->isValid(nextPos, this))
    {
        // Nếu hợp lệ, di chuyển robot đến vị trí mới
        pos = nextPos;
    }
}
string RobotC::str() const
{
    Position robotPos = getCurrentPosition();

    // Tính toán khoảng cách từ robot đến tội phạm
    int distance = criminal->manhattanDistance(robotPos, criminal->getCurrentPosition());

    // Tạo chuỗi mô tả robot
    string description = "Robot[pos=" + robotPos.str() + ";type=C;dist=" + to_string(distance) + "]";
    return description;
}
int RobotC::getDistance() const
{
    return 0;
}
RobotType RobotC::getType() const
{
    return C;
}
/*
 * CLASS: RobotW kế thừa class Robot
 */

RobotW::RobotW(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal, Watson *watson)
    : Robot(index, init_pos, map, robot_type, criminal), // Call base class constructor
      watson(watson)                                     // Initialize Watson pointer member
{
}

Position RobotW::getNextPosition()
{
    vector<char> directions = {'U', 'L', 'D', 'R'};
    Position nextPos = pos;
    int minDistanceToWatson = INT_MAX;
    char bestDirection = '\0'; // Initialize with null character

    // Iterate through all possible directions
    for (char direction : directions)
    {
        int nextRow = pos.getRow();
        int nextCol = pos.getCol();

        // Calculate the next position based on the current direction
        switch (direction)
        {
        case 'U':
            nextRow--;
            break;
        case 'L':
            nextCol--;
            break;
        case 'D':
            nextRow++;
            break;
        case 'R':
            nextCol++;
            break;
        }

        Position newPos(nextRow, nextCol);

        // Check if the new position is valid
        if (map->isValid(newPos, this))
        {
            // Calculate the Manhattan distance to Watson
            int distanceToWatson = abs(newPos.getRow() - watson->getCurrentPosition().getRow()) + abs(newPos.getCol() - watson->getCurrentPosition().getCol());

            // Update the next position if the distance to Watson is minimized
            if (distanceToWatson < minDistanceToWatson || (distanceToWatson == minDistanceToWatson && direction < bestDirection))
            {
                minDistanceToWatson = distanceToWatson;
                nextPos = newPos;
                bestDirection = direction;
            }
        }
    }

    return nextPos;
}

void RobotW::move()
{
    Position nextPos = getNextPosition();
    // Check if the next position is valid
    if (map->isValid(nextPos, this))
    {
        // Move to the next position
        pos = nextPos;
    }
}

string RobotW::str() const
{
    int distanceToWatson = abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());
    return "Robot[pos=" + pos.str() + ";type=W;dist=" + to_string(distanceToWatson) + "]";
}

RobotType RobotW::getType() const
{
    return W;
}

int RobotW::getDistance() const
{
    return abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());
}
/*
 * CLASS: RobotS kế thừa class Robot
 */
RobotS::RobotS(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal, Sherlock *sherlock)
    : Robot(index, init_pos, map, robot_type, criminal),
      sherlock(sherlock)
{
    // Phần khởi tạo cụ thể cho lớp RobotS
}

Position RobotS::getNextPosition()
{
    Position currentPos = getCurrentPosition();

    // Lấy vị trí tiếp theo gần nhất với Sherlock
    Position nextPos;
    int minDistance = std::numeric_limits<int>::max(); // Khởi tạo giá trị khoảng cách tối thiểu
    std::vector<Position> adjacentPositions = currentPos.getAdjacentPositions();

    for (const auto &pos : adjacentPositions)
    {
        if (map->isValid(pos, this)) // Ensure the correct number of arguments
        {
            int distance = criminal->manhattanDistance(pos, sherlock->getCurrentPosition()); // Use the appropriate function to calculate distance
            if (distance < minDistance)
            {
                minDistance = distance;
                nextPos = pos;
            }
        }
    }

    return nextPos;
}
void RobotS::move()
{
    Position nextPos = getNextPosition();
    Position nposTemp = Position(-1, -1);
    if (nextPos.getRow() != nposTemp.getRow() || nextPos.getCol() != nposTemp.getCol())
    {
        setCurrentPosition(nextPos);
    }
}

string RobotS::str() const
{
    return "Robot[pos=" + getCurrentPosition().str() + ";type=S;dist=" + to_string(getDistance()) + "]";
}

RobotType RobotS::getType() const
{
    return RobotType::S;
}

int RobotS::getDistance() const
{
    return criminal->manhattanDistance(getCurrentPosition(), sherlock->getCurrentPosition());
}
/*
 * CLASS: RobotSW kế thừa class Robot
 */
RobotSW::RobotSW(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal, Sherlock *sherlock, Watson *watson)
    : Robot(index, init_pos, map, robot_type, criminal),
      sherlock(sherlock),
      watson(watson)
{
    // Additional initialization for RobotSW
    // You can add more initialization here if needed
}

Position RobotSW::getNextPosition()
{
    vector<char> directions = {'U', 'L', 'D', 'R'};
    Position nextPos = pos;
    int minDistanceToSW = INT_MAX;
    char bestDirection = '\0'; // Initialize with null character

    // Iterate through all possible directions
    for (char direction : directions)
    {
        int nextRow = pos.getRow();
        int nextCol = pos.getCol();

        // Calculate the next position based on the current direction
        switch (direction)
        {
        case 'U':
            nextRow--;
            break;
        case 'L':
            nextCol--;
            break;
        case 'D':
            nextRow++;
            break;
        case 'R':
            nextCol++;
            break;
        }

        Position newPos(nextRow, nextCol);

        // Check if the new position is valid
        if (map->isValid(newPos, this))
        {
            // Calculate the Manhattan distance to both Sherlock and Watson
            int distanceToSherlock = abs(newPos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(newPos.getCol() - sherlock->getCurrentPosition().getCol());
            int distanceToWatson = abs(newPos.getRow() - watson->getCurrentPosition().getRow()) + abs(newPos.getCol() - watson->getCurrentPosition().getCol());
            int totalDistance = distanceToSherlock + distanceToWatson;

            // Update the next position if the total distance is minimized
            if (totalDistance < minDistanceToSW || (totalDistance == minDistanceToSW && direction < bestDirection))
            {
                minDistanceToSW = totalDistance;
                nextPos = newPos;
                bestDirection = direction;
            }
        }
    }

    return nextPos;
}
string RobotSW::str() const
{
    stringstream ss;
    ss << "Robot[pos=" << pos.str() << ";type=SW;dist=" << getDistance() << "]";
    return ss.str();
}
RobotType RobotSW::getType() const
{
    return SW;
}
int RobotSW::getDistance() const
{
    int distanceToSherlock = abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(pos.getCol() - sherlock->getCurrentPosition().getCol());
    int distanceToWatson = abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());

    return distanceToSherlock + distanceToWatson;
}
void RobotSW::move()
{
    // Lấy vị trí hiện tại của Sherlock và Watson
    Position sherlockPos = sherlock->getCurrentPosition();
    Position watsonPos = watson->getCurrentPosition();

    // Tính toán khoảng cách từ vị trí hiện tại của robot đến Sherlock và Watson
    int distanceToSherlock = abs(pos.getRow() - sherlockPos.getRow()) + abs(pos.getCol() - sherlockPos.getCol());
    int distanceToWatson = abs(pos.getRow() - watsonPos.getRow()) + abs(pos.getCol() - watsonPos.getCol());

    // Chọn vị trí mới sao cho tổng khoảng cách là nhỏ nhất
    int minTotalDistance = distanceToSherlock + distanceToWatson;
    Position nextPos = pos;

    // Thử di chuyển lần lượt đến các ô lân cận và chọn ô có tổng khoảng cách nhỏ nhất
    for (const Position &adjPos : pos.getAdjacentPositions())
    {
        int distanceToSherlockNew = abs(adjPos.getRow() - sherlockPos.getRow()) + abs(adjPos.getCol() - sherlockPos.getCol());
        int distanceToWatsonNew = abs(adjPos.getRow() - watsonPos.getRow()) + abs(adjPos.getCol() - watsonPos.getCol());
        int totalDistanceNew = distanceToSherlockNew + distanceToWatsonNew;
        if (totalDistanceNew < minTotalDistance && map->isValid(adjPos, this))
        {
            minTotalDistance = totalDistanceNew;
            nextPos = adjPos;
        }
    }

    // Di chuyển robot đến vị trí mới
    setCurrentPosition(nextPos);
}

/*
 * CLASS: ArrayMovingObject
 */

ArrayMovingObject::ArrayMovingObject(int capacity) : count(0), capacity(capacity), arr_mv_objs(new MovingObject *[capacity])
{
    // Khởi tạo mảng arr_mv_objs về NULL
    for (int i = 0; i < capacity; ++i)
    {
        arr_mv_objs[i] = NULL;
    }
}
ArrayMovingObject::~ArrayMovingObject()
{
    for (int i = 0; i < count; ++i)
    {
        delete arr_mv_objs[i];
    }
    delete[] arr_mv_objs;
}
bool ArrayMovingObject::isFull() const
{
    return count == capacity;
}
bool ArrayMovingObject::add(MovingObject *mv_obj)
{
    // Kiểm tra xem mảng đã đầy chưa
    if (count < capacity)
    {

        arr_mv_objs[count] = mv_obj;

        count++;
        return true; // Trả về true để thông báo rằng việc thêm đối tượng thành công
    }
    else
    {
        return false;
    }
}
MovingObject *ArrayMovingObject::get(int index) const
{
    if (index >= 0 && index < count)
    {
        return arr_mv_objs[index];
    }
    else
    {
        return nullptr;
    }
}

int ArrayMovingObject::size() const
{
    return this->count;
}

string ArrayMovingObject::str() const
{
    stringstream ss;
    ss << "ArrayMovingObject[count=" << count << ";capacity=" << capacity << ";";

    // Liệt kê các đối tượng trong mảng
    for (int i = 0; i < count; i++)
    {
        if (arr_mv_objs[i] != nullptr)
        {
            ss << arr_mv_objs[i]->str() << ";";
        }
    }

    return ss.str();
}
/*
 * CLASS: Configuration
 */
Configuration::Configuration(const string &filepath)
{
    ifstream configFile(filepath); // Open the configuration file
    if (configFile.is_open())      // Check if the file is successfully opened
    {
        string line;
        while (getline(configFile, line))
        {
            string config = getCommand(line);
            string var = getVar(line);

            if (config == "MAP_NUM_ROWS")
            {
                map_num_rows = stoi(var);
            }
            else if (config == "MAP_NUM_COLS")
            {
                map_num_cols = stoi(var);
            }
            else if (config == "MAX_NUM_MOVING_OBJECTS")
            {
                max_num_moving_objects = stoi(var);
            }
            else if (config == "ARRAY_WALLS")
            {
                num_walls = calculatePositions(var);
                extractCoordinates(var, arr_walls, num_walls);
            }
            else if (config == "ARRAY_FAKE_WALLS")
            {
                num_fake_walls = calculatePositions(var);
                extractCoordinates(var, arr_fake_walls, num_fake_walls);
            }
            else if (config == "SHERLOCK_MOVING_RULE")
            {
                sherlock_moving_rule = var;
            }
            else if (config == "SHERLOCK_INIT_POS")
            {
                getInitPos(var, sherlock_init_pos);
            }
            else if (config == "SHERLOCK_INIT_HP")
            {
                sherlock_init_hp = stoi(var);
            }
            else if (config == "SHERLOCK_INIT_EXP")
            {
                sherlock_init_exp = stoi(var);
            }
            else if (config == "WATSON_MOVING_RULE")
            {
                watson_moving_rule = var;
            }
            else if (config == "WATSON_INIT_POS")
            {
                getInitPos(var, watson_init_pos);
            }
            else if (config == "WATSON_INIT_HP")
            {
                watson_init_hp = stoi(var);
            }
            else if (config == "WATSON_INIT_EXP")
            {
                watson_init_exp = stoi(var);
            }
            else if (config == "CRIMINAL_INIT_POS")
            {
                getInitPos(var, criminal_init_pos);
            }
            else if (config == "NUM_STEPS")
            {
                num_steps = stoi(var);
            }
        }
        configFile.close(); // Close the configuration file
    }
}

Configuration::~Configuration()
{
    if (arr_walls != nullptr)
    {
        delete[] arr_walls;
        arr_walls = nullptr;
    }
    if (arr_fake_walls != nullptr)
    {
        delete[] arr_fake_walls;
        arr_fake_walls = nullptr;
    }
}
string Configuration::str() const
{
    ostringstream oss; // Create a string stream to build the output

    oss << "Configuration[" << endl;
    oss << "MAP_NUM_ROWS=" << map_num_rows << endl;
    oss << "MAP_NUM_COLS=" << map_num_cols << endl;
    oss << "MAX_NUM_MOVING_OBJECTS=" << max_num_moving_objects << endl;
    oss << "NUM_WALLS=" << num_walls << endl;
    oss << "ARRAY_WALLS=[";
    for (int i = 0; i < num_walls; ++i)
    {
        oss << "(" << arr_walls[i].getRow() << "," << arr_walls[i].getCol() << ")";
        if (i != num_walls - 1)
            oss << ";";
    }
    oss << "]" << endl;
    oss << "NUM_FAKE_WALLS=" << num_fake_walls << endl;
    oss << "ARRAY_FAKE_WALLS=[";
    for (int i = 0; i < num_fake_walls; ++i)
    {
        oss << "(" << arr_fake_walls[i].getRow() << "," << arr_fake_walls[i].getCol() << ")";
        if (i != num_fake_walls - 1)
            oss << ";";
    }
    oss << "]" << endl;
    oss << "SHERLOCK_MOVING_RULE=" << sherlock_moving_rule << endl;
    oss << "SHERLOCK_INIT_POS=(" << sherlock_init_pos.getRow() << "," << sherlock_init_pos.getCol() << ")" << endl;
    oss << "SHERLOCK_INIT_HP=" << sherlock_init_hp << endl;
    oss << "SHERLOCK_INIT_EXP=" << sherlock_init_exp << endl;
    oss << "WATSON_MOVING_RULE=" << watson_moving_rule << endl;
    oss << "WATSON_INIT_POS=(" << watson_init_pos.getRow() << "," << watson_init_pos.getCol() << ")" << endl;
    oss << "WATSON_INIT_HP=" << watson_init_hp << endl;
    oss << "WATSON_INIT_EXP=" << watson_init_exp << endl;
    oss << "CRIMINAL_INIT_POS=(" << criminal_init_pos.getRow() << "," << criminal_init_pos.getCol() << ")" << endl;
    oss << "NUM_STEPS=" << num_steps << endl;
    oss << "]";

    return oss.str(); // Return the built string
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
    // * Nếu thực hiện hủy toàn bộ trong ArrayMovingObject thì không cần delete criminal, sherlock và watson
    delete map;
    delete config;
    delete arr_mv_objs;
}
void StudyPinkProgram::printMap(ofstream &OUTPUT, int roundSize) const
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
            for (int k = 0; k < roundSize; k++)
            {
                if (arr_mv_objs->get(k)->getCurrentPosition().isEqual(charPos))
                {
                    if (cellValue == "     " || cellValue == "-----" || cellValue == "IIIII")
                        cellValue = "";
                    idx = arr_mv_objs->get(k)->getObjectType();
                    if (idx == 3)
                    {
                        MovingObject *temp = arr_mv_objs->get(k);
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
        OUTPUT << "__________________NEW STEP__________________" << endl;
        MovingObject *robot = nullptr;
        int roundSize = arr_mv_objs->size();
        // cout << "roundSize: " << roundSize << endl;
        for (int i = 0; i < roundSize; ++i)
        {

            OUTPUT << "ROUND : " << istep << " - TURN : " << i << endl;
            stringstream ss(arr_mv_objs->str());
            string lineArr = "";
            getline(ss, lineArr, 'C');
            OUTPUT << lineArr << "]" << endl;
            getline(ss, lineArr, ']');
            OUTPUT << "\tC" << lineArr.substr(1) << "]" << endl;
            while (getline(ss, lineArr, ']'))
            {
                if (lineArr.length() > 1)
                    OUTPUT << "\t" << lineArr.substr(1) << "]" << endl;
            }
            if (i == 0)
                OUTPUT << "Criminal current count : " << criminal->getCount() << endl;
            if (i == 1)
                OUTPUT << "Sherlock move direction : " << config->sherlock_moving_rule[istep % config->sherlock_moving_rule.length()] << endl;
            if (i == 2)
                OUTPUT << "Watson move direction : " << config->watson_moving_rule[istep % config->watson_moving_rule.length()] << endl;

            if (arr_mv_objs->get(i)->getObjectType() == MovingObjectType::CRIMINAL)
            {
                robot = Robot::create(arr_mv_objs->size(), map, criminal, sherlock, watson);
            }
            arr_mv_objs->get(i)->move();
            if (i == 0)
                OUTPUT << "Criminal count after moving : " << criminal->getCount() << endl;

            printMap(OUTPUT, roundSize);
            OUTPUT << "*********************************************************" << endl;
        }
        // if (robot != nullptr)
        // {
        //     if (criminal->getCount() % 3 == 0 && criminal->getCount() > 0)
        //     {
        //         string robotType[4] = {"C", "S", "W", "SW"};
        //         OUTPUT << "Robot " << robotType[dynamic_cast<Robot *>(robot)->getType()] << " has been created" << endl;
        //         arr_mv_objs->add(robot);
        //     }
        //     else
        //     {
        //         // delete robot;
        //     }
        // }
    }
}