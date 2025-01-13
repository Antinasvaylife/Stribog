/*
*	������������ ���� ��� ���������� ������������������ API
*/

#include "core.h"

/*
*	@brief ������� ������������ ������������� �������� �����������
*	
*	@details ������� �� ������������ ��������� ���������, 
*			������ ��� ���� ������ ���� �������� �������
* 
*	@param[in, out] ctx - ��������� �� �������� �����������
*	@param[in] mod - ����� ������ ���������
*/
PUBLIC_FUNC status_t gost3411_HashInit(HashContext_t* ctx, StribogMod_t mod);

/*
*	@brief ������� ��������� ���� 2 ����������� �� ����-34.11
*
*	@param[in, out] ctx - ��������� �� �������� �����������
*	@param[in] data - ��������� �� ����� ������
*	@param[in] len - ����� ������ ������ � ������
*/
PUBLIC_FUNC status_t gost3411_HashUpdate(HashContext_t* ctx, const uint8_t* data, size_t len);

/*
*	@brief ������� ��������� ���� 3 ����������� �� ����-34.11
* 
*	@param[in, out] ctx - ��������� �� �������� �����������
*/
PUBLIC_FUNC status_t gost3411_HashFinalize(HashContext_t* ctx);
