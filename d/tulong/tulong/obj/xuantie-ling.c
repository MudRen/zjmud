#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(CYN "������" NOR, ({ "xuantie ling", "xuantie", "ling"}) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "һ�����������ƣ���������������\n" );
		set("value", 1);
	}
}

int is_container() { return 1; }


