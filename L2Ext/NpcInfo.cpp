#include "StdAfx.h"
#include "Packets.h"

void CPacketFix::SendNpcInfo(CSocket *pSocket, const char *format, ...)
{
	CPacket Packet;
	va_list tag;
	va_start(tag, format);
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); 
		UINT objectId = va_arg(tag, DWORD);
/*d*/ Packet.WriteD(objectId);//ObjectId
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//NpcTypeId
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//IsAttackable
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//X
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//Y
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//Z
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//heading
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//mAtkSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//pAtkSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//runSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//walkSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//swimRunSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//swimWalkSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//flRunSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//flWalkSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//flyRunSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//flyWalkSpd
/*f*/ Packet.WriteF(va_arg(tag, double));//ProperMult
/*f*/ Packet.WriteF(va_arg(tag, double));//pAtkSpd
/*f*/ Packet.WriteF(va_arg(tag, double));//collisionRadius
/*f*/ Packet.WriteF(va_arg(tag, double));//collisionHeight
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//RHand
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//LHand
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //nameAbove
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //IsRunning?
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //IsInCombat?
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //IsAlikeDead?
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //IsSummoned?
/*S*/ Packet.WriteS(va_arg(tag, PWCHAR));//name
/*S*/ Packet.WriteS(va_arg(tag, PWCHAR));//title
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//karma
		
		DWORD AbnormalVisualEffect = va_arg(tag, DWORD);
		if(CNPC *pNpc = CNPC::GetNPCByServerId(&objectId))
		{
			if(pNpc->IsSummon() || pNpc->IsPet())
			{
				User *pMaster = pNpc->CastSummon()->GetMaster();
				if(pMaster->ValidUser())
				{
					if(pMaster->pED->spawnProtection == 2)
					{
						AbnormalVisualEffect |= 0x200000;
					}
				}
			}
		}
/*d*/ Packet.WriteD(AbnormalVisualEffect);//AbnormalEffect
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //unknown
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //Team
/*f*/ Packet.WriteF(va_arg(tag, double)); //collisRadius
/*f*/ Packet.WriteF(va_arg(tag, double)); //collisHeight
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//d
	va_end(tag);

	pSocket->Send("b", Packet.GetSize(), Packet.GetBuff());
}

void CPacketFix::BCSendNpcInfo(INT64 dwAddr, int nObjID, int nRange, FVector *pLocation, const char *format, ...)
{
	CPacket Packet;
	va_list tag;
	va_start(tag, format);
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); 
		UINT objectId = va_arg(tag, DWORD);
/*d*/ Packet.WriteD(objectId);//ObjectId
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//NpcTypeId
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//IsAttackable
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//X
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//Y
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//Z
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//heading
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//mAtkSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//pAtkSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//runSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//walkSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//swimRunSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//swimWalkSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//flRunSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//flWalkSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//flyRunSpd
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//flyWalkSpd
/*f*/ Packet.WriteF(va_arg(tag, double));//ProperMult
/*f*/ Packet.WriteF(va_arg(tag, double));//pAtkSpd
/*f*/ Packet.WriteF(va_arg(tag, double));//collisionRadius
/*f*/ Packet.WriteF(va_arg(tag, double));//collisionHeight
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//RHand
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//LHand
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //nameAbove
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //IsRunning?
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //IsInCombat?
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //IsAlikeDead?
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //IsSummoned?
/*S*/ Packet.WriteS(va_arg(tag, PWCHAR));//name
/*S*/ Packet.WriteS(va_arg(tag, PWCHAR));//title
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//karma
		
		DWORD AbnormalVisualEffect = va_arg(tag, DWORD);
		if(CNPC *pNpc = CNPC::GetNPCByServerId(&objectId))
		{
			if(pNpc->IsSummon() || pNpc->IsPet())
			{
				User *pMaster = pNpc->CastSummon()->GetMaster();
				if(pMaster->ValidUser())
				{
					if(pMaster->pED->spawnProtection == 2)
					{
						AbnormalVisualEffect |= 0x200000;
					}
				}
			}
		}
/*d*/ Packet.WriteD(AbnormalVisualEffect);//AbnormalEffect
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//0x00
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //unknown
/*c*/ Packet.WriteC(va_arg(tag, BYTE)); //Team
/*f*/ Packet.WriteF(va_arg(tag, double)); //collisRadius
/*f*/ Packet.WriteF(va_arg(tag, double)); //collisHeight
/*d*/ Packet.WriteD(va_arg(tag, DWORD));//d
	va_end(tag);

	BroadcastToNeighborExceptSelf(nObjID, nRange, pLocation, (int)Packet.GetSize(), Packet.GetBuff());
}