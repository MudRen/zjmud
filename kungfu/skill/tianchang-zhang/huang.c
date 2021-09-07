// huang.c �������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"���"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	string msg;
	int skill, ap, dp, damage;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! me->is_fighting(target))
		return notify_fail("��������ġ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_temp("weapon"))
		return notify_fail("������ֲ���ʩչ��������ġ���\n");

	if (me->query_skill_mapped("strike") != "tianchang-zhang")
		return notify_fail("��û�м����쳤�Ʒ����޷�ʩչ��������ġ���\n");

	skill = me->query_skill("tianchang-zhang", 1);

	if (skill < 100)
		return notify_fail("����쳤�Ʒ���Ϊ���ޣ�����ʹ�á�������ġ���\n");

	if (me->query("neili") < 150)
		return notify_fail("��������������޷����á�������ġ���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "���롱��һ����ȣ�����������ֻ������һƬѪ�죬ٿ������ĳ���"
	      HIR "һ���ȷ��ʱϮ��$n" HIR "����ǰ��Ѩ��"NOR"\n";

	ap = me->query_skill("strike", 1) / 2 + skill;
	dp = target->query_skill("force");
	if (dp < 1) dp = 1;
	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili", -120);
		me->start_busy(2);
		damage = skill + random(skill / 3);
		msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 45,
					   HIR "$n" HIR "һʱ��ֻ������Ѫ��ӿ����"
					   "�������٣���Ϣ���ң����ɵ�����һ��"
					   "��Ѫ��"NOR"\n");
	} else
	{
		me->add("neili", -50);
		msg += HIC "Ȼ��$n" HIC "�ڹ���տ��˿����Ϊ$N"
		       HIC "���Ʒ��������������¡�"NOR"\n";
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}

