#ifndef __PAGE_HPP__
#define __PAGE_HPP__
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class Page {
 private:
  class Choice {
   public:
    size_t src_pageNum;
    std::vector<size_t> des_pageNums;
    std::vector<std::string> choices;
    std::vector<std::pair<std::pair<std::string, long int>, std::string> > choices_con;
    void addChoice(const size_t & des_pageNum, const std::string & choice) {
      des_pageNums.push_back(des_pageNum);
      choices.push_back(choice);
    }
    void addChoicewithCon(const size_t & des_pageNum,
                          const std::string & condition_name,
                          const long int & condition_val,
                          const std::string & choice) {
      des_pageNums.push_back(des_pageNum);
      choices_con.push_back(
          std::make_pair(std::make_pair(condition_name, condition_val), choice));
    }
    Choice(const size_t & src_pageNum,
           const size_t & des_pageNum,
           const std::string & choice) :
        src_pageNum(src_pageNum) {
      des_pageNums.push_back(des_pageNum);
      choices.push_back(choice);
    }
    Choice(const size_t & src_pageNum,
           const size_t & des_pageNum,
           const std::string & condition_name,
           const long int & condition_val,
           const std::string & choice) :
        src_pageNum(src_pageNum) {
      des_pageNums.push_back(des_pageNum);
      choices_con.push_back(
          std::make_pair(std::make_pair(condition_name, condition_val), choice));
    }
    Choice(const size_t & src_pageNum,
           const std::vector<size_t> & des_pageNums,
           const std::vector<std::string> & choices) :
        src_pageNum(src_pageNum), des_pageNums(des_pageNums), choices(choices) {}
  };
  Choice * choice;
  size_t page_num;
  char type;
  bool referenced;
  std::string page_name;
  std::vector<std::string> content;
  std::vector<std::pair<std::string, long int> > conditions;

 public:
  Page() : choice(NULL), page_num(0), type('N'), referenced(false) {}
  Page(size_t page_num, char type, bool referenced, std::string page_name) :
      choice(NULL),
      page_num(page_num),
      type(type),
      referenced(referenced),
      page_name(page_name) {}
  Page(const Page & rhs);
  Page & operator=(const Page & rhs);
  void printContentandChoice() const;
  std::vector<size_t> printContentandChoicewithCon() const;
  size_t getPageNum() { return page_num; }
  char getType() { return type; }
  bool getReference() { return referenced; }
  size_t getChoiceSize() { return choice->choices.size(); }
  size_t getChoicewithConSize() { return choice->choices_con.size(); }
  size_t getSrcNum() { return choice->src_pageNum; }
  Choice * getChoice() { return choice; }
  long int getConditionVal(const std::string & condition_name) const;
  void setCondition(const std::string & condition_name, long int condition_val);
  std::vector<std::pair<std::pair<std::string, long int>, std::string> >
  getConditionChoices() {
    return choice->choices_con;
  }
  std::vector<size_t> getDesNums() { return choice->des_pageNums; }
  ~Page() {
    if (choice != NULL) {
      delete choice;
    }
  }
  friend void freePages(std::vector<Page *> & pages);
  friend void setReference(std::vector<Page *> & pages);
  friend std::vector<Page *> parseText(std::ifstream & ifs, std::string dirName);
  friend std::vector<Page *> parseTextwithCons(
      std::ifstream & ifs,
      std::string dirName,
      std::vector<std::pair<size_t, std::pair<std::string, long int> > > &
          condition_info);
};

//copy constructor
Page::Page(const Page & rhs) :
    choice(NULL),
    page_num(rhs.page_num),
    type(rhs.type),
    referenced(rhs.referenced),
    page_name(rhs.page_name),
    content(rhs.content) {
  choice =
      new Choice(rhs.choice->src_pageNum, rhs.choice->des_pageNums, rhs.choice->choices);
}
//assignment constructor
Page & Page::operator=(const Page & rhs) {
  if (this != &rhs) {
    Choice * temp = new Choice(
        rhs.choice->src_pageNum, rhs.choice->des_pageNums, rhs.choice->choices);
    delete choice;
    choice = temp;
    content = rhs.content;
    page_num = rhs.page_num;
    type = rhs.type;
    referenced = rhs.referenced;
    page_name = rhs.page_name;
  }
  return *this;
}

