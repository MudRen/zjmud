#pragma save_binary

#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
	set_name(WHT "���˵����콣" NOR, ({ "duan jian","sword" }) );
	set_weight(10000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("icon", "05060");
		set("long", "һ�����˵ĳ���\n");
		set("value", 0);
		set("rigidity",8000);   
		set("material", "steel");
	}
	init_sword(1);
	setup();
}

