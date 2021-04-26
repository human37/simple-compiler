# simple-compiler

A simple compiler written in C++. Can be configured to interpret to C++, or compile source code to machine code and execute. Supports a subset of the C programming language. 

### Features

<ul>
  <li> integers </li>
  <li> cout statements </li>
  <li> endl for a newline character </li>
  <li> line and block comments </li>
  <li> basic comparision operators (>, <, <=, >=, ==) </li>
  <li> logical && and || operators </li>
  <li> bitwise & operator </li>
  <li> nested statements with PEMDAS (4 + (4 * 2) / (1 & 1)) </li>
  <li> += and -= </li>
</ul>

Here is an example of some source code it currently supports:
```c
void main()
{
    // integers and math
    int sum;
    sum = (35 + 1) / (36 * 1) * (1 & 1);
    cout << sum << endl;

    // cout statements
    cout << endl << 0 << sum << 0 << endl;

    // plus equals & minus equals
    int test;
    test = 0;
    cout << test << endl;
    test += 99;
    cout << test << endl;
    test -= 99;
    cout << test << endl;

    // while loops
    int max;
    max = 10;
    while (max >= 0)
    {
        cout << max << endl;
        max -= 1;
    }
}
```

### Running
Your input file must be named ```INPUT.c``` and be in the projects root directory. You can then run 

    $ make interpret
  
in order to interpret the source code to C++, and

    $ make compile
  
in order to compile the source code into machine code and execute. (currently this is only available with g++-9 on <= ubuntu 16)

