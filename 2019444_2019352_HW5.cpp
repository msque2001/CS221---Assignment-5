
/*
    Name: Muhammad Saaim Qureshi
    Reg: 2019444

    Name: Muwahid Asim
    Reg: 2019352
*/

#include<iostream>
#include<string>
using namespace std;

class AVL
{
    struct Node
    {
        int number;
        string name;
        string address;
        string email;
        Node* rightPtr;
        Node* leftPtr;
        int height;
    }*root;

    int getHeight(Node* node)
    {
        if (!node)
            return -1;
        else
            return node->height;

    }
    int height(Node* N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }

    int Max(int h1, int h2)
    {
        if (h1 > h2)
            return h1;
        return h2;
    }

    Node* singleRotateWithLeft(Node* k2)
    {
        Node* k1 = k2->leftPtr;

        k2->leftPtr = k1->rightPtr;
        k1->rightPtr = k2;

        return k1;
    }

    Node* singleRotateWithRight(Node* k1)
    {
        Node* k2 = k1->rightPtr;

        k1->rightPtr = k2->leftPtr;
        k2->leftPtr = k1;

        k1->height = Max(getHeight(k1->leftPtr), getHeight(k1->rightPtr)) + 1;
        k2->height = Max(getHeight(k2->rightPtr), k1->height) + 1;

        return k2;
    }

    Node* doubleRotateWithLeft(Node* k3)
    {
        k3->leftPtr = singleRotateWithRight(k3->leftPtr);
        return singleRotateWithLeft(k3);
    }

