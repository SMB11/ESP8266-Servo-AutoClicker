void waterOneCycle()
{
    if (timeInMinutesNow - lastWateringTime >= delayForWakeUpClick)
    {
        longDelayClick();
    }
    else
    {
        oneClick();
    }
}

void checkWateringAllowed()
{
    if (!tasksForTodayFinished)
    {
        if (currentCycleNumber < currentTask.numOfCycles)
        {
            getTime();
            if (timeInMinutesNow - lastWateringTime > currentTask.minimumWateringDelay)
            {
               waterOneCycle();
            }
        }
        else
        {
            tasksForTodayFinished = true;
        }
    }
}
