// po.c ���ܾ�ʽ��

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "�ܾ�ʽ"; }

int perform(object me)
{
	string msg;
	object weapon;
	int skill, jing_cost;
	int improve;

	skill = me->query_skill("lonely-sword", 1);
	jing_cost = random(20) + 45 - (int)me->query("int");
	if (jing_cost < 5) jing_cost = 5;

	if (environment(me)->query("no_fight"))
		return notify_fail("����̫���ӣ��㲻�ܾ�������������\n");

	if (me->is_fighting())
		return notify_fail("���ܾ�ʽ��������ս����������\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�������ȥ��һ�ѽ���\n");

	if (! skill || skill < 20)
		return notify_fail("��Ķ��¾Ž��ȼ�����, �����������ܾ�ʽ����\n");

	if (me->query("neili") < 50)
		return notify_fail("�������������û�������������ܾ�ʽ����\n");

	if (me->query("jing") < jing_cost)
		return notify_fail("������̫���ˣ��޷����о����������ܾ�ʽ����\n");

	if (! me->can_improve_skill("lonely-sword"))
		return notify_fail("���ʵս���鲻�����޷���ᡸ�ܾ�ʽ����\n");

	tell_object(me, HIG "��ʹ�����¾Ž�֮���ܾ�ʽ����������" + weapon->name() + HIG "���������̡�"NOR"\n");

	me->add("neili", -40 - random(10));
	me->receive_damage("jing", jing_cost);

	improve = 1 + random(me->query("int"));

	tell_object(me, MAG "��ġ������������͡����¾Ž��������ˣ�"NOR"\n");
	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", improve / 2);

	improve += me->query_skill("martial-cognize", 1) / 10;
	me->improve_skill("lonely-sword", improve);
	me->start_busy(random(3));
	return 1;
}

