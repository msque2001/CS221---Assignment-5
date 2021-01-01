/*
    Name: Muhammad Saaim Qureshi
    Reg: 2019444

    Name: Muwahid Asim
    Reg: 2019352
*/

#include<iostream>
using namespace std;

class AVL
{
    struct Node
    {
        int number;
        string name;
        string address;
        string email;
        Node *rightPtr;
        Node *leftPtr;
        int height; 
    }*root;

    int getHeight(Node *node)
    {
        if(!node)
            return -1;
        else
            return node->height;
        
    }

    void inorder(Node *ptr)
    {
        if(ptr)
        {
            inorder(ptr->leftPtr);
            cout << ptr->number << '\t';
            inorder(ptr->rightPtr);
        }
    }

    int Max(int h1, int h2)
    {
        if(h1 > h2)
            return h1;
        return h2;
    }

    Node *singleRotateWithLeft(Node *k2)
    {
        cout << "singleRotateWithLeft called\n";
        Node *k1 = k2->leftPtr;

        k2->leftPtr = k1->rightPtr;
        k1->rightPtr = k2;

        k2->height = Max(getHeight(k2->leftPtr), getHeight(k2->rightPtr)) + 1;
        k1->height = Max(getHeight(k1->leftPtr), k2->height) + 1;

        return k1;
    }

    Node *singleRotateWithRight(Node *k1)
    {
        cout << "singleRotateWithRight called\n";
        Node *k2 = k1->rightPtr;

        k1->rightPtr = k2->leftPtr;
        k2->leftPtr = k1;

        k1->height = Max(getHeight(k1->leftPtr), getHeight(k1->rightPtr)) + 1;
        k2->height = Max(getHeight(k2->rightPtr), k1->height) + 1;

        return k2;
    }

    Node *doubleRotateWithLeft(Node *k3)
    {
        k3->leftPtr = singleRotateWithRight(k3->leftPtr);
        return singleRotateWithLeft(k3);
    }

    Node *doubleRotateWithRight(Node *k1)
    {
        k1->rightPtr = singleRotateWithLeft(k1->rightPtr);
        return singleRotateWithRight(k1);
    }

    Node *insert(Node *nodePtr, int num, string name, string add, string email)
    {
        if(!nodePtr)
        {
            nodePtr = new Node;
            nodePtr->number = num;
            nodePtr->name = name;
            nodePtr->address = add;
            nodePtr->email = email;
            nodePtr->leftPtr = nodePtr->rightPtr = NULL;
            return nodePtr;
        }
        else
        {
            if(num < nodePtr->number)
            {
                nodePtr->leftPtr = insert(nodePtr->leftPtr, num, name, add, email);
                if(getHeight(nodePtr->leftPtr) - getHeight(nodePtr->rightPtr) == 2)
                {
                    if(num < nodePtr->leftPtr->number)
                        nodePtr = singleRotateWithLeft(nodePtr);
                    else
                        nodePtr = doubleRotateWithLeft(nodePtr);
                }
            }

            else if(num > nodePtr->number)
            {
                nodePtr->rightPtr = insert(nodePtr->rightPtr, num, name, add, email);
                if(getHeight(nodePtr->rightPtr) - getHeight(nodePtr->leftPtr) == 2)
                {
                    if(num > nodePtr->rightPtr->number)
                        nodePtr = singleRotateWithRight(nodePtr);
                    else
                        nodePtr = doubleRotateWithRight(nodePtr);
                }
            }

            nodePtr->height = Max(getHeight(nodePtr->leftPtr), getHeight(nodePtr->rightPtr)) + 1;
            return nodePtr;
        }
    }

public:
    AVL()
    {
        root = NULL;
    }

    void Insert()
    {
        string name, address, email;
        name = address = email = "Saaim";
        int number;

        cout << "\nPlease enter the number: ", cin >> number, cout << endl;
        cin.ignore();
        cout << "Please enter the name: ", getline(cin, name), cout << endl;
        cout << "Please enter the address: ", getline(cin, address), cout << endl;
        cout << "Please enter the email: ", getline(cin, email), cout << endl;

        root = insert(root, number, name, address, email);
    }

    void Search()
    {
        int number;
        cout << "\nPlease enter the number you want to search: ", cin >> number, cout << endl;

        Node *tempNode = root;

        if(tempNode)
        {
            while(tempNode && tempNode->number != number)
            {
                if(number < tempNode->number)
                    tempNode = tempNode->leftPtr;
                else if(number > tempNode->number)
                    tempNode = tempNode->rightPtr;
            }

            if(!tempNode)
                cout << "Number not found!\n";
            else
            {
                cout << "\nNumber: " << tempNode->number;
                cout << "\nName: " << tempNode->name;
                cout << "\nAddress: " << tempNode->address;
                cout << "\nEmail: " << tempNode->email << endl;
            }
            
        }
        else
            cout << "Tree is empty!\n";

    }

};

int main()
{
    AVL myTree;
    myTree.Insert();
    myTree.Insert();
    myTree.Insert();
    myTree.Search();

    return 0;
}