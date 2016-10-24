using namespace std;

class Tree
{

private:
	class Node
	{
	private:
		int weight;
		char symbol;
		Node* left = NULL;
		Node* right = NULL;

	public:
		Node(int w, char s): weight(w), symbol(s) {}

		int getWeight(){
			return weight;
		}

		char getSymbol(){
			return symbol;
		}

		void setLeft(Node* leftChild){
			left = leftChild;
		}

		void setRight(Node* rightChild){
			right = rightChild;
		}


		
	};

	class Queue
	{
	private:
		class QueueNode
		{
		public:
			QueueNode(Node *roott): root(roott) {};
			Node* root = NULL;
			QueueNode* next = NULL;
		};

		QueueNode* first = NULL;

	public:

		void insert(Node* root){
			QueueNode* newNode = new QueueNode(root);

			int w_new = root->getWeight();

			QueueNode* actual = first;

			if (actual == NULL) {
				first = newNode;
				return;
			}

			int counter = 0;

			while(actual != NULL) {
				
				if (w_new <= actual->root->getWeight() and counter == 0) {
						newNode->next = actual;
					 	first = newNode;
					 	return;
				}


				if (actual->next == NULL and actual->root->getWeight() <= w_new) {
						actual->next = newNode;
					return;
				}

				if (w_new <= actual->next->root->getWeight()) {
					 newNode->next = actual->next;
					 actual->next = newNode;
					 return;
				}

				counter++;
				actual = actual->next;

			}


		}

		int remove(){
			if (first != NULL) {
				QueueNode* tmp = first;
				int w = tmp->root->getWeight();

				first = first->next;

				delete tmp;

				return w;
			}



			return -1;
		}
	};

public:
	void insertFather(char name, char childLeft, char childRight, int weight){
		return;
	}

	// void tmp(){
	// 	Queue miCola;

	// 	Node* miNodo1 = new Node(1, 'A');
	// 	Node* miNodo2 = new Node(2, 'B');
	// 	Node* miNodo3 = new Node(3, 'C');
	// 	Node* miNodo4 = new Node(4, 'C');

	// 	miCola.insert(miNodo3);
	// 	miCola.insert(miNodo1);
	// 	miCola.insert(miNodo4);
	// 	miCola.insert(miNodo2);
	// 	miCola.insert(miNodo3);

	// 	cout << miCola.remove() << endl;
	// 	cout << miCola.remove() << endl;
	// 	cout << miCola.remove() << endl;
	// 	cout << miCola.remove() << endl;
	// 	cout << miCola.remove() << endl;

	// }
	
};