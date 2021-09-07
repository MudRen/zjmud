// yuenv-jian.c ԽŮ����

inherit SKILL;

mapping *action = ({
([      "action" : "$N����$w�������$n��$l��Ѹ���ޱ�",
	"force"  : 70,
	"dodge"  : 60,
	"parry"  : 12,
	"damage" : 50,
	"lvl"    : 0,
	"damage_type" : "����"
]),
([      "action" : "$N��Ծ�������е�$w����һ����������Ȼ����$n",
	"force"  : 90,
	"dodge"  : 65,
	"parry"  : 15,
	"damage" : 54,
	"lvl"    : 20,
	"damage_type" : "����"
]),
([      "action" : "$Nʹ������ಽ�����е�$wб��$n��$l",
	"force"  : 100,
	"dodge"  : 70,
	"parry"  : 10,
	"damage" : 60,
	"lvl"    : 50,
	"damage_type" : "����"
]),
([      "action" : "$Nȴ���Ჽ�����е�$w�Ƶ��ɵ����ƽ��ǽ�������ֱ��$n",
	"force"  : 120,
	"dodge"  : 78,
	"parry"  : 10,
	"damage" : 80,
	"lvl"    : 75,
	"damage_type" : "����"
]),
([      "action" : "$N����$w�����ļ��죬ֻ�ϵ�$n�ۻ����ң��벻֪�Ӻι���",
	"force"  : 130,
	"dodge"  : 85,
	"parry"  : 12,
	"damage" : 95,
	"lvl"    : 100,
	"damage_type" : "����"
]),
([      "action" : "$N�������𣬽�����ָ�����������ƣ�ֱ��$n��$l",
	"force"  : 150,
	"dodge"  : 90,
	"parry"  : 18,
	"damage" : 100,
	"lvl"    : 130,
	"damage_type" : "����"
]),
([      "action" : "$N����$w��������һ�̣�û���κλ��ɣ�Ȼ�����ƿ�ò���˼��",
	"force"  : 180,
	"dodge"  : 95,
	"parry"  : 15,
	"damage" : 110,
	"lvl"    : 160,
	"damage_type" : "����"
]),
([      "action" : "$N��̾һ�������е�$w����һ����������$n",
	"force"  : 200,
	"dodge"  : 100,
	"parry"  : 22,
	"damage" : 120,
	"lvl"    : 200,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�����е�$w���������������������$n",
	"force"  : 220,
	"dodge"  : 105,
	"parry"  : 25,
	"damage" : 125,
	"lvl"    : 225,
	"damage_type" : "����"
]),
([  "action" : "$Nһ����Ц������$w�û��������ǵ㣬��֪����$n�ĺδ�",
	"force"  : 250,
	"dodge"  : 115,
	"parry"  : 30,
	"damage" : 150,
	"lvl"    : 250,
	"damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻵����޷�����ԽŮ������\n");

	if ((int)me->query_skill("sword", 1) < 100)
		return notify_fail("��Ľ������ײ��У��������ԽŮ������\n");

	if ((int)me->query("neili") < 800)
		return notify_fail("�������̫��޷�ѧϰԽŮ������\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("yuenv-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������ԽŮ������\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("yuenv-jian", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("�������������ԽŮ������\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("���������������ԽŮ������\n");

	me->receive_damage("qi", 64);
	me->add("neili", -65);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yuenv-jian/" + action;
}

