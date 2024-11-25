编辑类和后端的交互太多，我来前后端一起写，看能不能想点啥办法省点事

作者，论文和审稿人的交互就交给大家了

我们考虑采用先指令后数据的交互形式，即对于一个可能和后端发生交互的行为，先传递给后端一个指令代码，告知后端你要干啥，再传递可能存在的数据，如果没有数据就不传了

Paper类中：Review_comment pair的string代表审稿人的ORCID，int代表审稿意见编号。

首先是身份选择，这个仅回传指令，回传1代表作者身份，2代表审稿人身份
下面开始说对应身份的情况
作者：
登录/注册
登陆时回传指令3，创建一个对应类的对象，只需要填入ORCID和hashed_password（verify是给我在后端用的，前端不用，前端用HASH对用户输入的密码处理一下存到hashed_password即可），然后回传。并且准备接收一个来自客户端的bool，如果是0代表登录失败，如果是1代表已经登录。
注册时回传指令4，创建一个对应类的对象，回传 ORC，名字，单位，email，哈希后的密码。并且准备接收一个来自客户端的bool，如果是0代表注册失败(ORC已经被注册了)，如果是1代表注册成功。注册成功后不保留登录状态，还需要再登录。

登录成功后，前端准备接收一个Author对象OBJ，里面塞的是来自后端的信息

现在讨论作者登录后的情况，前面的数字代表对应指令代码，一定切记先回传指令代码：

5.信息修改：仅仅允许修改名字，单位，email三项，回传一个修改过这三项的对象，后端直接拿着这个对象去更新。

6.查看已经投稿的论文：使用OBJ中paperlist的size（）设置一个这么大的paper类数组，接收来自后端的论文类对象。然后在用户界面展示出来。这里前端逻辑自由发挥，反正数据都给了(可以列表页仅显示论文标题，然后还能进去选详情页之类的………),只要记得给数字代码换成实际的汉字就行。不可见的对象在类里面有标记。


7.投稿：
	要求用户填title，作者列表(注意区分共同一作，作者，和通讯，可以要求用户三次输入)。每个作者都需要用户输入ORCID，名字，单位，邮箱。 关键字(只允许用户从我们列出来的关键字中选，数组里面塞数字)。其他留空(id后端分配)，回传给后端。然后再发起论文PDF上传，后端会接收PDF，存储，并且编号关联等等工作。

	8.返修，返修允许修改title，author列表，摘要，key_word，把这四个改好，id还用原来那个论文的，返回一个Paper类的对象，只填充这五个后传递给后端即可。然后再发起论文PDF上传，后端会接收PDF，存储，并且编号关联等等工作。
审稿人：
审稿人不允许注册，到时候就说我们采取编辑邀请制度，这也符合现代期刊投稿情况

Reviewed_list中的第一个int指论文id，第二个int指审稿意见id
请求和待审列表中int都代表论文id

登录
登陆时回传指令9，创建一个对应类的对象，只需要填入ORCID和hashed_password（verify是给我在后端用的，前端不用，前端用HASH对用户输入的密码处理一下存到hashed_password即可），然后回传。并且准备接收一个来自客户端的bool，如果是0代表登录失败，如果是1代表已经登录。

登录成功后，前端准备接收一个Reviewer对象OBJ，里面塞的是来自后端的信息
审稿人允许的行为有：
10：查看审稿请求：利用OBJ对象中的review_request.size()创建对应大小的论文对象数组，并从后端接收一个论文类对象数组。剩下自由发挥，审稿人可以看到论文的标题，摘要，关键字，作者，其他的看不到。
11：拒绝审稿请求：回传int，代表被拒绝审稿的论文id。

12：决定审稿：回传int，代表决定审稿的论文id。

13：查看目前待审稿列表：利用OBJ对象中的review_wait.size(),创建对应大小的论文对象数组，并从后端接收一个论文类对象数组。剩下自由发挥，审稿人可以看到论文的标题，摘要，关键字，作者，其他的看不到。（这里就体现了同步数据的重要性，前后端的数据要是同步的）。

14：下载论文，这个依附于当前待审稿，也就是说仅仅允许下载已经接收审稿请求的稿件。回传论文的id，并从后端接收文件。（文件名可以设置为当前论文id的名字）

15：提供审稿意见：
生成一个审稿意见类对象，id留空，paper_id，reviewer_ORCID, string comment记得填,并回传这个审稿意见类对象。




SP操作:1000 请求论文信息:传到后端一个int论文id，后端返回一个论文类对象
SP操作:1001 请求审稿意见：传到后端一个int审稿意见id，后端返回一个审稿意见类对象
SP操作1002 刷新作者信息：传到后端一个string ORCID，注意字符串长度预分配为32位以后再赋值，后端返回一个 Author类
SP操作1003 刷新审稿人信息：传到后端一个string ORCID，注意字符串长度预分配为32位以后再赋值，后端返回一个 reviewer类