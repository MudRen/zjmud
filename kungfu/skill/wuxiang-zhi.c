// wuxiang-zhi.c - ��������ָ��
       
inherit SHAOLIN_SKILL;
	
mapping *action = ({
([     "action": "$N����ǰ̤��һ������ָ�й�ֱ����һʽ��������Ϣ������$n��$l",
       "force" : 80,
       "attack": 20,
       "parry" : 20,
       "dodge" : -5,
       "damage": 20,
       "lvl"   : 0,
       "skill_name" : "������Ϣ",
       "damage_type" : "����"
]),
([     "action": "$Nһ�С��������������ᳪһ����ţ����ҿ�������һ����һ�ž���������$n",
       "force" : 90,
       "attack": 30,
       "parry" : 5,
       "dodge" : 20,
       "damage": 50,
       "lvl"   : 40,
       "skill_name" : "��������",
       "damage_type" : "����"
]),
([     "action": "$N����Ʈ��������һʽ���޷����졹����ָ����$n��$l",
       "force" : 150,
       "attack": 50,
       "parry" : 35,
       "dodge" : 25,
       "damage": 80,
       "lvl"   : 80,
       "skill_name" : "�޷�����",
       "damage_type" : "����"
]),
([     "action": "$N��̤���ǲ���ͻȻһ�С�������ա�����ָ�����벻���ĽǶȹ���$n�ĸ���ҪѨ",
       "force" : 180,
       "attack": 70,
       "parry" : 35,
       "dodge" : -10,
       "damage": 100,
       "lvl"   : 120,
       "skill_name" : "�������",
       "damage_type" : "����"
]),
([     "action": "$Nһ�С����������������$n��ת��һָ����$n����ʤ��",
       "force" : 230,
       "attack": 70,
       "parry" : 30,
       "dodge" : 15,
       "damage": 130,
       "lvl"   : 160,
       "skill_name" : "�������",
       "damage_type" : "����"
]),
([     "action": "$N��ϥ������һ�С����ޱߡ�������Ĵָ����һ�����磬����$n",
       "force" : 160,
       "attack": 60,
       "parry" : 30,
       "dodge" : 5,
       "damage": 100,
       "lvl"   : 120,
       "skill_name" : "���ޱ�",
       "damage_type" : "����"
]),
([     "action": "$N˫Ŀ���գ�һ�С���ɫ���ࡹ���ۼ�ȫ��������һָ���һ����ɫ����ֱ��$n",
       "force" : 250,
       "attack": 100,
       "parry" : 50,
       "dodge" : 25,
       "damage": 180,
       "lvl"   : 200,
       "skill_name" : "��ɫ����",
       "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; } 
     
int valid_combine(string combo) { return combo == "xuni-zhang"; } 
      
int valid_learn(object me) 
{ 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
		return notify_fail("������ָ������֡�\n"); 
      
	if ((int)me->query_skill("force") < 60) 
		return notify_fail("����ڹ���򲻹����޷�ѧ����ָ��\n"); 
     
	if ((int)me->query("max_neili") < 300) 
		return notify_fail("�������̫�����޷�������ָ��\n"); 
      
	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("wuxiang-zhi", 1))
		return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷��������������ָ��\n"); 
      
	return 1; 
} 
      
string query_skill_name(int level) 
{ 
	int i; 
	for (i = sizeof(action) - 1; i >= 0; i--) 
		if (level >= action[i]["lvl"]) 
			return action[i]["skill_name"]; 
} 
      
mapping query_action(object me, object weapon) 
{ 
	int i, level; 
	level = (int) me->query_skill("wuxiang-zhi", 1); 
	for (i = sizeof(action); i > 0; i--) 
		if (level > action[i-1]["lvl"]) 
			return action[NewRandom(i, 20, level/5)]; 
} 
      
int practice_skill(object me) 
{ 
	if (me->query_temp("weapon") || 
	    me->query_temp("secondary_weapon")) 
		return notify_fail("����������ϰ��\n"); 
      
	if ((int)me->query("qi") < 70) 
		return notify_fail("�������̫���ˡ�\n"); 
      
	if ((int)me->query("neili") < 70) 
		return notify_fail("�����������������ָ��\n"); 
      
	me->receive_damage("qi", 50); 
	me->add("neili", -30); 
	return 1; 
} 
      
string perform_action_file(string action) 
{ 
	return __DIR__"wuxiang-zhi/" + action; 
} 
