// create a c++ programme to implement insert, traversal, maximum, minimum, searching a node in the tree 
// no of nodes, no of leaf nodes, height of the tree, number of brunches, sucessor & predesessor of a given node, height of a given node 

#include <iostream>
using namespace std;

// creating a class for nodes to initialize the members
class Node
{
public:
	int key;
	Node* parent;
	Node* lchild;
	Node* rchild;
    Node()
    {
        parent = lchild = rchild = NULL;
    }
};

//creating a class for Tree that holds all the methods
class Tree
{
  private:
	void insert(int value);
    bool search(Node* current, int value);
    void del();
    void inorder(Node* current);
    void preorder(Node* current);
    void postorder(Node* current);
    int maximum(Node* current);
    int min(Node* current);
    int noNodes(Node* current);
    int leafNode(Node* current);
    int height(Node* current);
    int branch(Node* current);
    Node* findMeomoryLoc(Node* current,int value);
    Node* getMemoryLocation(int value);
    int successor(int value);
    int predecessor(int value);
    int getHeight(Node* current, int value);
    
};


//Bstree is derived class of Tree class to inherite the methods  

class Bstree : Tree 

{
private:
     
	 //to find the total number of nodes in the BST
	 int no=1; 
	 
	 // to find the number of leaf and branches
	 int leaf=0;
	 int bh=0;
	 int ht=0;
	 int count=-1;
	 int value;
     
public:     

    //pointer root will hold the location of root node.
    Node* root;

    // taking "root" as varibale for the tree 
    Bstree()
     {
         root = NULL;
     }

    void insert(int value)
    {
        // a new node pointed by temp is created to hold the value to be inserted
        Node* temp = new Node();
        temp->key = value;

        // now we take a pointer current which will initially point to the root
        // and parent pointer will point to the parent of the current node

        Node* current = root;
        Node* parent = NULL;

        // when current is NULL, it means no BST is there and new node will form the root of the tree
        // if it is not NULL then the current has child so it will point to class 

        while (current != NULL)
        {
            parent = current;

            if (value < current->key)
            {
                current = current->lchild;
            }

            else
            {
                current = current->rchild;
            }
        }

        // now if we check the parent of current is NULL, if yes current is a root node 

        if (parent == NULL)
        {
        	//temp holds the value to be inserted, so now root will point to it.
            root = temp;  
        }
        else if(value < parent->key)
        {
            parent->lchild = temp;
        }
        else 
        {
            parent->rchild = temp;
        }

        //now the parent of temp will be the parent 
         
    }

    //for inorder traversal
    void inorder(Node* current)
    {
        if (current != NULL)
        {
	        inorder(current->lchild);
	        cout<<current->key<<" ";
	        inorder(current->rchild);   
        }
        
    }

    //for preorder traversal
    void preorder(Node* current)
    {
        if (current != NULL)
        {
           	cout<<current->key<<" ";
        	preorder(current->lchild);
        	preorder(current->rchild); 
        }
        
    }

    //for postorder traversal
    void postorder(Node* current)
    {
        if (current == NULL)
        {
            postorder(current->lchild);
       		postorder(current->rchild);
        	cout<<current->key<<" ";
        }
        
    }
    
    // for searching an element
    bool search(Node* current, int value)
    { 
		if (current==NULL){
			return false;
	    }
	    
	    while(current!=NULL){
		
			if(current->key == value){
				return true;
			}
			
			else if(current->key > value){
				current=current->lchild;
			}
			
			else current=current->rchild;   
		}	
	}

	
	// this block of code will find out the max value
	int maximum(Node* current)
	{
		if(current!=NULL){
			while(current->rchild!=NULL)
			{
				current=current->rchild;
				
				if(current->rchild==NULL){
					return current->key;
				}
			}
			
		}
		
	}
	
	// this block of code will find out the minimum value
	int min(Node* current)
	{
		 if(current!=NULL){
		 	while(current->lchild!=NULL)
			{
		 		current=current->lchild;
		    }
			return current->key;	
		}
	}
	
	// to calculate the number of nodes
	int noNode(Node* current)
	{
		if(current==NULL){
		   return 0;	
		}
		
		if(current->lchild!=NULL){
				
			no=no+1;
			no=noNode(current->lchild);
	    }
		    
		if(current->rchild!=NULL){
		    no=no+1;
		    no=noNode(current->rchild);
		}
		return no;
	}
	
	// to calculate the number of learf nodes avialable in the tree
	
	int leafNode(Node* current)
	{
		if(current==NULL){
		   return 0;	
		}
		
		if(current!=NULL){
			
			leafNode(current->lchild);
			
			if((current->lchild==NULL) && (current->rchild == NULL))
			   {
				   leaf=leaf+1;
			   }   
			
			leafNode(current->rchild);
	    }
	    
		return leaf;
	}
	
	
	//to count the number of brunches 
	int branch(Node* current)
	{
		if(current==NULL){
			return 0;
		}
		
		if(current!=NULL){
				
				branch(current->lchild);
				
				if((current->lchild==NULL) && (current->rchild == NULL))
				{
					bh=bh+1;
				}
				
				branch(current->rchild);
				
		}
		return bh;
	}
	
	
	// to calculate the height of the tree
	int height(Node* current)
	{
		if(current==NULL)
		{
			return -1;
		}
	
		return 1+ max(height(current->rchild),height(current->lchild));
	}

    // custom function to find memory location
    Node* findMeomoryLoc(Node* current,int value)
    {
    	if (current == NULL || value == current->key)
           return current;
        if (value < current->key)
           findMeomoryLoc(current->lchild, value);
        else
           findMeomoryLoc(current->rchild, value);
	}
	
