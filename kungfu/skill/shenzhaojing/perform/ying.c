#include <ansi.h>
#include <combat.h>

#define YING "��" HIR "��Ӱ��ȭ" NOR "��"

inherit F_SSERVER;

string query_name() { return "��Ӱ"ZJBR"��ȭ"; }

int perform(object me, object target)
{
	int damage;
	string msg;
	int ap, dp;
	int lvl;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail(YING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʩչ" YING "��\n");

	if (me->query_skill_mapped("unarmed") != "shenzhaojing")
		return notify_fail("��û�м������վ���Ϊ���ּ��ܣ��޷�ʩչ" YING "��\n");

	if (me->query_skill_prepared("unarmed") != "shenzhaojing")
		return notify_fail("������û��׼��ʹ�����վ��񹦣��޷�ʩչ" YING "��\n");

	if ((int)me->query_skill("shenzhaojing", 1) < 200)
		return notify_fail("������վ��񹦻�򲻹����޷�ʩչ" YING "��\n");

	if ((int)me->query_skill("unarmed", 1) < 200)
		return notify_fail("��Ļ���ȭ�Ż�򲻹����޷�ʩչ" YING "��\n");

	if ((int)me->query("max_neili") < 5000)
		return notify_fail("���������Ϊ���㣬�޷�ʩչ" YING "��\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("��������������޷�ʩչ" YING "��\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "ٿȻԾ����������Ӱ����һȭ��ȥ�ƿ켫��ȭӰ��"
	      "�ص�����ֱϮ$n" HIR "��ȥ��"NOR"\n";

	lvl = me->query_skill("shenzhaojing", 1);

	ap = me->query_skill("force") + me->query("con") * 5;
	dp = target->query_skill("force") + target->query("con") * 5;

	me->start_busy(4);
	if (ap / 2 + random(ap) > dp)
	{ 
		damage = ap + random(ap / 2);
		me->add("neili", -400);
		target->affect_by("shenzhao", ([
			"level" : me->query("jiali") + random(me->query("jiali")),
			"id"    : me->query("id"),
			"duration" : lvl / 50 + random(lvl / 20) ]));
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
			       damage, 90, HIR "$n" HIR "��ȭ�Ʊ任Ī�⣬ֻ��"
			       "΢΢һ㶣��ѱ�$N" HIR "һȭ�����ؿڣ����վ���"
			       "����\nʱ����ɽ�鱬��һ�㣬͸����롣"NOR"\n");
	} else
	{
		msg += CYN "$n" CYN "��$N" CYN "������ӿ����æ����Ծ����"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}

