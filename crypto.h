/*
*	Заголовочный файл для декларации криптографического API
*/

#include "core.h"

/*
*	@brief Функция осуществляет инициализацию операции хэширования
*	
*	@details Функция НЕ осуществляет аллокацию контекста, 
*			память под него должна быть выделена заранее
* 
*	@param[in, out] ctx - Указатель на контекст хэширования
*	@param[in] mod - Режим работы алгоритма
*/
PUBLIC_FUNC status_t gost3411_HashInit(HashContext_t* ctx, StribogMod_t mod);

/*
*	@brief Функция запускает Этап 2 хэширования по ГОСТ-34.11
*
*	@param[in, out] ctx - Указатель на контекст хэширования
*	@param[in] data - Указатель на буфер данных
*	@param[in] len - Длина буфера данных в байтах
*/
PUBLIC_FUNC status_t gost3411_HashUpdate(HashContext_t* ctx, const uint8_t* data, size_t len);

/*
*	@brief Функция запускает Этап 3 хэширования по ГОСТ-34.11
* 
*	@param[in, out] ctx - Указатель на контекст хэширования
*/
PUBLIC_FUNC status_t gost3411_HashFinalize(HashContext_t* ctx);
