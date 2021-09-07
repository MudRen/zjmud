// yinsuo-jinling.c ��������
// Vin 5/3/2001

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N����������һ�С���̨��ױ��������$w���ñ�ֱ����׼$n$lֱ�̶�ȥ",
	"force" : 80,
	"attack": 30,
	"dodge" : 35,
	"parry" : 25,
	"damage": 30,
	"lvl"   : 0,
	"skill_name" : "��̨��ױ",
	"damage_type": "����"
]),
([      "action": "$N����һת��һ�С������׺ס�������$w��������ڿ�һ���͵���$n��ͷ����",
	"force" : 130,
	"attack": 38,
	"dodge" : 43,
	"parry" : 27,
	"damage": 45,
	"lvl"   : 40,
	"skill_name" : "�����׺�",
	"damage_type": "����"
]),
([      "action": "$N������ң�һ�С�����ǧ�������$w��������Ӱ������ǵ�Ϯ��$nȫ��",
	"force" : 160,
	"attack": 45,
	"dodge" : 63,
	"parry" : 29,
	"damage": 61,
	"lvl"   : 80,
	"skill_name" : "����ǧ��",
	"damage_type": "����"
]),
([      "action":"$Nһ�����ȣ�һ�С�ӳ��������������$w�任Ī�⣬�����벻���ķ�λɨ��$n",
	"force" : 180,
	"attack": 50,
	"dodge" : 65,
	"parry" : 33,
	"damage": 68,
	"lvl"   : 120,
	"skill_name" : "ӳ������",
	"damage_type": "����"
]),
([      "action":"$N����һԾ�������һ�С�Ӱ����ԡ���$w��������ͨ�죬Я�����ƿ�֮��Ϯ��$n",
	"force" : 210,
	"attack": 53,
	"dodge" : 76,
	"parry" : 36,
	"damage": 73,
	"lvl"   : 160,
	"skill_name" : "Ӱ�����",
	"damage_type": "����"
]),
([      "action":"$N����Ʈ���޶���һ�С����к�ء�������$w�ó�������Ӱ������$nȫ��",
	"force" : 230,
	"attack": 65,
	"dodge" : 92,
	"parry" : 35,
	"damage": 91,
	"lvl"   : 180,
	"skill_name":  "���к��",
	"damage_type": "����"
]),
([      "action":"$N����Ʈ���޶���һ�С���¥��ɳ��������$w�ó�������Ӱ������$nȫ��",
	"force" : 251,
	"attack": 66,
	"dodge" : 117,
	"parry" : 40,
	"damage": 120,
	"lvl"   : 200,
	"skill_name" : "��¥��ɳ",
	"damage_type": "����"
]),
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
	object weapon;

	if (me->query("gender") != "Ů��")
		return notify_fail("��������ֻ��Ů��������\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "whip")
		return notify_fail("���������һ�����Ӳ������������塣\n");

	if ((int)me->query("max_neili") < 500)
		return notify_fail("����������㣬û�а취���������壬����Щ���������ɡ�\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ����̫ǳ��û�а취���������塣\n");

	if ((int)me->query_skill("whip", 1) < 20)
		return notify_fail("��Ļ����޷����̫ǳ��û�а취���������塣\n");

	if ((int)me->query_skill("whip", 1) < (int)me->query_skill("yinsuo-jinling", 1))
		return notify_fail("��Ļ����޷�ˮƽ���������޷�����������������塣\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("yinsuo-jinling", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "whip")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 50)
		return notify_fail("��������������������塣\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("��������������������塣\n");

	me->receive_damage("qi", 45);
	me->add("neili", -55);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yinsuo-jinling/" + action;
}
