// hua.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string final(object me, object target);

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int damage;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���ֻ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹����޷�ʩչ�����ơ�\n");

	if ((int)me->query_skill("huagu-mianzhang", 1) < 100)
		return notify_fail("��Ļ������ƻ�������죬���ữ���ơ�\n");

	if ((int)me->query("neili", 1) < 300)
		return notify_fail("����������������ܻ��ǡ�\n");

	if (me->query_skill_mapped("strike") != "huagu-mianzhang")
		return notify_fail("��û�м����������ƣ��޷�ʩչ�����ơ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	me->add("neili", -100);

	msg = MAG "$N" MAG "�Ƴ���磬��������$n" MAG "�ļ�ͷ��"NOR"\n";

	ap = me->query_skill("strike");
	dp = target->query_skill("force");
	if (ap / 2 + random(ap) > dp)
	{
		me->start_busy(2);
		damage = ap / 3 + random(ap / 2);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
					   (: final, me, target :));
	} else
	{
		msg += CYN "����$p" CYN "��æ����һ�ԣ����˿�ȥ��"NOR"\n";
		me->start_busy(3);
	}

	message_combatd(msg, me, target);
	return 1;
}

string final(object me, object target)
{
	int lvl;

	lvl = me->query_skill("strike");
	target->affect_by("huagu",
		       ([ "level" : me->query("jiali") + random(me->query("jiali")),
			  "id"    : me->query("id"),
			  "duration" : lvl / 60 + random(lvl / 60) ]));
	return HIM "���ֻ���˵�һ����$p" HIM "��$P"
	       HIM "һ�����У�һʱ��$p" HIM
	       "ֻ����ȫ��ů����ģ��е��е���Ʈ������"NOR"\n";
}
