// duan.c

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "���־�"; }
string *pfm_type() { return ({ "blade", }); }

int perform(object me, object target)
{
	object weapon, ob;
	string msg, string1;
	int count;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�廢���ŵ����ϡ��־�ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("blade") < 120)
		return notify_fail("����廢���ŵ��������ң��޷�ʹ�á��ϡ��־���\n");

	if (me->query_skill_mapped("blade") != "wuhu-duanmendao")
		return notify_fail("��û�м����廢���ŵ����޷�ʹ�á��ϡ��־���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "��Ȼ���أ�ʹ���廢���ŵ����ϡ��־�����"
	      "ʱһƬ�׹�ֱ��ǰ��ȥ��"NOR"\n";
	message_combatd(msg, me);

	me->clean_up_enemy();
	ob = me->select_opponent();

	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));
	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));
	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));

	me->add("neili", -150);
	me->start_busy(1 + random(3));

	return 1;
}