	// custom function to get the memory loaction found by the findMemoryLoc
	
	Node* getMemoryLocation(int value)
    {
        return findMeomoryLoc(root, value);
    }
	
	// to find successor
    
	int successor(int value)
	{
		Node* current=getMemoryLocation(value);
		
		if (current==NULL) 
			return 0;
		if (current->key==maximum(current)) 
			return 0;		
		if (current->rchild!=NULL) 
			return min(current->rchild);
			 
		//if node is a left child	
		if(current->key<current->parent->key)
			{   
			    //immediate parent is successor
				return current->parent->key;
			}
		else
			{
				//loop to move towards parent until it is a right child.
				
				while(current->key>current->parent->key)
				{
					current=current->parent;
				}
				return current->parent->key;
			}
	}
	
	// to find the predesessor 
	
	int predecessor(int value)
	{
		Node* current=getMemoryLocation(value);
		
		if (current==NULL) 
			return 0;
		if (current->key==min(current)) 
			return 0;		
		if (current->rchild!=NULL) 
			return maximum(current->rchild);
			 
		//if node is a left child	
		if(current->key>current->parent->key)
			{   
			    //immediate parent is successor
				return current->parent->key;
			}
		else
			{
				//loop to move towards parent until it is a right child.
				
				while(current->key<current->parent->key)
				{
					current=current->parent;
				}
				return current->parent->key;
			}  
	}
	
	// for searching an element
    int getHeight(Node* current, int value)
    {           
		 
		if (current==NULL){
			return count;
	    }
	    
	    while(current!=NULL){
		    
		    count++;
			if(current->key == value){
				return count; 
			}
			
			else if(current->key > value){
				current=current->lchild;
			}
			
			else current=current->rchild;   
		}
		
		return count;	
	}
	
	// Calling the getHeight function 
	int getH(int value)
    {
    	return getHeight(root, value);
	}
	
	/*
	// to delete a node from the tree
	delNode(int value)
	{
		Node *temploc=NULL;
	    Node* node=getMemoryLocation(value);
	    
		if (node == NULL)
		{
			return 0;
		} 
        
		if (node->lchild == NULL && node->rchild == NULL)
	    { 
            if(node->parent==NULL)
			{
				root == NULL;
		    }
			
			else
			{
			    if(node==node->parent->rchild)
				node->parent->rchild=NULL;
				
				else
				   
				   node->parent->lchild=NULL;
			}
			
			delete node;
		    return 1;     
	    }
	    
	    // delete condition if a node has two child
	    
	    if(node->lchild!=NULL&&node->rchild!=NULL)
        {
    	    temploc=getMemoryLocation(successor(node->key));
    	    node->key=temploc->key;
    	
    	    ////The node that is replaced, it's parent should point to null
			if(temploc==temploc->parent->rchild) 
			{ 
				 
				temploc->parent->rchild=NULL;
	     	}
				 
		    else
			    temploc->parent->lchild=NULL;
		        delete temploc;
		        return 1;
	    }
	    
	    // when the node has only one child
	    if(node->lchild!=NULL)
	    {
		    temploc=node->lchild;
		    temploc->parent=node->parent;
		    node->parent->lchild=temploc;
     	}
	
	    else
	    {
		    temploc=node->rchild;
		    temploc->parent=node->parent;
		    node->parent->rchild=temploc;
	    }
	    
		delete node;
	    return 1;
    }*/

};


int main()
{
		Bstree b1;
		b1.insert(11);
		b1.insert(20);
		b1.insert(21);
		b1.insert(10);
		b1.insert(27);
		b1.insert(15);
        b1.insert(31);
    
		cout<<"Preorder: "<<endl; //preorder traversal 
		b1.preorder(b1.root);
        cout << "\n\nInorder: " <<endl; //inorder traversal 
        b1.inorder(b1.root);
        cout << "\n\nPostorder: " << endl; //postorder traversal
        b1.postorder(b1.root);
        
        cout<<"\n\nSearch this value: (1)"<<endl; //to search a value from in the binary tree
        cout<<b1.search(b1.root, 1);
        
        cout<<"\n\nThe maximum of the tree: "<<endl; // to return maximum of the tree
        cout<<b1.maximum(b1.root);
        
        cout<<"\n\nThe minimum of the tree: "<<endl; // to return minimum of the tree
        cout<<b1.min(b1.root);
        
        cout<<"\n\nThe number of nodes in tree are: "<<endl; //to display the number of nodes in the tree
        cout<<b1.noNode(b1.root);
        
        cout<<"\n\nThe number of leaf nodes are: "<<endl; //to display the number of leaf nodes in the tree
        cout<<b1.leafNode(b1.root);
        
        cout<<"\n\nTotal number of branches are: "<<endl; //to display the number of branches in the tree 
		cout<<b1.branch(b1.root);
		
		cout<<"\n\nTree height: "<<endl; // to display tree height
		cout<<b1.height(b1.root);
		
		cout<<"\n\nThe successor of (11): "<<endl; //to display the successor of a given number		
		cout<<b1.successor(11);
		
		cout<<"\n\nThe predecessor of (15): "<<endl; //to display the predessor of a given number
		cout<<b1.predecessor(15); 
		
		cout<<"\n\nThe height of the node (27) is: "<<b1.getH(27)<<endl;  //to display height of a node in th tree 
		
		//<<b1.delNode(11); // to delete a node (here I am deleting node 11 but it can be made to delete user input [node] from the tree )
}


