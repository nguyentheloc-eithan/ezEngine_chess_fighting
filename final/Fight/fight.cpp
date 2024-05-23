#include "fight.h"
// ! Nội dung task cũ cần bỏ vào (chỉ bỏ dòng #include "moving.h")

bool isOdd(int number)
{
    return number % 2 != 0;
}
// *CLASS: MagicBook
ItemType MagicBook::getType() const
{
    return ItemType::MAGIC_BOOK;
}
string MagicBook::str() const
{
    return "MagicBook";
}
bool MagicBook::canUse(Character *obj, Robot *robot)
{
    bool flag = false;
    Position position = obj->getCurrentPosition();
    if (robot == nullptr)
    {
        MovingObjectType ObjectType = obj->getObjectType();
        if (ObjectType == SHERLOCK)
        {
            Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
            if (sherlock->getEXP() <= 350)
            {
                flag = true;
            }
        }
        else if (ObjectType == WATSON)
        {
            Watson *watson = dynamic_cast<Watson *>(obj);
            if (watson->getEXP() <= 350)
            {
                flag = true;
            }
        }
    }
    return flag;
}
void MagicBook::use(Character *obj, Robot *robot)
{
    MovingObjectType ObjectType = obj->getObjectType();
    if (ObjectType == MovingObjectType::SHERLOCK)
    {
        Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
        int newEXP = ceil((sherlock->getEXP() * 125) / 100.0);
        sherlock->setEXP(newEXP);
    }
    else if (ObjectType == MovingObjectType::WATSON)
    {
        Watson *watson = dynamic_cast<Watson *>(obj);
        int newEXP = ceil((watson->getEXP() * 125) / 100.0);
        watson->setEXP(newEXP);
    }
}
// *CLASS: EnergyDrink
ItemType EnergyDrink::getType() const
{
    return ItemType::ENERGY_DRINK;
}
string EnergyDrink::str() const
{
    return "EnergyDrink";
}
bool EnergyDrink::canUse(Character *obj, Robot *robot)
{
    bool flag = false;
    if (robot == nullptr)
    {
        MovingObjectType ObjectType = obj->getObjectType();
        if (ObjectType == SHERLOCK)
        {
            Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
            if (sherlock->getHP() <= 100)
            {
                flag = true;
            }
        }
        else if (ObjectType == WATSON)
        {
            Watson *watson = dynamic_cast<Watson *>(obj);
            if (watson->getHP() <= 100)
            {
                flag = true;
            }
        }
    }
    return flag;
}
void EnergyDrink::use(Character *obj, Robot *robot)
{
    MovingObjectType ObjectType = obj->getObjectType();
    if (ObjectType == MovingObjectType::SHERLOCK)
    {
        Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
        int newHP = ceil((sherlock->getHP() * 120) / 100.0);
        sherlock->setHP(newHP);
    }
    else if (ObjectType == MovingObjectType::WATSON)
    {
        Watson *watson = dynamic_cast<Watson *>(obj);
        int newHP = ceil((watson->getHP() * 120) / 100.0);
        watson->setHP(newHP);
    }
}
// *CLASS: FirstAid
ItemType FirstAid::getType() const
{
    return ItemType::FIRST_AID;
}
string FirstAid::str() const
{
    return "FirstAid";
}
bool FirstAid::canUse(Character *obj, Robot *robot)
{
    bool flag = false;
    if (robot == nullptr)
    {
        MovingObjectType ObjectType = obj->getObjectType();
        if (ObjectType == SHERLOCK)
        {

            Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
            // cout << "SHERLOCK " << sherlock->getHP() << " " << sherlock->getEXP() << endl;

            if (sherlock->getHP() <= 100 || sherlock->getEXP() <= 350)
            {
                flag = true;
            }
        }
        else if (ObjectType == WATSON)
        {
            Watson *watson = dynamic_cast<Watson *>(obj);
            // cout << "WATSON " << watson->getHP() << " " << watson->getEXP() << endl;

            if (watson->getHP() <= 100 || watson->getEXP() <= 350)
            {
                flag = true;
            }
        }
    }
    return flag;
}
void FirstAid::use(Character *obj, Robot *robot)
{
    robot = nullptr;
    MovingObjectType ObjectType = obj->getObjectType();
    if (ObjectType == MovingObjectType::SHERLOCK)
    {
        Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
        int newHP = ceil((sherlock->getHP() * 150) / 100.0);
        sherlock->setHP(newHP);
    }
    else if (ObjectType == MovingObjectType::WATSON)
    {
        Watson *watson = dynamic_cast<Watson *>(obj);
        int newHP = ceil((watson->getHP() * 150) / 100.0);
        watson->setHP(newHP);
    }
}
// *CLASS: ExcemptionCard
ItemType ExcemptionCard::getType() const
{
    return ItemType::EXCEMPTION_CARD;
}
string ExcemptionCard::str() const
{
    return "ExcemptionCard";
}
bool ExcemptionCard::canUse(Character *obj, Robot *robot)
{
    MovingObjectType ObjectType = obj->getObjectType();
    bool flag = false;

    if (ObjectType == MovingObjectType::SHERLOCK)
    {
        Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
        if (robot != NULL)
        {
            if (isOdd(sherlock->getHP()))
            {
                flag = true;
            }
        }
    }

    return flag;
}
void ExcemptionCard::use(Character *obj, Robot *robot)
{
}
// *CLASS: PassingCard
void PassingCard::setChallenge(string challenge)
{
    this->challenge = challenge;
}
PassingCard::PassingCard(int i, int j)
{
    int t = (i * 11 + j) % 4;
    if (t == 0)
    {
        this->setChallenge("RobotS");
    }
    else if (t == 1)
    {
        this->setChallenge("RobotC");
    }
    else if (t == 2)
    {
        this->setChallenge("RobotSW");
    }
    else
    {
        this->setChallenge("all");
    }
}
ItemType PassingCard::getType() const
{
    return ItemType::PASSING_CARD;
}
string PassingCard::str() const
{
    return "PassingCard";
}
bool PassingCard::canUse(Character *obj, Robot *robot)
{
    MovingObjectType ObjectType = obj->getObjectType();
    bool flag = false;

    if (ObjectType == MovingObjectType::WATSON)
    {
        Watson *watson = dynamic_cast<Watson *>(obj);
        if (robot != NULL)
        {
            if (!isOdd(watson->getHP()))
            {
                flag = true;
            }
        }
    }

    return flag;
}
void PassingCard::use(Character *obj, Robot *robot)
{
    int enumChallenge = 0;
    if (this->challenge != "all")
    {
        if (this->challenge == "RobotC")
        {
            enumChallenge = 0;
        }
        else if (this->challenge == "RobotS")
        {
            enumChallenge = 1;
        }
        else if (this->challenge == "RobotW")
        {
            enumChallenge = 2;
        }
        else if (this->challenge == "RobotSW")
        {
            enumChallenge = 3;
        }
        if (enumChallenge != robot->getType())
        {
            MovingObjectType ObjectType = obj->getObjectType();
            if (ObjectType == MovingObjectType::SHERLOCK)
            {
                Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
                int newEXP = (sherlock->getEXP() - 50);
                sherlock->setEXP(newEXP);
            }
            else if (ObjectType == MovingObjectType::WATSON)
            {
                Watson *watson = dynamic_cast<Watson *>(obj);
                int newEXP = (watson->getEXP() - 50);
                watson->setEXP(newEXP);
            }
        }
    }
}
// *CLASS: BaseBag
BaseBag::BaseBag(int capacity)
{
    this->capacity = capacity;
    this->size = 0;
    this->head = nullptr;
}
BaseBag::~BaseBag()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *nextNode = current->next;
        delete current->item;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}
