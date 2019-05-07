int parti(vector<int> &v,int l,int r){
    int pivot = v[r];
    int i=l-1;
    
    for(int j=l;j<r;j++) {
        if(v[j] <= pivot) {
            i++;
            swap(v[i],v[j]);
        }
    }
    swap(v[i+1],v[r]);
    return (i+1);
}

void quickSort(vector<int> &v,int l,int r){
    if(l<r) {
        int pi=parti(v,l,r);
        quickSort(v,l,pi-1);
        quickSort(v,pi+1,r);
    }
}
