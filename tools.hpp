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



class Dictionary
{
private:
	class Element
	{
	public:
		char symbol = '\0';
		int freq = 0;
	};

	// Cantidad de síbolos diferentes
	int symbol_len = 0;
	Element symbols[SYMBOLS];

public:

	void insert(char symb){
		for (int i = 0; i < symbol_len; ++i){

			if ( symb ==  symbols[i].symbol){
				symbols[i].freq += 1;
				return;
			}
		}

		symbols[symbol_len].symbol = symb;
		symbols[symbol_len].freq = 1;

		symbol_len += 1;

	}

	void printme(){
		for (int i = 0; i < symbol_len; ++i){
			char tmp = symbols[i].symbol;
			cout << tmp << "\t" << symbols[i].freq << endl;
		}
	}
	
};

class ReadData
{
/*
* Objeto que manipula un archivo de
* texto, lo abre, y le cada 
* línea
*/
protected:
	string file_name;
	ifstream text_file;
public:
	ReadData(string name) : file_name(name) {
		cout << "Opening file: " << file_name << endl;
		text_file.open(file_name, ios::in|ios::binary);
		cout << "Done!" << endl;
	} ;

	// Regresa una lína del'
	// archivo de texto
	string readLine(){
		string line;

		if (text_file.is_open()){
			getline(text_file, line);

			return line;
		}

		return "";
	}

	bool closeFile(){
		text_file.close();
	}
};