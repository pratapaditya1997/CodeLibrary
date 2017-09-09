struct node{
    int count;
    node* bit[2];
    node(){
        count=0;
        bit[0]=bit[1]=NULL;
    }
};
 
 
void insert(int s, node* root){
    node* cur = root;
    int x;
    for(int i=31;i>=0;i--){
        if(s&(1<<i)) x=1;
        else x=0;
        if(cur->bit[x]==NULL){
            cur->bit[x]=new node();
        }
        cur=cur->bit[x];
        cur->count++;
    }
}
 
void remove(node* p, int s, int c=31) {
    if (c==0) {
        p=p->bit[s&1];
        p->count--;
        return;
    }
    int x;
    if(s&(1<<c)) x=1;
    else x=0;
    p=p->bit[x];
    remove(p, s, c-1);
    p->count--;
}
 
int search(int s,node* root) {
    node *cur = root;
    int y=0,x;
    for (int i = 31; i >=0; i--) {
        if(s&(1<<i)) x=1;
        else x=0;
        if (cur->bit[1-x] != NULL and cur->bit[1-x]->count){
            cur = cur->bit[1-x];
            y+=1<<i;
        }else{
            cur = cur->bit[x];
        }
    }
    return y;
}
int main(){
    node* root = new node(); // or define globally and remove root parameter from functions;
}