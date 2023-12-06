int convertToMinutes(const char *time)
{
    int hour1 = time[0] - '0';
    int hour2 = time[1] - '0';
    int min1 = time[3] - '0';
    int min2 = time[4] - '0';
    int timeInMinutes = ((hour1 * 10 + hour2) * 60 + (min1 * 10 + min2));
    return timeInMinutes;
}