// longxia.c ��Ϻ

inherit ITEM;

#include <ansi.h>
#include "xia.h";

void create()
{
	set_name("��Ϻ", ({ "long xia", "longxia" }) );
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "һֻ����Ĵ���Ϻ��\n");
		set("unit", "ֻ");
	}

	setup();
}
