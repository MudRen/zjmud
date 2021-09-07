#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"Ǭ��"; }
string *pfm_type() { return ({ "club", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int count;
	int i, attack_time;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("������Ǭ����ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "club")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill_mapped("club") != "qujing-gunfa")
		return notify_fail("�����ڲ�δ����ȡ��������ʹ����������Ǭ������\n");

       if(me->query_skill("qujing-gunfa", 1) < 160 )
		return notify_fail("���ȡ��������������죬ʹ����������Ǭ������\n");

       if( (int)me->query_skill("force") < 200 )
		return notify_fail("����ڹ��ȼ�������ʹ����������Ǭ������\n");

	if( (int)me->query("max_neili") < 1800 )
		return notify_fail("����������̫����ʹ����������Ǭ������\n");      

	if( (int)me->query("neili") < 200 )
		return notify_fail("����������̫����ʹ����������Ǭ������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "\n$N" HIW "�����е�" + weapon->name() + HIW "������$n"
	      HIW "ѹȥ�����˾��������з���֮��������ȡ��������ɱ�š�"
	      NOR + HIR "����Ǭ��" NOR + HIW "����\n��Ȼ����˹�â��"
	      "�ǣ��ó�������" + weapon->name() + HIW "�����籼�׳���"
	      "������ǵ���$n" HIW "ϯ���ȥ��"NOR"\n";

	ap = me->query_skill("club");
	dp = target->query_skill("parry");
	attack_time = 5;
	if (ap / 2 + random(ap * 2) > dp)
	{
		msg += HIR "\n���$n" HIR "��$N" HIR
		       "���˸����ֲ�����Ŀ�Ӳ�Ͼ��ƣ�ڱ�����"NOR"\n";
		count = ap / 10;
		me->add_temp("apply/attack", count);
		attack_time += random(ap / 45);
	} else
	{
		msg += HIC "$n" HIC "��$N" HIC "������磬������Ȼ������Ӧ����"NOR"\n";
		count = 0;
	}
		
	message_combatd(msg, me, target);

	if (attack_time > 10)
		attack_time = 10;

	me->add("neili", -attack_time * 20);

	for (i = 0; i < attack_time; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(attack_time));
	return 1;
}

