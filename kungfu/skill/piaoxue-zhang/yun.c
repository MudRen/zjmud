// yun.c

#include <ansi.h>
#include <combat.h>

#define YUN "��" HIW "�ƺ�����" NOR "��"

inherit F_SSERVER; 
 
string query_name() { return "�ƺ�"ZJBR"����"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
 
	if (userp(me) && ! me->query("can_perform/piaoxue-zhang/yun"))
		return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

	if (! target) target = offensive_target(me); 
	
	if (! target || ! me->is_fighting(target)) 
		return notify_fail(YUN "ֻ����ս���жԶ���ʹ�á�\n");
	 
	if (me->query_temp("weapon") || 
	    me->query_temp("secondary_weapon")) 
		return notify_fail("�������ֲ���ʩչ" YUN "��\n");
	 
	if (me->query_skill("force") < 200) 
		return notify_fail("����ڹ�����Ϊ�������޷�ʩչ" YUN "��\n");
	
	if (me->query_skill("piaoxue-zhang", 1) < 150) 
		return notify_fail("���Ʈѩ��������Ϊ�������޷�ʩչ" YUN "��\n");
	 
	if (me->query("neili") < 200 || me->query("max_neili") < 2000) 
		return notify_fail("��������������޷�ʩչ" YUN "��\n");

	if (me->query_skill_mapped("strike") != "piaoxue-zhang") 
		return notify_fail("��û�м���Ʈѩ�����ƣ��޷�ʩչ" YUN "��\n");

	if (me->query_skill_prepared("strike") != "piaoxue-zhang")
		return notify_fail("��û��׼��ʹ��Ʈѩ�����ƣ��޷�ʩչ" YUN "��\n");

	if (! living(target))
	       return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "һ�����ȣ���Ȼʩ��Ʈѩ�����ƾ������ƺ����ơ���˲"
	      "�������������С�"NOR"\n";
	message_combatd(msg, me);

	me->add("neili", -100);

	// ��һ��
	me->add_temp("apply/attack", 30);
	COMBAT_D->do_attack(me, target, weapon, 0);

	// �ڶ���
	me->add_temp("apply/attack", 60);
	COMBAT_D->do_attack(me, target, weapon, 0);

	// ������
	me->add_temp("apply/attack", 90);
	COMBAT_D->do_attack(me, target, weapon, 0);

	// ������������
	me->add_temp("apply/attack", -180);

	me->start_busy(2 + random(3));

	return 1;
}
