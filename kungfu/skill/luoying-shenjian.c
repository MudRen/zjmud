// luoying-shenjian.c ��Ӣ��

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "skill_name": HIB"��Ӣ�ͷ�"NOR,
	"action" : "$Nʹһ�С�"+HIB+"��Ӣ�ͷ�"+NOR+"������������Ʈ������$w����ʵʵ�ó���㽣���׷���������$n$l",
	"force"  : 100,
	"parry"  : 15,
	"damage" : 40,
	"lvl"    : 0,
	"damage_type": "����"
]),
([      "skill_name": HIM"�����һ�"NOR,
	"action" : "$N�趯$w��һʽ��"+HIM+"�����һ�"+NOR+"����������$n����һ�Σ�����$w�������佣��Ю�Ż�����������$n��$l",
	"force"  : 150,
	"parry"  : 20,
	"damage" : 50,
	"lvl"    : 20,
	"damage_type": "����"
]),
([      "skill_name": HIR"��������"NOR,
	"action" : "$N������$nһת������$w����һָ��һʽ��"+HIR+"��������"+NOR+"���ó����콣Ӱ����$n$l�����ӳ�����",
	"force"  : 180,
	"dodge"  : 20,
	"damage" : 60,
	"lvl"    : 40,
	"damage_type": "����"
]),
([      "skill_name": GRN"���Ƿɻ�"NOR,
	"action" : "$N����ƮȻ�����ڰ��������һ������Ȼһʽ��"+GRN+"���Ƿɻ�"+NOR+"������$w�������޵�������$n��$l",
	"force"  : 210,
	"dodge"  : 30,
	"damage" : 70,
	"lvl"    : 60,
	"damage_type": "����"
]),
([      "skill_name": MAG"������"NOR,
	"action" : "$N�������࣬һ�С�"+MAG+"������"+NOR+"������$w���һ����������$n��$l",
	"force"  : 250,
	"dodge"  : 35,
	"damage" : 80,
	"lvl"    : 80,
	"damage_type": "����"
]),
([      "skill_name": CYN"���컨��"NOR,
	"action" : "$Nһ�����ʹ����"+CYN+"���컨��"+NOR+"��������$w�ó����컨�꣬Ѹ����������$n��$l",
	"force"  : 280,
	"dodge"  : 35,
	"damage" : 90,
	"lvl"    : 100,
	"damage_type": "����"
]),
([      "skill_name": HIY"�仨����"NOR,
	"action" : "$N��̾һ��������$w����һ����һʱ��"+HIY+"�仨����"+NOR+"����$w��ȻԾ��ٿ�Ļ��������¶���һ���ƮȻ����$n��$l",
	"force"  : 300,
	"dodge"  : 30,
	"damage" : 110,
	"lvl"    : 120,
	"damage_type": "����"
]),

});

int valid_learn(object me)
{
	object ob;

	if ((int)me->query_skill("force") < 45)
		return notify_fail("����ڹ���򻹲�����\n");

	if ((int)me->query("max_neili") < 250)
		return notify_fail("���������������������Ӣ�񽣡�\n");

	if (! objectp(ob = me->query_temp("weapon")) ||
	    (string)ob->query("skill_type") != "sword")
		return notify_fail("���������һ�ѽ�����ѧϰ������\n");
	 if (me->query_skill("sword",1) <= me->query_skill("luoying-shenjian",1) )
	return notify_fail("��Ļ��������������޷������������Ӣ�񽣡�\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage == "sword" || usage == "parry";
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

	level = (int)me->query_skill("luoying-shenjian", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}
//�ȼ��������Ƿ�ѧ���µ���ʽ
string query_skill_up(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
	 {
		if(level == action[i]["lvl"])
		 {
		     return action[i]["skill_name"];
		 }
	 }
	  return "no";
}

int practice_skill(object me)
{
	object ob;

	if ((int)me->query("qi") < 50)
		return notify_fail("�������̫�ͣ�û�а취��ϰ��Ӣ�񽣡�\n");

	if ((int)me->query("neili") < 35)
		return notify_fail("�������������û�а취��ϰ��Ӣ�񽣡�\n");

	if (! objectp(ob = me->query_temp("weapon")) ||
	    (string)ob->query("skill_type") != "sword")
		return notify_fail("���������һ�ѽ�����ϰ��������\n");

	me->receive_damage("qi", 45);
	me->add("force", -41);
	return 1;
}
