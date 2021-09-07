// zhong.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	string msg;
	int damage;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (environment(me)->query("no_fight"))
		return notify_fail("���ﲻ��ս����\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail("������ֻ������ս���еĶ������ϡ�\n");

	if (target->query("not_living"))
		return notify_fail("������ˣ��ǲ��ǻ��ˡ�\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ�������򣬲�������������\n");

	if ((int)me->query_skill("liuyang-zhang", 1) < 150)
		return notify_fail("�����ɽ�����Ʋ�����죬��������������\n");

	if (me->query_skill_mapped("strike") != "liuyang-zhang")
		return notify_fail("��û�м�����ɽ�����ƣ���������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "�����������������е�ˮ¶Ϊ������"
	      "�����У���ƮƮ������$n" HIC "��\n";

	ap = me->query_skill("strike");
	dp = target->query_skill("force");
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 2 + random(ap / 2);
		msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 53,
					   CYN "���$p" CYN "��$P" CYN "���˸����ţ�����$P"
					   CYN "һö��������"NOR"\n");
		target->affect_by("ss_poison",
			       ([ "level" : me->query("jiali") + random(me->query("jiali")),
				  "id"    : me->query("id"),
				  "duration" : ap / 70 + random(ap / 30) ]));
		me->start_busy(1 + random(4));
	} else
	{
		msg += CYN "����$p" CYN "������������$P"
		       CYN "���������޷������κ�Ч�á�"NOR"\n";
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
