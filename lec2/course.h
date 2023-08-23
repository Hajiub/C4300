#include <iostream>
#include <vector>
#include <fstream>

class Course
{
    std::string m_name = "Course";
    std::vector <Student> m_students;
public:
    // Default  constructor 
    Course() {}
    Course(const std::string& name)
	: m_name(name)
    {
    }

    void addStudent(const Student& student)
    {
        m_students.push_back(student);
    }

    const std::vector <Student>& getStudents() const
    {
        return m_students;
    }
    void print() const
    {
      for (const auto& s : m_students)
        {
            s.print();
        }
    }
    void LoadFromFile(const std::string& filename)
    {
        std::ifstream fin(filename);
        std::string first, last;
        int id;
        float avg;
        while (fin >> first)
        {
            fin >> last >> id >> avg;
            addStudent(Student(first, last, id, avg));
            
        }
    }
};
