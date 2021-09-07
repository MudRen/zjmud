// ranmu-daofa.c ȼľ����
// By Vin On 27/12/2000

#include <ansi.h>

inherit SHAOLIN_SKILL;
 
mapping *action = ({
([      "action" : "$N���΢Ц��һ�С��һ���������$w����$n�����˰˰���ʮ�ĵ��������ݺᣬѸ�ײ��ɵ�",
	"dodge" : 1,
	"attack": 31,
	"force" : 231,
	"damage": 94,
	"parry" : 2,
	"lvl"   : 0,
	"damage_type": "����"
]),
([      "action": "$N���쳤Ц��ʩչ��һ�С������ԭ������ʱ�ó�����$wͬʱն��$n",
	"dodge" : 12,
	"attack": 37,
	"force" : 263,
	"damage": 151,
	"parry" : 3,
	"lvl"   : 30,
	"damage_type": "����"
]),
([      "action": "$N�����Ծ��Խ��$nͷ����һ�С�������ġ�������$wֱ�����£�ն��$n$l",
	"dodge" : 9,
	"attack": 31,
	"force" : 251,
	"damage": 189,
	"parry" : 4,
	"lvl"   : 100,
	"damage_type": "����"
]),
([      "action" : "$N�����ڹ�һ�С���ľ���𡹣�$w�ϴ����ޱȾ���������һ���󻡣����϶�������$n��$l",
	"dodge" : 16,
	"attack": 28,
	"force" : 242,
	"damage": 207,
	"parry" : 7,
	"lvl"   : 120,
	"damage_type": "����"
]),
([      "action": "$N�ֱ�һ����һ�С��Ź����¡���˫�ֳ�$w����һ��ѩ�����⣬�����������У�����$n��$l",
	"dodge" : 11,
	"attack": 33,
	"force" : 263,
	"damage": 219,
	"parry" : 9,
	"lvl"   : 140,
	"damage_type": "����"
]),
([      "action": "$N����$w�������ã����ҿ���ʹ��һ�С��һ����ơ����������󵶷磬��������$n",
	"dodge" : 17,
	"attack": 31,
	"force" : 289,
	"damage": 237,
	"parry" : 13,
	"lvl"   : 160,
	"damage_type": "����"
]),
([      "action": "$Nһ�С�����ȡ���������Ծ����أ�����$w������ǰ��Ю�����ȵķ�������$n��$l",
	"dodge" : 13,
	"attack": 41,
	"force" : 323,
	"damage": 261,
	"parry" : 4,
	"lvl"   : 180,
	"damage_type": "����"
]),
([      "action": "$N�ڿն��𣬰����һ�С���ʯ��١�������$w�ӳ����������ĵ�Ӱ����$n��ȫ���ȥ",
	"dodge" : 11,
	"attack": 34,
	"force" : 302,
	"damage": 289,
	"parry" : 7,
	"lvl"   : 200,
	"damage_type": "����"
]),
});


int valid_enable(string usage) { return  (usage =="parry")|| (usage =="blade"); }

int valid_learn(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("���������һ�ѵ�������ȼľ������\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("����������㣬û�а취��ȼľ����������Щ���������ɡ�\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ����̫ǳ��û�а취��ȼľ������\n");

	if ((int)me->query_skill("blade", 1) < 100)
		return notify_fail("��Ļ����������̫ǳ��û�а취��ȼľ������\n");

	if ((int)me->query_skill("blade", 1) < (int)me->query_skill("ranmu-daofa", 1))
		return notify_fail("��Ļ�������ˮƽ���������޷����������ȼľ������\n");

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
	level = (int) me->query_skill("ranmu-daofa", 1);

	if (random(me->query_skill("ranmu-daofa", 1)) > 120 &&
	     me->query_skill("force") > 100 &&
	     me->query("neili") > 1000 &&
	     random(10) > 6)
	{
		me->add("neili", -100);
		return ([
		"action": HIR "$N" HIR "��Ȼ����һ����ţ����弱��"
			  "��ת������ͨ�죬���Ĺ���ɲ�Ǽ�����" + 
			  me->query_temp("weapon")->query("name")
			  + HIR "һ�������������\n��һ�����ȵ�������"
			  "Ϯ��$n" HIR "��" NOR,
		"dodge" : 11,
		"attack": 34,
		"force" : 302,
		"damage": 289,
		"parry" : 7,
		"damage_type": "����"]);
	}

	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 80)
		return notify_fail("�������������ȼľ������\n");

	if ((int)me->query("neili") < 90)
		return notify_fail("�������������ȼľ������\n");

	me->receive_damage("qi", 75);
	me->add("neili", -85);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"ranmu-daofa/" + action;
}

