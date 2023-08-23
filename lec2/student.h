// I love cpp 
#include <iostream>

class Student 
{
    std::string m_first = "First";
    std::string m_last  = "Last"; 
    int         m_id    = 0;
    float       m_avg   = 0;

    
public:
    Student() {}
    
    Student(std::string first, std::string last, int id, float avg)
	    : m_first (first)
	    , m_last  (last)
	    , m_id    (id)
	    , m_avg   (avg)
   {
   }
    float getAvg() const
    {
	    return m_avg;
    }
    int getId() const
    {
    	return  m_id;
    }
    std::string getFirst() const
    {
        return m_first;
    }
    std::string getLast() const
    {
        return m_last;
    }
    void print () const
    {
        std::cout << m_first << " " << m_last << " ";
	std::cout  << m_id << " " << m_avg << std::endl;
    }

};

