// jingang-zhi.c - ���ִ������ָ
       
inherit SHAOLIN_SKILL;
	
mapping *action = ({
([     "action": "$N�����ף���ָ�й�ֱ����һʽ����������������$n��$l",
       "force" : 80,
       "attack": 20,
       "parry" : 20,
       "dodge" : -5,
       "damage": 20,
       "lvl"   : 0,
       "skill_name" : "��������",
       "damage_type" : "����"
]),
([     "action": "$N����һ�ݣ��Ӹ����£�һʽ���ն�������������$n�������Ѩ",
       "force" : 100,
       "attack": 40,
       "parry" : 15,
       "dodge" : 0,
       "damage": 25,
       "lvl"   : 40,
       "skill_name" : "�ն�����",
       "damage_type" : "����"
]),
([     "action": "$N����Ʈ��������һʽ�������׻�������ָ����$n��$l",
       "force" : 110,
       "attack": 30,
       "parry" : 25,
       "dodge" : -5,
       "damage": 30,
       "lvl"   : 80,
       "skill_name" : "�����׻�",
       "damage_type" : "����"
]),
([     "action": "$N������ɫ��ͻȻһ�С�ն����ħ��������˫ָ�ֱ�ָ��$n�ĸ���ҪѨ",
       "force" : 150,
       "attack": 40,
       "parry" : 25,
       "dodge" : -10,
       "damage": 120,
       "lvl"   : 60,
       "skill_name" : "ն����ħ",
       "damage_type" : "����"
]),
([     "action": "$N��ָ�絶��һ�С��嶡��ɽ����˫ָ�ʵ��ƴ����벻���ĽǶ�����$n",
       "force" : 180,
       "attack": 50,
       "parry" : 30,
       "dodge" : -15,
       "damage": 160,
       "lvl"   : 80,
       "skill_name" : "�嶡��ɽ",
       "damage_type" : "����"
]),
([     "action": "$N��ϥ������һ�С����ޱߡ�������Ĵָ����һ�����磬����$n",
       "force" : 160,
       "attack": 60,
       "parry" : 30,
       "dodge" : 5,
       "damage": 100,
       "lvl"   : 200,
       "skill_name" : "���ޱ�",
       "damage_type" : "����"
]),
([     "action": "$N������ϣ�һ�С���շ�ħ����˫��ʳָ�˲������һ����������$n",
       "force" : 180,
       "attack": 60,
       "parry" : 40,
       "dodge" : -5,
       "damage": 120,
       "lvl"   : 225,
       "skill_name" : "��շ�ħ",
       "damage_type" : "����"
]),
([     "action": "$N���Ϻ������֮����һ�С���ɫ���ࡹ��һָңңָ��$n���ƺ����޾���",
       "force" : 200,
       "attack": 70,
       "parry" : 50,
       "dodge" : 15,
       "damage": 180,
       "lvl"   : 250,
       "skill_name" : "��ɫ����",
       "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; } 
     
int valid_combine(string combo) { return combo == "xumishan-zhang"; } 
      
int valid_learn(object me) 
{ 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
		return notify_fail("���������ָ������֡�\n"); 
      
	if ((int)me->query_skill("force") < 60) 
		return notify_fail("����ڹ���򲻹����޷�ѧ�������ָ��\n"); 
     
	if ((int)me->query("max_neili") < 300) 
		return notify_fail("�������̫�����޷����������ָ��\n"); 
      
	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("jingang-zhi", 1))
		return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷���������Ĵ������ָ��\n"); 
      
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
	level = (int) me->query_skill("jingang-zhi", 1); 
	for (i = sizeof(action); i > 0; i--) 
		if (level > action[i-1]["lvl"]) 
			return action[NewRandom(i, 20, level/5)]; 
} 
      
int practice_skill(object me) 
{ 
	if ((int)me->query("qi") < 70) 
		return notify_fail("�������̫���ˡ�\n"); 
      
	if ((int)me->query("neili") < 70) 
		return notify_fail("��������������������ָ��\n"); 
      
	me->receive_damage("qi", 60); 
	me->add("neili", -64); 
	return 1; 
} 
      
string perform_action_file(string action) 
{ 
	return __DIR__"jingang-zhi/" + action; 
} 
