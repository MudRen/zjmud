// qi.c ���ν���

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "finger", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���ν���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("force") < 360)
		return notify_fail("����ڹ���򲻹���ʹ�������ν�����\n");

	if ((int)me->query_skill("six-finger", 1) < 180)
		return notify_fail("��������񽣲�������������ʹ�����ν�����\n");

	if (me->query("max_neili") < 8000)
		return notify_fail("���������Ϊ��������ʹ�����Ϭ�������ν�����\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("��������������޷�ʹ�����ν�����\n");

	if (me->query_skill_mapped("finger") != "six-finger")
		return notify_fail("��û�м��������񽣣��޷�ʹ�����ν�����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	switch (random(5))
	{
	case 0:
		msg = HIC "$N" HIC "��ָһ����һ���������׵����ν���ֱ��$n"
		      HIC "��ǰ��ȥ��"NOR"\n";
		break;

	case 1:
		msg = HIC "$N" HIC "�����⴫��˫��Сָ��������ֱ���ƿ���������"
		      "�������ν���ֱ��$n" HIC "��ǰ��ȥ��"NOR"\n";
		break;

	case 2:
		msg = HIC "$N" HIC "����һЦ������ָ��Ȼ�̳���һ������֮����"
		      "���ν�����Ȼ��$n" HIC "��ǰ��ȥ��"NOR"\n";
		break;

	case 3:
		msg = HIC "$N" HIC "��Ĵָ������һ���Ե��ޱȵĽ����ƿմ���$n"
		      HIC "��ǰ��һʱ���������Щ���ȡ�"NOR"\n";
		break;

	default:
		msg = HIC "$N" HIC "ʳָ���������������ν�����ʱ����һ��������"
		      "��$n" HIC "����Χס��"NOR"\n";
		break;
	}

	ap = me->query_skill("finger");
	dp = target->query_skill("force");
	weapon = target->query_temp("weapon");
	me->start_busy(3);
	if (ap / 2 + random(ap) > dp)
	{ 
		damage = ap + random(ap / 2);
		me->add("neili", -400);
		if (! objectp(weapon) || weapon->query("skill_type") == "pin")
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 66,
						   HIR "$p" HIR "ֻ������ǰһ���ʹ����Ѫ"
						   "�Դ��ڼ����������ǰ��ʱһ�ڣ�"NOR"\n");
		else
		if (weapon->is_item_make() || weapon->query("damage") > 180 ||
		    weapon->query("skill_type") == "hammer")
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
						   HIR "$p" HIR "��" + weapon->name() + HIR "��ͼ�мܣ�"
						   HIR "���ν������Ϭ����͸��" + weapon->name() +
						   HIR "ֱ���$p" HIR "������Ѫ������������Ҫ��ת������"NOR"\n");
		else
		{
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
						   HIR "$p" HIR "��ת" + weapon->name() + HIR "��������"
						   "ǰ��ֻ��ž��һ����" + weapon->name() +
						   HIR "������أ��������죡\n$n" HIR "����"
						   "���������ۡ�������һ����Ѫ����ɫ��ĲҰס�"NOR"\n");
			weapon->move(environment(me));
			if (! weapon->is_item_make())
			{
				weapon->set("no_wield", weapon->name() + "�Ѿ�����ˣ�û��װ���ˡ�\n");
				weapon->set_name("�����" + weapon->name());
				weapon->set("value", 0);
			}
		}
	} else
	{
		msg += CYN "����$p" CYN "�ڹ���Ϊ������Ὣ�������������Ρ�"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
