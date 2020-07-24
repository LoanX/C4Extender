#include "StdAfx.h"
#include "CursedWeaponSystem.h"
#include "Packets.h"
#include "AIO.h"
#include "TerritoryData.h"
#include "VisualArmor.h"
#include "PlayerCustomizer.h"
#include "SubStack.h"

extern UINT g_ClanLeaderTitleColor;
extern UINT g_ClanLeaderNicknameColor;
extern UINT g_GMTitleColor;
extern UINT g_GMNicknameColor;
extern UINT g_DefaultTitleColor;

extern User* g_CharInfoUser[16];

void CPacketFix::CharInfoFix(CUserSocket *pSocket, const char *format, ...)
{
	g_Log.Add(CLog::Blue,"[%s]",__FUNCTION__);

	User *pUser = 0;
	UINT threadIndex = GetThreadIndex();
	if(threadIndex < 16)
	{
		pUser = g_CharInfoUser[threadIndex];
	}

	CPacket Packet;
	va_list tag;
	va_start(tag, format);
/* c */ Packet.WriteC(va_arg(tag, BYTE));
/* d */ Packet.WriteD(va_arg(tag, DWORD)); //X
/* d */ Packet.WriteD(va_arg(tag, DWORD)); //Y
/* d */ Packet.WriteD(va_arg(tag, DWORD)); //Z
		DWORD heading = va_arg(tag, DWORD);
/* d */ Packet.WriteD(heading); //Heading
/* d */	UINT nObjectID = va_arg(tag, DWORD); //ObjectID

		if(pUser == 0)
		{
			pUser = User::GetUserBySID(&nObjectID);
			if(!pUser->ValidUser())
			{
				return;
			}
		}

		Packet.WriteD(nObjectID); 

		PWCHAR wName = va_arg(tag, PWCHAR);
		CNickNameChangeTerritory *pTerritory = NULL;
		if(int TerritoryID = pUser->pSD->nInNickNameChangeZone)
		{
			pTerritory = g_TerritoryChecker.GetTerritory(TerritoryID)->SafeCastNickNameChange();
			if(pTerritory)
			{
				PWCHAR wNewName = (PWCHAR)pTerritory->GetNickName();
				if(wNewName)
				{
					wName = wNewName;
				}
			}
		}
		/*S*/ Packet.WriteS(wName); //nickname

		DWORD Race = va_arg(tag, DWORD);
		if(pUser->pED->fakeRace != UINT_MAX)
		{
			Race = pUser->pED->fakeRace;
		}
		DWORD Sex = va_arg(tag, DWORD);
		if(pUser->pED->fakeSex != UINT_MAX)
		{
			Sex = pUser->pED->fakeSex;
		}
		
/* d */ Packet.WriteD(Race);	//race
/* d */ Packet.WriteD(Sex);	//sex
		DWORD BaseClass = va_arg(tag, DWORD);

		if(g_SubStack.IsEnabled())
		{
			//get char index;
			UINT charIndex = UINT_MAX;
			for(UINT n=0;n<7;n++)
			{
				if(pUser->pSocket->characterDBID[n] == pUser->nDBID)
				{
					charIndex = n;
					break;
				}
			}
			if(charIndex != UINT_MAX && charIndex < 7)
			{
				if(pUser->pSocket->pED->baseClass[charIndex] != UINT_MAX)
				{
					BaseClass = pUser->pSocket->pED->baseClass[charIndex];
				}
			}
		}

/* d */ Packet.WriteD(BaseClass);

		INT32 dhairId = va_arg(tag, INT32);
		INT32 headId = va_arg(tag, INT32);
		INT32 rhandId = va_arg(tag, INT32);
		INT32 lhandId = va_arg(tag, INT32);
		INT32 glovesId = va_arg(tag, INT32);
		INT32 chestId = va_arg(tag, INT32);
		INT32 legsId = va_arg(tag, INT32);
		INT32 feetId = va_arg(tag, INT32);
		INT32 backId = va_arg(tag, INT32);
		INT32 lrhandId = va_arg(tag, INT32);
		INT32 hairId = va_arg(tag, INT32);		
		
		if(g_VisualArmor.IsEnabled())
		{
			VisualArmorUser& vUser = pUser->pED->visualArmorUser;
			if(vUser.armorId > 0)
			{
				if(vUser.armorType == 0 || vUser.armorType == pUser->pSD->nArmorType)
				{
					if(chestId > 0)
					{
						chestId = vUser.chestSlotId;
					}
					if(legsId > 0)
					{
						legsId = vUser.legsSlotId;
					}
					if(glovesId > 0)
					{
						glovesId = vUser.glovesSlotId;
					}
					if(feetId > 0)
					{
						feetId = vUser.feetSlotId;
					}
				}
			}
		}
/* d */ Packet.WriteD(dhairId);	//dhair
/* d */ Packet.WriteD(headId);	//head
/* d */ Packet.WriteD(rhandId);	//rhand
/* d */ Packet.WriteD(lhandId);	//lhand
/* d */ Packet.WriteD(glovesId);	//gloves
/* d */ Packet.WriteD(chestId);	//chest
/* d */ Packet.WriteD(legsId);	//legs
/* d */ Packet.WriteD(feetId);	//feet
/* d */ Packet.WriteD(backId);	//back
/* d */ Packet.WriteD(lrhandId);	//lrhand
/* d */ Packet.WriteD(hairId);	//hair		

/* d */ Packet.WriteD(va_arg(tag, DWORD));//PvpFlag
/* d */ Packet.WriteD(va_arg(tag, DWORD));//Karma
/* d */ Packet.WriteD(va_arg(tag, DWORD));//mAtkSpd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//pAtkSpd

/* d */ Packet.WriteD(va_arg(tag, DWORD));//PvpFlag
/* d */ Packet.WriteD(va_arg(tag, DWORD));//Karma

/* d */ Packet.WriteD(va_arg(tag, DWORD));//runSpd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//WalkSpd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//swim run spd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//swim walk spd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//fl run spd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//fl walk spd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//fly run spd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//fly walk spd

/* f */ Packet.WriteF(va_arg(tag, double));//movementSpdMult
/* f */ Packet.WriteF(va_arg(tag, double));//AtkSpdMult

		double radius = va_arg(tag, double);
		double height = va_arg(tag, double);
		
		if(pUser->pED->fakeRace != UINT_MAX || pUser->pED->fakeSex != UINT_MAX)
		{
			DWORD Magic = 0;
			if(CCategoryDataDB::IsInCategory(BaseClass, CCategoryDataDB::MAGE_GROUP))
				Magic = 1;
			radius = g_World.GetRadius(Race, Sex, Magic);
			height = g_World.GetHeight(Race, Sex, Magic);
		}
/* f */ Packet.WriteF(radius);	//collision_radius
/* f */ Packet.WriteF(height);	//collision_height

/* d */ Packet.WriteD(va_arg(tag, DWORD));	//hair_style
/* d */ Packet.WriteD(va_arg(tag, DWORD));	//hair_color
/* d */ Packet.WriteD(va_arg(tag, DWORD));	//face
		
		if(pTerritory && pTerritory->IsHidePledge())
		{
				va_arg(tag, PWCHAR);
		/* S */ Packet.WriteS(L"");	//title
				va_arg(tag, DWORD);
		/* d */ Packet.WriteD(0);	//pledge_id
				va_arg(tag, DWORD);
		/* d */ Packet.WriteD(0);	//pledge_crest_id
				va_arg(tag, DWORD);
		/* d */ Packet.WriteD(0);	//ally_id
				va_arg(tag, DWORD);
		/* d */ Packet.WriteD(0);	//ally_crest_id
		}else
		{
		/* S */ Packet.WriteS(va_arg(tag, PWCHAR));	//title
		/* d */ Packet.WriteD(va_arg(tag, DWORD));	//pledge_id
		/* d */ Packet.WriteD(va_arg(tag, DWORD));	//pledge_crest_id
		/* d */ Packet.WriteD(va_arg(tag, DWORD));	//ally_id
		/* d */ Packet.WriteD(va_arg(tag, DWORD));	//ally_crest_id
		}

/* d */ Packet.WriteD(va_arg(tag, DWORD));	//unknown

/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsSitting
/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsRunning
/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsInCombat
/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsAlikeDead

/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsInvisible
/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsMounted
/* c */ Packet.WriteC(va_arg(tag, BYTE));//PrivateStore?

/* h */ Packet.WriteH(va_arg(tag, WORD));//Cubics

/*Fix*/ va_arg(tag,DWORD);
/*Fix*/ va_arg(tag,DWORD);

/* c */ Packet.WriteC(va_arg(tag,BYTE));//Find party members
		DWORD AbnormalVisualEffect = va_arg(tag, DWORD);

		if(pUser->pSD->pExData->SkillMod.semiInvisible)
		{
			AbnormalVisualEffect |= 0x100000;	//stealth
		}
		if(pUser->pSD->activateOfflineShopTime)
		{
			AbnormalVisualEffect |= 0x000080; //Sleep
		}
		if(pUser->pED->spawnProtection == 2)
		{
			AbnormalVisualEffect |= 0x200000;
		}

/* d */ Packet.WriteD(AbnormalVisualEffect);//AbnormalEffect

/* c */ Packet.WriteC(va_arg(tag,BYTE));//RecomLeft
/* h */ Packet.WriteH(va_arg(tag, WORD));//RecomHave
/* d */ Packet.WriteD(va_arg(tag, DWORD));//ClassId

/* d */ Packet.WriteD(va_arg(tag, DWORD));//MaxCp
/* d */ Packet.WriteD(va_arg(tag,DWORD));//CurrentCp
/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsMounted

		BYTE bTeam = va_arg(tag, BYTE);

		if(pUser->pSD->DuelInfo.DuelID && pUser->pSD->DuelInfo.Fighting)
		{
			bTeam = pUser->pSD->DuelInfo.DuelTeam;
		}
		if(pUser->pED->tvtUser.status == TvT::UserFighting || pUser->pED->tvtUser.status == TvT::UserPreparing)
		{
				bTeam = pUser->pED->tvtUser.team;
		}

/* c */ Packet.WriteC(bTeam); //Team?
/* d */ Packet.WriteD(va_arg(tag, DWORD));//ClanCrestLargeId
/* c */ Packet.WriteC(va_arg(tag, BYTE));//Symbol on char CTRL+I
/* c */ Packet.WriteC(va_arg(tag, BYTE));//Hero Aura
/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsFishing
/* d */ Packet.WriteD(va_arg(tag, DWORD));//FishX
/* d */ Packet.WriteD(va_arg(tag, DWORD));//FishY
/* d */ Packet.WriteD(va_arg(tag, DWORD));//FishZ

		DWORD NickNameColor = va_arg(tag, DWORD);

		if(pUser->pSD->nIsPledgeLeader && g_ClanLeaderNicknameColor != 0)
		{
			NickNameColor = g_ClanLeaderNicknameColor;
		}
		if(pUser->pSD->nBuilder && g_GMNicknameColor != 0)
		{
			NickNameColor = g_GMNicknameColor;
		}
		if(pUser->pED->nicknameColor != 0)
		{
			NickNameColor = pUser->pED->nicknameColor;
		}
		if(pUser->pED->nameColorEx != 0)
		{
			NickNameColor = pUser->pED->nameColorEx;
		}
		if(pUser->pED->aioId > 0 && pUser->pSD->nSubClassIndex == 0)
		{
			if(g_AIOSystem.IsEnabled())
			{
				NickNameColor = pUser->pED->aioNicknameColor;
			}
		}
		if(pTerritory)
		{
			if(DWORD Color = pTerritory->GetColor())
				NickNameColor = Color;
		}
/* d */ Packet.WriteD(NickNameColor);//NameColor

	va_end(tag);
	pSocket->Send("b", Packet.GetSize(), Packet.GetBuff());
}

