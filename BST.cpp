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
	public:
		BST():root(NULL){}
		void insert(int a, string b);
		void search(int a);
		void PrintInorder();
		void Inorder(TreeNode*); 
};


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


int main(){
	BST A;
	A.insert(40,"goku");
	A.insert(25,"biko");
	A.insert(50,"vegita");
	A.insert(30,"kulin");
	A.insert(1,"human");
	
	A.PrintInorder();
	
	
	return 0;
}