bool BaseBag::insert(BaseItem *item)
{
    if (size >= capacity)
    {
        return false;
    }

    Node *newNode = new Node(item, head);
    head = newNode;
    size++;
    return true;
}

BaseItem *BaseBag::get(ItemType itemType)
{
    // TODO: Tìm và trả về item tương ứng với itemType
    // *Đảo vị trí trong BaseBag (2 cách phổ biến: swap Node hoặc con trỏ item của Node)
    // *Sau đó xóa Node (lưu ý cập nhật con trỏ head)
    if (head == nullptr)
    {
        return nullptr;
    }

    Node *prev = nullptr;
    Node *current = head;

    // Traverse the list to find the node with the specified itemType
    while (current != nullptr && current->item->getType() != itemType)
    {
        prev = current;
        current = current->next;
    }

    // If the item is not found, return nullptr
    if (current == nullptr)
    {
        return nullptr;
    }

    // Swap the found node with the head node
    if (prev != nullptr)
    {
        prev->next = head;          // Previous node points to the head node
        Node *temp = head->next;    // Temporary node to hold head's next node
        head->next = current->next; // Head node points to current's next node
        current->next = temp;       // Current node points to temporary node
        head = current;             // Update the head to the current node
    }

    // Now head is the node containing the item to be removed
    BaseItem *returnItem = head->item;
    Node *temp = head; // Temporary node to hold the current head
    head = head->next; // Update the head to the next node
    delete temp;       // Delete the temporary node
    size--;            // Decrement the size

    return returnItem;
}

