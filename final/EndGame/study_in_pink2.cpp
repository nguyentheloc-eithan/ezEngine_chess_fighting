// TODO:
// Chỉnh lại di chuyển của RobotC (gợi ý: thực hiện hàm getPrevPosition cho Criminal)
// Mô tả về các meet thay đổi (đã được confirm 90%)
// File study_in_pink2.h những phần trước "addition" là gốc của đề (không thay đổi)
// Chỉnh tên thuộc tính hp và exp của Sherlock và Watson
// Position có nạp chồng 2 hàm isEqual
// isStop kiểm tra vị trí Sherlock, Watson với Criminal và hp của Sherlock, Watson
// Hàm run chú ý chỉnh từ hàm run() gốc (vị trí gọi printResult và printStep)
// Hàm move của Sherlock và Watson khi exp == 0 sẽ không thực hiện gì
// NOTE:
// chú ý các phần addition nên sửa đổi để tránh đạo code
// nộp Bkel cần xóa đổi lại 2 hàm printResult và printStep gốc, xóa thuộc tính outputFile

#include "study_in_pink2.h"

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
        int newEXP = ceil((sherlock->getEXP() * 1.25) - 0.001);
        sherlock->setEXP(newEXP);
    }
    else if (ObjectType == MovingObjectType::WATSON)
    {
        Watson *watson = dynamic_cast<Watson *>(obj);
        int newEXP = ceil((watson->getEXP() * 1.25) - 0.001);
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
        int newHP = ceil((sherlock->getHP() * 1.2) - 0.001);
        sherlock->setHP(newHP);
    }
    else if (ObjectType == MovingObjectType::WATSON)
    {
        Watson *watson = dynamic_cast<Watson *>(obj);
        int newHP = ceil((watson->getHP() * 1.2) - 0.001);
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
        int newHP = ceil((sherlock->getHP() * 1.5) - 0.001);
        sherlock->setHP(newHP);
    }
    else if (ObjectType == MovingObjectType::WATSON)
    {
        Watson *watson = dynamic_cast<Watson *>(obj);
        int newHP = ceil((watson->getHP() * 1.5) - 0.001);
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
    int enumChallenge = 10;
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
            Watson *watson = dynamic_cast<Watson *>(obj);
            int newEXP = (watson->getEXP() - 50);
            watson->setEXP(newEXP);
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
        prev->next = head;
        Node *temp = head->next;
        head->next = current->next;
        current->next = temp;
        head = current;
    }
    BaseItem *returnItem = head->item;
    Node *temp = head;
    head = head->next;
    delete temp;
    size--;

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
    Node *temp = head;
    head = head->next;
    delete temp;
    size--;

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

//*******************MOVING OBJECT*********************************************************************************************************/
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
//     this->hp = init_hp;
//     this->exp = init_exp;
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
    if (map->isValid(next_pos, this) && this->exp > 0)
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
    return this->hp;
}
int Sherlock::getEXP() const
{
    return this->exp;
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
    this->hp = hpMax;
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
    this->exp = expMax;
}

// Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
//     : Character(index, init_pos, map, "WATSON")
// {
//     this->index_moving_rule = 0;
//     this->exp = init_exp;
//     this->hp = init_hp;
//     this->moving_rule = moving_rule;
// }

Position Watson::getNextPosition()
{

    if (moving_rule.empty())
        return pos;

    char direction = moving_rule[index_moving_rule % moving_rule.size()];

    int next_row = this->pos.getRow();
    int next_col = this->pos.getCol();

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
    if (next_pos.getRow() != -1 && next_pos.getCol() != -1 && this->exp > 0)
    {
        this->pos = next_pos;
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
    return this->hp;
}

int Watson::getEXP() const
{
    return this->exp;
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
    this->hp = hpMax;
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
    this->exp = expMax;
}

Map::Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls)
    : num_rows(num_rows), num_cols(num_cols)
{
    if (num_cols == 0 || num_rows == 0)
    {
        return;
    }
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
    if (num_cols == 0 || num_rows == 0)
    {
        return;
    }
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

bool Map::isValid(const Position &pos, MovingObject *mv_obj) const
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
            FakeWall *fakeWall = dynamic_cast<FakeWall *>(map[pos.getRow()][pos.getCol()]);

            if (fakeWall && watson->getEXP() > fakeWall->getReqExp())
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
    this->prev_pos = Position::npos;
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
        this->prev_pos = pos;
        pos = nextPos;
        this->count++;
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
    if (criminal->getCount() % 3 == 0 && criminal->getCount() != 0)
    {
        // Create RobotC
        if (criminal->getCount() == 3)
        {
            return new RobotC(index, criminal->getPrevPos(), map, criminal);
        }
        int criminalRow = criminal->getPrevPos().getRow();
        int criminalCol = criminal->getPrevPos().getCol();

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
            return new RobotS(index, criminal->getPrevPos(), map, criminal, sherlock);
        }
        else if (distanceToSherlock > distanceToWatson)
        {
            // Create RobotW
            return new RobotW(index, criminal->getPrevPos(), map, criminal, watson);
        }
        else
        {
            // Create RobotSW
            return new RobotSW(index, criminal->getPrevPos(), map, criminal, sherlock, watson);
        }
    }
    return NULL;
}

