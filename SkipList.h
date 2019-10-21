#ifndef UNTITLED1_SKIPLIST_H
#define UNTITLED1_SKIPLIST_H

#include <cstring>
#include "header.h"
// Class to implement node
struct Node
{
public:
    int key;
    string value;
    // Array to hold pointers to node of different level
    Node **forward;

    Node(int key, string value, int level)
    {
        this->key = key;
        this->value = value;

        // Allocate memory to forward
        forward = new Node*[level+1];

        // Fill forward array with 0(NULL)
        memset(forward, 0, sizeof(Node*)*(level+1));
    }
};

// Class for Skip list
class SkipList
{
    // Maximum level for this skip list
    int MAXLVL;

    // probability is the fraction of the nodes with level
    // i pointers also having level i+1 pointers
    float probability;

    // current level of skip list
    int currentLevel;

    // pointer to header node
    Node *header;

    //size of the skiplist
    int size;

public:
    SkipList(int MAXLVL, float P)
    {
        this->MAXLVL = MAXLVL;
        this->probability = P;
        currentLevel = 0;
        size = 0;

        // create header node and initialize key to -1
        header = new Node(-1, " ", MAXLVL);
    }
    // create random level for node
    int randomLevel()
    {
        float r = (float)rand()/RAND_MAX;
        int lvl = 0;
        cout << "TRUE/FALSE of Pseudo Level Generator: ";
        while (r < probability && lvl < MAXLVL)
        {
            cout << "False ";
            lvl++;
            r = (float)rand()/RAND_MAX;
        }
        cout << "True";
        cout << "\nThe Pseudo Random Number Generator decided to insert the Node into Level " << lvl << endl;
        return lvl;
    }

    // create new node
    Node* createNode(int key,string value, int level)
    {
        Node *n = new Node(key, value, level);
        return n;
    }

    // Insert given key in skip list
    void insertElement(int key, string value)
    {
        size ++;
        Node *current = header;

        // create update array and initialize it
        Node *update[MAXLVL+1];
        memset(update, 0, sizeof(Node*)*(MAXLVL+1));

        /*    start from highest level of skip list
            move the current pointer forward while key
            is greater than key of node next to current
            Otherwise inserted current in update and
            move one level down and continue search
        */
        for (int i = currentLevel; i >= 0; i--)
        {
            while (current->forward[i] != NULL &&
                   current->forward[i]->key <= key)
                current = current->forward[i];
            update[i] = current;
        }

        /* reached level 0 and forward pointer to
           right, which is desired position to
           insert key.
        */
        current = current->forward[0];

        /* if current is NULL that means we have reached
           to end of the level or current's key is not equal
           to key to insert that means we have to insert
           node between update[0] and current node */
        if (current == NULL || current->key != key)
        {
            // Generate a random level for node
            int rlevel = randomLevel();

            // If random level is greater than list's current
            // level (node with highest level inserted in
            // list so far), initialize update value with pointer
            // to header for further use
            if (rlevel > currentLevel)
            {
                for (int i= currentLevel + 1; i < rlevel + 1; i++)
                    update[i] = header;

                // Update the list current level
                currentLevel = rlevel;
            }

            // create new node with random level generated
            Node* n = createNode(key, value, rlevel);

            // insert node by rearranging pointers
            for (int i=0;i<=rlevel;i++)
            {
                n->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = n;
            }
            cout << "Successfully Inserted (" << key << ", " << value << ")" << "\n\n";
        }
    }
    // Display skip list level wise
    void displayList()
    {
        cout<<"\n*****Skip List*****"<<"\n";
        for (int i=0; i <= currentLevel; i++)
        {
            Node *node = header->forward[i];
            cout << "\nLevel " << i << ": ";
            while (node != NULL)
            {
                cout << "| (" << node->key<<", " << node->value << ") |";
                node = node->forward[i];
            }
            cout << "\n";
        }
    }



