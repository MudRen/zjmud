// �������

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }

int perform(object me, object target)
{
	object du;
	int damage;
	int ap;
	string msg;
	int lvl;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ֻ�ܶ�ս���еĶ��ֵ������\n");

	if ((int)me->query_skill("chousui-zhang", 1) < 120)
		return notify_fail("��ĳ����ƻ�򲻹���\n");

	if ((int)me->query_skill("poison", 1) < 120)
		return notify_fail("��Ļ���������򲻹���\n");

	if ((int)me->query_skill("huagong-dafa", 1) < 120)
		return notify_fail("��Ļ����󷨻�򲻹���\n");

	if ((int)me->query("max_neili") < 800)
		return notify_fail("���������Ϊ���㣬�޷��������������\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("��������Ϣ���㣬�޷��������������\n");

	if (! objectp(du = me->query_temp("handing")) && userp(me))
		return notify_fail("������Ҫ����(hand)һЩ��ҩ��Ϊ���ӡ�\n");

	if (objectp(du) && ! mapp(du->query("poison")))
		return notify_fail(du->name() + "�ֲ��Ƕ�ҩ���޷����䣿\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "����������һ�����ȣ���׼$n"
	      HIR "�͵ص���һ�����ɫ�Ļ���Я��һ��������$p" HIR "��ȥ��"NOR"\n";
	me->start_busy(2 + random(2));
	me->add("neili", -200);

	lvl = me->query_skill("chousui-zhang", 1);
	damage = 50 + random(lvl);

	if (me->query("max_neili") / 2 + random(me->query("max_neili")) <
	    target->query("max_neili") * 16 / 10)
	{
		msg += WHT "����$n" WHT "��Ȼ�����������������һ�����㽫����Ϩ��"NOR"\n";
	} else
	{
		ap = me->query_skill("poison", 1) / 2 +
		     me->query_skill("force");
		if (ap + random(ap) < target->query_skill("dodge"))
		{
			msg += CYN "$n" CYN "���Ʋ����æ��Ų���Σ��ܿ���$N"
			       CYN "�Ĺ�����"NOR"\n";
		} else
		{
			msg += HIR "���ֻ��$n" HIR "һ���Һ����ѱ�������У�Ƥ���յá����͡����졣"NOR"\n";
			target->affect_by("fire_poison",
				       ([ "level" : me->query("jiali") + random(me->query("jiali") * 3 / 2),
					  "id"    : me->query("id"),
					  "duration" : lvl / 30 + random(lvl / 15) ]));
			target->receive_damage("qi", damage, me);
			target->receive_damage("jing", damage / 2, me);
		}
	}

	if (objectp(du)) destruct(du);
	message_combatd(msg, me, target);

	return 1;
}
