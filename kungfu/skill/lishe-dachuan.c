// dragon-strike.c ����ʮ���� �����
// modified by Venus Oct.1997
// modified by Doing 1999

inherit SKILL;

mapping *action = ({
([      "action" : "$Nʩ��һ�С�����󴨡������Ʋ�������������$n��$l",
	"dodge"  : -10,
	"parry"  : 15,
	"force"  : 230,
	"damage" : 70,
	"damage_type": "����"
]),
});

string main_skill() { return "dragon-strike"; }

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }  

int valid_learn(object me)
{
	if (me->query_skill("dragon_strike", 1) > 0)
		return notify_fail("���Ѿ�ѧȫʮ�����ˣ������ٵ���ѧϰ��\n");

	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������ʮ���Ʊ�����֡�\n");

	if ((int)me->query("str") < 30)
		return notify_fail("���������ӹǻ�������ʮ���ƣ�С��Ū���˸첲��\n");

	if ((int)me->query_skill("force") < 90)
		return notify_fail("����ڹ���򲻹��޷�ѧϰ����ʮ���ơ�\n");

	if ((int)me->query("max_neili") < 600)
		return notify_fail("�������̫���޷�ѧϰ����ʮ���ơ�\n");

	if ((int)me->query_skill("strike", 1) < 30)
		return notify_fail("��Ļ����Ʒ���򲻹����޷�ѧϰ����ʮ���ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("lishe-dachuan", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ľ���ʮ���ơ�\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 120)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 50)
		return notify_fail("�����������������ʮ���ơ�\n");

	me->receive_damage("qi", 100);
	me->add("neili", -40);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"lishe-dachuan/" + action;
}