    // Delete element from skip list
    void deleteElement(int key)
    {
        Node *current = header;

        // create update array and initialize it
        Node *update[MAXLVL+1];
        memset(update, 0, sizeof(Node*)*(MAXLVL+1));

        /*    start from highest level of skip list
            move the current pointer forward while key
            is greater than key of node next to current
            Otherwise inserted current in update and
            move one level down and continue search
        */
        for(int i = MAXLVL; i >= 0; i--)
        {
            while(current->forward[i] != NULL  &&
                  current->forward[i]->key < key)
                current = current->forward[i];
            update[i] = current;
        }

        /* reached level 0 and forward pointer to
           right, which is possibly our desired node.*/
        current = current->forward[0];

        // If current node is target node
        if(current != NULL and current->key == key)
        {
            size --;
            /* start from lowest level and rearrange
               pointers just like we do in singly linked list
               to remove target node */
            for(int i=0;i<=MAXLVL;i++)
            {
                /* If at level i, next node is not target
                   node, break the loop, no need to move
                  further level */
                if(update[i]->forward[i] != current)
                    break;

                update[i]->forward[i] = current->forward[i];
            }

            // Remove levels having no elements
            while(MAXLVL>0 &&
                  header->forward[MAXLVL] == 0)
                MAXLVL--;
            cout<<"Successfully deleted key "<<key<<"\n";
        }
    };



// Search for element in skip list
    void find(int key)
    {
        Node *current = header;

        /*    start from highest level of skip list
            move the current pointer forward while key
            is greater than key of node next to current
            Otherwise inserted current in update and
            move one level down and continue search
        */
        for(int i = MAXLVL; i >= 0; i--)
        {
            while(current->forward[i] &&
                  current->forward[i]->key < key)
                current = current->forward[i];

        }

        /* reached level 0 and advance pointer to
           right, which is possibly our desired node*/
        current = current->forward[0];

        // If current node have key equal to
        // search key, we have found our target node
        if(current and current->key == key)
            cout<<"Found Key: (" << current->key<<", " << current->value << ")\n";
    };

    //outputs the size of the skiplist
    void displaySize()
    {
        cout << "The Size of The SkipList is: " << size << endl<< endl;
    }

    //checks if the skiplist is empty
    void isEmpty()
    {
        if(size == 0)
        {
            cout << "The Skip List Is Empty\n";
            return;
        }

        cout << "The Skip List Is Not Empty\n";
    }
    // Search for all elements in skip list
    void findAll(int key)
    {
        cout << "Using the FindAll() Function\n";
        Node *current = header;

        /*    start from highest level of skip list
            move the current pointer forward while key
            is greater than key of node next to current
            Otherwise inserted current in update and
            move one level down and continue search
        */
        int i = MAXLVL;
        for(MAXLVL; i >= 0; i--)
        {
            while(current->forward[i] &&
                  current->forward[i]->key < key)
                current = current->forward[i];
        }
        i++;
        /* reached level 0 and advance pointer to
        right, which is possibly our desired node*/
        current = current->forward[0];
        cout<<"Found Keys: ";

        while(current->forward[i]->key == key)
        {
            cout << "(" << current->key<<", " << current->value << ") ";
            current = current->forward[i];
        }
    }


    Node begin()
    {
        return *header->forward[0];
    }

    Node end()
    {
        Node *current = header;

        /*    start from highest level of skip list
            move the current pointer forward while key
            is greater than key of node next to current
            Otherwise inserted current in update and
            move one level down and continue search
        */
        for(int i = MAXLVL; i >= 0; i--)
        {
            while(current->forward[i])
                current = current->forward[i];

        }

        return *current;
    }
    // Delete element from skip list
    void deleteElementUsingIterator(Node *iterator)
    {
        cout << "Deleting A Node Using The DeleteElementUsingIterator Method\n";
        Node *current = header;

        // create update array and initialize it
        Node *update[MAXLVL+1];
        memset(update, 0, sizeof(Node*)*(MAXLVL+1));

        /*    start from highest level of skip list
            move the current pointer forward while key
            is greater than key of node next to current
            Otherwise inserted current in update and
            move one level down and continue search
        */
        for(int i = MAXLVL; i >= 0; i--)
        {
            while(current->forward[i] != NULL  &&
                  current->forward[i]->key < iterator->key)
                current = current->forward[i];
            update[i] = current;
        }

        /* reached level 0 and forward pointer to
           right, which is possibly our desired node.*/
        current = current->forward[0];

        // If current node is target node
        if(current != NULL and current->key == iterator->key)
        {
            size --;
            /* start from lowest level and rearrange
               pointers just like we do in singly linked list
               to remove target node */
            for(int i=0;i<=MAXLVL;i++)
            {
                /* If at level i, next node is not target
                   node, break the loop, no need to move
                  further level */
                if(update[i]->forward[i] != current)
                    break;

                update[i]->forward[i] = current->forward[i];
            }

            // Remove levels having no elements
            while(MAXLVL>0 &&
                  header->forward[MAXLVL] == 0)
                MAXLVL--;
            cout<<"Successfully deleted key "<<iterator->key<<"\n";
        }
    }


    //Displays the data from each Bucket
    void displayBuckets()
    {
        cout<<"\n*****Bucket List*****"<<"\n";
        for (int i=0; i <= currentLevel; i++)
        {
            Node *node = header->forward[i];
            cout << "\nLevel " << i << ": \n";
            int x = 0;
            while (node != NULL)
            {
                cout << "Bucket #" << x << "\t";
                cout << "Key: " << node->key;
                node = node->forward[i];
                cout << endl;
                x++;
            }
            cout << "\n";
        }
    }
};

#endif //UNTITLED1_SKIPLIST_H
