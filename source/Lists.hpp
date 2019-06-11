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
        return *node;
    }

    /* ... */
    ListIterator<T>& operator++() {
        //not implemented yet
        return {};
    } //PREINCREMENT

    /* ... */
    ListIterator<T> operator++(int) {
        //not implemented yet
        return {};
    } //POSTINCREMENT (signature distinguishes)

    /* ... */
    bool operator==(ListIterator<T> const& x) const {
        //not implemented yet
    }

    /* ... */
    bool operator!=(ListIterator<T> const& x) const {
        //not implemented yet
    }

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

    /* Checks if two Lists are equal */
    //TODO: operator== (Aufgabe 4.7)

    /* Checks if two Lists are unequal */
    //TODO: operator!= (Aufgabe 4.7)

    /* Destructor: Deletes all the Elements of the List and the list itself */
    ~List() {
        clear();
    }

    /* Returns iterator to start of List */
    ListIterator<T> begin() {
        ////not implemented yet
        return ListIterator<T>{};
    }

    /* Returns Operator to end of List */
    ListIterator<T> end() {
        ////not implemented yet
        return ListIterator<T>{};
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
