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
			
		while (current!=current->parent->left){
			current = current->parent;
			if (current->parent==NULL){
				return NULL;
			} 
		}
		return current->parent;
		
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
		return;
	}
	
	cout <<"will delete element: "<<current->name<< endl;
	
	if (current->left==NULL && current->right==NULL) {
		if (current == current->parent->left){
			current->parent->left = NULL;
		}
		else{
			current->parent->right = NULL;
		}
		delete current;
		return;
	}
	
	else if (current->right==NULL && current->left != NULL){
		TreeNode *Parent = current->parent;
		TreeNode *leftChild = current->left;
		if (Parent->right==current){
			Parent->right = leftChild;
		}
		else{
			Parent->left = leftChild;
		}
		delete current;
		return;
	}
	else{
		TreeNode *newcurrent = successor(current);
	//	cout <<"delete element is: "<< current->name << " and debug successor is "<< newcurrent->name<<endl;
		TreeNode *Parent = current->parent;
		TreeNode *rightChild = current->right;
		TreeNode *leftChild = current->left;
		
	//	cout << "==================debug=========================="<<endl<< " Parent: " << Parent->name<< " rightChild: "<< rightChild->name<< " leftChild: "<< leftChild->name<<endl<< "================================================="<<endl;
		if (newcurrent==rightChild){
			if (current == Parent->left){
				Parent->left = newcurrent;
			}
			else{
				Parent->right = newcurrent;
			}
			newcurrent->parent = Parent;
			newcurrent->left = leftChild;
			leftChild->parent = newcurrent;
		//	cout <<"===================================end delete flow===================="<<endl << "newcurrent parrent: "<<newcurrent->parent->name <<" newcurrent left: "<< newcurrent->left->name<< " newcurrent right: "<< newcurrent->right<< endl<< "===========================================" << endl;
			delete current;
			return;
		}
		else{
			//need to modify current parent which clild pointer
			if (current == Parent->left){
				Parent->left = newcurrent;
			}
			else{
				Parent->right = newcurrent;
			}
			// shifted leaf need to modify which parent pointer to NULL
			if (newcurrent->right != NULL){
				newcurrent->parent->left= newcurrent->right;
				newcurrent->right->parent = newcurrent->parent;
			}
			else{
				newcurrent->parent->left = NULL;
			}
		
			//let current connecting pointer connect to newcurrent
			newcurrent->parent = Parent;
			newcurrent->left = leftChild;
			newcurrent->right = rightChild;
			leftChild->parent= newcurrent;
			rightChild->parent= newcurrent;
		//	cout <<"===================================end delete flow===================="<<endl << "newcurrent parrent: "<<newcurrent->parent->name<<" newcurrent left: "<< newcurrent->left->name<< " newcurrent right: "<< newcurrent->right->name<< endl<< "===========================================" << endl;
		//	cout << "check one thing: "<< newcurrent->left->left<<endl;
			delete current;
			return;	
		}
	}	
}



int main(){
	BST A;
	A.insert(40,"goku");
	A.insert(25,"biko");
	A.insert(50,"vegita");
	
	A.insert(30,"kulin");
	A.insert(1,"human");
	A.insert(27,"napa");
	A.insert(28,"snapa");
	A.insert(35,"lati");
	
	A.search(40);
	A.search(1);
	A.search(144);
	
	A.PrintInorder();
	
	A.Delete(333);
	A.Delete(30);
	A.PrintInorder();
	A.Delete(25);
	A.PrintInorder();
	
	
	
	return 0;
}
