// TODO.cpp


#include <iostream>
#include <string> // Fot getline
#include <limits>  // For cin.fail check conditions
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// Struct for TODO List
struct TODOList 
{
  friend ostream &operator << (ostream &output, TODOList &itemEntrytemp);
  friend istream &operator >> (istream &input, TODOList &itemEntrytemp);
  int ID;
  string dateAdded;
  string description;
};

// Class for TODO List
class NganTODO
{
  public:
  int num = 1;
  TODOList* itemEntrytemp = nullptr;
  TODOList* tempArray = nullptr;
  NganTODO();
  ~NganTODO();
    void Persistence(int&, string&);
		void getTODO(int&, string&);
		void DisplayTODO(int&);
		void editTODO(int& num);
    void writeTODO(int&);
		void Resize(int& , string&);
		void ComponentTest(int&);
    string UnitTest();
    string DateTest();
    void remove(int&, int &);
    void modify(int&, string&);
    // Date class
  class Date
  {
    private:
          string Month;
          int Day;
          int Year;
          
    public:
          int getDay()
          {
            return Day;
          }
          void SetDay(int day)
          {
            if ( day > 0 && day < 31)
            {
              Day = day;
            }
            else 
            {
              Day = 1;
              cout << "Invalid Date. Date will be set to default 1."<< endl;
            }
          }
          int getYear()
          {
            return Year;
          }
          void SetYear(int year)
          {
            if ( year > 0)
            {
              if (year < 9999)
              {
                Year = year;
              }
              else
              {
                Year = 2020;
                cout << "Invalid Year. Year will be set to default 2020." << endl;      
              }
            }
            else 
            {
              Year = 2020;
              cout << "Invalid Year. Year will be set to default 1998." << endl;
            }
          }
          string getMonth()
          {
            return Month;
          }
          string SetMonth(int month)
          {
            if (month == 1)
            {
              Month = "01";
            }
            else if (month == 2)
            {
              Month = "02";
            }
            else if (month == 3)
            {
              Month = "03";
            }
            else if (month == 4)
            {
              Month = "04";
            }
            else if (month == 5)
            {
              Month = "05";
            }
            else if (month == 6)
            {
              Month = "06";
            }
            else if (month == '7')
            {
              Month = "07";
            }
            else if (month == 8)
            {
              Month = "08";
            }
            else if (month == 9)
            {
              Month = "09";
            }
            else if (month == 10)
            {
              Month = "10";
            }
            else if (month == 11)
            {
              Month = "11";
            }
            else if (month == 12)
            {
              Month = "12";
            }
            else
            {
              cout << "Invalid Month. Month will be set to default October." << endl;
              Month = "10";
            }
          return Month;
          }
          // Convert date to string
          string Convert()
          {
            string day_s = to_string(Day);
            string year_s = to_string(Year);
            string text = getMonth() + "/" + day_s + "/" + year_s;
            return text;
          }
  };
};

// Specification C4 - TODO array
NganTODO::NganTODO()
{
	const int count = 1;
	itemEntrytemp = new TODOList[num + count];
}

NganTODO::~NganTODO()
{
	cout << "Deleting pointers in heap.\n";
	delete [] itemEntrytemp;
	itemEntrytemp = nullptr;
	delete [] tempArray;
	tempArray = nullptr;
}

// Take Item's info
// Specification B1 - + Symbol
// Add task to TODO List
void NganTODO::getTODO (int& num, string& des)
{
  Resize (num, des);
  cin >> itemEntrytemp[num-1];
  string day;
  modify(num,des);
  day = UnitTest();
  itemEntrytemp[num-1].dateAdded = day;
  cout << "Date Added: "<< day << endl;
}

void NganTODO::modify(int&num, string&des)
{
  for(int i = 0; i < num; ++i)
  {
    itemEntrytemp[num-1].description = des;
  }
}

// Resize array
void NganTODO::Resize(int& num , string& des)
{
  // Resize Array - add to end
  const int count = 1;
  num++;
  tempArray = new TODOList[num+ count];
  for (int i = 0; i < num-1; i++)
  {
      // Specification A2 - Overload Assignment Operator
      tempArray[i] = itemEntrytemp[i];
  } 
    delete [] itemEntrytemp;
    itemEntrytemp = tempArray;
    tempArray = nullptr;
}

//Specification B4 - Persistence
// Specification C3 - Test TODO’s - Use file to test Struct TODO List
void NganTODO::Persistence(int& num, string& des)
{
  string dateold, desold;
  int idold;
  cout << "These are your TODO List from the last time: " << endl;
  // Create and open a text file
  ifstream TOODOO;
  string line;
  // Read from the text file
  TOODOO.open("todolist.txt");
  //checking whether the file is open
  while (getline (TOODOO, line))  
  {  //read data from file object and put it into string.
    int posid = line.find("ID:");
    string  subid = line.substr(posid + 4,5);
    idold = stoi(subid);
    int pos1 = line.find("added:"); 
    string subdate = line.substr(pos1 + 7, 10);
    dateold = subdate;
    int pos2 = line.find("tion:"); 
    string subdes = line.substr(pos2 + 6);
    des = subdes;
    Resize (num, des);
    for(int i = 0; i < num; i++)
    {
      itemEntrytemp[num-1].ID = idold;
      itemEntrytemp[num-1].description = des;
      itemEntrytemp[num-1].dateAdded = dateold;
    }
  }
  //print the data of the string
  DisplayTODO(num);
  TOODOO.close();
  cout << endl;
}

