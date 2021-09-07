inherit SHAOLIN_SKILL;
	
mapping *action = ({
([
       "action": "$N����һ����Σ���ָ������һ�С�������ӥ������ָ����$n��$l",
       "force" : 80,
       "attack": 25,
       "parry" : 15,
       "dodge" : -5,
       "damage" : 50,
       "lvl"   : 0,
       "skill_name" : "������ӥ",
       "damage_type" : "����"
]),
([
       "action": "$N������ϣ��������һ����һʽ��Ͷ�������,��ͼ��ס$n�������Ѩ",
       "force" : 100,
       "attack": 30,
       "parry" : 15,
       "dodge" : 0,
       "damage" : 65,
       "lvl"   : 20,
       "skill_name" : "Ͷ�����",
       "damage_type" : "��Ѩ"
]),
([
       "action": "$N��¶�׹⣬һʽ���ͷл�졹,��ֱָ����$n�İٻ��Ѩ",
       "force" : 150,
       "attack": 50,
       "parry" : 5,
       "dodge" : -15,
       "damage" : 100,
       "lvl"   : 40,
       "skill_name" : "�ͷл��",
       "damage_type" : "��Ѩ"
]),
([
       "action": "$N��ָ�絶��һ�С��۹ǳ��衹,˫ָ����һ����·����$n������",
       "force" : 150,
       "attack": 30,
       "parry" : 25,
       "dodge" : 10,
       "damage" : 100,
       "lvl"   : 60,
       "skill_name" : "�۹ǳ���",
       "damage_type" : "����"
]),
([
       "action": "$N��Ȼ�������ݣ�˫ָ���㣬һ�С�����ǧ�ơ���һʱ������������ͬʱ����$n",
       "force" : 180,
       "attack": 45,
       "parry" : 0,
       "dodge" : -15,
       "damage" : 120,
       "lvl"   : 80,
       "skill_name" : "����ǧ��",
       "damage_type" : "����"
]),
([
       "action": "$N�������Σ�һ�С����۲�ʩ��,�Ӹ����£���Ѷ�ײ����ڶ����ٶȹ���$n",
       "force" : 180,
       "attack": 35,
       "parry" : 0,
       "dodge" : -15,
       "damage" : 100,
       "lvl"   : 100,
       "skill_name" : "���۲�ʩ",
       "damage_type" : "����"
]),
([
       "action": "$N˫ָ��������·��һ�С���Ƥ�龭�����ֱ����$n������Ѩ����$n�벻����",
       "force" : 200,
       "attack": 50,
       "parry" : 10,
       "dodge" : 15,
       "damage" : 120,
       "lvl"   : 120,
       "skill_name" : "��Ƥ�龭",
       "damage_type" : "��Ѩ"
]),
([
       "action": "$Nһ�С����ľ�־����һָ��׼�Լ������͵�һ������������ʳָ����$n��$l",
       "force" : 220,
       "attack": 60,
       "parry" : 20,
       "dodge" : 25,
       "damage" : 130,
       "lvl"   : 160,
       "skill_name" : "���ľ�־",
       "damage_type" : "����"
]),
([
       "action": "$Nһ�С���Ѫ���ء���˫��ʮָ������һʱ�������������糱ˮ��ӿ��$n����$n�޴Ӷ���",
       "force" : 300,
       "attack": 100,
       "parry" : 40,
       "dodge" : 55,
       "damage" : 200,
       "lvl"   : 200,
       "skill_name" : "��Ѫ����",
       "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; } 
      
int valid_learn(object me) 
{ 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
		return notify_fail("������ָ������֡�\n"); 
      
	if ((int)me->query_skill("force") < 200) 
		return notify_fail("����ڹ���򲻹����޷�ѧ����ָ��\n"); 
     
	if ((int)me->query("max_neili") < 800) 
		return notify_fail("�������̫�����޷�������ָ��\n"); 
      
	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("xiuluo-zhi", 1))
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
	level = (int) me->query_skill("xiuluo-zhi", 1); 
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
      
	me->receive_damage("qi", 80); 
	me->add("neili", -60); 
	return 1; 
} 
      
string perform_action_file(string action) 
{ 
	return __DIR__"xiuluo-zhi/" + action; 
} 


