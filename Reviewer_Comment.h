#include <string>
using namespace std;

class Reviewer_Comment {
  int id;
  int paper_id;
  string comment;
  int score;
  Reviewer_Comment() { comment.reserve(8192); }
  int getId() { return id; }
  int getPaperid() { return paper_id; }
  string getComment() { return comment; }
  int getScore() { return score; }
};