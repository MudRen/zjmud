#include <ansi.h>
#include <combat.h>

#define BIAN "��" HIC "���Ʊ��" NOR "��"

inherit F_SSERVER;

string query_name() { return "����"ZJBR"���"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	string msg;
	int count;
	int lvl;
	int i;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail(BIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail(BIAN "ֻ�ܿ���ʩչ��\n");

	if ((lvl = (int)me->query_skill("wuluo-zhang", 1)) < 100)
		return notify_fail("�����������Ʋ�����죬����ʩչ" BIAN "��\n");

	if (me->query_skill_mapped("strike") != "wuluo-zhang")
		return notify_fail("��û�м������������ƣ�����ʩչ" BIAN "��\n");

	if (me->query_skill_prepared("strike") != "wuluo-zhang")
		return notify_fail("��û��׼�����������ƣ�����ʩչ" BIAN "��\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������㣬����ʩչ" BIAN "��\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "ʩ�����������ƾ�������������һ������ʱ���������"
	      "Ӱ����ƮƮ��$n" HIC "��ȥ��"NOR"\n";
	me->add("neili", -50);

	if (random(me->query_skill("force") + me->query_skill("strike")) >
	    target->query_skill("force"))
	{
		msg += HIR "$n" HIR "��ʱ�����ۻ����ң�ȫȻ�ֱ�"
		       "������α��ֻ��ƴ���˶��ֵ���"NOR"\n";
		count = lvl / 10;
		me->add_temp("apply/attack", count);
	} else
	{
		msg += HIC "����$n" HIC "��������������ֵ���˿"
		       "��������Ӱ�ĸ��ţ���"NOR"\n";
		count = 0;
	}
	message_combatd(msg, me, target);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, 0, 0);
	}
	me->start_busy(1 + random(5));
	me->add_temp("apply/attack", -count);
	return 1;
}

