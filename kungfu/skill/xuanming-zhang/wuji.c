#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "��ڤ"ZJBR"�޼�"; }

int perform(object me, object target)
{
	int damage;
	string msg;
	int ap, dp;
	int lvl;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ڤ�޼�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ����ڤ�޼���\n");	 

	if ((int)me->query_skill("xuanming-zhang", 1) < 150)
		return notify_fail("�����ڤ���Ʋ�������������ʹ����ڤ�޼���\n");

	if ((int)me->query("max_neili") < 2000)
		return notify_fail("���������Ϊ���㣬�޷�ʹ����ڤ�޼���\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("��������������޷�ʹ����ڤ�޼���\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = MAG "$N������ڤ�񹦣�ȫ���ֳ�һ����������Ȼ��˫�Ʒ��ڣ�ʩ"
		    "չ��������ڤ\n�޼���Я���������������֮�����ƾ��ѹ���$n��"NOR"\n";  

	lvl = me->query_skill("xuanming-zhang", 1);
	ap = me->query_skill("strike") + me->query("str") * 10;
	dp = target->query_skill("dodge") + target->query("dex") * 10;
	me->start_busy(4);
	if (ap / 2 + random(ap) > dp)
	{ 
		damage = ap + random(ap);
		me->add("neili", -400);
		target->apply_condition("xuanming_poison", lvl +
					(int)target->query_condition("xuanming_poison"));
				  msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
	       MAG "$nֻ����ǰ��Ӱ�ζ���ͻȻ���ؿ�һ����֪���Ʋ��ֻ���ؿڴ�һ��\n�������𣬾�������������"NOR"\n");
	} else
	{
		msg += HIY "$n����$N������ӿ����æ����Ծ����"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
