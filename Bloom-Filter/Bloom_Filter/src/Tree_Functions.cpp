#include "Tree.h"

///////////////////
// CONSTRUCTOR   //
///////////////////
Tree::Tree()
{
    root = NULL;       //initialize some variables
    curr_node=NULL;
    head_list=NULL;
    curr_list=NULL;
    total_kids=0;
    curr_depth=0;
    full_tree=false;
    empty_list=false;
}

///////////////////
// CREATE NODES  //
///////////////////
Tree::node* Tree::createnode(const char *word)
{
    total_kids++;           //total kid ++
    node* n=new node;       //create node
    char *  insert_node_word = ( char *)calloc(1,sizeof(word)); //create new word place
    strcpy(insert_node_word,word);      //copy the word
    n->check=false;             //initialize check(if the node is been used)
    n->right_sibling=NULL;  //initialize
    n->father=curr_node;
    n->data_word=insert_node_word;
    n->kids=NULL;
    insert_node_to_helper_list(n); //insert word to helper list
    return n;               //return node
}

/////////////////////////
// SET SIZE OF BLOOM   //
/////////////////////////
void Tree::set_bloom_size(int sizee,int hash_num)
{                                       //set the size of the bloom filter
    filter.bloom_filter_allocation(sizee,hash_num);//call the function
}

////////////////////
// SET TREE DEPTH //
////////////////////
void Tree::set_tree_depth(int depth)
{                   //initialize the depth of the tree
    depth=depth-1;  //- 1 because we already counted the root
    if(depth<0)     //if user insert invalid depth
    {
        depth=1;    //set 1
    }
    total_depth=depth;//set depth
}

///////////////////////
// INITIALIZE TREE   //
///////////////////////
void Tree::initialize_tree(int sizee,int hash_num)
{                   //Initialize the root,to start the tree
    node* n=new node;   //create new node tree
    root=n;             //set the root
    curr_node=root;     //set the helper list(for print and delete later)
    n->data_word=" ";   //insert root data
    n->right_sibling=NULL;//set right sibling to NULL
    n->father=NULL;     //set father
    set_bloom_size(sizee,hash_num);//Initialize the filter
    insert_node_to_helper_list(root);//initialize the helper list(for print and delete later)
}

///////////////////////
// ALLOCATE MEMORY   //
///////////////////////
void Tree::allocate_node_array(node* point)
{
    if(point->number_of_kids>0)
    {           //allocate memory for the number of the kids
        point->kids=(node**)calloc(point->number_of_kids,sizeof(node*));
        int i=0;
        for(i;i<point->number_of_kids;i++)
            point->kids[i]=NULL;
    }
    else        //if node has no kids
    {
        point->kids==NULL;
    }
}

///////////////////
// CONSTRUCTOR   //
///////////////////
const char * Tree::insert_words_Tree(int num_kids,const char **matrix)
{
    int j;
    int i;
    int new_num_kids=0;
    bool check_depth;
    List help_list;
    if(root==NULL)              //Empty tree
    {
        cout<<">>Error,must initialize tree first..."<<endl;
        exit(0);
    }
    if(filter.check_bloom_full()!=true)         //Filter the words through the bloom filter,check if it is full
    {
        for(j=0;j<num_kids;j++)                 //for each word
        {
            if(filter.check_word(matrix[j])==true)//check filter
            {
               help_list.insert_words_list(matrix[j]);//if it is ok add the word to helper list
               new_num_kids++;                          //++ node of list
            }
        }
    }
    else                    //else bloom is full
    {
        empty_list=true;
    }
    num_kids=new_num_kids;
    check_depth=check_tree_depth(); //check if tree is full
    if(check_depth==true)           //not full tree
    {
        curr_node->check=true;      //set the current node checked
        curr_node->number_of_kids=num_kids; //set the numbers of his kids
        allocate_node_array(curr_node);     //allocate his array
        for(i=0;i<num_kids;i++)           //for each kid
        {
            curr_node->kids[i]=createnode(help_list.return_next_word_list());//create a node
            if(i>=1)
            {
                curr_node->kids[i-1]->right_sibling=curr_node->kids[i];  //bond the children together as siblings
            }
        }
        set_tree();                         //set the tree
        if(curr_node->check==true)          //but check if the current is not on a already used node
        {
            while(curr_node->check==true)   //if it is reset
            {
                set_tree();
            }
        }
        return next_word_to_test();         //return next word to check
    }
    else                                //full tree
    {
        if(full_search==false)  //sent last leafs ,to main ,of the tree
        {
            curr_node->check=true;  //check the node
            while(curr_node->check==true)   //set the tree to new unchecked node
            {
                set_tree();
                if(curr_node->check==false) //if it is an unchecked node
                {
                    curr_node->check=true; //check it
                    for(i=0;i<num_kids;i++) //insert the "kids" of the node to list
                    {
                        lista.insert_words_list(help_list.return_next_word_list());
                    }
                    return next_word_to_test(); //return node
                }
                if(curr_node==temp) //to avoid infinite loop
                {
                    full_search=true; //sto the search at the tree completely
                    break;
                }
            }
        }
        else                //use only the list now
        {
            if(full_tree==false) //print message once
            {
                cout<<">>Tree is full,cannot support any more entries...Total entries:["<<total_kids<<"], Total depth:["<<total_depth+1<<"]"<<endl;
                cout<<">>Using list for new entries..."<<endl;
                full_tree=true;
            }
            for(i=0;i<num_kids;i++)         //set each filtered word to the list
            {
                lista.insert_words_list(help_list.return_next_word_list());
            }
            empty_list=lista.check_empty_list(); //check if is empty
            if(empty_list==true)                    //if is empty return root and end the game
            {
                return root->data_word;
            }
            else                                    //else return the next word to main
            {
                return lista.return_next_word_list();
            }
        }
    }
}

