#include <iostream> 
#include <string>
#include <cstdlib>
#include <algorithm>
#include <fstream>


const int MAX_MARTIANS = 100;

struct Martian {
    std::string fname_;
    std::string lname_;
    std::string SSN_;
    Martian(std::string fn, std::string ln, std::string ssn)
        : fname_(fn), lname_(ln), SSN_(ssn) { }

    // you may add other things to the structure	
};

enum class Criteria { first, last, ssn };

class MartianDatabase {
public:
    // creates a new empty Martian Database initialized with the
    // contents of filename.
    MartianDatabase(std::istream& infile);

    // add item m to database, return true if successfully added.
    bool addMartian(const Martian& m);

    // delete item with the ssn in database, return true if successfully 
    // deleted.
    bool deleteMartian(std::string ssn);

    // return true if the database does not contain any items, false
    // otherwise.
    bool isEmpty();

    // return true if the database is at its maximum storage, false
    // otherwise.
    bool isFull();

    // prints the list of Martians, sorted by last name, sorted
    // by first name and by MSSN.
    void printMartians(Criteria type);

    // deletes all the dynamically created memory
    ~MartianDatabase();
private:
    Martian* m_unsorted[MAX_MARTIANS];
    Martian* m_fname[MAX_MARTIANS];
    Martian* m_lname[MAX_MARTIANS];
    Martian* m_ssn[MAX_MARTIANS];
};

MartianDatabase::MartianDatabase(std::istream& infile) {
    for (int i = 0; i < MAX_MARTIANS; ++i) {
        m_unsorted[i] = nullptr;
        m_fname[i] = nullptr;
        m_lname[i] = nullptr;
        m_ssn[i] = nullptr;
    }

    int n = 0;
    std::string first, last, ssn;
    while (infile>>first) {      
        infile >> last;
        infile >> ssn;
        m_unsorted[n] = new Martian(first,last,ssn);
        n++;
    }
}

void MartianDatabase::printMartians(Criteria type) {
    int i = 0;
    if (type==Criteria::first) {
        while (i != MAX_MARTIANS && m_unsorted[i] != nullptr) {
            std::cout << m_unsorted[i]->fname_ << std::endl;
            i++;
        }
    }
    if (type==Criteria::last) {
        while (i != MAX_MARTIANS && m_unsorted[i] != nullptr) {
            std::cout << m_unsorted[i]->lname_ << std::endl;
            i++;
        }
    }
    if (type==Criteria::ssn) {
        while (i != MAX_MARTIANS && m_unsorted[i] != nullptr) {
            std::cout << m_unsorted[i]->SSN_ << std::endl;
            i++;
        }
    }
}

MartianDatabase::~MartianDatabase() {
    int i = 0;
    while (m_unsorted[i] != nullptr) {
    delete m_unsorted[i];
    i++;
    }
}

int main() {
    std::ifstream infile;
    std::string filename;
    std::cout << "Please enter a filename: ";
    std::cin >> filename;
    infile.open(filename);

    MartianDatabase test(infile);
    test.printMartians(Criteria::last);
    
     
  

}
