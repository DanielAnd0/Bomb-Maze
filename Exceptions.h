//
// Created by Daniel on 09.12.2025.
//

#ifndef OOP_EXCEPTIONS_H
#define OOP_EXCEPTIONS_H

#include <iostream>
#include <exception>

class Exceptions : public std::exception {
    std::string message;
public:
    explicit Exceptions(const std::string& msg):message(msg){}
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};
class FileLoadFail : public Exceptions {
public:
      FileLoadFail(): Exceptions("File failed to load"){}
};
class NotInMaze : public Exceptions {
public:
      NotInMaze(const float position_x, const float position_y):Exceptions("Position (" + std::to_string(position_x) + ", " + std::to_string(position_y) + ") is not in curent's game maze."){}
};
class InvalidTileNumber : public Exceptions {
public:
    explicit InvalidTileNumber(const int number):Exceptions("Number " + std::to_string(number) + " is not a valid tile number."){}
};

#endif //OOP_EXCEPTIONS_H