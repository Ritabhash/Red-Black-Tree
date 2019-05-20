#include<iostream>

using namespace std;

template<typename T>
class RBtree
{
   public:
      struct node
      {
            T key;
            node *parent;
            char color;
            node *left;
            node *right;
      };

      node *root;
      node *q;

      RBtree() //ctor
      {
              q = NULL;
              root = NULL;
      }

      void insert(T val);
      void insertfix(node *);
      void leftrotate(node *);
      void rightrotate(node *);
      void del(T val);
      void delfix(node *);
      void disp();
      void display( node *);
      void search(T val);
};

template <class T>
void RBtree<T>::insert(T val)
{
     node *p,*q;

     node *t = new node; //t is node to be inserted

     t->key = val;	//initializing with val
     t->left = NULL;
     t->right = NULL;
     t->color = 'r';	//because we initially start off with a red node

     p = root;
     q = NULL;

     if(root == NULL)
     {
           root = t;
           t->parent = NULL;
     }
     else
     {
         while(p != NULL)
         {
              q = p;
              if(p->key< t->key)
                  p = p->right;
              else
                  p = p->left;
         }
         t->parent = q;
         if(q->key < t->key)
              q->right = t;
         else
              q->left = t;
     }
     //disp();
     insertfix(t);	//insertfix will handle the rotations
}

/* Performs necessary rotations on tree after inserting node t */
template <class T>
void RBtree<T>::insertfix(node *t)
{
	/*cout << "<--------------------->";
	cout << "\n[BEFORE ROTATIONS]:";
	disp();*/
	cout<<"\n\n<in insertfix>>";
     node *u;
     if(root == t)
     {
         t->color = 'b';
         //return;
     }
     while((t->parent != NULL) && (t->parent->color == 'r'))
     {
     		cout<<"\n\n in insertfix() while";
     	   int lr = 0; // flag to determine whether to print LR or R rotation
     	   int rl = 0; // flag to determine whether to print L or RL

           node *g = t->parent->parent;
           if(g != NULL){
           if(g->left == t->parent)
           {
                        if(g->right != NULL)
                        {
                              u = g->right;
                              if(u->color == 'r')
                              {
                                   t->parent->color = 'b';
                                   u->color = 'b';
                                   g->color = 'r';
                                   t = g;
                              }
                        }
                        else
                        {

                            if(t->parent->right == t)
                            {
                                 t = t->parent;
                                 leftrotate(t);
                                 lr = 1;
                            }
                            t->parent->color = 'b';
                            g->color = 'r';
                            rightrotate(g);
                        }
                        if(lr == 1){cout << "\n\n[LR ROTATION.]";}
                        else{cout<<"\n\n[R ROTATION.]";}
           }
           else
           {

                        if(g->left != NULL)
                        {
                             u = g->left;
                             if(u->color == 'r')
                             {
                                  t->parent->color = 'b';
                                  u->color = 'b';
                                  g->color = 'r';
                                  t = g;
                             }else{
                                 t->parent->color = 'b';
                                 g->color = 'r';
                                 leftrotate(g);
                             }
                             //cout << "\n\n[LEFT ROTATION.]";
                        }
                        else
                        {

                            if(t->parent->left == t)
                            {
                                   t = t->parent;
                                   rightrotate(t);
                                   rl = 1;
                            }
                            t->parent->color = 'b';
                            g->color = 'r';
                            leftrotate(g);
                        }
                       	if(rl == 1){cout << "\n\n[RL ROTATION.]";}
           				else{cout<<"\n\n[L ROTATION.]";}
           }
           }
           root->color = 'b';
     }
    /*cout << "<--------------------->";
	cout << "[AFTER ROTATIONS]:";

     disp();*/

}

