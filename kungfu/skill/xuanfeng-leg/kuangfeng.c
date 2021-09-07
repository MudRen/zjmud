// kuangfeng.c  ������

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "���"ZJBR"����"; }
string *pfm_type() { return ({ "unarmed", }); }

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
		return notify_fail("����������ֻ����ս���жԶ���ʹ�á�\n");
 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������������ʼʱ�������ű�����\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ�ˮƽ������\n");

	if ((int)me->query_skill("luoying-shenzhang", 1) < 100 ||
	    me->query_skill("xuanfeng-leg", 1) < 100)
		return notify_fail("������ƹ��򻹲����ң��޷�ʹ�ÿ�������\n");

	if (sizeof(me->query_skill_prepare()) &&
	    me->query_skill_prepared("unarmed") != "xuanfeng-leg")
		return notify_fail("��û��׼�������ȷ����޷�ʩչ��������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "ʹ���һ���������������������Ʈ��"
	      "�������������ɣ�"NOR"\n";
	message_combatd(msg, me);
	me->add("neili", -100);

	for (i = 0; i < 6; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(3) == 0 && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, 0, 0);
	}

	me->start_busy(1 + random(6));
	return 1;
}