///////////////////
// SET THE TREE  //
///////////////////
void Tree::set_tree()   //set the curr to the node that is about to send to main
{
    if(curr_node==root)         //case first,curr is the root
    {
        curr_node=root->kids[0];
    }
    else if(curr_node->right_sibling!=NULL)//case that node has simpling
    {
        curr_node=curr_node->right_sibling;//go to the last left kid of the simpling
        while(curr_node->kids!=NULL)
        {
            curr_node=curr_node->kids[0]; //last left kid
        }
    }
    else
    {                               //case that we are at the last node without sibling
       while(curr_node->father!=NULL)//go up until arrive root
       {
           curr_node=curr_node->father;     //go to the father
           if(curr_node->right_sibling!=NULL)   //check for simpling
           {
                curr_node=curr_node->right_sibling;//if it has simpling
                while(curr_node->kids!=NULL)    //go to the last left kid
                {
                    curr_node=curr_node->kids[0];
                }
                break;
           }
           if(curr_node->father==NULL)//if we are to root
           {
               curr_depth++;        //we will have ++depth
               curr_node=root;
               while(curr_node->kids!=NULL) //go to the last left kid of the tree
                {
                    curr_node=curr_node->kids[0];
                }
                temp=curr_node;     //save the last kid address
                break;
           }
       }
    }
}

///////////////////
// PRINTER TREE  //
///////////////////
void Tree::print_tree()
{
    int i=1;
    int counter=0;
    curr_list=head_list->next;
    cout<<">>Printing the word Tree...\n";
    if(curr_list==NULL)
    {
        cout<<">>No tree to delete..Create Tree.."<<endl;
    }
    else
    {
        cout<<">>Root :[ ] \n";
         while(curr_list!=NULL)
        {
            cout<<">>--------->kids["<<curr_list->data->number_of_kids<<"]"<<endl;
            for(counter=0;counter<curr_list->data->number_of_kids;counter++)
            {
                cout<<">>--------->("<<counter+1<<"):"<<curr_list->data->kids[counter]->data_word<<endl;
            }
            curr_list=curr_list->next;
            if(curr_list==NULL)
            {
                break;
            }
            cout<<">>node>("<<i<<") :"<<curr_list->data->data_word<<endl;
            i++;
        }
    }
}

/////////////////////////
// NEXT WORD TO TEST   //
/////////////////////////
const char * Tree::next_word_to_test()
{               //Returns the word that point the curr_node
    return curr_node->data_word;
}

////////////////////////
// CHECK TREE DEPTH   //
////////////////////////
bool Tree::check_tree_depth()
{      //Check if the tree has arrived to the total depth
    if(curr_depth>total_depth)  //if yes
    {
        return false;
    }
    else                        //if no
    {
        return true;
    }
}

///////////////////////////
// TOTAL NODES IN TREE   //
///////////////////////////
int Tree::Tree_total_words()
{           //Returns the total nodes of the tree
    return total_kids;
}

///////////////////////////
// TOTAL NODES IN LIST   //
///////////////////////////
int Tree::total_kids_in_list()
{           //Returns the total nodes of the LIST
    return lista.return_list_kid();
}


//////////////////////////////
// HOW BLOMM FILTER IS FULL //
//////////////////////////////
float Tree::full_percentage_filter_tree()
{               //Returns the percentage of the bloom filter that is full
    return filter.full_percentage_bloom();
}

/////////////////////////
// CHECK IF GAME ENDS   //
//////////////////////////
bool Tree::end_of_game()
{       //check if list is empty
    if(empty_list==true)//if it is empty ,no more words to check
    {
        return false;
    }
    else           //else if not empty
    {
        return true;
    }
}

///////////////////
// DELETE ALL    //
///////////////////
void Tree::delete_tree()
{   //delete all structures
    print_tree();           //print tree
    filter.delete_bloom(); //delete filter
    lista.delete_list();   //delete list
    delete_nodes();        //delete nodes
    cout<<">>Tree deleted..."<<endl;
}


///////////////////
// HELPER LIST   //
///////////////////
//-------LIST USED FOR HELP,FOR DELETION AND PRINTING TREE--------//
void Tree::insert_node_to_helper_list(node *node)                 //
{                                                                 //
    list_node *n = new list_node;     //allocate memory           //
    n->data=node;                                                 //
    n->fath=node->father;                                         //
    n->next = NULL;               //insert data to node           //
    if(head_list!=NULL)        //if there are  nodes in list      //
    {                                                             //
        curr_list = head_list;                                    //
        while(curr_list->next!=NULL)   //find the last node       //
        {                                                         //
            curr_list = curr_list->next;                          //
        }                                                         //
        curr_list->next = n;                                      //
    }                                                             //
    else                    //if there are no nodes in list       //
    {                                                             //
        head_list = n;          //head is the first node          //
    }                                                             //
}                                                                 //
void Tree::delete_nodes()                                         //
{                       //DELETE all nodes                        //
    list_node *temp;                                              //
    if(head_list!=NULL)                                           //
    {                                                             //
        curr_list=head_list;                                      //
        while(curr_list!=NULL)                                    //
        {                                                         //
            temp=curr_list; //set temp for deletion               //
            curr_list=curr_list->next; //next node                //
            free(temp->data->kids); //free kid array              //
            delete temp->data; //delete data                      //
            delete temp; //delete temp                            //
        }                                                         //
        delete root; //delete root                                //
    }                                                             //
}                                                                 //
////////////////////////////////////////////////////////////////////