/* Accept node (by key) from user in-function; search for and consequently delete key */
template <class T>
void RBtree<T>::del(T val)
{
     if(root == NULL)
     {
           cout << "\nEmpty Tree." ;
           return ;
     }


     node *p;
     p = root;
     node *y = NULL;
     node *q = NULL;

     int found = 0;

     while(p != NULL && found == 0)
     {
           if(p->key == val)
               found= 1;
           if(found == 0)
           {
                 if(p->key < val){p = p->right;}
                 else
                    p = p->left;
           }
     }
     if(found == 0)
     {
            cout << "\n[Element Not Found].";
            return ;
     }
     else
     {
         cout << "\n[Deleted Element]: "<<p->key;

         cout<<"\n[Color]: "; if(p->color=='b'){cout<<"Black\n";}
    	 else{cout<<"Red\n";}

         if(p-> parent != NULL)
               cout << "\n[Parent]: "<<p->parent->key;
         else
               cout << "\n[There is no parent of the node]. "; if(p->right!=NULL)
               cout << "\n[Right Child]: "<<p->right->key;
         else
               cout << "\n[There is no right child of the node]. "; if(p->left!=NULL)
               cout << "\n[Left Child]: "<<p->left->key;
         else
               cout << "\n[There is no left child of the node].  ";
         cout << "\n[Node Deleted].";

         if((p->left == NULL) || (p->right == NULL))
              y = p;
         else {
                node *y1 = NULL;
                if(p->left != NULL)
                {
                    y1 = p->left;
                    while(y1->right != NULL)
                    y1 = y1->right;
                }
                else
                {
                    y1 = p->right;
                    while(y1->left != NULL)
                    y1 = y1->left;
                }
                y = y1;
         }
         if(y->left != NULL)
              q = y->left;
         else
         {
              if(y->right != NULL)
                   q = y->right;
              else
                   q = NULL;
         }
         if(q != NULL)
              q->parent = y->parent;
         if(y->parent == NULL)
              root = q;
         else
         {
             if(y == y->parent->left)
                y->parent->left = q;
             else
                y->parent->right = q;
         }
         if(y != p)
         {
             p->color = y->color;
             p->key = y->key;
         }
         if(y->color == 'b' and q != NULL){
         	//disp();
             delfix(q);}
     }
}

/* Performs rotations needed after deleting a node */
template <class T>
void RBtree<T>::delfix(node *p)
{
	/*cout << "<--------------------->";
	cout << "\n[BEFORE ROTATIONS]:";
	disp();*/


    node *s;
    while((p!=root) && (p->color=='b'))
    {
    	  int lr = 0; // flag to check whether to print
    	  int rl = 0; // flag to check whether to print

          if(p->parent->left == p)
          {
                  s = p->parent->right;
                  if(s->color == 'r')
                  {
                         s->color = 'b';
                         p->parent->color = 'r';
                         leftrotate(p->parent);
                         s = p->parent->right;
                         //cout << "\n\n[LEFT ROTATION.]";
                  }
                  if(s->right != NULL && s->left != NULL){
                  if(s->right->color == 'b'&& s->left->color == 'b')
                  {
                         s->color = 'r';
                         p = p->parent;

                  }
                  else
                  {
                      if(s->right->color == 'b')
                      {
                             s->left->color == 'b';
                             s->color = 'r';
                             rightrotate(s);
                             s = p->parent->right;
                             rl = 1;
                      }
                      s->color = p->parent->color;
                      p->parent->color = 'b';
                      s->right->color = 'b';
                      leftrotate(p->parent);
                      if(rl == 1){cout << "\n\n[RL ROTATION.]";}
                  	  else{cout << "\n\n[LEFT ROTATION.]";}
                  }}
          }
          else
          {
                  s = p->parent->left;
                  if(s->color == 'r')
                  {
                        s->color = 'b';
                        p->parent->color = 'r';
                        rightrotate(p->parent);
                        s = p->parent->left;
                        cout << "\n\n[RIGHT ROTATION.]";
                  }
                  if((s->right != NULL) && (s->left != NULL)){
                  if(s->left->color == 'b'&& s->right->color == 'b')
                  {
                        s->color = 'r';
                        p = p->parent;
                  }
                  else
                  {
                        if(s->left->color == 'b')
                        {
                              s->right->color = 'b';
                              s->color = 'r';
                              leftrotate(s);
                              s = p->parent->left;
                              lr = 1;
                        }
                        s->color = p->parent->color;
                        p->parent->color = 'b';
                        s->left->color = 'b';
                        rightrotate(p->parent);
                        if(lr == 1){cout << "\n\n[LR ROTATION.]";}
                        else{cout << "\n\n[RIGHT ROTATION.]";}
                  }}
          }
       p->color = 'b';
       root->color = 'b';
       p = root;
    }
    /*cout << "<--------------------->";
	cout << "[AFTER ROTATIONS]:";
	disp();*/

}

template <class T>
void RBtree<T>::leftrotate(node *p)
{
     if(p->right == NULL)
           return ;
     else
     {
           node *y = p->right;
           if(y->left != NULL)
           {
                  p->right = y->left;
                  y->left->parent = p;
           }
           else
                  p->right = NULL;
           if(p->parent != NULL)
                y->parent = p->parent;
           if(p->parent == NULL)
                root = y;
           else
           {
               if(p == p->parent->left)
                       p->parent->left = y;
               else
                       p->parent->right = y;
           }
           y->parent = NULL;
           y->left = p;
           p->parent = y;
     }
}

