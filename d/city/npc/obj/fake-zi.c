// puti-zi.c ������

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("������", ({"puti zi", "zi"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�ž�Ө����������ӣ�������ɽ������ǰ����ϡ�ޱȣ�
������������֮ʵ�����ܻ��ٽ٣���ǧ�֣������ͬ�١�\n");
		set("value",100);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision(HIR "$N" HIR "����һ��������... ���ã�"NOR"\n", me);
	me->unconcious();
	destruct(this_object());
	return 1;
}
