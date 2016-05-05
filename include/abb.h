#ifndef ABB_H_
#define ABB_H_

class ABB
{
	public:
		struct Node
		{
			int key;
			Node * left;
			Node * right;
			Node * parent;
			int leftSize;
			int rightSize;
		};

	private:
		Node * root;
		int size;
		int height;

		Node * search_aux(int key, int * f);

	public:
		ABB();

		~ABB();

		Node * search(int key);

		void insert(int key);

		bool remove(int key);

		int nElement(int n);

		int position(int key);

		int mediana();

		void print(); //depuracao
};

#endif