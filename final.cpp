#include<iostream>
#include<math.h>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<fstream>
#define MAX 99999
using namespace std;

const int k = 2; //2 dimensional point

struct Node
{
	int point[k]; // To store k dimensional point
	char place;
	Node *left, *right;
};

struct Node *root = NULL;

//for file
class data
    {
        public:
        int point[k];
        char place;
    }d;


//create a new node
struct Node* newNode(int arr[],char s)
{
	struct Node* temp = new Node;
// assigning coordinates and type of place.
	for (int i=0; i<k; i++)
        {
        temp->point[i] = arr[i];
        temp->place=s;
        }

	temp->left = temp->right = NULL;
	return temp;
}

//inserting a new node
// aligned plane = depth%k
Node *insertRec(Node *root, int point[],char s, unsigned depth)
{
	if (root == NULL)
            return newNode(point,s);
	unsigned cd = depth % k;

	if (point[cd] < (root->point[cd]))
		root->left = insertRec(root->left, point,s, depth + 1);
	else
		root->right = insertRec(root->right, point,s, depth + 1);

	return root;
}

Node* insert(Node *root, int point[],char s)
{
	return insertRec(root, point,s,0);
}

// check if both are the same point
bool arePointsSame(int point1[], int point2[])
        {
                for (int i = 0; i < k; ++i)
                    if (point1[i] != point2[i])
                        return false;

                return true;
        }
//search for a node
bool searchRec(Node* root, int point[], unsigned depth)
        {
                if (root == NULL)
                            return false;
                if (arePointsSame(root->point, point))
                            {   cout<<"Place: "<<root->place<<endl;
                                return true;
                            }
                unsigned cd = depth % k;
                if (point[cd] < root->point[cd])
                            return searchRec(root->left, point, depth + 1);

                return searchRec(root->right, point, depth + 1);
        }

bool search(Node* root, int point[])
        {
            return searchRec(root, point, 0);
        }


//find all node of a type within a range
void find_range(Node*root,int x1,int x2,int y1,int y2,char s, int depth)
{
    if (root == NULL)
    {
                cout<<"No data available"<<endl;
    }
    unsigned cd = depth % k;
    int low,up;
    if(cd==0)
            {    low=x1;
                 up=x2;
            }
    else
    {    low=y1;
         up=y2;
    }
    if(root->point[0]>=x1 && root->point[0]<=x2 && root->point[1]>=y1 && root->point[1]<=y2 && root->place==s )
           {    cout<<"Place: "<<root->place<<endl;
               cout<<"Point  "<<root->point[0]<<" , "<<root->point[1]<<endl;
           }
    if(root->point[cd]>=low && root->point[cd]<=up)
                    {
                         if(root->right!=NULL)
                                find_range(root->right,x1,x2,y1,y2,s, depth + 1);
                         if(root->left!=NULL)
                                find_range(root->left,x1,x2,y1,y2,s, depth + 1);
    }
    else if (root->point[cd]<=low )
                        {if(root->right!=NULL)
                        find_range(root->right,x1,x2,y1,y2,s, depth + 1);}
    else if( root->point[cd]>=up)
                        {if(root->left!=NULL)
                        find_range(root->left,x1,x2,y1,y2,s, depth + 1);}

}

float Euclidean(int* query,Node*p1)
{
        float dis=sqrt((pow(p1->point[0] - query[0],2)+ pow(p1->point[1] - query[1],2) )*0.1);
        return dis;
}

void find_nearest(Node* root,int *query)
{
        if(root==NULL)
            cout<<endl<<"No data available"<<endl;
        if(root->left == NULL && root->right==NULL)
            {   cout<<"Place : "<<root->place<<endl;
                cout<<"Nearest point :"<<root->point[0]<<" , " <<root->point[1];
            }
        else{

                Node* lchild,*rchild,*temp;
                float dleft=MAX, dright=MAX, dtemp=MAX;

                    if(root->left!=NULL)
                    {lchild = root->left;
                     dleft=Euclidean(query,lchild);
                    }
                    if(root->right!=NULL)
                    {rchild = root->right;
                     dright=Euclidean(query,rchild);
                    }
                temp=root;
                dtemp=Euclidean(query,temp);
               // cout<<dtemp<<" "<<dleft<<" "<<dright<<endl;
        if(dleft<dright && dleft<dtemp )
                    find_nearest(root->left,query);
        else if(dright<dleft && dright<dtemp )
                    find_nearest(root->right,query);
        else{
                    cout<<"Place : "<<root->place<<endl;
                    cout<<root->point[0]<<" , " <<root->point[1]<<endl;
                }
        }
}
void input()
{
    ofstream ofs;
    ofs.open("data.dat",ios::app);
    cout<<endl<<"No of inputs: ";
    int num;
    cin>>num;

    for(int i=0;i<num;i++)
    {

        cout<<"DATA "<<i+1<<endl<<"X CORD:";
        cin>>d.point[0];
        cout<<endl<<"Y CORD:";
        cin>>d.point[1];
        cout<<endl<<"TYPE OF PLACE (hospital(h),restaurant(r),shopping(s):";
        cin>>d.place;
        ofs.write((char*)&d,sizeof(d));
    }

    ofs.close();

    ifstream ifs;
	for (int i=0; i<num; i++)
	{

        ifs.open("data.dat",ios::in);

        while(!ifs.eof())
        {
            ifs.read((char*)&d,sizeof(d));
            root = insert(root,d.point,d.place);
        }
	}
	ifs.close();
}

int main()
{


	char c;
	do{
	cout<<endl<<"1.SEARCH A POINT"<<endl<<"2.RANGE QUERY"<<endl<<"3.NEAREST NEIGHBOUR"<<endl<<"4.INPUT DATA POINTS"<<endl;
	int option;
	cin>>option;


    switch(option)
    {
            case 1: int point1[2];
                    cout<<"point to be searched "<<endl;
                    cout<<endl<<"x coordinate ";
                    cin>>point1[0];
                    cout<<endl<<"y coordinate ";
                    cin>>point1[1];
                    search(root, point1)?cout << "Node Found\n" : cout << "Node not Found\n";
                    break;

            case 2: cout<<endl<<"   RANGE QUERY "<<endl;
                    cout<<"Start of x range :x1  ";
                    int x1;
                    cin>>x1;
                    cout<<"End of x range  :x2  ";
                    int x2;
                    cin>>x2;
                    cout<<"Start of y range :y1 ";
                    int y1;
                    cin>>y1;
                    cout<<"End of y range :y2  ";
                    int y2;
                    cin>>y2;
                    cout<<"Type of the place: ";
                    char s;
                    cin>>s;
                    find_range(root,x1,x2,y1,y2,s,0);
                    break;

            case 3: cout<<endl<<"Query point"<<endl;
                    int query[2];
                    cout<<"x coordinate and y coordinate"<<endl;
                    cin>>query[0]>>query[1];
                    find_nearest(root,query);

                    break;
            case 4: input();
                    break;
            default:
                    cout<<endl<<"Enter a valid option"<<endl;
    }
    cout<<endl<<"Continue?(y/n)"<<endl;
    cin>>c;
    system("cls");
    }
    while(c=='y');
 	return 0;
}
