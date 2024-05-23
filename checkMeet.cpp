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