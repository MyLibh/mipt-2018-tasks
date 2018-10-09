#pragma once

//====================================================================================================================================
//!
//!	\file   Stack.hpp
//!
//! \brief	Implementation of a non-stackable stack 
//!
//====================================================================================================================================

#ifndef __STACK_HPP_INCLUDED__
#define __STACK_HPP_INCLUDED__

#ifndef __cplusplus
	#error
	#error  Must use C++ to compile.
	#error
#endif /* __cplusplus */

#include "Hash.hpp"

#include <memory>      
#include <cassert> // assert
#include <iomanip> // std::setw
#include <string>  
#include <iostream>

#if   GUARD_LVL == 3
#define   HASH_GUARD(...) __VA_ARGS__
#define CANARY_GUARD(...) __VA_ARGS__
#define  GUARD_CHECK(   ) if(!this->ok()) std::cerr << "[ERROR] "<< __FUNCTION__ << std::endl, this->dump(std::cerr);
#elif GUARD_LVL == 2
#define   HASH_GUARD(...) 
#define CANARY_GUARD(...) __VA_ARGS__
#define  GUARD_CHECK(   ) if(!this->ok()) std::cerr << "[ERROR] "<< __FUNCTION__ << std::endl, this->dump(std::cerr);
#elif GUARD_LVL == 1
#define   HASH_GUARD(...) 
#define CANARY_GUARD(...) 
#define  GUARD_CHECK(   ) if(!this->ok()) std::cerr << "[ERROR] "<< __FUNCTION__ << std::endl, this->dump(std::cerr);
#else
#define   HASH_GUARD(...)
#define CANARY_GUARD(...) 
#define  GUARD_CHECK(   )
#endif // GUARD_LVL

namespace NStack
{
	template<typename T = int>
	class Stack final
	{

//====================================================================================================================================
//!
//! \brief	Reallocs memory for stack(increases by a power of two)
//!
//! \throw  std::bad_alloc
//!
//====================================================================================================================================

		void reallocMemory();

	public:
		static constexpr size_t DEFAULT_SIZE = 1;

		typedef       T &&rrVal_;
		typedef const T  &crVal_;

		explicit Stack(size_t = DEFAULT_SIZE) noexcept;
		Stack(const Stack<T>&)                noexcept;
		Stack(Stack&&)                        noexcept;
		~Stack();

		Stack<T> &operator=(const Stack&) noexcept;
		Stack<T> &operator=(Stack&&)      noexcept;

		bool operator==(const Stack&) const;
		bool operator!=(const Stack&) const;

//====================================================================================================================================
//!
//! \brief   Returnes number of elements in stack
//! 
//! \return  Stack size
//!
//====================================================================================================================================

		size_t size()  const noexcept;

//====================================================================================================================================
//!
//! \brief   Check the number of elements in stack
//! 
//! \return  Is stack empty
//!
//====================================================================================================================================

		bool empty() const noexcept;

//====================================================================================================================================
//!
//! \brief  Pushes an element to the stack
//! 
//! \param  val  Value to push to the top of the stack
//!
//! \throw  std::bad_alloc
//!
//====================================================================================================================================

		void push(crVal_ val);

//====================================================================================================================================
//!
//! \brief  Pushes an element to the stack
//! 
//! \param  val  Value to push to the top of the stack
//!
//! \throw  std::bad_alloc
//!
//====================================================================================================================================

		void push(rrVal_ val);

//====================================================================================================================================
//!
//! \brief  Pops an element from the top of the stack
//! 
//! \throw  std::length_error
//!
//====================================================================================================================================

		void pop();

//====================================================================================================================================
//!
//! \brief	 Returns an element from the top of the stack
//!
//! \return  Top element
//!  
//! \throw   std::out_of_range
//!
//====================================================================================================================================

		crVal_ top() const;

//====================================================================================================================================
//!
//! \brief	 Swaps two instances of stack
//!
//! \param   rStack  The stack to swap with
//!
//! \throw   std::_Is_nothrow_swappable<T>::value  
//!
//====================================================================================================================================

		void swap(Stack &rStack) noexcept(std::_Is_nothrow_swappable<T>::value);

//====================================================================================================================================
//!
//! \brief	Recalculates the hash
//!
//====================================================================================================================================

		HASH_GUARD(inline void rehash() noexcept { hash_ = std::move(makeHash()); })

//====================================================================================================================================
//!
//! \brief	 Returns current hash
//!
//! \return  Hash
//!
//====================================================================================================================================

		HASH_GUARD(inline std::string_view getHash() const noexcept { return hash_; })

//====================================================================================================================================
//!
//! \brief	 Validates the stack condition
//!
//! \return  Is stack ok
//!
//====================================================================================================================================

		bool ok() const noexcept;

//====================================================================================================================================
//!
//! \brief	Dumps stack to the stream
//!
//! \param  rOstr  Stream to output
//!
//====================================================================================================================================

		template<typename Char, typename Traits = std::char_traits<Char>>
		void dump(std::basic_ostream<Char, Traits> &rOstr) const noexcept;

