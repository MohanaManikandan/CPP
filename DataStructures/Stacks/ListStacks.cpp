#include <iostream>
#include <string>
#include <cstdlib>

template <typename X>
class Node
{
	public:
		X m_Value;
		Node *m_Next;

		Node()
		{
			m_Value = X();
			m_Next = NULL;
		}
		
		Node (const X &pi_Value)
		{
			m_Value = pi_Value;
			m_Next = NULL;
		}
};

template <typename X>
class Stack
{
	private:
			unsigned long m_Size;
			Node <X> *m_Head, *m_Tail;

			Node<X> * newNode(const X &pi_Value = X())
			{
				Node<X>* l_NewNode = NULL;
				try
				{
					l_NewNode = new Node<X>(pi_Value);
				}
				catch(std::bad_alloc)
				{
					std::cout << "Bad Alloc !!!!!!!!!!!!!\n";
					exit(0);
				}
				return l_NewNode;
			}
			
			bool isEmpty()
			{
				bool l_ReturnValue = false;
				if(this->m_Head == NULL)
				{
					l_ReturnValue = true;
				}
				return l_ReturnValue;
			}

	public:
			Stack()
			{
				m_Size = 0;
				m_Head = NULL;
				m_Tail = m_Head;
			}

			Stack(X pi_Element)
			{
				m_Size += 1;
				m_Head = newNode(pi_Element);
				m_Tail = m_Head;
			}
			
			void show()
			{
				if(!isEmpty())
				{
					Node <X> *l_CurrentNode = this->m_Head;
					while(l_CurrentNode != NULL)
					{
						std::cout << "Value : " << l_CurrentNode->m_Value << std::endl;
						l_CurrentNode = l_CurrentNode->m_Next;
					}
				}
				else
				{
					std::cout << "Empty Stack !!!" << std::endl;
				}
			}

			void pushTop(const X &pi_Element)
			{
				if(this->isEmpty())
				{
					this->m_Head = newNode(pi_Element);
					this->m_Tail = this->m_Head;
				}
				else
				{
					Node<X> *l_NewNode = newNode(pi_Element);
					l_NewNode->m_Next = this->m_Head;
					this->m_Head = l_NewNode;
				}
				++this->m_Size;
			}

			X popTop()
			{
				X l_Value = X();
				if(isEmpty())
				{
					std::cout << "Empty Stack !!!" << std::endl;
				}
				else
				{
					Node <X> * l_Removal = this->m_Head;
					l_Value = l_Removal->m_Value;
					this->m_Head = l_Removal->m_Next;
					delete l_Removal;
					l_Removal->m_Next = NULL;
					--this->m_Size;
				}
				return l_Value;
			}
			
			~Stack()
			{
				while(this->m_Head != NULL)
				{
					Node<X> *l_Del = this->m_Head;
					this->m_Head = this->m_Head->m_Next;
					delete l_Del;
				}
				this->m_Size = 0;
			}
};

void displayOptions()
{
	std::cout << "\n1.Show\t2.PushTop\t3.PopTop\tChoice : ";
}

int main()
{
	Stack<int> myStack;
	while(true)
	{
		short l_Choice = 0;
		int l_Element = 0;
		unsigned long l_Position = 0;
		displayOptions();
		std::cin >> l_Choice;
		switch(l_Choice)
		{
			case 1: myStack.show();
					break;
			case 2: std::cout << "Enter Element : ";
					std::cin >> l_Element;
					myStack.pushTop(l_Element);
					std::cout << "Element Inserted\n";
					break;
			case 3: std::cout << "Element @ Front : " << myStack.popTop() << "\n";
					break;
		}
	}
	return 0;
}