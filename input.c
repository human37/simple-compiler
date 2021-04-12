void main()
{
    // testing the bitwise AND operator, and the priority:
    if ((1 & 1) && (1 & 0))
    {
        // it will not print this
        cout << 999; // (secondsum's value is 8)
    }

    if ((1 & 1) && (1 & 1) || (1 & 1))
    {
        // it will print this
        cout << 0; // (firsum's value is 4)
    }

    int mathtest = 1 * 2 / 3 - 4 + 6;
    cout << mathtest; // 2

    // while loop
    int i = 10;
    while (i >= 0)
    {
        cout << i;
        i = i - 1;
    }
}
