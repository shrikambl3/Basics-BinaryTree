#include<iostream>
using namespace std;

struct node{
	int data = NULL;
	node* left = NULL;
	node* right = NULL;
};

void addNode(int val, node* referenceNode){
	if(val > referenceNode->data){
		if(referenceNode->right == NULL){					
			node * newNode = new node();
			newNode->data = val;
			referenceNode->right = newNode;
		} else {
			addNode(val, referenceNode->right);
		}
	} else if(val < referenceNode->data) {
		if(referenceNode->left == NULL){					
			node * newNode = new node();
			newNode->data = val;
			referenceNode->left = newNode;
		} else {
			addNode(val, referenceNode->left);
		}
	}
}

void printInOrder(node* referenceNode){
	if(referenceNode == NULL){
		cout<<"##Tree is Empty \n";
	} else {
		if( referenceNode->left != NULL){
			printInOrder(referenceNode->left);
		}
		cout<<referenceNode->data<<" , ";
		if( referenceNode->right != NULL){
			printInOrder(referenceNode->right);
		}
	}
}

int getLowestInLeft(node* parent,node* child){
	if(child->left == NULL){
		if(child->right == NULL){
			parent->left = NULL;
		} else {
			parent->left = child->right;
		}
		return child->data;
	} else {
		return getLowestInLeft(child,child->left);
	}
}

void deleteLowestInRight(node* referenceNode){
	node * child = referenceNode->right;
	if(child->left == NULL){
			referenceNode->data=child->data;
		if(child->right == NULL){
			referenceNode->right=NULL;
		} else {
			referenceNode->right == child->right;
		}			
	} else {
		int val = getLowestInLeft(referenceNode,referenceNode->left);
		referenceNode->data = val;
	}
}

void deleteNoneOrOneChild(node* parentNode , node* referenceNode , node* child){
	if(parentNode == NULL){
		referenceNode = child;
		return;
	}
	if(parentNode->left == referenceNode){
		parentNode->left = child;
	} else {
		parentNode->right = child;
	}
}

void getDeleteNode(int val , node* referenceNode, node* parentNode){
	if(referenceNode == NULL){
		cout<<"##TREE is empty\n";
		return;
	}
	
	if( val ==  referenceNode->data ){
		if(referenceNode->left == NULL){
			if(referenceNode->right == NULL){	//case 1 : no child present				
				deleteNoneOrOneChild(parentNode, referenceNode , NULL);
			} else {							//case 2 : right child exist
				deleteNoneOrOneChild(parentNode, referenceNode , referenceNode->right);
			}
		} else {
			if(referenceNode->right == NULL){	//case 3 : left child exist
				deleteNoneOrOneChild(parentNode, referenceNode , referenceNode->left);
			} else {							//case 4 : both child exist
				deleteLowestInRight(referenceNode);
			}
		}
	} else if( val > referenceNode->data){
		if(referenceNode->right == NULL){
			cout<<"##Element is not present in TREE\n";
		} else {
			getDeleteNode(val,referenceNode->right,referenceNode);
		}
	} else {
		if(referenceNode->left == NULL){
			cout<<"##Element is not present in TREE\n";
		} else {
			getDeleteNode(val,referenceNode->left,referenceNode);
		}
	}
}

int main(){
	int option,val;
	node* root = NULL;
	do{
		cout<<"Options:\n";
		cout<<"1:Add Node\n";
		cout<<"2:Display InOrder\n";		
		cout<<"3:Delete Node\n";				
		cout<<"4:Display Root Node\n";
		cout<<"0:exit\n";
		cin>>option;
		switch(option){
			case 1:
				cout<<"Enter the value to be added:\n";
				cin>>val;
				if(root==NULL){
					node* newNode = new node();
					newNode->data = val;
					root = newNode;
				} else {
					addNode(val, root);
				}				
				break;
			case 2:
				printInOrder(root);
				break;
			case 3:
				cout<<"Enter the value to be deleted:\n";
				cin>>val;
				getDeleteNode( val , root, NULL);
				break;
			case 4:
				if(root == NULL){
					cout<<"##TREE is empty\n";
				} else {
					cout<<"Root is Node:"<<root->data<<endl;
				}
				break;
			case 0:
				break;
			default:
				break;				
		}
		cout<<endl;
	} while ( option != 0)	;
}
