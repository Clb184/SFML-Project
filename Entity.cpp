#include <random>
#include "Entity.h"


void Entity::scriptRead(CAnmContainer* anm_cont) {
	uint32_t temp[8] = {};
	float tempf[8] = {};
	bool jmp;

	uint32_t *pPos, *pTemp;

Cmd:
	while (1) {
		pPos = (uint32_t*)(this->p_Script + (this->m_Offset));
		switch (pPos[0]) {
		case NOP:
			if (!this->m_Rep) {
				this->m_Rep = CalcStack.top();
				CalcStack.pop();
				return;
			}
			if (--this->m_Rep)
				return;
			else
				this->m_Offset++;
			break;

		case JMP:
			this->m_Offset = pPos[1];
			break;

		case JMPT:
			jmp = CalcStack.top();
			CalcStack.pop();
			goto jump;
		case JMPF:
			jmp = !CalcStack.top();
			CalcStack.pop();
		jump:
			if (jmp) 
				this->m_Offset = pPos[1];
			else
				this->m_Offset += 2;
			break;

		case CALL:
			this->m_RetStack.push(this->m_Offset + 2);
			this->m_Offset = pPos[1];
			break;
		case RET:
			this->m_Offset = this->m_RetStack.top();
			this->m_RetStack.pop();
			break;
		case PUSHC:
			CalcStack.push(pPos[1]);
			this->m_Offset += 2;
			break;
		case PUSHR:
			temp[1] = (int)( &this->m_x + (pPos[1]));
			temp[0] = *(uint32_t*)(temp[1]);
			CalcStack.push(temp[0]);
			this->m_Offset += 2;
			break;

		case POP:
			pTemp = (uint32_t*)(&this->m_x + (pPos[1])); 
			*pTemp = CalcStack.top();
			CalcStack.pop();
			this->m_Offset += 2;
			break;

		case MOVC:

			pTemp = (uint32_t*)(&this->m_x + (pPos[1]));
			*pTemp = pPos[2];
			this->m_Offset += 3;
			break;
		
		case MOVR:

			pTemp = (uint32_t*)(&this->m_x + (pPos[1]));
			*pTemp = *(uint32_t*)(&this->m_x + (pPos[2]));
			this->m_Offset += 3;
			break;


		case ADDI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() += temp[0];
			this->m_Offset++;
			break;
		case SUBI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() -= temp[0];
			this->m_Offset++;
			break;
		case MULI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() *= temp[0];
			this->m_Offset++;
			break;
		case DIVI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() /= temp[0];
			this->m_Offset++;
			break;
		case MODI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() %= temp[0];
			this->m_Offset++;
			break;
		case SHL:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() <<= temp[0];
			this->m_Offset++;
			break;
		case SHR:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() >>= temp[0];
			this->m_Offset++;
			break;
		case AND:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = CalcStack.top() & temp[0];
			this->m_Offset++;
			break;
		case OR:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = CalcStack.top() | temp[0];
			this->m_Offset++;
			break;

		case XOR:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = CalcStack.top() ^ temp[0];
			this->m_Offset++;
			break;
		case NOTI:
			CalcStack.top() = ~CalcStack.top();
			this->m_Offset++;
			break;

		case MAXI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = (CalcStack.top() > temp[0]) ? CalcStack.top() : temp[0];
			this->m_Offset++;
			break;
		case MINI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = (CalcStack.top() < temp[0]) ? CalcStack.top() : temp[0];
			this->m_Offset++;
			break;
		case ATANI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = atan2(CalcStack.top(), temp[0]);
			this->m_Offset++;
			break;
		case HYPOTI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = hypot(CalcStack.top(), temp[0]);
			this->m_Offset++;
			break;
		case POWI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = pow(CalcStack.top(), temp[0]);
			this->m_Offset++;
			break;
		case EQUI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = CalcStack.top() == temp[0];
			this->m_Offset++;
			break;
		case NEQI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = CalcStack.top() != temp[0];
			this->m_Offset++;
			break;
		case GREATI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = CalcStack.top() > temp[0];
			this->m_Offset++;
			break;
		case GEQI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = CalcStack.top() >= temp[0];
			this->m_Offset++;
			break;
		case LESSI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = CalcStack.top() < temp[0];
			this->m_Offset++;
			break;
		case LEQI:
			temp[0] = CalcStack.top();
			CalcStack.pop();
			CalcStack.top() = CalcStack.top() <= temp[0];
			this->m_Offset++;
			break;
		case RNDI:
			temp[0] = CalcStack.top();
			CalcStack.top() = rand() % temp[0];
			this->m_Offset++;
			break;
		case FTOI:
			temp[0] = CalcStack.top();
			memcpy(&tempf[0], &temp[0], 4);
			temp[0] = tempf[0];
			CalcStack.top() = temp[0];
			this->m_Offset++;
			break;
		case ADDF:
		case SUBF:
		case MULF:
		case DIVF:
		case MAXF:
		case MINF:
		case ATANF:
		case HYPOTF:
		case POWF:
		case EQUF:
		case NEQF:
		case GREATF:
		case GEQF:
		case LESSF:
		case LEQF:
			tempf[0] = (float)CalcStack.top();
			CalcStack.pop();
			tempf[1] = (float)CalcStack.top();
			//memcpy(&tempf[0], &temp[0], 4);
			//memcpy(&tempf[1], &temp[1], 4);
			goto Float_op;
		case COS:
		case SIN:
		case SQRTF:
		case NEGF:
		case RNDF:
			temp[0] = CalcStack.top();
			memcpy(&tempf[0], &temp[0], 4);
			goto Float_op;
		case ITOF:
			tempf[0] = CalcStack.top();
			memcpy(&temp[0], &tempf[0], 4);
			CalcStack.top() = temp[0];
			this->m_Offset++;
			break;
		}
	}

Float_op:

	switch (pPos[0]) {
	case ADDF:
		tempf[1] += tempf[0];
		break;
	case SUBF:
		tempf[1] -= tempf[0];
		break;
	case MULF:
		tempf[1] *= tempf[0];
		break;
	case DIVF:
		tempf[1] /= tempf[0];
		break;
	case MAXF:
		tempf[1] = (tempf[0] > tempf[1]) ? tempf[0]: tempf[1];
		break;
	case MINF:
		tempf[1] = (tempf[0] < tempf[1]) ? tempf[0] : tempf[1];
		break;
	case COS:
		tempf[1] = cos(tempf[0]);
		break;
	case SIN:
		tempf[1] = sin(tempf[0]);
		break;
	case ATANF:
		tempf[1] = atan2(tempf[1], tempf[0]);
		break;
	case HYPOTF:
		tempf[1] = hypot(tempf[1], tempf[0]);
		break;
	case SQRTF:
		tempf[1] = sqrtf(tempf[0]);
		break;
	case POWF:
		tempf[1] = pow(tempf[1], tempf[0]);
		break;
	case NEGF:
		tempf[1] = -tempf[0];
		break;
	case EQUF:
		tempf[1] = tempf[1] == tempf[0];
		break;
	case NEQF:
		tempf[1] = tempf[1] != tempf[0];
		break;
	case GREATF:
		tempf[1] = tempf[1] > tempf[0];
		break;
	case GEQF:
		tempf[1] = tempf[1] >= tempf[0];
		break;
	case LESSF:
		tempf[1] = tempf[1] < tempf[0];
		break;
	case LEQF:
		tempf[1] = tempf[1] <= tempf[0];
		break;
	}

	memcpy(&temp[0], &tempf[1], 4);
	CalcStack.top() = temp[0];
	this->m_Offset++;
	goto Cmd;
}