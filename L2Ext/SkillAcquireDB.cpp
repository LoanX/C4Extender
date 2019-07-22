#include "StdAfx.h"
#include "SkillAcquireDB.h"
#include "ObjectDB.h"

CSkillAcquireDB g_SkillAcquireDB;

WCHAR* g_className[92] = { L"fighter", L"warrior", L"gladiator", L"warlord", L"knight", L"paladin", L"dark_avenger", L"rogue", L"treasure_hunter", L"hawkeye", L"mage", L"wizard", L"sorcerer", L"necromancer", L"warlock", L"cleric", L"bishop", L"prophet", L"elven_fighter", L"elven_knight", L"temple_knight", L"swordsinger", L"elven_scout", L"plains_walker", L"plain_walker", L"silver_ranger", L"elven_mage", L"elven_wizard", L"spellsinger", L"elemental_summoner", L"oracle", L"elder", L"dark_fighter", L"palus_knight", L"shillien_knight", L"bladedancer", L"assassin", L"assasin", L"abyss_walker", L"phantom_ranger", L"dark_mage", L"dark_wizard", L"spellhowler", L"phantom_summoner", L"shillien_oracle", L"shillien_elder", L"orc_fighter", L"orc_raider", L"destroyer", L"orc_monk", L"tyrant", L"orc_mage", L"orc_shaman", L"overlord", L"warcryer", L"dwarven_fighter", L"scavenger", L"bounty_hunter", L"artisan", L"warsmith", L"duelist", L"dreadnought", L"phoenix_knight", L"hell_knight", L"sagittarius", L"adventurer", L"archmage", L"soultaker", L"arcana_lord", L"cardinal", L"hierophant", L"evas_templar", L"sword_muse", L"wind_rider", L"moonlight_sentinel", L"mystic_muse", L"elemental_master", L"evas_saint", L"shillien_templar", L"spectral_dancer", L"ghost_hunter", L"ghost_sentinel", L"storm_screamer", L"spectral_master", L"shillien_saint", L"titan", L"grand_khavatari", L"dominator", L"doomcryer", L"fortune_seeker", L"maestro", L"fishing"};
int g_classId[92] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 999 };

int CSkillAcquireDB::GetClassIdFromName(const wchar_t* wName)
{
	for(int n=0;n<93;n++)
	{
		if(!wcscmp(wName, g_className[n]))
			return g_classId[n];
	}

	return -1;
}

CSkillAcquireDB::CSkillAcquireDB()
{
	InitializeCriticalSection(&_lock);
}

CSkillAcquireDB::~CSkillAcquireDB()
{
	DeleteCriticalSection(&_lock);
}

void CSkillAcquireDB::Init()
{
	g_Log.Add(CLog::Blue, "[%s] Initializing", __FUNCTION__);
	Load();
}

