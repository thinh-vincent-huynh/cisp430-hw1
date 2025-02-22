#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

struct node{
    string name;
    node* prev;
    node* next;
    node(string name_, node* prev_, node* next_){
        name = name_;
        prev = prev_;
        next = next_;
    }
};

void InsertNode(node*& head, node*& tail, string data){
    if (!head){                      //no other nodes
        head = tail = new node(data, nullptr, nullptr);
    }else if (data < head->name){   //smaller than head
        head->prev = new node(data, nullptr, head);
        head = head->prev;
    }else if (data > tail->name){   //larger than tail
        tail->next = new node(data, tail, nullptr);
        tail = tail->next;
    }else{                          //somewhere in the middle
        node* curr = head->next;
        while (data > curr->name){  //move to where data should belong to
            curr = curr->next;
        }
        node* newNode = new node(data, curr->prev, curr);
        curr->prev->next = newNode;
        curr->prev = newNode;
    }
}

void DeleteNode(node*& head, node*& tail, string data){
    node* curr = head;
    while (data != curr->name){
        curr = curr->next;
    }
    if (data == curr->name){
        if (curr->prev) {
            curr->prev->next = curr->next;
        } else {
            head = curr->next;
            if (head) head->prev = nullptr;
        }
        if (curr->next) {
            curr->next->prev = curr->prev;
        } else {
            tail = curr->prev;
            if (tail) tail->next = nullptr;
        }
    }
    delete curr;
}

ostream& AscendDisplay(ostream& out, node* head){
    node* curr = head;
    while (curr){
        out << curr->name << endl;
        curr = curr->next;
    }
    return out;
}

ostream& DescendDisplay(ostream& out, node* tail){
    node* curr = tail;
    while (curr){
        out << curr->name << endl;
        curr = curr->prev;
    }
    return out;
}

int main(){
    ifstream in("input.txt");
    string str;
    node* head = nullptr;
    node* tail = nullptr;
    while (in >> str){
        if (str != "delete"){
            for (char &c : str) {
                c = tolower(c);
            }
            InsertNode(head, tail, str);
        }else{
            in >> str;
            DeleteNode(head, tail, str);
        }
    }
    in.close();

    ofstream out("output.txt");
    AscendDisplay(out, head);
    out << "=============" << endl;
    DescendDisplay(out, tail);
    out.close();
}