void CPacketFix::CharInfoBCFix(INT64 dwAddr, int nObjID, int nRange, FVector *pLocation, const char *format, ...)
{
	User *pUser = 0;
	UINT threadIndex = GetThreadIndex();
	if(threadIndex < 16)
	{
		pUser = g_CharInfoUser[threadIndex];
	}

	CPacket Packet;
	va_list tag;
	va_start(tag, format);
/* c */ Packet.WriteC(va_arg(tag, BYTE));
/* d */ Packet.WriteD(va_arg(tag, DWORD)); //X
/* d */ Packet.WriteD(va_arg(tag, DWORD)); //Y
/* d */ Packet.WriteD(va_arg(tag, DWORD)); //Z
		DWORD heading = va_arg(tag, DWORD);
/* d */ Packet.WriteD(heading); //Heading
/* d */	UINT nObjectID = va_arg(tag, DWORD); //ObjectID

		if(pUser == 0)
		{
			pUser = User::GetUserBySID(&nObjectID);
			if(!pUser->ValidUser())
			{
				return;
			}
		}

		Packet.WriteD(nObjectID); 

		PWCHAR wName = va_arg(tag, PWCHAR);
		CNickNameChangeTerritory *pTerritory = NULL;
		if(int TerritoryID = pUser->pSD->nInNickNameChangeZone)
		{
			pTerritory = g_TerritoryChecker.GetTerritory(TerritoryID)->SafeCastNickNameChange();
			if(pTerritory)
			{
				PWCHAR wNewName = (PWCHAR)pTerritory->GetNickName();
				if(wNewName)
				{
					wName = wNewName;
				}
			}
		}
		/*S*/ Packet.WriteS(wName); //nickname

		DWORD Race = va_arg(tag, DWORD);
		if(pUser->pED->fakeRace != UINT_MAX)
		{
			Race = pUser->pED->fakeRace;
		}
		DWORD Sex = va_arg(tag, DWORD);
		if(pUser->pED->fakeSex != UINT_MAX)
		{
			Sex = pUser->pED->fakeSex;
		}
		
/* d */ Packet.WriteD(Race);	//race
/* d */ Packet.WriteD(Sex);	//sex
		DWORD BaseClass = va_arg(tag, DWORD);

		if(g_SubStack.IsEnabled())
		{
			//get char index;
			UINT charIndex = UINT_MAX;
			for(UINT n=0;n<7;n++)
			{
				if(pUser->pSocket->characterDBID[n] == pUser->nDBID)
				{
					charIndex = n;
					break;
				}
			}
			if(charIndex != UINT_MAX && charIndex < 7)
			{
				if(pUser->pSocket->pED->baseClass[charIndex] != UINT_MAX)
				{
					BaseClass = pUser->pSocket->pED->baseClass[charIndex];
				}
			}
		}

/* d */ Packet.WriteD(BaseClass);

		INT32 dhairId = va_arg(tag, INT32);
		INT32 headId = va_arg(tag, INT32);
		INT32 rhandId = va_arg(tag, INT32);
		INT32 lhandId = va_arg(tag, INT32);
		INT32 glovesId = va_arg(tag, INT32);
		INT32 chestId = va_arg(tag, INT32);
		INT32 legsId = va_arg(tag, INT32);
		INT32 feetId = va_arg(tag, INT32);
		INT32 backId = va_arg(tag, INT32);
		INT32 lrhandId = va_arg(tag, INT32);
		INT32 hairId = va_arg(tag, INT32);		
		
		if(g_VisualArmor.IsEnabled())
		{
			VisualArmorUser& vUser = pUser->pED->visualArmorUser;
			if(vUser.armorId > 0)
			{
				if(vUser.armorType == 0 || vUser.armorType == pUser->pSD->nArmorType)
				{
					if(chestId > 0)
					{
						chestId = vUser.chestSlotId;
					}
					if(legsId > 0)
					{
						legsId = vUser.legsSlotId;
					}
					if(glovesId > 0)
					{
						glovesId = vUser.glovesSlotId;
					}
					if(feetId > 0)
					{
						feetId = vUser.feetSlotId;
					}
				}
			}
		}
/* d */ Packet.WriteD(dhairId);	//dhair
/* d */ Packet.WriteD(headId);	//head
/* d */ Packet.WriteD(rhandId);	//rhand
/* d */ Packet.WriteD(lhandId);	//lhand
/* d */ Packet.WriteD(glovesId);	//gloves
/* d */ Packet.WriteD(chestId);	//chest
/* d */ Packet.WriteD(legsId);	//legs
/* d */ Packet.WriteD(feetId);	//feet
/* d */ Packet.WriteD(backId);	//back
/* d */ Packet.WriteD(lrhandId);	//lrhand
/* d */ Packet.WriteD(hairId);	//hair		

/* d */ Packet.WriteD(va_arg(tag, DWORD));//PvpFlag
/* d */ Packet.WriteD(va_arg(tag, DWORD));//Karma
/* d */ Packet.WriteD(va_arg(tag, DWORD));//mAtkSpd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//pAtkSpd

/* d */ Packet.WriteD(va_arg(tag, DWORD));//PvpFlag
/* d */ Packet.WriteD(va_arg(tag, DWORD));//Karma

/* d */ Packet.WriteD(va_arg(tag, DWORD));//runSpd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//WalkSpd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//swim run spd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//swim walk spd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//fl run spd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//fl walk spd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//fly run spd
/* d */ Packet.WriteD(va_arg(tag, DWORD));//fly walk spd

/* f */ Packet.WriteF(va_arg(tag, double));//movementSpdMult
/* f */ Packet.WriteF(va_arg(tag, double));//AtkSpdMult

		double radius = va_arg(tag, double);
		double height = va_arg(tag, double);
		
		if(pUser->pED->fakeRace != UINT_MAX || pUser->pED->fakeSex != UINT_MAX)
		{
			DWORD Magic = 0;
			if(CCategoryDataDB::IsInCategory(BaseClass, CCategoryDataDB::MAGE_GROUP))
				Magic = 1;
			radius = g_World.GetRadius(Race, Sex, Magic);
			height = g_World.GetHeight(Race, Sex, Magic);
		}
/* f */ Packet.WriteF(radius);	//collision_radius
/* f */ Packet.WriteF(height);	//collision_height

/* d */ Packet.WriteD(va_arg(tag, DWORD));	//hair_style
/* d */ Packet.WriteD(va_arg(tag, DWORD));	//hair_color
/* d */ Packet.WriteD(va_arg(tag, DWORD));	//face
		
		if(pTerritory && pTerritory->IsHidePledge())
		{
				va_arg(tag, PWCHAR);
		/* S */ Packet.WriteS(L"");	//title
				va_arg(tag, DWORD);
		/* d */ Packet.WriteD(0);	//pledge_id
				va_arg(tag, DWORD);
		/* d */ Packet.WriteD(0);	//pledge_crest_id
				va_arg(tag, DWORD);
		/* d */ Packet.WriteD(0);	//ally_id
				va_arg(tag, DWORD);
		/* d */ Packet.WriteD(0);	//ally_crest_id
		}else
		{
		/* S */ Packet.WriteS(va_arg(tag, PWCHAR));	//title
		/* d */ Packet.WriteD(va_arg(tag, DWORD));	//pledge_id
		/* d */ Packet.WriteD(va_arg(tag, DWORD));	//pledge_crest_id
		/* d */ Packet.WriteD(va_arg(tag, DWORD));	//ally_id
		/* d */ Packet.WriteD(va_arg(tag, DWORD));	//ally_crest_id
		}

/* d */ Packet.WriteD(va_arg(tag, DWORD));	//unknown

/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsSitting
/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsRunning
/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsInCombat
/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsAlikeDead

/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsInvisible
/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsMounted
/* c */ Packet.WriteC(va_arg(tag, BYTE));//PrivateStore?

/* h */ Packet.WriteH(va_arg(tag, WORD));//Cubics

/*Fix*/ va_arg(tag,DWORD);
/*Fix*/ va_arg(tag,DWORD);

/* c */ Packet.WriteC(va_arg(tag,BYTE));//Find party members
		DWORD AbnormalVisualEffect = va_arg(tag, DWORD);

		if(pUser->pSD->pExData->SkillMod.semiInvisible)
		{
			AbnormalVisualEffect |= 0x100000;	//stealth
		}
		if(pUser->pSD->activateOfflineShopTime)
		{
			AbnormalVisualEffect |= 0x000080; //Sleep
		}
		if(pUser->pED->spawnProtection == 2)
		{
			AbnormalVisualEffect |= 0x200000;
		}

/* d */ Packet.WriteD(AbnormalVisualEffect);//AbnormalEffect

/* c */ Packet.WriteC(va_arg(tag,BYTE));//RecomLeft
/* h */ Packet.WriteH(va_arg(tag, WORD));//RecomHave
/* d */ Packet.WriteD(va_arg(tag, DWORD));//ClassId

/* d */ Packet.WriteD(va_arg(tag, DWORD));//MaxCp
/* d */ Packet.WriteD(va_arg(tag,DWORD));//CurrentCp
/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsMounted

		BYTE bTeam = va_arg(tag, BYTE);

		if(pUser->pSD->DuelInfo.DuelID && pUser->pSD->DuelInfo.Fighting)
		{
			bTeam = pUser->pSD->DuelInfo.DuelTeam;
		}
		if(pUser->pED->tvtUser.status == TvT::UserFighting || pUser->pED->tvtUser.status == TvT::UserPreparing)
		{
				bTeam = pUser->pED->tvtUser.team;
		}

/* c */ Packet.WriteC(bTeam); //Team?
/* d */ Packet.WriteD(va_arg(tag, DWORD));//ClanCrestLargeId
/* c */ Packet.WriteC(va_arg(tag, BYTE));//Symbol on char CTRL+I
/* c */ Packet.WriteC(va_arg(tag, BYTE));//Hero Aura
/* c */ Packet.WriteC(va_arg(tag, BYTE));//IsFishing
/* d */ Packet.WriteD(va_arg(tag, DWORD));//FishX
/* d */ Packet.WriteD(va_arg(tag, DWORD));//FishY
/* d */ Packet.WriteD(va_arg(tag, DWORD));//FishZ

		DWORD NickNameColor = va_arg(tag, DWORD);

		if(pUser->pSD->nIsPledgeLeader && g_ClanLeaderNicknameColor != 0)
		{
			NickNameColor = g_ClanLeaderNicknameColor;
		}
		if(pUser->pSD->nBuilder && g_GMNicknameColor != 0)
		{
			NickNameColor = g_GMNicknameColor;
		}
		if(pUser->pED->nicknameColor != 0)
		{
			NickNameColor = pUser->pED->nicknameColor;
		}
		if(pUser->pED->nameColorEx != 0)
		{
			NickNameColor = pUser->pED->nameColorEx;
		}
		if(pUser->pED->aioId > 0 && pUser->pSD->nSubClassIndex == 0)
		{
			if(g_AIOSystem.IsEnabled())
			{
				NickNameColor = pUser->pED->aioNicknameColor;
			}
		}
		if(pTerritory)
		{
			if(DWORD Color = pTerritory->GetColor())
				NickNameColor = Color;
		}
/* d */ Packet.WriteD(NickNameColor);//NameColor

	va_end(tag);

	BroadcastToNeighborExceptSelf(nObjID, nRange, pLocation, (int)Packet.GetSize(), Packet.GetBuff());
}