string BaseBag::str() const
{
    // *"Bag[count=<thuộc tính size>;<danh sách tên các item cách nhau bởi dấu ,>]"
    stringstream ss;
    ss << "Bag[count=" << size << ";";
    Node *current = head;
    while (current != nullptr)
    {
        ss << current->item->str();
        current = current->next;
        if (current != nullptr)
        {
            ss << ",";
        }
    }
    ss << "]";
    return ss.str();
}
// *CLASS: SherlockBag

BaseItem *SherlockBag::get()
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Node *current = head;
    Node *prev = nullptr;

    // Traverse the list to find a usable item
    while (current != nullptr)
    {
        if (current->item->getType() != EXCEMPTION_CARD && current->item->getType() != PASSING_CARD &&
            current->item->canUse(this->sherlock, nullptr))
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
    Node *temp = head; // Temporary node to hold the current head
    head = head->next; // Update the head to the next node
    delete temp;       // Delete the temporary node
    size--;            // Decrement the size

    return returnItem;
}
// *CLASS: WatsonBag

BaseItem *WatsonBag::get()
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Node *current = head;
    Node *prev = nullptr;

    while (current != nullptr)
    {
        if (current->item->getType() != EXCEMPTION_CARD && current->item->getType() != PASSING_CARD &&
            current->item->canUse(this->watson, nullptr))
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
    Node *temp = head; // Temporary node to hold the current head
    head = head->next; // Update the head to the next node
    delete temp;       // Delete the temporary node
    size--;            // Decrement the size

    return returnItem;
}

//*******************TASK MOVING*********************************************************************************************************/
const Position Position::npos = Position(-1, -1);
int findMaxULDR(int arr[], int size)
{
    if (size <= 0)
    {
        return -1;
    }

    int maxIndex = 0;

    for (int i = 1; i < size; ++i)
    {

        if (arr[i] > arr[maxIndex])
        {
            maxIndex = i;
            // If the next element is smaller than the current max, break the loop
            if (arr[i + 1] < arr[maxIndex])
            {
                break;
            }
        }
    }

    return maxIndex; // Return the index of the maximum element found
}
bool isDivisibleByThree(int num)
{
    return num % 3 == 0;
}
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

// Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
//     : Character(index, init_pos, map, "SHERLOCK")
// {
//     this->index_moving_rule = 0;
//     this->moving_rule = moving_rule;
//     this->HP = init_hp;
//     this->EXP = init_exp;
// }

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
        index_moving_rule++;
        return Position(-1, -1);
    }
}
void Sherlock::move()
{

    Position next_pos = getNextPosition();
    if (map->isValid(next_pos, this))
    {

        // Move to the next position
        pos = next_pos;
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
    int hpMax = hp;
    if (hp > 500)
    {
        hpMax = 500;
    }
    else if (hp < 0)
    {
        hpMax = 0;
    }
    this->HP = hpMax;
}

void Sherlock::setEXP(int exp)
{
    int expMax = exp;
    if (exp > 900)
    {
        expMax = 900;
    }
    else if (exp < 0)
    {
        expMax = 0;
    }
    this->EXP = expMax;
}
/*
 * CLASS: Watson kế thừa class Character
 */

// Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
//     : Character(index, init_pos, map, "WATSON")
// {
//     this->index_moving_rule = 0;
//     this->EXP = init_exp;
//     this->HP = init_hp;
//     this->moving_rule = moving_rule;
// }

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
    if (map->isValid(next_pos, this) == true)
    {
        index_moving_rule++;
        return next_pos;
    }
    else
    {
        index_moving_rule++;
        return Position::npos; // Position(-1,-1)
    }
}

