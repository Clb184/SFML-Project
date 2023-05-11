#pragma once
#include "Commons.h"
#include <random>
#define STACK_MAX 1024

class CalcStack {
public:
	template<typename T>
	static inline void push(T val) {
		size_t ptr = ++m_StackPtr;
		if ((ptr) <= STACK_MAX) {
			m_pStack[ptr] = T(val);
		}
	}
	template<typename T>
	static inline T pop() {
		size_t ptr = m_StackPtr--;
		if ((ptr) > 0) {
			return T(m_pStack[ptr]);
		}
		else {
			return -1;
		}
	}

	//Simplifying life with lambdas!
	template<typename T, typename FN>
	static inline bool single_op(const FN& func) {
		if (const size_t ptr = m_StackPtr) {
			m_pStack[ptr] = T(func(m_pStack[ptr]));
			return true;
		}
		return false;
	}

	template<typename T, typename FN>
	static inline bool dual_op(const FN& func) {
		const size_t ptr = m_StackPtr - 1;
		if (ptr > 0) {
			T lval1 = m_pStack[ptr], lval2 = m_pStack[ptr + 1];
			m_pStack[ptr] = T(func(lval1, lval2));
			m_StackPtr--;
			return true;
		}
		return false;
	}

	//Math operations
	template<typename T>
	static inline void add() {
		dual_op<T>([](T val1, T val2) {
			return T(T(val1) + T(val2));
			});
	}

	template<typename T>
	static inline void sub() {
		dual_op<T>([](T val1, T val2) {
			return T(T(val1) - T(val2));
			});

	}

	template<typename T>
	static inline void mul() {
		dual_op<T>([](T val1, T val2) {
			return T(T(val1) * T(val2));
			});

	}

	template<typename T>
	static inline void div() {
		dual_op<T>([](T val1, T val2) {
			return T(T(val1) / T(val2));
			});

	}

	static inline void mod() {
		dual_op<int>([](int val1, int val2) {
			return val1 % val2;
			});
	}

	static inline void sin() {
		single_op<float>([](float val1) {
			return float(sinf(float(val1)));
			});
	}
	static inline void cos() {
		single_op<float>([](float val1) {
			return float(cosf(float(val1)));
			});
	}

	template<typename T>
	static inline void atan2() {
		dual_op<T>([](T val1, T val2) {
			return T(atan2f(T(val1), T(val2)));
			});

	}

	template<typename T>
	static inline void hypot() {
		dual_op<T>([](T val1, T val2) {
			return T(hypotf(T(val1), T(val2)));
			});

	}

	static inline void normrad() {
		float ang;
		if (m_StackPtr > 0) {
			ang = m_pStack[m_StackPtr];
			if (ang <= PI && ang >= -PI) {
				ang = remainderf(ang, 2 * PI);
				m_pStack[m_StackPtr] = ang;
			}
		}
	}

	template<typename T>
	static inline void neg() {
		single_op<T>([](T val1) {
			return T(-T(val1));
			});

	}

	static inline void ftoi() {
		if (const size_t ptr = m_StackPtr) {
			m_pStack[ptr] = int(float(m_pStack[ptr]));
		}

	}

	static inline void itof() {
		if (const size_t ptr = m_StackPtr) {
			m_pStack[ptr] = float(int(m_pStack[ptr]));
		}

	}

	static inline void shl() {
		dual_op<int>([](int val1, int val2) {
			return int(int(val1) << int(val2));
			});

	}
	static inline void shr() {
		dual_op<int>([](int val1, int val2) {
			return int(int(val1) >> int(val2));
			});

	}

	template<typename T>
	static inline void eq() {
		if(dual_op<T>([](T val1, T val2) {
			return int(T(val1) == T(val2));
			}))
			m_pStack[m_StackPtr] = int(1);

	}
	template<typename T>
	static inline void neq() {
		if (dual_op<T>([](T val1, T val2) {
			return int(T(val1) != T(val2));
			}))
			m_pStack[m_StackPtr] = int(1);

	}
	template<typename T>
	static inline void great() {
		if (dual_op<T>([](T val1, T val2) {
			return int(T(val1) > T(val2));
			}))
			m_pStack[m_StackPtr] = int(1);

	}
	template<typename T>
	static inline void geq() {
		if (dual_op<T>([](T val1, T val2) {
			return int(T(val1) >= T(val2));
			}))
			m_pStack[m_StackPtr] = int(1);

	}
	template<typename T>
	static inline void less() {
		if (dual_op<T>([](T val1, T val2) {
			return int(T(val1) < T(val2));
			}))
			m_pStack[m_StackPtr] = int(1);

	}
	template<typename T>
	static inline void leq() {
		if (dual_op<T>([](T val1, T val2) {
			return int(T(val1) <= T(val2));
			}))
			m_pStack[m_StackPtr] = int(1);

	}

	static inline void andop() {
		dual_op<int>([](int val1, int val2) {
			return int(int(val1) & int(val2));
			});

	}
	static inline void orop() {
		dual_op<int>([](int val1, int val2) {
			return int(int(val1) | int(val2));
			});

	}
	static inline void xorop() {
		dual_op<int>([](int val1, int val2) {
			return int(int(val1) ^ int(val2));
			});
	}
	static inline void notop() {
		single_op<int>([](int val1) {
			return int(!int(val1));
			});
	}

	static inline void crand() {
		single_op<int>([](int val1) {
			return rand() % val1;
			});
	}

	static inline void randi() {
		std::uniform_int_distribution<int> intRandDev(-999999999999, 999999999999);
		const size_t ptr = ++m_StackPtr;
		if (ptr < STACK_MAX) {
			m_pStack[ptr] = intRandDev(m_RandDev);
		}
	}

	static inline void randf() {
		std::uniform_real_distribution<float> floatRandDev(-999999999999.9f, 999999999999.9f); 
		const size_t ptr = ++m_StackPtr;
		if (ptr < STACK_MAX) {
			m_pStack[ptr] = floatRandDev(m_RandDev);
		}
	}

	static inline void randAng() {
		std::uniform_real_distribution<float> floatRandDev(-PI, PI);
		const size_t ptr = ++m_StackPtr;
		if (ptr < STACK_MAX) {
			m_pStack[ptr] = floatRandDev(m_RandDev);
		}
	}

	CalcStack() { m_StackPtr = 0; }
	~CalcStack() {}
private:
	//Stack Pointer...
	static size_t m_StackPtr;

	static std::random_device m_RandDev;
	static constant m_pStack[STACK_MAX];
};
