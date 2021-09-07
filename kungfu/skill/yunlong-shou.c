// yunlongshou.c -������

inherit SKILL;

mapping *action = ({
([	"action" : "$Nһʽ����ľ�Ա�����ʮָ����������ʵʵ��Ϯ��$n��ȫ��ҪѨ",
	"force" : 80,
	"dodge" : 30,
	"damage": 15,
	"lvl" : 0,
	"skill_name" : "��ľ�Ա�",
	"damage_type" : "ץ��"
]),
([	"action" : "�ں��������У�$Nʹһ�С�����׽Ӱ����˫���繳��ꫣ�����$n��$l",
	"force" : 100,
	"dodge" : 35,
	"damage": 20,
	"lvl"   : 30,
	"skill_name" : "����׽Ӱ" ,		
	"damage_type" : "����"
]),
([	"action" : "$N˫ȭ���裬һʽ������ȥ���������ֻ��ۣ�£��Ȧ״���ͻ�$n�����",
	"force" : 120,
	"dodge" : 30,
	"damage": 25,
	"lvl" : 60,
	"skill_name" : "����ȥ��",
	"damage_type" : "����"
]),
([	"action" : "$N˫��ƽ�죬ʮָ΢΢���¶�����һ�С�ʮָǬ��������$n��$l",
	"force" : 140,
	"dodge" : 35,
	"damage": 30,
	"lvl"   : 80,
	"skill_name" : "ʮָǬ��" ,		
	"damage_type" : "����"
]),
([	"action" : "$N���ֻ��أ�Ҹ�º��գ�������ָ�繳��һ�С�������ȱ������$n�Ķ���",
	"force" : 160,
	"dodge" : 40,
	"damage": 30,
	"lvl"   : 100,
	"skill_name" : "������ȱ" ,		
	"damage_type" : "����"
]),
([	"action" : "$N����б��$n����֮�䣬һ�С��������项������ȡĿ�����ַ���$n���ɲ�",
	"force" : 180,
	"dodge" : 35,
	"damage": 40,
	"lvl"   : 120,
	"skill_name" : "��������" ,		
	"damage_type" : "����"
]),
([	"action" : "$Nһ����ָ$n�Ľ�����һ�С��������С�������ץ��$n���еı���",
	"force" : 210,
	"dodge" : 35,
	"damage": 45,
	"lvl"   : 130,
	"skill_name" : "��������" ,		
	"damage_type" : "ץ��"
]),
([	"action" : "$N����ָ��$n��ǰ�������Ѩ������бָ̫��Ѩ��һ�С�����������ʹ$n��������",
	"force" : 230,
	"dodge" : 40,
	"damage": 50,
	"lvl"   : 140,
	"skill_name" : "��������" ,		
	"damage_type" : "����"
]),
([	"action" : "$Nһ�ֶ����צ��һ��ָ�أ�һ�С����Ƽ��ա�,��������$n��ȫ��",
	"force" : 250,
	"dodge" : 50,
	"damage": 55,
	"lvl"   : 150,
	"skill_name" : "���Ƽ���" ,		
	"damage_type" : "����"
]),
([	"action" : "$Nһʽ���������¡���ȭ���������֣��������ޣ�����������$n�ĵ���",
	"force" : 270,
	"dodge" : 60,
	"damage": 60,
	"lvl" : 160,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([	"action" : "$N���������ʹһʽ���������ɡ�������΢��,��������$n��$l",
	"force" : 290,
	"dodge" : 60,
	"parry" : 60,
	"damage": 70,
	"lvl" : 170,
	"skills_name" : "��������",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="hand" ||  usage=="parry"; }

int valid_combine(string combo) { return combo=="yunlong-zhua"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������ֱ�����֡�\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("��������񹦻�򲻹����޷�ѧ�����֡�\n");

	if ((int)me->query("max_neili") < 700)
		return notify_fail("�������̫�����޷��������֡�\n");

	if ((int)me->query_skill("hand",1) < 100)
		return notify_fail("��Ļ����ַ���򲻹����޷�ѧ�����֡�\n");

	if ((int)me->query_skill("hand",1) < (int)me->query_skill("yunlong-shou",1))
		return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷�����ѧ�����֡�\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action); i > 0; i--)
		if(level >= action[i-1]["lvl"])
			return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level   = (int) me->query_skill("yunlong-shou",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];

}


int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("������������������֡�\n");

	me->receive_damage("qi", 62);
	me->add("neili", -59);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yunlong-shou/" + action;
}