void CSkillAcquireDB::Load()
{
	{
		//load skill_pch
			//[s_power_strike12] = 770
		wstring wData = ReadFileW(L"..\\Script\\Skill_Pch.txt");
		wstringstream wsstr;
		wsstr << wData;
		wstring wLine;
		int Skills = 0;
		int Levels = 0;
		while(getline(wsstr, wLine))
		{
			wLine = Utils::Trim(wLine);
			if(wLine.find(L"//") == 0)
				continue;

			size_t pos = wLine.find(L'=');
			if(pos != wstring::npos)
			{
				wstring wName = wLine.substr(0, pos);
				int SkillNameID = CParser::GetValueInt(wLine, wName);
				if(SkillNameID != 0)
				{
					int nSkillID = SkillNameID >> 8;
					int nLevel = SkillNameID - (nSkillID << 8);

					CSkillKey key(nSkillID, nLevel);
					map<int, int>::iterator Iter = mSkillLevel.find(key.skill_id);
					if(Iter != mSkillLevel.end())
					{
						if(Iter->second < key.level)
						{
							Iter->second = key.level;
						}
					}else
					{
						mSkillLevel.insert(pair<int, int>(key.skill_id, key.level));
					}

					if(key.level < 100)
					{
						map<int, int>::iterator Iter2 = mNotEnchantedSkillLevel.find(key.skill_id);
						if(Iter2 != mNotEnchantedSkillLevel.end())
						{
							if(Iter2->second < key.level)
							{
								Iter2->second = key.level;
							}
						}else
						{
							//g_Log.Add(CLog::Blue, "[%s] [%d][%d]", __FUNCTION__, key.skill_id, key.level);
							mNotEnchantedSkillLevel.insert(pair<int, int>(key.skill_id, key.level));
						}
					}
				}
			}
		}
	}

	wstring wFile = ReadFileW(L"..\\Script\\SkillAcquire.txt");
	wstringstream wStream;
	wStream << wFile;
	wstring wLine;
	int nLine = 0;	
	int currentClassId = 0;
	wstring wClass = L"";

	while(getline(wStream, wLine))
	{
		nLine++;
		wstring wTrim = CParser::Trim(wLine);

		if(wTrim.find(L"//") == 0)
			continue;

		if(wTrim.find(L"skill_begin") == 0)
		{
//skill_begin	/* [??? ?? ????] */	skill_name = [s_light_armor_mastery_war122]	get_lv = 58	lv_up_sp = 73000	auto_get = false	item_needed = {}	skill_end
			AcquireSkillInfo si;
			si.name = CParser::GetName(CParser::GetValueString(wLine, L"skill_name"));
			g_SkillDB.GetSkillIdLevelByName((PWCHAR)si.name.c_str(), &si.skillId, &si.level);
			wstring autoGet = CParser::GetValueString(wLine, L"auto_get");
			if(autoGet == L"true" || autoGet == L"TRUE")
				si.autoGet = true;
			else
				si.autoGet = false;
			si.requiredLevel = CParser::GetValueInt(wLine, L"get_lv");
			si.requiredSp = CParser::GetValueInt(wLine, L"lv_up_sp");
			wstring items = CParser::GetValueString(wLine, L"item_needed");
			if(items.size() > 4)
			{
				//item_needed = {{[sb_divine_inspiration_original_version];1}}
				items = CParser::Replace(items, L'{', L' ');
				items = CParser::Replace(items, L'}', L' ');
				items = CParser::Replace(items, L'[', L' ');
				items = CParser::Replace(items, L']', L' ');
				items = CParser::Replace(items, L';', L' ');
				wstringstream sstr;
				sstr << items;
				wstring itemname;
				int itemCount = 0;
				while(sstr >> itemname >> itemCount)
				{
					int itemId = g_ObjectDB.GetClassIdFromName(itemname.c_str()); //GetItemIdByName
					si.requiredItems.AddItem(itemId, itemCount);
				}
			}
			map<int, CAcquirableSkills>::iterator Iter = mData.find(currentClassId);
			if(Iter!=mData.end())
			{
				Iter->second.Add(si);
				lSkillId.push_back(si.skillId);
			}else
			{
				g_Log.Add(CLog::Error, "[%s] Cannot get data for class[%d]", __FUNCTION__, currentClassId);
			}
		}else if(wTrim.find(L"_begin") != wstring::npos)
		{
			//get class
			size_t pos = wTrim.find(L"_begin");
			wClass = wTrim.substr(0, pos);
			currentClassId = GetClassIdFromName(wClass.c_str());
			if(currentClassId > -1)
			{
				CAcquirableSkills skills;
				mData.insert(pair<int, CAcquirableSkills>(currentClassId, skills));
			}else
			{
				g_Log.Add(CLog::Error, "[%s] Cannot get data for classId for[%S]", __FUNCTION__, wClass.c_str());
			}
		}else if(wTrim.find(L"_end") != wstring::npos)
		{
			wClass.clear();
			currentClassId = 0;
		}else if(wTrim.find(L"include_") == 0)
		{
			wstring wName = wTrim.substr(8, (wTrim.size() - 8));
			int includeClassId = GetClassIdFromName(wName.c_str());
			map<int, CAcquirableSkills>::iterator Iter = mData.find(currentClassId);
			if(Iter!=mData.end())
			{
				map<int, CAcquirableSkills>::iterator IterIncluded = mData.find(includeClassId);
				if(IterIncluded!=mData.end())
				{
					Iter->second.Include(IterIncluded->second);
				}else
				{
					g_Log.Add(CLog::Error, "[%s] Cannot include from [%d]", __FUNCTION__, includeClassId);
				}
			}else
			{
				g_Log.Add(CLog::Error, "[%s] Cannot include into [%d]", __FUNCTION__, currentClassId);
			}
		}
	}
	lSkillId.sort();
	lSkillId.unique();
}

int CSkillAcquireDB::GetMaxSkillLevel(int skillId)
{
	map<int, int>::iterator Iter = mSkillLevel.find(skillId);
	if(Iter!=mSkillLevel.end())
	{
		return Iter->second;
	}
	return -1;
}

int CSkillAcquireDB::GetMaxNotEnchantedSkillLevel(int skillId)
{
	map<int, int>::iterator Iter = mNotEnchantedSkillLevel.find(skillId);
	if(Iter!=mNotEnchantedSkillLevel.end())
	{
		return Iter->second;
	}
	return -1;
}

int CSkillAcquireDB::GetMaxAcquirableLevel(int classId, int level, int skillId)
{
	map<int, int> mSkills = GetAcquirableSkills(classId, level);
	map<int, int>::iterator Iter = mSkills.find(skillId);
	if(Iter!=mSkills.end())
	{
		return Iter->second;
	}
	return -1;
}

map<int, int> CSkillAcquireDB::GetAcquirableSkills(int classId, int level)
{
	map<int, CAcquirableSkills>::iterator Iter = mData.find(classId);
	if(Iter!=mData.end())
	{
		return Iter->second.GetList(level);
	}else
	{
		g_Log.Add(CLog::Error, "[%s] Cannot find classId[%d]", __FUNCTION__, classId);
	}

	map<int, int> mTmp;
	return mTmp;
}

