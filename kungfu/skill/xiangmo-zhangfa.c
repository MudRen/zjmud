// Cracked by chenzzz
// poshui-zhangfa
// ��ħ�ȷ���

inherit SKILL;

mapping *action = ({
([      "action": "$N���г�Хһ����һ�С���Ӧ��ˬ������$w����ֱ�룬�ɴ�$n$l",
	"force"  : 20,
	"attack" : 8,
	"dodge"  : 10,
	"parry"  : 15,
	"damage" : 9,
	"skill_name" : "��Ӧ��ˬ",
	"damage_type": "����"
]),
([      "action": "$N����$wһ����ʹ�������޽�����������һ����Ӱ����ԼԼ���������޵���$nѹ��",
	"force"  : 30,
	"attack" : 10,
	"dodge"  : 15,
	"parry"  : 15,
	"damage" : 10,
	"skill_name" : "���޽���",
	"damage_type": "����"
]),
([      "action": "ֻ��$N����$w���ᣬ���ص�������С��޷����졹����Ʈ�ݣ�\n$n�ۼ��ȷ�Ϯ��������֪����Ǻ�",
	"force"  : 50,
	"attack" : 14,
	"dodge"  : 10,
	"parry"  : 20,
	"damage" : 13,
		"skill_name" : "�޷�����",
	"damage_type": "����"
]),
([      "action": "$N���һ��������$w��$n��ͷ���䣬����δ�����ѽ�$n������·��������һ�С��ڽ����ӡ�",
	"attack" : 21,
	"force"  : 70,
	"dodge"  : 15,
	"parry"  : 20,
	"damage" : 19,
	"skill_name" : "�ڽ�����",
	"damage_type": "����"
]),
([      "action": "$N����$w������һ�ݣ�һ�С������ֻ֡���$n���벻���ĵط��̳���$n��ʱ�����޴룬�Ǳ����",
	"force"  : 90,
	"attack" : 26,
	"dodge"  : 5,
	"parry"  : 20,
	"damage" : 21,
	"skill_name" : "�����ֻ�",
	"damage_type": "����"
]),
([      "action": "$N����ͻ��ɷ������������$w������$n$l���䣬���С��ٶ��ֻء������ֿ��ֺ�",
	"force"  : 110,
	"attack" : 31,
	"dodge"  : 20,
	"parry"  : 20,
	"damage" : 21,
	"skill_name" : "�ٶ��ֻ�",
	"damage_type": "����"
]),
});

int valid_enable(string usage) { return usage=="staff" ||  usage=="parry"; }

int valid_learn(object me)
{
		object ob;

	if ((int)me->query("max_neili") < 2500)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("staff", 1) < 120)
		return notify_fail("��Ļ����ȷ����̫ǳ��\n");

	if( !(ob = me->query_temp("weapon")) || 
			(string)ob->query("skill_type") != "staff" )
		return notify_fail("���������һ�����Ȳ���ѧ��ħ�ȷ���\n");

	if ((int)me->query_skill("staff", 1) < (int)me->query_skill("xiangmo-zhangfa", 1))
		return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷���������Ľ�ħ�ȷ���\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("��������������Ľ�ħ�ȷ���\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("���������������ħ�ȷ���\n");

	me->receive_damage("qi", 60);
	me->add("neili", -70);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xiangmo-zhangfa/" + action;
}

