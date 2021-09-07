// zhua.c ������צ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string final(object me, object target);

string query_name() { return "����"ZJBR"��צ"; }
string *pfm_type() { return ({ "claw", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������צ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("sanyin-wugongzhao", 1) < 80)
		return notify_fail("����������צ������죬�޷�ʹ�á�������צ����\n");

	if (me->query_skill_mapped("claw") != "sanyin-wugongzhao")
		return notify_fail("��û�м����������צ���޷�ʹ�á�������צ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "ͻȻһ���ֽУ���������Ѫ���漴����һ����ץ��$n"
	      HIR "��Ҫ����"NOR"\n";

	ap = me->query_skill("claw");
	dp = target->query_skill("parry");
	if (ap  / 2 + random(ap*3/2) > dp)
	{
		damage = ap / 2 + random(ap / 2);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
					   (: final, me, target :));
		me->start_busy(2);
	} else
	{
		msg += HIR "����$p" HIR "������$P" HIR "����ʽ��"
		       "�����мܣ���ס��$P" HIR "�Ķ��С�"NOR"\n";
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}

string final(object me, object target)
{
	int lvl;

	lvl = me->query_skill("claw");
	target->affect_by("sanyin",
		       ([ "level" : me->query("jiali") + random(me->query("jiali")),
			  "id"    : me->query("id"),
			  "duration" : lvl / 40 + random(lvl / 40) ]));

	return HIR "$p" HIR "����ʧ�룬��æ���ˣ�Ȼ��û"
	       "�ܱܿ�����$P" HIR "��һצץ����Ѫ���죡"NOR"\n";
}