MovingObjectType Robot::getObjectType() const
{
    return ROBOT;
}

/*
 *CLASS: RobotC kế thừa class Robot
 */
RobotC::RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal)
    : Robot(index, init_pos, map, criminal)
{
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
    return criminal->getPrevPos();
}
void RobotC::move()
{
    Position nextPos = getNextPosition();

    if (map->isValid(nextPos, this))
    {
        this->pos = nextPos;
    }
    // nextPosition = criminal->getCurrentPosition();
}
string RobotC::str() const
{
    Position robotPos = getCurrentPosition();

    // int distance = criminal->manhattanDistance(robotPos, criminal->getCurrentPosition());

    string description = "Robot[pos=" + robotPos.str() + ";type=C;dist=" + "]";

    return description;
}
// int RobotC::getDistance() const
// {
//     return 0;
// }
RobotType RobotC::getType() const
{
    return RobotType::C;
}
/*
 * CLASS: RobotW kế thừa class Robot
 */

RobotW::RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson)
    : Robot(index, init_pos, map, criminal), // Call base class constructor
      watson(watson)                         // Initialize Watson pointer member
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
RobotS::RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock)
    : Robot(index, init_pos, map, criminal),
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
RobotSW::RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson)
    : Robot(index, init_pos, map, criminal),
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
    for (int i = 3; i < count; ++i)
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

    num_fake_walls = 0;
    num_walls = 0;
    sherlock_init_exp = 0;
    sherlock_moving_rule = "";
    watson_init_exp = 0;
    watson_moving_rule = "";
    sherlock_init_hp = 0;
    watson_init_hp = 0;
    sherlock_init_pos = Position ::npos;
    watson_init_pos = Position::npos;
    criminal_init_pos = Position::npos;
    arr_fake_walls = nullptr;
    arr_walls = nullptr;
    map_num_cols = 0;
    map_num_rows = 0;
    max_num_moving_objects = 0;
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
    ostringstream oss;

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

//****************************************************TASK FIGHT***************************************************************************************/
// ! Các mục sửa đổi:
// ! HÀM KHỞI TẠO: Sherlock và Watson thêm thuộc tính bag, Robot thêm thuộc tính để sinh item
// !
Robot::Robot(int index, const Position &pos, Map *map, Criminal *criminal, const string &name)
    : MovingObject(index, pos, map, name), criminal(criminal), poshead(pos)
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
    // check case create item by range of s
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
    : Character(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), hp(init_hp), exp(init_exp), index_moving_rule(0)
{
    this->bag = new SherlockBag(this);
}
Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "Watson"), moving_rule(moving_rule), hp(init_hp), exp(init_exp), index_moving_rule(0)
{
    this->bag = new WatsonBag(this);
}

