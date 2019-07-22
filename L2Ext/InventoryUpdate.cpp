#include "StdAfx.h"
#include "Packets.h"

int InventoryUpdateFix(PCHAR buf, int bufLen, CItem *pItem, WORD UpdateType, WORD ItemType, DWORD ObjectID, DWORD ItemID, DWORD Count, WORD ItemType2, WORD CustomType1, WORD IsEquiped, DWORD BodyPart, WORD EnchantLevel, WORD CustomType2)
{
	// Old FMT:			 "hhdddhhhdhh"
	//const char *format = "hhdddhhhdhhdd"; //New IL Format
	const char *format = "hhdddhhhdhh"; //C4
		
	return Assemble(buf, bufLen, format, UpdateType, ItemType, ObjectID, ItemID, Count, ItemType2
		,CustomType1, IsEquiped, BodyPart, EnchantLevel, CustomType2);
}