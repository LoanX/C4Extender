#include "StdAfx.h"
#include "Packets.h"
#include "Augmentation.h"

extern UINT g_WareHouseAugmentationId[32];

int CPacketFix::WarehouseWithdrawList(PCHAR buff, int bufLen, const char *format, ...)
{
	va_list tag;
	va_start (tag, format);
	//hdddhhdhhhd
	WORD ItemType = va_arg(tag, WORD);
	DWORD ObjectID = va_arg(tag, DWORD);
	DWORD ItemID = va_arg(tag, DWORD);
	DWORD Count = va_arg(tag, DWORD);
	WORD ItemType2 = va_arg(tag, WORD);
	WORD wUnkn = va_arg(tag, WORD);
	DWORD BodyPart = va_arg(tag, DWORD);
	WORD Enchant = va_arg(tag, WORD);
	WORD wUnkn2 = va_arg(tag, WORD);
	WORD wUnkn3 = va_arg(tag, WORD);
	DWORD DatabaseID = va_arg(tag, DWORD);
	va_end (tag);
	char * newFormat = "hdddhhdhhhd"; //C4 Format
	UINT currentIdx = GetThreadIndex();
	if(currentIdx < 32)
	{		
		g_WareHouseAugmentationId[currentIdx] = 0;
		return Assemble(buff, bufLen, newFormat, ItemType, ObjectID, ItemID, Count, ItemType2, wUnkn
			,BodyPart, Enchant, wUnkn2, wUnkn3, DatabaseID);
	}else
	{
		g_Log.Add(CLog::Error, "[%s] Invalid thread index[%d]!", __FUNCTION__, currentIdx);
		return Assemble(buff, bufLen, newFormat, ItemType, ObjectID, ItemID, Count, ItemType2, wUnkn
			,BodyPart, Enchant, wUnkn2, wUnkn3, DatabaseID);
	}
}
int CPacketFix::WarehouseWithdrawListEx(PCHAR buff, int bufLen, const char *format, ...)
{
	va_list tag;
	va_start (tag, format);
	//hdddhhdhhhd
	WORD ItemType = va_arg(tag, WORD);
	DWORD ObjectID = va_arg(tag, DWORD);
	DWORD ItemID = va_arg(tag, DWORD);
	DWORD Count = va_arg(tag, DWORD);
	WORD ItemType2 = va_arg(tag, WORD);
	WORD wUnkn = va_arg(tag, WORD);
	DWORD BodyPart = va_arg(tag, DWORD);
	WORD Enchant = va_arg(tag, WORD);
	WORD wUnkn2 = va_arg(tag, WORD);
	WORD wUnkn3 = va_arg(tag, WORD);
	DWORD DatabaseID = va_arg(tag, DWORD);
	va_end (tag);
	char * newFormat = "hdddhhdhhhd"; //C4 Format
	
	return Assemble(buff, bufLen, newFormat, ItemType, ObjectID, ItemID, Count, ItemType2, wUnkn
		,BodyPart, Enchant, wUnkn2, wUnkn3, DatabaseID);
}