	private:
		CANARY_GUARD(const std::string CANARY_VALUE;)

		CANARY_GUARD(const std::string canaryStart_;)
		HASH_GUARD(std::string hash_;)

		size_t               counter_,
		                     size_;
		std::unique_ptr<T[]> buffer_;

		CANARY_GUARD(const std::string canaryFinish_;)

//====================================================================================================================================
//!
//! \brief	 Constructs line to calculate hash
//!
//! \return  Hash
//!  
//! \throw   smth
//!
//====================================================================================================================================

		HASH_GUARD
		(
			std::string makeHash() const
			{
				std::string tmp(std::to_string(counter_) + std::to_string(size_));

				for (size_t i = 0; i < counter_; ++i) 
					tmp += std::to_string(buffer_[i]);

				return std::string(NHash::Hash<>(tmp).getHash());				
			}
		)

		static size_t numberOfInstances;
	};

	template<typename T>
	size_t Stack<T>::numberOfInstances = 0; 

#pragma region METHOD_DEFINITION

	template<typename T>
	inline Stack<T>::Stack(size_t size /* = DEFAULT_SIZE */) noexcept :
		CANARY_GUARD(CANARY_VALUE(NHash::Hash<>("Stack" + std::to_string(++numberOfInstances)).getHash()),)
		CANARY_GUARD(canaryStart_(CANARY_VALUE),)
		HASH_GUARD(hash_(),)

		counter_(NULL),
		size_(size),
		buffer_(new T[size])

		CANARY_GUARD(, canaryFinish_(CANARY_VALUE))
	{
		HASH_GUARD(rehash();)

		CANARY_GUARD(numberOfInstances--;)
		numberOfInstances++;

		GUARD_CHECK()
	}

	template<typename T>
	inline Stack<T>::Stack(const Stack<T> &crStack) noexcept :
		CANARY_GUARD(CANARY_VALUE(NHash::Hash("Stack" + std::to_string(++numberOfInstances)).getHash()),)
		CANARY_GUARD(canaryStart_(CANARY_VALUE),)
		HASH_GUARD(hash_(),)

		counter_(crStack.counter_),
		size_(crStack.size_),
		buffer_(new T[crStack.size_])

		CANARY_GUARD(, canaryFinish_(CANARY_VALUE))
	{
		std::copy(crStack.buffer_.get(), crStack.buffer_.get() + crStack.counter_, buffer_.get());

		HASH_GUARD(rehash();)

		CANARY_GUARD(numberOfInstances--;)
		numberOfInstances++;

		GUARD_CHECK()
	}

	template<typename T>
	inline Stack<T>::Stack(Stack<T> &&rrStack) noexcept :
		CANARY_GUARD(CANARY_VALUE(NHash::Hash("Stack" + std::to_string(++numberOfInstances)).getHash()),)
		CANARY_GUARD(canaryStart_(CANARY_VALUE), )
		HASH_GUARD(hash_(rrStack.hash_), )

		counter_(rrStack.counter_),
		size_(rrStack.size_),
		buffer_(rrStack.buffer_.release())

		CANARY_GUARD(, canaryFinish_(CANARY_VALUE))
	{
		rrStack.counter_ = NULL;
		rrStack.size_    = NULL;
		rrStack.buffer_  = nullptr;
		HASH_GUARD(rrStack.hash_.clear();)

		CANARY_GUARD(numberOfInstances--;)
		numberOfInstances++;

		GUARD_CHECK()
	}

	template<typename T>
	inline Stack<T>::~Stack()
	{
		numberOfInstances--;

		GUARD_CHECK()
	}

	template<typename T>
	void Stack<T>::reallocMemory()
	{
		GUARD_CHECK()

		T *pBuf = buffer_.release();

		size_ <<= 1;
		buffer_.reset(new T[size_]);

		std::copy(pBuf, pBuf + counter_, buffer_.get());

		HASH_GUARD(rehash();)

		GUARD_CHECK()
	}

	template<typename T>
	Stack<T> &Stack<T>::operator=(const Stack &crStack) noexcept
	{
		GUARD_CHECK()

		if (this != &crStack)
		{
			counter_ = crStack.counter_;

			if (size_ != crStack.size_)
			{
				size_ = crStack.size_;

				buffer_.reset(new T[size_]);
			}

			std::copy(crStack.buffer_.get(), crStack.buffer_.get() + crStack.size_, buffer_.get());
		}
		HASH_GUARD(hash_ = crStack.hash_;)

		GUARD_CHECK()

		return (*this);
	}

	template<typename T>
	Stack<T> &Stack<T>::operator=(Stack &&rrStack) noexcept
	{
		GUARD_CHECK()

		assert(this != &rrStack);

		buffer_ = nullptr;

		counter_ = rrStack.counter_;
		size_    = rrStack.size_;
		buffer_  = std::move(rrStack.buffer_);

		HASH_GUARD(hash_ = rrStack.hash_;)

		rrStack.counter_ = NULL;
		rrStack.size_    = NULL;
		rrStack.buffer_  = nullptr;
		HASH_GUARD(rrStack.hash_.clear();)

		GUARD_CHECK()

		return (*this);
	}

