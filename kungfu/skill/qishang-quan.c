// qishang-quan.c -����ȭ
// pal 1997.05.26

inherit SKILL;

mapping *action = ({
([	"action" : "$N������ɽ��һʽ�����������˫ȭ���ƶ���������$n��$l",
	"force" : 180,
	"dodge" : 5,
	"damage": 10,
	"lvl" : 0,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
([	"action" : "$N�������أ�����������һʽ��ľ�ѳ��ۡ���������$n�Ƴ�",
	"force" : 220,
	"dodge" : 5,
	"damage": 15,
	"lvl" : 40,
	"skill_name" : "ľ�ѳ���",
	"damage_type" : "����"
]),
([	"action" : "$N�������飬����������ޣ�һʽ��ˮ�����¡�����$n�޿ɶ���",
	"force" : 250,
	"dodge" : 15,
	"damage": 20,
	"lvl" : 70,
	"skill_name" : "ˮ������",
	"damage_type" : "����"
]),
([	"action" : "$N����Ծ��һʽ���𺣵�ɽ����˫ȭ���ջ��£��Ʋ��ɵ�",
	"force" : 290,
	"dodge" : 5,
	"damage": 30,
	"lvl" : 100,
	"skill_name" : "�𺣵�ɽ",
	"damage_type" : "����"
]),
([	"action" : "$N����һ����һʽ�������������ȭ���¶��ϣ�����$n",
	"force" : 330,
	"dodge" : 10,
	"damage": 45,
	"lvl" : 120,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([	"action" : "$N����һת��һʽ������Ҳҡ�������$n����ǰ���",
	"force" : 380,
	"dodge" : 25,
	"damage": 50,
	"lvl" : 140,
	"skill_name" : "����Ҳ�",
	"damage_type" : "����"
]),
([	"action" : "$N���λ�λ������ȭ����һʽ���������ա�������˷�����ȭӰ",
	"force" : 410,
	"dodge" : 15,
	"damage": 55,
	"lvl" : 150,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([	"action" : "$N��Хһ������ǰ̤��һ����˫ȭ�й�ֱ����һʽ�����߽��ˡ�����Ȼ����$n��ǰ��",
	"force" : 430,
	"dodge" : 20,
	"damage": 70,
	"lvl" : 160,
	"skill_name" : "���߽���",
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return  usage=="cuff" || usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������ȭ������֡�\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("��Ļ����ڹ�����120�����޷�ѧ����ȭ��\n");

	if ((int)me->query("max_neili") < 700)
		return notify_fail("��������������700�㣬�޷�������ȭ��\n");

	if ((int)me->query_skill("cuff", 1) < 100)
		return notify_fail("��Ļ���ȭ������100�����޷�������ȭ��\n");

	if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("qishang-quan", 1))
		return notify_fail("��Ļ���ȭ��ˮƽ���������޷��������������ȭ����\n");

	if ((int)me->query_skill("force", 1) < (int)me->query_skill("qishang-quan", 1) * 3 / 2)
		return notify_fail("����ڹ���Ϊ̫�����������������ȭ�����������塣\n");

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
	level   = (int) me->query_skill("qishang-quan",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("�����������������ȭ��\n");

	me->receive_damage("qi", 55);
	me->add("neili", -61);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"qishang-quan/" + action;
}
