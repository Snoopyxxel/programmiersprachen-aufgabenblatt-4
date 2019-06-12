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
    T         value = T();
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
        if (node->next != nullptr) {
            node = node->next;
        }
        return *this;
    }

    ListIterator<T> operator+(int plus) {
        ListIterator<T> erg{node};
        for(int i = 0; i < plus; ++i){
            ++erg;
        }
        return erg;
    }

    /* returns an iterator to  */
    ListIterator<T> operator++(int) {
        auto old_node = node;
        if (node->next != nullptr) {
            node = node->next;
        }
        return ListIterator<T>{old_node};
    } //POSTINCREMENT (signature distinguishes)

    /* returns true if nodes of iterators are equal */
    bool operator==(ListIterator<T> const& x) const {
        return node == x.node;
    }

    /* returns false if nodes of iterators are equal */
    bool operator!=(ListIterator<T> const& x) const {
        return node != x.node;    }

    /* returns an interator to the element in the list next to the original iterator */
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
    List(){}

    /* Erstellt neue Liste mit allen Elementen aus alter Liste */
    List(List<T> const& original) {
        auto original_elem = original.first_;
        for(int i = 0; i < original.size_; ++i) {
            push_back(original_elem->value);
            original_elem = original_elem->next;
        }
    }

    //assigns values from rhs to this
    List<T>& operator=(List<T> rhs){
        rhs.swap(*this);
        return *this;
    }

    void swap(List<T>& rhs){
        auto this_first = first_;
        auto this_last = last_;
        first_ = rhs.first_;
        last_ = rhs.last_;
        rhs.first_ = this_first;
        rhs.last_ = this_last;
        auto this_size = size_;
        size_ = rhs.size_;
        rhs.size_ = this_size;
    }

    friend void swap(List<T>& lhs, List<T>& rhs) {lhs.swap(rhs);}


    /* Bewegt alle Objekte von alter Liste in neue Liste */
    List(List<T>&& rhs):
        first_(rhs.first_), last_(rhs.last_) {
        rhs.first_ = nullptr;
        rhs.last_ = nullptr;
        size_ = rhs.size_;
        rhs.size_ = 0;
    }

    /* Erstellt neue Liste mit übergebenen Werten als Knoten */
    List(std::initializer_list<T> ini_list) {
        for (int i = 0; i < ini_list.size(); ++i){
            push_back(*(ini_list.begin() + i));
        }
    }

    bool operator==(List<T> const& rhs){
        if(first_ == nullptr and rhs.first_ == nullptr){
            return true;
        } else if(first_ == nullptr xor rhs.first_ == nullptr){
            return false;
        } else if(size_ != rhs.size_){
            return false;
        }else{
            auto lhs_elem = first_;
            auto rhs_elem = rhs.first_;
            for(int i = 0; i < size_; ++i){
                if(lhs_elem->value != rhs_elem->value){
                    return false;
                }
                rhs_elem = rhs_elem->next;
                lhs_elem = lhs_elem->next;
            }
            return true;
        }
    }

    bool operator!=(List<T> const& rhs){
        if(first_ == nullptr and rhs.first_ == nullptr){
            return false;
        } else if(first_ == nullptr xor rhs.first_ == nullptr){
            return true;
        } else if(size_ != rhs.size_){
            return true;
        } else{
            auto lhs_elem = first_;
            auto rhs_elem = rhs.first_;
            for(int i = 0; i < size_; ++i){
                if(lhs_elem->value != rhs_elem->value){
                    return true;
                }
                rhs_elem = rhs_elem->next;
                lhs_elem = lhs_elem->next;
            }
            return false;
        }
    }

    /* Destructor: Deletes all the Elements of the List and the list itself */
    ~List() {
        clear();
    }

    /* Returns iterator to start of List */
    ListIterator<T> begin() const {
        return ListIterator<T>{first_};
    }

    /* Returns iterator to end of List */
    ListIterator<T> end() const {
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
    ListIterator<T> insert(T data, ListIterator<T> const& pos_it){
        if(pos_it.node == first_){
            push_front(data);
            return begin();
        } else {
            ListNode<T>* in = new ListNode<T>{data, pos_it.node->prev, pos_it.node};
            in->prev->next = in;
            in->next->prev = in;
            ++size_;
            return ListIterator<T>{in};
        }
    }

    /* reverses the list */
    void reverse(){
        if(size_ <= 1){
            //do nothing
        } else{
            auto node = first_;
            for(int i = 0; i < size_; ++i){
                auto old_prev = node->prev;
                node->prev = node->next;
                node->next = old_prev;
                node = node->prev;
            }
            auto old_first = first_;
            first_ = last_;
            last_ = old_first;
        }
    }

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
    T& front() const {
        assert(!empty());
        /*
        if(empty()){
            return nullptr;
        }
        */
        return first_->value;
    }

    /* returns reference to the last element of the list */
    T& back() const {
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
template <typename T>
List<T> reverse(List<T> const& in){
    List<T> erg{in};
    erg.reverse();
    return erg;
}

/* adds the elements of Lists in one List */
template <typename T>
List<T> operator+(List<T> const& lhs, List<T> const& rhs){
    List<T> erg{lhs};
    for(int i = 0; i < rhs.size(); ++i){
        erg.push_back(*rhs.begin() + i);
    }
    return erg;
}

#endif // # define BUW_LIST_HPP
