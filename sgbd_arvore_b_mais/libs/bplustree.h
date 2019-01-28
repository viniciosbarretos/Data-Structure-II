#ifndef SGBD_ARVORE_B_MAIS_BPLUSTREE_H
#define SGBD_ARVORE_B_MAIS_BPLUSTREE_H

// TYPES.

#include "student.h"
#include <stdbool.h>
#ifdef _WIN32
#define bool char
#define false 0
#define true 1
#endif

/* Type representing the Record
 * to which a given key refers.
 * In a real B+ tree system, the
 * Record would hold data (in a database)
 * or a file (in an operating system)
 * or some other information.
 * Users can rewrite this part of the code
 * to change the type and content
 * of the value field.
 */
typedef struct Record {
    int line;
} Record;

/* Type representing a node in the B+ tree.
 * This type is general enough to serve for both
 * the leaf and the internal node.
 * The heart of the node is the array
 * of keys and the array of corresponding
 * pointers.  The relation between keys
 * and pointers differs between leaves and
 * internal nodes.  In a leaf, the index
 * of each key equals the index of its corresponding
 * pointer, with a maximum of order - 1 key-pointer
 * pairs.  The last pointer points to the
 * leaf to the right (or NULL in the case
 * of the rightmost leaf).
 * In an internal node, the first pointer
 * refers to lower nodes with keys less than
 * the smallest key in the keys array.  Then,
 * with indices i starting at 0, the pointer
 * at i + 1 points to the subtree with keys
 * greater than or equal to the key in this
 * node at index i.
 * The num_keys field is used to keep
 * track of the number of valid keys.
 * In an internal node, the number of valid
 * pointers is always num_keys + 1.
 * In a leaf, the number of valid pointers
 * to data is always num_keys.  The
 * last leaf pointer points to the next leaf.
 */
typedef struct Node {
    void ** pointers;
    int * keys;
    struct Node * parent;
    bool is_leaf;
    int num_keys;
    struct Node * next; // Used for queue.
} Node;


Node * insert(Node * root, int id, int line);
Node * delete(Node * root, int id);
Record * find(Node * root, int id, bool verbose, Node ** leaf_out);

void print_leaves(const Node *root);
void print_tree(const Node *root);

void resume(const Node * root);
int countPages(const Node * root);

#endif //SGBD_ARVORE_B_MAIS_BPLUSTREE_H
