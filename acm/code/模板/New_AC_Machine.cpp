//使用时先调用 PreProcess()然后插入字符串,再调用BFS函数建立失败指针
//例如
PreProcess();
for (i = 0; i < n; i++)
{
    scanf("%s", str);
    Insert(str, true);
}
BFS();



//AC Machine
const int TSIZE=100+5;  //状态个数上限=单词总数*单词长度
const int CN=4;         //可选择字符数

struct Trie             //Trie 结构
{
    int c[CN];          
    int fail;           //fail指针
    bool flag;           //状态标志(有时需要int类型)
    void init()        //节点初始化
    {
        memset(c,0,sizeof(c));
        fail=-1;
        flag=0;
    }
};

Trie trie[TSIZE];
int len;               //当前长度
void PreProcess()  
{
    trie[0].init();
    len=1;
}

int Get(char ch)  //根据具体题目修改
{
    switch (ch)
    {
        case 'A':return 0;break;
        case 'T':return 1;break;
        case 'C':return 2;break;
        case 'G':return 3;break;
    }
}

void Insert(char *str,bool id)  //插入单词,标志
{
    int r,no;
    int i;
    r=0;
    for (i=0;str[i];i++)
    {
        no=Get(str[i]);
        if (!trie[r].c[no])
        {
            trie[len].init();
            trie[r].c[no]=len++;
        }
        r=trie[r].c[no];
    }
    trie[r].flag=id;
}

queue<int>que;
void BFS()               //利用BFS建立失败指针,构造trie图
{
    while (!que.empty()) que.pop();
    que.push(0);         //根进队列
    int cur,fail,pos;
    int i;
    while (!que.empty())
    {
        cur=que.front();
        que.pop();
        for (i=0;i<CN;i++)
            if (trie[cur].c[i])
            {
                pos=trie[cur].c[i];
                que.push(pos);
                fail=trie[cur].fail;
                while (fail!=-1 && !trie[fail].c[i]) fail=trie[fail].fail;
                if (fail!=-1)
                    trie[pos].fail=trie[fail].c[i];    //连接失败指针
                else
                    trie[pos].fail=0;

             //必要时可以在此处添加一句处理标志,可以避免以后查找需要遍历失败指针
             //例如   trie[pos].flag|=trie[trie[pos].fail].flag;
            }
            else
            {
                 if (trie[cur].fail!=-1)                 //完善trie图
                     trie[cur].c[i]=trie[trie[cur].fail].c[i];
            }
    }
}

//AC Machine