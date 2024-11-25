#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
class Author;
class Paper
{
private:
	int id;
	string title;
	string file_address;
	vector<pair<int,string> >author;
	vector<int> key_word;
	string abstract_text;
	int paper_state;//0等待编辑处理，1在审，-1拒绝，2审完等待编辑处理,3接收
	vector<bool> update_state;//初始里面是5个0，只有当审稿人更新意见时才会变
	vector<pair<string, int> >review_comment;
	bool in_process;
	int reivewer_need;//需要编辑分配几个审稿人，只有在审稿人拒审的时候才会为1
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
        review_comment(5);
        in_process = 0;
        editor = 0;
        repair_cnt = 0;
        reivewer_need = 0;
        update_state.asign(5, 0);
    }
    int getId() const
    {
        return id;
    }

    const string& getTitle() const
    {
        return title;
    }

    const string& getFileAddress() const 
    {
        return file_address;
    }

    vector<pair<string, int>>* getAuthor() 
    {
        return &author;
    }

    vector<int>* getKeyWord() 
    {

        return &key_word;
    }

    const string& getAbstractText() const 
    {
        return abstract_text;
    }

    int getPaperState() const 
    {
        return paper_state;
    }

    vector<bool>* getUpdateState() 
    {
        return &update_state;
    }

    vector<pair<string, int>>* getReviewComment() 
    {
        return &review_comment;
    }

    bool isInProcess() const 
    {
        return in_process;
    }

    int getReviewerNeed() const 
    {
        return reviewer_need;
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
    void Repair(Paper x,string new_paper_address,deque<int> *dq)
    {
        title = x.getTitle();
        key_word.clear();
        key_word = x.getKeyWord();
        abstract_text = x.getAbstractText();
        file_address = new_paper_address;
        author.clear();
        author = x.getAuthor();
        paper_state = 0;
        repair_cnt++;
        review_comment.clear();
        update_state.clear();
        update_state.asign(5, 0);
        dq.push_back(x);
        x.in_process = 1;
    }
    void printinfo (ostream& os,const map<string,Author> &AuthorSet,const map<int,string> KEY_WORD) 
    {
        os<<"ID:"<<id<<'\n';
        os<<"标题:"<<title<<'\n';
        os << "作者:\n";
        author.sort(author.begin(),author.end());
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
class Author()
{
    string ORCID;
    string name;
    string workplace;
    string email;
    vector<int> paperlist;
    pair<unsigned long long int, unsigned long long int> hashed_password;
public :
    Author()
    {
        ORCID.reserve(32);
        name.reserve(256);
        workplace.reserve(256);
        email.reserve(256);
        paperlisr.reserve(512);
    }
    string getORCID()
    {
        return ORCID;
    }
    string getWorkplace()
    {
        return workplace;
    }
    string getName()
    {
        return name;
    }
    string getEmail()
    {
        return email;
    }
    vector<int>* getPaperList()
    {
        return &paperlist;
    }
    void modify_Name(string new_name)
    {
        name = new_name;
    }
    void modify_Email(string new_email)
    {
        email = new_email;
    }
    void modify_workplace(string new_workplace)
    {
        workplace = new_workplace;
    }
    static unsigned long long int hash1(const string & str, unsigned long long int mod)
    {
        unsigned long long int hash = 0;
        for (char c : str) {
            hash = (hash * 31 + c) % mod;
        }
        return hash;
    }
    static unsigned long long int hash2(const string & str, unsigned long long int mod)
    {
        unsigned long long int hash = 0;
        for (char c : str) {
            hash = (hash * 17 + c) % mod;
        }
        return hash;
    }
    static pair<unsigned long long int, unsigned long long int> HASH(string orgpw)
    {
        unsigned long long int mod1 = 1e9 + 7;
        unsigned long long int mod2 = 1e9 + 9;
        unsigned long long int h1 = hash1(str, mod1);
        unsigned long long int h2 = hash2(str, mod2);
        return make_pair(h1, h2);
    }
    bool Verify(string password)
    {
        if (HASH(password) == hashed_password)
            return 1;
        return 0;
    }
};
Class Reviewer_Comment()
{
    int id;
    int paper_id;
    string comment;
    int score;
    Reviewer_Comment()
    {
        comment.reserve(8192);
    }
    int getId()
    {
        return id;
    }
    int getPaperid()
    {
        return paper_id;
    }
    string getComment()
    {
        return comment;
    }
    int getScore()
    {
        return score;
    }
}
class Reviewer
{
    string ORCID;
    string name;
    string workplace;
    string email;
    vector<int> key_word;
    pair<unsigned long long int, unsigned long long int> hashed_password;
    vector<pair<int, int> >reviewed_list;
    vector<int> review_wait;
    vector<int> vector<int> review_request;
    public
    Reviewer()
    {
        ORCID.reserve(32);
        name.reserve(256);
        workplace.reserve(256);
        email.reserve(256);
        paperlisr.reserve(512);
        key_word.reserve(8);
        reviewed_list.reserve(128);
        review_wait.reserve(128);
        review_request.reserve(128);
    }
    const std::string& getORCID() const { return ORCID; }
    const std::string& getName() const { return name; }
    const std::string& getWorkplace() const { return workplace; }
    const std::string& getEmail() const { return email; }
    std::vector<int>* getKeyWord() const
    { 
        return &key_word;
    }
    const std::pair<unsigned long long int, unsigned long long int>& getHashedPassword() const { return hashed_password; }
    vector<std::pair<int, int>>* getReviewedList()
    {
        return &reviewed_list; 
    }
    vector<int>* getReviewWait() 
    {
        return &review_wait;
    }
    vector<int>* getReviewRequest()
    { 
        return &review_request;
    }
    void modify_Name(string new_name)
    {
        name = new_name;
    }
    void modify_Email(string new_email)
    {
        email = new_email;
    }
    void modify_workplace(string new_workplace)
    {
        workplace = new_workplace;
    }
    static unsigned long long int hash1(const string& str, unsigned long long int mod)
    {
        unsigned long long int hash = 0;
        for (char c : str) {
            hash = (hash * 31 + c) % mod;
        }
        return hash;
    }
    static unsigned long long int hash2(const string& str, unsigned long long int mod)
    {
        unsigned long long int hash = 0;
        for (char c : str) {
            hash = (hash * 17 + c) % mod;
        }
        return hash;
    }
    static pair<unsigned long long int, unsigned long long int> HASH(string orgpw)
    {
        unsigned long long int mod1 = 1e9 + 7;
        unsigned long long int mod2 = 1e9 + 9;
        unsigned long long int h1 = hash1(str, mod1);
        unsigned long long int h2 = hash2(str, mod2);
        return make_pair(h1, h2);
    }
    bool Verify(string password)
    {
        if (HASH(password) == hashed_password)
            return 1;
        return 0;
    }
    string getPaper(int x,vector<Paper>* PaperSet)
    {
        return PaperSet[x].getFileAddress();
    }
    string getAbstract(int x, vector<Paper>* PaperSet)
    {
        return PaperSet[x].getAbstractText();
    }
    void review_reject(int x, vector<Paper>* PaperSet,deque<int> *dq)
    {
        PaperSet[x].reivewer_need++;
        if (!PaperSet[x].isInProcess())
        {
            PaperSet[x].modify_in_process(1);
        }
        dq.front_back(x);
        //需要回做回双端队列
    }
    void review_decide(int x, vector<Paper>* PaperSet)
    {
        PaperSet[x].review_comment.push_back(make_pair(ORCID, -1));
        //相当于占了一个审稿人位置
    }
    void review_update(int x, vector<Paper>* PaperSet, vector<Comment>* CommentSet,Comment feed_back,deque<int>* dq)
    {
        //这里的feed_back是来自前端传回的
        //除了没有意见id以外啥都有
        feed_back.id = CommentSet->size();
        CommentSet->push_back(feed_back);
        //这样feed_back的id就是其实际位置
        for (int i = 0; i < PaperSet[x].review_comment.size(); i++)
        {
            if (PaperSet[x].review_comment[i].first == ORCID)
            {
                PaperSet[x].review_comment[i].second = feed_back.id;
                PaperSet[x].update_state[i] = 1;
                break;
            }
            if (i == PaperSet[x].review_comment.size() - 1)
            {
                cout << "MISTAKE:UNFIND REVIEWER!\n";
            }
        }
        bool Flag = 1;
        fot(auto i : PaperSet[x].update_state)
        {
            Flag &= i;
        }
        if (Flag == 1)
        {
            //如果所有审稿人都到位并且上传意见了
            //就更新文件状态为已经审完
            paper_state = 2;
            dq.push_back(x);//回做到双端队列里面;
        }
    }
};
class Editor()
{
private:
    int id;
    pair<unsigned long long int, unsigned long long int> hashed_password;
    vector<int> paperlist;
public:
    Editor()
    {
        paperlist.reserve(4096);
    }
    static unsigned long long int hash1(const string & str, unsigned long long int mod)
    {
        unsigned long long int hash = 0;
        for (char c : str) {
            hash = (hash * 31 + c) % mod;
        }
        return hash;
    }
    static unsigned long long int hash2(const string & str, unsigned long long int mod)
    {
        unsigned long long int hash = 0;
        for (char c : str) {
            hash = (hash * 17 + c) % mod;
        }
        return hash;
    }
    static pair<unsigned long long int, unsigned long long int> HASH(string orgpw)
    {
        unsigned long long int mod1 = 1e9 + 7;
        unsigned long long int mod2 = 1e9 + 9;
        unsigned long long int h1 = hash1(str, mod1);
        unsigned long long int h2 = hash2(str, mod2);
        return make_pair(h1, h2);
    }
    bool Verify(string password)
    {
        if (HASH(password) == hashed_password)
            return 1;
        return 0;
    }
}