bool CSkillAcquireDB::CanAcquire(int classId, int level, int skillId, int skillLevel)
{
	if(classId == -1)
		return false;

	map<int, CAcquirableSkills>::iterator Iter = mData.find(classId);
	if(Iter!=mData.end())
	{
		if(skillLevel > 100)
			skillLevel = GetMaxNotEnchantedSkillLevel(skillId);

		return Iter->second.CanAcquire(level, skillId, skillLevel);
	}else
	{
		g_Log.Add(CLog::Error, "[%s] Cannot find classId[%d]", __FUNCTION__, classId);
	}

	return false;
}

bool CSkillAcquireDB::IsInDatabase(int skillId)
{
	for(list<int>::iterator Iter = lSkillId.begin();Iter!=lSkillId.end();Iter++)
	{
		if((*Iter) == skillId)
		{
			return true;
		}
	}

	return false;
}

bool CSkillAcquireDB::CanAcquireMaxLevel(int classId, int level, int skillId)
{
	int maxLevel = GetMaxNotEnchantedSkillLevel(skillId);
	return CanAcquire(classId, level, skillId, maxLevel);
}

void CSkillAcquireDB::ValidateSkills(User *pUser)
{
	guard;
	if(pUser->ValidUser())
	{
		map<int, int> mAcquirable = GetAcquirableSkills(pUser->pSD->nClass, pUser->pSD->nLevel);
		list<int> lToDelete;
		map<int, int> mToDown;
		pUser->acquiredSkillLock.Lock(__FILEW__, __LINE__);
		for(map<int, int>::iterator Iter = pUser->mAcquiredSkill.begin();Iter!=pUser->mAcquiredSkill.end();Iter++)
		{
			map<int, int>::iterator Iter2 = mAcquirable.find(Iter->first);
			if(Iter2!=mAcquirable.end())
			{
				if(Iter2->second < Iter->second)
				{
					if(Iter->second >= 100)
					{
						//enchanted skill
						if(CanAcquireMaxLevel(pUser->pSD->nClass, 80, Iter->first))
						{
							//do not remove enchanted skills
							continue;
						}
					}
					mToDown.insert(pair<int, int>(Iter->first, Iter2->second));
				}
			}else
			{
				lToDelete.push_back(Iter->first);
			}
		}
		pUser->acquiredSkillLock.Unlock();
		for(list<int>::iterator Iter = lToDelete.begin();Iter!=lToDelete.end();Iter++)
		{
			int skillId = (*Iter);
			if(skillId!= 1324 && skillId != 1325 && skillId != 1326 && skillId != 1327 && skillId != 326 && skillId != 247 && skillId != 325)
			{
				if(skillId == 1323)
				{
					if(pUser->pSD->nNobless == 0)
					{
						pUser->DeleteSkill((*Iter));
						pUser->SendDeleteSkillToDB((*Iter));
					}
				}else
				{
					pUser->DeleteSkill((*Iter));
					pUser->SendDeleteSkillToDB((*Iter));
				}
			}
		}
		for(map<int, int>::iterator Iter = mToDown.begin();Iter!=mToDown.end();Iter++)
		{
			pUser->AcquireSkill(Iter->first, Iter->second, 1, 1);
			pUser->SendAcquireSkillToDB(Iter->first, Iter->second, true);
		}

		pUser->ValidateSkillList();
		pUser->ValidateParameters();
	}
	unguard;
}

//CAcquirableSkills

void CAcquirableSkills::Add(AcquireSkillInfo data)
{
	CSkillKey key(data.skillId, data.level);
	mData.insert(pair<CSkillKey, AcquireSkillInfo>(key, data));
}

void CAcquirableSkills::Include(CAcquirableSkills& other)
{
	mData.insert(other.mData.begin(), other.mData.end());
}

map<int, int> CAcquirableSkills::GetList(int level)
{
	map<int, int> mTmp;
	for(map<CSkillKey, AcquireSkillInfo>::iterator Iter = mData.begin();Iter!=mData.end();Iter++)
	{
		if(Iter->second.requiredLevel <= level)
		{
			map<int, int>::iterator mIter = mTmp.find(Iter->first.skill_id);
			if(mIter!=mTmp.end())
			{
				if(mIter->second < (int)(Iter->first.level))
				{
					mTmp[Iter->first.skill_id] = Iter->first.level;
				}
			}else
			{
				mTmp.insert(pair<int, int>(Iter->first.skill_id, Iter->first.level));
			}
		}
	}
	return mTmp;
}

bool CAcquirableSkills::CanAcquire(int level, int skillId, int skillLevel)
{
	CSkillKey key(skillId, skillLevel);
	map<CSkillKey, AcquireSkillInfo>::iterator Iter = mData.find(key);
	if(Iter!=mData.end())
	{
		if(level >= Iter->second.requiredLevel)
			return true;
	}
	return false;
}
