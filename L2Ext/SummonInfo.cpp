#include "StdAfx.h"
#include "Packets.h"

void CPacketFix::SendSummonStatusFix(CSocket *pSocket, const char *format, ...)
{
	g_Log.Add(CLog::Blue,"[%s]",__FUNCTION__);
	CPacket Packet;
	va_list va;
	va_start(va, format);
/*c*/	Packet.WriteC(va_arg(va, BYTE)); //header
/*d*/	int nSummonType = va_arg(va, DWORD);
		Packet.WriteD(nSummonType); // SummonType
/*d*/	Packet.WriteD(va_arg(va, DWORD)); //ObjectID
/*d*/	Packet.WriteD(va_arg(va, DWORD)); //x
/*d*/	Packet.WriteD(va_arg(va, DWORD)); //y
/*d*/	Packet.WriteD(va_arg(va, DWORD)); //z
/*S*/	Packet.WriteS(va_arg(va, PWCHAR)); //caption
/*d*/	Packet.WriteD(va_arg(va, DWORD)); // current feed
/*d*/	Packet.WriteD(va_arg(va, DWORD)); // max feed
/*d*/	Packet.WriteD(va_arg(va, DWORD)); //current hp
/*d*/	Packet.WriteD(va_arg(va, DWORD)); //max hp
/*d*/	Packet.WriteD(va_arg(va, DWORD)); //current mp
/*d*/	Packet.WriteD(va_arg(va, DWORD)); //max mp
/*d*/	int nLevel = va_arg(va, DWORD);
		Packet.WriteD(nLevel); //level
/*d*/	INT64 nExp = va_arg(va, DWORD);
		Packet.WriteQ(nExp); //exp
/*d*/	INT64 nLowestExp = va_arg(va, DWORD);
		Packet.WriteQ(nLowestExp); //lowest exp
/*d*/	INT64 nHighestExp = va_arg(va, DWORD);
		Packet.WriteQ(nHighestExp); //highest exp
	va_end(va);
	pSocket->Send("b", Packet.GetSize(), Packet.GetBuff());
};
void CPacketFix::SendSummonInfo(CSocket *pSocket, const char *format, ...)
{
	
	
	CPacket Packet;
	va_list va;
	va_start(va, format);
/*c*/	Packet.WriteC(va_arg(va, BYTE));//0xb1
/*d*/	int nSummonType = va_arg(va, DWORD);
		Packet.WriteD(nSummonType);//SummonType
/*d*/	Packet.WriteD(va_arg(va, DWORD));//ObjectId
/*d*/	Packet.WriteD(va_arg(va, DWORD));//template
/*d*/	Packet.WriteD(va_arg(va, DWORD));//attackable? 1 or 0
/*d*/	Packet.WriteD(va_arg(va, DWORD));//X
/*d*/	Packet.WriteD(va_arg(va, DWORD));//Y
/*d*/	Packet.WriteD(va_arg(va, DWORD));//Z
/*d*/	Packet.WriteD(va_arg(va, DWORD));//heading
/*d*/	Packet.WriteD(va_arg(va, DWORD));//0
/*d*/	Packet.WriteD(va_arg(va, DWORD));//mAtkSpd
/*d*/	Packet.WriteD(va_arg(va, DWORD));//pAtkSpd
/*d*/	Packet.WriteD(va_arg(va, DWORD));//RunSpd
/*d*/	Packet.WriteD(va_arg(va, DWORD));//WalkSpd
/*d*/	Packet.WriteD(va_arg(va, DWORD));//swimRunSpd
/*d*/	Packet.WriteD(va_arg(va, DWORD));//swimWalkSpd
/*d*/	Packet.WriteD(va_arg(va, DWORD));//flRunSpd
/*d*/	Packet.WriteD(va_arg(va, DWORD));//flWalkSpd
/*d*/	Packet.WriteD(va_arg(va, DWORD));//flyRunSpd
/*d*/	Packet.WriteD(va_arg(va, DWORD));//flyWalkSpd
/*f*/	Packet.WriteF(va_arg(va, double));//properMult
/*f*/	Packet.WriteF(va_arg(va, double));//pAtkSpdMult
/*f*/	Packet.WriteF(va_arg(va, double));//colliRadius
/*f*/	Packet.WriteF(va_arg(va, double));//colliHeight
/*d*/	Packet.WriteD(va_arg(va, DWORD));//RightHand Weapon
/*d*/	Packet.WriteD(va_arg(va, DWORD));//0
/*d*/	Packet.WriteD(va_arg(va, DWORD));//LeftHand Weapon
/*c*/	Packet.WriteC(va_arg(va, BYTE));//NameAbove?
/*c*/	Packet.WriteC(va_arg(va, BYTE));//IsRunning?
/*c*/	Packet.WriteC(va_arg(va, BYTE));//IsInCombat?
/*c*/	Packet.WriteC(va_arg(va, BYTE));//IsAliveDead?
/*c*/	Packet.WriteC(va_arg(va, BYTE));//IsSummonded?
/*S*/	Packet.WriteS(va_arg(va, PWCHAR));//Name
/*S*/	Packet.WriteS(va_arg(va, PWCHAR));//Title
/*d*/	Packet.WriteD(va_arg(va, DWORD));//1
/*d*/	Packet.WriteD(va_arg(va, DWORD));//getPvpFlag
/*d*/	Packet.WriteD(va_arg(va, DWORD));//getKarma
/*d*/	Packet.WriteD(va_arg(va, DWORD));//currentFed
/*d*/	Packet.WriteD(va_arg(va, DWORD));//maxFed
/*d*/	Packet.WriteD(va_arg(va, DWORD));//currHp
/*d*/	Packet.WriteD(va_arg(va, DWORD));//maxHp
/*d*/	Packet.WriteD(va_arg(va, DWORD));//currMp
/*d*/	Packet.WriteD(va_arg(va, DWORD));//maxMp
/*d*/	Packet.WriteD(va_arg(va, DWORD));//SP
/*d*/	int nLevel = va_arg(va, DWORD);
		Packet.WriteD(nLevel);//level
/*d*/	INT32 nExp = va_arg(va, DWORD);
		Packet.WriteD(nExp); //exp

/*d*/	INT32 nLowestExp = va_arg(va, DWORD);
		Packet.WriteD(nLowestExp); //lowest exp for this level
/*d*/	INT32 nHighestExp = va_arg(va, DWORD);
		Packet.WriteD(nHighestExp); //exp for next level
/*d*/	Packet.WriteD(va_arg(va, DWORD));//weight
/*d*/	Packet.WriteD(va_arg(va, DWORD));//patk
/*d*/	Packet.WriteD(va_arg(va, DWORD));//pdef
/*d*/	Packet.WriteD(va_arg(va, DWORD));//matk
/*d*/	Packet.WriteD(va_arg(va, DWORD));//mdef
/*d*/	Packet.WriteD(va_arg(va, DWORD));//accuracy
/*d*/	Packet.WriteD(va_arg(va, DWORD));//evasion
/*d*/	Packet.WriteD(va_arg(va, DWORD));//critical
/*d*/	Packet.WriteD(va_arg(va, DWORD));//speed
/*d*/	Packet.WriteD(va_arg(va, DWORD));//atkspd
/*d*/	Packet.WriteD(va_arg(va, DWORD));//casting speed
/*d*/	Packet.WriteD(va_arg(va, DWORD));//abnormal effect
/*h*/	Packet.WriteH(va_arg(va,DWORD));//Ride
/*c*/	Packet.WriteC(va_arg(va,BYTE));//c2
/*h*/	Packet.WriteH(va_arg(va,WORD));//??
/*c*/	Packet.WriteC(va_arg(va,BYTE));//team aura
/*d*/	Packet.WriteD(va_arg(va,DWORD));//UsedSoulshots
/*d*/	Packet.WriteD(va_arg(va,DWORD));//UsedSpiritShots
	va_end(va);
	pSocket->Send("b", Packet.GetSize(), Packet.GetBuff());
};