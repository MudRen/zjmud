// shenzhang-bada.c - ���ư˴�
       
inherit SHAOLIN_SKILL;
	
mapping *action = ({
([     "action": "$Nһ�С����ƶϷ塹�����𹥣��������ƻ���$n��$l",
       "force" : 120,
       "attack": 40,
       "parry" : 20,
       "dodge" : -15,
       "damage": 20,
       "lvl"   : 0,
       "skill_name" : "���ƶϷ�",
       "damage_type" : "����"
]),
([     "action": "$N������ǰ��˫��ͬʱ������һ�С�����̩������$n�������Ʒ�֮��",
       "force" : 150,
       "attack": 50,
       "parry" : 15,
       "dodge" : 0,
       "damage": 35,
       "lvl"   : 20,
       "skill_name" : "����̩",
       "damage_type" : "����"
]),
([     "action": "$Nһ�С��绢��ɽ�������Ƴ���ֱ����Ѹ�װ�����$n��$l",
       "force" : 180,
       "attack": 60,
       "parry" : 25,
       "dodge" : -5,
       "damage": 50,
       "lvl"   : 40,
       "skill_name" : "�绢��ɽ",
       "damage_type" : "����"
]),
([     "action": "$Nһ�С���Ծ��Ԩ����������һ���������������һ�����ݣ������������$n��$l",
       "force" : 200,
       "attack": 70,
       "parry" : 35,
       "dodge" : -15,
       "damage": 80,
       "lvl"   : 60,
       "skill_name" : "��Ծ��Ԩ",
       "damage_type" : "����"
]),
([     "action": "$Nһ�С�����ƽɳ���������ף�˫��һɨ�������������$n������",
       "force" : 230,
       "attack": 80,
       "parry" : 30,
       "dodge" : -15,
       "damage": 110,
       "lvl"   : 80,
       "skill_name" : "����ƽɳ",
       "damage_type" : "����"
]),
([     "action": "$Nһ��ת��һ�С����񻮳������������ģ��Ʒ����·����$n",
       "force" : 270,
       "attack": 100,
       "parry" : 30,
       "dodge" : 5,
       "damage": 140,
       "lvl"   : 120,
       "skill_name" : "���񻮳�",
       "damage_type" : "����"
]),
([     "action": "$N������ϣ�һ�С������Ʋ���������һȦ�������漴ֱ����$n���ؿ�",
       "force" : 300,
       "attack": 100,
       "parry" : 10,
       "dodge" : -15,
       "damage": 160,
       "lvl"   : 160,
       "skill_name" : "�����Ʋ�",
       "damage_type" : "����"
]),
([     "action": "$N������ת������һ�С�����˷������ó�������Ӱ��ͬʱ����$n",
       "force" : 350,
       "attack": 120,
       "parry" : 50,
       "dodge" : 15,
       "damage": 200,
       "lvl"   : 200,
       "skill_name" : "����˷�",
       "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; } 
     
int valid_combine(string combo) { return combo == "wuxiang-zhi"; } 
      
int valid_learn(object me) 
{ 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
		return notify_fail("�����ư˴������֡�\n"); 
      
	if ((int)me->query_skill("force") < 300) 
		return notify_fail("����ڹ���򲻹����޷�ѧ���ư˴�\n"); 
     
	if ((int)me->query("max_neili") < 3000) 
		return notify_fail("�������̫�����޷������ư˴�\n"); 
      
	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("shenzhang-bada", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷�������������ư˴�\n");
      
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
	level = (int) me->query_skill("shenzhang-bada", 1); 
	for (i = sizeof(action); i > 0; i--) 
		if (level > action[i-1]["lvl"]) 
			return action[NewRandom(i, 20, level/5)]; 
} 
      
int practice_skill(object me) 
{ 
	if (me->query_temp("weapon") || 
	    me->query_temp("secondary_weapon")) 
		return notify_fail("����������ϰ��\n"); 
      
	if ((int)me->query("qi") < 100) 
		return notify_fail("�������̫���ˡ�\n"); 
      
	if ((int)me->query("neili") < 80) 
		return notify_fail("����������������ư˴�\n"); 
      
	me->receive_damage("qi", 90); 
	me->add("neili", -70); 
	return 1; 
} 
      
string perform_action_file(string action) 
{ 
	return __DIR__"shenzhang-bada/" + action; 
} 
