#ifndef __SharedPtr_h
#define __SharedPtr_h


#pragma once
namespace DuiLib
{
	
	// 智能指针.
	template <class T>
	class SharedPtr
	{
		// 引用计数类.
		class shared_ref
		{
		public:
			shared_ref(int c = 0) : use_count(c) {}
			~shared_ref() {}

			// 增加引用计数, 并返回计数值.
			int addref() { return ++use_count; }
			// 减少引用计数, 并返回计数值.
			int release() { return --use_count; }

		private:
			// 计数变量.
			int use_count;
		};
	public:
		// 构造指针, 并使引用计数置为1.
		explicit SharedPtr (T* ptr) : p(ptr), u(new shared_ref(1))
		{}

		// 构造空指针.
		explicit SharedPtr () : p(NULL), u(NULL)
		{}

		// 智能指针析构.
		~SharedPtr (void)
		{
			// 如果引用计数等于0, 则删除数据和引用计数, 并置p为NULL.
			// 此处需要注意的是, 共用的u并未置为 NULL, 在其它指针析构
			// 时, p为NULL, 则不会重复delete.
			if (p && u->release() <= 0)
			{
				delete p;
				delete u;
				p = NULL;
			}		
		}

		// 智能指针拷贝构造函数.
		SharedPtr (const SharedPtr<T>& t)
		{
			p = t.p;
			u = t.u;

			if (u) // 必须判断空值.
			{
				u->addref();	// 增加引用计数.
			}
		}

		// 指针赋值.
		void operator = (SharedPtr<T>& t)
		{
			// 首先将引用计数减1, 然后再判断是否小于0, 如果小于0, 则delete.			
			if (p && u->release() <= 0)
			{
				delete p;
				delete u;
			}

			// 直接赋值.
			p = t.p;
			u = t.u;

			if (u)	// 必须判断空值.
			{
				u->addref(); // 增加引用计数.
			}
		}

		// 重载->操作和*操作符.
		T* operator -> (void) { return p; }
		T* operator -> (void) const { return p; }
		T& operator * (void) { return *p; }
		// 重载!操作符.
		bool operator ! () const { return !p;}

		// 重载指针bool值操作符.
		typedef SharedPtr<T> this_type;
		typedef T * this_type::*unspecified_bool_type;
		operator unspecified_bool_type() const { return !p ? 0: &this_type::p; }
		// 得到原指针.
		T* get() { return p; }
		void reset (T* ptr)
		{
			// 首先将引用计数减1, 然后再判断是否小于0, 如果小于0, 则delete.			
			if (p && u->release() <= 0)
			{
				delete p;
				delete u;
			}

			// 赋值, 如果是NULL, 则不创建引用计数.
			p = ptr;
			if (p)
				u = new shared_ref(1);
			else
				u = NULL;
		}

		void reset(SharedPtr<T>& t)
		{
			// 首先将引用计数减1, 然后再判断是否小于0, 如果小于0, 则delete.			
			if (p && u->release() <= 0)
			{
				delete p;
				delete u;
			}

			// 赋值.
			p = t.p;
			u = t.u;

			if (u)	// 必须判断空值.
			{
				u->addref(); // 增加引用计数.
			}
		}

	private:
		T* p;
		shared_ref* u;
	};

	// 重载==操作符.
	template<class T, class U> 
	inline bool operator == (SharedPtr<T> & a, SharedPtr<U> & b)
	{
		return a.get() == b.get();
	}

	// 重载!=操作符.
	template<class T, class U> 
	inline bool operator != (SharedPtr<T> & a, SharedPtr<U> & b)
	{
		return a.get() != b.get();
	}
	

};

#endif//__SharedPtr_h
