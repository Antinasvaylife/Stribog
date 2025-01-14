/*
*	Заголовочный файл, определяющий ядро приложения - размеры блоков, типов данных, сами типы данных и проч. 
*/

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#define PUBLIC_FUNC extern

#define SBOX_SIZE 256
#define COUNT_OF_ROUNDS 12

#define BLOCK_BYTE_SIZE 64
#define BLOCK_QWORD_SIZE 8

#define QWORD_BIT_SIZE 64

#define FILE_BUFFER_SIZE 4096
#define MODE_256 256
#define MODE_512 512

typedef union
{
	uint8_t u8[BLOCK_BYTE_SIZE];
	uint64_t u64[BLOCK_QWORD_SIZE];
} uint512_t;

typedef enum
{
	STATUS_OK = 0,					//< Успех
	STATUS_ERROR = 1,				//< Ошибка в самом общем виде
	STATUS_NOT_ENOUGH_MEMORY = 2,	//< Недостаточно памяти
	STATUS_INVALID_PATH = 3,		//< Адрес файла задан неверно либо нет прав не чтение
} status_t;

typedef enum 
{
	STRIBOG256 = 0,		//< 256-битный режим
	STRIBOG512 = 1,		//< 512-битный режим
} StribogMod_t;

typedef struct 
{
	uint512_t buffer;			//<< буфер для очередного блока хэшируемого сообщения
	uint512_t hash_completed;	//<< итоговый хэш
	uint512_t hash_current;		//<< промежуточный результат
	
	uint512_t N;				
	uint512_t control_sum;		//<< для хранения контрольной суммы
	uint512_t IV_0;				//<< вектор инициализации
	uint512_t IV_512;			//<< вектор инициализации
	size_t tail_size;			//<< размер неполного блока, который придётся дополнять

	StribogMod_t mod;			//<< режим
} HashContext_t;
