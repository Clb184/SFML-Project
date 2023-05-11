#pragma once
#include <SFML/System.hpp>
typedef enum {
	//Math stuff
	PUSHC, //Push integer
	PUSHR, //	Register
	//PUSHV, //	Variable

	POPR, //Pop to Register
	//POPV, //	Variable

	MOVC, //Move to register
	MOVR,

	ADDI, //Pop for operation
	ADDF, //2
	SUBI,
	SUBF,
	MULI,
	MULF,
	DIVI,
	DIVF,
	MOD,

	SIN, //1
	COS, //1
	ATAN2I, //
	ATAN2F,
	HYPOTI,
	HYPOTF,
	NORMRAD,//1

	NEGI,
	NEGF,
	ITOF,
	FTOI,
	SHL,
	SHR,

	EQI,
	EQF,
	NEQI,
	NEQF,
	GREATI,
	GREATF,
	GEQI,
	GEQF,
	LESSI,
	LESSF,
	LEQI,
	LEQF,

	AND,
	OR,
	XOR,
	NOT,

	CRAND, // This does rand() % MOD
	RANDI, // These others add a random number onto the stack
	RANDF,
	RANDANG,

	//System stuff
	NOP = 100,
	JMP,
	TJMP,
	FJMP,
	CALL,
	RET,
	SETINTERRUPT,
	RETCODE, //Use only for specific stuff pls.

	//Enemy stuff
	ENMCREATE = 200,

	//Sprite stuff
	SETSLOT = 300,
	SETSPRITE, //1 Param (Pop)
	SETCOLOR, //3 Params (R, G, B) (Pop)
	SETALPHA, //1 Param
	SETDRAWLAYER,
	SETSPRITEBLEND,

	//Audio stuff
	PLAYMUSIC = 400,
	PAUSEMUSIC,
	RESUMEMUSIC,
	STOPMUSIC,
	ADDVOLUME,
	SETVOLUME,
	PLAYSOUND,
} ScriptCommand;

typedef enum {
	ERET_FORCEKILL = -3,
	ERET_KILL,
	ERET_NORMAL,
	ERET_EXIT,
	ERET_RESUME,
	ERET_RELOAD,
	ERET_CHANGE
} ReturnCodeEnm;

typedef struct {
	uint32_t command;
	uint32_t length;
	uint32_t paramCnt;
} ScriptInstruction;


/*
*Estructura del archivo de script:
* 
* 1.- Strings terminados en 0x00 para cargar archivos de animaci�n.
* 2.- Strings para archivos de audio a cargar.
* 3.- Inicio del archivo de script.
* 
*/

/* Defined Structure for the script file (2023/04/01)
* CSTR TextFileMaster -> Text stuff
* CSTR ShaderFileMaster -> 
* CSTR SoundFileMaster
* CSTR MusicFileMaster
* CSTR SpriteFileMaster
* uint32_t ScriptFlags
* constant(float/int)* commands. 
* 
* CSTR stands for null terminated string (C String)
*/