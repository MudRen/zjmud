// kuihua.c �������ķ���

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"�ķ�"; }
string *pfm_type() { return ({ "xinfa", }); }

int exert(object me, object target)
{
	string msg;
	object weapon;
	int skill, jing_cost;
	int improve;

	skill = me->query_skill("kuihua-mogong", 1);
	jing_cost = 45 - (int)me->query("int");
	if (jing_cost < 5) jing_cost = 5;

	if ( environment(me)->query("no_fight") )
		return notify_fail("����̫���ӣ��㲻�ܾ���������ϰ��\n");

	if (me->is_fighting())
		return notify_fail("�������ķ���������ս������ϰ��\n");

	if (! skill || skill < 80)
		return notify_fail("��Ŀ���ħ���ȼ�����, ������ϰ�������ķ�����\n");

	if (me->query("neili") < 30)
		return notify_fail("��������������޷���ϰ�������ķ�����\n");

	if (me->query("jing") < jing_cost)
		return notify_fail("������̫���ˣ��޷����о�����ϰ�������ķ�����\n");

	if (! me->can_improve_skill("dodge"))
		return notify_fail("���ʵս���鲻�����޷���ᡸ�����ķ�����\n");

	if (me->query("dodge", 1) >= me->query_skill("kuihua-mogong", 1) + 10)
		return notify_fail("��Ŀ���ħ����Ϊ���ޣ��޷���������ġ������ķ�����\n");

	msg = HIM "$N" HIM "��ϥĬ����������ϰ�����ķ���ֻ��������Խ��Խ�ᡣ"NOR"\n";
	message_combatd(msg, me);

	me->add("neili", -20 - random(10));
	me->receive_damage("jing", jing_cost);

	improve = 20 + random(me->query("int"));

	tell_object(me, MAG "��ġ������Ṧ�������ˣ�"NOR"\n");
	me->improve_skill("dodge", improve);
	me->start_busy(random(3));
	return 1;
}
