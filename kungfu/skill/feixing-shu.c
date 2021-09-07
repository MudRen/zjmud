// feixing-shu.c ������

#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
	"$n��һ����һ�Σ��漴�ص�ԭ�أ����ɵض����$N��һ�С�\n",
	"$n����Ծ��һ���շ�����˳������һ�ߡ�\n",
	"$n�������Ա�һ�ݣ�������$N�����൱�ľ��룬$N��һ����ȻʧЧ��\n",
	"$n������ϣ������Ծ��$N��������$N�ı���\n",
	"$n���μ�����б��ǰһ������Ȼ�Ѿ��㿪��$N����һ�С�\n",
	"$N��ǰһ����ȴ��$n��Ȼ�����Լ�������֮Զ��ȴû��$n��ζ���Լ��Ĺ�����?�\n",
	"$Nһ��������$n��û����Ӱ��$N��ת��ȴ��$n���Ƕ����Լ����֡�\n",
	"$Nһ�й�����$n��Ȼ������$NãȻ�Ĺˣ�ȴ����$n��Ӱ�ӣ�\n",
});

int valid_enable(string usage)
{
	return usage == "throwing" ||
	       usage == "dodge";
}

int valid_learn(object me)
{
	if ((int)me->query_skill("force") < 50)
		return notify_fail("����ڹ��ķ���򲻹����޷�ѧ��������\n");

	if ((int)me->query_skill("dodge") < 40)
		return notify_fail("����Ṧ��򲻹����޷�ѧϰ��������\n");

	if ((int)me->query_skill("poison", 1) < 30)
		return notify_fail("��Ķ�����򲻹����޷������������\n");

	if ((int)me->query_dex() < 25)
		return notify_fail("������������ɣ��޷�ѧϰ��������\n");

	if ((int)me->query_skill("poison", 1) < (int)me->query_skill("feixing-shu", 1))
		return notify_fail("��Ķ���ˮƽ���ޣ��޷����������ķ�������\n");

	if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("feixing-shu", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������ķ�������\n");

	return 1;
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	object weapon;

	if ((int)me->query("qi") < 60)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("���������������������\n");

	me->receive_damage("qi", 50);
	me->add("neili", -48);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"feixing-shu/" + action;
}