void Watson::move()
{

    Position next_pos = getNextPosition();

    if (map->isValid(next_pos, this) == true)
    {

        // cout << "Moving Pass" << " row_next_pos: " << next_pos.getRow() << " col_next_pos: " << next_pos.getCol() << endl;
        this->pos = next_pos;
        // cout << "Moving Pass" << " row_next_pos: " << this->pos.getRow() << " col_next_pos: " << this->pos.getCol() << endl;
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
    int hpMax = hp;
    if (hp > 500)
    {
        hpMax = 500;
    }
    else if (hp < 0)
    {
        hpMax = 0;
    }
    this->HP = hpMax;
}

void Watson::setEXP(int exp)
{
    int expMax = exp;
    if (exp > 900)
    {
        expMax = 900;
    }
    else if (exp < 0)
    {
        expMax = 0;
    }
    this->EXP = expMax;
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
                int reqNew = (fake_wall_row * 257 + fake_wall_col * 139 + 89) % 900 + 1;
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
    this->count = 0;
}

Position Criminal::getNextPosition()
{
    std::array<Position, 4> adjacentPositions = pos.getAdjacentPositionsULDR();
    int maxDistance = -1;
    Position nextPos = Position::npos;

    // Duyệt qua các vị trí lân cận
    for (const auto &adjPos : adjacentPositions)
    {
        // Kiểm tra tính hợp lệ của vị trí
        if (map->isValid(adjPos, this))
        {
            // Tính toán tổng khoảng cách Manhattan
            int distanceToSherlock = manhattanDistance(adjPos, sherlock->getCurrentPosition());
            int distanceToWatson = manhattanDistance(adjPos, watson->getCurrentPosition());
            int totalDistance = distanceToSherlock + distanceToWatson;

            // Nếu tổng khoảng cách lớn hơn hoặc bằng maxDistance, cập nhật vị trí
            if (totalDistance > maxDistance)
            {
                if (totalDistance > maxDistance)
                {
                    maxDistance = totalDistance;
                    nextPos = adjPos;
                }
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
        count++;
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

int Criminal::manhattanDistance(const Position &pos1, const Position &pos2) const
{
    // Tính khoảng cách Manhattan giữa hai vị trí
    int distance = abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
    return distance;
}

/*
 * CLASS: Robot kế thừa class MovingObject
 */
// constructor move to NEW UNDER
Robot *Robot::create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson)
{
    // Check if this is the first robot created on the map
    if (criminal->getCount() == 2 && index != 0)
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
RobotType Robot::getType()
{
    return this->robot_type;
}
/*
 *CLASS: RobotC kế thừa class Robot
 */
RobotC::RobotC(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal)
    : Robot(index, init_pos, map, robot_type, criminal)
{
    nextPosition = criminal->getNextPosition();
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
    return nextPosition;
}
void RobotC::move()
{
    Position nextPos = getNextPosition();

    if (map->isValid(nextPos, this))
    {
        this->pos = nextPos;
    }
    nextPosition = criminal->getCurrentPosition();
}
string RobotC::str() const
{
    Position robotPos = getCurrentPosition();

    // int distance = criminal->manhattanDistance(robotPos, criminal->getCurrentPosition());

    string description = "Robot[pos=" + robotPos.str() + ";type=C;dist=" + "]";

    return description;
}
int RobotC::getDistance() const
{
    return 0;
}
RobotType RobotC::getType() const
{
    return RobotType::C;
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

    std::array<Position, 4> adjacentPositions = pos.getAdjacentPositions();
    int minDistance = INT_MAX;
    Position nextPos;

    for (const auto &adjPos : adjacentPositions)
    {
        if (map->isValid(adjPos, this))
        {
            int distanceToWatson = criminal->manhattanDistance(adjPos, watson->getCurrentPosition());

            if (distanceToWatson <= minDistance)
            {
                if (distanceToWatson < minDistance)
                {
                    minDistance = distanceToWatson;
                    nextPos = adjPos;
                }
            }
        }
    }

    return nextPos;
}

void RobotW::move()
{
    Position nextPos = getNextPosition();
    if (map->isValid(nextPos, this))
    {
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
    return RobotType::W;
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
    Position nextPos;

    int minDistance = INT_MAX;

    std::array<Position, 4> adjacentPositions = currentPos.getAdjacentPositions();

    for (const auto &pos : adjacentPositions)
    {
        if (map->isValid(pos, this))
        {
            int distance = criminal->manhattanDistance(pos, sherlock->getCurrentPosition());
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
    if (nextPos.getRow() != nposTemp.getRow() && nextPos.getCol() != nposTemp.getCol())
    {
        pos = nextPos;
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
}

Position RobotSW::getNextPosition()
{
    Position sherlockPos = sherlock->getCurrentPosition();
    Position watsonPos = watson->getCurrentPosition();

    int minTotalDistance = INT_MAX;
    Position nextPos = Position::npos;

    for (const Position &adjPos : pos.eightDirectionOfRobotSW())
    {
        if (map->isValid(adjPos, this))
        {
            int distanceToSherlockNew = criminal->manhattanDistance(adjPos, sherlockPos);
            int distanceToWatsonNew = criminal->manhattanDistance(adjPos, watsonPos);

            int totalDistanceNew = distanceToSherlockNew + distanceToWatsonNew;
            if (totalDistanceNew < minTotalDistance)
            {
                minTotalDistance = totalDistanceNew;
                nextPos = adjPos;
            }
        }
    }
    return nextPos;
}
void RobotSW::move()
{

    Position nextPos = getNextPosition();
    if (map->isValid(nextPos, this))
        pos = nextPos;

    // Di chuyển robot đến vị trí mới
}
string RobotSW::str() const
{
    stringstream ss;
    ss << "Robot[pos=" << pos.str() << ";type=SW;dist=" << getDistance() << "]";
    return ss.str();
}
RobotType RobotSW::getType() const
{
    return RobotType::SW;
}
int RobotSW::getDistance() const
{
    int distanceToSherlock = abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(pos.getCol() - sherlock->getCurrentPosition().getCol());
    int distanceToWatson = abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());

    return distanceToSherlock + distanceToWatson;
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
    count = 0;
}
bool ArrayMovingObject::isFull() const
{
    return count == capacity;
}
bool ArrayMovingObject::add(MovingObject *mv_obj)
{

    if (count < capacity)
    {
        arr_mv_objs[count] = mv_obj;
        this->count++;
        return true;
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
    bool isFirstObject = true; // Flag to determine if it's the first object
    for (int i = 0; i < count; i++)
    {
        if (arr_mv_objs[i] != nullptr)
        {
            // Append a semicolon before adding the object details if it's not the first object
            if (!isFirstObject)
            {
                ss << ";";
            }
            ss << arr_mv_objs[i]->str();
            isFirstObject = false; // Update the flag
        }
    }

    ss << "]"; // Close the string with a closing bracket

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

// ! Các mục sửa đổi:
// ! HÀM KHỞI TẠO: Sherlock và Watson thêm thuộc tính bag, Robot thêm thuộc tính để sinh item
// !
Robot::Robot(int index, const Position &pos, Map *map, RobotType robot_type, Criminal *criminal, const string &name)
    : MovingObject(index, pos, map, name), criminal(criminal), robot_type(robot_type), poshead(pos)
{
}
bool BaseBag::checkItem(ItemType itemType)
{
    if (head == nullptr)
    {
        return false;
    }
    bool flag = false;
    Node *current = head;
    while (current != nullptr)
    {
        if (current->item->getType() == itemType)
        {
            flag = true;
            break;
        }
        current = current->next;
    }

    // If the item is not found, return nullptr
    return flag;
}
BaseItem *Robot::NewItem()
{
    int i = this->poshead.getRow();
    int j = this->poshead.getCol();
    int p = i * j;
    // Calculate the dominant number s
    int s = p;
    while (s >= 10)
    {
        int sum = 0;
        while (s > 0)
        {
            sum += s % 10;
            s /= 10;
        }
        s = sum;
    }
    if (s >= 0 && s <= 1)
    {
        return new MagicBook();
    }
    else if (s >= 2 && s <= 3)
    {
        return new EnergyDrink();
    }
    else if (s >= 4 && s <= 5)
    {
        return new FirstAid();
    }
    else if (s >= 6 && s <= 7)
    {
        return new ExcemptionCard();
    }
    else if (s >= 8 && s <= 9)
    {
        return new PassingCard(i, j);
    }
    else
    {
        return nullptr;
    }
}
Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), HP(init_hp), EXP(init_exp), index_moving_rule(0)
{
    this->bag = new SherlockBag(this);
}
Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "Watson"), moving_rule(moving_rule), HP(init_hp), EXP(init_exp), index_moving_rule(0)
{
    this->bag = new WatsonBag(this);
}

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
    stopChecker = false;
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
            OUTPUT << setw(7) << ""
                   << "|";
        else
            OUTPUT << setw(7) << i << "|";
    }
    OUTPUT << endl;
    for (int i = 0; i < config->map_num_rows; i++)
    {
        OUTPUT << setw(7) << i << "|";
        for (int j = 0; j < config->map_num_cols; j++)
        {
            int idx = map->getElementType(i, j);
            string nameElement[3] = {"     ", "IIIII", "-----"};
            string nameChar[4] = {"S", "W", "C", "R"};
            string robotName[4] = {"0", "1", "2", "3"};
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
                cellValue = "" + cellValue + "";
            OUTPUT << setw(7) << cellValue << "|";
        }
        OUTPUT << endl;
    }
}
void StudyPinkProgram::run(ofstream &OUTPUT)
{
    if (!OUTPUT.is_open())
    {
        return;
    }
    OUTPUT << config->str() << endl;
    stopChecker = sherlock->getHP() == 0 || watson->getHP() == 0;
    for (int istep = 0; istep < config->num_steps && !stopChecker; ++istep)
    {
        int roundSize = arr_mv_objs->size();
        for (int i = 0; i < roundSize && !stopChecker; ++i)
        {
            OUTPUT << endl
                   << "*********************************************************" << endl;
            OUTPUT << "ROUND : " << istep << " - TURN : " << i << endl;
            stringstream ss(arr_mv_objs->str());
            string lineArr = "";
            getline(ss, lineArr, 'C');
            OUTPUT << lineArr << "]" << endl;
            getline(ss, lineArr, ']');
            OUTPUT << "\tC" << lineArr << "]" << endl;
            while (getline(ss, lineArr, ']'))
            {
                if (lineArr.length() > 0)
                    OUTPUT << "\t" << lineArr.substr(1) << "]" << endl;
            }
            if (i == 0)
                OUTPUT << "Criminal current count : " << criminal->getCount() << endl;
            if (i == 1)
                OUTPUT << "Sherlock move direction : " << config->sherlock_moving_rule[istep % config->sherlock_moving_rule.length()] << endl;
            if (i == 2)
                OUTPUT << "Watson move direction : " << config->watson_moving_rule[istep % config->watson_moving_rule.length()] << endl;
            if (arr_mv_objs->get(i)->getObjectType() == ROBOT)
            {
                BaseItem *item = dynamic_cast<Robot *>(arr_mv_objs->get(i))->NewItem();
                if (item)
                {
                    OUTPUT << "Robot holding item : " << item->str() << endl;
                    // delete item;
                }
            }
            MovingObject *robot = nullptr;
            if (arr_mv_objs->get(i)->getObjectType() == MovingObjectType::CRIMINAL)
            {
                robot = Robot::create(arr_mv_objs->size(), map, criminal, sherlock, watson);
            }
            arr_mv_objs->get(i)->move();
            stopChecker = arr_mv_objs->checkMeet(i);
            if (i == 0)
                OUTPUT << "Criminal count after moving : " << criminal->getCount() << endl;
            if (robot != nullptr)
            {
                if (criminal->getCount() % 3 == 0 && criminal->getCount() > 0)
                {
                    arr_mv_objs->add(robot);
                }
                else
                {
                    // delete robot;
                }
            }
            printMap(OUTPUT);
            OUTPUT << "---------------" << endl
                   << "LOG AFTER MOVE : " << endl
                   << "Sherlock HP_" << sherlock->getHP() << " EXP_" << sherlock->getEXP() << endl
                   << "Watson HP_" << watson->getHP() << " EXP_" << watson->getEXP() << endl
                   << "SherlockBag : " << sherlock->getBag()->str() << endl
                   << "WatsonBag : " << watson->getBag()->str() << endl;
        }
    }
    OUTPUT << "---------------" << endl
           << "RESULT : ";

    if (watson->getHP() == 0)
        OUTPUT << "Watson can not continue the journey";
    else if (sherlock->getHP() == 0)
        OUTPUT << "Sherlock can not continue the journey";
    else if (stopChecker)
        OUTPUT << "The Criminal was caught";
    else
        OUTPUT << "The Criminal escaped";
}
// *------------------------------------------------------------------
// *
// *------------------------------------------------------------------
// !-----------------------------------
// ! Lưu ý về việc xét thông số khi tăng giảm
// ! Các thay đổi thông số là dựa trên thông số hiện tại
// ! Các thông số không phải số nguyên THỰC HIỆN LÀM TRÒN LÊN -> NHÂN VẬT CHỈ HI SINH KHI INIT HP = 0
// !-----------------------------------

// *CLASS: ArrayMovingObject
bool ArrayMovingObject::checkMeet(int index)
{

    MovingObject *objAtIndex = arr_mv_objs[index];
    Position posAtIndex = objAtIndex->getCurrentPosition();

    for (int i = 0; i < count; ++i)
    {
        if (i == index)
            continue;

        MovingObject *otherObj = arr_mv_objs[i];
        Position otherPos = otherObj->getCurrentPosition();

        if (posAtIndex.isEqual(otherPos))
        {
            MovingObjectType typeAtIndex = objAtIndex->getObjectType();
            MovingObjectType otherType = otherObj->getObjectType();

            switch (typeAtIndex)
            {
            case SHERLOCK:
                if (otherType == ROBOT)
                {
                    Robot *robot = dynamic_cast<Robot *>(otherObj);
                    if (robot->getType() == C && dynamic_cast<Sherlock *>(objAtIndex)->meet(dynamic_cast<RobotC *>(robot)))
                    {
                        return true;
                    }
                    return false;
                }
                else if (otherType == WATSON)
                {
                    Sherlock *sherlock = dynamic_cast<Sherlock *>(objAtIndex);
                    Watson *watson = dynamic_cast<Watson *>(otherObj);
                    BaseBag *tempBag = sherlock->getBag();

                    sherlock->setBag(watson->getBag());
                    watson->setBag(tempBag);
                    return false;
                }
                else if (otherType == CRIMINAL)
                {
                    return true;
                }
                break;
            case WATSON:
                if (otherType == ROBOT)
                {
                    Robot *robot = dynamic_cast<Robot *>(otherObj);
                    return false;
                }
                else if (otherType == SHERLOCK)
                {
                    Watson *watson = dynamic_cast<Watson *>(objAtIndex);
                    Sherlock *sherlock = dynamic_cast<Sherlock *>(otherObj);
                    BaseBag *tempBag = watson->getBag();
                    watson->setBag(sherlock->getBag());
                    sherlock->setBag(tempBag);
                    return false;
                }
                else if (otherType == CRIMINAL)
                {
                    return true;
                }
                break;
            case CRIMINAL:
                if (otherType == ROBOT)
                {
                    return false;
                }
                else if (otherType == SHERLOCK || otherType == WATSON)
                {
                    return true;
                }
                break;
            case ROBOT:
                if (otherType == ROBOT)
                {
                    return false;
                }
                else if (otherType == SHERLOCK)
                {
                    Robot *robot = dynamic_cast<Robot *>(objAtIndex);
                    if (robot->getType() == C && dynamic_cast<Sherlock *>(otherObj)->meet(dynamic_cast<RobotC *>(robot)))
                    {
                        return true;
                    }
                    return false;
                }
                else if (otherType == WATSON)
                {
                    return false;
                }
                else if (otherType == CRIMINAL)
                {
                    return false;
                }
                break;
            }
        }
    }

    return false;
}
// *CLASS: Sherlock
// ! Lưu ý: ExcemptionCard được dùng để BỎ QUA nếu THỬ THÁCH THẤT BẠI -> xem như không thực hiện thử thách -> không gọi get lần 2
// ! Thực hiện get từ bag sau khi insert item
void Sherlock::setPos(Position pos)
{
    this->pos = pos;
}
bool Sherlock::meet(RobotS *robotS)
{
    if (EXP > 400)
    {
        BaseItem *item = robotS->NewItem();
        if (item)
        {
            bag->insert(item);
        }
        return true;
    }
    else
    {
        // Sherlock loses 10% EXP or uses ExcemptionCard if available
        BaseItem *excemptionCard = bag->get(ItemType::EXCEMPTION_CARD);
        if (excemptionCard)
        {
            excemptionCard->use(this, robotS);
            return true;
        }
        else
        {
            int lostExp = ceil((EXP * 10) / 100.0);
            EXP -= lostExp;
            BaseItem *anotherItem = bag->get();
            while (anotherItem)
            {
                if (anotherItem->canUse(this, robotS))
                {
                    anotherItem->use(this, robotS);
                    return true;
                }
                anotherItem = bag->get();
            }
            return false;
        }
    }
}
bool Sherlock::meet(RobotW *robotW)
{
    BaseItem *item = robotW->NewItem();
    if (item)
    {
        bag->insert(item);
    }
    return true;
}
bool Sherlock::meet(RobotSW *robotSW)
{
    if (EXP > 300 && HP > 335)
    {
        BaseItem *item = robotSW->NewItem();
        if (item)
        {
            bag->insert(item);
        }
        return true;
    }
    else
    {
        HP = HP - ceil((HP * 15) / 100);
        EXP = ceil((EXP * 15) / 100);
        return false;
    }
}
bool Sherlock::meet(RobotC *robotC)
{
    if (EXP > 500)
    {
        return true;
    }
    else
    {
        BaseItem *item = robotC->NewItem();
        if (item)
        {
            bag->insert(item);
        }
        return false;
    }
}
bool Sherlock::meet(Watson *watson)
{
    SherlockBag *sherlockBag = dynamic_cast<SherlockBag *>(this->bag);
    WatsonBag *watsonBag = dynamic_cast<WatsonBag *>(watson->getBag());

    bool exchanged = false;
    while (sherlockBag->checkItem(PASSING_CARD))
    {
        BaseItem *passingCard = this->bag->get(PASSING_CARD); // PASSING_CARD
        if (passingCard != nullptr)
        {
            watsonBag->insert(passingCard);
            exchanged = true;
        }
    }

    // Then, Watson gives ExcemptionCards to Sherlock
    while (watsonBag->checkItem(EXCEMPTION_CARD))
    {
        BaseItem *excemptionCard = watson->getBag()->get(EXCEMPTION_CARD); // EXCEMPTION_CARD
        if (excemptionCard != nullptr)
        {
            sherlockBag->insert(excemptionCard);
            exchanged = true;
        }
    }

    return exchanged;
}
// *CLASS: Watson
// ! Lưu ý: PassingCard được dùng khi GẶP ROBOT để bỏ qua thử thách nếu đúng loại thẻ
// ! Thực hiện get từ bag sau khi insert item
bool Watson::meet(RobotS *robotS)
{
    BaseItem *passingCard = getBag()->get(ItemType::PASSING_CARD);
    if (passingCard && passingCard->canUse(this, robotS))
    {
        passingCard->use(this, robotS);
    }
    return true;
}
bool Watson::meet(RobotW *robotW)
{
    BaseItem *passingCard = getBag()->get(ItemType::PASSING_CARD);
    if (passingCard && passingCard->canUse(this, robotW))
    {
        passingCard->use(this, robotW);
        return true;
    }

    // Watson needs to battle RobotW
    if (this->getHP() > 350)
    {
        getBag()->insert(robotW->NewItem());
    }
    else
    {
        int newHP = this->getHP() - (ceil((this->getHP() * 5) / 100));
        this->setHP(newHP);
        for (int i = 0; i < getBag()->getSize(); ++i)
        {
            BaseItem *item = getBag()->get();
            if (item && item->canUse(this, robotW))
            {
                item->use(this, robotW);
                break;
            }
        }
    }

    return true;
}
bool Watson::meet(RobotSW *robotSW)
{
    // TODO: Xử lý trao đổi khi gặp robot SW
    BaseItem *passingCard = getBag()->get(ItemType::PASSING_CARD);
    if (passingCard && passingCard->canUse(this, robotSW))
    {
        passingCard->use(this, robotSW);

        return true;
    }

    if (this->getEXP() > 600 && this->getHP() > 165)
    {
        getBag()->insert(robotSW->NewItem());
    }
    else
    {
        // Watson loses and his HP and EXP are reduced by 15%
        this->setHP(this->getHP() - ceil((this->getHP() * 15) / 100));
        this->setEXP(this->getEXP() - ceil((this->getEXP() * 15) / 100));

        for (int i = 0; i < getBag()->getSize(); ++i)
        {
            BaseItem *item = getBag()->get();
            if (item && item->canUse(this, robotSW))
            {
                item->use(this, robotSW);

                break;
            }
        }
    }

    return true;
}
bool Watson::meet(RobotC *robotC)
{
    // TODO: Xử lý trao đổi khi gặp robot C
    BaseItem *passingCard = getBag()->get(ItemType::PASSING_CARD);
    if (passingCard && passingCard->canUse(this, robotC))
    {
        passingCard->use(this, robotC);
        return true;
    }

    // Watson defeats RobotC and receives the item
    getBag()->insert(robotC->NewItem());

    return true;
}
bool Watson::meet(Sherlock *sherlock)
{
    // TODO: Xử lý trao đổi khi gặp Sherlock

    SherlockBag *sherlockBag = dynamic_cast<SherlockBag *>(sherlock->getBag());
    WatsonBag *watsonBag = dynamic_cast<WatsonBag *>(this->bag);

    bool exchanged = false;
    while (sherlockBag->checkItem(PASSING_CARD))
    {
        BaseItem *passingCard = sherlock->getBag()->get(PASSING_CARD); // PASSING_CARD
        if (passingCard != nullptr)
        {
            watsonBag->insert(passingCard);
            exchanged = true;
        }
    }

    // Then, Watson gives ExcemptionCards to Sherlock
    while (watsonBag->checkItem(EXCEMPTION_CARD))
    {
        BaseItem *excemptionCard = this->bag->get(EXCEMPTION_CARD); // EXCEMPTION_CARD
        if (excemptionCard != nullptr)
        {
            sherlockBag->insert(excemptionCard);
            exchanged = true;
        }
    }

    return exchanged;
}

BaseBag *Sherlock::getBag() const
{
    // TODO: get bag
    return this->bag;
}
BaseBag *Watson::getBag() const
{
    // TODO: get bag
    return this->bag;
}