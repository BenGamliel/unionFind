
#ifndef UNION_FIND_H_
#define UNION_FIND_H_

#include <iostream>
class ReverseTree {
public:
    /*
     * a constructor for the class reverse tree' it`s also contains the default constructor
     */
    ReverseTree(const int& value = 0, ReverseTree* parent = NULL,
                const int& num = 1) :
            value(value), parent(parent), num_members(num) {
    }
    /*
     * copy constructor
     */
    ReverseTree(const ReverseTree& reverse_tree) {
        value = reverse_tree.value;
        parent = reverse_tree.parent;
        num_members = reverse_tree.num_members;
    }
    ReverseTree& operator=(const ReverseTree& reverse_tree) {
        if (this == &reverse_tree) {
            return *this;
        }
        value = reverse_tree.value;
        parent = reverse_tree.parent;
        num_members = reverse_tree.num_members;
        return *this;
    }
    bool operator>(const ReverseTree& reverse_tree) {
        if (num_members > reverse_tree.num_members) {
            return true;
        }
        if (num_members == reverse_tree.num_members) {
            return value > reverse_tree.value;
        }
        return false;
    }
    /*
     * a method which return the size of the node
     */
    int size() {
        return num_members;
    }
    /*
     * a method which returns the id of the node
     */
    int get_value() {
        return value;
    }
    /*
     * a method which sets a new size for the node
     */
    void setSize(const int& size) {
        num_members = size;
    }
    /*
     * a method which returns a pointer to the parent of a node
     */
    ReverseTree* getParent() {
        return parent;
    }
    /*
     * a method which sets a new parent for a node
     */
    void setParent(ReverseTree* new_parent) {
        parent = new_parent;
    }
    /*
     * a method which sets a new id for the node
     */
    void set_value(const int& new_value) {
        value = new_value;
    }
    /*
     * destructor
     */
    ~ReverseTree() {
        parent = NULL;
    }
private:
    int value;
    ReverseTree* parent;
    int num_members;
};
template <class T>
class UnionFind {
public:
    /*
     * constructor of the union find class according to how we learn in class the class supports
     * merging by size and collapse tracks - O(log*n)
     */
    UnionFind(const int& n) :
            size(n), pointers(new ReverseTree*[n]), reverse_tree(
            new ReverseTree[n]), data(new T[n]){
        MakeSet();
    }
    ~UnionFind() {
        delete[] pointers;
        delete[] reverse_tree;
    }
    /*
     * a method which returns the id of the scores_tree of the group according to how we learn in class
     */
    int Find(const int& i) {
        ReverseTree* head = helper_find(i);
        return head->get_value();
    }
    /*
     * a method which merges between two groups according to their size
     */
    void Union(const int& i, const int& j) {
        if (i == j) {
            return;
        }
        ReverseTree* head1 = helper_find(i);
        ReverseTree* head2 = helper_find(j);
        if (head1 == head2) {
            return;
        }
        if (*head1 > *head2) {
            head2->setParent(head1);
            head1->setSize(head1->size() + head2->size());
        } else {
            head1->setParent(head2);
            head2->setSize(head2->size() + head1->size());
        }
    }
    int get_size(const int& i) {
        return helper_find(i)->size();
    }
    int get_id(const int& i) {
        return pointers[i]->get_value();
    }
    T& get_data(const int& i) {
        return data[i];
    }
private:
    int size;
    ReverseTree** pointers;
    ReverseTree* reverse_tree;
    T* data;
    /*
     * a helper function which initiates the union find, it creates groups according to the size
     * in the field size and set the pointers for every group in appropriate place in the pointers
     * array
     */
    void MakeSet() {
        for (int i = 0; i < size; i++) {
            reverse_tree[i].set_value(i);
            pointers[i] = &reverse_tree[i];
            ((T)data[i]).setCourseId(i);
        }
    }
    /*
     * a private method which search the scores_tree of the group according to how we learn in class
     */
    ReverseTree* helper_find(const int& i) {
        ReverseTree* current = pointers[i];
        ReverseTree* start = pointers[i];
        while (current->getParent() != NULL) {
            current = current->getParent();
        }
        if (start->getParent() != NULL) {
            ReverseTree* to_set_parent = pointers[i];
            to_set_parent->setParent(current);
        }
        return current;
    }
};

#endif /* UNION_FIND_H_ */
