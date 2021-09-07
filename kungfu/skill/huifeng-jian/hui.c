// hui.c  �ط�����������ط������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "�ط�"ZJBR"����"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	int damage;
	string msg;
	object weapon;
	string wname;
	int ap, dp;

	if (userp(me) && ! me->query("can_perform/huifeng-jian/hui"))
		return notify_fail("�㻹����ʹ�á��ط��������һ������\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���ط������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("ûװ������ôʹ�á��ط��������\n");

	if (me->query_skill_mapped("sword") != "huifeng-jian")
		return notify_fail("��û�м����ط��������������ʹ�á��ط��������\n");

	if ((int)me->query_skill("huifeng-jian", 1) < 120)
		return notify_fail("��Ļط��������������죬��ʹ�������ط��������\n");

	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹�������ʩչ���ط��������\n");

	if ((int)me->query("neili") < 500)
	       return notify_fail("��������������������ʩչ���ط��������"NOR"\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	wname = weapon->name();

	damage = (int)me->query_skill("huifeng-jian", 1) / 2;
	damage += random(damage);

	// ��һ��
	ap = me->query_str();
	dp = target->query_str();
	msg = HIC "$N" HIC "һ�����ȣ����е�" + wname + HIC "��׼$n" HIC "ֱ�����£�"NOR"\n";
	if (ap / 2 + random(ap) > dp)
	{
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
					   HIR "$p" HIR "�����ֵ���ȴ�����мܵ�ס����$P"
					   HIR "��һ�����£���ʱ��Ѫ������"NOR"\n");
	} else
	{
		msg += CYN "$p" CYN "�ٵ�һ����Ӳ������$P"
		       CYN "��һ���ܿ���˿������"NOR"\n";
	}

	// �ڶ���
	ap = me->query_int();
	dp = target->query_int();
	msg += "\n" HIC "$N" HIC "�漴һ����Ц�����е�" + wname +
	       HIC "�����������������£����Ī�⣬��㽣��������$n" HIC "��"NOR"\n";
	if (ap / 2 + random(ap) > dp)
	{
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
					   HIR "$p" HIR "��󲻽⣬һʱ���Կ�͸��"
					   "�а��һ�����˼��У�����������"NOR"\n");
	} else
	{
		msg += CYN "$p" CYN "����һЦ����Ȼ����$P"
		CYN "����������������У����⽫֮�ܿ���"NOR"\n";
	}

	// ������
	ap = me->query_con();
	dp = target->query_con();
	msg += "\n" HIC "$N" HIC "��������һ���������е�" + wname +
	       HIC "�û���һ��ǳǳ�Ĺ�â���˽���һ������$n" HIC "��"NOR"\n";
	if (ap / 2 + random(ap) > dp)
	{
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
					   HIR "$p" HIR "�����ֵ���ֻ����һ��͸������"
					   "Ϯ��������һ�����裬�������̱�ÿտյ�����"NOR"\n");
	} else
	{
		msg += CYN "$p" CYN "һ�����Ե�������������$P"
		CYN "���彣â��Ȼ������ȴδ����$p" CYN "�ֺ���"NOR"\n";
	}

	// ������
	ap = me->query_dex();
	dp = target->query_dex();
	msg += "\n" HIC "$N" HIC "�Ų�һ�Σ���Ȼ��������������죬���е�" + wname +
	       HIC "Ӧ�����𣬴���$n" HIC "��"NOR"\n";
	if (ap / 2 + random(ap) > dp)
	{
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
					   HIR "$p" HIR "ֻ������һ������ʱ��$P"
					   HIR "��һ�����˸����У���Ѫ�Ĵ����䣡"NOR"\n");
	} else
	{
		msg += CYN "$p" CYN "��ȴ�Ǹ��죬ֻ��һ�ˣ���$P"
		CYN "��һ�п���������Ч��"NOR"\n";
	}

	// ������
	ap = me->query_skill("sword");
	dp = target->query_skill("parry");
	msg += "\n" HIC "$N" HIC "һ����̾�������ú������飬" + wname +
	       HIC "���ƶ�ת�����¿���ɪɪ����Ȼ��ɱ������������������˵����Ĳ���֮�⡣"NOR"\n";
	if (ap / 2 + random(ap) > dp)
	{
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
					   HIR "$p" HIR "ֻ������ԡ�ڷ���һ�㣬�����о�Ȼ���޿ɵֵ�����"
					   HIR "�������˸�Ѫ��ģ����"NOR"\n");
	} else
	{
		msg += CYN "$p" CYN "�侲�Ƿ���˿����Ϊ����õ�����"
		       "����������ֵ�����©���������"NOR"\n";
	}

	me->start_busy(2 + random(5));
	me->add("neili", -400 - random(100));
	message_combatd(msg, me, target);
	return 1;
}
