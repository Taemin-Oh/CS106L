/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <sstream>

std::string kYourName = "SOOBIN CHAE"; // Don't forget to change this!

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
std::set<std::string> get_applicants(std::string filename) {
  std::set<std::string> data;
  std::string name;
  std::ifstream file;
  file.open(filename,std::ios::in);
  while(!file.eof())
  {
    getline(file, name);
    data.insert(name);
  }
  file.close();
  return data;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::string get_initial(std::string name)
{
  std::stringstream ss(name);
  std::string part;
  std::string output = "";
  while(ss >> part)
  {
    output = output + part[0];
  }
  return output;
}

 std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> data;
  std::string initial_name = get_initial(name);
  for(auto& elem: students)
  {
    if(initial_name == get_initial(elem)) data.push(&elem);
  }
  return data;
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
  if(matches.empty()) return "NO MATCHES FOUND.";
  std::string output = *(matches.front());
  return output;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
