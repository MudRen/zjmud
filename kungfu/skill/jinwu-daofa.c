// jinwu-dao.c ���ڵ�

inherit SKILL;

mapping *action = ({
([      "action" : "$N�ص����գ�һ�С�����鮵������������¶��ϻ��˸��뻡����$n��$l��ȥ",
	"force" : 20,
	"dodge" : -10,
	"parry" : 5,
	"damage": 10,
	"lvl" : 0,
	"skill_name" : "����鮵�",
	"damage_type" : "����"
]),
([      "action" : "$N�����������⣬һ�С�÷ѩ���ġ�������$w��ֱ����$n��$l",
	"force" : 30,
	"dodge" : -10,
	"parry" : 10,
	"damage": 15,
	"lvl" : 10,
	"skill_name" : "÷ѩ����",
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С�ǧ��ѹ�ա���$w�ƾ�������ˢ��һ�����϶�����$n����",
	"force" : 40,
	"dodge" : -5,
	"parry" : 5,
	"damage": 20,
	"lvl" : 20,
	"skill_name" : "ǧ��ѹ��",
	"damage_type" : "����"
]),
([      "action" : "$N���ַ�ִ������һ�С����ս�ġ�����һ����$wֱ��$n�ľ���նȥ",
	"force" : 60,
	"dodge" : 5,
	"parry" : 5,
	"damage": 25,
	"lvl" : 30,
	"skill_name" : "���ս��",
	"damage_type" : "����",
]),
([      "action" : "$Nһ�С��������ء����������⻯����㷱�ǣ���$n��$l��ȥ",
	"force" : 80,
	"dodge" : 10,
	"parry" : 5,
	"damage": 30,
	"lvl" : 40,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action" : "$N˫�ֺ�ִ$w��һ�С�����֮������š��ת������ֱ����$n��˫��",
	"force" : 110,
	"dodge" : 15,
	"parry" : 15,
	"damage": 35,
	"lvl" : 50,
	"skill_name" : "����֮��",
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С����ò����������$w����һ����ƽʮ�֣���$n�ݺ���ȥ",
	"force" : 140,
	"dodge" : 15,
	"parry" : 15,
	"damage": 40,
	"lvl" : 60,
	"skill_name" : "���ò��",
	"damage_type" : "����"
]),
([      "action" : "$N��ת�����׼�Լ���һ�С�������֦����ȫ��һ��������$w��$n����նȥ",
	"force" : 180,
	"dodge" : 20,
	"parry" : 10,
	"damage": 50,
	"lvl" : 70,
	"skill_name" : "������֦",
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С��������ס���$w�ĵ���·𻯳�һ�ش����棬��$n����Χ��",
	"force" : 220,
	"dodge" : 10,
	"parry" : 20,
	"damage": 55,
	"lvl" : 80,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action" : "$N����ƽָ��һ�С��󺣳�ɳ����һƬƬ�йǵ�����쫷�����$n��ȫ��",
	"force" : 270,
	"dodge" : 5,
	"parry" : 25,
	"damage": 60,
	"lvl" : 90,
	"skill_name" : "�󺣳�ɳ",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return (usage == "blade") || (usage == "parry")
; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 120)
		return notify_fail("�������������\n");
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
	level   = (int) me->query_skill("jinwu-daofa",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 50)
		return notify_fail("����������������ڵ�����\n");

	if ((int)me->query("neili") < 50)
		return notify_fail("����������������ڵ�����\n");

	me->receive_damage("qi", 30);
	me->add("neili", -31);
	return 1;
}
