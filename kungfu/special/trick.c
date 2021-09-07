// trick.c ����ƪ
// Created by Doing Lu 10/7/2K

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

string name() { return HIM "����ƪ" NOR; }

int perform(object me, string skill)
{
	int heal;
	int ap, dp;
	object target;

	if (me->query("jing") < 50)
		return notify_fail("��ľ��񲻼ã����Թ�˼���ԡ�\n");

	me->clean_up_enemy();
	target = me->select_opponent();

	if (! me->is_fighting())
		return notify_fail("���ֲ����ڴ�ܣ�û��˵�Ѹ�ʲô��\n");

	if (! target->query("can_speak") || target->query("not_living"))
		return notify_fail("��ϧ��������" + target->name() +
				   "����������Ļ��ˡ�\n");

	message_vision(HIM "$N" HIM "�鼱���ǣ�����$n" HIM
		       "������һ�׳�ƪ���ۣ��������컨��׹��\n",
		       me, target);
	ap = me->query_int();
	dp = target->query_int();
	if (me->query("character") == "������")
		ap += ap / 4;
	if (me->query("character") == "���ռ�թ")
		ap += ap / 6;

	me->receive_damage("jing", 30 + random(20));

	if (ap / 3 + random(ap) > random(dp + 10))
	{
		// ʩչ����ƪ�ɹ�
		message_vision(HIM "$n" HIM "�������κ�������֪���ԣ�"
			       "��ֻ�ǻ���һ����$N" HIM "�û����ߡ�"NOR"\n",
			       me, target);
		me->set_temp("success_flee", HIG "��ɹ��������ˣ�"NOR"\n");
		GO_CMD->do_flee(me);
	} else
	{
		message_vision(CYN "$n" CYN "����ĵ�$N" CYN
			       "˵�꣬�ŵ������㻹�������˰�"
			       "����˵�վ���һ�У�"NOR"\n",
			       me, target);
		me->start_busy(1 + random(4));
	}

	return 1;
}
