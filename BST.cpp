#include <iostream>
using namespace std;

class TreeNode{
	private:
		TreeNode *left,*right;
		TreeNode *parent;
		string name;
		int key;
	public:
		TreeNode():left(NULL),right(NULL),parent(NULL),key(0),name(""){}
		TreeNode(int a, string b):left(NULL),right(NULL),parent(NULL),key(a),name(b){}
	friend class BST;
}; 

class BST{
	private:
		TreeNode* root;
		TreeNode* successor(TreeNode*);
		TreeNode* leftmost(TreeNode*);
	public:
		BST():root(NULL){}
		void insert(int a, string b);
		void PrintInorder();
		void Inorder(TreeNode*); 
		TreeNode* search(int);
		void Delete(int);
		void printleftmost();
};

void BST::printleftmost(){ // for leftmost function verify
	TreeNode *current= root;
	current = leftmost(current);
	cout<< "leftmost name is: "<<current->name<<endl;
}


TreeNode* BST::leftmost(TreeNode* current){
		if (current->left==NULL) return current;
		current=current->left;
		return leftmost(current);
}

TreeNode* BST::successor(TreeNode *current){
	
	if (current->right == NULL){
		if (current==current->parent->left){
			return current->parent;
		}
		else{
			while (current!=current->parent->left){
				current = current->parent;
				if (current==NULL){
					return NULL;
				} 
			}
			return current->parent;
		}
	}
	else {
		return leftmost(current->right);
	}
	
}

void BST::insert(int a, string b){
	TreeNode *NewNode = new TreeNode(a,b);
	if (root==NULL){
		root=NewNode;
		return;
	}
	TreeNode *current = root;
	TreeNode *CurrentParent= current->parent;
	while (current!=NULL){
		CurrentParent = current;
		if (NewNode->key>current->key){
			current = current->right;
		}
		else{
			current = current->left;
		}
	}
	
	if (NewNode->key>CurrentParent->key){
		CurrentParent->right = NewNode;
		NewNode->parent = CurrentParent;
	}
	else{
		CurrentParent->left = NewNode;
		NewNode->parent = CurrentParent;
	}
}

void BST::PrintInorder(){
	TreeNode *current = root;
	Inorder(current);
}

void BST::Inorder(TreeNode* A){
	if (A){
		Inorder(A->left);
		cout << " element is: "<<A->name<<" key is: "<< A->key<<endl;
		Inorder(A->right);
	}
}

TreeNode* BST::search(int kkey){
	
	TreeNode *current = root;
	while (current!=NULL){
		if (current->key==kkey){
//			cout << "name is: "<< current->name<<endl;
			return current;
		}
		if (current->key<kkey){
			current=current->right;
		}
		else {
			current=current->left;
		}
	}
	cout << "no finding"<< endl;
	return NULL;	
}

void BST::Delete(int kkey){
	TreeNode *current = search(kkey) ;
	if (current==NULL){
		cout << "no such key element can delete"<<endl;
	}
	
	if (current->right != NULL){
		TreeNode *newcurrent = leftmost(current->right);
		newcurrent->parent = current->parent;
		newcurrent->left= current->left;
		if (newcurrent!=current->right){
			newcurrent->right=current->right;
		}
		delete current;
	}
	
	else if(current->left!=NULL){
		current->left->parent = current->parent;
		current->parent->left = current->left;
		delete current;
	}
	else{
		delete current;
		current = NULL;
	}
	
}



int main(){
	BST A;
	A.insert(40,"goku");
	A.insert(25,"biko");
	A.insert(50,"vegita");
	
	A.insert(30,"kulin");
	A.insert(1,"human");

	A.search(40);
	A.search(1);
	A.search(144);
	
	A.PrintInorder();
	
	A.Delete(1);
	A.PrintInorder();
	
	
	
	return 0;
}
