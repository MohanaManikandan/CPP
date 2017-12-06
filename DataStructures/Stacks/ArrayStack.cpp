#include <iostream>
#include <cstdlib>
#include <algorithm>

template <typename X>
class ArrayStack
{
	private:
		unsigned long m_Size;
		unsigned long m_Top;
		X * m_Stack;

		void checkOverflow()
		{
			if(this->m_Size -1 == this->m_Top)
			{
				try
				{
					X * l_LocalX = this->m_Stack;
					this->m_Size <<= 1;
					this->m_Stack = new X[this->m_Size];
					std::copy(l_LocalX, l_LocalX+this->m_Size, this->m_Stack);
					delete l_LocalX;
					l_LocalX = NULL;
				}
				catch(std::bad_alloc)
				{
					std::cout << "BAD ALLOC !!\n";
					exit(0);
				}
			}
		}

		bool isEmpty()
		{
			return (this->m_Top == -1 ? true : false);
		}

	public:
		ArrayStack()
		{
			this->m_Size = 8;
			this->m_Top = -1;
			m_Stack = new X[this->m_Size];
		}
		
		ArrayStack(const unsigned long &pi_Size)
		{
			this->m_Size = pi_Size;
			this->m_Top = -1;
			m_Stack = new X[this->m_Size];
		}

		void pushTop(const X &pi_Element)
		{
			checkOverflow();
			this->m_Stack[++this->m_Top] = pi_Element;
		}

		bool popTop(X &po_Element)
		{
			bool l_ReturnValue = false;
			if(isEmpty())
			{
				std::cout << "Empty Stack !";
			}
			else
			{
				po_Element = this->m_Stack[this->m_Top--];
				l_ReturnValue = true;
			}
			return l_ReturnValue;
		}

		void show()
		{
			if(isEmpty())
			{
				std::cout << "Empty Stack !\n";
			}
			else
			{
				unsigned long l_Index = 0;
				while(l_Index <= this->m_Top && l_Index < this->m_Size)
				{
					std::cout << this->m_Stack[l_Index++] << "  ";
				}
				std::cout << std::endl;
			}
		}
};

void displayOptions()
{
	std::cout << "\n1.Show\t2.PushTop\t3.PopTop\tChoice : ";
}

int main()
{
	short l_Choice = -1;
	int l_Element = 0;
	ArrayStack<int> l_MyAStack(2);
	while(true)
	{
		displayOptions();
		std::cin >> l_Choice;
		switch(l_Choice)
		{
			case 1: l_MyAStack.show(); break;
			case 2: std::cout << "Element : "; 
					std::cin >> l_Element; 
					l_MyAStack.pushTop(l_Element);
					break;
			case 3: if(l_MyAStack.popTop(l_Element))
					{
						std::cout << "Element " << l_Element << " Retreived\n";
					}
					break;
		}
	}
	return 0;
}