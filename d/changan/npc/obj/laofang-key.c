//laofang-key.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIC "�η�Կ��" NOR, ({"laofang key", "key"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else 
	{
		set("unit", "��");
		set("long", "һ���η�Կ�ס�\n");
	}
  
	set("is_monitored", 1);
	setup();
}


