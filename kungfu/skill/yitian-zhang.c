// tianchang-zhang.c �쳤�Ʒ�
// modified by Venus Oct.1997

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$Nʹ�������������е�һʽ"+HIY"����������"NOR+"��һ��"
		   "һ���������ھ�������$n��$l",
	"force" : 110,
	"dodge" : 5,
	"parry" : 7,
	"damage": 6,
	"damage_type" : "����",
	"lvl" : 0,
	"skill_name" : "��������"
]),
([      "action" : "$Nʹ�������������е�һʽ"+HIY"������������"NOR+"������"
		   "���ֱʻ����࣬�ʻ���Ĳ����䷱������$n��$l",
	"force" : 148,
	"dodge" : 15,
	"parry" : 27,
	"damage": 15,
	"damage_type" : "����",
	"lvl" : 30,
	"skill_name" : "��������"
]),
([      "action" : "$Nʹ�������������е�һʽ"+HIY"���������¡�"NOR+"������"
		   "���ֱʻ����٣��ʻ��ٵĲ�����ª������$n��$l",
	"force" : 195,
	"dodge" : 22,
	"parry" : 33,
	"damage": 19,
	"damage_type" : "����",
	"lvl" : 50,
	"skill_name" : "��������"
]),
([      "action" : "$Nʹ�������������е�һʽ"+HIY"��Ī�Ҳ��ӡ�"NOR+"������"
		   "Ҳ���أ��Ƴ��֮��������Ҳ�վ��������֮�ѣ���\n��$n��$l",
	"force" : 245,
	"dodge" : 32,
	"parry" : 41,
	"damage": 23,
	"damage_type" : "����",
	"lvl" : 80,
	"skill_name" : "Ī�Ҳ���"
]),
([      "action" : "$Nʹ�������������е�һʽ"+HIY"�����첻����"NOR+"������"
		   "�������ۻ�ս������ݴ����Ʈ����ѩ�裬���ش���\n���ף�"
		   "���󲽣�����$n��$l",
	"force" : 280,
	"dodge" : 37,
	"parry" : 46,
	"damage": 29,
	"damage_type" : "����",
	"lvl" : 120,
	"skill_name" : "���첻��"
]),
([      "action" : "$Nʹ�������������е�һʽ"+HIY"��˭�����桻"NOR+"����Х"
		   "һ��������ֱ���������������ǽ���â����ʸӦ����\n����Ͼ"
		   "�����粻���ɣ���һֱ���ǡ��桱�ֵ����һ�ʣ�ֱ����$n��$l",
	"force" : 330,
	"dodge" : 45,
	"parry" : 57,
	"damage": 36,
	"damage_type" : "����",
	"lvl" : 160,
	"skill_name" : "˭������"
]),
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }  

int valid_combine(string combo) { return combo == "hujia-quan"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����������Ʊ�����֡�\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���򲻹����޷������������ơ�\n");
	
	if ((int)me->query("max_neili") < 750)
		return notify_fail("�������̫�����޷������������ơ�\n");

	if ((int)me->query_skill("strike", 1) < 80)
		return notify_fail("��Ļ����Ʒ���򲻹����޷���ϰ���������ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("yitian-zhang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷�������������������ơ�\n");

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
	level = (int)me->query_skill("yitian-zhang", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("����������������������ơ�\n");

	me->receive_damage("qi", 55);
		me->add("neili", -62);

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yitian-zhang/" + action;
}

