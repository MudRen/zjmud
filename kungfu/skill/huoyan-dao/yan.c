#include <ansi.h>
#include <combat.h>

#define YAN "��" HIR "�������" NOR "��"

inherit F_SSERVER; 
 
string query_name() { return "���"ZJBR"����"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
 
	if (! target) target = offensive_target(me); 
	
	if (! target || ! me->is_fighting(target)) 
		return notify_fail(YAN "ֻ����ս���жԶ���ʹ�á�\n");
	 
	if (me->query_temp("weapon") || 
	    me->query_temp("secondary_weapon")) 
		return notify_fail("�������ֲ���ʩչ" YAN "��\n");
	 
	if (me->query_skill("force") < 200) 
		return notify_fail("����ڹ�����Ϊ�������޷�ʩչ" YAN "��\n");
	
	if (me->query_skill("huoyan-dao", 1) < 150) 
		return notify_fail("��Ļ��浶��Ϊ�������޷�ʩչ" YAN "��\n");
	 
	if (me->query("neili") < 600 || me->query("max_neili") < 2000) 
		return notify_fail("��������������޷�ʩչ" YAN "��\n");

	if (me->query_skill_mapped("strike") != "huoyan-dao") 
		return notify_fail("��û�м������浶���޷�ʩչ" YAN "��\n");

	if (me->query_skill_prepared("strike") != "huoyan-dao")
		return notify_fail("��û��׼�����浶���޷�ʩչ" YAN "��\n");

	if (me->query_skill_prepared("hand") == "dashou-yin")
		return notify_fail("ʩչ" YAN "ʱ���浶���˺����ڴ���ӡ������\n");

	if (! living(target))
	       return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "һ��ŭ�����������ע�뵥�ƣ���Ե��ʱ����һ�����ף��Ӷ�������$n"
	      HIR "��ȥ��"NOR"\n";
	message_combatd(msg, me, target);

	me->add("neili", -500);

	me->add_temp("apply/attack", 10);
	COMBAT_D->do_attack(me, target, weapon, 0);

	me->add_temp("apply/attack", 10);
	COMBAT_D->do_attack(me, target, weapon, 0);

	me->add_temp("apply/attack", 10);
	COMBAT_D->do_attack(me, target, weapon, 0);

	me->add_temp("apply/attack", 10);
	COMBAT_D->do_attack(me, target, weapon, 0);

	me->add_temp("apply/attack", 10);
	COMBAT_D->do_attack(me, target, weapon, 0);

	// ������������
	me->add_temp("apply/attack", -50);

	me->start_busy(3 + random(2));

	return 1;
}

