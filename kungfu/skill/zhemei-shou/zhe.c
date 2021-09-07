// zhe.c ��÷ʽ
 
#include <ansi.h>
 
inherit F_SSERVER;
 
string query_name() { return "��÷ʽ"; }
string *pfm_type() { return ({ "hand", }); }

int perform(object me, object target)
{
	string msg;
	object weapon, weapon2;
	int skill, ap, dp;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("����÷ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʩչ����÷ʽ����\n");

	if (target->is_busy())
		return notify_fail("�Է�����������æ���ҵ��أ��㲻�ص��ġ�\n");

	skill = me->query_skill("zhemei-shou", 1);

	if (skill < 100)
		return notify_fail("�����ɽ��÷�ֵȼ����������ܡ���÷ʽ����\n");

	if (me->query_skill("force") < 200)
		return notify_fail("���ڹ���򲻹���ʹ��������÷ʽ����\n");

	if (me->query("neili") < 100)
		return notify_fail("��������������޷�ʩչ����÷ʽ����\n");
 
	if (me->query_skill_prepared("hand") != "zhemei-shou")
		return notify_fail("��û��׼��ʹ����÷�֣��޷�ʩչ����÷ʽ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "����ץ��������ʵʵ������$n" HIC
	      "�ҪѨ��"NOR"\n";
	message_combatd(msg, me, target);
 
	ap = me->query_skill("hand");
	dp = target->query_skill("parry");
	me->add("neili", -40);
	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili", -30);
		msg = HIY "$n" HIY "��ͷһ������æ����������"
		      "һʱ���޷�������"NOR"\n";
		target->start_busy(ap / 30 + 2);
	} else
	{
		msg = CYN "����$p" CYN "�Ŀ�����$P" CYN
		      "����ͼ����Ϊ��������$P" CYN "��"
		      "����û������κ����á�"NOR"\n";
		me->start_busy(1);
	}
	message_combatd(msg, me, target);
	return 1;
}
