#include <iostream>
using namespace std;

class TreeNode{
	private:
		TreeNode* left, *right;
		TreeNode* parent;
		string name;
		int key;
		bool color;    //consider 0 is red
	public:
		TreeNode():left(NULL),right(NULL),parent(NULL),name(""),key(0),color(0){}  
		TreeNode(int EnterKey, string EnterName):left(NULL),right(NULL),parent(NULL),name(EnterName),key(EnterKey),color(0){} 
	friend class RBT;
};


class RBT{
	private:
		TreeNode* root;
		TreeNode* nil;
	public:
		RBT():root(NULL){
			nil = new TreeNode;
			nil->color=1;
			}
		void LeftTurn (TreeNode* );
		void RightTurn (TreeNode* );
		
		void Insert (int , string );
		char JudgeInsertion(TreeNode*);
		void InsertFix(TreeNode*);
		
		// these two use in deletenode		
		TreeNode* find(int);
		void Delete (int);
		void DeleteFix(TreeNode*);
		TreeNode* successor (TreeNode *);
		TreeNode* LeftMost (TreeNode* );
		
		void LeftRotation(TreeNode*);
		void RightRotation(TreeNode*);
		 
		TreeNode* GetGrandfather(TreeNode*);
		void PrintInorder();
		void InorderPrint(TreeNode*);
};

TreeNode* RBT::GetGrandfather(TreeNode* Current){
	return Current->parent->parent;
}

TreeNode* RBT::LeftMost(TreeNode* current){
	while(current->left!=nil){
		current= current->left;
	}
	return current;
}

TreeNode* RBT::successor ( TreeNode* current){
	if (current->right != nil){
		return LeftMost(current->right);
	}
	else{
		while (	current->parent!=nil && current!=current->parent->left){ //need to notice no succeccor  
			current=current->parent;
		}
		return current->parent;
	}
}

TreeNode* RBT::find(int EnterKey){
	TreeNode* current = root; 
	while(current!=nil){
		if (current->key==EnterKey){
			return current;
		}
		if (EnterKey<current->key){
			current=current->left;
		}
		else{
			current=current->right;
		}
	}
	cout << "can not find item which key is: "<<EnterKey<<endl; 
	return current;	
}

void RBT::LeftRotation(TreeNode* current){
	TreeNode* y = current->right;
	TreeNode* z = y->left;
	
	current->right = z;
	if (z!=nil){
		z->parent = current;
	}
	
	y->parent= current->parent; 
	
	if (current->parent==nil){
		root = y;
	}
	if (current == current->parent->left){
		current->parent->left = y;
	}
	else {
		current->parent->right = y;
	}
	
	current->parent = y;
	y->left= current;
	
}

void RBT::RightRotation(TreeNode* current){
	TreeNode* y = current->left;
	TreeNode* z = y->right;
	
	current-> left = z;
	if (z!=nil){
		z->parent = current;
	}
	
	y->parent= current->parent; 
	
	if (current->parent==nil){
		root = y;
	}
	if (current == current->parent->left){
		current->parent->left = y;
	}
	else {
		current->parent->right = y;
	}
	
	current->parent = y;
	y->right= current;
		
}

void RBT::Insert(int EnterKey, string EnterName){
	TreeNode* newnode = new TreeNode(EnterKey, EnterName);
	TreeNode* Current = root;
	TreeNode* CurrentFather = NULL;
	
	if (root == NULL){  //if this is new RBT, root is NULL
		root = newnode;
		root->parent = nil;
		root->left = nil;
		root->right = nil;
		root->color = 1;
		return;
	}
	
	while (Current!=nil){
		CurrentFather = Current;
		if (newnode->key<Current->key){
			Current= Current->left;
		}
		else{
			Current= Current->right;
		}
	}
	

	newnode->parent = CurrentFather;
	if (newnode->key < CurrentFather->key){
		CurrentFather->left = newnode ;

	}
	else {
		CurrentFather->right = newnode ;	
	}
	newnode->left=nil;
	newnode->right=nil;

	InsertFix(newnode);
}

