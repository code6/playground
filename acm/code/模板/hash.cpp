
const int MAX=100000+5;
const int HASH_SIZE=262144;
const int BUFFER=90000;




//hash_table
struct Hash_Node
{
    int v,next;
    int tag;
};    

Hash_Node hash_table[HASH_SIZE+BUFFER];
int hash_top;
bool hash_flag[HASH_SIZE];

int hash(int v)
{
    if (v<0) v=-v;
    return v&(HASH_SIZE-1);
}    

void Hash_Init()
{
    memset(hash_flag,0,sizeof(hash_flag));
    hash_top=HASH_SIZE;
}    

void Hash_Insert(int v,int tag)
{
    int pos=hash(v);
    if (!hash_flag[pos])
    {
        hash_flag[pos]=true;
        hash_table[pos].v=v;
        hash_table[pos].tag=tag;
        hash_table[pos].next=-1;
        return;
    }    
    while (true)
    {
        if (hash_table[pos].v==v) 
        {
            hash_table[pos].tag=tag;
            return;            
        }    
        if (hash_table[pos].next==-1) break;
        pos=hash_table[pos].next;
    }      
    hash_table[pos].next=hash_top;
    hash_table[hash_top].v=v;
    hash_table[hash_top].tag=tag;
    hash_table[hash_top].next=-1;
    hash_top++;    
}  

int Hash_Query(int v)
{
   int pos=hash(v);
   if (!hash_flag[pos]) return -1;
   while (true)
    {
        if (hash_table[pos].v==v) return pos;
        if (hash_table[pos].next==-1) return -1;
        pos=hash_table[pos].next;
    }  
}      

