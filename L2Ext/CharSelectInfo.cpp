#include "StdAfx.h"
#include "Packets.h"
#include "AccountDB.h"
#include "SocketDB.h"

extern INT32 g_AntiBotVersion;

void CPacketFix::CharSelectInfoFix(CUserSocket *pSocket, const char *szFormat, BYTE bOpCode, DWORD dwCharNum, DWORD dwPacketSize, PUCHAR pOldPacket)
{
	if(dwCharNum<=0)
		pSocket->Send(szFormat, bOpCode, dwCharNum, dwPacketSize, pOldPacket);
	else if (pSocket && pOldPacket)
	{
		g_AccountDB.Add(pSocket->accountId, pSocket);

		CPacket OldPacket(pOldPacket);
		CPacket NewPacket;
		for(unsigned int n=0;n<dwCharNum; n++)
		{
			/*S*/ NewPacket.WriteS(OldPacket.ReadS()); //Name
			/*d*/ NewPacket.WriteD(OldPacket.ReadD()); //CharId
			/*S*/ NewPacket.WriteS(OldPacket.ReadS()); //LoginName
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//SessionId
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//ClanId
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Unknown
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Sex
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Race
			UINT baseClass = OldPacket.ReadD();
					pSocket->pED->baseClass[n] = baseClass;
			/*d*/ NewPacket.WriteD(baseClass);	//BaseClassId
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());	//active
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());	//x
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());	//y
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());	//z
			/*f*/ NewPacket.WriteF(OldPacket.ReadF());	//cur hp
			/*f*/ NewPacket.WriteF(OldPacket.ReadF());	//cur mp
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//SP
			/*d*/ NewPacket.WriteD(OldPacket.ReadD()); //EXP			
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Unknown
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Level			
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Karma

			//Skip 36 bytes
			for(int i = 0;i<9;i++){NewPacket.WriteD(OldPacket.ReadD());}
		
			//ObjectType
		
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Under
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//REar
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//LEar
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Neck
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//RFinger
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//LFinger
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Head
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//RHand			
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//LHand
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Gloves
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Chest
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Legs
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Feet
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Back
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//LRHand			
			/*Fix*/ OldPacket.ReadD(); //Unknown - Correction
			/*d*/ NewPacket.WriteD(OldPacket.ReadD()); //Hair

			//End of ObjectType

			//ObjectId

			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Under
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//REar
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//LEar
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Neck
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//RFinger
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//LFinger
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Head
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//RHand
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//LHand
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Gloves
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Chest
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Legs			
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//Feet			
				int nBackItemType = OldPacket.ReadD();
			/*d*/ NewPacket.WriteD(nBackItemType);//Back								
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//LRHand
				int nHairItemType = OldPacket.ReadD();
			/*d*/ NewPacket.WriteD(nHairItemType); //Hair Slot type
			
			//End of ObjectId									
			NewPacket.Rewind(sizeof(INT32));
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//HairStyle
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//HairColor
				OldPacket.ReadD();
			NewPacket.Next(sizeof(INT32));
				
			/*f*/ NewPacket.WriteF(OldPacket.ReadF());//hp max
			/*f*/ NewPacket.WriteF(OldPacket.ReadF());//mp max
			
			/*d*/ NewPacket.WriteD(OldPacket.ReadD()); //Delete Days
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//ClassId
			/*d*/ NewPacket.WriteD(OldPacket.ReadD());//LastUsed
			/*c*/ NewPacket.WriteC(OldPacket.ReadC());//EnchantEffect
						
			

			OldPacket.ReadD();
			OldPacket.ReadS();
			OldPacket.ReadS();
			OldPacket.ReadD();
			OldPacket.ReadS();
			OldPacket.ReadD();
			OldPacket.ReadS();		
			
		}
		pSocket->Send(szFormat, bOpCode, dwCharNum, NewPacket.GetSize(), NewPacket.GetBuff());
	}
	
	g_SocketDB.SetStatus(pSocket, CSocketData::CHAR_SELECTION_SCREEN);
}