char RBT::JudgeInsertion(TreeNode* Current){
	TreeNode* CurrentFather= Current->parent;
	if ( CurrentFather==  CurrentFather->parent->left){  //uncle is grandfather right
		if ( CurrentFather-> parent-> right->color == 0){ //uncle is red
			return 'A';
		}
		else{ //uncle is black
			if (Current== CurrentFather->left){ 
				return 'B';
			}
			else return 'C';
		}
	}
	else {
		if ( CurrentFather-> parent-> left ->color == 0){ //uncle is red
			return 'D';
		}
		else{ //uncle is black
			if (Current== CurrentFather->right){ 
				return 'E';
			}
			else return 'F';
		}
	}
}

void RBT::InsertFix(TreeNode* Current){
	
	while (!Current->parent->color){	 //current parent is red need to enter the judge
//	 cout <<"current name= "<<Current->name << " current judge" << judge(Current) <<endl;
//	 cout <<"current father key: "<< Current->parent->key <<" current key: "<< Current->key<<endl;
		switch (JudgeInsertion(Current)){
			case 'A':
				Current->parent->color=1;
				GetGrandfather(Current)->right->color=1;
				GetGrandfather(Current)->color=0;
				Current= GetGrandfather(Current);
				break;
			case 'B':   //uncle is black, newnode is parrent left
				Current->parent->color=1;
				GetGrandfather(Current)->color=0;
				RightRotation(GetGrandfather(Current));
				break;
			case 'C':
				Current = Current->parent;
				LeftRotation(Current);
				Current->parent->color=1;
				GetGrandfather(Current)->color=0;
				RightRotation(GetGrandfather(Current));
				break;
				
		// symmetric structure	
			case 'D':
				Current->parent->color=1;
				GetGrandfather(Current)->left->color=1;
				GetGrandfather(Current)->color=0;
				Current= GetGrandfather(Current);
				break;
			case 'E':
				Current->parent->color=1;
				GetGrandfather(Current)->color=0;
				LeftRotation(GetGrandfather(Current));
				break;
			case 'F':
				Current = Current->parent;
				LeftRotation(Current);
				Current->parent->color=1;
				GetGrandfather(Current)->color=0;
				RightRotation(GetGrandfather(Current));
				break;
		}
	}
	
	root->color=1;
} 


// can be modify in simple way.
void RBT::Delete(int key){
	
	TreeNode* current = find(key);
	if (current == nil)	return;
	
	TreeNode* DeleteNode = NULL;
	TreeNode* Child = NULL;
	if (current->left==nil&&current->right==nil){
		DeleteNode = current;
		Child = nil;
		if (current==current->parent->left){
			current->parent->left= Child;
		}
		else{
			current->parent->right= nil;
		}
		Child->parent = current->parent;
	}
	
	else if (current->left!=nil&&current->right==nil){
		DeleteNode = current;
		Child = current->left; 
		Child->parent = current->parent;
		current->parent->left= current->left;
 
	}
	
	else if (current->right!=nil&&current->left==nil){
		DeleteNode = current;
		Child = current->right;
		Child->parent = current->parent;
		current->parent->right= current->right;
	}
	
	else if (current->left!=nil && current->right != nil){
		DeleteNode = successor(current);
		Child = DeleteNode->right;
		Child->parent = DeleteNode->parent;
		if (DeleteNode == DeleteNode->parent->left){
			DeleteNode->parent->left = Child;			
		}
		else{
			DeleteNode->parent->right = Child;
		}
			
		current->key = DeleteNode->key;
		current->name = DeleteNode->name;
	}
	
	delete DeleteNode;
	if (current->color==1){
		DeleteFix(Child);
	}
}

void RBT::DeleteJudge(TreeNode* current){
	
}

void RBT::DeleteFix(TreeNode* current){
	
}



void RBT::PrintInorder(){
	TreeNode * current = root;
	if (root==NULL){
		cout << "RBT is empty"<<endl;
		return;
	}
	InorderPrint(current);
	cout <<" root is: "<< root->name << endl;
}

void RBT::InorderPrint(TreeNode* current){
	if(current != nil){
		InorderPrint(current->left);
		cout << "key is: "<<current->key<<" name is: "<< current->name<< " color is: "<< current-> color <<endl;
		InorderPrint(current->right);
	}
}


int main(){
	
	RBT A;
	A.PrintInorder();
	A.Insert(40,"goku");
	A.Insert(25,"biko");
	A.Insert(50,"vegita");
	A.PrintInorder();
	
	A.Insert(30,"kulin");
	A.Insert(1,"human");
	A.Insert(27,"napa");
	A.Insert(28,"snapa");
	A.Insert(35,"lati");
	A.PrintInorder();
	
	
	return 0;
}



