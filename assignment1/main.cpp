#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";


struct Course {
  std::string title;
  std::string number_of_units;
  std::string quarter;
};

#include "utils.cpp"

/**
 * This function should populate the `courses` vector with structs of type
 * `Course`. We want to create these structs with the records in the courses.csv
 * file, where each line is a record!
 *
 * Hints:
 * 1) Take a look at the split function we provide in utils.cpp
 * 2) Each LINE is a record! *this is important, so we're saying it again :>)*
 * 3) The first line in the CSV defines the column names, so you can ignore it!
 *
 * @param filename The name of the file to parse.
 * @param courses  A vector of courses to populate.
 */
void parse_csv(std::string filename, std::vector<Course>& courses) {
  std::fstream input_file;
  std::string tmp;
  input_file.open(filename, std::ios::in);
  getline(input_file,tmp);
  while(!input_file.eof())
  {
    getline(input_file,tmp);
    auto tmp_vector = split(tmp, ',');
    Course mem{tmp_vector[0], tmp_vector[1], tmp_vector[2]};
    courses.push_back(mem);
  }
  input_file.close();
}

/**
 * This function has TWO requirements.
 *
 * 1) Write the courses that are offered to the file
 * "student_output/courses_offered.csv"
 *
 * 2) Delete the courses that are offered from the `all_courses` vector.
 * IMPORTANT: do this after you write out to the file!
 *
 * HINTS:
 * 1) Keep track of the classes that you need to delete!
 * 2) Use the delete_elem_from_vector function we give you!
 * 3) Remember to write the CSV column headers at the beginning of the output!
 *    See courses.csv for reference.
 *
 * @param all_courses A vector of all courses gotten by calling `parse_csv`.
 *                    This vector will be modified by removing all offered courses.
 */
void write_courses_offered(std::vector<Course>& all_courses) {
  std::fstream output_file;
  output_file.open(COURSES_OFFERED_PATH, std::ios::out);
  output_file<<"Title,Number of Units,Quarter"<<std::endl;
  for(auto elem: all_courses)
  {
    if(elem.quarter!="null")
    {
      output_file<<elem.title<<","<<elem.number_of_units<<","<<elem.quarter<<std::endl;
    }
  }
  all_courses.erase(std::remove_if(all_courses.begin(),all_courses.end(),[](Course x) {return x.quarter!="null";}), all_courses.end());
  output_file.close();
}

/**
 * This function writes the courses NOT offered to the file
 * "student_output/courses_not_offered.csv".
 *
 * This function is ALWAYS called after the `write_courses_offered` function.
 * `unlisted_courses` will trivially contain classes that are not offered
 * since you delete offered classes from `all_courses` in the
 * `write_courses_offered` function.
 *
 * HINT: This should be VERY similar to `write_courses_offered`
 *
 * @param unlisted_courses A vector of courses that are not offered.
 */
void write_courses_not_offered(std::vector<Course> unlisted_courses) {
  std::fstream output_file;
  output_file.open(COURSES_NOT_OFFERED_PATH, std::ios::out);
  output_file<<"Title,Number of Units,Quarter"<<std::endl;
  for(auto elem: unlisted_courses)
  {
    output_file<<elem.title<<","<<elem.number_of_units<<","<<elem.quarter<<std::endl;
  }
  output_file.close();
}

int main() {
  /* Makes sure you defined your Course struct correctly! */
  static_assert(is_valid_course<Course>, "Course struct is not correctly defined!");

  std::vector<Course> courses;
  parse_csv("courses.csv", courses);

  write_courses_offered(courses);
  write_courses_not_offered(courses);

  return run_autograder();
}