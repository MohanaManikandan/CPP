#include <iostream>
#include <string>
#include <cstdlib>

template <typename X>
class Node
{
	public:
		X m_Value;
		Node *m_Next;
		Node *m_Previous;

		Node()
		{
			m_Value = X();
			m_Next = NULL;
			m_Previous = NULL;
		}
		
		Node (const X &pi_Value)
		{
			m_Value = pi_Value;
			m_Next = NULL;
			m_Previous = NULL;
		}
};

template <typename X>
class List
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
			List()
			{
				m_Size = 0;
				m_Head = NULL;
				m_Tail = m_Head;
			}

			List(X pi_Element)
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
					std::cout << "Empty List !!!" << std::endl;
				}
			}

			void insert(const X &pi_Element, const unsigned long &pi_Position)
			{
				Node<X> *l_CurrentNode = this->m_Head;
				Node<X> *l_PreviousNode = NULL;
				unsigned int l_Index = 0;
				if(isEmpty())
				{
					this->pushFront(pi_Element);
				}
				else
				{
					try
					{
						if(pi_Position < 0 || pi_Position > this->m_Size)
						{
							throw std::string("Index Out Of Bounds !");
						}
						else
						{
							while(pi_Position != l_Index)
							{	
								++ l_Index;
								l_PreviousNode = l_CurrentNode;
								l_CurrentNode = l_CurrentNode->m_Next;
								continue;
							}
						
							Node<X> * l_NewNode = newNode(pi_Element);
							l_NewNode->m_Next = l_CurrentNode;
							if(l_PreviousNode == NULL)
							{
								this->m_Head->m_Previous =l_NewNode;
								this->m_Head = l_NewNode;
							}
							else
							{
								l_NewNode->m_Previous = l_PreviousNode;
								l_PreviousNode->m_Next = l_NewNode;
							}
							
							if(l_NewNode->m_Next == NULL)
							{
								this->m_Tail = l_NewNode;
							}
							else
							{
								l_CurrentNode->m_Previous = l_NewNode;
							}
							++ this->m_Size;
						}
					}
					catch(std::string pi_Message)
					{
						std::cout << pi_Message << "\n";
						exit(0);
					}
				}
			}

			void remove(const unsigned long &pi_Position)
			{
				unsigned int l_Index = 0;
				if(isEmpty())
				{
					std::cout << "Empty List !!!\n";
					return;
				}
				else
				{
					Node<X> *l_CurrentNode = this->m_Head;
					Node<X> *l_PreviousNode = NULL;
					unsigned int l_Index = 0;
					try
					{
						if(pi_Position > this->m_Size)
						{
							throw std::string("Index Out Of Bounds !!");
						}
						else
						{
							while(l_Index != pi_Position)
							{
								++ l_Index;
								l_PreviousNode = l_CurrentNode;
								l_CurrentNode = l_CurrentNode->m_Next;
								continue;
							}
						
							Node<X> * l_RemoveNode = l_CurrentNode;
							if(l_CurrentNode->m_Next != NULL && l_PreviousNode != NULL)
							{
								this->m_Tail = l_PreviousNode;
								l_PreviousNode->m_Next = NULL;
							}
							else if(l_CurrentNode->m_Next == NULL && l_PreviousNode == NULL)
							{
								this->m_Head = NULL;
								this->m_Tail = NULL;
							}
							else
							{
								if(l_PreviousNode == NULL)
								{
									this->m_Head = l_CurrentNode->m_Next;
									l_CurrentNode->m_Next = NULL;
								}
								else if(l_CurrentNode->m_Next == NULL)
								{
									this->m_Tail = l_PreviousNode;
									l_PreviousNode->m_Next = NULL;
								}
							}
							delete l_CurrentNode;							
							--this->m_Size;
						}
					}
					catch(std::string pi_Message)
					{
						std::cout << pi_Message << std::endl;
						exit(0);
					}
				}
			}

			void pushBack(const X &pi_Element)
			{
				if(this->isEmpty())
				{
					this->m_Head = newNode(pi_Element);
					this->m_Tail = this->m_Head;
				}
				else
				{
					Node<X> *l_NewNode = newNode(pi_Element);
					this->m_Tail->m_Next = l_NewNode;
					l_NewNode->m_Previous = this->m_Tail;
					this->m_Tail = l_NewNode;
					l_NewNode->m_Next = NULL;
				}
				++this->m_Size;
			}

			void pushFront(const X &pi_Element)
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
					this->m_Head->m_Previous = l_NewNode;
					this->m_Head = l_NewNode;
				}
				++this->m_Size;
			}

			X popBack()
			{
				X l_Value = X();
				if(isEmpty())
				{
					std::cout << "Empty List !!!" << std::endl;
				}
				else if(this->m_Head == this->m_Tail)
				{
					l_Value = this->m_Head->m_Value;
					delete this->m_Head;
					this->m_Head = this->m_Tail = NULL;
					--this->m_Size;
				}
				else
				{
					Node<X> *l_LastNode = this->m_Tail;
					l_Value = l_LastNode->m_Value;
					this->m_Tail = l_LastNode->m_Previous;
					if(this->m_Tail != NULL)
					{
						this->m_Tail->m_Next = NULL;
					}
					delete l_LastNode;;
					--this->m_Size;
				}
				return l_Value;
			}

			X popFront()
			{
				X l_Value = X();
				if(isEmpty())
				{
					std::cout << "Empty List !!!" << std::endl;
				}
				else
				{
					Node <X> * l_Removal = this->m_Head;
					l_Value = l_Removal->m_Value;
					this->m_Head = l_Removal->m_Next;
					if(this->m_Head != NULL)
					{
						this->m_Head->m_Previous = NULL;
					}
					l_Removal->m_Next = NULL;
					delete l_Removal;
					--this->m_Size;
				}
				return l_Value;
			}

			int find(const X &pi_Element)
			{
				if(isEmpty())
				{
					std::cout << "Empty List !!!" << std::endl;
					return -1;
				}

				Node<X> *l_CurrentNode = this->m_Head;
				unsigned int l_Index = 0;
				bool l_Present = false;
				while(l_CurrentNode != NULL)
				{
					if(l_CurrentNode->m_Value == pi_Element)
					{
						l_Present = true;
						break;
					}
					else
					{
						++l_Index;
						l_CurrentNode = l_CurrentNode->m_Next;
					}
				}
				return (l_Present ? l_Index : -1);
			}
			
			~List()
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
	std::cout << "\n1.Show\t2.Insert\t3.PushFront\t4.PushBack\t5.Remove\t6.PopFront\t7.PopBack\tChoice : ";
}

int main()
{
	List<int> myList;
	while(true)
	{
		short l_Choice = 0;
		int l_Element = 0;
		unsigned long l_Position = 0;
		displayOptions();
		std::cin >> l_Choice;
		switch(l_Choice)
		{
			case 1: myList.show();
					break;
			case 2: std::cout << "Enter Element : ";
					std::cin >> l_Element;
					std::cout << "Enter Insert Position : ";
					std::cin >> l_Position;
					myList.insert(l_Element, l_Position);
					std::cout << "Element Inserted\n";
					break;
			case 3: std::cout << "Enter Element : ";
					std::cin >> l_Element;
					myList.pushFront(l_Element);
					std::cout << "Element Inserted\n";
					break;
			case 4: std::cout << "Enter Element : ";
					std::cin >> l_Element;
					myList.pushBack(l_Element);
					std::cout << "Element Inserted\n";
					break;
			case 5: std::cout << "Enter Removal Position : ";
					std::cin >> l_Position;
					myList.remove(l_Position);
					std::cout << "Element Removed\n";
					break;
			case 6: std::cout << "Element @ Front : " << myList.popFront() << "\n";
					break;
			case 7: std::cout << "Element @ Back : " << myList.popBack() << "\n";
					break;
		}
	}
	return 0;
}