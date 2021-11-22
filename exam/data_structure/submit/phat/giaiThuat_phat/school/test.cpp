#include <iostream>
#include <conio.h>
using namespace std;


class Animal{

    private:   
        string name;
        float height,weight;
        int id;

    public:
    	virtual void toStream (istream& is);
        friend istream& operator >> (istream& ,Animal* );
        friend ostream& operator << (ostream& os,Animal* al);
        Animal operator = (Animal* al); 
        
        Animal();
        Animal(string name,float height, float weight, int id);
        Animal(Animal* al);
        ~Animal();
        void setName(string name);
        void setID(int &id);
        string getName();
        int getID();
        void EnterID();
		void EnterName();            
};


//Dv An Co 
typedef class Graminivore:public Animal{

        string food;
        int amount;
    public: 
        virtual void toStream(istream& is);
        friend ostream& operator << (ostream& os,Graminivore *gn);
        
}Grami;


// Dv An Thit
typedef class Hypercarnivore:public Animal{
        string food;
        int amount;
    public: 
        virtual void toStream(istream& is);
        friend ostream& operator << (ostream& os,Hypercarnivore *hy);
        
}Hyper;

// Vi Sinh Vat
typedef class Microorganism:public Animal{
		string food; 
        int amount;
    public: 
        virtual void toStream(istream& is);
        friend ostream& operator << (ostream& os,Microorganism *mi);
}Microo;


// Cay Tim Kiem Nhi Phan
struct Node{
	Animal *data; 
	Node* left;
	Node* right; 
}; 


struct BST{
		
		Node *root; 
		long size;
		
		Node* CreateNode(Animal *al); 
		//Work With Tree
        int LeftOf(Animal *al,Node* root );
        int RightOf(Animal *al,Node* root );
        Node* Insert(Node* &root, Animal* al1);
        Node* SearchName(Node* root,Animal* al1);
        void PostOrder(Node* root);
        void InOrder(Node* root);
        Node* Delete(Node* &root, Animal *al1);
        Animal* LeftMostAnimal(Node* root);
};

//Linked List
struct NodeL{
    Animal *data;
    NodeL *next;
};

struct SList{
	NodeL *head;
	NodeL *tail;
	long size;
	SList();
    ~SList();
	NodeL* CreateNodeL(Animal *v);
    void addLast(Animal *v);
    NodeL *previous(NodeL *p);
    NodeL *searchName(Animal* al);
    void sort();
    void removeFirst();
    void removeLast();
    void removeName();
    void traverse() const;
};
 
void Hyper::toStream(istream& is){
    Animal::toStream(is);
    fflush(stdin);
    cout <<"\t\tFavorite Food: ";
    is >> food;
    cout <<"\t\tAmout: ";
    is >> amount;
}

ostream& operator << (ostream& os,Hyper *hy){
    Animal *al = static_cast <Animal *> (hy);
    os << al;
    os << "\t\tAmount: "<< hy->amount<<endl; 
    os << "\t\tFavorite Food: "<< hy->food<<endl; 
    cout <<"\t*********************~~*********************" << endl; 
}

NodeL* SList::CreateNodeL(Animal *v){
	NodeL* p = new NodeL;
    Animal *v1 = new Animal(v);
	p->data = v1;	
	p->next = NULL;	
	return p; 
}

//khoi tao
SList::SList(){
    head = NULL;
    tail = NULL;
    size =0;
}

// giai phong bo nho
SList::~SList(){
    head = NULL;
    tail = NULL;
    size = 0;
}

// them vao cuoi
void SList::addLast(Animal *v){
    NodeL *p = CreateNodeL(v);
    if(size == 0){
        head = p;
        tail = p;
    }
    else{
        tail->next = p;
        tail = p;
    }
    size = size + 1;
}

// Duyet cac ptu trong danh sach
void SList::traverse() const{
    NodeL *p = head;
    while(p != NULL){
    cout << p->data; 
        p = p->next;
    }
    cout <<endl;
    delete p;   
}

