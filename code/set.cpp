#include "set.hpp"

#include <algorithm>  //std::swap

/*
* std::size_t is defined in the C++ standard library
* std::size_t is an unsigned integer type that can store the maximum size of any possible object
* sizes are non-negative integers -- i.e. unsigned integer type
*/

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* ************************************ */

// Default constructor
Set::Set() : head{ new Node{} }, counter{ 0 } {  // create the dummy node
}

// Constructor for creating a singleton {x}
Set::Set(int x) : Set() {
    insert(x);
}

// Constructor: create a set with elements
// elements is not sorted and values in it may not be unique
Set::Set(const std::vector<int>& elements) : Set() {
    for (int i = 0; i < std::ssize(elements); i++) { // g�r igenom varje elemnt i vektorn
        insert(elements[i]); // insert i node
    }
}

// copy constructor
Set::Set(const Set& rhs) : Set() {
    
    Node* ptrSource = rhs.head->next; // hoppar �ver dummy node
    Node* ptrThis = head; // dummy node finns och beh�ver ej kopieras

    while (ptrSource != nullptr) { // kopierar fr�n rhs till nya listan
        insert(ptrThis, ptrSource->value);
        ptrSource = ptrSource->next; // g�r till n�sta node
        ptrThis = ptrThis->next;
    }
    counter = rhs.counter;
}

// Assignment operator: use copy-and-swap idiom
Set& Set::operator=(Set rhs) {
    
    std::swap(head, rhs.head); // byter head, resterande f�ljer med pga pointers
    std::swap(counter, rhs.counter);

    return *this;
}

// Destructor: deallocate all nodes
Set::~Set() {
    Node* ptr = head; // pekat mot f�rsta node

    while (ptr != nullptr) { // s� l�nge det finns nodes
        head = ptr->next; // pekar mot n�sta node i listan
        remove(ptr);
        ptr = head; // ny f�rsta node
    }
    counter = 0;
    head = nullptr;
}

// Return number of elements in the set
std::size_t Set::cardinality() const {

    return counter;
}

// Test if set is empty
bool Set::empty() const {
    if (counter == 0) {
        return true;
    } else {
        return false;
    }
}

// Test if x is an element of the set
bool Set::member(int x) const {
    
    Node* ptr = head; // pointer mot dummy node

    while ((ptr != nullptr) && (ptr->value != x)) { // k�r tills listan �r slut och x inte �r med i listan

        ptr = ptr->next;
    }
    if (ptr == nullptr) { // om listan tar slut
        return false;
    } else {
        return true;
    }
}

// Return true, if *this is a subset of Set b
// Otherwise, false is returned
bool Set::is_subset(const Set& b) const {
    
    Node* ptr = head;

    int sub_size = this->cardinality(); // storleken av delm�ngden mha countern 
    int part = 0;
    int not_part = 0;

    while (ptr != nullptr) { // g�r igenom listan
        if (!b.member(ptr->value)) { // om v�rdet ej finn i stora m�ngden 
            not_part++;
        } else {
            part++;
        }
        ptr = ptr->next;
    }

    return(not_part == 0); // om not_part �r noll, �r alla v�rden med i delm�ngden, return true
}

// Return a new Set representing the union of Sets *this and b
// Repeated values are not allowed
// Implement an algorithm similar to the one in exercise 3/Set 1, but don't use vectors
Set Set::set_union(const Set& b) const {

    Set result{ b }; // skapa ett nytt set, fyll med b
    Node* ptr = head->next;
    
    while (ptr != nullptr) {
        result.insert(ptr->value); // s�tt in v�rden fr�n this set i result
        ptr = ptr->next;
    }

    return result;
}

// Return a new Set representing the intersection of Sets *this and b
Set Set::set_intersection(const Set& b) const {
    
    Set result;
    Node* ptr = head->next;

    while (ptr != nullptr) {
        if (b.member(ptr->value)) { // om value �r member av b
            result.insert(ptr->value); // s�tt in i result
        }
        ptr = ptr->next;
    }

    return result;
}

// Return a new Set representing the difference between Set *this and Set b
Set Set::set_difference(const Set& b) const {

    Set result;
    Node* ptr = head->next;

    // vilka i this finns inte i b
    while (ptr != nullptr) { 
        if (!b.member(ptr->value)) { // om value inte finns i b
            result.insert(ptr->value); // s�tt in i result
        }
        ptr = ptr->next;
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Set& rhs) {
    if (rhs.empty()) { // om set �r tomt
        os << "Set is empty!";
    }
    else {
        Set::Node* ptr = rhs.head->next;
        os << "{ ";

        while (ptr != nullptr) { // skriver ut values i listan ex. { 1 2 3 4 }
            os << ptr->value << " ";
            ptr = ptr->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/

void Set::insert(Node* ptr, int value) {

    Node* newNode = new Node(value, ptr->next); // skapa ny node

    ptr->next = newNode; // nya noden blir n�sta i listan
    counter++; // l�gger till antalet nodes
}

void Set::insert(int value) {

    Node* ptr = head; // head pekar mot f�rsta node

    while ((ptr->next != nullptr) && (ptr->next->value < value)) {  // kollar om n�sta node har ett v�rde och om det �r st�rre �n n�sta v�rde

        ptr = ptr->next;
    }

    if (ptr->next == nullptr || ptr->next->value != value) { // om i slutet p� en list skapar ny node med value

        insert(ptr, value);
    }
}

void Set::remove(Node* ptr) {

    delete ptr; // deallocate
}