// da.c ���ߴ��ߴ�

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"�ߴ�"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int lvl;
 
	weapon = me->query_temp("weapon");

	if( !target )
		return notify_fail("��Ҫ�������ߣ�\n");

	if( !target->is_snake() )
		return notify_fail("�����Щ���ǲ����ߣ���Ϲ��ʲô��\n");

	if( !living(target) )
		return notify_fail("��������ʱ���ᶯ���ˣ��㲻���ٴ��ˡ�\n");

	if( (int)me->query_skill("shedu-qiqiao", 1) < 20 )
		return notify_fail("����߶����ɻ��������, ���ܴ��� !\n");

	if( (int)me->query_skill("force") < 30 )
		return notify_fail("����ڹ�����Ϊ����, ���ܴ��� !\n");

	if( (int)me->query("neili") < 100 )
		return notify_fail("�����ڵ�����������\n");

	if( weapon )
		msg = HIG "\n$N�趯���е�" + weapon->name() + "������" +
		      target->name() + "���ߴ���˹�ȥ��"NOR"\n";
	else
		msg = HIG "\n$N���˫ָ��Ѹ���ޱȵĳ���" +
		      target->name() + "���ߴ���˹�ȥ��"NOR"\n";

	lvl = (int) me->query_skill("shedu-qiqiao", 1) +
	      (int) me->query_skill("dodge");
	lvl = lvl * lvl / 10 * lvl;
	if (lvl / 2 + random(lvl) > (int) target->query("combat_exp"))
	{
		msg += HIM "��ž����������" + target->name() + "���ߴ��ϡ�\n";
		lvl = (int) me->query_skill("force");
		lvl = lvl * 13 / 10;
		lvl = lvl * lvl / 10 * lvl;
		if ( lvl / 2 + random(lvl) > (int) target->query("combat_exp") )
		{
			msg += HIM + target->name() + HIM
			       "��������ζ����£��Ͳ��ٶ�����\n" + NOR;
			message_vision(msg, me);
			target->unconcious();
		} else
		{
			msg += HIW + "�����뵽" + target->name() +
			       HIW "������һ������Ȼ�������£�����\n\n" + NOR;
			message_vision(msg, me);
			target->kill_ob(me);
		}
	} else
	{
		msg += WHT "Ȼ��" + target->name() + WHT "����һ�������˹�ȥ��"NOR"\n";
		message_vision(msg, me);
		target->kill_ob(me);
	}

	me->add("neili", -50);
	me->start_busy(2);

	return 1;
}
