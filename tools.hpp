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

		Node* getLeft(){
			return left;
		}

		Node* getRight(){
			return right;
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

		Node* remove(){
			if (first != NULL) {
				QueueNode* tmp = first;
				int w = tmp->root->getWeight();

				Node* root = tmp->root;

				first = first->next;

				delete tmp;

				return root;
			}



			return NULL;
		}
	};

	void insertFather(Node* leftChild, Node* rightChild, int weight){
		Node* newNode = new Node(weight, '\0');

		newNode->setLeft(leftChild);
		newNode->setRight(rightChild);

		myQueue.insert(newNode);

		treeRoot = newNode;

	}

	Queue myQueue;
	Node* treeRoot;

public:

	void insertNode(int freq, char symbol){

		Node* tmp = new Node(freq, symbol);

		myQueue.insert(tmp);

	}

	void makeMe(){
		Node* leftChild  = myQueue.remove();
		Node* rightChild = myQueue.remove();
		
		while (leftChild != NULL  and rightChild != NULL){		

			int weight = leftChild->getWeight() + rightChild->getWeight();

			insertFather(leftChild, rightChild, weight);

			leftChild  = myQueue.remove();
			rightChild = myQueue.remove();
		}

	}

	bool find(Node* root, char symbol, string code, int branch, char bin){

		if (root == NULL)
			return false;


		if (code.length() < branch) code += bin;
		else code[branch] = bin;

		branch++;



		if (root->getSymbol() == symbol) {
			cout << root->getSymbol() << "\t"
				 << code.substr(0, branch) << endl;
			return true;
		}



		if (find(root->getLeft(), symbol, code, branch, '0'))
			return true;

		if (find(root->getRight(), symbol, code, branch, '1'))
			return true;

		return false;

	}

	void showme(char c){
		find(treeRoot, c, "", 0, '0');
	}
	
};

///////////////////////////////////////
///////////////////////////////////////
// Implementación de un diccionario
// para guardar los símbolos
///////////////////////////////////////
///////////////////////////////////////

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

	int getSymbolLen(){
		return symbol_len;
	}

	char getSymbol(int index){
		return symbols[index].symbol;
	}

	int getFreq(int index){
		return symbols[index].freq;
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

		text_file >> noskipws;
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

	string getHexChar(){
		unsigned char x;

		if (text_file >> x) {
			
			ostringstream buffer;
			buffer << hex << (int) x << " ";

			return buffer.str();
		}

		return "";
	}

	bool closeFile(){
		text_file.close();
	}
};