// Tim kiem 
NodeL *SList::searchName(Animal *al){
	NodeL *p = head;
    while(p != NULL){
        if(p->data->getName() == al->getName())
            break;
        p=p->next;
    }
    return p;
}

// Sap xep
void SList::sort(){
    for(NodeL *p = head; p->next != NULL; p=p->next){
        for(NodeL *q = p->next; q != NULL; q = q->next){
            if(p->data->getID() > q->data->getID()){
                swap(p->data,q->data);
            }
        }
    }
}

// tim 1 phan tu ngay truoc phan tu bat ky
NodeL* SList::previous(NodeL *p) {
	NodeL *t = head;
	while (t->next != p)
		t = t->next;
	return t;
}


void SList::removeFirst(){
   if(size == 0){
   	    cout <<" No Name Has Be Found ! ";
	}else{
		NodeL*t = head;
		head=head->next;
		delete t;
		size--;
    }
}


void SList::removeLast(){
	NodeL *pre = previous(tail);
	NodeL*t =tail;
	pre->next=NULL;
	tail=pre;
	delete t;
	size--;
}	

// xoa 1 ptu 
void SList::removeName(){
    string name;
    cout<<"Enter the animal that need to delete: ";
    fflush(stdin);
    getline(cin,name);
    NodeL *p = head;
    for(p;p!=NULL;p=p->next){
        if(p->data->getName()==name){
            if(p == head){
                removeFirst();
                break;
            }
            else if(p==tail){
                removeLast();
                break;
            }
            else{
                NodeL *pre = previous(p);
                pre->next = p->next;
                delete p;
                size--;
                break; 
            }
        }
    }
    if(p == NULL){
        cout <<" No Name Has Be Found ! " <<endl;
    }
}

void Grami::toStream(istream& is){
    Animal::toStream(is);
    fflush(stdin);
    cout <<"\t\tFavorite Food: ";
    is >> food;
    cout <<"\t\tAmount: ";
    is >> amount; 
}

ostream& operator << (ostream& os,Grami *gn){
    Animal *al = static_cast <Animal *> (gn);
    os << al;
    os << "\t\tAmount: "<< gn->amount<<endl; 
    os << "\t\tFavorite Food: "<< gn->food<<endl; 
    cout <<"\t*********************~~*********************" << endl; 
}

Node* BST::CreateNode(Animal *al){
	Node * p= new Node; 
    Animal *al1 = new Animal(al);
	p->data = al1;
	p->left = NULL;
	p->right = NULL; 
	return p; 
} 

//Duyet Phan Tu Ben Trai Root > Left va Right > Root
int BST::LeftOf(Animal *al,Node* root){    
    return (al->getID() < root->data->getID());
}

int BST::RightOf(Animal *al,Node* root){    
    return (al->getID() > root->data->getID());
}

//Chen Phan Tu
Node* BST::Insert(Node* &root,Animal *al1){
    if ( root == NULL){
        Node* node = CreateNode(al1);
        size++;
        return node;
    }
    else{
    	if(LeftOf(al1,root))
    		root->left = Insert(root->left,al1);
    	else if(RightOf(al1,root))
    		root->right = Insert(root->right,al1);
	}
        // size ++;
		return root;
}

//Tim Kiem Phan Tu
Node* BST::SearchName(Node *root,Animal *al1){
    if (root == NULL){
        return NULL;
    }
    
    if(root->data->getID() == al1->getID()){
        return root;
    }
    else if(LeftOf(al1,root))
        return SearchName(root->left,al1);
    else if(RightOf(al1,root))
        return SearchName(root->right,al1);
}

//Duyet Phan Tu Theo Left -> Right -> Node
void BST::PostOrder(Node* root){
	if(root != NULL){
		PostOrder(root->left);
		PostOrder(root->right);
		cout << root->data;
	}
}