template <class T>
void RBtree<T>::rightrotate(node *p)
{
     if(p->left == NULL)
          return ;
     else
     {
         node *y = p->left;
         if(y->right != NULL)
         {
                  p->left = y->right;
                  y->right->parent = p;
         }
         else
                 p->left = NULL;
         if(p->parent != NULL)
                 y->parent = p->parent;
         if(p->parent == NULL)
               root = y;
         else
         {
             if(p == p->parent->left)
                   p->parent->left = y;
             else
                   p->parent->right = y;
         }
         y->parent = NULL;
         y->right = p;
         p->parent = y;
     }
}

/* Wrapper for display function */
template <class T>
void RBtree<T>::disp()
{
     display(root);
}

/* Display val, Parent, left-child, and right-child of node p */
template <class T>
void RBtree<T>::display(node *p)
{
     if(root == NULL)
     {
          cout << "\n<<<<<<<<<[Empty Tree].>>>>>>>>>>>>>";
          return ;
     }
     if(p != NULL)
     {			cout << "\n\n\n";
     			cout << "<---------------------------->";
                cout << "\n\t [NODE]: ";
                cout << "\n [KEY]: "<<p->key;

                cout<<"\n [Color]: "; if(p->color=='b'){cout<<"Black";}
    			else{cout<<"Red";}

                if(p->parent != NULL)
                       cout << "\n [Parent]: "<<p->parent->key;
                else
                       cout << "\n [There is no parent of the node]. "; if(p->right!=NULL)
                       cout << "\n [Right Child]: "<<p->right->key;
                else
                       cout << "\n [There is no right child of the node]. "; if(p->left!=NULL)
                       cout << "\n [Left Child]: "<<p->left->key;
                else
                       cout << "\n [There is no left child of the node].  ";
                cout << endl;
                if(p->left)
    			{
                	cout << "\n\n[Left]:\n"; display(p->left);
    			}

    			if(p->right)
    			{
     				cout << "\n\n[Right]:\n"; display(p->right);
    			}

     }
}

/* Search for node with a value 'val' in tree */
template<class T>
void RBtree<T>::search(T val)
{
     if(root == NULL)
     {
           cout << "\n<<<<<<<<<<<<<<Empty Tree>>>>>>>>>>>>\n" ;
           return;
     }

     node *p = root;
     int found = 0;
     while(p != NULL && found == 0)
     {
            if(p->key == val)
                found = 1;
            if(found == 0)
            {
                 if(p->key < val){p = p->right;}
                 else
                      p = p->left;
            }
     }
     if(found == 0)
          cout << "\n<----------  [ELEMENT NOT FOUND]. ----------->";
     else
     {
     			cout << "<---------------------->";
     			cout << "\n\n\n";
                cout << "\n\t<------------- [FOUND NODE]: -------------->";
                cout << "\n Key: "<< p->key;
                cout<<"\n Key: "<<p->key;
                cout<<"\n [Color]: "; if(p->color=='b'){cout<<"Black";}
                else {cout<<"Red";}
                if(p->parent != NULL)
                       cout << "\n [Parent]: "<< p->parent->key;
                else
                       cout<< "\n [There is no parent of the node]. ";
                if(p->right != NULL)
                       cout<< "\n [Right Child]: "<< p->right->key;
                else
                       cout << "\n [There is no right child of the node]. ";
                if(p->left != NULL)
                       cout << "\n [Left Child]: " << p->left->key;
                else
                       cout << "\n [There is no left child of the node].  ";
                cout << endl;

     }
}
int main()
{
    int ch,y = 0;
    string s;
    RBtree<string> obj;

    do
    {
    			cout << "------------------------------->";
                cout << "\n\t RED BLACK TREE " ;
                cout << "\n 1. Insert in the tree ";
                cout << "\n 2. Delete a node from the tree";
                cout << "\n 3. Search for an element in the tree";
                cout << "\n 4. Display the tree ";
                cout << "\n 5. Exit " ;
                cout << "\nEnter Your Choice: "; cin >> ch;
                switch(ch)
                {
                          case 1 :
                                   cout << "\nEnter key of the node to be inserted: "; cin >> s;
                                   obj.insert(s);
                                   cout << "\nNode Inserted.\n";
                                   break;
                          case 2 : cout << "\nEnter the key of the node to be deleted: "; cin >> s;
                                   obj.del(s);
                                   break;
                          case 3 : cout << "\n Enter key of the node to be searched: "; cin >> s;
                                   obj.search(s);
                                   break;
                          case 4 : obj.disp();
                                   break;
                          case 5 : y=1;
                                   break;
                          default : cout << "\nEnter a Valid Choice.";
                }
                cout << "\n\n\n\n\n\n\n";

    }while(y != 1);
    return 1;
}
