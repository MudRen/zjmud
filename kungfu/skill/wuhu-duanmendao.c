// wuhu-duanmendao.c �廢���ŵ�

inherit SKILL;

mapping *action = ({
([	"action" : "$N����$wбָ��һ�С�ֱ��ֱȥ��������һ�٣�һ����$n��$l��ȥ",
	"force"  : 30,
	"dodge"  : -10,
	"parry"  : 5,
	"lvl"    : 0,
	"skill_name"  : "ֱ��ֱȥ",
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С����Ϲһ�������������㣬$wһ��һ�գ�ƽ�л���$n�ľ���",
	"force"  : 35,
	"dodge"  : -10,
	"parry"  : 10,
	"lvl"    : 10,
	"skill_name"  : "���Ϲһ�",
	"damage_type" : "����"
]),
([	"action" : "$Nչ���鲽������Ծ�䣬һ�С��ƴ����¡�������һ������ն��$n",
	"force"  : 40,
	"dodge"  : -5,
	"parry"  : 5,
	"lvl"    : 20,
	"skill_name"  : "�ƴ�����",
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С�������ɽ����$w�󿪴��أ����϶��»���һ�����磬ֱ����$n",
	"force"  : 60,
	"dodge"  : 5,
	"parry"  : 5,
	"lvl"    : 30,
	"skill_name"  : "������ɽ",
	"damage_type" : "����"
]),
([	"action" : "$N����$wһ����һ�С���Ϫ���㡹��˫�ֳ����������У�����$n���ؿ�",
	"force"  : 80,
	"dodge"  : 10,
	"parry"  : 5,
	"lvl"    : 40,
	"skill_name"  : "��Ϫ����",
	"damage_type" : "����"
]),
([	"action" : "$N����$w��ʹ��һ�С��Ź����ġ����������ã����ҿ�����������$n",
	"force"  : 100,
	"dodge"  : 15,
	"parry"  : 15,
	"lvl"    : 50,
	"skill_name"  : "�Ź�����",
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С��������ۡ������Ծ����أ�$w˳����ǰ��Ю��������$n��$l",
	"force"  : 110,
	"dodge"  : 5,
	"parry"  : 15,
	"damage" : 10,
	"lvl"    : 60,
	"skill_name"  : "��������",
	"damage_type" : "����"
]),
([	"action" : "$N����פ�أ�һ�С�������Ϣ�����ӳ�һƬ�����ĵ�Ӱ����$n��ȫ��ӿȥ",
	"force"  : 130,
	"dodge"  : 20,
	"parry"  : 10,
	"damage" : 20,
	"lvl"    : 70,
	"skill_name"  : "������Ϣ",
	"damage_type" : "����"
]),
([	"action" : "$N���ֺ󳷣�����һ����һ�С�׳ʿ���󡹣���ʱһ���׹�ֱն��$n���ֱ�",
	"force"  : 150,
	"dodge"  : 20,
	"parry"  : 20,
	"damage" : 20,
	"lvl"    : 80,
	"skill_name"  : "׳ʿ����",
	"damage_type" : "����"
]),
([	"action" : "$N�߸�Ծ��һ�С���ͷ��ء�������$wֱ����$n�ľ���",
	"force"  : 170,
	"dodge"  : 20,
	"parry"  : 20,
	"damage" : 25,
	"lvl"    : 90,
	"skill_name"  : "��ͷ���",
	"damage_type" : "����"
]),
([	"action" : "$N���ػ��У�һ�С����Ӿ��������$wֱ��ȥ$n���ɲ�",
	"force"  : 180,
	"dodge"  : 30,
	"parry"  : 30,
	"damage" : 30,
	"lvl"    : 100,
	"skill_name"  : "���Ӿ���",
	"damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 350)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 50)
		return notify_fail("��Ļ����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("blade", 1) < (int)me->query_skill("wuhu-duanmendao", 1))
		return notify_fail("��Ļ�������������ޣ��޷�����������廢���ŵ�����\n");

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
    	level = (int) me->query_skill("wuhu-duanmendao", 1);
    	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
	    		return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 50)
		return notify_fail("��������������廢���ŵ�����\n");

	if ((int)me->query("neili") < 30)
		return notify_fail("��������������廢���ŵ�����\n");

	me->receive_damage("qi", 30);
	me->add("neili", -18);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"wuhu-duanmendao/" + action;
}
