// chan.c ̫�������������־�

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���־�"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	int level;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("̫�������������־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if ((level = me->query_skill("taiji-jian", 1)) < 80)
		return notify_fail("���̫������������죬����ʹ�á������־���\n");

	if (me->query_skill_mapped("sword") != "taiji-jian")
		return notify_fail("����뼤��̫����������ʹ�á������־���\n");

	if (me->query("neili") < 60)
		return notify_fail("�����������������޷�ʹ�á������־���\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG "$N" HIG "ʹ��̫�������������־�������Ȧת����"
	      "�಻������������������ͼ����$n" HIG "�Ĺ��ơ�"NOR"\n";

	me->add("neili", -30);
	if (random(level) > (int)target->query_skill("parry", 1) / 2)
	{
		msg += HIR "���$p" HIR "��$P" HIR "�ָ���æ���ң�"
		       "����ʧ�룬���ڵ�������֪���Ӧ�ԣ�"NOR"\n";
		target->start_busy(level / 40 + 2);
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ����"
		       "����㣬ȫ��Ӧ�����硣"NOR"\n";
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