//print the content and choices of every page
void Page::printContentandChoice() const {
  std::stringstream ss;
  std::vector<std::string>::const_iterator it_cnt = content.begin();
  while (it_cnt != content.end()) {
    ss << *it_cnt << '\n';
    ++it_cnt;
  }
  if (type == 'W') {
    ss << "Congratulations! You have won. Hooray!\n";
  }
  else if (type == 'L') {
    ss << "Sorry, you have lost. Better luck next time!\n";
  }
  else if (type == 'N') {
    ss << "What would you like to do?\n\n";
    if (choice == NULL) {
      std::cerr << "a normal page has to have choice(s)" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::vector<std::string>::const_iterator it_chs = choice->choices.begin();
    int i = 1;
    while (it_chs != choice->choices.end()) {
      ss << ' ' << i << ". " << *it_chs << '\n';
      ++i;
      ++it_chs;
    }
  }
  std::cout << ss.str();
}
// print the content and choices with condition of every page
std::vector<size_t> Page::printContentandChoicewithCon() const {
  std::vector<size_t> ans;
  std::stringstream ss;
  std::vector<std::string>::const_iterator it_cnt = content.begin();
  while (it_cnt != content.end()) {
    ss << *it_cnt << '\n';
    ++it_cnt;
  }
  if (type == 'W') {
    ss << "Congratulations! You have won. Hooray!\n";
  }
  else if (type == 'L') {
    ss << "Sorry, you have lost. Better luck next time!\n";
  }
  else if (type == 'N') {
    ss << "What would you like to do?\n\n";
    if (choice == NULL) {
      std::cerr << "a normal page has to have choice(s)" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::vector<std::pair<std::pair<std::string, long int>, std::string> >::const_iterator
        it_chs = choice->choices_con.begin();
    int i = 1;
    while (it_chs != choice->choices_con.end()) {
      // check if this choice has no condition
      if (it_chs->first.first == "noCondition") {
        ss << ' ' << i << ". " << it_chs->second << '\n';
      }
      // if this choice has condition
      // compare the choice condition to the page condition which was set when parsing the story.txt
      else {
        long int condition_val = getConditionVal(it_chs->first.first);
        if (condition_val == it_chs->first.second) {
          ss << ' ' << i << ". " << it_chs->second << '\n';
        }
        else {
          ss << ' ' << i << ". "
             << "<UNAVAILABLE>\n";
          // remember the choice numbers that are unavailable
          // make it easier to check if the choice chosen is available afterwards
          ans.push_back(i);
        }
      }
      ++i;
      ++it_chs;
    }
  }
  std::cout << ss.str();
  return ans;
}
// get the condition value based on a condition name in this particular page
long int Page::getConditionVal(const std::string & condition_name) const {
  std::vector<std::pair<std::string, long int> >::const_iterator it = conditions.begin();
  while (it != conditions.end()) {
    if (it->first == condition_name) {
      return it->second;
    }
    ++it;
  }
  return 0;
}
// set a particular pair of condition name and condition value to all pages
// means that after a speical page, a specific condition has been set to all pages
void Page::setCondition(const std::string & condition_name, long int condition_val) {
  if (conditions.empty()) {
    conditions.push_back(std::make_pair(condition_name, condition_val));
  }
  else {
    std::vector<std::pair<std::string, long int> >::iterator it = conditions.begin();
    int found = 0;
    // if this condition is in this page's conditions, change its value to new value
    while (it != conditions.end()) {
      if (it->first == condition_name) {
        it->second = condition_val;
        found = 1;
        break;
      }
      ++it;
    }
    // else if this condition is not in this page's conditions
    // push this new pair of condition name and condition value into the page's conditions
    if (found == 0) {
      conditions.push_back(std::make_pair(condition_name, condition_val));
    }
  }
}
// parse information in story.txt to create pages and related elements
std::vector<Page *> parseText(std::ifstream & ifs, std::string dirName) {
  std::vector<Page *> pages;
  std::string line;
  size_t next_pageNum = 0;
  while (!ifs.eof()) {
    std::getline(ifs, line);
    if (!line.empty()) {
      // page declaration
      if (line.find('@') != std::string::npos) {
        size_t at_pos = line.find('@');
        // check if this line has page number
        if (at_pos == 0) {
          std::cerr << line << " have not declared a page number!" << std::endl;
          exit(EXIT_FAILURE);
        }
        char * end = NULL;
        size_t page_num = strtoull(line.c_str(), &end, 10);
        // check if page number is out of range
        if (errno == ERANGE) {
          std::cerr << "one page number is too large!" << std::endl;
          exit(EXIT_FAILURE);
        }
        // check if page number is valid number
        if (*end != '@') {
          std::cerr << "the format of (" << line << ") is wrong!" << std::endl;
          exit(EXIT_FAILURE);
        }
        // check if page number is sequential
        if (page_num != next_pageNum) {
          std::cerr << "page numbers have to be sequential!" << std::endl;
          exit(EXIT_FAILURE);
        }
        char type = line[at_pos + 1];
        // check if type is valid
        if (type != 'N' && type != 'W' && type != 'L') {
          std::cerr << "valid types for pages only contain N, W and L!" << std::endl;
          exit(EXIT_FAILURE);
        }
        size_t colon = line.find(':');
        // check if colon exists
        if (colon == std::string::npos) {
          std::cerr << "the format of (" << line << ") is wrong!" << std::endl;
          exit(EXIT_FAILURE);
        }
        // check if type is valid, ensure that type is just N, W or L
        if (colon - at_pos != 2) {
          std::cerr << "the type of (" << line << ") is invalid!" << std::endl;
          exit(EXIT_FAILURE);
        }
        std::string page_name = line.substr(colon + 1);
        Page * new_page = new Page(page_num, type, false, page_name);
        pages.push_back(new_page);
        // get name of specific page and load its content
        std::string page_addr = dirName + '/' + page_name;
        std::ifstream page_ifs(page_addr.c_str(), std::ifstream::in);
        // check if the file exists and can be open
        if (!page_ifs) {
          std::cerr << "fail to open file " << page_addr << " or no such file exists"
                    << std::endl;
          exit(EXIT_FAILURE);
        }
        std::string content_line;
        // load the content of this page file into content
        while (!page_ifs.eof()) {
          std::getline(page_ifs, content_line);
          new_page->content.push_back(content_line);
        }
        next_pageNum++;
      }
      // choices declaration, load choices into specific pages
      else {
        size_t first_colon = line.find(':');
        // check if the first colon exists
        if (first_colon == std::string::npos) {
          std::cerr << "the format of (" << line << ") is wrong!" << std::endl;
          exit(EXIT_FAILURE);
        }
        if (first_colon == 0) {
          std::cerr << line << "does not have source page number!" << std::endl;
          exit(EXIT_FAILURE);
        }
        size_t second_colon = line.find(':', first_colon + 1);
        // check if the second colon exists
        if (second_colon == std::string::npos) {
          std::cerr << "the format of (" << line << ") is wrong!" << std::endl;
          exit(EXIT_FAILURE);
        }
        std::string des = line.substr(first_colon + 1, second_colon - first_colon - 1);
        if (des.empty()) {
          std::cerr << line << "does not have destination page number!" << std::endl;
          exit(EXIT_FAILURE);
        }
        char * end = NULL;
        size_t src_pageNum = strtoull(line.c_str(), &end, 10);
        // check if the source page number is out of range
        if (errno == ERANGE) {
          std::cerr << "one source page number is too large!" << std::endl;
          exit(EXIT_FAILURE);
        }
        // check if the source page number is valid number
        if (*end != ':') {
          std::cerr << "the source number in (" << line << ") is invalid!" << std::endl;
          exit(EXIT_FAILURE);
        }
        // check if the specific page has been created before choice declaration
        if (src_pageNum >= pages.size()) {
          std::cerr << "page " << src_pageNum
                    << " has not been created but choice declaration has used it!"
                    << std::endl;
          exit(EXIT_FAILURE);
        }
        // make sure only noraml pages have choices
        if (pages[src_pageNum]->type != 'N') {
          std::cerr << "WIN and LOSE page should not have choices" << std::endl;
          exit(EXIT_FAILURE);
        }
        end = NULL;
        size_t des_pageNum = strtoull(des.c_str(), &end, 10);
        if (errno == ERANGE) {
          std::cerr << "one destination page number is too large!" << std::endl;
          exit(EXIT_FAILURE);
        }
        // check if destination page number is valid number
        if (*end != '\0') {
          std::cerr << "the destination number in (" << line << ") is invalid!"
                    << std::endl;
          exit(EXIT_FAILURE);
        }
        std::string choice = line.substr(second_colon + 1);
        // if this particular page has no choices yet, new one choice
        if (pages[src_pageNum]->choice == NULL) {
          pages[src_pageNum]->choice = new Page::Choice(src_pageNum, des_pageNum, choice);
        }
        // else add a new choice into existed choices
        else {
          pages[src_pageNum]->choice->addChoice(des_pageNum, choice);
        }
      }
    }
  }

  return pages;
}
// set reference for every pages
// means that if one page is referenced by other page(s)
// set its referenced to true
void setReference(std::vector<Page *> & pages) {
  for (std::vector<Page *>::iterator it_pages = pages.begin(); it_pages != pages.end();
       ++it_pages) {
    if ((*it_pages)->choice == NULL) {
      continue;
    }
    else {
      std::vector<size_t>::iterator it_des = (*it_pages)->choice->des_pageNums.begin();
      while (it_des != (*it_pages)->choice->des_pageNums.end()) {
        if (*it_des != (*it_pages)->choice->src_pageNum) {
          if (pages[*it_des]->referenced == false) {
            pages[*it_des]->referenced = true;
          }
          ++it_des;
        }
      }
    }
  }
}

void freePages(std::vector<Page *> & pages) {
  int len = pages.size();
  for (int i = 0; i < len; i++) {
    if (pages[i] != NULL) {
      delete pages[i];
    }
  }
}
// check if the page referenced by destination number is valid
bool verifyValidation(const std::vector<Page *> & pages) {
  size_t len = pages.size();
  for (size_t i = 0; i < pages.size(); ++i) {
    if (pages[i]->getChoice() == NULL) {
      continue;
    }
    else {
      std::vector<size_t> des_pageNums = pages[i]->getDesNums();
      for (size_t j = 0; j < des_pageNums.size(); ++j) {
        // if the page is not created yet or
        // if the page number is not equal to destination number
        // the page is invalid
        if (des_pageNums[j] >= len ||
            pages[des_pageNums[j]]->getPageNum() != des_pageNums[j]) {
          return false;
        }
      }
    }
  }
  return true;
}
// check if every page is referenced by at least one other page
bool verifyReference(const std::vector<Page *> & pages) {
  for (size_t i = 1; i < pages.size(); i++) {
    if (pages[i]->getReference() == false) {
      return false;
    }
  }
  return true;
}
// check if there is at least one WIN page and at least one LOSE page in all of pages
bool verifyWinandLose(const std::vector<Page *> & pages) {
  bool foundWin = false;
  bool foundLose = false;
  for (size_t i = 0; i < pages.size(); ++i) {
    if (pages[i]->getType() == 'W') {
      foundWin = true;
      if (foundLose) {
        break;
      }
    }
    else if (pages[i]->getType() == 'L') {
      foundLose = true;
      if (foundWin) {
        break;
      }
    }
  }
  return foundWin & foundLose;
}
// check if all of the requirements for pages are met
// means that check if all of the pages are referenced and valid
// and at least one WIN page and LOSE page exist
void check(std::vector<Page *> & pages) {
  if (!verifyValidation(pages)) {
    std::cerr << "some page(s) is not valid!" << std::endl;
    exit(EXIT_FAILURE);
  }
  setReference(pages);
  if (!verifyReference(pages)) {
    std::cerr << "some page(s) is not referenced by other pages!" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (!verifyWinandLose(pages)) {
    std::cerr << "Win and(or) Lose pages do not exist!" << std::endl;
    exit(EXIT_FAILURE);
  }
}
// set correct condition name and condition value for every pages
void setConditionForPages(std::vector<Page *> & pages,
                          const std::string & condition_name,
                          long int condition_val) {
  std::vector<Page *>::iterator it = pages.begin();
  while (it != pages.end()) {
    // iteratively use setCondition to set condition for all pages
    (*it)->setCondition(condition_name, condition_val);
    ++it;
  }
}
// parse the content of story.txt with conditions
// besids recognize the old types of line, this function can recognize new types of line
// and save corresponding elements into pages
std::vector<Page *> parseTextwithCons(
    std::ifstream & ifs,
    std::string dirName,
    std::vector<std::pair<size_t, std::pair<std::string, long int> > > & condition_info) {
  std::vector<Page *> pages;
  std::string line;
  size_t next_pageNum = 0;
  while (!ifs.eof()) {
    std::getline(ifs, line);
    if (!line.empty()) {
      char * end = NULL;
      size_t page_num = strtoull(line.c_str(), &end, 10);
      // check if page number is out of range
      if (errno == ERANGE) {
        std::cerr << "the page number in (" << line << ") is out of range!" << std::endl;
        exit(EXIT_FAILURE);
      }
      // check the format of this line
      if (*end != '@' && *end != '$' && *end != ':' && *end != '[') {
        std::cerr << "the format of (" << line << ") is wrong!" << std::endl;
        exit(EXIT_FAILURE);
      }
      // page declaration
      if (line.find('@') != std::string::npos && *end == '@') {
        // check if page number is sequential
        if (page_num != next_pageNum) {
          std::cerr << "page numbers have to be sequential!" << std::endl;
          exit(EXIT_FAILURE);
        }
        size_t at_pos = line.find('@');
        // check if page number exists
        if (at_pos == 0) {
          std::cerr << "page number in (" << line << ") does not exist!" << std::endl;
          exit(EXIT_FAILURE);
        }
        //size_t page_num = strtoull(line.c_str(), NULL, 10);
        char type = line[at_pos + 1];
        // check if type is valid
        if (type != 'N' && type != 'W' && type != 'L') {
          std::cerr << "valid types for pages only contain N, W and L!" << std::endl;
          exit(EXIT_FAILURE);
        }
        size_t colon = line.find(':');
        // check if colon exists
        if (colon == std::string::npos) {
          std::cerr << "the format of (" << line << ") is wrong!" << std::endl;
          exit(EXIT_FAILURE);
        }
        // check if type is valid, ensure that type is just N, W or L
        if (colon - at_pos != 2) {
          std::cerr << "the type of (" << line << ") is invalid!" << std::endl;
          exit(EXIT_FAILURE);
        }
        std::string page_name = line.substr(colon + 1);
        Page * new_page = new Page(page_num, type, false, page_name);
        pages.push_back(new_page);
        std::string page_addr = dirName + '/' + page_name;
        std::ifstream page_ifs(page_addr.c_str(), std::ifstream::in);
        // check if the file exists and can be open
        if (!page_ifs) {
          std::cerr << "fail to open " << page_addr << " or the file does not exist!"
                    << std::endl;
          exit(EXIT_FAILURE);
        }
        std::string content_line;
        // load the content of each page file into coresponding content
        while (!page_ifs.eof()) {
          std::getline(page_ifs, content_line);
          new_page->content.push_back(content_line);
        }
        next_pageNum++;
      }
      // set choice condition
      else if (line.find('$') != std::string::npos && *end == '$') {
        size_t dollar_sign = line.find('$');
        // check if page number exist
        if (dollar_sign == 0) {
          std::cerr << "the page number in (" << line << ") does not exist!" << std::endl;
          exit(EXIT_FAILURE);
        }
        size_t equal = line.find('=');
        // check if equal exists
        if (equal == std::string::npos) {
          std::cerr << "the format of (" << line << ") is wrong!" << std::endl;
          exit(EXIT_FAILURE);
        }
        std::string condition_name =
            line.substr(dollar_sign + 1, equal - dollar_sign - 1);
        std::string temp = line.substr(equal + 1);
        // check if the condition value exists
        if (temp.empty()) {
          std::cerr << "the condition value in (" << line << ") does not exist!"
                    << std::endl;
          exit(EXIT_FAILURE);
        }
        char * newEnd = NULL;
        long int condition_val = strtol(temp.c_str(), &newEnd, 10);
        // check if the condition value is out of range
        if (errno == ERANGE) {
          std::cerr << "the condition value is too large" << std::endl;
          exit(EXIT_FAILURE);
        }
        // check if the condition value is valid
        if (*newEnd != '\0') {
          std::cerr << "the condition value is invalid" << std::endl;
          exit(EXIT_FAILURE);
        }
        condition_info.push_back(
            std::make_pair(page_num, std::make_pair(condition_name, condition_val)));
        pages[page_num]->conditions.push_back(
            std::make_pair(condition_name, condition_val));
      }
      // choices declaration
      else {
        size_t first_colon = line.find(':');
        // check if the first colon exists
        if (first_colon == std::string::npos) {
          std::cerr << "the format of (" << line << ") is wrong!" << std::endl;
          exit(EXIT_FAILURE);
        }
        // check if source page number exists
        if (first_colon == 0) {
          std::cerr << line << "does not have source page number!" << std::endl;
          exit(EXIT_FAILURE);
        }
        size_t second_colon = line.find(':', first_colon + 1);
        // check if the second colon exists
        if (second_colon == std::string::npos) {
          std::cerr << "the format of (" << line << ") is wrong!" << std::endl;
          exit(EXIT_FAILURE);
        }
        std::string des = line.substr(first_colon + 1, second_colon - first_colon - 1);
        // check if a destination page number exists
        if (des.empty()) {
          std::cerr << line << "does not have destination page number!" << std::endl;
          exit(EXIT_FAILURE);
        }
        char * newEnd = NULL;
        size_t src_pageNum = strtoull(line.c_str(), &newEnd, 10);
        // check if the source page number is out of range
        if (errno == ERANGE) {
          std::cerr << "the source page number is too large" << std::endl;
          exit(EXIT_FAILURE);
        }
        // check if the source page number is valid number
        if (*newEnd != ':' && *newEnd != '[') {
          std::cerr << "the source number in (" << line << ") is invalid!" << std::endl;
          exit(EXIT_FAILURE);
        }
        // check if the specific page has been created before choice declaration
        if (src_pageNum >= pages.size()) {
          std::cerr << "page " << src_pageNum
                    << " has not been created but choice declaration has used it!"
                    << std::endl;
          exit(EXIT_FAILURE);
        }
        // make sure only noraml pages have choices
        if (pages[src_pageNum]->type != 'N') {
          std::cerr << "WIN and LOSE page should not have choices" << std::endl;
          exit(EXIT_FAILURE);
        }
        newEnd = NULL;
        size_t des_pageNum = strtoull(des.c_str(), &newEnd, 10);
        if (errno == ERANGE) {
          std::cerr << "the destination page number is too large" << std::endl;
          exit(EXIT_FAILURE);
        }
        // check if destination page number is valid number
        if (*newEnd != '\0') {
          std::cerr << "the destination number in (" << line << ") is invalid!"
                    << std::endl;
          exit(EXIT_FAILURE);
        }
        std::string choice = line.substr(second_colon + 1);
        std::string condition_name;
        long int condition_val;
        size_t first_brace = line.find('[');
        // if this line is a common choice, no condition in this line
        if (first_brace == std::string::npos) {
          condition_name = "noCondition";
          condition_val = -1;
        }
        else {
          size_t second_brace = line.find(']');
          // check if the second brace exists
          if (second_brace == std::string::npos) {
            std::cerr << "the format of (" << line << ") is wrong!" << std::endl;
            exit(EXIT_FAILURE);
          }
          std::string con = line.substr(first_brace + 1, second_brace - first_brace - 1);
          size_t equal = con.find('=');
          // check if the equal exists
          if (equal == std::string::npos) {
            std::cerr << "the format of condition choice in (" << line << ") is wrong!"
                      << std::endl;
            exit(EXIT_FAILURE);
          }
          condition_name = con.substr(0, equal);
          std::string temp = con.substr(equal + 1);
          // check if the condition value exists
          if (temp.empty()) {
            std::cerr << "the condition value in (" << line << ") does not exist!"
                      << std::endl;
            exit(EXIT_FAILURE);
          }
          char * newEnd = NULL;
          condition_val = strtol(temp.c_str(), &newEnd, 10);
          // check if the condition value is out of range
          if (errno == ERANGE) {
            std::cerr << "the condition value in (" << line << ") is too large!"
                      << std::endl;
            exit(EXIT_FAILURE);
          }
          // check if the condition value is valid
          if (*newEnd != '\0') {
            std::cerr << "the condition value in (" << line << ") is invalid!"
                      << std::endl;
            exit(EXIT_FAILURE);
          }
        }
        if (pages[src_pageNum]->choice == NULL) {
          pages[src_pageNum]->choice = new Page::Choice(
              src_pageNum, des_pageNum, condition_name, condition_val, choice);
        }
        else {
          pages[src_pageNum]->choice->addChoicewithCon(
              des_pageNum, condition_name, condition_val, choice);
        }
      }
    }
  }

  return pages;
}
#endif
