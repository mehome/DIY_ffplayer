#pragma once
template < class T >
class TNsSmartPtr
{
public:

	TNsSmartPtr()
	{
		m_ptInterface = NULL;
	}

	TNsSmartPtr(T* in_ptInterface)
	{
		m_ptInterface = NULL;

		if (in_ptInterface != NULL)
		{
			in_ptInterface->AddRef();
		}

		m_ptInterface = in_ptInterface;
	}

	TNsSmartPtr(const TNsSmartPtr< T >  &in_reftInterface)
	{
		m_ptInterface = NULL;

		if (in_reftInterface.m_ptInterface != NULL)
		{
			in_reftInterface.m_ptInterface->AddRef();
		}

		m_ptInterface = in_reftInterface.m_ptInterface;
	}

	virtual ~TNsSmartPtr()
	{
		Release();
	}

	T* AssignNew(T* in_ptInterface)
	{
		if (m_ptInterface != NULL)
		{
			m_ptInterface->Release();
			m_ptInterface = NULL;
		}

		// We assign the newly created interface directly, without AddRef-ing
		// beacause its RefCount is already set to 1, and we are tbe the only
		// ones keeping the pointer on that interface.
		m_ptInterface = in_ptInterface;

		return m_ptInterface;
	}

	void Release()
	{
		if (m_ptInterface != NULL)
		{
			m_ptInterface->Release();
		}

		m_ptInterface = NULL;
	}

	virtual operator T*()
	{
		return  (T*)m_ptInterface;
	}

	virtual T& operator*()
	{
		if (m_ptInterface == NULL)
		{
			assert(false);
			throw CNsSmartPointerException("TNsSmartPtr::operator* -> Internal pointer is NULL!");
		}
		return *m_ptInterface;
	}

	virtual T** operator&()
	{
		if (m_ptInterface != NULL)
		{
			assert(false);
			throw CNsSmartPointerException("TNsSmartPtr::operator* -> Internal pointer will be overriden!");
		}
		return &m_ptInterface;
	}

	virtual T* operator->()
	{
		if (m_ptInterface == NULL)
		{
			assert(false);
			throw CNsSmartPointerException("TNsSmartPtr::operator* -> Internal pointer is NULL!");
		}
		return m_ptInterface;
	}

	virtual T* operator=(T* in_ptInterface)
	{
		if (in_ptInterface != NULL)
		{
			in_ptInterface->AddRef();
		}

		if (m_ptInterface != NULL)
		{
			m_ptInterface->Release();
			m_ptInterface = NULL;
		}

		m_ptInterface = in_ptInterface;

		return m_ptInterface;
	}

	virtual bool operator!()
	{
		return (m_ptInterface == NULL);
	}

	virtual bool operator==(T* in_ptInterface)
	{
		return (m_ptInterface == in_ptInterface);
	}

	T* operator=(const TNsSmartPtr< T > &in_reftInterface)
	{
		return operator=(in_reftInterface.m_ptInterface);
	}

protected:

	T*			           m_ptInterface;  // any interface.   
};
