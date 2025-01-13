/*
*	������������ ����, ������������ ���� ���������� - ������� ������, ����� ������, ���� ���� ������ � ����. 
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
	STATUS_OK = 0,					//< �����
	STATUS_ERROR = 1,				//< ������ � ����� ����� ����
	STATUS_NOT_ENOUGH_MEMORY = 2,	//< ������������ ������
	STATUS_INVALID_PATH = 3,		//< ����� ����� ����� ������� ���� ��� ���� �� ������
} status_t;

typedef enum 
{
	STRIBOG256 = 0,		//< 256-������ �����
	STRIBOG512 = 1,		//< 512-������ �����
} StribogMod_t;

typedef struct 
{
	uint512_t buffer;			//<< ����� ��� ���������� ����� ����������� ���������
	uint512_t hash_completed;	//<< �������� ���
	uint512_t hash_current;		//<< ������������� ���������
	
	uint512_t N;				
	uint512_t control_sum;		//<< ��� �������� ����������� �����
	uint512_t IV_0;				//<< ������ �������������
	uint512_t IV_512;			//<< ������ �������������
	size_t tail_size;			//<< ������ ��������� �����, ������� ������� ���������

	StribogMod_t mod;			//<< �����
} HashContext_t;
