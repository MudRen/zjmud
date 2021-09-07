// raozhi-roujian.c �䵱��ָ�ὣ

inherit SKILL;

mapping *action = ({
([      "action" : "$Nʹ��һ�С��������ǡ�������$w��һ�����߰����$n��$l",
	"force"  : 120,
	"dodge"  : 20,
	"parry"  : 14,
	"damage" : 25,
	"lvl"    : 0,
	"damage_type": "����"
]),
([      "action" : "$Nһʽ���仨���졹������$w�������콣Ӱֱ����$n��$l",
	"force"  : 120,
	"dodge"  : 20,
	"parry"  : 15,
	"damage" : 20,
	"lvl"    : 10,
	"damage_type": "����"
]),
([      "action" : "$Nʹ��һ�С��������¡�������$w���裬�����������Ȧ��$n��$l",
	"force"  : 140,
	"dodge"  : 15,
	"parry"  : 16,
	"damage" : 25,
	"lvl"    : 20,
	"damage_type": "����"
]),
([      "action" : "$N����һԾ��һ�С��˷��ȥ����ȴ��ת��֮�ʶ�׼$n$lбб�ӳ�һ��",
	"force"  : 150,
	"dodge"  : 15,
	"parry"  : 18,
	"damage" : 35,
	"lvl"    : 30,
	"damage_type": "����"
]),
([      "action" : "$N��̬���У�����$wƾ��һָ��һ�С�����ǧ�ء�����ػ���$n��$l",
	"force"  : 130,
	"dodge"  : 25,
	"parry"  : 21,
	"damage" : 25,
	"lvl"    : 40,
	"damage_type": "����"
]),
([      "action" : "$Nʹ��һ�С��Ǻ�Ӱ������������˸�������������޵ش���$n$l",
	"force"  : 120,
	"dodge"  : 25,
	"parry"  : 22,
	"damage" : 25,
	"lvl"    : 50,
	"damage_type": "����"
]),
([      "action" : "$N����$w����һ�֣�һ�С��������������ֶ�׼$n$lһ����ȥ",
	"force"  : 110,
	"dodge"  : 15,
	"parry"  : 35,
	"damage" : 38,
	"lvl"    : 60,
	"damage_type": "����"
]),
([      "action" : "$N����ת����ͣ��ͻȻһ�С�һ����Ϭ��ʹ��������$w����һ������������$n$l",
	"force"  : 150,
	"dodge"  : 35,
	"parry" :  45,
	"damage" : 43,
	"lvl"    : 70,
	"damage_type": "����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 20)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("raozhi-roujian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������ָ�ὣ��\n");

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
	level = (int) me->query_skill("raozhi-roujian", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 40)
		return notify_fail("���������������ָ�ὣ��\n");

	if ((int)me->query("neili") < 40)
		return notify_fail("���������������ָ�ὣ��\n");

	me->receive_damage("qi", 35);
	me->add("neili", -30);

	return 1;
}
string perform_action_file(string action)
{
	return __DIR__"raozhi-roujian/" + action;
}
