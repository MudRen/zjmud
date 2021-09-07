// jianzhang.c  ����������

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int i;
	int count;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("����������������ʼʱ��������һ�ѽ���\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("��������������޷�ʩչ����������������\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹�������ʩչ����������������\n");

	if ((int)me->query_skill("huashan-sword", 1) < 50)
		return notify_fail("��Ļ�ɽ�����������ң��޷�ʹ�ý�����������\n");

	if (me->query_skill_mapped("sword") != "huashan-sword")
		return notify_fail("��û�м�����ɽ�������޷�ʹ�á���������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "ʹ����ɽ�ɾ�����������������������Ȼ�ӿ죡"NOR"\n";
	message_combatd(msg, me);
	me->add("neili", -100);

	count = me->query_skill("sword") / 10;
	me->add_temp("apply/attack", count);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(5));
	return 1;
}
