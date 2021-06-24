#pragma once

// Type must support:
//
//  operator = (numeric)
//  operator += (Type)
//  operator /= (numeric)

/**		��� �ٿ�ε�/���ε� �ӵ� ���� ���ø� Ŭ����. 
*
*		@author soyokaze
*		@date   2005-11-02
*/

template <class Type>
class Accrue
{
public:
	Accrue(void)
	{
		m_Limit = 60;
	}

	~Accrue(void)
	{
	}

	void SetLimit(DWORD Limit)
	{
		m_Limit = Limit;

		while(m_Data.GetSize() > m_Limit)
		{
			m_Data.Pop();
		}
	}

	void Add(Type t)
	{
		DWORD i;

		m_Data.PushBack(t);
		while(m_Data.GetSize() > m_Limit)
		{
			m_Data.Pop();
		}

		m_Average = 0;

		if(m_Data.GetSize() != 0)
		{
			for(i = 0; i < m_Data.GetSize(); i++)
			{
				m_Average += m_Data[i];
			}

			m_Average /= m_Data.GetSize();
		}
	}

	Type GetAverage(void)
	{
		return m_Average;
	}

protected:
	DWORD m_Limit;
	Type m_Average;
	List<Type> m_Data;
};
