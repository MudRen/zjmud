// chan.c �����޷� ���־�

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���־�"; }
string *pfm_type() { return ({ "whip", }); }

int perform(object me, object target)
{
	string msg;
	object weapon;

	if (! target) target = offensive_target(me);

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    weapon->query("skill_type") != "whip")
		return notify_fail("������û�бޣ�����ʹ�á������־���\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("yunlong-bian",1) < 50)
		return notify_fail("��ġ������޷�������̫ǳ��ʹ���ˡ������־���\n");

	if (me->query_skill_mapped("whip") != "yunlong-bian")
		return notify_fail("��û�м��������޷�������ʹ�á������־���\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹���ʹ���ˡ������־���\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = CYN "$N" CYN "ʹ�������޷��������־������ӳ�����ͼ��$n"
	      CYN "��ȫ���ס��"NOR"\n";

	if (random(me->query_skill("whip")) > target->query_skill("parry") / 2)
	{
		msg += HIY "���$p" HIY "��$P" HIY "���˸����ֲ�����"NOR"\n";
		target->start_busy((int)me->query_skill("whip") / 22 + 1);
		me->start_busy(1 + random(2));
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ����û���ϵ���"NOR"\n";
		me->start_busy(4);
	}
	message_combatd(msg, me, target);
	return 1;
}
