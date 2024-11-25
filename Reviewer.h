#include "Author.h"
#include "Paper.h"
#include "Reviewer_Comment.h"
#include <cstring>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Reviewer
{
	string ORCID;
	string name;
	string workplace;
	string email;
	vector<int> key_word;
	pair<unsigned long long int, unsigned long long int> hashed_password;
	vector<pair<int, int>> reviewed_list; // 存储pair类型，元素为论文id,审稿意见id
	vector<int> review_wait;			  // 存储论文id
	vector<int> review_request;			  // 存储论文id

  public:
	Reviewer();

	const string &getORCID() const;
	const string &getName() const;
	const string &getWorkplace() const;
	const string &getEmail() const;
	const vector<int> &getKeyWord() const;
	const pair<unsigned long long int, unsigned long long int> &getHashedPassword() const;
	vector<std::pair<int, int>> &getReviewedList();
	vector<int> &getReviewWait();
	vector<int> &getReviewRequest();
	string getPaper(int x, vector<Paper> &PaperSet);
	string getAbstract(int x, vector<Paper> &PaperSet);

	void modify_Name(string new_name);
	void modify_Email(string new_email);
	void modify_workplace(string new_workplace);

	static unsigned long long int hash1(const string &str, unsigned long long int mod)
	{
		unsigned long long int hash = 0;
		for (char c : str)
		{
			hash = (hash * 31 + c) % mod;
		}
		return hash;
	}

	static unsigned long long int hash2(const string &str, unsigned long long int mod)
	{
		unsigned long long int hash = 0;
		for (char c : str)
		{
			hash = (hash * 17 + c) % mod;
		}
		return hash;
	}

	static pair<unsigned long long int, unsigned long long int> HASH(string orgpw)
	{
		unsigned long long int mod1 = 1e9 + 7;
		unsigned long long int mod2 = 1e9 + 9;
		unsigned long long int h1 = hash1(orgpw, mod1);
		unsigned long long int h2 = hash2(orgpw, mod2);
		return make_pair(h1, h2);
	}

	bool verify(string password);

	// 审稿人行为
  // 查看审稿请求: 传入类型为Paper的vector类待审列表
  void review_view(vector<Paper> &PaperSet);
	// 拒绝审稿请求：回传int，代表被拒绝审稿的论文id
	void review_reject(int x, vector<Paper> &PaperSet, deque<int> &dq);
	// 决定审稿：回传int，代表决定审稿的论文id
	void review_decide(int x, vector<Paper> &PaperSet);
	// 查看目前待审稿列表：利用OBJ对象中的review_wait.size(),创建对应大小的论文对象数组，
	// 并从后端接收一个论文类对象数组。
	void review_update(int x, vector<Paper> &PaperSet, vector<Reviewer_Comment> *CommentSet, Reviewer_Comment feed_back,
					   deque<int> *dq);
};
