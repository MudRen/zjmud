// juan.c ���־�

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���"ZJBR"����"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	int ap, dp;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("xuantie-jian", 1) < 70)
		return notify_fail("�����������������죬����ʹ�þ��־���\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���򲻹�������ʹ�þ��־���\n");

	if ((int)me->query("neili") < 100 )
		return notify_fail("����������̫��������ʹ�þ��־���\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	if (me->query_skill_mapped("sword") != "xuantie-jian")
		return notify_fail("��û�м�����������������ʩչ���־���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$Nһ�����е�" + weapon->name() + HIY "�����¶��ϵĳ�$n"
	      HIY "���˹�ȥ���������ۣ��仯�޳���"NOR"\n";

	ap = me->query_skill("sword");
	dp = target->query_skill("dodge");
	if (ap + random(ap / 2) > dp)
	{
		target->start_busy(ap / 20 + 2);
		me->add("neili", -50);
		msg += YEL "$p" YEL "��æ�����мܣ�һʱ��Ͼ������"NOR"\n";
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ��бԾ�ܿ���$P"
		       CYN "�Ĺ�����"NOR"\n";
		me->add("neili", -25);
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
