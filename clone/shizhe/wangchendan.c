// jinsha.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "������" NOR, ({ "wangchen dan" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "�����ɫ��Ԫ���ͻ�Ա��ص��������ݡ�\n");
		set("unit", "��");
		set("value", 500000);
		set("yuanbao", 1200);
		set("only_do_effect", 1);
		set("weight", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision(CYN "$N" CYN "С�ĵķ�����" + name() + CYN "������������ա�"NOR"\n", me);
	UPDATE_D->init_player(me);
	destruct(this_object());
	return 1;
}
