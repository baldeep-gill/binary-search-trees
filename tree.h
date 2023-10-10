#ifndef TREE_H
#define TREE_H

#include "treenode.h"

template <typename T> class BinarySearchTree {
    private:
        unique_ptr<TreeNode<T>> root;

    public:
        BinarySearchTree() = default;

        BinarySearchTree(const BinarySearchTree& other) {
            root.reset(cloneTree(other.root.get()));
        }

        TreeNode<T>* cloneTree(TreeNode<T>* rootIn) {
            if (!rootIn) {
                return nullptr;
            }

            TreeNode<T>* newNode = new TreeNode<T>(rootIn->data);

            newNode->setLeftChild(cloneTree((rootIn->leftChild).get()));
            newNode->setRightChild(cloneTree((rootIn->rightChild).get()));

            return newNode;
        }

        BinarySearchTree& operator=(const BinarySearchTree& other) {
            root.reset(cloneTree(other.root.get()));
            return *this;
        }

        void write(ostream & o) const {
            root->write(o);
        }

        TreeNode<T> * insert(T data) {
            TreeNode<T> * newNode = new TreeNode<T>(data);

            // Check if there is a root or not
            if (!root) {
                root.reset(newNode);
                return newNode;
            }

            TreeNode<T>* currentNode = root.get();
            TreeNode<T>* prevNode = nullptr;
            bool exists = false;

            // Find a place for the new node
            while(currentNode) {
                if (data < currentNode->data) {
                    prevNode = currentNode;
                    currentNode = &(*(currentNode->leftChild));
                } else if (currentNode->data < data) {
                    prevNode = currentNode;
                    currentNode = &(*(currentNode->rightChild));
                } else {
                    exists = true;
                    prevNode = currentNode;
                    currentNode = nullptr;
                }
            }

            // Place the new node if it doesn't already exist
            if (exists) {
                return prevNode;
            } else if (data < prevNode->data) {
                prevNode->setLeftChild(newNode);
                newNode->parent = prevNode;
            }
            else {
                prevNode->setRightChild(newNode);
                newNode->parent = prevNode;
            }

            return newNode;
        }

        TreeNode<T>* find(T data) {
            if (!root)
                return nullptr;

            TreeNode<T>* currentNode = root.get();
            TreeNode<T>* prevNode = nullptr;
            bool exists = false;

            while(currentNode) {
                if (data < currentNode->data) {
                    prevNode = currentNode;
                    currentNode = &(*(currentNode->leftChild));
                } else if (currentNode->data < data) {
                    prevNode = currentNode;
                    currentNode = &(*(currentNode->rightChild));
                } else {
                    exists = true;
                    prevNode = currentNode;
                    currentNode = nullptr;
                }
            }   

            if (exists)
                return prevNode;
            else
                return nullptr;
        }

        TreeNodeIterator<T> begin() {
            if (!root) {
                return TreeNodeIterator<T>();
            } else {
                TreeNode<T>* searchNode = root.get()    ;
                while (searchNode->leftChild) {
                    searchNode = searchNode->leftChild.get();
                }
                return TreeNodeIterator<T>(searchNode);
            }
        }

        TreeNodeIterator<T> end() {
            return TreeNodeIterator<T>(nullptr);
        }

        int maxDepth() {
            if (!root) {
                return 0;
            }

            return TreeNode<T>::maxDepth(root.get());
        }

        int balanceFactor(TreeNode<T>* node) {
            int left = TreeNode<T>::maxDepth(node->leftChild.get());
            int right = TreeNode<T>::maxDepth(node->rightChild.get());

            return left - right;
        }
};

#endif