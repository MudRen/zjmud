// duoluoye-zhi.c - ���ֶ���Ҷָ(��Ϊ�Ե����书)
       
inherit SHAOLIN_SKILL;
	
mapping *action = ({
([     "action": "$N����ǰ�㣬��ָ����һ�ž��磬Ʈ�����εĻ���$n��$l",
       "force" : 180,
       "attack": 80,
       "parry" : 30,
       "dodge" : 15,
       "damage": 70,
       "lvl"   : 0,
       "damage_type" : "����"
]),
([     "action": "$N���󲻶���ӡ������Ծ��˫�ֻ�������$n������ָ��֮��",
       "force" : 200,
       "attack": 90,
       "parry" : 45,
       "dodge" : 10,
       "damage": 95,
       "lvl"   : 40,
       "damage_type" : "����"
]),
([     "action": "$N������ϣ���ָ����ֱ�룬�ڵ�$n�Ĵ�Ѩ��һ�����ܾ��˵Ĵ�",
       "force" : 250,
       "attack": 100,
       "parry" : 50,
       "dodge" : 35,
       "damage": 110,
       "lvl"   : 80,
       "damage_type" : "��Ѩ"
]),
([     "action": "$N����Ծ�𣬾Ӹ����£�˫�ֱַ����$n�ĸ���ҪѨ",
       "force" : 300,
       "attack": 90,
       "parry" : 45,
       "dodge" : 10,
       "damage": 120,
       "lvl"   : 120,
       "damage_type" : "��Ѩ"
]),
([     "action": "$N��������ע��ָ�䣬һָ�������²��ɵ���Ӳ����$n�������У�����$n��$l",
       "force" : 420,
       "attack": 50,
       "parry" : 30,
       "dodge" : -15,
       "damage": 100,
       "lvl"   : 160,
       "damage_type" : "����"
]),
([     "action": "$N�粽��ǰ��ͻȻ������ָ������һ���ǳɣ��������ָ�����$n",
       "force" : 260,
       "attack": 150,
       "parry" : 50,
       "dodge" : 25,
       "damage": 80,
       "lvl"   : 200,
       "damage_type" : "����"
]),
([     "action": "$N������ϣ�����ʳָ�������������$n��$l���ƺ���������",
       "force" : 500,
       "attack": 60,
       "parry" : 55,
       "dodge" : 35,
       "damage": 120,
       "lvl"   : 240,
       "damage_type" : "����"
]),
([     "action": "$N������ǰ������ȫ������˫ָ��������ָ�磬��$n��ȫ�����ڹ���֮��",
       "force" : 450,
       "attack": 70,
       "parry" : 60,
       "dodge" : 65,
       "damage": 180,
       "lvl"   : 280,
       "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; } 
      
int valid_learn(object me) 
{ 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
		return notify_fail("������Ҷָ������֡�\n"); 
      
	if ((int)me->query_skill("force") < 150) 
		return notify_fail("����ڹ���򲻹����޷�ѧϰ����Ҷָ��\n"); 
     
	if ((int)me->query("max_neili") < 2000) 
		return notify_fail("�������̫�����޷�������Ҷָ��\n"); 
      
	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("duoluoye-zhi", 1))
		return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷���������Ķ���Ҷָ��\n"); 
      
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
	level = (int) me->query_skill("duoluoye-zhi", 1); 
	for (i = sizeof(action); i > 0; i--) 
		if (level > action[i-1]["lvl"]) 
			return action[NewRandom(i, 20, level/5)]; 
} 
      
int practice_skill(object me) 
{ 
	if (me->query_temp("weapon") || 
	    me->query_temp("secondary_weapon")) 
		return notify_fail("����������ϰ��\n"); 
      
	if ((int)me->query("qi") < 130) 
		return notify_fail("�������̫���ˡ�\n"); 
      
	if ((int)me->query("neili") < 110) 
		return notify_fail("�����������������Ҷָ��\n");
      
	me->receive_damage("qi", 110);
	me->add("neili", -100); 
	return 1; 
} 
      
string perform_action_file(string action) 
{ 
	return __DIR__"duoluoye-zhi/" + action; 
}