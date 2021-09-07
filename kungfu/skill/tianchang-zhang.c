// tianchang-zhang.c �쳤�Ʒ�
// modified by Venus Oct.1997

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$Nһʽ"+HIC"��Ǳ��Ĭ����"NOR+"�������ȷ������ƺ���������$n��$l",
	"force" : 60,
	"dodge" : 30,
	"damage": 5,
	"damage_type" : "����",
	"lvl" : 0,
	"skill_name" : "Ǳ��Ĭ��"
]),
([      "action" : "$N������ϣ�һ��"+HIB"�����Ǵ��¡�"NOR+"��˫�����������$n��$l",
	"force" : 100,
	"dodge" : 25,
	"damage": 10,
	"damage_type" : "����",
	"lvl" : 30,
	"skill_name" : "���Ǵ���"
]),
([      "action" : "$N����Ծ��ʹ��"+BLU"�������ܲ���"NOR+"������������Ӱ������$n��$l",
	"force" : 140,
	"dodge" : 20,
	"damage": 15,
	"damage_type" : "����",
	"lvl" : 50,
	"skill_name" : "�����ܲ�"
]),
([      "action" : "$N�����˿�һ��������һʽ"+HIW"����������"NOR+"��������������"
		   "���ƣ�������������İ���Ϯ��$n��$l",
	"force" : 170,
	"dodge" : 25,
	"damage": 15,
	"damage_type" : "����",
	"lvl" : 90,
	"skill_name" : "��������"
]),
([      "action" : "$N˫��ͻȻһ���������ƿ���һʽ"+HIW"���������ߡ�"NOR+"���Ƴ�����"
		   "��������$n��$l",
	"force" : 190,
	"dodge" : 30,
	"damage": 25,
	"damage_type" : "����",
	"lvl" : 110,
	"skill_name" : "��������"
]),
([      "action" : "$Nб�ﴩ����ʹ��"+RED"�������ƻ�"NOR+"��˫��Ĭ���ھ���$n���ؿ�"
		   "ƽ�Ƴ�һ��������Ϣ�����ȵľ���",
	"force" : 210,
	"dodge" : 25,
	"damage": 25,
	"damage_type" : "����",
	"lvl" : 130,
	"skill_name" : "�����ƻ�"
]),
([      "action" : "$Nʩչ��"+HIR"����ζ���"NOR+"����������ǰ΢΢һ�ڣ�������һ�̣�"
		   "���������͵�һ�ƣ��������������һ����������$n���ؿ�",
	"force" : 250,
	"parry" : 45,
	"dodge" : 35,
	"damage": 45,
	"damage_type" : "����",
	"lvl" : 150,
	"skill_name" : "��ζ���"
]),
([      "action" : "$Nʹһʽ"+WHT"���ºڷ�ߡ�"NOR+"��˫�Ƶ�������������������$n��$l",
	"force" : 270,
	"parry" : 55,
	"dodge" : 40,
	"damage": 50,
	"damage_type" : "����",
	"lvl" : 170,
	"skill_name" : "�ºڷ��"
]),
([      "action" : "$Nʹ��"+HIW"������ȸߡ�"NOR+"��˫�ƻ���������գ�������Ȼ�����ջأ�"
		   "��$n�͵��Ƴ�",
	"force" : 300,
	"parry" : 50,
	"dodge" : 35,
	"damage": 65,
	"damage_type" : "����",
	"lvl" : 180,
	"skill_name" : "����ȸ�"
]),
([      "action" : "$N����Ǳ����ʩչ��"+HIY"������ͬ�ԡ�"NOR+"��˫��б���������ҿ�������"
		   "������������$n��$l",
	"force" : 330,
	"parry" : 50,
	"dodge" : 35,
	"damage": 70,
	"damage_type" : "����",
	"lvl" : 190,
	"skill_name" : "����ͬ��"
]),
([      "action" : "$N˫�ƽ���һ����������һ����ʹ��"+HIY"���������ԡ�"NOR+"�����������ϣ�"
		   "�����£�����ʯ��ط�������$n",
	"force" : 350,
	"parry" : 55,
	"dodge" : 45,
	"damage": 75,
	"damage_type" : "����",
	"lvl" : 200,
	"skill_name" : "��������"
])
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }  

int valid_combine(string combo) { return combo == "hujia-quan"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���쳤�Ʒ�������֡�\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���򲻹����޷����쳤�Ʒ���\n");
	
	if ((int)me->query("max_neili") < 750)
		return notify_fail("�������̫�����޷����쳤�Ʒ���\n");

	if ((int)me->query_skill("strike", 1) < 80)
		return notify_fail("��Ļ����Ʒ���򲻹����޷���ϰ�쳤�Ʒ���\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("tianchang-zhang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷����������쳤�Ʒ���\n");

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
	level = (int)me->query_skill("tianchang-zhang", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("��������������쳤�Ʒ���\n");

	me->receive_damage("qi", 55);
		me->add("neili", -62);

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"tianchang-zhang/" + action;
}
