// cao.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("���Ĳ�", ({"fuxin cao", "cao"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ���޸�С�ݣ����ú�С��ȴ����һ���������ٵĸо���\n");
		set("only_do_effect", 1);
	}

	setup();
}

int do_effect(object me)
{
	message_vision(HIG "$N" HIG "����һ�긯�Ĳݣ���"
		       "Ȼ���е������...�Ͻ�ȥ������"NOR"\n", this_player());
	destruct(this_object());
	return 1;
}
