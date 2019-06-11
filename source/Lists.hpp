#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>

#include <initializer_list>

template <typename T>
class List;

template <typename T>
struct ListNode {
    T         value = T ();
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
};


template <typename T>
struct ListIterator {
    using Self              = ListIterator<T>;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
    using difference_type   = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;


    /* DESCRIPTION  operator*() */
    T&  operator*()  const {
        return node->value;
    }

    /* DESCRIPTION  operator->() */
    T* operator->() const {
        return &node->value;
    }

    /* returns an iterator to the next element from self */
    ListIterator<T>& operator++() {
        node = node->next;
        return *this;
    }

    /* returns an iterator to  */
    ListIterator<T> operator++(int) {
        auto old_node = node;
        node = node->next;
        return ListIterator<T>{old_node};
    } //POSTINCREMENT (signature distinguishes)

    /* ... */
    bool operator==(ListIterator<T> const& x) const {
        return node == x.node;
    }

    /* ... */
    bool operator!=(ListIterator<T> const& x) const {
        return node != x.node;    }

    /* ... */
    ListIterator<T> next() const {
        if (nullptr != node) {
            return ListIterator{node->next};
        } else {
            return ListIterator{nullptr};
        }
    }


    ListNode<T>* node = nullptr;
};



template <typename T>
class List {
public:
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = T const*;
    using reference       = T&;
    using const_reference = T const&;
    using iterator        = ListIterator<T>;

    // not implemented yet
    // do not forget about the initialiser list !
    /* Constructor: erstellt leere Liste */
    List() {}

    /* Erstellt neue Liste mit allen Elementen aus alter Liste */
    //TODO: Copy-Konstruktor using Deep-Copy semantics (Aufgabe 4.8)

    /* Bewegt alle Objekte von alter Liste in neue Liste */
    //TODO: Move-Konstruktor (Aufgabe 4.13)

    //TODO: Initializer-List Konstruktor (4.14)

    /* Erstellt neue Liste mit übergebenen Werten als Knoten */
    List(std::initializer_list<T> ini_list) {
        //not implemented yet
    }

    /* ... */
    //TODO: Assignment operator (Aufgabe 4.12)

    bool operator==(List<T> const& rhs){
        if(first_ == nullptr and rhs.first_ == nullptr){
            return true;
        } else if(first_ == nullptr xor rhs.first_ == nullptr){
            return false;
        } else{
            auto lhs_elem = first_;
            auto rhs_elem = rhs.first_;
            for(int i = 0; i < size_; ++i){
                if(lhs_elem->value != rhs_elem->value){
                    return false;
                }
            }
            return true;
        }
    }

    bool operator!=(List<T> const& rhs){
        if(first_ == nullptr and rhs.first_ == nullptr){
            return false;
        } else if(first_ == nullptr xor rhs.first_ == nullptr){
            return true;
        } else{
            auto lhs_elem = first_;
            auto rhs_elem = rhs.first_;
            for(int i = 0; i < size_; ++i){
                if(lhs_elem->value == rhs_elem->value){
                    return false;
                }
            }
            return true;
        }
    }

    /* Destructor: Deletes all the Elements of the List and the list itself */
    ~List() {
        clear();
    }

    /* Returns iterator to start of List */
    ListIterator<T> begin() {
        return ListIterator<T>{first_};
    }

    /* Returns Operator to end of List */
    ListIterator<T> end() {
        return ListIterator<T>{last_};
    }

    /* Deletes all the elemtents of the List, but not the List itself */
    void clear() {
        auto inital_size = size_;
        for(int i = 0; i < inital_size; ++i){
            pop_back();
        }
    }

    /* Inserts a Node with given value at given position */
    //TODO: member function insert

    /* reverses the list */
    //TODO: member function reverse

    /* Adds an element to the start of the list */
    void push_front(T const& element) {
        ListNode<T>* push = new ListNode<T>{element};
        ++size_;
        if(empty()){
            first_ = push;
            last_ = push;
        } else{
            push->next = first_;
            first_->prev = push;
            first_ = push;
        }
    }

    /* Adds an element to the end of the list */
    void push_back(T const& element) {
        ListNode<T>* push = new ListNode<T>{element};
        ++size_;
        if(empty()){
            first_ = push;
            last_ = push;
        } else{
            push->prev = last_;
            last_->next = push;
            last_ = push;
        }
    }

    /* deletes the first element of the list */
    void pop_front() {
        assert(!empty());
        if(empty()){
        }else if(size_ == 1) {
            --size_;
            delete(first_);
            first_ = nullptr;
            last_ = nullptr;
        } else{
            --size_;
            auto old_first = first_;
            old_first->next->prev = nullptr;
            first_ = old_first->next;
            delete(old_first);
        }
    }

    /* deletes the last element of the list */
    void pop_back() {
        assert(!empty());
        if(empty()){
        } else if(size_ == 1){
            --size_;
            delete(first_);
            first_ = nullptr;
            last_ = nullptr;
        } else{
            --size_;
            auto old_last = last_;
            old_last->prev->next = nullptr;
            last_ = old_last->prev;
            delete(old_last);
        }
    }

    /* returns reference to value of first element*/
    T& front() {
        assert(!empty());
        /*
        if(empty()){
            return nullptr;
        }
        */
        return first_->value;
    }

    /* returns reference to the last element of the list */
    T& back() {
        assert(!empty());
        /*
        if(empty()){
            return nullptr;
        }
        */
        return last_->value;
    }

    /* returns true if list is empty, false if it contains items */
    bool empty() const {
        return first_ == nullptr;
    };

    /* returns number of nodes in the list */
    std::size_t size() const{
        return size_;
    };


private:
    std::size_t size_ = 0;
    ListNode<T>* first_ = nullptr;
    ListNode<T>* last_ = nullptr;
};

/* kehrt die Liste um */
//TODO: Freie Funktion reverse

/* adds the elements of Lists in one List */
//TODO: Freie Funktion operator+ (4.14)

#endif // # define BUW_LIST_HPP
