#include "CalcStack.h"


size_t CalcStack::m_StackPtr;
constant CalcStack::m_pStack[STACK_MAX];
std::random_device CalcStack::m_RandDev;
/*
template<typename T>
inline void CalcStack::push

template<typename T>
inline T CalcStack::pop() 

//Math Operations

template<typename T, typename FN>
inline void CalcStack::single_op

template<typename T, typename FN>
inline void CalcStack::dual_op(const FN& func) 

template<typename T>
inline void CalcStack::add()

template<typename T>
inline void CalcStack::sub() 

template<typename T>
inline void CalcStack::mul() 

template<typename T>
inline void CalcStack::div() 

/// <summary>
/// ///////////////////
/// </summary>

inline void CalcStack::sin() 

inline void CalcStack::cos() 

template<typename T>
inline void CalcStack::atan2() 

template<typename T>
inline void CalcStack::hypot() 

inline void CalcStack::normrad() 

template<typename T>
inline void CalcStack::neg() 

inline void CalcStack::ftoi() 

inline void CalcStack::itof()

inline void CalcStack::shl() 

inline void CalcStack::shr() {
	dual_op<int>([](int val1, int val2) {
		return int(int(val1) >> int(val2));
		});

}

template<typename T>
inline void CalcStack::eq() 

template<typename T>
inline void CalcStack::neq() {
	dual_op<T>([](T val1, T val2) {
		return int(T(val1) != T(val2));
		});

}

template<typename T>
inline void CalcStack::great() {
	dual_op<T>([](T val1, T val2) {
		return int(T(val1) > T(val2));
		});

}

template<typename T>
inline void CalcStack::geq() {
	dual_op<T>([](T val1, T val2) {
		return int(T(val1) >= T(val2));
		});

}

template<typename T>
inline void CalcStack::less() {
	dual_op<T>([](T val1, T val2) {
		return int(T(val1) < T(val2));
		});

}

template<typename T>
inline void CalcStack::leq() {
	dual_op<T>([](T val1, T val2) {
		return int(T(val1) <= T(val2));
		});

}

inline void CalcStack::andop() 

inline void CalcStack::orop() 

inline void CalcStack::xorop() 

inline void CalcStack::notop() 
*/
