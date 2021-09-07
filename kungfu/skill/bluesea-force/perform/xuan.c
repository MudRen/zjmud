// yong.c ����������

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	string msg;
	int count;
	int lvl;
	int i,ap,dp;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (me->query("neili") < 200)
		return notify_fail("��������������޷�ʩչ���������ƣ�\n");

	if ((lvl = me->query_skill("bluesea-force", 1)) < 150)
		return notify_fail("����Ϻ�������򲻹����޷�ʩչ���������ƣ�\n");

	if (me->query_skill_mapped("strike") != "bluesea-force")
		return notify_fail("��û�м����Ϻ�����Ϊ�Ʒ����޷�ʩչ���������ƣ�\n");

	if (me->query_skill_prepared("strike") != "bluesea-force")
		return notify_fail("��û��׼����ʹ���Ϻ��������޷�ʩչ���������ƣ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	ap = me->query_skill("strike") + me->query("con") * 20 +
	     me->query_skill("martial-cognize", 1);
	dp = target->query_skill("force") + target->query("con") * 20 +
	     target->query_skill("martial-cognize", 1);


	msg = HIC "$N" HIC "���Ữ�˸�Ȧ�ӣ����κ�Ȼ��죬������Ϊһ������$n"
	      HIC "��"NOR"\n";
	i = 5;
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIY "��������֮�£�$n" HIY "��ʱ���ú���"
		       "����������������ѹ��������ܣ�ֻ��$N"
		       HIY "һ�ƽ�һ�ƵĹ��������纣�ˡ�"NOR"\n";
		count = me->query_skill("bluesea-force", 1) / 5;
		me->add_temp("apply/attack", count);
		i += random(5);
	} else
	{
		msg += CYN "$n" CYN "��������죬ֻ���������������ֵ���"NOR"\n";
		count = 0;
	}

	message_combatd(msg, me, target);
	me->add("neili", -i * 20);

	while (i--)
	{
		if (! me->is_fighting(target))
			break;
		if (i > 5 && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, 0, 0);
	}
	target->interrupt_me(target, 1);

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(7));
	return 1;
}
