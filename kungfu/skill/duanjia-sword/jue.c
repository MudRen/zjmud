// jue.c �����

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "���"ZJBR"����"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int i;

	if (userp(me) && ! me->query("can_perform/duanjia-sword/jue"))
		return notify_fail("�����ڻ�����ʹ���������\n");
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("�μ������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword" &&
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("�����ֽ����Ȳ���ʩչ�μ��������\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("duanjia-sword", 1) < 100)
		return notify_fail("��Ķμҽ����������ң��޷�ʹ���������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "����һ���������²�������������֮�������е�" +
	      weapon->name() + HIY "ʹ���������һ�㣬������$n" HIY "��"NOR"\n";
	message_combatd(msg, me, target);
	me->add("neili", -100);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(5) == 0 && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->start_busy(1 + random(5));
	return 1;
}
