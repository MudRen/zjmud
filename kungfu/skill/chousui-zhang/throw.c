// throw.c ������ʩ��

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }

int perform(object me, object target)
{
	object obj;
	string msg;
	int lvl;

	if (! target) target = offensive_target(me);

	if (environment(me)->query("no_fight"))
		return notify_fail("���ﲻ�ܹ�������! \n");

	if (! target || ! target->is_character())
		return notify_fail("ʩ��ֻ�ܶԶ���ʹ�á�\n");

	if (target->query("not_living"))
		return notify_fail("��������ǲ��ǻ��ˡ�\n");

	if ((int)me->query_skill("huagong-dafa", 1) < 40)
		return notify_fail("��Ļ����󷨲�����죬����ʩ����\n");

	if ((int)me->query_skill("chousui-zhang", 1) < 40)
		return notify_fail("��ĳ����Ʋ�����죬����ʩ����\n");

	if (! (objectp(obj=present("corpse", environment(me)))  ||  objectp(obj = present("corpse", me)) ||
	    objectp(obj = present("Skeleton", environment(me))) ||  objectp(obj = present("Skeleton", me))) )
		return notify_fail("����Χû��ʬ�壬�޷�ʩչ������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = CYN "$N" CYN " ˳��ץ��ʬ�壬�������������ϣ�����$n" CYN "��"NOR"\n";

	if (random(lvl = (int)me->query_skill("chousui-zhang", 1)) >
	    target->query_skill("dodge") / 2)
	{
		msg += HIR " ���$p" HIR "��$P" HIR "���˸����ţ�"NOR"\n";
		target->receive_damage("qi",(int)me->query_skill("chousui-zhang", 1), me);
		target->receive_wound("qi",15 + random(10), me);
		target->receive_wound("jing", 10, me);
		target->affect_by("xx_poison",
			       ([ "level" : me->query("jiali") + random(me->query("jiali")),
				  "id"    : me->query("id"),
				  "duration" : lvl / 50 + random(lvl / 20) ]));
		me->start_busy(2);
	} else
	{
		msg += CYN "����$p" CYN "��æ����һ�ԣ����˿�ȥ��"NOR"\n";
		me->start_busy(4);
	}
	message_combatd(msg, me, target);
	destruct(obj);
	return 1;
}
