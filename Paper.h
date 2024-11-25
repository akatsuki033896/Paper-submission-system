#pragma once
#include "Author.h"
#include "Paper.h"
#include <deque>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>


using namespace std;
class Paper
{
  private:
	int id;
	string title;
	string file_address;
	vector<pair<int, string>> author;
	vector<int> key_word;
	string abstract;
	int paper_state;		   // 0等待编辑处理，1在审，-1拒绝，2审完等待编辑处理,3接收
	vector<bool> update_state; // 初始里面是5个0，只有当审稿人更新意见时才会变
	vector<pair<string, int>> review_comment;
	bool in_process;
	int reivewer_need; // 需要编辑分配几个审稿人，只有在审稿人拒审的时候才会为1
	int editor;
	int repair_cnt;

  public:
	Paper()
	{
		id = 0;
		title.reserve(128);
		author.reserve(32);
		file_address.reserve(512);
		key_word.reserve(8);
		abstract.reserve(4096);
		paper_state = 0;
		update_state.reserve(5);
		review_comment.reserve(5);
		in_process = 0;
		editor = 0;
		repair_cnt = 0;
		reivewer_need = 0;
		update_state.assign(5, 0);
	}
	int getId() const
	{
		return id;
	}

	const string &getTitle() const
	{
		return title;
	}

	const string &getFileAddress() const
	{
		return file_address;
	}

	vector<pair<int, string>> &getAuthor()
	{
		return author;
	}

	vector<int> &getKeyWord()
	{

		return key_word;
	}

	const string &getAbstractText() const
	{
		return abstract;
	}

	int getPaperState() const
	{
		return paper_state;
	}

	vector<bool> *getUpdateState()
	{
		return &update_state;
	}

	vector<pair<string, int>> &getReviewComment()
	{
		return review_comment;
	}

	bool isInProcess() const
	{
		return in_process;
	}

	int getReviewerNeed() const
	{
		return reivewer_need;
	}

	int getEditor() const
	{
		return editor;
	}
	void modify_id(int x)
	{
		id = x;
	}
	void modify_state(int x)
	{
		paper_state = x;
	}
	void modify_in_process(bool x)
	{
		in_process = 1;
	}

	void modify_reviewer_need(int x)
	{
		reivewer_need = x;
	} // Added

	void modify_review_comment(pair<string, int> x)
	{
		review_comment.push_back(x);
	} // Added

	void Repair(Paper x, string new_paper_address, deque<int> *dq)
	{
		title = x.getTitle();
		key_word.clear();
		key_word = x.getKeyWord();
		abstract = x.getAbstractText();
		file_address = new_paper_address;
		author.clear();
		author = x.getAuthor();
		paper_state = 0;
		repair_cnt++;
		review_comment.clear();
		update_state.clear();
		update_state.assign(5, 0);
		dq.push_back(x);
		x.in_process = 1;
	}
	void printinfo(ostream &os, const map<string, Author> &AuthorSet, const map<int, string> KEY_WORD)
	{
		os << "ID:" << id << '\n';
		os << "标题:" << title << '\n';
		os << "作者:\n";
		author.sort(author.begin(), author.end());
		for (auto u : author)
		{
			if (u.first > 1000)
			{
				os << "通讯作者:\n";
			}
			AuthorSet[u.second].print(os);
		}
		os << "关键词:\n";
		for (auto u : key_word)
		{
			os << KEY_WORD[u] << ' ';
		}
		os << "\n\n";
	}
};