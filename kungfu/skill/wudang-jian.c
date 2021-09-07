// wudang-jian.c �䵱����

inherit SKILL;

mapping *action = ({
([      "action" : "$N������ת�����ֽ�ָ��������ϥ����ǰ������������ǰ��һ�紦�̴ٶ���"
		   "����һ�С��������֡�������$w���������һ�����϶�������$n��$l",
	"force"  : 120,
	"dodge"  : 20,
	"damage" : 25,
	"lvl"    : 0,
	"skill_name" : "��������",
	"damage_type": "����"
]),
([      "action" : "$N���β�������ǰ�������������ϱ������������󹭲���һ�С�������ˮ������"
		   "��$w��ǰ�·��̣�һ��ָ��$n��$l",
	"force"  : 120,
	"dodge"  : 20,
	"damage" : 20,
	"lvl"    : 10,
	"skill_name" : "������ˮ",
	"damage_type": "����"
]),
([      "action" : "$N�����ǰһ�����ŵ����������ڿռ�����ת������$w����ǰ�̣���ת���"
		   "��ʹ��һʽ�����ֿ�ѡ���������ƥ����й��$n��$l",
	"force"  : 140,
	"dodge"  : 15,
	"damage" : 25,
	"lvl"    : 20,
	"skill_name" : "���ֿ��",
	"damage_type": "����"
]),
([      "action" : "$N�鲽�������ὣ�ؽ��������ϱ���һ�С��������š�ֱȡ$n��$l",
	"force"  : 150,
	"dodge"  : 15,
	"damage" : 35,
	"lvl"    : 30,
	"skill_name" : "��������",
	"damage_type": "����"
]),
([      "action" : "$Nƽ��бϴ����Բ��ֱ��˫�Ž��满������������$wʹ��һʽ����Ů���󡹣�"
		   "����������ת�������಻������$n��$l",
	"force"  : 130,
	"dodge"  : 25,
	"damage" : 25,
	"lvl"    : 40,
	"skill_name" : "��Ů����",
	"damage_type": "����"
]),
([      "action" : "$N����̧�ۣ�����ǰ����Ϸ������ͦ����ƽ��������ǰ������$wʹ��һʽ"
		   "������ָ·������$n��$l",
	"force"  : 120,
	"dodge"  : 25,
	"damage" : 25,
	"lvl"    : 50,
	"skill_name" : "����ָ·",
	"damage_type": "����"
]),
([      "action" : "$N�󳷲����������أ��ӽ���Բ���Σ���������������$wһʽ�����б��¡���"
		   "����Բ�󣬴���$n��$l",
	"force" : 110,
	"dodge" : 15,
	"lvl"   : 60,
	"skill_name" : "���б���",
	"damage_type": "����"
]),
([      "action" : "$N�����˲������ֽ�ָ��ת������һŤ���������������$wһ�ǡ���������"
		   "��������ָ��$n��$l",
	"force"  : 150,
	"dodge"  : 35,
	"damage" : 40,
	"lvl"    : 70,
	"skill_name" : "������",
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

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("wudang-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷�����������䵱������\n");

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
	level = (int) me->query_skill("wudang-jian", 1);
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
		return notify_fail("��������������䵱������\n");

	if ((int)me->query("neili") < 10)
		return notify_fail("��������������䵱������\n");

	me->receive_damage("qi", 25);
	me->add("neili", -1);

	return 1;
}

