
#include "PreComfiled.h"
#include "CircularBuffer.h"
#include <assert.h>

bool CircularBuffer::Peek( OUT char* destbuf, size_t bytes ) const
{
	assert( m_Buffer != nullptr );

	if ( m_ARegionSize + m_BRegionSize < bytes )
	{
		return false;
	}
	
	size_t cnt = bytes;
	size_t aRead = 0;

	if ( m_ARegionSize > 0 )
	{
		aRead = (cnt > m_ARegionSize) ? m_ARegionSize : cnt;
		memcpy( destbuf, m_ARegionPointer, aRead );
		cnt -= aRead;
	}

	if ( cnt > 0 && m_BRegionSize > 0 )
	{
		assert( cnt <= m_BRegionSize );

		size_t bRead = cnt;

		memcpy( destbuf+aRead, m_BRegionPointer, bRead );
		cnt -= bRead;
	}

	assert( cnt == 0 );

	return true;
}
bool CircularBuffer::Read( OUT char* destbuf, size_t bytes )
{
	assert( m_Buffer != nullptr );

	if ( m_ARegionSize + m_BRegionSize < bytes )
	{
		return false;
	}

	size_t cnt = bytes;
	size_t aRead = 0;

	if ( m_ARegionSize > 0 )
	{
		aRead = (cnt > m_ARegionSize) ? m_ARegionSize : cnt;
		memcpy( destbuf, m_ARegionPointer, aRead );
		m_ARegionSize -= aRead;
		m_ARegionPointer += aRead;
		cnt -= aRead;
	}

	if ( cnt > 0 && m_BRegionSize > 0 )
	{
		assert( cnt <= m_BRegionSize );
		size_t bRead = cnt;

		memcpy( destbuf+aRead, m_BRegionPointer, bRead );
		m_BRegionSize -= bRead;
		m_BRegionPointer += bRead;
		cnt -= bRead;
	}

	assert( cnt == 0 );

	if ( m_ARegionSize == 0 )
	{
		if ( m_BRegionSize == 0 )
		{
			if ( m_BRegionPointer != m_Buffer )
			{
				memmove( m_Buffer, m_BRegionPointer, m_BRegionSize );

				m_ARegionPointer = m_Buffer;
				m_ARegionSize = m_BRegionSize;
				m_BRegionPointer = nullptr;
				m_BRegionSize = 0;
			}
			else
			{
				m_BRegionPointer = nullptr;
				m_BRegionSize = 0;
				m_ARegionPointer = m_Buffer;
				m_ARegionSize = 0;
			}
		}
	}

	return true;
}
bool CircularBuffer::Write( const char* data, size_t bytes )
{
	assert( m_Buffer != nullptr );

	/// Read�� �ݴ�� B�� �ִٸ� B������ ���� ����
	if( m_BRegionPointer != nullptr )
	{
		if ( GetBFreeSpace() < bytes )
			return false;

		memcpy(m_BRegionPointer + m_BRegionSize, data, bytes);
		m_BRegionSize += bytes;

		return true;
	}

	/// A�������� �ٸ� ������ �뷮�� �� Ŭ ��� �� ������ B�� �����ϰ� ���
	if ( GetAFreeSpace() < GetSpaceBeforeA() )
	{
		AllocateB();

		if ( GetBFreeSpace() < bytes )
			return false;

		memcpy( m_BRegionPointer+m_BRegionSize, data, bytes );
		m_BRegionSize += bytes;

		return true;
	}
	/// A������ �� ũ�� �翬�� A�� ����
	else
	{
		if ( GetAFreeSpace() < bytes )
			return false;

		memcpy( m_ARegionPointer+m_ARegionSize, data, bytes );
		m_ARegionSize += bytes;

		return true;
	}
}

void CircularBuffer::Remove( size_t len )
{
	size_t cnt = len;

	/// Read�� ���������� A�� �ִٸ� A�������� ���� ����

	if ( m_ARegionSize > 0 )
	{
		size_t aRemove = (cnt > m_ARegionSize) ? m_ARegionSize : cnt;
		m_ARegionSize -= aRemove;
		m_ARegionPointer += aRemove;
		cnt -= aRemove;
	}

	// ������ �뷮�� �� ������� B���� ���� 
	if ( cnt > 0 && m_BRegionSize > 0 )
	{
		size_t bRemove = (cnt > m_BRegionSize) ? m_BRegionSize : cnt;
		m_BRegionSize -= bRemove;
		m_BRegionPointer += bRemove;
		cnt -= bRemove;
	}

	/// A������ ������� B�� A�� ����ġ 
	if ( m_ARegionSize == 0 )
	{
		if ( m_BRegionSize > 0 )
		{
			/// ������ ��� ���̱�
			if ( m_BRegionPointer != m_Buffer )
				memmove( m_Buffer, m_BRegionPointer, m_BRegionSize );

			m_ARegionPointer = m_Buffer;
			m_ARegionSize = m_BRegionSize;
			m_BRegionPointer = nullptr;
			m_BRegionSize = 0;
		}
		else
		{
			m_BRegionPointer = nullptr;
			m_BRegionSize = 0;
			m_ARegionPointer = m_Buffer;
			m_ARegionSize = 0;
		}
	}
}

size_t CircularBuffer::GetFreeSpaceSize()
{
	if ( m_BRegionPointer != nullptr )
	{
		return GetBFreeSpace();
	}
	else
	{
		if ( GetAFreeSpace() < GetSpaceBeforeA() )
		{
			AllocateB();
			return GetBFreeSpace();
		}
		else
		{
			return GetAFreeSpace();
		}
	}
}
size_t CircularBuffer::GetStoredSize() const
{
	return m_ARegionSize + m_BRegionSize;
}

size_t CircularBuffer::GetContiguiousBytes() const
{
	if ( m_ARegionSize > 0 )
	{
		return m_ARegionSize;
	}
	else
	{
		return m_BRegionSize;
	}
}

void* CircularBuffer::GetBuffer() const
{
	if ( m_BRegionPointer != nullptr )
	{
		return m_BRegionPointer + m_BRegionSize;
	}
	else
	{
		return m_ARegionPointer + m_ARegionSize;
	}
}
void CircularBuffer::Commit( size_t len )
{
	if ( m_BRegionPointer != nullptr )
	{
		m_BRegionSize += len;
	}
	else
	{
		m_ARegionSize += len;
	}
}

void* CircularBuffer::GetBufferStart() const
{
	if ( m_ARegionSize > 0 )
	{
		return m_ARegionPointer;
	}
	else
	{
		return m_BRegionPointer;
	}
}

void CircularBuffer::AllocateB()
{
	m_BRegionPointer = m_Buffer;
}
size_t CircularBuffer::GetAFreeSpace()
{
	return (m_BufferEnd - m_ARegionPointer - m_ARegionSize);
}
size_t CircularBuffer::GetSpaceBeforeA()
{
	return (m_ARegionPointer - m_Buffer);
}
size_t CircularBuffer::GetBFreeSpace()
{
	if ( m_BRegionPointer == nullptr )
	{
		return 0;
	}
	return (m_ARegionPointer - m_BRegionPointer - m_BRegionSize);
}