	template<typename T>
	inline bool Stack<T>::operator==(const Stack &crStack) const
	{
		GUARD_CHECK()

		if (counter_ != crStack.counter_) 
			return false;

		if (!counter_) 
			return true; // Zero-size verification

		GUARD_CHECK()

		return std::equal(&buffer_[0], &buffer_[counter_ - 1], &crStack.buffer_[0]);
	}

	template<typename T>
	inline bool Stack<T>::operator!=(const Stack &crStack) const 
	{
		return (!(*this == crStack));
	}

	template<typename T>
	inline size_t Stack<T>::size() const noexcept
	{ 
		return counter_;
	}

	template<typename T>
	inline bool Stack<T>::empty() const noexcept
	{ 
		return (counter_ ? false : true); 
	}

	template<typename T>
	inline void Stack<T>::push(crVal_ val)
	{
		GUARD_CHECK()

		if (counter_ + 1 == size_) 
			reallocMemory();

		buffer_[counter_] = val;
		++counter_;

		HASH_GUARD(rehash();)

		GUARD_CHECK()
	}

	template<typename T>
	inline void Stack<T>::push(rrVal_ val)
	{
		GUARD_CHECK()

		if (counter_ + 1 == size_) 
			reallocMemory();

		buffer_[counter_] = val;
		++counter_;

		HASH_GUARD(rehash();)

		GUARD_CHECK()
	}

	template<typename T>
	inline void Stack<T>::pop()
	{
		GUARD_CHECK()

		if (!counter_) 
			throw std::length_error(std::string("[") + __FUNCTION__ + "] Stack length error\n");

		--counter_;

		HASH_GUARD(rehash();)

		GUARD_CHECK()
	}

	template<typename T>
	inline typename Stack<T>::crVal_ Stack<T>::top() const
	{
		GUARD_CHECK()

		if (!counter_) 
			throw std::out_of_range(std::string("[") + __FUNCTION__ + "] Stack out of range\n");

		GUARD_CHECK()

		return buffer_[counter_ - 1];
	}

	template<typename T>
	void Stack<T>::swap(Stack &rStack) noexcept(std::_Is_nothrow_swappable<T>::value)
	{
		GUARD_CHECK()

		using std::swap; // To have all possible swaps

		HASH_GUARD(swap(hash_, rStack.hash_);)

		swap(counter_, rStack.counter_);
		swap(size_, rStack.size_);

		swap(buffer_, rStack.buffer_);

		GUARD_CHECK()
	}

	template<typename T>
	inline bool Stack<T>::ok() const noexcept
	{
		return (CANARY_GUARD(canaryStart_ == CANARY_VALUE && canaryFinish_ == CANARY_VALUE && )
				HASH_GUARD(hash_ == makeHash() && )
				(size_ > counter_) && buffer_);		
	}

	template<typename T>
	template<typename Char, typename Traits>
	void Stack<T>::dump(std::basic_ostream<Char, Traits> &rOstr) const noexcept
	{
		try
        {
			rOstr << "\t[STACK DUMP]" << std::endl;
		    rOstr << "Stack <" << typeid(T).name() << "> [0x" << this << "]\n" //-V128
			      << "{\n\tbuffer [" << counter_ << "] = 0x" << buffer_.get() << "\n\t{\n";

		    if (counter_) for (size_t i = 0; i < counter_; ++i) rOstr << "\t\t[" << i << "] = " << std::setw(8) << buffer_[i] << std::endl; //-V128
		    else                                                rOstr << "\t\tempty\n";

		    rOstr << "\t}\n\n";

		    CANARY_GUARD
		    (
			    rOstr << "\tCANARY_VALUE  = " << CANARY_VALUE << std::endl;

			    rOstr << "\tCANARY_START  = " << canaryStart_;
			    if (canaryStart_ == CANARY_VALUE) rOstr << "  TRUE \n";
			    else                              rOstr << "  FALSE\n";

			    rOstr << "\tCANARY_FINISH = " << canaryFinish_;
			    if (canaryFinish_ == CANARY_VALUE) rOstr << "  TRUE \n";
			    else                               rOstr << "  FALSE\n";
			    )

		    HASH_GUARD
		    (
			    rOstr << "\n\tHASH = " << hash_;		
			    if (hash_ == makeHash()) rOstr << "  TRUE \n";
			    else                     rOstr << "  FALSE\n";
		    )

		    rOstr << "}\n";
			rOstr << "\t[   END    ]\n";
        }
        catch(...)
        {
            std::cerr << "Something went wrong in \"" << __FUNCTION__ << "\"! Goodbye!!!\n";
            
            terminate();    
        }
	}

#pragma endregion

} // namespace NStack

#endif /* __STACK_HPP_INCLUDED__ */