// Show all Items in the TODO List
// Specification B2 - ? Symbol
// Display TODO List
void NganTODO::DisplayTODO(int& num)
{
  cout << "----------------------------------------------------------------------"<< endl;
  cout << "----------------------------------------------------------------------"<< endl;
  for (int i = 1; i < num; i++)
  {
    cout << left << setw(18) << "Item numer: " << i << endl;
    cout << itemEntrytemp[i]<<"|";
    cout << endl;
    cout << "----------------------------------------------------------------------"<< endl;
  }
  cout << endl;
}

// Get system Date
// Specification A3 - System Date
string NganTODO::UnitTest()
{
  // Get Current date from System
  Date SystemDate;
  time_t current = time(0);
  tm* overwatch = localtime(&current);
  int m = 1 + overwatch->tm_mon;
  int d = overwatch->tm_mday;
  int y = 1900 + overwatch->tm_year;
  SystemDate.SetMonth(m);
  SystemDate.SetDay(d);
  SystemDate.SetYear(y);
  string dd = to_string(d);
  string mm = SystemDate.getMonth();
  string yy = to_string(y);
  string expect = (SystemDate.getMonth() + "/" + dd + "/" + yy);
  return expect;
}

// Specification C3 - Test TODO’s
// Object Test Diagnose #1 - User ability to enter a date of their wish
string NganTODO::DateTest()
{
  NganTODO::Date thisday;
  int d,y,m;
  cout << "Enter a Month: ";
  cin >> m;
  // Re-enter if user enter non-numeric input
  while (m<13)
  {
    if(cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
      cout<< "You have not enter a numeric input. Enter Month again: ";
      cin >> m;
    }
    if(!cin.fail())
    break;
  }
  cout << "Please enter Date: ";
  cin >> d;
  // Re-enter if user enter non-numeric input
  while (d<32)
  {
    if(cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
      cout<< "You have not enter a numeric input. Enter Date again: ";
      cin >> d;
    }
    if(!cin.fail())
    break;
  }
  cout << "Please enter Year: ";
  cin >> y;
  // Re-enter if user enter non-numeric input
  while (y<13)
  {
    if(cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
      cout<< "You have not enter a numeric input. Enter Year again: ";
      cin >> y;
    }
    if(!cin.fail())
    break;
  }
  thisday.SetMonth(m);
  thisday.SetDay(d);
  thisday.SetYear(y);
  cout << "Today is: "<< thisday.getMonth() << "/" << thisday.getDay() << "/" << thisday.getYear() << endl;
  string dd = to_string(d);
  string mm = thisday.getMonth();
  string yy = to_string(y);
  string expect = (thisday.getMonth() + "/" + dd + "/" + yy);
  return expect;
}

//Specification B4 - Persistence
void NganTODO::writeTODO(int&num)
{
  ofstream TOODOO;
  TOODOO.open("todolist.txt");  //Open a file to perform write operation using file object
  for (int i =1; i< num; i++)
    {
    TOODOO << "|"<< i <<"|";
    TOODOO << "ID: " <<itemEntrytemp[i].ID<<"|--|";
    TOODOO << "Date added: " <<itemEntrytemp[i].dateAdded<<"|--|";
    TOODOO << "Description: " << itemEntrytemp[i].description << endl;
    }
  TOODOO.close();
}

// Specification B3 - - symbol
void NganTODO::remove(int & num, int& edit)
{
  int i=0;
  while (i < num )
  {
    
    // Search through Inventory
    if( edit == itemEntrytemp[i].ID)
    {
      num = num-1;
      cout << "Item found: " << itemEntrytemp[i].ID << endl;
      for (int m = i; m < num; m++)
      {
        itemEntrytemp[m].ID = itemEntrytemp[m+1].ID;
        itemEntrytemp[m].dateAdded = itemEntrytemp[m+1].dateAdded;
        itemEntrytemp[m].description = itemEntrytemp[m+1].description;
      }
    }
    i+=1;
  }
}

