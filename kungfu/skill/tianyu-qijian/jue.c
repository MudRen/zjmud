// yu.c  ������

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "������"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	if ((int)me->query_skill("tianyu-qijian", 1) < 60)
		return notify_fail("��������潣������죬����ʹ����������\n");

	if ((int)me->query_skill("force") < 90)
		return notify_fail("����ڹ�ʵ��̫�û���á�����������\n");

	if ((int)me->query("neili", 1) < 300)
		return notify_fail("����������̫��������ʹ�á�����������\n");
			
	if (me->query_skill_mapped("sword") != "tianyu-qijian")
		return notify_fail("��û�м��������潣��û���á�����������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "����΢΢һ��������һ̽��һ�����⼲������$n��"NOR"\n";
	me->add("neili", -70);

	ap = me->query_skill("sword");
	dp = target->query_skill("parry");
	if (ap / 2 + random(ap) > dp)
	{
		target->start_busy((int)me->query_skill("tianyu-qijian", 1) / 23 + 1);
		msg += HIR "$n" HIR "���һ������æ�мܣ���һ�±�ʧ���Ȼ���"NOR"\n";
	} else 
	{
		msg += CYN "����$p" CYN "���Ų�æ�������˴���"
		       "��ʵ����û���ܵ����Ӱ�졣"NOR"\n";
		me->add("neili", -100);
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}
