void main()
{
    // // integers and math
    // int sum;
    // sum = (35 + 1) / (36 * 1) * (1 || 1);
    // cout << sum << endl;

    // // cout statements
    // cout << endl << 0 << sum << 0 << endl;

    // // plus equals & minus equals
    // int test;
    // test = 0;
    // cout << test << endl;
    // test += 99;
    // cout << test << endl;
    // test -= 99;
    // cout << test << endl;

    // // while loops
    // int max;
    // max = 10;
    // while (max >= 0)
    // {
    //     cout << max << endl;
    //     max -= 1;
    // }
    // if ((3<5) == true)
    // {
    //     cout << 420 << endl;
    // }
    int x;
    x = 24;
    int y;
    y = 2;
    cout << (x >> y); // 6
    cout << (x >> y-1); // 12, not 5. -1 happens first
    cout << (x >> y==2); // 0, not 12. ==2 happens after
}
