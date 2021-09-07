// hannbing-mianzhang.c ��������
// pal 1997.05.26

inherit SKILL;

mapping *action = ({
([	"action" : "$Nһʽ���󽭶�ȥ����˫�ƴ󿪴�ϣ�ֱ��$n��$l��ȥ",
	"force" : 100,
	"dodge" : 15,
	"parry" : 20,
	"damage": 10,
	"lvl"   : 0,
	"skill_name" : "�󽭶�ȥ",
	"damage_type" : "����"
]),
([	"action" : "$N����һ�䣬һʽ���ƺӾ�������˫��������ֱ������$n��$l",
	"force" : 130,
	"dodge" : 10,
	"parry" : 15,
	"damage": 20,
	"lvl"   : 30,
	"skill_name" : "�ƺӾ���",
	"damage_type" : "����"
]),
([	"action" : "$Nʹһʽ������ɽɫ����������΢����棬������ϸ�����ֱȡ$n��$l",
	"force" : 160,
	"dodge" : 20,
	"parry" : 20,
	"damage": 25,
	"lvl"   : 60,
	"skill_name" : "����ɽɫ",
	"damage_type" : "����"
]),
([	"action" : "$N����һ�֣�һʽ�������׺���������������������$n�����ȥ",
	"force" : 180,
	"dodge" : 20,
	"parry" : 30,
	"damage": 30,
	"lvl"   : 80,
	"skill_name" : "�����׺�",
	"damage_type" : "����"
]),
([	"action" : "$N����һת��ʹ��һʽ��ˮ�����١���ֻ��������Ӱ��ס��$n��ȫ��",
	"force" : 210,
	"dodge" : 25,
	"parry" : 20,
	"damage": 35,
	"lvl"   : 100,
	"skill_name" : "ˮ������",
	"damage_type" : "����"
]),
([	"action" : "$NͻȻ����һ����ʹ��һʽ��С����硹���������أ�������ӯ������$n��$l",
	"force" : 250,
	"dodge" : 25,
	"parry" : 25,
	"damage": 40,
	"lvl"   : 120,
	"skill_name" : "С�����",
	"damage_type" : "����"
]),
([	"action" : "$Nʹһʽ����ѩ��ɽ����˫��Ю��籩ѩ֮�ƣ��͵�����$n��$l",
	"force" : 280,
	"dodge" : 30,
	"parry" : 30,
	"damage": 50,
	"lvl"   : 140,
	"skill_name" : "��ѩ��ɽ",
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С�˪�����ء���˫�ƴ�����ɪ������������$n��$l",
	"force" : 300,
	"dodge" : 30,
	"parry" : 35,
	"damage": 60,
	"lvl"   : 150,
	"skill_name" : "˪������",
	"damage_type" : "����"
]),
([	"action" : "$N����Ȼһ�䣬ʹ��һʽ���������������Ӱǧ����ã���$n�޷�����",
	"force" : 320,
	"dodge" : 40,
	"parry" : 45,
	"damage": 80,
	"lvl"   : 160,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
([	"action" : "$N��Хһ����һʽ����˪ѩ�꡹��˫�ƻ��裬��ͬѩ������ת������$n��$l",
	"force" : 350,
	"dodge" : 45,
	"parry" : 50,
	"damage": 100,
	"lvl"   : 180,
	"skill_name" : "�������",
	"damage_type" : "����"
])
});

int valid_enable(string usage)
{
	return usage=="strike" || usage=="parry";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���������Ʊ�����֡�\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���򲻹����޷����������ơ�\n");

	if ((int)me->query("max_neili") < 900)
		return notify_fail("�������̫�����޷����������ơ�\n");

	if ((int)me->query_skill("strike", 1) < 80)
		return notify_fail("��Ļ����Ʒ���򲻹����޷����������ơ�\n");

	if ((int)me->query_skill("strike", 1) < 80)
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ĺ������ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("hanbing-mianzhang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ĺ������ơ�\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level   = (int) me->query_skill("hanbing-mianzhang",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 60)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("��������������������ơ�\n");

	me->receive_damage("qi", 50);
	me->add("neili", -54);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int lvl;
	int flvl;

	lvl  = me->query_skill("hanbing-mianzhang", 1);
	flvl = me->query("jiali");
	if (lvl < 80 || flvl < 10 || ! damage_bonus || random(4))
		return;

    	if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
	    victim->affect_by("ice_poison",
			      ([ "level" : flvl + random(flvl),
				 "id"    : me->query("id"),
				 "duration" : lvl / 20 + random(lvl / 3) ])))
	{
		return "$n��Ȼ��ɫ��䣬һ����ս�����˼�����\n";
    	}
}

string perform_action_file(string action)
{
	return __DIR__"hanbing-mianzhang/" + action;
}
