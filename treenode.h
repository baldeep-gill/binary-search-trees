#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <memory>
#include <utility>

using namespace std;

template <typename T> class TreeNode {
    public:
        T data;
        unique_ptr<TreeNode<T>> leftChild;
        unique_ptr<TreeNode<T>> rightChild;
        TreeNode<T> * parent;

        TreeNode(T dataIN) 
            : data(dataIN), parent(nullptr) {}

        void setLeftChild(TreeNode* child) {
            leftChild.reset(child);
            if (leftChild) {
                leftChild->parent = this;
            }
        }

        void setRightChild(TreeNode* child) {
            rightChild.reset(child);
            if (rightChild) {
                rightChild->parent = this;
            }
        }

        static int maxDepth(TreeNode<T>* node) {
            if(!node) {
                return 0;
            } else {
                int depthLeft = maxDepth(node->leftChild.get());
                int depthRight = maxDepth(node->rightChild.get());

                if (depthLeft > depthRight) {
                    return depthLeft + 1;
                } else {
                    return depthRight + 1;
                }
            }
        }

        void write(ostream & o) const {
            if (leftChild) {
                leftChild->write(o);
            }

            o << " " << data << " ";

            if (rightChild) {
                rightChild->write(o);
            }
        }
};

template <typename T> ostream & operator<<(ostream & o, const TreeNode<T> & rhs) {
    rhs.write(o);
    return o;
}

template <typename T> class TreeNodeIterator {
    private:
        TreeNode<T>* current;

    public:
        TreeNodeIterator(TreeNode<T>* cIn)
            : current(cIn) {}

        TreeNodeIterator()
            : current(nullptr) {}

        T & operator*() {
            return current->data;
        }

        bool operator==(TreeNodeIterator other) {
            return (current == other.current);
        }

        bool operator!=(TreeNodeIterator other) {
            return (current != other.current);
        }

        void operator++() {
            bool breaker = false;
            TreeNode<T>* testNode = current;

            while (testNode->parent) {
                testNode = testNode->parent;
            }

            if (current->rightChild) { // Right child of node should be next node in ascending order
                current = current->rightChild.get();
            } else if (current->data > testNode->data) { // Check if current is on the right hand side of the tree and doesn't have right children
                current = nullptr;
            } else if (current->parent) { // Current is on the left side of the tree
                while (current->parent) {
                    if (current->parent->data > current->data) {
                        current = current->parent;
                        breaker = true;
                        return;
                    } else {
                        current = current->parent;
                    }
                }
            } else if (!breaker) {
                current = nullptr;
            }
        }
};

#endif