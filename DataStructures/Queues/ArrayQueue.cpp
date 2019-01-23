#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

template <typename X>
class ArrayQueue
{
	private:
		unsigned long m_Size;
		long m_Front;
		long m_Back;
		X * m_Queue;

		bool isEmpty()
		{
			return (m_Front == m_Back ? true : false);
		}

	public:
		ArrayQueue()
		{
			m_Size = 8;
			m_Front = 0;
			m_Back = 0;
			m_Queue = new X[m_Size];
		}
		
		ArrayQueue(const unsigned long &pi_Size)
		{
			m_Size = pi_Size;
			m_Front = 0;
			m_Back = 0;
			m_Queue = new X[m_Size];
		}

		void pushFront(const X &pi_Element)
		{
			if((m_Front + 1)%m_Size != (m_Back%m_Size))
			{
				m_Queue[m_Front] = pi_Element;
				m_Front = (++m_Front)%m_Size;
			}
			else
				std::cout << "Queue Full\n";
		}

		bool popBack(X &po_Element)
		{
			bool l_ReturnValue = false;
			if(isEmpty())
			{
				std::cout << "Empty Queue !";
			}
			else
			{
				po_Element = m_Queue[m_Back];
				m_Back = (++m_Back)%m_Size;
				l_ReturnValue = true;
			}
			return l_ReturnValue;
		}

		void show()
		{
			if(isEmpty())
			{
				std::cout << "Empty Queue !\n";
			}
			else
			{
				long l_Index = m_Back;
				while(l_Index != m_Front)
				{
					std::cout << m_Queue[l_Index] << " ";
					l_Index = (++l_Index)%m_Size;
				}
			}
		}
};

void displayOptions()
{
	std::cout << "\n1.Show\t2.PushFront\t3.PopBack\tChoice : ";
}

int main()
{
	short l_Choice = -1;
	int l_Element = 0;
	ArrayQueue<int> l_MyAQueue(5);
	while(true)
	{
		displayOptions();
		std::cin >> l_Choice;
		switch(l_Choice)
		{
			case 1: l_MyAQueue.show(); break;
			case 2: std::cout << "Element : "; 
					std::cin >> l_Element; 
					l_MyAQueue.pushFront(l_Element);
					break;
			case 3: if(l_MyAQueue.popBack(l_Element))
					{
						std::cout << "Element " << l_Element << " Retreived\n";
					}
					break;
		}
	}
	return 0;
}