StudyPinkProgram::StudyPinkProgram(const string &config_file_path)
{
    // first
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

bool ArrayMovingObject::checkMeet(int index) const
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
            MovingObjectType typeAtIndex = objAtIndex->getObjectType(); // dt dang duyet
            MovingObjectType otherType = otherObj->getObjectType();     // dtt bi va

            switch (typeAtIndex)
            {
            case SHERLOCK:
                if (otherType == ROBOT)
                {
                    Robot *robot = dynamic_cast<Robot *>(otherObj);
                    RobotType typeRobot = robot->getType();
                    bool fight = false;
                    switch (typeRobot)
                    {
                    case RobotType::C:
                        fight = dynamic_cast<Sherlock *>(objAtIndex)->meet(dynamic_cast<RobotC *>(robot));
                        if (fight)
                            return true;
                        break;
                    case RobotType::S:
                        dynamic_cast<Sherlock *>(objAtIndex)->meet(dynamic_cast<RobotS *>(robot));
                        break;
                    case RobotType::W:
                        dynamic_cast<Sherlock *>(objAtIndex)->meet(dynamic_cast<RobotW *>(robot));
                        break;
                    case RobotType::SW:
                        dynamic_cast<Sherlock *>(objAtIndex)->meet(dynamic_cast<RobotSW *>(robot));
                        break;
                    }
                }
                else if (otherType == WATSON)
                {
                    Sherlock *sherlock = dynamic_cast<Sherlock *>(objAtIndex);
                    Watson *watson = dynamic_cast<Watson *>(otherObj);
                    sherlock->meet(watson);
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
                    RobotType typeRobot = robot->getType();
                    switch (typeRobot)
                    {
                    case RobotType::C:
                        dynamic_cast<Watson *>(objAtIndex)->meet(dynamic_cast<RobotC *>(robot));
                        break;
                    case RobotType::S:
                        dynamic_cast<Watson *>(objAtIndex)->meet(dynamic_cast<RobotS *>(robot));
                        break;
                    case RobotType::W:
                        dynamic_cast<Watson *>(objAtIndex)->meet(dynamic_cast<RobotW *>(robot));
                        break;
                    case RobotType::SW:
                        dynamic_cast<Watson *>(objAtIndex)->meet(dynamic_cast<RobotSW *>(robot));
                        break;
                    }
                }
                else if (otherType == SHERLOCK)
                {
                    Watson *watson = dynamic_cast<Watson *>(objAtIndex);
                    Sherlock *sherlock = dynamic_cast<Sherlock *>(otherObj);
                    watson->meet(sherlock);
                    continue;
                }
                else if (otherType == CRIMINAL)
                {
                    return true;
                }
                break;
            case CRIMINAL:
                if (otherType == ROBOT)
                {
                    continue;
                }
                else if (otherType == SHERLOCK || otherType == WATSON)
                {
                    return true;
                }
                break;
            case ROBOT:
                if (otherType == ROBOT)
                {
                    continue;
                }
                else if (otherType == SHERLOCK)
                {
                    Robot *robot = dynamic_cast<Robot *>(objAtIndex); // index
                    RobotType typeRobot = robot->getType();
                    bool fight = false;
                    switch (typeRobot)
                    {
                    case RobotType::C:
                        fight = dynamic_cast<Sherlock *>(otherObj)->meet(dynamic_cast<RobotC *>(robot));
                        if (fight)
                            return true;
                        break;
                    case RobotType::S:
                        dynamic_cast<Sherlock *>(otherObj)->meet(dynamic_cast<RobotS *>(robot));
                        break;
                    case RobotType::W:
                        dynamic_cast<Sherlock *>(otherObj)->meet(dynamic_cast<RobotW *>(robot));
                        break;
                    case RobotType::SW:
                        dynamic_cast<Sherlock *>(otherObj)->meet(dynamic_cast<RobotSW *>(robot));
                        break;
                    }
                }
                else if (otherType == WATSON) // robot vs watson
                {
                    Robot *robot = dynamic_cast<Robot *>(objAtIndex);
                    RobotType typeRobot = robot->getType();
                    switch (typeRobot)
                    {
                    case RobotType::C:
                        dynamic_cast<Watson *>(otherObj)->meet(dynamic_cast<RobotC *>(robot));
                        break;
                    case RobotType::S:
                        dynamic_cast<Watson *>(otherObj)->meet(dynamic_cast<RobotS *>(robot));
                        break;
                    case RobotType::W:
                        dynamic_cast<Watson *>(otherObj)->meet(dynamic_cast<RobotW *>(robot));
                        break;
                    case RobotType::SW:
                        dynamic_cast<Watson *>(otherObj)->meet(dynamic_cast<RobotSW *>(robot));
                        break;
                    }
                }
                else if (otherType == CRIMINAL)
                {
                    continue;
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
    if (this->getBag()->checkItem(ItemType::EXCEMPTION_CARD))
    {
        if (this->getHP() % 2 != 0)
        {
            BaseItem *excemptionCard = this->bag->get(ItemType::EXCEMPTION_CARD);
            if (this->exp > 400)
            {
                BaseItem *item = robotS->NewItem();
                this->bag->insert(item);

                BaseItem *otherItem = bag->get();
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
                return true;
            }
            else
            {
                BaseItem *otherItem = bag->get();
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
                return false;
            }
        }
        else
        {
            if (this->exp > 400)
            {
                BaseItem *item = robotS->NewItem();
                this->bag->insert(item);

                BaseItem *otherItem = bag->get();
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
                return true;
            }
            else
            {
                this->exp = ceil(this->exp * 0.9 - 0.0001);

                BaseItem *otherItem = bag->get();
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
                return false;
            }
        }
    }

    else
    {
        if (this->exp > 400)
        {
            BaseItem *item = robotS->NewItem();
            this->bag->insert(item);

            BaseItem *otherItem = bag->get();
            if (otherItem)
            {
                otherItem->use(this, nullptr);
            }
            return true;
        }
        else
        {

            this->exp = ceil(this->exp * 0.9 - 0.0001);

            BaseItem *otherItem = bag->get();
            if (otherItem)
            {
                otherItem->use(this, nullptr);
            }
            return false;
        }
    }
}
bool Sherlock::meet(RobotW *robotW)
{
    if (this->getBag()->checkItem(ItemType::EXCEMPTION_CARD) && this->getHP() % 2 != 0)
    {
        BaseItem *excemptionCard = this->bag->get(ItemType::EXCEMPTION_CARD);
    }

    BaseItem *item = robotW->NewItem();
    this->bag->insert(item);

    BaseItem *otherItem = bag->get();
    if (otherItem)
    {
        otherItem->use(this, nullptr);
    }
    return true;
}
bool Sherlock::meet(RobotSW *robotSW)
{
    if (this->getBag()->checkItem(ItemType::EXCEMPTION_CARD))
    {
        if (this->getHP() % 2 != 0)
        {
            BaseItem *excemptionCard = this->bag->get(ItemType::EXCEMPTION_CARD);
            if (exp > 300 && hp > 335)
            {
                BaseItem *item = robotSW->NewItem();
                this->bag->insert(item);

                BaseItem *otherItem = bag->get();
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
                return true;
            }
            else
            {
                BaseItem *otherItem = bag->get();
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
                return false;
            }
        }
        else
        {
            if (exp > 300 && hp > 335)
            {
                BaseItem *item = robotSW->NewItem();
                this->bag->insert(item);

                BaseItem *otherItem = bag->get();
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
                return true;
            }
            else
            {
                this->exp = ceil(this->exp * 0.85 - 0.0001);
                this->hp = ceil(this->hp * 0.85 - 0.0001);

                BaseItem *otherItem = bag->get();
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
                return false;
            }
        }
    }
    else
    {
        if (exp > 300 && hp > 335)
        {
            BaseItem *item = robotSW->NewItem();
            this->bag->insert(item);

            BaseItem *otherItem = bag->get();
            if (otherItem)
            {
                otherItem->use(this, nullptr);
            }
            return true;
        }
        else
        {
            this->exp = ceil(this->exp * 0.85 - 0.0001);
            this->hp = ceil(this->hp * 0.85 - 0.0001);

            BaseItem *otherItem = bag->get();
            if (otherItem)
            {
                otherItem->use(this, nullptr);
            }
            return false;
        }
    }
}
bool Sherlock::meet(RobotC *robotC)
{
    if (this->getBag()->checkItem(ItemType::EXCEMPTION_CARD))
    {
        if (this->getHP() % 2 != 0)
        {
            BaseItem *excemptionCard = this->bag->get(ItemType::EXCEMPTION_CARD);
            if (this->exp > 500)
            {
                this->pos = robotC->getCriminalPosition();

                BaseItem *otherItem = bag->get();
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
                return true;
            }
            else
            {
                BaseItem *item = robotC->NewItem();
                this->bag->insert(item);

                BaseItem *otherItem = bag->get();
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
                return false;
            }
        }
        else
        {
            if (exp > 500)
            {

                this->pos = robotC->getCriminalPosition();

                BaseItem *otherItem = bag->get();
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
                return true;
            }
            else
            {
                BaseItem *item = robotC->NewItem();
                this->bag->insert(item);

                BaseItem *otherItem = bag->get();
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
                return false;
            }
        }
    }
    else
    {
        if (exp > 500)
        {

            this->pos = robotC->getCriminalPosition();

            BaseItem *otherItem = bag->get();
            if (otherItem)
            {
                if (otherItem)
                {
                    otherItem->use(this, nullptr);
                }
            }
            return true;
        }
        else
        {
            BaseItem *item = robotC->NewItem();
            this->bag->insert(item);

            BaseItem *otherItem = bag->get();
            if (otherItem)
            {
                otherItem->use(this, nullptr);
            }
            return false;
        }
    }
}
bool Sherlock::meet(Watson *watson)
{

    if (this->bag->checkItem(PASSING_CARD) && watson->getBag()->checkItem(EXCEMPTION_CARD))
    {
        while (this->bag->checkItem(PASSING_CARD))
        {
            BaseItem *passingCard = this->bag->get(PASSING_CARD); // PASSING_CARD
            watson->getBag()->insert(passingCard);
        }

        // Then, Watson gives ExcemptionCards to Sherlock
        while (watson->getBag()->checkItem(EXCEMPTION_CARD))
        {
            BaseItem *excemptionCard = watson->getBag()->get(EXCEMPTION_CARD); // EXCEMPTION_CARD
            this->bag->insert(excemptionCard);
        }
        return true;
    }
    else
    {
        return false;
    }
}
// *CLASS: Watson
// ! Lưu ý: PassingCard được dùng khi GẶP ROBOT để bỏ qua thử thách nếu đúng loại thẻ
// ! Thực hiện get từ bag sau khi insert item
bool Watson::meet(RobotS *robotS)
{
    if (this->getBag()->checkItem(ItemType::PASSING_CARD) && this->hp % 2 == 0)
    {
        BaseItem *passingCard = getBag()->get(ItemType::PASSING_CARD);
        passingCard->use(this, robotS);
    }

    BaseItem *item = getBag()->get();
    if (item)
    {
        item->use(this, nullptr);
    }
    return true;
}
bool Watson::meet(RobotW *robotW)
{
    if (this->getBag()->checkItem(ItemType::PASSING_CARD) && this->hp % 2 == 0)
    {
        BaseItem *passingCard = getBag()->get(ItemType::PASSING_CARD);
        passingCard->use(this, robotW);

        this->bag->insert(robotW->NewItem());

        BaseItem *item = getBag()->get();
        if (item)
        {
            item->use(this, nullptr);
        }
        return true;
    }
    else
    {
        if (this->getHP() > 350)
        {
            this->bag->insert(robotW->NewItem());

            BaseItem *item = getBag()->get();
            if (item)
            {
                item->use(this, nullptr);
            }
            return true;
        }
        else
        {
            int newHP = ceil(this->getHP() * 0.95 - 0.0001);
            this->setHP(newHP);

            BaseItem *item = getBag()->get();
            if (item)
            {
                item->use(this, nullptr);
            }
            return false;
        }
    }
}
bool Watson::meet(RobotSW *robotSW)
{
    if (this->getBag()->checkItem(ItemType::PASSING_CARD) && this->hp % 2 == 0)
    {
        BaseItem *passingCard = getBag()->get(ItemType::PASSING_CARD);
        passingCard->use(this, robotSW);

        this->bag->insert(robotSW->NewItem());

        BaseItem *item = getBag()->get();
        if (item)
        {
            item->use(this, nullptr);
        }
        return true;
    }
    else
    {
        if (this->getEXP() > 600 && this->getHP() > 165)
        {
            this->bag->insert(robotSW->NewItem());

            BaseItem *item = getBag()->get();
            if (item)
            {
                item->use(this, nullptr);
            }
            return true;
        }
        else
        {
            this->setHP(ceil((this->getHP() * 0.85) - 0.001));
            this->setEXP(ceil((this->getEXP() * 0.85) - 0.001));
            BaseItem *item = getBag()->get();
            if (item)
            {
                item->use(this, nullptr);
            }
            return false;
        }
    }
}
bool Watson::meet(RobotC *robotC)
{
    if (this->getBag()->checkItem(ItemType::PASSING_CARD) && this->hp % 2 == 0)
    {
        BaseItem *passingCard = getBag()->get(ItemType::PASSING_CARD);
        passingCard->use(this, robotC);
        this->bag->insert(robotC->NewItem());

        BaseItem *item = getBag()->get();
        if (item)
        {
            item->use(this, nullptr);
        }
        return true;
    }
    else
    {
        this->bag->insert(robotC->NewItem());
        BaseItem *item = getBag()->get();

        if (item)
        {
            item->use(this, nullptr);
        }

        return false;
    }
}
bool Watson::meet(Sherlock *sherlock)
{
    if (sherlock->getBag()->checkItem(PASSING_CARD) && this->bag->checkItem(EXCEMPTION_CARD))
    {
        while (sherlock->getBag()->checkItem(PASSING_CARD))
        {
            BaseItem *passingCard = sherlock->getBag()->get(PASSING_CARD); // PASSING_CARD
            this->bag->insert(passingCard);
        }

        while (this->bag->checkItem(EXCEMPTION_CARD))
        {
            BaseItem *excemptionCard = this->bag->get(EXCEMPTION_CARD); // EXCEMPTION_CARD
            sherlock->getBag()->insert(excemptionCard);
        }
        return true;
    }
    else
    {
        return false;
    }
}

BaseBag *Sherlock::getBag() const
{
    return this->bag;
}
BaseBag *Watson::getBag() const
{
    return this->bag;
}