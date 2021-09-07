// duo.c ���������
 
#include <ansi.h>
 
inherit F_SSERVER;

string query_name() { return "���ʽ"; }
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
		return notify_fail("�����ֶ���С�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʩչ�����ֶ���С���\n");

	if (! objectp(weapon2 = target->query_temp("weapon")))
	   return notify_fail("�Է�û�б��У��㲻�õ��ġ�\n");

	skill = me->query_skill("zhemei-shou", 1);

	if (skill < 100)
		return notify_fail("�����ɽ��÷�ֵȼ����������ܡ����ֶ���С���\n");

	if (me->query_skill("force") < 200)
		return notify_fail("���ڹ���򲻹���ʹ���������ֶ���С���\n");

	if (me->query("neili") < 100)
		return notify_fail("��������������޷���������У�\n");
 
	if (me->query_skill_prepared("hand") != "zhemei-shou")
		return notify_fail("��û��׼��ʹ����÷�֣��޷�ʩչ����÷ʽ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "�����Ϣ��˫�ֲ���$n" HIC
	      "������֮������ͼ�������ı��С�"NOR"\n";
	message_combatd(msg, me, target);
 
	ap = me->query_skill("hand");
	dp = target->query_skill("parry") * 3 / 2;
	me->add("neili", -50);
	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili", -50);
		msg = HIY "$n" HIY "��ʱ������ǰһ��������һ�飬��"
		     "�б������ֶ�����"NOR"\n";
		weapon2->move(me, 1);
		me->start_busy(2);
	}
	else
	{
		msg = CYN "����$p" CYN "�Ŀ�����$P" CYN
		      "����ͼ�����̲�ȡ���ƣ�ʹ$P" CYN "û�ܶ���$p"
		      CYN "�ı��С�"NOR"\n";
		me->start_busy(3);
	}
	message_combatd(msg, me, target);
	return 1;
}
