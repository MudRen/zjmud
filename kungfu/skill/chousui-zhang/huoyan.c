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
		return notify_fail("��ֻ�ܶ�ս���еĶ��ֵ�����档\n");

	if ((int)me->query_skill("chousui-zhang", 1) < 80)
		return notify_fail("��ĳ����ƻ�򲻹���\n");

	if ((int)me->query_skill("poison", 1) < 80)
		return notify_fail("��Ļ���������򲻹���\n");

	if ((int)me->query_skill("huagong-dafa", 1) < 80)
		return notify_fail("��Ļ����󷨻�򲻹���\n");

	if ((int)me->query("max_neili") < 500)
		return notify_fail("���������Ϊ���㣬�޷���������������档\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("��������Ϣ���㣬�޷���������������档\n");

	if (! objectp(du = me->query_temp("handing")) && userp(me))
		return notify_fail("������Ҫ����(hand)һЩ��ҩ��Ϊ���ӡ�\n");

	if (objectp(du) && ! mapp(du->query("poison")))
		return notify_fail(du->name() + "�ֲ��Ƕ�ҩ����ô���䣿\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "�����һЦ������������������ָ��׼$n"
	      HIR "����һ����ֻ��һ�����ɫ�Ļ�����$n" HIR "Ʈȥ��"NOR"\n";
	me->start_busy(2);
	me->add("neili", -120);

	lvl = me->query_skill("chousui-zhang", 1);
	damage = 50 + random(lvl) / 2;

	if (me->query("max_neili") + random(me->query("max_neili")) <
	    target->query("max_neili") * 15 / 10)
	{
		msg += WHT "����$n" WHT "��Ȼ�����������������һ�����㽫����Ϩ��"NOR"\n";
	} else
	{
		ap = me->query_skill("poison", 1) / 2 +
		     me->query_skill("force");
		if (ap + random(ap) < target->query_skill("dodge"))
		{
			msg += CYN "$n" CYN "���Ʋ����æ��"
			       "Ų���Σ��ܿ���$N" CYN "�Ĺ�����"NOR"\n";
		} else
		{
			msg += HIG "$n" HIG "ֻ�����˿�һ�����ˣ��漴�������ľ������"NOR"\n";
			target->affect_by("fire_poison",
				       ([ "level" : me->query("jiali") + random(me->query("jiali")),
					  "id"    : me->query("id"),
					  "duration" : lvl / 50 + random(lvl / 20) ]));
			target->receive_damage("qi", damage, me);
			target->receive_damage("jing", damage / 2, me);
		}
	}

	if (objectp(du)) destruct(du);
	message_combatd(msg, me, target);

	return 1;
}
