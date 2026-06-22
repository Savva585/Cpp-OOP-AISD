struct Entry {
    int key;
    int value;
    Entry* next;
};

struct HashMap {
    int capacity;
    int size;
    Entry** buckets;  
};

int get(HashMap& map, int key){
    
}