//Tra Ve Phan Tu Bu Nhat Ben Trai
Animal* BST::LeftMostAnimal(Node* root){
    while(root->left != NULL)
        root = root->left;
    return root->data;
}

//Xoa Phan Tu
Node* BST::Delete(Node* &root, Animal *al1){
    if (root == NULL)
        return root;
    if (LeftOf(al1,root))
        return root->left = Delete(root->left,al1);
    else if (RightOf(al1,root))
        return root->right = Delete(root->right,al1);
    else
    {
        if (root->left == NULL)
        {
            Node* newRoot = root->right;
            delete root;
            return newRoot;
        }
        if (root->right == NULL)
        {
            Node* newRoot = root->left;
            delete root;
            return newRoot;
        }
        root->data = LeftMostAnimal(root->right);
        root->right = Delete(root->right,root->data);
    }
    // size --;
    return root;
} 

istream& operator >> (istream& is,Animal *al){
    al->toStream(is);
    return is;
}

ostream& operator << (ostream& os,Animal *al){
    os << "\t*********************--*********************\n";
    os << "\t\t\tName: " << al->name << endl;
    os << "\t\tHeight: " << al->height << " kg" << "|| Weight: " << al->weight << " cm" <<endl;
    os << "\t\tID: " << al->id<<endl;
    return os;
}

void Animal::toStream(istream& is){
    fflush(stdin);
    cout <<"\n\t\tName Of The Animal: ";
    getline  (is,name);
    cout <<"\t\tHeight: ";
    is >> height;
    cout <<"\t\tWeight: ";
    is >> weight;
    do{
        cout <<"\t\tID: ";
        is >> id;
        if(id < 1 || id > 299)
            cout << "\t\tNegative !"<<endl;
    }   while(id < 1 || id > 299);  
}

Animal Animal::operator = (Animal* al){
	this->name = al->name;
	this->height = al->height;
	this->weight = al->weight;
	this->id = al->id; 
}

//Khoi Tao Ham
Animal::Animal(){
    this->name = "None";
	this->height = 0;
	this->weight = 0;
	this->id = 0;
}

Animal::Animal(string name,float height, float weight, int id){
    this->name = name;
    this->height = height;
    this->weight = weight;
    this->id =  0; 
}

Animal::Animal(Animal* al){
    this->name = al->name;
	this->height = al->height;
    this->weight = al->weight;
    this->id =  al->id; 
}

Animal::~Animal(){
}

//Lay Du Lieu
string Animal::getName(){
	return name; 
}

int Animal::getID(){
	return id;
}

//Produce Key 
void Animal::setName(string name){
    this->name = name;
}

void Animal::setID(int &id){
    this->id = id;
}

void Microorganism::toStream(istream& is){
    Animal::toStream(is) ;
    fflush(stdin);
    cout <<"\t\tFavorite Food: ";
    is >> food;
    cout <<"\t\tAmount: ";
    is >> amount;  
}

ostream& operator << (ostream& os,Microo *mi){
    Animal *al = static_cast <Animal *> (mi);
    os << al;
    os << "\t\tAmount: "<< mi->amount<<endl; 
    os << "\t\tFavorite Food: "<< mi->food<<endl; 
    cout <<"\t*********************~~*********************" << endl; 
}

void BST::InOrder(Node* root){
	if(root != NULL){
		InOrder(root->left);
		cout << root->data;
		InOrder(root->right);
	}
}

