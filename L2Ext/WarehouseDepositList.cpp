#include "StdAfx.h"
#include "Packets.h"
#include "Augmentation.h"

int CPacketFix::WarehouseDepositListFix(PCHAR buff, int bufLen, const char *format, ...)
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
int CPacketFix::WarehouseDepositListExFix(PCHAR buff, int bufLen, const char *format, ...)
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

void CPacketFix::WarehouseDepositListSend(CSocket *pSocket, const char *format, ...)
{
	va_list tag;
	va_start(tag, format);
	//chdhb
	BYTE opCode = va_arg(tag, BYTE);
	WORD WhType = va_arg(tag, WORD);
	int Adena = va_arg(tag, int);
	WORD ItemCount = va_arg(tag, WORD);
	int BuffLen = va_arg(tag, int);
	PCHAR Buff = va_arg(tag, PCHAR);
	va_end(tag);
	CPacket packet;
	packet.WriteC(opCode);
	packet.WriteH(WhType);
	packet.WriteD(Adena);
	if(WhType > 1)
	{
		int nNewCount = 0;
		CPacket ItemBuff;
		for(int n=0;n<ItemCount;n++)
		{
			WORD ItemType = 0;
			DWORD ObjectID = 0;
			DWORD ItemID = 0;
			DWORD Count = 0;
			WORD ItemType2 = 0;
			WORD wUnkn = 0;
			DWORD BodyPart = 0;
			WORD Enchant = 0;
			WORD wUnkn2 = 0;
			WORD wUnkn3 = 0;
			DWORD DatabaseID = 0;
			
			Buff = (PCHAR)Disassemble((const unsigned char*)Buff, "hdddhhdhhhd", &ItemType, &ObjectID, &ItemID, &Count, &ItemType2,
				&wUnkn, &BodyPart, &Enchant, &wUnkn2, &wUnkn3, &DatabaseID);
			
			CItem *pItem = CObject::GetObjectBySID(ObjectID)->CastItem();
			
			if(pItem->IsValidItem())
			{
				if(pItem->nProtectionTimeout > time(0))
				{
					continue;
				}else
				{
					nNewCount++;
					ItemBuff.WriteH(ItemType);
					ItemBuff.WriteD(ObjectID);
					ItemBuff.WriteD(ItemID);
					ItemBuff.WriteD(Count);
					ItemBuff.WriteH(ItemType2);
					ItemBuff.WriteH(wUnkn);
					ItemBuff.WriteD(BodyPart);
					ItemBuff.WriteH(Enchant);
					ItemBuff.WriteH(wUnkn2);
					ItemBuff.WriteH(wUnkn3);
					ItemBuff.WriteD(DatabaseID);					
				}
			}
		}
		packet.WriteH(nNewCount);
		packet.WriteB((int)ItemBuff.GetSize(), ItemBuff.GetBuff());
	}
	else
	{
		packet.WriteH(ItemCount);
		packet.WriteB(BuffLen, Buff);
	}
	pSocket->Send("b", packet.GetSize(), packet.GetBuff());
}