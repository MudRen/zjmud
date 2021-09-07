#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "�ܹ�"ZJBR"��â"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp, lvl;
	int skill;
	int damage;
	object ob;

	if (userp(me) && ! me->query("can_perform/zhougong-jian/mang"))
		return notify_fail("�㻹��֪����η�����â��\n");

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("��âֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("ֻ���ý����ܷ�����â��\n");

	if (me->query_skill_mapped("sword") != "zhougong-jian")
		return notify_fail("����뼤���ܹ�������ʹ����â��\n");

	if ((int)me->query_skill("zhougong-jian", 1) < 100)
		return notify_fail("����ܹ���������죬�޷�ʹ����â��\n");

	if ((int)me->query("max_neili", 1) < 1500)
		return notify_fail("����Ŀǰ��������Ϊ���޷�ʹ����â��\n");

	if ((int)me->query("neili", 1) < 500)
		return notify_fail("�����������������޷�ʹ����â��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	skill = me->query_skill("zhougong-jian", 1);

	ap = me->query_skill("sword");
	dp = target->query_skill("parry");

	lvl = (int) me->query_skill("zhougong-jian", 1) / 5 + 1;

	msg = HIW "$N" HIW "һ����Х������" + weapon->name() + HIW "��"
		  "�ջ��������ⶸȻ����������²�������â��һ�������ƿ�"
		  "��ֱ����$n��"NOR"\n";

	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 2 + random(ap / 2);

		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
					   HIR "$n" HIR "һ���ҽУ������Ľ����ѻ������ţ�"
					   "�����ϴ̳�����Ѫ������Ѫ��Ȫˮ��ӿ����"NOR"\n");
		message_combatd(msg, me, target);
	} else
	{
		msg += CYN "����$n" CYN "������$N" CYN "����ͼ��бԾ�ܿ���"NOR"\n";
		message_combatd(msg, me, target);
	}

	msg = HIW "$N" HIW "��$n" HIW "Ӧ�Ӳ�Ͼ��һ����Ц�����л���������һ�Ǹ���"
		  "�����Ľ�â�ɽ��ⵯ����������ֱ��$n" HIW "��"NOR"\n";

	if (ap / 4 + random(ap) > dp)
	{
		damage = ap / 2 + random(ap / 2);

		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
					   HIR "ֻ�������͡�һ������������$n" HIR "�ؿڣ���"
					   "��һ����ڴ��Ѫ����$n" HIR "����һ������Ҳ�޷�"
					   "վ��"NOR"\n");
		me->start_busy(2 + random(2));
		me->add("neili", -300);
		message_combatd(msg, me, target);
		return 1;
	}

	msg += CYN "$n" CYN "ǿ��ȫ���ʹ��������һԾ���ܿ���$N" CYN "��ǿ���ɱ�š�"NOR"\n";
	me->start_busy(2 + random(3));
	me->add("neili", -200);
	message_combatd(msg, me, target);
	return 1;
}
