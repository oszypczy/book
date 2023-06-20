# Book readme

This project consists of a C++ program that reads a book's information from a text file and creates a `Book` object with the extracted data. The program takes a command-line argument specifying the input file containing the book details.

## Prerequisites

To compile and run the program, you need to have a C++ compiler and the necessary libraries installed on your system. This project assumes you have the following:

- C++ compiler
- Standard Template Library (STL)
- C++ Input/Output Streams (`<iostream>`)
- File Input/Output (`<fstream>`)
- String Manipulation (`<string>`)
- String Stream (`<sstream>`)
- Vector Container (`<vector>`)

## Compilation

To compile the project, use the following command:

```
g++ main.cpp bookReader.cpp book.cpp -o bookReader
```

## Usage

Once the program is compiled, you can run it by providing the input file as a command-line argument. The input file should follow a specific format where each line represents a key-value pair of the book's information.

Here's an example of the input file format:

```
Title: The Great Gatsby
Authors: F.Scott Fitzgerald; Jan Kowalski
ISBN: 9783161484100
Publisher: Charles Scribner's Sons
Release Date: 10/10/1925
Release Place: Toruń
Chapters: 1, The great war, 100; 2, The man in the picture, 200; 3, The boats against the current, 300
```

To run the program, use the following command:

```
./bookReader <input_file.txt>
```

Replace `<input_file.txt>` with the actual path to your input file.

## Code Structure

The project consists of the following files:

1. `main.cpp`: The main entry point of the program. It handles command-line arguments, opens the input file, and creates a `BookReader` object to read the book information.

2. `bookReader.h` and `bookReader.cpp`: These files define and implement the `BookReader` class. The `BookReader` class reads the book details from the input file and creates a `Book` object with the extracted data.

3. `book.h` and `book.cpp`: These files define and implement the `Book` class, which represents a book and its properties such as title, authors, ISBN, publisher, release date, release place, and chapters.

4. `author.h` and `author.cpp`: These files define and implement the `Author` class, which represents an author and has properties for their first name and last name.

5. `chapter.h` and `chapter.cpp`: These files define and implement the `Chapter` class, which represents a chapter in a book and contains properties for its number, title, and number of pages.

6. `date.h` and `date.cpp`: These files define and implement the `Date` class, which represents a date and stores the day, month, and year.

## Additional Notes

- The input file should follow the specified format, with each line containing a key-value pair separated by a colon (`:`). Any extra spaces around the values are automatically removed.

- If an unknown key is encountered in the input file, an error message will be displayed, indicating the unknown key.

- If the input file cannot be opened or read, an error message will be displayed, and the program will exit.

- The extracted book information is displayed on the console once it is successfully read from the input file.

## Conclusion

This project provides a simple C++ program that can read book information from a text file and create a `Book` object

 with the extracted data. You can customize the project further to add more features or modify the existing classes to suit your requirements.
