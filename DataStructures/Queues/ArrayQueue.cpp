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
			return (this->m_Front == this->m_Back ? true : false);
		}

	public:
		ArrayQueue()
		{
			this->m_Size = 8;
			this->m_Front = 0;
			this->m_Back = 0;
			this->m_Queue = new X[this->m_Size];
		}
		
		ArrayQueue(const unsigned long &pi_Size)
		{
			this->m_Size = pi_Size;
			this->m_Front = 0;
			this->m_Back = 0;
			this->m_Queue = new X[this->m_Size];
		}

		void pushFront(const X &pi_Element)
		{
			if((this->m_Front + 1)%this->m_Size != (this->m_Back%this->m_Size))
			{
				this->m_Queue[this->m_Front] = pi_Element;
				this->m_Front = (++this->m_Front)%this->m_Size;
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
				po_Element = this->m_Queue[this->m_Back];
				this->m_Back = (++this->m_Back)%this->m_Size;
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
				long l_Index = this->m_Back;
				while(l_Index != this->m_Front)
				{
					std::cout << this->m_Queue[l_Index] << " ";
					l_Index = (++l_Index)%this->m_Size;
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