    Node* doubleRotateWithRight(Node* k1)
    {
        k1->rightPtr = singleRotateWithLeft(k1->rightPtr);
        return singleRotateWithRight(k1);
    }
    Node* minValueNode(Node* node)
    {
        Node* current = node;

        
        while (current->leftPtr != NULL)
            current = current->leftPtr;

        return current;
    }
    Node* insert(Node* nodePtr, int num, string name, string add, string email)
    {
        if (!nodePtr)
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
            if (num < nodePtr->number)
            {
                nodePtr->leftPtr = insert(nodePtr->leftPtr, num, name, add, email);
                if (getHeight(nodePtr->leftPtr) - getHeight(nodePtr->rightPtr) == 2)
                {
                    if (num < nodePtr->leftPtr->number)
                        nodePtr = singleRotateWithLeft(nodePtr);
                    else
                        nodePtr = doubleRotateWithLeft(nodePtr);
                }
            }

            else if (num > nodePtr->number)
            {
                nodePtr->rightPtr = insert(nodePtr->rightPtr, num, name, add, email);
                if (getHeight(nodePtr->rightPtr) - getHeight(nodePtr->leftPtr) == 2)
                {
                    if (num > nodePtr->rightPtr->number)
                        nodePtr = singleRotateWithRight(nodePtr);
                    else
                        nodePtr = doubleRotateWithRight(nodePtr);
                }
            }

            nodePtr->height = Max(getHeight(nodePtr->leftPtr), getHeight(nodePtr->rightPtr)) + 1;
            return nodePtr;
        }
    }
    void deleteNode(int num, Node*& nodePtr)
    {
        if (num < nodePtr->number)
            deleteNode(num, nodePtr->leftPtr);
        else if (num > nodePtr->number)
            deleteNode(num, nodePtr->rightPtr);
        else
            makeDeletion(nodePtr); 
    }

    void makeDeletion(Node*& nodePtr) {
        Node* tempNodePtr;
       
        if (nodePtr == NULL)
            cout << "Cannot delete empty node.\n";
        else if (nodePtr->rightPtr == NULL)
        {
            tempNodePtr = nodePtr;
            nodePtr = nodePtr->leftPtr;
            
            delete tempNodePtr;
        }
        else if (nodePtr->leftPtr == NULL)
        {
            tempNodePtr = nodePtr;
            nodePtr = nodePtr->rightPtr;
           
            delete tempNodePtr;
        }
       
        else	
        {
            
            tempNodePtr = nodePtr->rightPtr;
            
            while (tempNodePtr->leftPtr)
                tempNodePtr = tempNodePtr->leftPtr;
           
            tempNodePtr->leftPtr = nodePtr->leftPtr;
            tempNodePtr = nodePtr;
           
            nodePtr = nodePtr->rightPtr;
            delete tempNodePtr;
        }
    }

    int getBalance(Node* N)
    {
        if (N == NULL)
            return 0;
        return height(N->leftPtr) -
            height(N->rightPtr);
    }

    void displayInOrder(Node* ptr)
    {
        if (ptr != NULL)
        {
            displayInOrder(ptr->leftPtr);
            cout << "\nNumber: " << ptr->number;
            cout << "\nName: " << ptr->name;
            cout << "\nAddress: " << ptr->address;
            cout << "\nEmail: " << ptr->email << endl;
            displayInOrder(ptr->rightPtr);
        }
    }
    void displayPostOrder(Node* ptr)
    {
        if (ptr != NULL)
        {
            displayPostOrder(ptr->leftPtr);
            displayPostOrder(ptr->rightPtr);
            cout << "\nNumber: " << ptr->number;
            cout << "\nName: " << ptr->name;
            cout << "\nAddress: " << ptr->address;
            cout << "\nEmail: " << ptr->email << endl;
        }
    }
    void displayPreOrder(Node* ptr)
    {
        if (ptr != NULL)
        {
            cout << "\nNumber: " << ptr->number;
            cout << "\nName: " << ptr->name;
            cout << "\nAddress: " << ptr->address;
            cout << "\nEmail: " << ptr->email << endl;
            displayPreOrder(ptr->leftPtr);
            displayPreOrder(ptr->rightPtr);
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

    void Search_num()
    {
        int number;
        cout << "\nPlease enter the number you want to search: ", cin >> number, cout << endl;

        Node* tempNode = root;

        if (tempNode)
        {
            while (tempNode && tempNode->number != number)
            {
                if (number < tempNode->number)
                    tempNode = tempNode->leftPtr;
                else if (number > tempNode->number)
                    tempNode = tempNode->rightPtr;
            }

            if (!tempNode)
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

    Node* deleteNode(Node* root, int num)
    {

         
        if (root == NULL)
            return root;

     
        if (num < root->number)
            root->leftPtr = deleteNode(root->leftPtr, num);

    
        else if ( num > root->number)
            root->rightPtr = deleteNode(root->rightPtr, num);

   
        else
        {
           
            if ((root->leftPtr == NULL) ||
                (root->rightPtr == NULL))
            {
                Node* temp = root->leftPtr ?
                    root->leftPtr :
                    root->rightPtr;

                
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else  
                    *root = *temp;  
                free(temp);
            }
            else
            {
            
                Node* temp = minValueNode(root->rightPtr);

                  
                root->number = temp->number;

                
                root->rightPtr = deleteNode(root->rightPtr,
                    temp->number);
            }
        }

        
        if (root == NULL)
            return root;

        
        root->height = 1 + Max(height(root->leftPtr),
            height(root->rightPtr));

      
        int balance = getBalance(root);

         
        if (balance > 1 &&
            getBalance(root->leftPtr) >= 0)
            return singleRotateWithRight(root);

         
        if (balance > 1 &&
            getBalance(root->leftPtr) < 0)
        {
            root->leftPtr = singleRotateWithLeft(root->leftPtr);
            return singleRotateWithRight(root);
        }

        
        if (balance < -1 &&
            getBalance(root->rightPtr) <= 0)
            return singleRotateWithLeft(root);

        
        if (balance < -1 &&
            getBalance(root->rightPtr) > 0)
        {
            root->rightPtr = singleRotateWithRight(root->rightPtr);
            return singleRotateWithLeft(root);
        }

        return root;
    }
    void remove()
    {
        int num;
        cout << "\nPlease enter the number you want to delete: ", cin >> num, cout << endl;
        
        deleteNode(root, num);
    }
    void in()
    {

        displayInOrder(root);
    }
    void pre()
    {

        displayPreOrder(root);
    }
    void post()
    {

        displayPostOrder(root);
    }

};

int menu();

int main()
{
    AVL PhoneBook;
    bool isDone = false;
    int choice;

    while(!isDone)
    {
        choice = menu();
        switch (choice)
        {
        case 1:
            PhoneBook.Insert();
            break;
        case 2:
            PhoneBook.remove();
            break;
        case 3:
            PhoneBook.Search_num();
            break;
        case 4:
            PhoneBook.in();
            break;
        case 5:
            PhoneBook.pre();
            break;
        case 6:
            PhoneBook.post();
            break;
        case 7:
            isDone = true;
            cout << "\nBye, bye!\n";
            break;
        
        default:
            cout << "\nIncorrect choice!\n";
            break;
        }
    }


    return 0;
}

int menu()
{
    int choice;

    cout << "\n1) Insert Contact";
    cout << "\n2) Delete Contact";
    cout << "\n3) Search Contact";
    cout << "\n4) Display Contact (In-order)";
    cout << "\n5) Display Contact (Pre-order)";
    cout << "\n6) Display Contact (Post-order)";
    cout << "\n7) Exit Program\n";

    cout << "\nPlease enter the number corrensponding to your choice: ", cin >> choice, cout << endl;
    return choice;
}
