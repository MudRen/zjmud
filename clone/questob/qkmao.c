// qkmao.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("Ǭ��ñ", ({ "qiankun mao", "mao" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��СС�ĺ�ñ�ӣ��������˼��ű�ʯ��\n");
		set("value", 10000);
		set("material", "cloth");
	}
	setup();
}
