// yao1.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(RED "��ҩ" NOR, ({ "gaoyao" }));
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "����ȥ����ֵ�һ����ҩ����ߺ��ߺڡ�\n");
		set("unit", "��");
		set("value", 500);
		set("can_be_applied", 1);
	}
	setup();
}

int do_apply(object me)
{
	write("��˺��ҩ������ֻ��һ��ֽ���и���Ŀ��Ի����ȥ�帴����ҩ����\n");
	destruct(this_object());
	return 1;
}
