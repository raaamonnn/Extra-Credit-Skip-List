#include <time.h>
#include "header.h"
#include "SkipList.h"

int main()
{
    // Seed random number generator
    srand((unsigned)time(0));

    // create SkipList object with MAXLVL and probability
    SkipList dictionary(3, 0.5);

    dictionary.isEmpty();
    dictionary.displaySize();
    dictionary.insertElement(18, "Laguna Niguel");
    dictionary.insertElement(41, "Mission Viejo");
    dictionary.insertElement(22, "San Clemente");
    dictionary.insertElement(44, "Irvine");
    dictionary.deleteElement(41);
    dictionary.deleteElement(42);
    dictionary.insertElement(58, "Lake Forest");
    dictionary.insertElement(32, "San Diego");
    dictionary.insertElement(49, "Anaheim");
    dictionary.deleteElement(58);
    dictionary.insertElement(31, "Los Angeles");
    dictionary.insertElement(17, "Orange");
    dictionary.insertElement(72, "Palm Springs");
    dictionary.insertElement(41, "Riverside");
    dictionary.deleteElement(72);
    dictionary.insertElement(19, "Brea");
    dictionary.insertElement(60, "Santa Ana");
    dictionary.insertElement(35, "Tustin");
    dictionary.insertElement(103, "Ocean Side");
    dictionary.insertElement(11, "La Jolla");
    dictionary.insertElement(18, "Del Mar");
    dictionary.insertElement(22, "Aliso Viejo");
    dictionary.insertElement(49, "Laguna Beach");
    dictionary.deleteElement(41);
    dictionary.insertElement(42, "Vista");
    dictionary.insertElement(49, "San Diego");
    dictionary.insertElement(99, "San Juan");
    dictionary.insertElement(29, "Dana Point");
    dictionary.insertElement(88, "El Segundo");
    dictionary.insertElement(41, "San Clemente");
    dictionary.insertElement(62, "Laguna Hills");

    dictionary.displayList();
    dictionary.displayBuckets();

    dictionary.isEmpty();
    dictionary.displaySize();

    cout << "Using Begin() Method That Returns an Iterator To The Beginning\n";
    cout << "(" << dictionary.begin().key << ", ";
    cout << dictionary.begin().value << ")\n\n";

    cout << "Using END() Method That Returns an Iterator To The End\n";
    cout << "(" << dictionary.end().key << ", ";
    cout << dictionary.end().value << ")\n\n";

    dictionary.findAll(49);
    cout << endl << endl;

    Node* iterator = new Node(19, "Brea", 0);
    dictionary.deleteElementUsingIterator(iterator);

    dictionary.displayList();
    dictionary.displayBuckets();

    return 0;
}
