// ���ɷ����־�

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���־�"; }

int perform(object me, object target)
{
	string msg;
	int neili, damage;
	int i;

	if (! target ) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���ɷ����־�ֻ����ս���жԶ���ʹ�á�\n");

	if ((int)me->query_skill("shedao-qigong", 1) < 100)
		return notify_fail("����ߵ��湦������죬����ʹ�ó��ɷ����־���\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("�����ﲻ�ܹ������ˡ�\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("���Ѿ���ƣ���ߣ����������ˡ�\n");

	neili = me->query("max_neili");

	me->add("neili", -(300 + random(200)));
	me->receive_damage("qi", 10);

	me->start_busy(1 + random(5));

	message_combatd(HIY "$N" HIY "�������һ��������Ȼ���쳤Х����"
			"����У�����������Ψ�Ҳ��ܣ�"NOR"\n", me);

	if (neili / 2 + random(neili / 2) < (int)target->query("max_neili"))
		return notify_fail("���˵�������ѷ���㣬�˲��ˣ�\n");
		
	damage = (neili - (int)target->query("max_neili")) / 10;
	if (damage > 0)
	{
		target->receive_damage("jing", damage, me);
		target->receive_damage("qi", damage, me);
		target->receive_wound("jing", damage / 8, me);
		target->receive_wound("qi", damage / 8, me);
		message_combatd(HIR "$N" HIR "ֻ������һ���ʹ��������"
				"ð��������������������ǰ�趯��"NOR"\n", target);
	}
	me->want_kill(target);
	me->kill_ob(target);
	return 1;
}
