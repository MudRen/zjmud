// ruyi.c ��������

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "blade", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int i;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (!objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("����û�У�ʹʲô��������������\n");

	if ((int)me->query("neili") < 250)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 145 )
		return notify_fail("����ڹ���򲻹���\n");

	if (me->query_skill("blade") < 135)
		return notify_fail("������⵶���������ң��޷�ʹ�á�������������\n");

	if (me->query_skill_mapped("blade") != "ruyi-dao")
		return notify_fail("��û�м������⵶�����޷�ʹ�á�������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "ʹ����ң����������������������Ȼ����ޱȣ����Ī�⣡"NOR"\n";
	message_combatd(msg, me);
	me->add("neili", -120);

	for (i = 0; i < 6; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->start_busy(1 + random(6));

	return 1;
}
