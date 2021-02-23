

#include <iostream>
#include <time.h>
struct stored_data
{
	int int_data;
	char char_data;

	void generate_data()
	{
		const char letters[] = "abcdefghijklmnopqrstuvwxyz";
		this->int_data = rand() % 10000;
		this->char_data = letters[rand() % (sizeof(letters) - 1)];

	}
	friend std::ostream& operator<<(std::ostream& os, const stored_data& sd)
	{
		os << sd.int_data << " " << sd.char_data << "\n";
		return os;
	}
	friend bool operator==(const stored_data &st, const stored_data&sd)
	{
		if (st.int_data == sd.int_data &&st.char_data == sd.char_data)
			return true;
		else
			return false;
	}
	friend bool operator !=(const stored_data& st, const stored_data&sd)
	{
		if (st.int_data == sd.int_data &&st.char_data == sd.char_data)
			return false;
		else
			return true;
	}
	friend bool operator >(const stored_data&  so1, const stored_data& so2)
	{
		int diff = so1.int_data - so2.int_data;
		if (diff > 0)
			return true;
		else
			return false;
	}
};
enum color { BLACK, RED };
template<typename T>
struct node
{
	T field;
	node *left;
	node *right;
	node *parent;
	enum color color_node;
	int index_node;
	node(T field, size_t size)
	{

		this->field = field;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
		this->index_node = size;
		this->color_node = RED;
	}
	node() 
	{
		this->color_node = BLACK;
		this->field = T();
		this->parent = NULL;
		this->index_node = 0;
		this->left = NULL;
		this->right = NULL;
		
	}
	void set_NIL(node<T>*nil)
	{
		this->left = nil;
		this->right = nil;
	}
	void set_field(T field)
	{
		this->field = field;
	}
	void set_color(color color)
	{
		this->color_node = color;
	}
};
template<typename T>
class RED_BLACK_TREE
{
public:
	size_t size;
	node<T> *NIL;
	node<T> *root;
	RED_BLACK_TREE() 
	{
		NIL = new node<T>;
		root = NIL;
		size = 0;
	}
	bool add(node<T>*wsk)
	{
		if (root == NIL)
		{
			this->root =wsk;
			size++;
			return true;
		}
		node<T> *temp;
		temp = root;
		while (temp != NIL)
		{

			if (temp->field == wsk->field)
			{
				return false;
			}

			if (temp->field > wsk->field)
			{
				if (temp->left != NIL)
				{
					temp = temp->left;
				}
				else
				{
					size++;
					temp->left = wsk;
					temp->left->parent = temp;
					return true;
				}
			}
			else
			{
				if (temp->right != NIL)
				{
					temp = temp->right;
				}
				else
				{
					size++;
					temp->right = wsk;
					temp->right->parent = temp;
					return true;
				}
			}

		}
		return false;
	}
	void left_rotate(node<T>*temp)
	{
		node<T>*wsk;
		wsk = temp->right;
		
		temp->right = wsk->left;
		if (wsk->left != NIL)
		{
			wsk->left->parent = temp;
		}
		wsk->parent = temp->parent;
	

		if (temp->parent == NULL)
		{
			this->root = wsk;
		}
		else if (temp == temp->parent->left)
		{
			temp->parent->left = wsk;
		}
		else
		{
			temp->parent->right = wsk;
		}
		wsk->left = temp;
		temp->parent = wsk;
	}
	void right_rotate(node<T>*temp)
	{
		node<T>*wsk;
		wsk = temp->left;
		temp->left = wsk->right;
		if (wsk->right != NIL)
		{
			wsk->right->parent = temp;
		}
		
		wsk->parent = temp->parent;

		if (temp->parent == NULL)
		{
			this->root = wsk;
		}
		else if (temp == temp->parent->right)
		{
			temp->parent->right = wsk;
		}
		else
		{
			temp->parent->left = wsk;
		}
		wsk->right = temp;
		temp->parent = wsk;
	
	}
	void Red_Black_Insert(T data)
	{
		node<T> *node_to_add = new node<T>(data, size);
		node_to_add->set_NIL(NIL);
		node<T> *temp;
		bool insertion=this->add(node_to_add);
		if (insertion == false)
		{
			return;
		}
		
		while ((node_to_add != root) && (node_to_add->parent->color_node == RED))
		{
			
			if (node_to_add->parent == node_to_add->parent->parent->left)
			{
				temp = node_to_add->parent->parent->right;
				if (temp->color_node == RED)
				{
					temp->set_color(BLACK);
					node_to_add->parent->set_color(BLACK);
					node_to_add->parent->parent->set_color(RED);
					node_to_add = node_to_add->parent->parent;
				}
				else
				{
					if (node_to_add == node_to_add->parent->right)
					{
						
						node_to_add= node_to_add->parent;
						this->left_rotate(node_to_add);

					}
					node_to_add->parent->set_color(BLACK);
					
					node_to_add->parent->parent->set_color(RED);

					this->right_rotate(node_to_add->parent->parent);
					
				}
			}
			else if (node_to_add->parent == node_to_add->parent->parent->right)
			{
				temp = node_to_add->parent->parent->left;
				if (temp->color_node == RED)
				{
					temp->set_color(BLACK);
					node_to_add->parent->set_color(BLACK);
					
					node_to_add->parent->parent->set_color(RED);
					node_to_add = node_to_add->parent->parent;
				}
				else
				{	
					if (node_to_add == node_to_add->parent->left)
					{
						node_to_add = node_to_add->parent;
						this->right_rotate(node_to_add);
					}
					node_to_add->parent->set_color(BLACK);
					node_to_add->parent->parent->set_color(RED);
					this->left_rotate(node_to_add->parent->parent);
				}
			}
		}
		root->set_color(BLACK);
	}
	node<T>*search(T data)
	{
		node<T> *temp;
		temp = root;
		while (temp != NIL)
		{

			if (temp->field == data)
			{

				return temp;
			}

			if (temp->field > data)
			{
				if (temp->left != NIL)
				{
					temp = temp->left;
				}
				else
					return NULL;
			}
			else
			{
				if (temp->right != NIL)
				{
					temp = temp->right;
				}
				else
				{
					return NULL;
				}
			}
		}
		return NULL;
	}
	void preorder(node<T>*root)
	{

		if (root == NIL)
		{
			return;
		}
		std::cout << root->field << "\n";
		preorder(root->left);
		preorder(root->right);

	}
	void in_order(node<T>*root)
	{

		if (root == NIL)
		{
			return;
		}
		in_order(root->left);
		std::cout << root->field << "\n";
		in_order(root->right);

	}
	void BST_clear(node<T>*root)
	{
		if (root != NIL)
		{
			BST_clear(root->left);
			BST_clear(root->right);
			size--;
			delete root;
		}
		this->root = NIL;
	}
	void display_preorder(node<T>*root)
	{
		if (root == NIL)
		{
			return;
		}
		std::cout << root->index_node << ": [p: ";
		if (root->parent == NULL)
		{
			std::cout << "NULL, ";
		}
		else std::cout << root->parent->index_node << " ";
		if (root->left == NIL)
		{
			std::cout << "l: NULL, ";
		}
		else std::cout << "l: " << root->left->index_node << " ";
		if (root->right == NIL)
		{
			std::cout << "r: NULL, ";
		}
		else std::cout << "r: " << root->right->index_node << " ";
		if (root->color_node == BLACK)
		{
			std::cout << "color: BLACK ";
		}
		else std::cout << "color: RED ";

		std::cout << "] , data: " << root->field << "\n";


		display_preorder(root->left);

		display_preorder(root->right);
	}
	int height(node<T>*root)
	{
		if (root == NIL)
			return 0;
		else
		{
			int left_height = height(root->left);
			int right_height = height(root->right);

			if (left_height > right_height)
				return(left_height + 1);
			else return(right_height + 1);
		}
	}
};
int main()
{
	srand(time(NULL));
	RED_BLACK_TREE<stored_data>*bst = new RED_BLACK_TREE<stored_data>();

	
	stored_data so[6];
	for (int i = 0; i < 6; i++)
	{

		so[i].generate_data();
		bst->Red_Black_Insert(so[i]);
	}

	bst->display_preorder(bst->root);
	int height = bst->height(bst->root);
	std::cout << height << "\n";
	bst->BST_clear(bst->root);
	std::cout << "\n";
	

	

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
