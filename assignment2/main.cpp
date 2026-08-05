/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Erik Yang"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::unordered_set<std::string> get_applicants(std::string filename) {
    // STUDENT TODO: Implement this function.
    std::unordered_set<std::string> students;
    std::ifstream fin(filename, std::ios::in);
    std::string student_name;

    while (std::getline(fin, student_name)) {
        students.insert(student_name);
    }

    return students;
}

bool help_func(std::string s1, std::string s2) {
    bool f = true;
    f &= (s1.front() == s2.front());

    auto get_it = [](std::string& s) -> char {
        auto it = s.begin();
        while (it != s.end() && (*it) != ' ') {
            it = std::next(it);
        }

        assert(std::next(it) != s.end());

        return *(next(it));
    };

    f &= (get_it(s1) == get_it(s2));

    return f;
}
/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::unordered_set<std::string>& students) {
    // STUDENT TODO: Implement this function.
    std::queue<const std::string*> que;

    for (auto other_name : students) {
        if (help_func(name, other_name)) {
            que.push(&other_name);
        }
    }
    
    return que;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
    // STUDENT TODO: Implement this function.
    std::string result = "";

    while (matches.empty() == false) {
        if (matches.size() == 5) {
            result = *matches.front();
        }

        matches.pop();
    }

    if (result == "") {
        result = "NO MATCHES FOUND.";
    }
    
    return result;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
