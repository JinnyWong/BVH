# Notes and Explanations

## Parser

**How does a parser work?**

A parser can be divided into three components / stages:

- lexical analysis (scanner) - reads code and breaks it into smaller pieces called tokens. A token is the smallest chunk of meaningful code.

- synthatic analysis - uses tokens to construct a parse treee that combines the predefined grammar of the programming language with the tokens of the input string

- semantic analysis - data type checking, label checking and flow control checking.

.

**Methods on writing a parser:**

- top-down parsers

- bottom-up parsers

- recursive descent parser

- pratt parser

- string parsing

-----

## Code Related

#### `file(argv[1])`

#### `vector<vector<double>> motion`

#### `stringstream`

- `stringstream` can be used to read strings and write data into strings / convert between strings and other numerical types / parse out the pieces of a string 

- `stringstream ss` - create object

- `clear()` - to clear the stream

- `str()` - to get and set string object whose content is present in the stream (create a large string from many value)

- `ss << "something"` - output 

#### `istream& getline(istream& is, string& str)`

- `istream& is` - input source

- `string& str` - where to store the string

#### Pointers

- `int* pointer` - declare a pointer 

- `&var1` - get the address of var1

- `pointer = &var1` - assign address to pointer 

- `.` operator - is used to normally access members of a structure or union

- `->` operator - is used to access members of a structure or union using pointers