// Delete TODO List by matching ID
// Specification B3 - - symbol
void NganTODO::editTODO(int& num)
{
  // Retrive the item ID needs editing
  int edit;
  research:
  cout << "Enter id task to be removed: ";
  cin >> edit;
  // Inventory Entry Input Validation
  while (edit <= 100000 && edit >= 9999)
  {
    if(cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
      cout<< "You have not enter a numeric input. Enter input again: ";
      cin>> edit;
    }
    if(!cin.fail())
    break;
  }
  remove(num, edit);  
  return;
  // Inventory Entry Input Validation
  // Research if user choose Y
  cout << "Item not found. ";
  char prompt;
  cout << "Re search? (y/n):";
  cin >> prompt;
  if(cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<< "You have not enter a one letter input. Enter input again: ";
    cin>> prompt;
  }
  switch (prompt)
  {
    case 'Y':
    case 'y':
    goto research;
    case 'N':
    case 'n':
    {
      break;
    }
    default:
      cout << "Your selection " << prompt << " is invalid. Exit edit option." << endl;
      break;
  }
}


//Specification C1 - Overload Operator <<
ostream &operator << (ostream &output, TODOList &itemEntrytemp)
{
  output << left << setw(18) << "ID: " << "|  " << itemEntrytemp.ID << endl; 
  output << left << setw(18) << "Date Added: "<< "|  "<< itemEntrytemp.dateAdded << endl; 
  output << left << setw(18) << "Description: "<< "|  "<< itemEntrytemp.description << endl; 
  return output;
}



// Program Greeting
void ProgramGreeting();
// Function Prototypes
// Alpha Menu
void Display_Menu(TODOList*&, int&, string&); 
void getCurrenttime();

// Main Function
int main() {
  ProgramGreeting();
  // Specification C4 - TODO array
  // Dynamic Array
  // Initialize Array size
  int count = 1;
  string des;
  TODOList* itemEntrytemp = nullptr;
  itemEntrytemp = new TODOList[count];
  Display_Menu(itemEntrytemp, count, des);
  cout << endl;
  return 0;
}

// Alpha Menu
void Display_Menu(TODOList* &itemEntrytemp, int &num, string &des)
{
  NganTODO holder;
  
  string option;
  while (option.substr(0, 1) != "E" && option.substr(0, 1) != "e") 
  {
    menu:
    cout << "***********************" << endl;
    cout << setw (18) <<"* Main Menu **Now array size is: "<< num << "*" <<endl;
    cout << "*---------------------------------------------*" << endl;
    cout << "*+) Add Item to TODO                    " << "*"  << endl;
    cout << "*?) Display TODO List                   " << "*"  << endl;
    cout << "*-) Remove task in TODO List            " << "*"  << endl;
    cout << "*E) Quit Program and save tasks to file " << "*"  << endl;
    cout << "*---------------------------------------------*" << endl;
    cout << "Enter your command: ";
    // Enter Option
    getline(cin>> ws, option);
    // Specification B1 - + Symbol
    if (option.substr(0, 1) == "+")
    {
      des = option.substr(2, 100);
      holder.getTODO(num, des);
    }
    // Specification B2 - ? Symbol
    else if (option.substr(0, 1) == "?")
    {        
      holder.DisplayTODO(num);
    }
    // Specification B3 - - symbol
    else if (option.substr(0, 1) == "-")
    {        
      holder.editTODO(num);
    }
    else if (option.substr(0, 1) == "E" || option.substr(0, 1) == "e")
    {        
      holder.writeTODO(num);
      cout << "Exit";
    }
    else
    {
      cout << "Your selection is invalid." << endl;
      cout << "Here is menu again:"<< endl;
      goto menu;
    }
  } 
}

//Specification C2 - Overload Operator >>
istream &operator >>(istream &input,TODOList &itemEntrytemp )
{
  cout << "______________________________" << endl;
  cout << "Enter information for your task " << endl;
  redo:
  cout << "Enter task ID: ";
  int idfake = 0;
  input >> itemEntrytemp.ID;
  while (idfake == 0)
  {
  idfake = itemEntrytemp.ID;
  if(cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
      cout<< "You have not enter a numeric input. Enter input again: ";
      input >> itemEntrytemp.ID;
    }
    if(!cin.fail())
    break;
  }
  // Verify item ID is 5 digits
  if (idfake <= 9999 && idfake >= 100000)
  {
    // Inventory Entry Input Validation
    cout << "Item ID you entered: " << itemEntrytemp.ID <<endl;
    cout << "Item ID can only be 5 digits" << endl;
    idfake = 0;
    goto redo;
  }
  return input;   
} 

// Program Greeting Function
void ProgramGreeting() 
{
	cout << "Welcome! This is TODO List Program" << endl;
  	cout << "My name is Ngan Bao" << endl;
  getCurrenttime();
	return;
}

// Object Test Diagnose #2 - Show current date to user
void getCurrenttime()
{
  // Get Current date from System
  NganTODO::Date SystemDate;
  time_t current = time(0);
  tm* overwatch = localtime(&current);
  int m = 1 + overwatch->tm_mon;
  int d = overwatch->tm_mday;
  int y = 1900 + overwatch->tm_year;
  SystemDate.SetMonth(m);
  SystemDate.SetDay(d);
  SystemDate.SetYear(y);
  cout << "Current Date is: " << SystemDate.getMonth() <<" " << SystemDate.getDay() << ", " << SystemDate.getYear() << endl;
}
   
















