// fei.c ������

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "�ߵ�"ZJBR"����"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int count;
	int i;

	if (userp(me) && ! me->query("can_perform/shedao-qigong/fei"))
		return notify_fail("�����ڻ�����ʹ�÷�������\n");
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("�ߵ�������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword" &&
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("�����ֽ����Ȳ���ʩչ�ߵ���������\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("shedao-qigong", 1) < 100)
		return notify_fail("����ߵ��湦����Ϊ���������ң��޷�ʹ�÷�������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	switch (random(3))
	{
	case 0:
		msg = HIY "$N" HIY "�ֽ�һ�������е�" + weapon->name() +
		      HIY "һ�Σ�����������Ӱ����$n" HIY "��"NOR"\n";
		break;

	case 1:
		msg = HIY "$N" HIY "���������дʣ����е�" + weapon->name() +
		      HIY "ԽʹԽ�죬�����γ�һ�Ź�â��������$n" HIY "��"NOR"\n";
		break;

	default:
		msg = HIY "$N" HIY "��Ц�������������������������죬���е�" +
		      weapon->name() + HIY "��Ȼ������һ�����б���$n" HIY "��"NOR"\n";
		break;
	}

	message_combatd(msg, me, target);
	me->add("neili", -100);
	count = me->query_skill("shedao-qigong", 1) / 6;
	me->add_temp("apply/attack", count);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(3) == 0 && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(5));
	return 1;
}
