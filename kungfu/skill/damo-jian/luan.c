// luan.c ����������

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "������"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;

	if (userp(me) && ! me->query("can_perform/damo-jian/luan"))
		return notify_fail("�㲻��ʹ�á�����������\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("damo-jian", 1) < 200)
		return notify_fail("��Ĵ�Ħ����������죬����ʹ�á�����������\n");

	if (me->query("neili") < 300)
		return notify_fail("�����������������޷�ʹ�á�����������\n");

	if (me->query_skill_mapped("sword") != "damo-jian")
		return notify_fail("��û�м�����Ħ�������޷�ʹ�á�����������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIM "$N" HIM "��" + weapon->name() + "����һ�񣬷���һ����������������"
	      "����������$n" HIM "��ȫ����"NOR"\n";

	me->add("neili", -200);
	ap = me->query_skill("sword") + me->query_skill("force");
	dp = target->query_skill("force") * 2;

	if (ap / 3 + random(ap) > dp)
	{
		msg += HIR "���$p" HIR "��ͷһ���Ի����ڵ�"
		       "������ʱ����ʹ�����Ĵ����ߣ�"NOR"\n";
		damage = ap / 12 + random(ap / 12);
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage / 2, me);
		target->affect_by("damo_luanqi",
			       ([ "level" : ap / 4 + random(ap / 4),
				  "id"    : me->query("id"),
				  "duration" : ap / 90 + random(ap / 90) ]));
		me->start_busy(2);
	} else
	{
		msg += CYN "����$p" CYN "�������ʹ��$P" CYN
		       "��һ��û�����κ����á�"NOR"\n";
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}