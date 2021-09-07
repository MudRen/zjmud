#include <ansi.h>
#include <combat.h>

#define SHI "��" HIR "߱Ԫ��" NOR "��"

inherit F_SSERVER;

string query_name() { return "߱Ԫ��"; }
string *pfm_type() { return ({ "claw", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int ap, dp;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail(SHI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail(SHI "ֻ�ܿ���ʩչ��\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹�������ʩչ" SHI "��\n");

	if ((int)me->query_skill("yuezhao-gong", 1) < 130)
		return notify_fail("��Խצ���ȼ�����������ʩչ" SHI "��\n");
 
	if (me->query_skill_mapped("claw") != "yuezhao-gong")
		return notify_fail("��û�м���Խצ��������ʩչ" SHI "��\n");

	if (me->query_skill_prepared("claw") != "yuezhao-gong")
		return notify_fail("��û��׼��Խצ��������ʩչ" SHI "��\n");

	if (me->query("neili") < 300)
		return notify_fail("�����ڵ��������㣬����ʩչ" SHI "��\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = WHT "$N" WHT "ʩ��Խצ����" HIR "߱Ԫ��" NOR + WHT "����������"
	      "��һ�ᣬֱֱץ��$n" WHT "�������ڡ�"NOR"\n";

	me->add("neili", -100);
	ap = me->query_skill("claw");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		damage = me->query_skill("yuezhao-gong", 1);
		damage += random(damage);
		me->add("neili", -50);

		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
					   HIR "ֻ��$n" HIR "һ���Һ�������$N" HIR
					   "����ָץ�����ţ���Ѫ��ʱ�Ĵ��ɽ���"NOR"\n");
		me->start_busy(2);
	} else 
	{
		msg += HIC "����$p" HIC "�������ݣ����μ�ת������Ķ����$P"
		       HIC "�Ĺ�����"NOR"\n";
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}

