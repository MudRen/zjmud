// qujing-gunfa.c ȡ������
// By Vin 2000

#include <ansi.h>

inherit SHAOLIN_SKILL;
 
mapping *action = ({
([      "action": "$N�������ˣ�һ�С��������޸���������$wӭ��һ��������$n��ͷ�������ҽ���",
	"dodge" : 31,
	"attack": 31,
	"force" : 289,
	"damage": 34,
	"parry" : 35,
	"lvl" : 0,
	"damage_type": "����"
]),
([      "action": "$N���쳤Ц����Ҳ������һ�С�̸Ц�������������һ����$n��ͷ����",
	"dodge" : 33,
	"attack": 37,
	"force" : 316,
	"damage": 41,
	"parry" : 42,
	"lvl" : 25,
	"damage_type": "����"
]),
([      "action": "$Nһ��������Խ��$nͷ����һ�С��¶������񡹣�����$w�ո���Բ������$n$l",
	"dodge" : 38,
	"attack": 38,
	"force" : 318,
	"damage": 73,
	"parry" : 35,
	"lvl" : 50,
	"damage_type": "����"
]),
([      "action": "$Nһ���޺ȣ�һ�С������Ͼ�¯����$nһ�֮�䣬$N����$w�Ѻ�Х������ɨ��$n��$l",
	"dodge" : 31,
	"attack": 48,
	"force" : 331,
	"damage": 91,
	"parry" : 33,
	"lvl" : 75,
	"damage_type": "����"
]),
([      "action": "$N�������ˣ�һ�С��������޸���������$wӭ��һ��������$n��ͷ�������ҽ���",
	"dodge" : 49,
	"attack": 63,
	"force" : 391,
	"damage": 103,
	"parry" : 31,
	"lvl" : 100,
	"damage_type": "����"
]),
([      "action": "$Nʹ����������һ᡹���Ų����ԣ���һ������һ�������$n��æ���ң��мܲ���",
	"dodge" : 51,
	"attack": 74,
	"force" : 481,
	"damage": 167,
	"parry" : 28,
	"lvl" : 130,
	"damage_type": "����"
]),
([      "action": "$N�����������ʹ��������׹Ǿ���������$wת����糵һ�㣬һ������ֱ��$n����",
	"dodge" : 31,
	"attack": 83,
	"force" : 503,
	"damage": 184,
	"parry" : 35,
	"lvl" : 160,
	"damage_type": "����"
]),
([      "action": "$Nһ�С�ǧ�������������$w��Ϊ���ϼ�⣬��$nĿѣ֮ʱ��$w�ѵ���$n��$l",
	"dodge" : 23,
	"attack": 98,
	"force" : 548,
	"damage": 193,
	"parry" : 51,
	"lvl" : 200,
	"damage_type": "����"
]),
});


int valid_enable(string usage) { return  (usage =="parry")|| (usage =="club"); }

int valid_learn(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "club")
		return notify_fail("���������һ�����Ӳ�����ȡ��������\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("����������㣬û�а취��ȡ������������Щ���������ɡ�\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ����̫ǳ��û�а취��ȡ��������\n");

	if ((int)me->query_skill("club", 1) < 100)
		return notify_fail("��Ļ����������̫ǳ��û�а취��ȡ��������\n");

	if ((int)me->query_skill("club", 1) < (int)me->query_skill("qujing-gunfa", 1))
		return notify_fail("��Ļ�������ˮƽ���������޷����������ȡ��������\n");

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
	level = (int) me->query_skill("qujing-gunfa", 1);

	if (random(me->query_skill("qujing-gunfa", 1)) > 120 &&
	     me->query_skill("force") > 100 &&
	     me->query("neili") > 1000 &&
	     random(10) > 6)
	{
		me->add("neili", -100);
		return ([
		"action": HIY "$N" HIY "������" + me->query_temp("weapon")->query("name")
			  + HIY "ӭ��һ�ӣ�ʹ����ɱ������" NOR + HIR "������ǧ���� "
			  "����������ﰣ" NOR + HIY "����"
			  + me->query_temp("weapon")->query("name") + HIY "��ʱ�ó�"
			  "��ǧ��\nӰ����׼$n������ֱ�����¡���һ��Ҫ�Ǵ��У���������"
			  "�޽���Ҳ����һ��" NOR,
		"force" : 630,
		"attack": 138,
		"damage": 231,
		"dodge" : -10,
		"damage_type": "����"]);
	}

	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "club")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 80)
		return notify_fail("�������������ȡ��������\n");

	if ((int)me->query("neili") < 90)
		return notify_fail("�������������ȡ��������\n");

	me->receive_damage("qi", 75);
	me->add("neili", -85);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"qujing-gunfa/" + action;
}

