#pragma once

#include "Core/AresMath.h"

using namespace boost;

namespace Ares
{
	enum BufferUsage
	{
		BU_Static,
		BU_Dynamic,
	};

	enum BufferAccess
	{
		BA_ReadOnly,
		BA_WriteOnly,
		BA_ReadWrite,
	};

	//--------------------------------------
	// ͼ��Buffer 2012-4-1  ����
	//--------------------------------------
	class CORE_EXPORT GraphicsBuffer
	{
	public:
		// GraphicsBuffer Modifier
		class Modifier : noncopyable
		{
			friend class GraphicsBuffer;
		public:
			// constructors
			Modifier( s_ptr<GraphicsBuffer>& buffer, BufferAccess bufAccess)
				: m_buffer( buffer)
			{
				m_data = m_buffer->Map( bufAccess);
			}

			// desctructor
			~Modifier()
			{
				m_buffer->Unmap();
			}

			// returns the pointer of the data
			template<typename T>
			T* GetPointer()
			{
				return static_cast<T*>(m_data);
			}

			// returns the pointer of the data
			template<typename T>
			const T* GetPointer() const
			{
				return static_cast<T*>(m_data);
			}

			// returns size of the data
			template<typename T>
			int GetSize() const
			{
				// ��0�ж�
				A_ASSERT( sizeof( T));

				return m_buffer->GetSize() / sizeof(T);
			}

			// set data
			template<typename T>
			void Set( int idx, const T& t)
			{
				// ��С����
				A_ASSERT( m_buffer->GetSize() / sizeof(t) > idx);

				// change value
				T* buf = static_cast<T*>( m_data);
				buf[idx] = t;
			}

			// set data
			void Set( const void* src, size_t sizeInByte)
			{
				//ARES_ASSERT( sizeInByte < m_buffer.GetSize());
				A_ASSERT( m_data);

				std::memcpy( m_data, src, sizeInByte);
			}

		private:
			s_ptr<GraphicsBuffer> m_buffer;		// buffer
			void*				  m_data;		// data
		};

	public:
		// ���캯��
		explicit GraphicsBuffer( BufferUsage usage, UINT accessHint);

		// ��������
		virtual ~GraphicsBuffer();

		// ��ȡ��С(Byte �ֽ�)
		UINT GetSize() const { return m_sizeInByte; }

		// ��ȡUsage
		BufferUsage GetUsage() const { return m_usage; }

		// ��ȡAccessHint
		UINT GetAccessHint() { return m_accessHint; }

		// ���ô�С
		virtual void Resize( UINT sizeInByte) { m_sizeInByte = sizeInByte; }

	private:
		// Map
		virtual void* Map( BufferAccess bufAccess)=0;

		// Unmap
		virtual void Unmap()=0;

	protected:
		BufferUsage		m_usage;
		UINT			m_accessHint;
		UINT			m_sizeInByte;
	};
}