void MENU(){
	Animal* al;
    long allSize[2] = {0};
    char k, c;
	do{
		cout << "\t-------------------------------------------------------------------" << endl;
        cout << "\t|                             +|MENU|+                            |" << endl;
        cout << "\t-------------------------------------------------------------------" <<endl;
    	cout << "\t+       MENU BUILDING PROGRAM WORKING WITH CLASS OF ANIMALS       +\n" << endl;
        cout << "\t+                CHOOSE THE FOLLOWING FUNCTIONS:                  +\n" << endl;
        cout << "\t+            1. TO WORK WITH THE CLASS OF GRAMINIVORE             +\n" << endl;
        cout << "\t+            2. TO WORK WITH THE CLASS OF HYPERCARNIVORE          +\n" << endl;
        cout << "\t+            3. TO WORK WITH THE CLASS OF MICROORGANISM           +\n" << endl;
        cout << "\t+            4. TO WORK WITH THE LINKED LIST                      +\n" << endl;
        cout << "\t+            5. TO QUANTITY STATISTICS                            +\n" << endl;
        cout << "\t+                          -ESC . EXIT-                           +\n" << endl;
        cout << "\t-------------------------------------------------------------------" <<endl;
        int panel;
        cout << "\n\n\t Please Choose A Function:  ";
        cin >> panel;
        switch (panel){
            case 1: {
                BST tree;
                tree.root = NULL;
                tree.size = 0;
                cout << "\n\t Welcome to the Graminivore class" << endl;
                cout << "\n\t Enter Number Of Animal: ";
                int n;
                cin >> n;
                for(int i = 0; i < n; i++){
                    al = new Grami;
                    cin >> al;
                    tree.root = tree.Insert(tree.root, al);
                }
                cout << "\n\t Now choose your work \n";
                int work2;
                char k, c;
                do{
                	cout << "\t\t          | THE GRAMINIVORE MENU |        " << endl;
                    cout << "\t\t-------------------------------------------" << endl;
                    cout << "\t\t+  1.  PRINT GRAMINIVORE WITH TREE LIST   +\n" << endl;
                    cout << "\t\t+  2.            SORTED LIST  	  	  +\n" << endl;
                    cout << "\t\t+  3.          ADD MORE ANIMAL		  +\n" << endl;
                    cout << "\t\t+  4.           DELETE ANIMAL 		  +\n" << endl;
                    cout << "\t\t+  5.         SEARCH FOR ANIMAL		  +\n" << endl;
                    cout << "\t\t+ 	         -ESC. EXIT-	 	  +\n" << endl;
                    cout << "\t\t-------------------------------------------" << endl;
                    cout << "\n\n\t Please choose a function:  ";
                    cin >> work2;
                    switch(work2){
                        case 1: {
                            tree.PostOrder(tree.root);
                        }break;
                        case 2: {
                            cout << "\t Here Is Sorted Tree \n" << endl;
                            tree.InOrder(tree.root);
                        }break;
                        case 3: {
                            Animal *all = new Grami;
                            cout << "\t Enter Another Animal \n";
                            cin >> all;
                            tree.Insert(tree.root, all);
                        }break;
                        case 4: {
                            cout << "\t Delete Animal - Enter Animal ID:  ";
                            int id;
                            Animal *temp1 = new Grami;
                            cin >> id;
                            temp1->setID(id);
                            tree.Delete(tree.root, temp1);
                            cout <<"\t\tDeleted Success !"<<endl;
                        }break;
                        case 5: {
                            cout << "\t Search Animal By ID: ";
                            Animal *temp2 = new Grami;
                            int id;
                            cin >> id;
                            temp2->setID(id);
                            cout << tree.SearchName(tree.root, temp2)->data;
                        }break;
                    }
                        cout << "\n\tDo You Want To Exit ?(esc)"<<endl;
                        k = c;
                        c = getch();
                        
                }while(c!=27);
                allSize[0] = tree.size;
            }break;
            case 2: {
                BST tree;
                tree.root = NULL;
                tree.size = 0;
                cout << "\n\t Welcome To The Hypercarnivore Class !" << endl;
                cout << "\n\t Enter Number Of Animal: ";
                int n;
                cin >> n;
                for(int i = 0; i < n; i++){
                    al = new Hyper;
                    cin >> al;
                    tree.root = tree.Insert(tree.root, al);
                }
                cout << "\n\t Now Choose Your Work \n";
                int work3;
                char k,c;
                do{
                    cout << "\t\t          | THE HYPERCARNIVORE MENU |        " << endl;
                    cout << "\t\t----------------------------------------------" << endl;
                    cout << "\t\t+  1.  PRINT HYPERCARNIVORE WITH TREE LIST   +\n" << endl;
                    cout << "\t\t+  2.            SORTED LIST  	  	     +\n" << endl;
                    cout << "\t\t+  3.          ADD MORE ANIMAL		     +\n" << endl;
                    cout << "\t\t+  4.           DELETE ANIMAL 		     +\n" << endl;
                    cout << "\t\t+  5.         SEARCH FOR ANIMAL		     +\n" << endl;
                    cout << "\t\t+ 	         -ESC. EXIT-	 	     +\n" << endl;
                    cout << "\t\t----------------------------------------------" << endl;
                    cout << "\n\n\t Please Choose A Function:  ";
					cin >> work3; 
                    switch(work3){
                        case 1: {
                            tree.PostOrder(tree.root);
                        }break;
                        case 2: {
                            cout << "\t Here Is Sorted Tree \n" << endl;
                            tree.InOrder(tree.root);
                        }break;
                        case 3: {
                            Animal *all = new Hyper;
                            cout << "\t\t Enter Another Animal \n";
                            cin >> all;
                            tree.Insert(tree.root, all);
                        }break;
                        case 4: {
                            cout << "\t Delete Animal - Enter Animal ID:  ";
                            int id;
                            Animal *temp1 = new Hyper;
                            cin >> id;
                            temp1->setID(id);
                            tree.Delete(tree.root, temp1);
                            cout <<"\t\tDeleted Success !"<<endl;
                        }break;
                        case 5: {
                            cout << "\t Search Animal By ID: ";
                            Animal *temp2 = new Hyper;
                            int id;
                            cin >> id;
                            temp2->setID(id);
                            cout << tree.SearchName(tree.root, temp2)->data;
                        }break;
                    }
                        cout << "\n\tDo You Want To Exit ?(esc)";
                        c = getch();
                        
                }while(c!=27); 
                allSize[1] = tree.size;
            }break;
            case 3: {
                BST tree;
                tree.root = NULL;
                tree.size = 0;
                cout << "\n\t Welcome To The Microorganism Class !" << endl;
                cout << "\n\t Enter Number Of Animal: ";
                int n;
                cin >> n;
                for(int i = 0; i < n; i++){
                    al = new Microo;
                    cin >> al;
                    tree.root = tree.Insert(tree.root, al);
                }
                cout << "\n\t Now Choose Your Work \n";
                int work4; 
                char k, c;
                do{
                    cout << "\t\t          | THE MICROORGANISM MENU |        " << endl;
                    cout << "\t\t---------------------------------------------" << endl;
                    cout << "\t\t+  1.  PRINT MICROORGANISM WITH TREE LIST   +\n" << endl;
                    cout << "\t\t+  2.            SORTED LIST  	  	    +\n" << endl;
                    cout << "\t\t+  3.          ADD MORE ANIMAL		    +\n" << endl;
                    cout << "\t\t+  4.           DELETE ANIMAL 		    +\n" << endl;
                    cout << "\t\t+  5.         SEARCH FOR ANIMAL		    +\n" << endl;
                    cout << "\t\t+ 	         -ESC. EXIT-	 	    +\n" << endl;
                    cout << "\t\t---------------------------------------------" << endl;
                    cout << "\n\n\t Please Choose A Function:  \n";
					cin >> work4;
                    switch(work4){
                        case 1: {
                            tree.PostOrder(tree.root);
                        }break;
                        case 2: {
                            cout << "\t\t Here Is Sorted Tree \n" << endl;
                            tree.InOrder(tree.root);
                        }break;
                        case 3: {
                            Animal *all = new Microo;
                            cout << "\t Enter Another Animal \n";
                            cin >> all;
                            tree.Insert(tree.root, all);
                        }break;
                        case 4: {
                            cout << "\t Delete Animal - Enter Animal ID:  ";
                            int id;
                            Animal *temp1 = new Microo;
                            cin >> id;
                            temp1->setID(id);
                            tree.root = tree.Delete(tree.root, temp1);
                            cout <<"\t\tDeleted Success !"<<endl;
                        }break;
                        case 5: {
                            cout << "\t Search  Animal By ID: ";
                            Animal *temp2 = new Microo;
                            int id;
                            cin >> id;
                            temp2->setID(id);
                            cout << tree.SearchName(tree.root, temp2)->data;
                        }break;
                    }
                    cout << "\n\tDo You Want To Exit ?(esc)"<<endl;
                    k = c;
                    c = getch();
                        
                }while(c!=27);
                allSize[2] = tree.size;
            }break;
            case 4: {
                Animal *al;
                SList list;
                cout << "\n\t\t\t Welcome To The Linked List ! \n " << endl;
                cout << "\t Now Choose Your Work \n";
                int work5;
                char k, c;
                do{ 
                	cout << "\n\t\t                | THE LINKED LIST MENU |              " << endl;
                    cout << "\t\t------------------------------------------------------" << endl;
                    cout << "\t\t+  1. INSERT THE ANIMAL CLASS WITH THE LINKED LIST  +\n" << endl;
                    cout << "\t\t+  2.   PRINT THE ANIMAL CLASS WITH LINKED LIST     +\n" << endl;
                    cout << "\t\t+  3.                 SORTED LIST		    +\n" << endl;
                    cout << "\t\t+  4.                DELETE ANIMAL 		    +\n" << endl;
                    cout << "\t\t+  5.              SEARCH FOR ANIMAL		    +\n" << endl;
                    cout << "\t\t+                     -ESC . EXIT-	 	    +" << endl;
                    cout << "\t\t------------------------------------------------------" << endl;
                    cout << "\n\n\t Please choose a function:  ";
                    cin >> work5; 
                    switch(work5){
                        case 1: {
                            Animal *al1 = new Grami;
                            cout << "\t Enter: \n" << endl;
                            cin >> al1;
                            list.addLast(al1);
                            
                            al1 = new Hyper; 
                            cout << "\t Enter: \n" << endl;
                            cin >> al1;
                            list.addLast(al1);
                            
                            al1 = new Microo; 
                            cout << "\t Enter: \n" << endl;
                            cin >> al1;
                            list.addLast(al1);
                            
                        }break;
                        case 2: {
                        	list.traverse();
                        }break;
                        case 3: {
                            list.sort();
                            list.traverse();
                        }break;
                        case 4: {
                        	list.removeName();
                            cout << "\n\tDeleted Success!"<<endl;
                        }break;
                        case 5: {
                            Animal *al1 = new Animal;
                            string name;
                            fflush(stdin);
                            getline(cin,name);
                            al1->setName(name); 
                            cout << list.searchName(al1)->data;
                             
                        }break;
                    }
                    cout << "\n\t Do you want to exit ?(esc) \n";
                    k = c;
                    c = getch();
                }while(c!=27);
                
            }break;
            case 5: {
                cout << "\n\t\t Welcome To Quantity Statistics ! \n " << endl;
                cout << "\t There is: "<<allSize[0]<<" Graminivore \n"<<endl;
				cout << "\t There is: "<<allSize[1]<<" Hypecarrivore \n"<<endl;   
				cout << "\t There is: "<<allSize[2]<<" Microorganism \n"<<endl;
				cout << "\t Total:   "<< allSize[0] + allSize[1] + allSize[2] ;   	
            }break;
            default : {
                cout << "\n\t You have chosen to Exit the program \n" << endl;
            }break;
        }
        cout << "\n\t Do you want to exit ?(esc)"<<endl;
        k = c;
        c = getch();
        delete al;
	}while(c!=27);
}
int main(){
    MENU();
}