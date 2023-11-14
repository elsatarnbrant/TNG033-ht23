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
    for (int i = 0; i < std::ssize(elements); i++) { // går igenom varje elemnt i vektorn
        insert(elements[i]); // insert i node
    }
}

// copy constructor
Set::Set(const Set& rhs) : Set() {
    
    Node* ptrSource = rhs.head->next; // hoppar över dummy node
    Node* ptrThis = head; // dummy node finns och behöver ej kopieras

    while (ptrSource != nullptr) { // kopierar från rhs till nya listan
        insert(ptrThis, ptrSource->value);
        ptrSource = ptrSource->next; // går till nästa node
        ptrThis = ptrThis->next;
    }
    counter = rhs.counter;
}

// Assignment operator: use copy-and-swap idiom
Set& Set::operator=(Set rhs) {
    
    std::swap(head, rhs.head); // byter head, resterande följer med pga pointers
    std::swap(counter, rhs.counter);

    return *this;
}

// Destructor: deallocate all nodes
Set::~Set() {
    Node* ptr = head; // pekat mot första node

    while (ptr != nullptr) { // så länge det finns nodes
        head = ptr->next; // pekar mot nästa node i listan
        remove(ptr);
        ptr = head; // ny första node
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

    while ((ptr != nullptr) && (ptr->value != x)) { // kör tills listan är slut och x inte är med i listan

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

    int sub_size = this->cardinality(); // storleken av delmängden mha countern 
    int part = 0;
    int not_part = 0;

    while (ptr != nullptr) { // går igenom listan
        if (!b.member(ptr->value)) { // om värdet ej finn i stora mängden 
            not_part++;
        } else {
            part++;
        }
        ptr = ptr->next;
    }

    return(not_part == 0); // om not_part är noll, är alla värden med i delmängden, return true
}

// Return a new Set representing the union of Sets *this and b
// Repeated values are not allowed
// Implement an algorithm similar to the one in exercise 3/Set 1, but don't use vectors
Set Set::set_union(const Set& b) const {

    Set result{ b }; // skapa ett nytt set, fyll med b
    Node* ptr = head->next;
    
    while (ptr != nullptr) {
        result.insert(ptr->value); // sätt in värden från this set i result
        ptr = ptr->next;
    }

    return result;
}

// Return a new Set representing the intersection of Sets *this and b
Set Set::set_intersection(const Set& b) const {
    
    Set result;
    Node* ptr = head->next;

    while (ptr != nullptr) {
        if (b.member(ptr->value)) { // om value är member av b
            result.insert(ptr->value); // sätt in i result
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
            result.insert(ptr->value); // sätt in i result
        }
        ptr = ptr->next;
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Set& rhs) {
    if (rhs.empty()) { // om set är tomt
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

    ptr->next = newNode; // nya noden blir nästa i listan
    counter++; // lägger till antalet nodes
}

void Set::insert(int value) {

    Node* ptr = head; // head pekar mot första node

    while ((ptr->next != nullptr) && (ptr->next->value < value)) {  // kollar om nästa node har ett värde och om det är större än nästa värde

        ptr = ptr->next;
    }

    if (ptr->next == nullptr || ptr->next->value != value) { // om i slutet på en list skapar ny node med value

        insert(ptr, value);
    }
}

void Set::remove(Node* ptr) {

    delete ptr; // deallocate
}