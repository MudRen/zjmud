// self.c С������ת
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "С������ת" NOR; }

int perform(object me, string skill)
{
	int heal;

	if (me->query("jing") < 80)
		return notify_fail("��ľ������������ڻ�����ʩչС������ת��\n");

	if (me->is_fighting())
		return notify_fail("�����ڴ�ܣ��޷�ʹ��С������ת��\n");

	if (me->query("qi") >= me->query("eff_qi"))
		return notify_fail("��������ܺã�û�б�Ҫʹ��С������ת��\n");

	message_vision(HIC "$N" HIC "˫��ƽ�٣������³���һ"
		       "��������ɫ���Բ����ˡ�"NOR"\n", me);
	tell_object(me, HIG "��о�����������ָ��ˡ�"NOR"\n");

	me->receive_damage("jing", 60 + random(20));
	heal = me->query_con() * 10;
	me->receive_heal("qi", heal);
	me->start_busy(1 + random(5));
	return 1;
}
