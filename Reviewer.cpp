#include "Reviewer.h"
#include <deque>
#include <iostream>
#include <string>
#include <utility>

using namespace std;
Reviewer::Reviewer()
{
	ORCID.reserve(32);
	name.reserve(256);
	workplace.reserve(256);
	email.reserve(256);

	key_word.reserve(8);
	// paperlisr.reserve(512); ???
	reviewed_list.reserve(128);
	review_wait.reserve(128);
	review_request.reserve(128);
}

const string &Reviewer::getORCID() const
{
	return ORCID;
}

const string &Reviewer::getName() const
{
	return name;
}

const string &Reviewer::getWorkplace() const
{
	return workplace;
}

const std::string &Reviewer::getEmail() const
{
	return email;
}

const vector<int> &Reviewer::getKeyWord() const
{
	return key_word;
}

const pair<unsigned long long int, unsigned long long int> &Reviewer::getHashedPassword() const
{
	return hashed_password;
}

vector<std::pair<int, int>> &Reviewer::getReviewedList()
{
	return reviewed_list;
}

vector<int> &Reviewer::getReviewWait()
{
	return review_wait;
}

vector<int> &Reviewer::getReviewRequest()
{
	return review_request;
}

void Reviewer::modify_Name(string new_name)
{
	name = new_name;
}

void Reviewer::modify_Email(string new_email)
{
	email = new_email;
}

void Reviewer::modify_workplace(string new_workplace)
{
	workplace = new_workplace;
}

bool Reviewer::verify(string password)
{
	if (HASH(password) == hashed_password)
		return 1;
	return 0;
}

string Reviewer::getPaper(int x, vector<Paper> &PaperSet)
{
	return PaperSet[x].getFileAddress();
}

string Reviewer::getAbstract(int x, vector<Paper> &PaperSet)
{
	return PaperSet[x].getAbstractText();
}

void Reviewer::review_view(vector<Paper> &PaperSet)
{
	int size = PaperSet.size();
	for (int i = 0; i < PaperSet.size(); i++)
	{
		cout << "Title: " << PaperSet[i].getTitle() << endl;
    
    cout << "Keywords: ";
    for (int j = 0; j < PaperSet[i].getKeyWord().size(); j++)
    {
      cout << PaperSet[i].getKeyWord()[j] << " ";
    }
    
    cout << "\nAuthor: ";
    for (int k = 0; k < PaperSet[i].getAuthor().size(); k++)
    {
      cout << PaperSet[i].getAuthor()[k].first << " ";
      cout << PaperSet[i].getAuthor()[k].second << " ";
    }

    cout << "\nAbstract: ";
		cout << PaperSet[i].getAbstractText() << endl;
	}
}

void Reviewer::review_reject(int x, vector<Paper> &PaperSet, deque<int> &dq)
{
	// PaperSet[x].reivewer_need++;
  // Add modifyReviewerNeed() in Paper;
  PaperSet[x].modify_reviewer_need(PaperSet[x].getReviewerNeed() + 1);
	if (!PaperSet[x].isInProcess())
	{
		PaperSet[x].modify_in_process(1);
	}
	dq.push_back(x);
	// 双端队列
}

void Reviewer::review_decide(int x, vector<Paper> &PaperSet) {
  // Add modify_review_comment in Paper
  // PaperSet[x].review_comment.push_back(make_pair(ORCID, -1));
  PaperSet[x].modify_review_comment(make_pair(ORCID, -1));
}
