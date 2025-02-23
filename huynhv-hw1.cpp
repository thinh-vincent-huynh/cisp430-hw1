#include <string>   // to easily store names
#include <cctype>   // to use tolower()
#include <fstream>  // to read and write files
using namespace std;

struct node{       // a struct of node is sufficient
    string name;   // to create a double linked list
    node* prev;
    node* next;
    node(string name_, node* prev_, node* next_){
        name = name_;   // data stored in node
        prev = prev_;   // previous node in list
        next = next_;   // next node ___ in list
    }
};

void InsertNode(node*& head, node*& tail, string data){
    if (!head){                     // no other nodes
        head = tail = new node(data, nullptr, nullptr);
    }else if (data < head->name){   // smaller than head
        head = head->prev = new node(data, nullptr, head);
    }else if (data > tail->name){   // larger than tail
        tail = tail->next = new node(data, tail, nullptr);
    }else{                          // somewhere in the middle
        node* curr = head->next;
        while (data > curr->name){  // move to where data should belong to
            curr = curr->next;
        }
        curr->prev = curr->prev->next = new node(data, curr->prev, curr);
    }
}

void DeleteNode(node*& head, node*& tail, string data){
    node* curr = head;
    while (curr && data != curr->name){   // find the node needed to be deleted
        curr = curr->next;
    }
    if (curr){             // node found?
        if (curr->prev){   // check if previous node exists
            curr->prev->next = curr->next;
        }else{             // node = head
            head = curr->next;
        }
        if (curr->next){   // check if next node ___ exists
            curr->next->prev = curr->prev;
        }else{             // node = tail
            tail = curr->prev;
        }
        delete curr;
    }                      // nothing happens if node not found
}

ostream& AscendDisplay(ostream& out, node* head){
    node* curr = head;   // traverse the list from head to tail
    while (curr){        // to display each node ascendingly
        out << curr->name << endl;
        curr = curr->next;
    }
    return out;
}

ostream& DescendDisplay(ostream& out, node* tail){
    node* curr = tail;   // traverse the list from tail to head
    while (curr){        // to display each node descendingly
        out << curr->name << endl;
        curr = curr->prev;
    }
    return out;
}

int main(){
    // input process
    ifstream in("input.txt");
    string str;
    node* head = nullptr;
    node* tail = nullptr;
    while (in >> str){              // for each string in input file
        for (char &c : str) {       // convert all string to lowercase
            c = tolower(c);
        }
        if (str != "delete"){       // insert mode
            InsertNode(head, tail, str);
        }else{                      // delete mode
            in >> str;              // delete what name?
            for (char &c : str) {   // convert all string to lowercase
                c = tolower(c);
            }
            DeleteNode(head, tail, str);
        }
    }
    in.close();

    // output process
    ofstream out("output.txt");
    AscendDisplay(out, head);
    out << "=============" << endl;
    DescendDisplay(out, tail);
    out.close();
}
