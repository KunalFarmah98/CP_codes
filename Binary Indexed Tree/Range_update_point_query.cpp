#include <iostream>
using namespace std;

// RANGE SUM QUERIES

int BIT[10000] = {0};

void update(int index, int n, int inc){
    // updating the required index and then only updating where that range exists (next power of 2 index)
    // given by i+(i&-i)
    while(index<=n){
        BIT[index]+=inc;
        index+=(index&(-index));
    }
}

// updating from l to r means update all elements form l to r
// updating in BIT will propagate that update till the end
// to update only till r, we update for index l which will
// update every element till n and then update alll elements
// after r with -ve of the increment , or change that we did.
void rangeUpdate(int l, int r, int n,int val){

    update(l,n,val);
    update(r+1,n,(-val));// nullifying the effect of update done by updating index l after r
}

void build(int a[], int n){
    // building is similar to updating all indices of a 0 initialised BIT 
    //with inc equal to the original array
    for(int i=1; i<=n; i++){
    update(i,n,a[i]);
     }
}

// This returns cumulative sum till index i
int query(int i){
    int ans=0;
    // going back from one index to the next index with the last set bit removed till 0
    while(i>0){
        ans+=BIT[i];
        i-=(i&(-i));
    }

    return ans;
}

// for both inclusive, range l,r is diffference of range r and l-1
int rangequery(int l, int r){
    return query(r)-query(l-1);
}

int main() {
    int n;
    cin>>n;

    int a[n+1];

    for(int i=1; i<=n; i++){
        cin>>a[i];
    }

    build(a,n);

    // alternate for building BIT
    /*for(int i=1; i<=n; i++){
        cin>>a[i];
        update(i,n,a[i]);
    }*/

    int q;
    cin>>q;

    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<rangequery(l,r)<<endl;
    }

    return 0;
}
