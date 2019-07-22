#include "StdAfx.h"
#include "Packets.h"
#include "SubStack.h"

void CPacketFix::LoadCharSelectedPacket(CUserSocket *pSocket, const char *format, ...)
{
	CPacket packet;
	va_list va;
	va_start(va, format);
/* c */packet.WriteC(va_arg(va, unsigned char));
/* S */packet.WriteS(va_arg(va, PWCHAR));//Name
		UINT charId = va_arg(va, UINT);
/* d */packet.WriteD(charId);//CharId
/* S */packet.WriteS(va_arg(va, PWCHAR));//Title
/* d */packet.WriteD(va_arg(va, UINT));//SessionId
/* d */packet.WriteD(va_arg(va, UINT));//ClanID
/* d */packet.WriteD(va_arg(va, UINT));//unknown
/* d */packet.WriteD(va_arg(va, UINT));//Sex
/* d */packet.WriteD(va_arg(va, UINT));//Race

		UINT baseClass = va_arg(va, UINT);
		if(g_SubStack.IsEnabled())
		{
			UINT charIndex = UINT_MAX;
			for(UINT n=0;n<7;n++)
			{
				if(pSocket->characterDBID[n] == charId)
				{
					charIndex = n;
					break;
				}
			}
			if(charIndex != UINT_MAX && charIndex < 7)
			{
				if(pSocket->pED->baseClass[charIndex] != UINT_MAX)
				{
					baseClass = pSocket->pED->baseClass[charIndex];
				}
			}
		}

/* d */packet.WriteD(baseClass);//ClassId

/* d */packet.WriteD(va_arg(va, UINT));//active
/* d */packet.WriteD(va_arg(va, UINT));//X
/* d */packet.WriteD(va_arg(va, UINT));//Y
/* d */packet.WriteD(va_arg(va, UINT));//Z
/* f */packet.WriteF(va_arg(va, double));//current hp
/* f */packet.WriteF(va_arg(va, double));//current mp
/* d */packet.WriteD(va_arg(va, UINT));//sp
/* d */packet.WriteD(va_arg(va, UINT));//exp
/*Fix*/ int level = va_arg(va,UINT);
/* d */packet.WriteD(level);//Level
/* d */packet.WriteD(va_arg(va, UINT));//karma
/* d */packet.WriteD(va_arg(va, UINT));//INT
/* d */packet.WriteD(va_arg(va, UINT));//STR
/* d */packet.WriteD(va_arg(va, UINT));//CON
/* d */packet.WriteD(va_arg(va, UINT));//MEN
/* d */packet.WriteD(va_arg(va, UINT));//DEX
/* d */packet.WriteD(va_arg(va, UINT));//WIT

//Skip 128 bytes
for(int i = 0;i<33;i++){packet.WriteD(va_arg(va,UINT));}

/* d */UINT nTime = (va_arg(va, UINT));
		packet.WriteD(L2Server::GetL2Time()); //InGame Time

for(int i = 0;i<6;i++){packet.WriteD(0x00);}
	
	va_end(va);
	pSocket->Send("b", packet.GetSize(), packet.GetBuff());
}