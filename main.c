/*
*	Программа вычисляет хэш файла или строки по ГОСТ-34.11 "Стрибог"
* 
*	Файл содержит функцию main, функции для вычисления хэша строки или файла, всевозможные принтеры и проч.
* 
*	Воробьёв Денис, 2025 год
*/

#include "main.h"
#pragma warning(disable : 4996) //< Компилятор на стандарте MSVC ругается за использование fopen

/*
*	@brief Функция печатает справочное сообщение в стандартный вывод 
*/
static void printHelpMessage() 
{
	printf("%s\n", "This program calculates hash of file or string using gost 34.11 STRIBOG");
	printf("%s\n", "Usage: stribog [-h(elp)] [-m(ode)] [[-f(ile) <path_to_file>] | [-s(tring) <string_to_hash>]]");
	printf("%s\n", "Default hash size is 512 bit, use -m to set 256 bit mode");
	printf("%s\n", "Program puts hash to stdout");
	printf("%s\n", "Vorobyov Denis, MIREA");
}

/*
*	@brief Функция печатает статус операции хэширования в стандартный вывод
*/
static void printStatus(status_t status) 
{
	switch (status) 
	{
	case STATUS_OK:
		printf("%s\n", "OK!");
		break;
	case STATUS_ERROR:
		printf("%s\n", "ERROR!");
		break;
	case STATUS_NOT_ENOUGH_MEMORY:
		printf("%s\n", "ERROR! Not enough memory.");
		break;
	case STATUS_INVALID_PATH:
		printf("%s\n", "ERROR! Invalid path.");
		break;
	}
}

/*
*	@brief Функция печатает вычисленный хэш в стандартный вывод
*/
static status_t printHash(HashContext_t* ctx)
{
	int i = 0;
	if (ctx) 
	{
		switch (ctx->mod) 
		{
		case STRIBOG256:
			printf("%d-bit stribog hash sum: \n", MODE_256);
			for (i = BLOCK_BYTE_SIZE - 1; i >= BLOCK_BYTE_SIZE / 2; i--) 
			{
				printf("%02x", ctx->hash_completed.u8[i]);
			}
			break;
		case STRIBOG512:
			printf("%d-bit stribog hash sum: \n", MODE_512);
			for (i = BLOCK_BYTE_SIZE - 1; i >= 0 ; i--)
			{
				printf("%02x", ctx->hash_completed.u8[i]);
			}
			break;
		default:
			return STATUS_ERROR;
		}
		return STATUS_OK;
	}
	else 
	{
		return STATUS_ERROR;
	}
}

/*
*	@brief Функция вычисляет хэш файла
*/
static status_t calculateHashFile(const char* file_name, HashContext_t* ctx, StribogMod_t mod) 
{
	FILE* file;
	uint8_t* buffer;
	size_t len;
	gost3411_HashInit(ctx, mod);
	if ((file = fopen(file_name, "rb")) != NULL) 
	{
		if ((buffer = malloc((size_t)FILE_BUFFER_SIZE)) != NULL) 
		{
			while ((len = fread(buffer, (size_t)1, (size_t)FILE_BUFFER_SIZE, file)))
			{
				gost3411_HashUpdate(ctx, buffer, len);
			}
			free(buffer);
			gost3411_HashFinalize(ctx);
			return STATUS_OK;
		}
		else 
		{
			return STATUS_NOT_ENOUGH_MEMORY;
		}
	}
	else 
	{
		return STATUS_INVALID_PATH;
	}
}

/*
*	@brief Функция вычисляет хэш строки
*/
static status_t calculateHashString(const char* string, HashContext_t* ctx, StribogMod_t mod)
{
	uint8_t* buffer;
	if ((buffer = malloc(strlen(string))) != NULL) 
	{
		memcpy(buffer, string, strlen(string));
		gost3411_HashInit(ctx, mod);
		gost3411_HashUpdate(ctx, buffer, strlen(string));
		gost3411_HashFinalize(ctx);
		free(buffer);
		return STATUS_OK;
	}
	else 
	{
		return STATUS_NOT_ENOUGH_MEMORY;
	}
}

/*
*	@brief Функция зачищает структуру контекста
*/
static void freeContext(HashContext_t* ctx)
{
	if (ctx) 
	{
		memset(ctx, 0x00, sizeof(*ctx));
	}
}

int main(int argc, char* argv[])
{
	HashContext_t ctx = {0};
	StribogMod_t mod = STRIBOG512;
	status_t status = STATUS_OK;

	int optind;
	for (optind = 1; optind < argc && argv[optind][0] == '-'; optind++) {
		switch (argv[optind][1]) 
		{
		case 'h':
			printHelpMessage();
			return;
			break;
		case 'm':
			mod = STRIBOG256;
			break;
		case 'f':
			if ((status = calculateHashFile(argv[optind + 1], &ctx, mod)) != STATUS_OK) 
			{
				printStatus(status);
				return 0;
			}
			if ((status = printHash(&ctx)) != STATUS_OK) 
			{
				printStatus(status);
				return 0;
			}
			freeContext(&ctx);
			return;
		case 's':
			if ((status = calculateHashString(argv[optind + 1], &ctx, mod)) != STATUS_OK)
			{
				printStatus(status);
				return 0;
			}
			if ((status = printHash(&ctx)) != STATUS_OK)
			{
				printStatus(status);
				return 0;
			}
			freeContext(&ctx);
			return;
		default:
			printHelpMessage();
			break;
		}
	}

	printHelpMessage();

	return 0;
}
