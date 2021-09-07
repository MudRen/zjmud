// luan.c �ҵ���

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "�ҵ���"; }

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
		return notify_fail("���ҵ�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("�����õ�����ʩչ���ҵ�������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("��������������޷�ʩչ���ҵ�������\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹�������ʩչ���ҵ�������\n");

	if ((int)me->query_skill("dongyang-dao", 1) < 80)
		return notify_fail("��Ķ��󵶷��������ң��޷�ʹ���ҵ�����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "\n$N" HIY "�ٺ�һ����Ц�����е�" + weapon->name() +
	      HIY "��ͻ���죬�����������벻���ĵط�����$n"
	      HIY "��"NOR"\n";
	message_combatd(msg, me, target);
	me->add("neili", -100);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(2) && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->start_busy(1 + random(5));
	return 1;
}
