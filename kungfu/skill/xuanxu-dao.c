inherit SKILL;

mapping *action = ({
([      "action": "$Nһʽ���������ﶯ��ɫ���ײ��ŵ���ѩɽ������̤���㡹λ������$w�����ŵ���Ӱ����\n"
		  "$n��$l",
	"force" : 30,
	"attack": 25,
	"dodge" : 20,
	"parry" : 25,
	"damage": 15,
	"lvl"   : 0,
	"damage_type" : "����"
]),
([      "action": "$Nһʽ�����ӵ�����ʯ������¯�ٲ�ң����������ռ������λ������$w����ƬƬ����, ��\n"
		  "���ӵ�к�����$n$l",
	"force" : 33,
	"attack": 32,
	"dodge" : 26,
	"parry" : 38,
	"damage": 18,
	"lvl"   : 20,
	"damage_type" : "����"
]),
([      "action": "$Nһʽ���Ǹ�׳����ؼ䣬��ããȥ���ơ���������λ������$w��Ϊ���쵶Ӱ����\n"
		  "����������������$n$l",
	"force" : 40,
	"attack": 38,
	"dodge" : 32,
	"parry" : 43,
	"damage": 22,
	"lvl"   : 40,
	"damage_type" : "����"
]),
([      "action": "$Nһʽ��ɽ������������������ƾ���ӷ��꡹��������ȹѻ����ڡ��ޡ�λͻ��һ��������ѹ\n"
		  "ǧ��֮������$n$l",
	"force" : 60,
	"attack": 42,
	"dodge" : 45,
	"parry" : 45,
	"damage": 26,
	"lvl"   : 60,
	"damage_type" : "����"
]),
([      "action": "$Nһʽ����̨���·�ҹ��һ����ʯ���綷�������弱����ת���ڡ��롹λ��һ�����磬����\n"
		  "$w৵ؿ���$n��$l",
	"force" : 80,
	"attack": 45,
	"dodge" : 50,
	"parry" : 55,
	"damage": 32,
	"lvl"   : 80,
	"damage_type" : "����"
]),
([      "action": "$Nһʽ��ɱ����ʱ�����ƣ�����һҹ���󶷡���ռס���ҡ�λ������$w��������ɱ������\n"
		  "$n��$l",
	"force" : 90,
	"attack": 52,
	"dodge" : 65,
	"parry" : 55,
	"damage": 40,
	"lvl"   : 100,
	"damage_type" : "����"
]),
});
int valid_enable(string usage) { return (usage == "blade") || (usage == "parry"); }

int valid_learn(object me)
{
    if ((int)me->query("max_neili") < 500)
	return notify_fail("���������Ϊ������\n");

    if ((int)me->query_skill("force") < 100)
	return notify_fail("����ڹ����̫ǳ��\n");

    if ((int)me->query_skill("blade", 1) < (int)me->query_skill("xuanxu-dao", 1))
	return notify_fail("��Ļ�������ˮƽ���ޣ��޷�������������鵶����\n");

    return 1;
}
string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action)-1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("xuanxu-dao", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
    object weapon;

    if (! objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "blade")
	return notify_fail("��ʹ�õ��������ԡ�\n");

    if ((int)me->query("qi") < 60)
	return notify_fail("����������������鵶����\n");

    if ((int)me->query("neili") < 60)
	return notify_fail("����������������鵶����\n");

    me->receive_damage("qi", 45);
    me->add("neili", -43);
    return 1;
}
string perform_action_file(string action)
{
	return __DIR__"xuanxu-dao/" + action;
}

