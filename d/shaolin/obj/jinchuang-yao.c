// jinchuang-yao.c ��ҩ

#include <ansi.h>

inherit ITEM;

void create()
{

	set_name("��ҩ", ({"jin chuangyao", "yao"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�������Ч�����ֽ�ҩ��ר�������˵ȡ�\n");
		set("value", 2000);
		set("only_do_effect", 1);
	}

	set("shaolin",1);
	setup();
}

int do_effect(object me)
{
	if (me->query("eff_qi") == me->query("max_qi"))
		return notify_fail("�����ڲ���Ҫ�ý�ҩ��\n");
	
	me->start_busy(1);
	me->receive_curing("qi", 50);
	message_vision(HIC "$N" HIC "����һ����ҩ��ֻ��������"
		       "������ɫ�������ö��ˡ�"NOR"\n", me);

	destruct(this_object());
	return 1;
}

